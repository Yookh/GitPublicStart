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
#include "TargetD_COMM.h"
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
int Message_send_endD(void);

/** private functions **/


//#pragma CODE_SECTION(CheckMessageD, "ramfuncs");
void CheckMessageD(void)
{
//    int       Cmd_num;

//	Cmd_num = SET_NUM;

	/* Received Command processing */
	if (rxd_start != rxd_end)
	{

	    TargetCommParsing(IDD_QUE[rxd_start], RXD_QUE[rxd_start], 'D');
		if(++rxd_start>=MAX_QUE) rxd_start=0;
	}

	/* Transmit Data trigger */
	if (txd_flag==0 && (txd_start!=txd_end))
	{
		ScidRegs.SCITXBUF = TXD_QUE[txd_start];
		txd_flag=1;
	}
}

void RS232_Comm_checkD(void)
{
    SciDAutoBusReset();
	if(ScidRegs.SCIFFRX.bit.RXFFST>0)  scidRxFifoService();
	CheckMessageD();
	if(ScidRegs.SCIFFTX.bit.TXFFST==0) scidTxFifoService();
}

int Message_send_endD(void)
{	
	if((txd_flag==1)||(txd_start!=txd_end))	return 1;
	else									return 0;
}



