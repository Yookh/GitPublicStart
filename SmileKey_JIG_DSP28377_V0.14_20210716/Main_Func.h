/*
 * Main_Func.h
 *
 *  Created on: 2016. 9. 27.
 *      Author: Yoo Kwang Hyun
 */

#ifndef DUALFREQ_F28377D_CPU1_V1_01_MAIN_FUNC_H_
#define DUALFREQ_F28377D_CPU1_V1_01_MAIN_FUNC_H_

/** external functions **/

extern void	Sys_init28377(void);

/** internal functions **/
// This function is found in the Main.c file.
void	ResetService(void);
void 	RUN(void);
void 	STOP(void);
void 	AdcAvgCalc(void);
void 	FaultService(long FaultInfo);
void	Check_Model(void);
void	EEP_RW(void);

void 	External_HW_Check(Uint32 GP_IN_filt);
void 	External_Operation( Uint32 GP_IN_filt );
void	Auto_save( void );
void	LCD2Upload( void );
void 	DAC_Out( void );
void 	CAN_Divice_Control( void );
int		ChangeSetValue(int wID, char channel);
void	InitECapture( void );

Uint16  CapturePhase( Uint16 SW_Period, Uint16 Dead_T );
void 	ResetService( void );

// This function is found in the Epwm_App.c file.
void ArcTimerStop( void );
void InitArcVar( void );

void AdcRead( void );
void AdcAverage( void );

/** external data **/
// This function is found in the LCD_COMM.c file.
extern int	Message_send_end(void);
extern void RS232_Comm_check(void);
extern void CheckMessageB(void);
extern void MakePktB(byte msg,word wData);
extern void scibTxFifoService(void);
extern void scibRxFifoService(void);
extern void SCIB_INIT_VAL(void);
extern void SCIA_INIT_VAL(void);
extern void SCID_INIT_VAL(void);

extern void INIT_485_VAR_C(void);
extern void SCIC_CHECK(void);
extern void RS485_Comm_check_C(void);

extern void RS232_Comm_checkA(void);
extern void RS232_Comm_checkB(void);
extern void RS232_Comm_checkD(void);

// This function is found in the ModBus_485.c file.
extern void RS485_Comm_check(void);
extern void CheckMessageA(void);
extern void MakePktA(byte msg,word wData);
extern void sciaTxFifoService(void);
extern void sciaRxFifoService(void);
extern void SCIA_CHECK(void);

extern void MakePktB(byte msg,word wData);
extern void MakePktD(byte msg,word wData);

// This function is found in the TimeBaseSystem.c file.
extern int Period_CpuTimer( void );
extern int Period_10ms( void );
extern int Period_50ms( void );
extern int Period_100ms( void );
extern int Period_1000ms( void );
extern int Period_Control( void );

// This function is found in the ControlPI.c file.
extern void InitControlVar( void );

// This function is found in the Epwm_App.c file.
extern void HwFaultInit( float Vo_Arc, float Io_Arc, float Vo_OVP, float Io_OCP, float Ir_OCP, float VOP_OVP, float IOP_OVP );

// This function is found in the DataLogging.c file.
extern void	Timer(void);			   		// tic toc
extern void initializeDlog(void);	   		// you must Call by Reset_Service in Main.C
extern void Dlog_Service(void);		   		//{ DLogger Beha function.
extern void	Data_Recording(int dat1, int dat2, int dat3, int dat4, int dat5);			// feedback data recording
extern void	Dlog_Transmitt(void);			// log data 통신 전송.
extern void Flog_Transmitt(Uint16 addr);


extern void InternalCompRef(Uint16 Comp1Neg);
// This function is found in the dCAN.c file.
extern void InitializeCAN( void );
extern void TransmitCAN_A( uint32_t TXMsgID);
extern void RecieveCAN_A( void );
extern void TransmitCAN_B( uint32_t TXMsgID);
extern void RecieveCAN_B( void );
extern void Ext_return(void);
//extern void MakePkt_CAN( uint32_t addr ,Uint16 idx, Uint16 data);
//extern void CAN_TxData(void);
//extern void CheckMessage_CAN( void );

// This function is found in the Fan_Ctrl.c file.
extern void INIT_FAN_VAR( void );
extern void Fan_Ctrl(int fan_op);
extern int Fan_Op(void);

extern void InitDog( void );
extern Uint32 ReadInputStatus( void );

Uint16 CableLoopDetect(void);


extern void Ethernet_Init( void );
extern void Ethernet_Socket_Ctrl( void );
extern void CommCheckTcpSoket( uint8_t sn );

extern void CommCheckUcpSoket( uint8_t sn );

extern void MakeUdpPacket( Uint16 Code );

extern void DHCP_time_handler(void);
extern int16 DHCP_Ctrl( void );

extern void Txfifo_SPCI( void );
extern void Rxfifo_SCPI( void );
extern void Init_SCPI( void );

extern void InitTargetValue( void );
extern void AutoConnectCheck( void );
extern void ElectricalRequirementTest( void );
extern void AgingTest( void );

//extern void SendUdpPacket( Uint16 type);
#endif /* DUALFREQ_F28377D_CPU1_V1_01_MAIN_FUNC_H_ */
