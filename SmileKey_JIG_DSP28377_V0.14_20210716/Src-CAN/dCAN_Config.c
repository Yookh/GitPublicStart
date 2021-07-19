/*
 * dCAN.c
 *
 *  Created on: 2017. 3. 29.
 *      Author: LimHS
 */


#include "F28x_Project.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "inc/hw_memmap.h"
#include "DCAN.h"

extern void CAN_enableTestMode(uint32_t base, uint16_t mode);

extern tCANMsgObject sTXCANMessageA, sTXCANMessageB;
extern tCANMsgObject sRXCANMessageA[CAN_RX_SIZE], sRXCANMessageB[CAN_RX_SIZE];

CAN_Data CAN_RXDA[CAN_RX_SIZE], CAN_RXDB[CAN_RX_SIZE];
CAN_Data CAN_TXDA,CAN_TXDB ;
unsigned char txbuff[8];

void InitializeCAN( void );
void Config_CAN( void );
void Config_CAN_A( void );
void Config_CAN_B( void );

void InitializeCAN( void )
{
	// CAN controllers 초기화
	CANInit(CANA_BASE);
	CANInit(CANB_BASE);

	// CAN 모듈에 공급되는 클럭 선택
	CANClkSourceSelect(CANA_BASE, 0);
	CANClkSourceSelect(CANB_BASE, 0);

	// CAN Bit Rate 설정
	CANBitRateSet(CANA_BASE, 200000000,1000000);			// 1Mbps
	CANBitRateSet(CANB_BASE, 200000000,1000000);			// 1Mbps

    // CAN 모듈의 인터럽트 활성화.
//    CANIntEnable(CANA_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
//    CANIntEnable(CANB_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

	// CAN-A 모듈의 인터럽트 신호 활성화.
//	CANGlobalIntEnable(CANA_BASE, CAN_GLB_INT_CANINT0);
//	CANGlobalIntEnable(CANB_BASE, CAN_GLB_INT_CANINT0);

	// CAN 메세지 오브젝트 초기화.
	Config_CAN();

	CAN_enableTestMode(CANA_BASE, CAN_TEST_LBACK | CAN_TEST_SILENT);
	CAN_enableTestMode(CANB_BASE, CAN_TEST_LBACK | CAN_TEST_SILENT);

	// CAN 모듈 동작 활성화
	CANEnable(CANA_BASE);
	CANEnable(CANB_BASE);

}

void Config_CAN( void )
{
	Config_CAN_A();
	Config_CAN_B();
}

void Config_CAN_A( void )
{
	Uint8 i=0;

	for(i=0; i < CAN_RX_SIZE; i++)
	{
		sRXCANMessageA[i].ui32MsgID = 0x200 + i;
		sRXCANMessageA[i].ui32MsgLen = 8;
		sRXCANMessageA[i].ui32MsgIDMask = 0;                 // no mask needed for RX
		sRXCANMessageA[i].ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_FIFO; //
		sRXCANMessageA[i].pucMsgData = (unsigned char *)&CAN_RXDA[i].Data0[0];         // ptr to message content
		CANMessageSet(CANA_BASE, i+1, &sRXCANMessageA[i], MSG_OBJ_TYPE_RX);
	}

//	sRXCANMessageA[0].ui32MsgID = 0x201;
//	sRXCANMessageA[0].ui32MsgLen = 4;
//	sRXCANMessageA[0].ui32MsgIDMask = 0;                 // no mask needed for RX
//	sRXCANMessageA[0].ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_FIFO; //
//	sRXCANMessageA[0].pucMsgData = (unsigned char *)&CAN_RXDA[0].Data0[0];         // ptr to message content
//	CANMessageSet(CANA_BASE, CAN_RX_MSG_OBJ, &sRXCANMessageA[0], MSG_OBJ_TYPE_RX);


	//----------------------Tx Config-------------------------------
	sTXCANMessageA.ui32MsgIDMask = 0;                   // no mask needed for TX
	sTXCANMessageA.ui32Flags = MSG_OBJ_TX_INT_ENABLE;   // enable interrupt on TX
	sTXCANMessageA.pucMsgData = 0;
}

void Config_CAN_B( void )
{
	Uint8 i;

	for(i=0; i < CAN_RX_SIZE; i++)
	{
		sRXCANMessageB[i].ui32MsgID = 0x300 + i;
		sRXCANMessageB[i].ui32MsgLen = 8;
		sRXCANMessageB[i].ui32MsgIDMask = 0;                 // no mask needed for RX
		sRXCANMessageB[i].ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_FIFO; //
		sRXCANMessageB[i].pucMsgData = (unsigned char *)&CAN_RXDB[i].Data0[0];         // ptr to message content
		CANMessageSet(CANB_BASE, i+1, &sRXCANMessageB[i], MSG_OBJ_TYPE_RX);
	}

	//----------------------Tx Config-------------------------------
	sTXCANMessageB.ui32MsgIDMask = 0;                   // no mask needed for TX
	sTXCANMessageB.ui32Flags = MSG_OBJ_TX_INT_ENABLE;   // enable interrupt on TX
	sTXCANMessageB.pucMsgData = (unsigned char *)&CAN_TXDB.Data0[0];
}
