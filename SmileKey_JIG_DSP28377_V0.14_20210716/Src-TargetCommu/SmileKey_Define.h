/*
 * SmileKey_Define.h
 *
 *  Created on: 2021. 6. 21.
 *      Author: YooKH
 */

#ifndef SRC_TARGET_MANAGEMENT_SMILEKEY_DEFINE_H_
#define SRC_TARGET_MANAGEMENT_SMILEKEY_DEFINE_H_

#include "../Src-Target_Management/Target_Struct.h"

// 디버깅용 통신 번지.
/*  Communication Parameters    */
#define ID_START            0x02
#define ID_END              0x03
#define ID_STATUS           0x04
#define ID_COM_OK           0x99
#define ID_COM_CUT          0x66
#define ID_FAULT            0x06
#define ID_WARNING          0x07
#define ID_RESET            0x08
#define ID_MSG_RESET        0xD0
#define ID_MSG_FAN_ON       0xD1
#define ID_MSG_SHUT_L       0xD2
#define ID_MSG_SHUT_R       0xD3

#define ID_REQ_CMD          0x09
#define ID_REQ_DATA         0x0A
#define ID_EOD              0x0B    // End of Download
#define ALL                 0xFFFF
#define DEFAULT_ALL         0xFFFE

/*  Commands from Front Panel to DSP    */
#define ID_CMD_RUN          0xf0
#define ID_CMD_STOP         0xff
#define ID_CMD_POWER        0xf2
#define ID_CMD_TEMP         0xf3
#define ID_CMD_TEMP_CTRL    0xf5

/*  Data from DSP to Front Panel    */
#define ID_DATA_PO          0x10
#define ID_DATA_VO          0x11
#define ID_DATA_IO          0x12
#define ID_DATA_IR          0x13
#define ID_DATA_SP1         0x14
#define ID_DATA_SP2         0x15
#define ID_DATA_Ichg        0x16
#define ID_DATA_PH          0x17
#define ID_DATA_TEMP1       0x18
#define ID_DATA_TEMP2       0x19
#define ID_DATA_ID_LSW      0x1a
#define ID_DATA_ID_MSW      0x1b
#define ID_DATA_AGING_CNT   0x1c


/*  Data Request from PC to DSP */
#define ID_REQ_DATA_PO          0x10
#define ID_REQ_DATA_VO          0x11
#define ID_REQ_DATA_IO          0x12
#define ID_REQ_DATA_ILU         0x13
#define ID_REQ_DATA_LIFE_TIME   0x14
#define ID_REQ_DATA_RO          0x15

/*  Reference Command from Front Panel to DSP   */
#define ID_CMD_IR_TIP1          0x80
#define ID_CMD_IR_TIP2          0x81
#define ID_CMD_IR_TIP3          0x82
#define ID_CMD_RUN_TIME         0x83
#define ID_CMD_PO               0x84
#define ID_CMD_VO_GAIN          0x85
#define ID_CMD_MIN_FREQ         0x86

/*  Request from Front Panel to DSP */
#define ID_REQ_PSO              0x20
#define ID_REQ_ISC              0x21
#define ID_REQ_IOM              0x22
#define ID_REQ_LIFE_TIME        0x23
#define ID_REQ_RO_MAX_WARNING   0x24

/*  Feedback from DSP to Front Panel    */
#define ID_FDB_PSO              0x40
#define ID_FDB_ISC              0x41
#define ID_FDB_IOM              0x42
#define ID_FDB_LIFE_TIME        0x43
#define ID_FDB_RO_MAX_WARNING   0x44


// Fault Define
#define FAULT_HW_IR_OCP         BIT0
#define FAULT_IR_OCP            BIT1
#define FAULT_HEATSINK1_OTP     BIT2
#define FAULT_HEATSINK2_OTP     BIT3
#define FAULT_VIN_HIGH          BIT4
#define FAULT_VIN_LOW           BIT5
#define FAULT_PHASE_FAIL        BIT6
#define FAULT_MODE_SELECT       BIT7
#define FAULT_COMM_ERROR        BIT8   // used
#define FAULT_EXT_INTERLOCK     BIT9   // not used
#define FAULT_TIP               BIT10
#define FAULT_Ichg_OCP          BIT11
#define FAULT_IO_OCP            BIT12 //Idc OCP
#define FAULT_485_CUT           BIT13
#define FAULT_NOT3              BIT14
#define FAULT_NOT4              BIT15
//#define FAULT_I_LEAK_FAULT        BIT16

// Warning Define
#define WARNING_LOW_ILLUM       BIT0
#define WARNING_LIFE_TIME       BIT1
#define WARNING_RO_HIGH         BIT2
#define WARNING_EEP_WR_ERR      BIT3
#define WARNING_RS485_CUT       BIT4
#define WARNING_TEMP_IN_HIGH    BIT5
#define WARNING_MAIN_SHUT_DOWN  BIT6


/*-----------------*/
/* position & SET  */
/*-----------------*/

#define SET_SK_IR_TIP1         0
#define SET_SK_IR_TIP2         1
#define SET_SK_IR_TIP3         2
#define SET_SK_RUN_TIME        3
#define SET_SK_PO              4
#define SET_SK_IO              5
#define SET_SK_MIN_FREQ        6
#define SET_SK_PHASE           7
#define SET_SK_IO_GAIN         8
#define SET_SK_IR_GAIN         9
#define SET_SK_Vbat_GAIN       10  //180411 Tdet gain index 추가.
#define SET_SK_IO_OFFSET       11
#define SET_SK_IR_OFFSET       12
#define SET_SK_Tdet_OFFSET     13  //180411 Tdet offset index 추가.
#define SET_SK_VBAT_OFFSET     14
#define SET_SK_PHASE_OFFSET    15
#define SET_SK_ICHG_GAIN       16
#define SET_SK_ICHG_OFFSET     17
#define SET_SK_BUZZER_FREQ     18
#define SET_SK_MODE_SEL        19
#define SET_SK_AGING_COUNT     20
#define SET_SK_STOP_TIME       21

#define MODE_NORMAL             0
#define MODE_TEST               1
#define MODE_AGING              2

extern TargetDB SmileKey[3];

#endif /* SRC_TARGET_MANAGEMENT_SMILEKEY_DEFINE_H_ */
