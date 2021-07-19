
/*
 * dCAN.c
 *
 *  Created on: 2017. 3. 3.
 *      Author: YooKH
 */


#include "F28x_Project.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "inc/hw_memmap.h"
#include "..\define.h"
#include "..\DUAL_PARAM.h"
#include "DCAN.h"
#include "string.h"

extern CAN_Data CAN_TXDA, CAN_RXDA[CAN_RX_SIZE];
extern CAN_Data CAN_TXDB, CAN_RXDB[CAN_RX_SIZE];

extern C1_2	C12;
extern C2_1	C21;

extern const int SET[M_NUM][SET_NUM][3];

extern Uint16 ADC_Avg[ADC_NUMBER], DISP_Avg[ADC_NUMBER];
extern Uint16 warning_status, system_status;
extern Uint16    model;
//====================================================================
tCANMsgObject sTXCANMessageA, sTXCANMessageB;
tCANMsgObject sRXCANMessageA[CAN_RX_SIZE], sRXCANMessageB[CAN_RX_SIZE];
Uint8 ucRXMsgData[CAN_RX_SIZE][8], ucTXMsgData[8];
Uint8 _TxSize, _RxSize;
uint32_t MsgAddr;
extern CAN_Data CAN_RXDA[CAN_RX_SIZE];
extern unsigned char txbuff[8];

//=================================test==============================
Uint16 OpCanCmd, NewCMD;
Uint16 CANCommCnt, CanLive;
//====================================================================

extern void MakePktA(byte msg,word wData);

void Init_CAN_VAR( void );

void TransmitCAN_A( uint32_t TXMsgID);
void TransmitCAN_B( uint32_t TXMsgID);
void RecieveCAN_A( void );
void RecieveCAN_B( void );

void Word2ArrayCAN (unsigned char array[2], Uint16 Data);
unsigned char Array2WordCAN(unsigned char array[2]);
int SetValueLimiter(Uint16 wID, Uint16 data);
void CAN_COMM_RECOVERY(void);

Uint16 testview[2][4];

void Init_CAN_VAR( void )
{
	OpCanCmd = 0;
	NewCMD = 0;
	CanLive = 0;
	CANCommCnt =0;
}
void TransmitCAN_A( uint32_t TXMsgID)
{
	Uint16 	DataLength;

	txbuff[0] = 0x12;
	txbuff[1] = 0x34;
	txbuff[2] = 0x56;
	txbuff[3] = 0x78;
	txbuff[4] = 0x9a;
	txbuff[5] = 0xbc;
	txbuff[6] = 0xde;
	txbuff[7] = TXMsgID-0x200;

	DataLength = 8;
	sTXCANMessageA.pucMsgData = txbuff;
	sTXCANMessageA.ui32MsgID = TXMsgID;
	sTXCANMessageA.ui32MsgLen = DataLength;
	CANMessageSet(CANA_BASE, 30, &sTXCANMessageA, MSG_OBJ_TYPE_TX);	//0x200
}
// 0x200 ~ 228
//|ID | Io | Vo | Status |
void RecieveCAN_A( void )
{
	int i;
	for(i = 0; i<CAN_RX_SIZE; i++)
	{
		CANMessageGet(CANA_BASE, i+1, &sRXCANMessageA[i], MSG_OBJ_TYPE_RX);
		if(sRXCANMessageA[i].ui32Flags & MSG_OBJ_NEW_DATA)
		{
/*			if(( sRXCANMessageA[i].ui32MsgID >= 0x200) && (sRXCANMessageA[i].ui32MsgID < (0x200+CAN_RX_SIZE)))
			{
				ModuleInfo[i].Io_FeedBack = Array2WordCAN((Uint8 *)CAN_RXDA[i].Data0);
				ModuleInfo[i].Vo_FeedBack = Array2WordCAN((Uint8 *)CAN_RXDA[i].Data1);
				ModuleInfo[i].Status 	  = Array2WordCAN((Uint8 *)CAN_RXDA[i].Data2);
				ModuleInfo[i].FaultInfo   = Array2WordCAN((Uint8 *)CAN_RXDA[i].Data3);
			}*/
		}
	}
}
//@brief Transmitt Can A Channel.
//! \param TXMsgID - contains the message ID, either 11 or 29 bits.
void TransmitCAN_B( uint32_t TXMsgID)
{
	Uint16 	DataLength;

	txbuff[0] = 0x12;
	txbuff[1] = 0x34;
	txbuff[2] = 0x56;
	txbuff[3] = 0x78;
	txbuff[4] = 0x9a;
	txbuff[5] = 0xbc;
	txbuff[6] = 0xde;
	txbuff[7] = TXMsgID-0x200;

	DataLength = 8;
	sTXCANMessageB.pucMsgData = txbuff;
	sTXCANMessageB.ui32MsgID = TXMsgID;
	sTXCANMessageB.ui32MsgLen = DataLength;
	CANMessageSet(CANB_BASE, 30, &sTXCANMessageB, MSG_OBJ_TYPE_TX);	//0x200

	/*
		switch(TXMsgID)
		{
		case 0x98 :
					Word2ArrayCAN((unsigned char *)CAN_TXD.Data0, EmifData.Vf);
					Word2ArrayCAN((unsigned char *)CAN_TXD.Data1, EmifData.Vr);
					Word2ArrayCAN((unsigned char *)CAN_TXD.Data2, EmifData.DIor);
					Word2ArrayCAN((unsigned char *)CAN_TXD.Data3, EmifData.DVor);
					DataLength = 8;
				break;

			DataLength = 4;
			break;
		}*/

}

//@brief Recieve Can A Channel.
//!  Call as Posive as fast fuction.
void RecieveCAN_B( void )
{
	int i;
	for(i = 0; i<CAN_RX_SIZE; i++)
	{
		CANMessageGet(CANB_BASE, i+1, &sRXCANMessageB[i], MSG_OBJ_TYPE_RX);
		if(sRXCANMessageB[i].ui32Flags & MSG_OBJ_NEW_DATA)
		{
/*			if(( sRXCANMessageB[i].ui32MsgID >= 0x300) && (sRXCANMessageB[i].ui32MsgID < (0x300+CAN_RX_SIZE)))
			{
				ModuleInfo[i+20].Io_FeedBack = Array2WordCAN((Uint8 *)CAN_RXDB[i].Data0);
				ModuleInfo[i+20].Vo_FeedBack = Array2WordCAN((Uint8 *)CAN_RXDB[i].Data1);
				ModuleInfo[i+20].Status 	 = Array2WordCAN((Uint8 *)CAN_RXDB[i].Data2);
				ModuleInfo[i+20].FaultInfo   = Array2WordCAN((Uint8 *)CAN_RXDB[i].Data3);
			}*/
		}
	}
}

// �����̰� § ���� �Լ�. ����ȵ�.
void Word2ArrayCAN (unsigned char array[2], Uint16 Data)
{
	array[0] = Data >>8;
	array[1] = Data & 0xffff;
}

unsigned char Array2WordCAN(unsigned char array[2])
{
	int tmp;
	tmp = ((Uint16)array[0]<<8)|array[1];
	return tmp;
}

int SetValueLimiter(Uint16 wID, Uint16 data)
{
    int Value;

    if(data>SET[model][wID][MAX])           Value=SET[model][wID][MAX];
    else if(data<SET[model][wID][MINIMUM])  Value=SET[model][wID][MINIMUM];
    else                                    Value=data;

    return(Value);
}

void CAN_COMM_RECOVERY(void)
{
    //-- can auto recovery -----------------------------------------------------------//
    if(DcanbRegs.CAN_ES.bit.BOff)
    {

    }
    //--------------------------------------------------------------------------------//
}

Uint16 errorFlag;
Uint16 Testval;
Uint16 rxCnt;
Uint16 CAN_Statview;
Uint16 CAN_errview;

__interrupt void dCANA_isr(void)
{
    uint32_t status;

    // ���ͷ�Ʈ �߻� ���� Ȯ��
    status = CANIntStatus(CANA_BASE, CAN_INT_STS_CAUSE);
    CAN_Statview = status;
    // ���ͷ�Ʈ �߻� ������ CAN Controller Status�� ���� ���̶��,
    // �ش� Status�� �о��
    if(status == CAN_INT_INT0ID_STATUS)
    {
    	// CAN controller status �� �о� �پ��� ���� ��Ȳ�� ������ �� ������,
    	// ������ �ܼ�ȭ�ϱ� �� ���������� ����ó�� ������ �������� ����.
        // ���� ���� ���� ���� �ڼ��� ������ CAN���� API ������ ������ ��.
    	// �׸��� status ���� �о� ���̴� ������ �ش� ���ͷ�Ʈ�� Ŭ���� ��.
        status = CANStatusGet(CANA_BASE, CAN_STS_CONTROL);

        // ���� �߻� ���� Ȯ��
        if(((status  & ~(CAN_ES_RXOK)) != 7) && ((status  & ~(CAN_ES_RXOK)) != 0))
        {
        	errorFlag = 777;
            // ������ �߻��ߴٸ�, errorFlag ���� Set ��.
            if(DcanbRegs.CAN_ES.bit.BOff)
            {
            	CAN_errview = status;

                errorFlag = 888;
            }

        }
    }

    // ���ͷ�Ʈ �߻� ������ CAN-B receive message object �� ���� ������ Ȯ��
    else if(status == CAN_RX_MSG_OBJ)
    {
        // ���ſ� ������Ʈ ���ۿ� ����� �޼����� �о��
//        CANMessageGet(CANA_BASE, CAN_RX_MSG_OBJ, &sRXCANMessageA[0], true);
        RecieveCAN_A();

        // �޼��� ������Ʈ ���ͷ�Ʈ�� Ŭ����
        CANIntClear(CANA_BASE, CAN_RX_MSG_OBJ);
        // �޼����� ���ŵ� ����, ���� �÷��׸� ����
        errorFlag = 0;
    }

    // �������� ���� ��� ���ͷ�Ʈ��� ���⼭ ó��
    else
    {
        // Spurious interrupt handling can go here.
    }
    rxCnt++;

    // CAN-B ���� ���ͷ�Ʈ �÷��� Ŭ����
    CANGlobalIntClear(CANA_BASE, CAN_GLB_INT_CANINT0);

    // PIE group 9 ACK ��Ʈ Ŭ����
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

__interrupt void dCANB_isr(void)
{
    CANGlobalIntClear(CANB_BASE, CAN_GLB_INT_CANINT0);

    // PIE group 9 ACK ��Ʈ Ŭ����
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

