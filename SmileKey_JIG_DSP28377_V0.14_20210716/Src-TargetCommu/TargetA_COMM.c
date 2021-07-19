/*******************************************************************
 *
 *    DESCRIPTION: Communication for LCD
 *	
 *    AUTHOR:	K.H.YOO	
 *
 *    HISTORY: 2011-06-13 CODING START
 *
 *******************************************************************/

/** include files **/
#include "TargetA_COMM.h"
#include "SmileKey_Define.h"

/** local definitions **/

/** default settings **/

/** external functions **/
extern void RUN(void);
extern void STOP(void);
/** external data **/
extern int reset_flag;
extern int cal_flag;
extern int step_flag;

/** internal functions **/

/** public data **/

/** private data **/

/** public functions **/
int Message_send_endA(void);

/** private functions **/

//#pragma CODE_SECTION(CheckMessageA, "ramfuncs");
void CheckMessageA(void)
{
//    int       Cmd_num;

//	Cmd_num = SET_NUM;

	/* Received Command processing */
	if (rxa_start != rxa_end)
	{
	    TargetCommParsing(IDA_QUE[rxa_start], RXA_QUE[rxa_start], 'A');
		if(++rxa_start>=MAX_QUE) rxa_start=0;
	}

	/* Transmit Data trigger */
	if (txa_flag==0 && (txa_start!=txa_end))
	{
		SciaRegs.SCITXBUF = TXA_QUE[txa_start];
		txa_flag=1;
	}
}

void RS232_Comm_checkA(void)
{
    SciAAutoBusReset();
	if(SciaRegs.SCIFFRX.bit.RXFFST>0)  sciaRxFifoService();
	CheckMessageA();
	if(SciaRegs.SCIFFTX.bit.TXFFST==0) sciaTxFifoService();
}

int Message_send_endA(void)
{	
	if((txa_flag==1)||(txa_start!=txa_end))	return 1;
	else									return 0;
}



