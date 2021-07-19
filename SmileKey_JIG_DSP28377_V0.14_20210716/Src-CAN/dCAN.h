/*
 * dCAN.h
 *
 *  Created on: 2017. 4. 18.
 *      Author: YooKH
 */

#ifndef RFGEN3KW_F28377D_CPU1_V0_16_SRC_CAN_DCAN_H_
#define RFGEN3KW_F28377D_CPU1_V0_16_SRC_CAN_DCAN_H_

#define CAN_TX_SIZE			1		// used Tx count of channel
#define CAN_RX_SIZE			20		// used Rx count of channel

#define CAN_TX_MSG_OBJ		1		// CAN 송신용 오브젝트(=메일박스) 번호 선택
#define CAN_RX_MSG_OBJ		15		// CAN 수신용 오브젝트(=메일박스) 번호 선택
//=========================RX list==================================


//========================TX list====================================



//=========================RX list==================================


//========================TX list====================================

//=====================================================================
struct  CAN_D0_WORD    {
        Uint16  WORD0:16;
};

struct  CAN_BYTE
{
        unsigned char Data;
};

struct CAN_BIT
{
	Uint16 	Bit0:1;
	Uint16  Bit1:1;
	Uint16  Bit2:1;
	Uint16  Bit3:1;
	Uint16  Bit4:1;
	Uint16  Bit5:1;
	Uint16  Bit6:1;
	Uint16  Bit7:1;
};
union CAN_DATA
{
        Uint8                       all;
        struct  CAN_BYTE            Byte;
        struct  CAN_BIT             Bit;
};

typedef struct {

  union CAN_DATA     		Data0[2];
  union CAN_DATA	  		Data1[2];
  union CAN_DATA			Data2[2];
  union CAN_DATA			Data3[2];

} CAN_Data;


#endif /* RFGEN3KW_F28377D_CPU1_V0_16_SRC_CAN_DCAN_H_ */
