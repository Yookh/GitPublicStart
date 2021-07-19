/*******************************************************************
 *
 *    DESCRIPTION: Communication for LCD - Header file
 *
 *    AUTHOR:	K.H.Yoo
 *
 *    HISTORY:	2011-06-13 Code START
 *
 *******************************************************************/

/** include files **/
#include "F28x_Project.h"
#include "../define.h"
#include "../DUAL_PARAM.h"
/** local definitions **/
#define	MAX_QUE		100

#define	CPUCLK		200000000L				// CPU Main Clock
#define	LSPCLK		(CPUCLK/4)				// Peripheral Low Speed Clock
#define BoudRate	57600L
#define SETRATE		((LSPCLK/(8*BoudRate))-1)

/*	Reference Command from Front Panel to DSP	*/

/** external functions **/

/** external data **/
extern const int SET[M_NUM][SET_NUM][3];
extern int		 BUFF[SET_NUM], model;
extern int 		 model, reset_flag;

extern Uint16 	 fault_check_delay, flagDecel, stop_flag;
extern Uint16	 A_upload_flag, A_upload_count, system_status, warning_status;

extern long		 flag_set_save1, flag_set_save2;

extern C1_2	C12;
extern C2_1	C21;

/** public data **/

unsigned char 	txa_flag=0, txa_start=0, txa_end=0, rxa_end=0, rxa_start=0;
unsigned char 	IDA_QUE[MAX_QUE], TXA_QUE[MAX_QUE], maska[6];
int16		  	RXA_QUE[MAX_QUE];


extern void TargetCommParsing( char ID, int Data, char Ch );
/** public functions **/
void CheckMessageA(void);
void MakePktA(byte msg,word wData);
void sciaTxFifoService(void);
void sciaRxFifoService(void);
int ChangeSetValueA(int wID, char channel);
void scia_fifo_init(void);
void SCIA_INIT_VAL(void);
void RS232_Comm_checkA(void);
int Message_send_endA(void);
void SciAAutoBusReset(void);

void SCIA_INIT_VAL( void )
{
	int i;

	for(i=0;i<MAX_QUE;i++){ IDA_QUE[i]=0; TXA_QUE[i]=0;	 RXA_QUE[i]=0; }
	for(i=0;i<6;i++)		maska[i]=0;
	txa_flag=0; txa_start=0; txa_end=0;
	rxa_end=0; rxa_start=0;
	A_upload_flag=0; A_upload_count=0;
}

#pragma CODE_SECTION(MakePktA, "ramfuncs");
void MakePktA(byte msg,word wData)
{
	byte chksum;

	chksum=msg;
	chksum+=(wData>>8)&0xff;
	chksum+=(wData & 0xff);

	TXA_QUE[txa_end]=ID_START;			if(++txa_end>=MAX_QUE) txa_end=0;
	TXA_QUE[txa_end]=msg;				if(++txa_end>=MAX_QUE) txa_end=0;
	TXA_QUE[txa_end]=(wData>>8)&0xff;	if(++txa_end>=MAX_QUE) txa_end=0;
	TXA_QUE[txa_end]=(wData & 0xff);	if(++txa_end>=MAX_QUE) txa_end=0;
	TXA_QUE[txa_end]=ID_END;			if(++txa_end>=MAX_QUE) txa_end=0;
	TXA_QUE[txa_end]=(chksum & 0xff);	if(++txa_end>=MAX_QUE) txa_end=0;
}

#pragma CODE_SECTION(ChangeSetValueA, "ramfuncs");
int ChangeSetValueA(int wID, char channel)
{
	int Value;

	if(channel=='a')
	{
		if(RXA_QUE[rxa_start]>SET[model][wID][MAX])		 Value=SET[model][wID][MAX];
		else if(RXA_QUE[rxa_start]<SET[model][wID][MINIMUM]) Value=SET[model][wID][MINIMUM];
		else 											 Value=RXA_QUE[rxa_start];
	}
	return(Value);
}

#pragma CODE_SECTION(sciaTxFifoService, "ramfuncs");
void sciaTxFifoService(void)
{
//	if(++txa_start>=MAX_QUE) txa_start=0;

	if (txa_flag==1)
	{
		if(++txa_start>=MAX_QUE) txa_start=0;
		if(txa_start!=txa_end) SciaRegs.SCITXBUF=TXA_QUE[txa_start];
		else txa_flag=0;
	}

//	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
}

#pragma CODE_SECTION(sciaRxFifoService, "ramfuncs");
void sciaRxFifoService(void)
{
	static unsigned char ch, checksum, i;

	for(;SciaRegs.SCIFFRX.bit.RXFFST>0;) {
		ch = SciaRegs.SCIRXBUF.all;
		for(i=0;i<5;i++) maska[i]=maska[i+1];
		maska[5]=ch;
	}

	if((maska[0]==ID_START) && (maska[4]==ID_END))
	{
		checksum = maska[1]+maska[2]+maska[3];
		if(maska[5]==(checksum&0xff))
		{
			IDA_QUE[rxa_end]=maska[1];
			RXA_QUE[rxa_end]=((unsigned int)maska[2]<<8)|maska[3];
			if(++rxa_end >= MAX_QUE)	rxa_end=0;
		}
	}

	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;	// Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;	// Clear Interrupt flag
}

void SciAAutoBusReset ( void )
{
    if(SciaRegs.SCIRXST.all & 0x80)
    {
        SciaRegs.SCICTL1.all =0x0003;     // Relinquish SCI from Reset
        DELAY_US(1);
        SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
    }
}



void scia_fifo_init()
{
   long	bps_val;

   bps_val = SETRATE;

   SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

   SciaRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                   // No parity,   8 char bits,
                                   // async mode, idle-line protocol
   SciaRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL2.bit.TXINTENA =0;	//1
   SciaRegs.SCICTL2.bit.RXBKINTENA =0;	//1;
   SciaRegs.SCIHBAUD = bps_val >> 8;		// High Value
   SciaRegs.SCILBAUD = bps_val & 0xff;		// Low Value


   SciaRegs.SCIFFTX.all=0xC000;	//c020
//	ScibRegs.SCIFFRX.all=0x0021;	//0021
   SciaRegs.SCIFFCT.all=0x00;

   SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
}
