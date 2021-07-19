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
extern Uint16	 D_upload_flag, D_upload_count, system_status, warning_status;

extern long		 flag_set_save1, flag_set_save2;

extern C1_2	C12;
extern C2_1	C21;

/** public data **/

unsigned char 	txd_flag=0, txd_start=0, txd_end=0, rxd_end=0, rxd_start=0;
unsigned char 	IDD_QUE[MAX_QUE], TXD_QUE[MAX_QUE], maskd[6];
int16		  	RXD_QUE[MAX_QUE];


extern void TargetCommParsing( char ID, int Data, char Ch );
/** public functions **/
void CheckMessageD(void);
void MakePktD(byte msg,word wData);
void scidTxFifoService(void);
void scidRxFifoService(void);
int ChangeSetValueD(int wID, char channel);
void scid_fifo_init(void);
void SCID_INIT_VAL(void);
void RS232_Comm_checkD(void);
int Message_send_endD(void);
void SciDAutoBusReset(void);

void SCID_INIT_VAL( void )
{
	int i;

	for(i=0;i<MAX_QUE;i++){ IDD_QUE[i]=0; TXD_QUE[i]=0;	 RXD_QUE[i]=0; }
	for(i=0;i<6;i++)		maskd[i]=0;
	txd_flag=0; txd_start=0; txd_end=0;
	rxd_end=0; rxd_start=0;
	D_upload_flag=0; D_upload_count=0;
}

#pragma CODE_SECTION(MakePktD, "ramfuncs");
void MakePktD(byte msg,word wData)
{
	byte chksum;

	chksum=msg;
	chksum+=(wData>>8)&0xff;
	chksum+=(wData & 0xff);

	TXD_QUE[txd_end]=ID_START;			if(++txd_end>=MAX_QUE) txd_end=0;
	TXD_QUE[txd_end]=msg;				if(++txd_end>=MAX_QUE) txd_end=0;
	TXD_QUE[txd_end]=(wData>>8)&0xff;	if(++txd_end>=MAX_QUE) txd_end=0;
	TXD_QUE[txd_end]=(wData & 0xff);	if(++txd_end>=MAX_QUE) txd_end=0;
	TXD_QUE[txd_end]=ID_END;			if(++txd_end>=MAX_QUE) txd_end=0;
	TXD_QUE[txd_end]=(chksum & 0xff);	if(++txd_end>=MAX_QUE) txd_end=0;
}

#pragma CODE_SECTION(ChangeSetValueD, "ramfuncs");
int ChangeSetValueD(int wID, char channel)
{
	int Value;

	if(channel=='d')
	{
		if(RXD_QUE[rxd_start]>SET[model][wID][MAX])		 Value=SET[model][wID][MAX];
		else if(RXD_QUE[rxd_start]<SET[model][wID][MINIMUM]) Value=SET[model][wID][MINIMUM];
		else 											 Value=RXD_QUE[rxd_start];
	}
	return(Value);
}

#pragma CODE_SECTION(scidTxFifoService, "ramfuncs");
void scidTxFifoService(void)
{
//	if(++txa_start>=MAX_QUE) txa_start=0;

	if (txd_flag==1)
	{
		if(++txd_start>=MAX_QUE) txd_start=0;
		if(txd_start!=txd_end) ScidRegs.SCITXBUF=TXD_QUE[txd_start];
		else txd_flag=0;
	}

//	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
}

#pragma CODE_SECTION(scidRxFifoService, "ramfuncs");
void scidRxFifoService(void)
{
	static unsigned char ch, checksum, i;

	for(;ScidRegs.SCIFFRX.bit.RXFFST>0;) {
		ch = ScidRegs.SCIRXBUF.all;
		for(i=0;i<5;i++) maskd[i]=maskd[i+1];
		maskd[5]=ch;
	}

	if((maskd[0]==ID_START) && (maskd[4]==ID_END))
	{
		checksum = maskd[1]+maskd[2]+maskd[3];
		if(maskd[5]==(checksum&0xff))
		{
			IDD_QUE[rxd_end]=maskd[1];
			RXD_QUE[rxd_end]=((unsigned int)maskd[2]<<8)|maskd[3];
			if(++rxd_end >= MAX_QUE)	rxd_end=0;
		}
	}

	ScidRegs.SCIFFRX.bit.RXFFOVRCLR=1;	// Clear Overflow flag
	ScidRegs.SCIFFRX.bit.RXFFINTCLR=1;	// Clear Interrupt flag
}

void SciDAutoBusReset ( void )
{
    if(ScidRegs.SCIRXST.all & 0x80)
    {
        ScidRegs.SCICTL1.all =0x0003;     // Relinquish SCI from Reset
        DELAY_US(1);
        ScidRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
    }
}

void scid_fifo_init()
{
   long	bps_val;

   bps_val = SETRATE;

   ScidRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScidRegs.SCIFFRX.bit.RXFIFORESET=1;

   ScidRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                   // No parity,   8 char bits,
                                   // async mode, idle-line protocol
   ScidRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
   ScidRegs.SCICTL2.bit.TXINTENA =0;	//1
   ScidRegs.SCICTL2.bit.RXBKINTENA =0;	//1;
   ScidRegs.SCIHBAUD = bps_val >> 8;		// High Value
   ScidRegs.SCILBAUD = bps_val & 0xff;		// Low Value


   ScidRegs.SCIFFTX.all=0xC000;	//c020
//	ScibRegs.SCIFFRX.all=0x0021;	//0021
   ScidRegs.SCIFFCT.all=0x00;

   ScidRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScidRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScidRegs.SCIFFRX.bit.RXFIFORESET=1;
}
