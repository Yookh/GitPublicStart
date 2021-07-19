///////////////////////////////////////////////////////////////////////////////////////////////
//																							 //
//																							 //
//							DataLogging.c													 //
//																							 //
//	2012.8.11 Coded by Yoo.K.H																 //
//	description : 실시간 이벤트 발생시 데이터를 저장하는 블랙박스 기능 구현.				 //
//  2012.9.18 Update Code -> 실시간 출력 값 저장 및 출력 기능 추가.							 // 
//							 상태 발생 이벤트에 Ready 삭제.									 //
//							 stop , fault , warning 상태에서 만 Data Save					 //		  
///////////////////////////////////////////////////////////////////////////////////////////////
#include "F28x_Project.h"
#include "define.h"
#include "DUAL_PARAM.h"
//*********************************************************************************************
#define MAX_QUE			100

#define Q_SIZE 			200							//원형 Queue의 데이터 크기		   = Time, index, warn, fault, status,block = 600word 250
#define BUFF_SIZE		100							//피드백 데이터의 레코딩 사이즈  20
#define FB_DATA_NUM 	5							// 피드백 데이터의 총 개 수 
#define SAVE_BLOCK_NUM  50							// 5개의 data에 20개의 버퍼 사이즈 = 100word *50block 저장 시 5000word  --> 128 MAX = 8K Word
													// 총 5600word = 11200[byte]
#define BLOCK_SIZE  	((BUFF_SIZE * FB_DATA_NUM) +1) // feedback 데이터를 저장 하는 한 블럭의 크기 

#define DLOG_STATUS 	(EEP_END_ADDR + 1)
#define DLOG_FAULT		(DLOG_STATUS + Q_SIZE)
#define DLOG_WARN		(DLOG_STATUS + (Q_SIZE*2))
#define DLOG_TIME		(DLOG_STATUS + (Q_SIZE*3))
#define DLOG_INDEX		(DLOG_STATUS + (Q_SIZE*4))
#define DLOG_BLOCK		(DLOG_STATUS + (Q_SIZE*5))

#define FLOG_OFFSET 	(DLOG_STATUS + (Q_SIZE*6))			//500
#define FLOG_DATA1		(FLOG_OFFSET+(BLOCK_SIZE*block_num))	
#define FLOG_DATA2		(FLOG_DATA1+1)
#define FLOG_DATA3		(FLOG_DATA1+2)
#define FLOG_DATA4		(FLOG_DATA1+3)
#define FLOG_DATA5		(FLOG_DATA1+4)	

#define FLOG_LOAD1(page)		(FLOG_OFFSET+(BLOCK_SIZE*page))	
#define FLOG_LOAD2(page)		(FLOG_LOAD1(page)+1)
#define FLOG_LOAD3(page)		(FLOG_LOAD1(page)+2)
#define FLOG_LOAD4(page)		(FLOG_LOAD1(page)+3)
#define FLOG_LOAD5(page)		(FLOG_LOAD1(page)+4) 

#define FLOG_LABEL		30000				// this is Last ADDRESS 

#define Dlog_EVENT_Trigger	(old_dlog_status != dlog_status)?	1:0

extern int16 	system_status,warning_status;
extern Uint16 	input_status, cnt_waitsaveend, dlog_index, dlog_tx_index,DATA[10];
extern Uint16   i2cReadData(Uint16 wDevice, Uint16 wAddr);
extern Uint16 	i2cWriteData(Uint16 wDevice, Uint16 wAddr, Uint16 wData);

extern 	Uint16	transmit_end, TRANSMIT_QUE[MAX_QUE], transmit_flag,  transmit_start, dlog_tx_flag, flog_tx_flag;

extern C1_2	C12;
extern C2_1	C21;

int		dlog_status, old_dlog_status;
Uint16	timer_tick, timer_sec, timer_min;
Uint16	flog_update, block_num, feedback_data_count, fdata_load_end;
Uint16	Flog_trigger;

Uint16	KTest[10];
/*
int Q_save_flag,Q_upload_flag;
Uint16 Q_data=Q_OFFSET;
Uint16 F_data=Q_OFFSET+(Q_SIZE*Q_EA);
*/

typedef struct CreateBuffer
{
	int		Dat1[BUFF_SIZE];
	int		Dat2[BUFF_SIZE];
	int		Dat3[BUFF_SIZE];
	int		Dat4[BUFF_SIZE];
	int		Dat5[BUFF_SIZE];
	Uint16		index;					
}Flog;

typedef struct CreateQueue
{
	Uint16 Index;
	Uint16 SaveIndex;
	Uint16 BLOCK[Q_SIZE];
	Uint16 Status[Q_SIZE];
	Uint16 Time[Q_SIZE];
	Uint16 Warning[Q_SIZE]; 
	Uint16 Fault[Q_SIZE];	
//	void (*update)();					// Not used
}Dlog;

void	Dlog_update(void);				// Event 발생하여 buffer 와 Rom 에 저장.
void	Dlog_Load(void);				// EEPROM으로 부터 data load
void 	Flog_Load(Uint16 addr);
void	Dlog_Transmitt(void);			// log data 통신 전송.
void	MATCH_status(void);				// DLogger use Event Trigger check
Uint16	Dlog_Save(void);				// status data save
Uint16  Flog_Save(void);				// feedback data save
void	Timer(void);			   		// tic toc
void 	initializeDlog(void);	   		// you must Call by Reset_Service in Main.C 
void    Dlog_Service(void);		   		//{ DLogger Beha function.
void  	Flog_Transmitt(Uint16 addr);

void	Data_Recording(int dat1, int dat2, int dat3, int dat4, int dat5);			// feedback data recording

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	아래부터 Costomize

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Dlog   logData;								// Queue Create
 Flog	logFeedback, load_buffer;
////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Dlog_Service()
{
	MATCH_status();
//	Dlog_update();
	Dlog_Save();
	Flog_Save();
}

void MATCH_status()						//for main routine
{
	dlog_status = 0;

	if(C12.run_flag) 			dlog_status |= BIT0;	//			run= bit0
	if(warning_status)		dlog_status |= BIT5;
	if(C12.fault_status)		dlog_status |= BIT6;
	
	if(Dlog_EVENT_Trigger)
	{
		Dlog_update();
	}
	
	old_dlog_status = dlog_status;				
} 

void Dlog_update()
{	
	Uint16 feedback_page;

	feedback_page = 0xff;
	if(Flog_trigger == 0)														// 한 번만.
	{
		if((dlog_status&BIT5)||(dlog_status&BIT6))
		{
				flog_update = 1;												// fault 시 혹은 warning 시 
				feedback_data_count = logFeedback.index;					//oldest data
				if(feedback_data_count>=BUFF_SIZE)	feedback_data_count =0;
				Flog_trigger = 1;
				feedback_page = block_num;
		}
	}

	if((Flog_trigger) && ( Dlog_EVENT_Trigger ))		// Reset or wanning clear
	{
		Flog_trigger = 0;
	} 
	if(C12.run_flag)									flog_update = 1;				// Run 했다가 STop 할 때만.

	logData.Status[logData.Index] = dlog_status;	
	logData.Fault[logData.Index]  = (Uint16)(C12.fault_status>>16);
	logData.Warning[logData.Index]= (Uint16)(C12.fault_status&0xffff);
	logData.Time[logData.Index]	  = timer_min;		
	logData.BLOCK[logData.Index]  = feedback_page;	

	logData.Index++;
	if(logData.Index>=Q_SIZE) logData.Index=0;
		
	dlog_index = logData.Index;
	
}

Uint16 Dlog_Save()			//main routine 4번씩 
{
	static int i=0;
	Uint16	log_index,temp;
	Uint16	Sav_index;

	log_index = logData.Index;
	Sav_index = logData.SaveIndex;

	if((Sav_index != log_index)&&(cnt_waitsaveend ==0) && (C12.run_flag == 0) )
	{	
		switch(i)
		{
				case 0: temp=i2cWriteData(0x50, DLOG_STATUS+Sav_index, logData.Status[Sav_index]); 	i++; break;
				case 1: temp=i2cWriteData(0x50, DLOG_FAULT+Sav_index , logData.Fault[Sav_index]);  	i++; break;
				case 2: temp=i2cWriteData(0x50, DLOG_WARN+Sav_index  , logData.Warning[Sav_index]);	i++; break;
				case 3: temp=i2cWriteData(0x50, DLOG_TIME+Sav_index  , logData.Time[Sav_index]);	i++; break;
				case 4: temp=i2cWriteData(0x50, DLOG_INDEX,Sav_index);								i++; break;
				case 5: temp=i2cWriteData(0x50, DLOG_BLOCK+Sav_index , logData.BLOCK[Sav_index]);	
						i=0; 
						if(++logData.SaveIndex >= Q_SIZE) logData.SaveIndex = 0;
						break;
		}
		KTest[0] = DLOG_STATUS+Sav_index;
		cnt_waitsaveend = (SAMPL_FREQ/200);	
	}
	return temp;
}
	
Uint16 Flog_Save()			//main routine 4번씩 
{
	static int i=0, index=0;
	int	temp;

	if(( flog_update )/*&&( C12.run_flag == 0 )*/&&( cnt_waitsaveend ==0 ))
	{	
		switch(i){
			case 0: temp=i2cWriteData(0x50, FLOG_DATA1+index, logFeedback.Dat1[feedback_data_count]); 	i++;	break;
			case 1: temp=i2cWriteData(0x50, FLOG_DATA2+index, logFeedback.Dat2[feedback_data_count]); 	i++;	break;
			case 2: temp=i2cWriteData(0x50, FLOG_DATA3+index, logFeedback.Dat3[feedback_data_count]);	i++;	break;
			case 3: temp=i2cWriteData(0x50, FLOG_DATA4+index, logFeedback.Dat4[feedback_data_count]);	i++;	break;

			case 4: temp=i2cWriteData(0x50, FLOG_DATA5+index, logFeedback.Dat5[feedback_data_count++]);
					
					if(feedback_data_count>=BUFF_SIZE)	feedback_data_count =0;	//circular queue

					if(feedback_data_count == logFeedback.index)  i++;							
					else							   			     i=0;

					index+=FB_DATA_NUM;
					if(index > ( BUFF_SIZE*FB_DATA_NUM ))	index =0;	//circular queue	
														
					break;

			case 5: 						
					feedback_data_count=0; 
					block_num++;
					temp=i2cWriteData(0x50, FLOG_LABEL, block_num);		// last label save = block end	 
					flog_update=0;  
					i=0;  index = 0;
					if(block_num>=SAVE_BLOCK_NUM) block_num =0;

					break;	// index 호출 방식 
		}	
		KTest[3] = i;																						  																								  
		cnt_waitsaveend = (SAMPL_FREQ/200);				//5ms wait												  
	}
	return temp;
} 

void Dlog_Load()									// load reset_service
{
	static int i=0;

	logData.Index=i2cReadData(0x50, DLOG_INDEX);
	if(logData.Index>Q_SIZE)	logData.Index =0;

	KTest[1]=	DLOG_INDEX;
	i=logData.Index;

	for(;;)
	{
		KTest[2] = DLOG_STATUS+i;
		logData.Status[i] 	=  i2cReadData(0x50, DLOG_STATUS+i);
		logData.Fault[i] 	=  i2cReadData(0x50, DLOG_FAULT+i);
		logData.Warning[i]  =  i2cReadData(0x50, DLOG_WARN+i);
		logData.Time[i] 	=  i2cReadData(0x50, DLOG_TIME+i);
		logData.BLOCK[i] 	=  i2cReadData(0x50, DLOG_BLOCK+i);
		block_num = i2cReadData(0x50, FLOG_LABEL);
		i++;

		if(i>=Q_SIZE)	i=0;
		if(i==logData.Index) break;
	}
//	block_num = logData.BLOCK[logData.Index];
	if(block_num>SAVE_BLOCK_NUM) block_num =0;

	timer_min = logData.Time[logData.Index];

	logData.Index++;
	if(logData.Index>=Q_SIZE) logData.Index=0;

	dlog_index = logData.Index;

}

void Flog_Load(Uint16 addr)									// 
{
	int i;
	i=0;

	for(;;)
	{
		load_buffer.Dat1[i]		=  i2cReadData(0x50, FLOG_LOAD1(addr)+ (i*FB_DATA_NUM));
		load_buffer.Dat2[i]		=  i2cReadData(0x50, FLOG_LOAD2(addr)+ (i*FB_DATA_NUM));
		load_buffer.Dat3[i]  	=  i2cReadData(0x50, FLOG_LOAD3(addr)+ (i*FB_DATA_NUM));
		load_buffer.Dat4[i]		=  i2cReadData(0x50, FLOG_LOAD4(addr)+ (i*FB_DATA_NUM));
		load_buffer.Dat5[i]		=  i2cReadData(0x50, FLOG_LOAD5(addr)+ (i*FB_DATA_NUM));
		i++;

		if(i>=BUFF_SIZE)	break;
	} 
	fdata_load_end =1;
}

void  Flog_Transmitt(Uint16 addr)
{
	static int flog_tx_index=0;

	if(fdata_load_end==0) Flog_Load(addr);

	TRANSMIT_QUE[transmit_end]=ID_START+0xf0;									if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=flog_tx_index;								if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat1[flog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat1[flog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat2[flog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat2[flog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat3[flog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat3[flog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat4[flog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat4[flog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat5[flog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(load_buffer.Dat5[flog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=addr;										if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=0x00;									if(++transmit_end>=MAX_QUE) transmit_end=0; // dummy
	TRANSMIT_QUE[transmit_end]=0x00;									if(++transmit_end>=MAX_QUE) transmit_end=0; // dummy
	TRANSMIT_QUE[transmit_end]=ID_END+0xf0;									if(++transmit_end>=MAX_QUE) transmit_end=0;
//	TRANSMIT_QUE[transmit_end]=0x0d;									if(++transmit_end>=MAX_QUE) transmit_end=0;

	flog_tx_index++;
	if(flog_tx_index>=BUFF_SIZE){ flog_tx_index =0; fdata_load_end =0; flog_tx_flag =0;}
}

void  Dlog_Transmitt()
{

	if(dlog_tx_index>Q_SIZE) dlog_tx_index=0;
		
	TRANSMIT_QUE[transmit_end]=ID_START;								if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=dlog_tx_index;							if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Time[dlog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Time[dlog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Status[dlog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Status[dlog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Fault[dlog_tx_index]>>8)&0xff;	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Fault[dlog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Warning[dlog_tx_index]>>8)&0xff;if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.Warning[dlog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=(logData.BLOCK[dlog_tx_index] & 0xff);	if(++transmit_end>=MAX_QUE) transmit_end=0;
	TRANSMIT_QUE[transmit_end]=0x00;									if(++transmit_end>=MAX_QUE) transmit_end=0; // dummy
	TRANSMIT_QUE[transmit_end]=0x00;									if(++transmit_end>=MAX_QUE) transmit_end=0; // dummy
	TRANSMIT_QUE[transmit_end]=0x00;									if(++transmit_end>=MAX_QUE) transmit_end=0; // dummy
	TRANSMIT_QUE[transmit_end]=0x00;									if(++transmit_end>=MAX_QUE) transmit_end=0; // dummy
	TRANSMIT_QUE[transmit_end]=ID_END;									if(++transmit_end>=MAX_QUE) transmit_end=0;
//	TRANSMIT_QUE[transmit_end]=0x0d;									if(++transmit_end>=MAX_QUE) transmit_end=0;

	dlog_tx_index++;
	if(dlog_tx_index>=Q_SIZE) dlog_tx_index=0;

	if(dlog_tx_index==logData.Index) dlog_tx_flag=0; 
}

void Data_Recording(int dat1, int dat2, int dat3, int dat4, int dat5)
{
	if((C12.run_flag)/*&&(flog_update == 0)*/)
	{
		logFeedback.Dat1[logFeedback.index] = dat1;
		logFeedback.Dat2[logFeedback.index] = dat2;
		logFeedback.Dat3[logFeedback.index] = dat3; 
		logFeedback.Dat4[logFeedback.index] = dat4;
		logFeedback.Dat5[logFeedback.index] = dat5;

		logFeedback.index++;
		if(logFeedback.index>=BUFF_SIZE)	logFeedback.index=0;
	}
} 

void Timer()
{
	timer_tick++;
	if(timer_tick>SAMPL_FREQ){ timer_sec++; timer_tick=0;}
	if(timer_sec>59)		 { timer_min++; timer_sec=0;}

}

void initializeDlog()
{
	int i;
	
	for(i=0; i<Q_SIZE; i++)
	{
		logData.Status[i]=0;	logData.Fault[i]=0; logData.Warning[i]=0;	logData.Time[i]=0; logData.BLOCK[i] =0;
	}
	logData.Index=0; 

	for(i=0; i< sizeof(logFeedback.Dat1); i++)
	{
		logFeedback.Dat1[i]=0;	logFeedback.Dat2[i]=0; logFeedback.Dat3[i]=0; logFeedback.Dat4[i]=0; logFeedback.Dat5[i]=0;
	}
	logFeedback.index = 0;

	timer_tick =0; timer_sec=0; timer_min=0;
	dlog_status =0; old_dlog_status=0;
	flog_update=0;
	block_num =0; feedback_data_count=0; fdata_load_end=0;
	Dlog_Load();

	logData.SaveIndex = logData.Index;
	dlog_tx_index=logData.Index+1;
	Flog_trigger=0;
} 
/*************************************************************************************************************************************/
//	Costomize end
/*************************************************************************************************************************************/


