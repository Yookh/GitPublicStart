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
#include "TargetB_COMM.h"
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
int Message_send_end(void);

/** private functions **/


//#pragma CODE_SECTION(CheckMessageB, "ramfuncs");
void CheckMessageB(void)
{
//	Uint16 i, wTmp;
//	int		  Cmd_num;
//	Uint16	ptmp;

//	Cmd_num = SET_NUM;

	/* Received Command processing */
	if (rxb_start != rxb_end)
	{
	    TargetCommParsing(IDB_QUE[rxb_start], RXB_QUE[rxb_start], 'B');
		if(++rxb_start>=MAX_QUE) rxb_start=0;
	}

	/* Transmit Data trigger */
	if (txb_flag==0 && (txb_start!=txb_end))
	{
		ScibRegs.SCITXBUF = TXB_QUE[txb_start];
		txb_flag=1;
	}
}

void RS232_Comm_checkB(void)
{
    SciBAutoBusReset();
	if(ScibRegs.SCIFFRX.bit.RXFFST>0)  scibRxFifoService();
	CheckMessageB();
	if(ScibRegs.SCIFFTX.bit.TXFFST==0) scibTxFifoService();	
}

int Message_send_end(void)
{	
	if((txb_flag==1)||(txb_start!=txb_end))	return 1;
	else									return 0;
}



