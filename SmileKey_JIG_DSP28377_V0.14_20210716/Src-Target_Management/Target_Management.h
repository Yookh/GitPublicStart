/*
 * Target_Management.h
 *
 *  Created on: 2021. 6. 23.
 *      Author: YooKH
 */

#ifndef SRC_TARGET_MANAGEMENT_TARGET_MANAGEMENT_H_
#define SRC_TARGET_MANAGEMENT_TARGET_MANAGEMENT_H_
#include "F28x_Project.h"

extern void MakePktA(char msg,int16 wData);
extern void MakePktB(char msg,int16 wData);
extern void MakePktD(char msg,int16 wData);

extern Uint16        wMb_control_data_C;
extern int           flag_RS485_data_new_C;

enum AutoCal_State{ InitState = 0,
                    FactoryDefault,
                    CheckControlVolt,
                    OffsetCalibration,
                    VbatCalibration,
                    IRCalibration,
                    IDCCalibration,
                    IChageCalibration,
                    Final_Run_cmd,
                    OutputCheck,
                    AutoCal_Error,
                    AutoCal_End
                  }AutoCal_Step;


enum AutoAging_State{
    InitStateAging = 0,
    AgingSetting,
    RunCmdTransmitt,
    Aging,
    NormalSetting,
    BatteryCharging,
    ChargingSpecCheck,
    AgingEnd,
    Charging_Err,
    AutoAging_Err
}AutoAging_Step;

#define  CTRL_V_TOLERANCE       0.10f            //10% 오차 허용.
#define  OUTPUT_TOLERANCE       0.10f
#define  VBAT_TOLERANCE         0.01f

#define PASS_OUTPUT_PO          17              // 17[W]
#define PASS_OUTPUT_IR          800             // 8.00[A]
#define PASS_VBAT               410             // 4.10[V]
#define CHARGING_TIME           3.9               // 4 [hour]
#define IDC_REF                 500             // 5.00[A]

#define IO_OFFSET_COEF          4.0f
#define IR_OFFSET_COEF          4.0f
#define I_CHARGE_OFFSET_COEF    0.5f
#define Vbat_GAIN_COEF          5.0f
#define IR_GAIN_COEF            10.0f
#define IDC_GAIN_COEF           10.0f
#define I_CHARGE_GAIN_COEF      5.0f

#define MODULE_MAX              3               // 3 module
#define SMILEKEY_TIMEOUT        80              // 8.0 sec
#define POLLING_TIME            30              // 3.0 sec  Connect Request poll time when after Listen.



#endif /* SRC_TARGET_MANAGEMENT_TARGET_MANAGEMENT_H_ */
