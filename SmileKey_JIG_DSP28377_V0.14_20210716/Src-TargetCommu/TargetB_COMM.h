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
extern int		 Po_Ref, Ir_Ref, Vout_Ref, Poref_Act;

extern Uint16 	 fault_check_delay, flagDecel, stop_flag;
extern Uint16	 B_upload_flag, B_upload_count, system_status, warning_status;

extern long		 flag_set_save1, flag_set_save2;
extern long		 debug_var[10];

extern C1_2	C12;
extern C2_1	C21;

/** public data **/

unsigned char 	txb_flag=0, txb_start=0, txb_end=0, rxb_end=0, rxb_start=0;
unsigned char 	IDB_QUE[MAX_QUE], TXB_QUE[MAX_QUE], maskb[6];
int16		  	RXB_QUE[MAX_QUE];


extern void TargetCommParsing( char ID, int Data, char Ch );

/** public functions **/
void CheckMessageB(void);
void MakePktB(byte msg,word wData);
void scibTxFifoService(void);
void scibRxFifoService(void);
int ChangeSetValue(int wID, char channel);
void scib_fifo_init(void);
void SCIB_INIT_VAL(void);
void RS232_Comm_checkB(void);
int Message_send_end(void);
void SciBAutoBusReset(void);

void SCIB_INIT_VAL( void )
{
	int i;

	for(i=0;i<MAX_QUE;i++){ IDB_QUE[i]=0; TXB_QUE[i]=0;	 RXB_QUE[i]=0; }
	for(i=0;i<6;i++)		maskb[i]=0;
	txb_flag=0; txb_start=0; txb_end=0;
	rxb_end=0; rxb_start=0;
	B_upload_flag=0; B_upload_count=0;
}

#pragma CODE_SECTION(MakePktB, "ramfuncs");
void MakePktB(byte msg,word wData)
{
	byte chksum;

	chksum=msg;
	chksum+=(wData>>8)&0xff;
	chksum+=(wData & 0xff);

	TXB_QUE[txb_end]=ID_START;			if(++txb_end>=MAX_QUE) txb_end=0;
	TXB_QUE[txb_end]=msg;				if(++txb_end>=MAX_QUE) txb_end=0;
	TXB_QUE[txb_end]=(wData>>8)&0xff;	if(++txb_end>=MAX_QUE) txb_end=0;
	TXB_QUE[txb_end]=(wData & 0xff);	if(++txb_end>=MAX_QUE) txb_end=0;
	TXB_QUE[txb_end]=ID_END;			if(++txb_end>=MAX_QUE) txb_end=0;
	TXB_QUE[txb_end]=(chksum & 0xff);	if(++txb_end>=MAX_QUE) txb_end=0;
}

#pragma CODE_SECTION(ChangeSetValue, "ramfuncs");
int ChangeSetValue(int wID, char channel)
{
	int Value;

	if(channel=='b')
	{
		if(RXB_QUE[rxb_start]>SET[model][wID][MAX])		 Value=SET[model][wID][MAX];
		else if(RXB_QUE[rxb_start]<SET[model][wID][MINIMUM]) Value=SET[model][wID][MINIMUM];
		else 											 Value=RXB_QUE[rxb_start];
	}
	return(Value);
}

#pragma CODE_SECTION(scibTxFifoService, "ramfuncs");
void scibTxFifoService(void)
{
//	if(++txa_start>=MAX_QUE) txa_start=0;

	if (txb_flag==1)
	{
		if(++txb_start>=MAX_QUE) txb_start=0;
		if(txb_start!=txb_end) ScibRegs.SCITXBUF=TXB_QUE[txb_start];
		else txb_flag=0;
	}

//	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
}

#pragma CODE_SECTION(scibRxFifoService, "ramfuncs");
void scibRxFifoService(void)
{
	static unsigned char ch, checksum, i;

	for(;ScibRegs.SCIFFRX.bit.RXFFST>0;) {
		ch = ScibRegs.SCIRXBUF.all;
		for(i=0;i<5;i++) maskb[i]=maskb[i+1];
		maskb[5]=ch;
	}

	if((maskb[0]==ID_START) && (maskb[4]==ID_END))
	{
		checksum = maskb[1]+maskb[2]+maskb[3];
		if(maskb[5]==(checksum&0xff))
		{
			IDB_QUE[rxb_end]=maskb[1];
			RXB_QUE[rxb_end]=((unsigned int)maskb[2]<<8)|maskb[3];
			if(++rxb_end >= MAX_QUE)	rxb_end=0;
		}
	}

	ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;	// Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;	// Clear Interrupt flag
}

void SciBAutoBusReset ( void )
{
    if(ScibRegs.SCIRXST.all & 0x80)
    {
        ScibRegs.SCICTL1.all =0x0003;     // Relinquish SCI from Reset
        DELAY_US(1);
        ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
    }
}

void scib_fifo_init()
{
   long	bps_val;

   bps_val = SETRATE;

   ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;

   ScibRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                   // No parity,   8 char bits,
                                   // async mode, idle-line protocol
   ScibRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
   ScibRegs.SCICTL2.bit.TXINTENA =0;	//1
   ScibRegs.SCICTL2.bit.RXBKINTENA =0;	//1;
   ScibRegs.SCIHBAUD = bps_val >> 8;		// High Value
   ScibRegs.SCILBAUD = bps_val & 0xff;		// Low Value


   ScibRegs.SCIFFTX.all=0xC000;	//c020
//	ScibRegs.SCIFFRX.all=0x0021;	//0021
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;
}
