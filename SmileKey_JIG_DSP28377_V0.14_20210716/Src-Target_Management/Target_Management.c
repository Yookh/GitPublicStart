/*
 * Target_Mamagement.c
 *
 *  Created on: 2021. 6. 21.
 *      Author: YooKH
 */

#include "Target_Struct.h"
#include "Target_Management.h"
#include "../define.h"
#include "string.h"
#include "../Src-TargetCommu/SmileKey_Define.h"

#include <stdio.h>

// LCD 설정파라미터 테이블.
//                                                IRT1  IRT2  IRT3   Time    PO   IO   MFQ  PHASE   IOG   IRG  VOG, IOOF, IROF, VOOF  VbatOF  phof, ICHG, ICHGOF, B_FREQ  MODE AGING_cnt  S_TIME
//                                                   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,     15,   16,   17,   18 ,     19     20         21
const int SMK_SET[1][3][SMILEKEY_SET_NUMBER]=  {  1600, 1600, 1600,  100,  300, 2000,  900, 1800,  999,  999,  999,  999,  999,  999,  999,    999,  999,  999,  3500,     2,   999,        3600,  // MAX
                                                     0,    0,    0,    0,    0,  100,    0,    0, -999, -999, -999, -999, -999, -999, -999,   -999, -999, -999,   440,     0,     0,         00,  // MIN
                                                  1600, 1000,  800,   80,  300, 1000,  120,  180,    0,    0,    0,    0,    0,    0,    0,   -962,    0,    0,  3500,     0,     0,         40   // DEFAULT
                                               };

void TargetCommParsing( char ID, int Data, char Ch );
void AutoConnectCheck( void );
void InitTargetValue( void );
Uint16 GetJigStatus( void );
Uint16 GetJigFault( void );

void ElectricalRequirementTest( void );
void AgingTest( void );

extern int16   ADC_Avg[ADC_NUMBER];
TargetDB SmileKey[3];
int tolerance_5V_min, tolerance_5V_max;
int tolerance_6V_min, tolerance_6V_max;
int tolerance_3_3V_min, tolerance_3_3V_max;
int tolerance_1_8V_min, tolerance_1_8V_max;
int tolerance_Ir_min, tolerance_Ir_max;
int tolerance_Po_min, tolerance_Po_max;
int tolerance_Vbat_min, tolerance_Vbat_max;
Uint16 JigStatusInfo, JigFaultInfo;
Uint16 Term;
Uint16 reTryCnt;

Uint16 DebugTryCnt;

int Step_Cali;
int Step_Aging;

void InitTargetValue( void )
{
    memset(&SmileKey, 0, sizeof(SmileKey));

    tolerance_5V_min = 5000 * (1.0 - CTRL_V_TOLERANCE); tolerance_5V_max = 5000 * (1.0 + CTRL_V_TOLERANCE);
    tolerance_6V_min = 6000 * (1.0 - CTRL_V_TOLERANCE); tolerance_6V_max = 6000 * (1.0 + CTRL_V_TOLERANCE);
    tolerance_3_3V_min = 3300 * (1.0 - CTRL_V_TOLERANCE); tolerance_3_3V_max = 3300 * (1.0 + CTRL_V_TOLERANCE);
    tolerance_1_8V_min = 1800 * (1.0 - CTRL_V_TOLERANCE); tolerance_1_8V_max = 1800 * (1.0 + CTRL_V_TOLERANCE);

    tolerance_Vbat_min = PASS_VBAT * (1.0 - VBAT_TOLERANCE); tolerance_Vbat_max = PASS_VBAT * (1.0 + VBAT_TOLERANCE);

    tolerance_Ir_min = PASS_OUTPUT_IR * (1.0 - OUTPUT_TOLERANCE); tolerance_Ir_max = PASS_OUTPUT_IR * (1.0 + OUTPUT_TOLERANCE);
    tolerance_Po_min = PASS_OUTPUT_PO * (1.0 - OUTPUT_TOLERANCE); tolerance_Po_max = PASS_OUTPUT_PO * (1.0 + OUTPUT_TOLERANCE);

    JigStatusInfo = 0;  JigFaultInfo = 0;
    Term = 0;
    DebugTryCnt =0;
    reTryCnt = 0;

    AutoCal_Step = InitState;
    AutoAging_Step = InitStateAging;

    Step_Cali = AutoCal_Step;
    Step_Aging = AutoAging_Step;

    ONOFF_RELAY1(OFF);
    ONOFF_RELAY2(OFF);
    ONOFF_RELAY3(OFF);

}

Uint16 GetJigStatus( void )
{
    int i;

    JigStatusInfo = 0;

    if(SmileKey[0].Connected == 1) JigStatusInfo |= BIT0;
    if(SmileKey[1].Connected == 1) JigStatusInfo |= BIT1;
    if(SmileKey[2].Connected == 1) JigStatusInfo |= BIT2;

    if(SmileKey[0].AutoCal_ing == 1) JigStatusInfo |= BIT3;
    if(SmileKey[0].AutoCal_end == 1) JigStatusInfo |= BIT4;

    for(i=0; i < MODULE_MAX; i++)
        if( SmileKey[i].Error != 0 ) JigStatusInfo |= BIT6;

    if(SmileKey[0].AutoAging == 1)   JigStatusInfo |= BIT7;
    if(SmileKey[1].AutoAging == 1)   JigStatusInfo |= BIT8;
    if(SmileKey[2].AutoAging == 1)   JigStatusInfo |= BIT9;

    if(SmileKey[0].Charging == 1)   JigStatusInfo |= BIT10;
    if(SmileKey[1].Charging == 1)   JigStatusInfo |= BIT11;
    if(SmileKey[2].Charging == 1)   JigStatusInfo |= BIT12;

    if(SmileKey[0].Charging_End == 1)   JigStatusInfo |= BIT13;
    if(SmileKey[1].Charging_End == 1)   JigStatusInfo |= BIT14;
    if(SmileKey[2].Charging_End == 1)   JigStatusInfo |= BIT15;


    return JigStatusInfo;
}

Uint16 GetJigFault( void )
{
    JigFaultInfo = 0;

    if(SmileKey[0].fault == 1) JigFaultInfo |= BIT0;
    if(SmileKey[1].fault == 1) JigFaultInfo |= BIT1;
    if(SmileKey[2].fault == 1) JigFaultInfo |= BIT2;

    return JigFaultInfo;
}

//100ms Call
void AutoConnectCheck(void)
{
    int i;
    for(i=0; i < MODULE_MAX; i++)
    {
        if((SmileKey[i].Connected == 1) || (SmileKey[i].Listen == 1)) SmileKey[i].CommTic++;                   // Connected. time Out Check.

        // Disconnected Check.
        if(SmileKey[i].CommTic > SMILEKEY_TIMEOUT)
        {
            SmileKey[i].Connected = 0;  SmileKey[i].CommTic = 0; SmileKey[i].Listen = 0; Term = 0;
            AutoCal_Step = InitState;
            AutoAging_Step = InitStateAging;
        }

        if((SmileKey[i].Connected == 0) && (SmileKey[i].Listen == 1))                                        // Data Listen => Connect try.
        {
           if(( AutoCal_Step == InitState ) && (AutoAging_Step == InitStateAging))
           {
               if((Term % 30) == 0 )
               {
                   if(i== 0){ MakePktA(ID_REQ_CMD, ALL);
                       printf("EOD Request Count = %d \n" , DebugTryCnt++);
                       fflush (stdout);
                   }                               // Request Connect.
                   if(i== 1) MakePktB(ID_REQ_CMD, ALL);                                // Request Connect.
                   if(i== 2) MakePktD(ID_REQ_CMD, ALL);                                // Request Connect.
               }
               Term++;
           }
        }
    }
}

#pragma CODE_SECTION(TargetCommParsing, "ramfuncs");
void TargetCommParsing( char ID, int Data, char Ch )
{
    TargetDB* pTargeter;

    if(Ch == 'A') pTargeter = &SmileKey[0];
    if(Ch == 'B') pTargeter = &SmileKey[1];
    if(Ch == 'D') pTargeter = &SmileKey[2];

    if((ID >= 0x80) && (ID < ( 0x80 + SMILEKEY_SET_NUMBER ))) pTargeter->SetValue[ID-0x80] = Data;
    else
    {
        switch(ID)
        {
        case ID_DATA_PO:        pTargeter->Po = Data;                   break;
        case ID_DATA_VO:        pTargeter->Vo = Data;                   break;
        case ID_DATA_IO:        pTargeter->Idc = Data;                  break;
        case ID_DATA_IR:        pTargeter->Ir = Data;                   break;
        case ID_DATA_SP1:       pTargeter->Version = Data;              break;
        case ID_DATA_SP2:       pTargeter->Vbat = Data;                 break;
        case ID_DATA_Ichg:      pTargeter->I_Charge = Data;             break;
        case ID_DATA_PH:        pTargeter->Phase = Data;                break;
        case ID_DATA_TEMP1:     pTargeter->Temperature1 = Data;         break;
        case ID_DATA_TEMP2:     pTargeter->Temperature2 = Data;         break;
        case ID_DATA_ID_LSW :   pTargeter->UniqueID.Word.LSW = Data;    break;
        case ID_DATA_ID_MSW :   pTargeter->UniqueID.Word.MSW = Data;    break;
        case ID_DATA_AGING_CNT :pTargeter ->Aging_Cnt = Data;           break;


        case ID_STATUS :        pTargeter ->StautsInfo = Data;

                                if((pTargeter ->StautsInfo) & BIT1)     pTargeter->RunFlag  = 1;
                                else                                    pTargeter->RunFlag  = 0;

                                if((pTargeter ->StautsInfo) & BIT2)     pTargeter->Charging_End  = 1;
                                else                                    pTargeter->Charging_End  = 0;

                                if((pTargeter ->StautsInfo) & BIT3)     pTargeter->AutoAgingEndRx  = 1;
                                else                                    pTargeter->AutoAgingEndRx  = 0;

                                break;

        case ID_CMD_RUN:    pTargeter->RunFlag  = 1;                    break;
        case ID_CMD_STOP:   pTargeter->RunFlag  = 0;                    break;
        case ID_FAULT:      pTargeter->fault  = Data;    break;

        case ID_EOD :       pTargeter->Connected  = 1;
                            if( pTargeter->UniqueID.All != pTargeter->Unique_ID_OLD.All)
                            {
                                pTargeter->AutoCal_end = 0;
                                pTargeter->AutoAging_End = 0;
                                pTargeter->Charging_End = 0;
                                pTargeter->Unique_ID_OLD.All = pTargeter->UniqueID.All;
                            }
                            break;
        }
    }
    pTargeter->CommTic = 0;
    pTargeter->Listen = 1;
}

#pragma CODE_SECTION(FindTarget, "ramfuncs");
int FindTarget( int ref, int avg, float coef)      // coef 작을수록 강하게 흔들림.
{
    int delta;
    int comp;

    if (coef == 0) coef = 1;

    delta = ref - avg;
    comp = delta / coef;

    if(comp == 0)
        if(delta < 0)              comp = -1;
        else if(delta > 0)         comp = 1;

    return comp;
}

int mon_result;
#pragma CODE_SECTION(ElectricalRequirementTest, "ramfuncs");
void ElectricalRequirementTest ( void )
{
    int i;
    int success;
    static int wait = 0;
    //step 1. Smilekey 장비 초기화.
         // - MakepktA(ID_REQ_CMD, DEFAULT_ALL) 전송.

    //step 2. 기본 전원 체크.
         // - +6V, +5V, +3.3V, +1.8V 전원 체크 오차 허용범위 고려.

    //step 3. LCD 설정 변경 Aging Mode, Count 3, time 220

    //step 4. Io, IR, I Charge OFFSET 설정.

    //Step 5. Vbat 게인 Calibration.

    //step 6. RUN. 1번 모듈만.

    //step 7. Ir, Io Calibration.

    //step 8. 주파수 검출.

    //step 9. 충전 릴레이 ON

    //step 10. I chg Calibration.

    //step 11. 충전 릴레이 Off

    //step 12. LCD 설정 Normal Mode로 원복

    //Step 13. PC에 결과 리포트 준비보고


///////// Auto calibration Stop Command
    if(( flag_RS485_data_new_C == 1 ) && ((wMb_control_data_C & BIT0) == 0) && (AutoCal_Step != InitState ))
    {
        SmileKey[0].AutoCal_ing = 0;
        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);
        AutoCal_Step = InitState;

//        flag_RS485_data_new_C = 0;
        MakePktA(ID_CMD_STOP, 0xffff);

        printf("ShutDown Auto Calibration Mode \n");
        fflush (stdout);
    }

    if(flag_RS485_data_new_C == 1 )
    {
        if( wMb_control_data_C == 0 )
            if(( AutoCal_Step == InitState ) && (AutoAging_Step == InitStateAging))  flag_RS485_data_new_C = 0;
    }
/////////////////////////////////

//////// Calibration 진행중 Disconnected. 처리.
    if(AutoCal_Step > CheckControlVolt)
    {
        if( SmileKey[0].Connected == 0 )
        {
            SmileKey[0].AutoCal_ing = 0;
            ONOFF_RELAY1(OFF);
            ONOFF_RELAY2(OFF);
            ONOFF_RELAY3(OFF);
            SmileKey[0].Error = ERR_DISCONNECTED;
            AutoCal_Step = InitState;
            MakePktA(ID_CMD_STOP, 0xffff);
            printf("SmileKey Disconnected!! \n");
            fflush (stdout);
        }
    }

//////// Calibration 진행중 Smilekey Fault occurrence!!
    if( SmileKey[0].fault != 0)
    {
        SmileKey[0].AutoCal_ing = 0;
        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);
        SmileKey[0].Error = ERR_SMILEKEY;
        AutoCal_Step = InitState;
        MakePktA(ID_CMD_STOP, 0xffff);
        printf("SmileKey Fault Occurrence!! \n");
        fflush (stdout);
    }

//////// Auto Calibration FSM Start!!
    switch( AutoCal_Step )
    {
    case InitState:
        if( flag_RS485_data_new_C == 1 ){
            if( wMb_control_data_C & BIT0 ){
                if( SmileKey[0].Connected == 1){                        // Auto Calibration Start Command.
                    flag_RS485_data_new_C = 0;
                    SmileKey[0].AutoCal_end = 0;
                    SmileKey[0].AutoAging_End = 0;
                    SmileKey[0].Charging_End = 0;
                    SmileKey[0].Error = 0;
                    SmileKey[0].Connected = 0;

                    wait = 0;
                    SmileKey[0].AutoCal_ing = 1;
                    reTryCnt = 0;

                    MakePktA(ID_REQ_CMD, DEFAULT_ALL);                  // 초기화 지령.

                    ONOFF_RELAY1(OFF);
                    ONOFF_RELAY2(OFF);
                    ONOFF_RELAY3(OFF);

                    AutoCal_Step = FactoryDefault;

                    printf("\t Auto Cal Start \n");
                    printf("Auto Cal State Change >> FactoryDefault \n");
                    fflush (stdout);
                }
                else { printf(" Disconnected SmileKey #1 \n"); fflush (stdout);}

                flag_RS485_data_new_C = 0;
            }
        }

        break;

    case FactoryDefault:
        if(SmileKey[0].Connected == 1)                          // 초기화 완료 확인.
        {
            for(i=0; i <SMILEKEY_SET_NUMBER; i++)
            {
                if((i >= SET_SK_IO_GAIN )&& (i <= SET_SK_ICHG_OFFSET)) continue;        // 비 초기화 영역.

                if( SmileKey[0].SetValue[i] != SMK_SET[0][DFT][i])                      // 초기화 됐는지 확인.
                {
                    SmileKey[0].Error = ERR_INIT;                                       // 초기화 에러.
                    AutoCal_Step = AutoCal_Error;
                    printf("SmileKey Initializing Error Index %d \n" , i);
                    fflush (stdout);
                    break;
                }
            }

            if(SmileKey[0].Error == 0)
            {
                MakePktA(0x80 + SET_SK_AGING_COUNT, 90);
                MakePktA(0x80 + SET_SK_MODE_SEL, MODE_AGING);
                MakePktA(0x80 + SET_SK_STOP_TIME, 220);

                AutoCal_Step = CheckControlVolt;
                printf("Auto Cal State Change >> CheckControlVolt \n ");
                fflush (stdout);
            }
        }
        else    reTryCnt++;
        // 초기화 리트라이.
        if(reTryCnt == 200) MakePktA(ID_REQ_CMD, DEFAULT_ALL);

        // 초기화 명령 이후 EOD 명령 못받음.
        if(reTryCnt > 400)
        {
            AutoCal_Step = AutoCal_Error;
            SmileKey[0].Error = ERR_INIT;
            printf("SmileKey Initializing Error NoAck EOD  \n" );
            fflush (stdout);
        }

        break;

        //동작 전원 체크.
    case CheckControlVolt:

        if((ADC_Avg[AD_P5V] < tolerance_5V_min) || (ADC_Avg[AD_P5V]  > tolerance_5V_max))           SmileKey[0].Error = ERR_5V;
        if((ADC_Avg[AD_P6V] < tolerance_6V_min) || (ADC_Avg[AD_P6V]  > tolerance_6V_max))           SmileKey[0].Error = ERR_6V;
        if((ADC_Avg[AD_P3_3V] < tolerance_3_3V_min) || (ADC_Avg[AD_P3_3V]  > tolerance_3_3V_max))   SmileKey[0].Error = ERR_3_3V;
        if((ADC_Avg[AD_P1_8V] < tolerance_1_8V_min) || (ADC_Avg[AD_P1_8V]  > tolerance_1_8V_max))   SmileKey[0].Error = ERR_1_8V;

        if(SmileKey[0].Error == 0) AutoCal_Step = OffsetCalibration;
        else
        {
            AutoCal_Step = AutoCal_Error;
            printf( "Control Voltage Error!! Error Code = %d \n" ,SmileKey[0].Error);
            fflush (stdout);
        }
        break;

    case OffsetCalibration:
        success = 0;

        // Idc Offset Calibration! ////////////////////////
        SmileKey[0].SetValue[SET_SK_IO_OFFSET] += FindTarget(0, SmileKey[0].Idc, IO_OFFSET_COEF );
        //offset value limitation check.
        if(( SmileKey[0].SetValue[SET_SK_IO_OFFSET] < -999) || (SmileKey[0].SetValue[SET_SK_IO_OFFSET] > 999)) SmileKey[0].Error = ERR_OFFSET_IDC;
        else MakePktA(0x80 + SET_SK_IO_OFFSET, SmileKey[0].SetValue[SET_SK_IO_OFFSET] );

        // Ir Offset Calibration! ////////////////////////
        SmileKey[0].SetValue[SET_SK_IR_OFFSET] += FindTarget(0, SmileKey[0].Ir, IR_OFFSET_COEF );
        //offset value limitation check.
        if(( SmileKey[0].SetValue[SET_SK_IR_OFFSET] < -999) || (SmileKey[0].SetValue[SET_SK_IR_OFFSET] > 999)) SmileKey[0].Error = ERR_OFFSET_IR;
        else MakePktA(0x80 + SET_SK_IR_OFFSET, SmileKey[0].SetValue[SET_SK_IR_OFFSET] );

        // Ic Offset Calibration! ////////////////////////
        SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] += FindTarget(0, SmileKey[0].I_Charge, I_CHARGE_OFFSET_COEF );
        //offset value limitation check.
        if(( SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] < -999) || (SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] > 999)) SmileKey[0].Error = ERR_OFFSET_ICH;
        else MakePktA(0x80 + SET_SK_ICHG_OFFSET, SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] );

        if( SmileKey[0].SetValue[SET_SK_IO_OFFSET] < -999 ) SmileKey[0].SetValue[SET_SK_IO_OFFSET] = -999;
        if( SmileKey[0].SetValue[SET_SK_IR_OFFSET] < -999 ) SmileKey[0].SetValue[SET_SK_IR_OFFSET] = -999;
        if( SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] < -999 ) SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] = -999;

        if( SmileKey[0].SetValue[SET_SK_IO_OFFSET] > 999 ) SmileKey[0].SetValue[SET_SK_IO_OFFSET] = 999;
        if( SmileKey[0].SetValue[SET_SK_IR_OFFSET] > 999 ) SmileKey[0].SetValue[SET_SK_IR_OFFSET] = 999;
        if( SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] > 999 ) SmileKey[0].SetValue[SET_SK_ICHG_OFFSET] = 999;

        if( SmileKey[0].Idc == 0 ) success |= BIT0;                     // Idc Offset Calibration Success.
        if( SmileKey[0].Ir == 0 )  success |= BIT1;                     // Ir Offset Calibration Success.
        if( SmileKey[0].I_Charge == 0 )  success |= BIT2;               // Ic Offset Calibration Success.


        if(SmileKey[0].Error != 0) AutoCal_Step = AutoCal_Error;
        else if(success == 7){  AutoCal_Step = VbatCalibration;  reTryCnt = 0;}

        // for Debug.
        printf( " ****  Offset Calibration **** \n");
        printf( "Io Offset  = %d \n" , SmileKey[0].SetValue[SET_SK_IO_OFFSET]);
        printf( "Ir Offset  = %d \n" , SmileKey[0].SetValue[SET_SK_IR_OFFSET]);
        printf( "Ic Offset  = %d \n" , SmileKey[0].SetValue[SET_SK_ICHG_OFFSET]);
        printf( "Retry Count  = %d \n" , reTryCnt++);
        fflush (stdout);

        break;

    case VbatCalibration:
//        ADC_Avg[AD_VBAT] = 4100;        // Test Code. should be delete.

        // Vbat Gain Calibration! ////////////////////////
        SmileKey[0].SetValue[SET_SK_Vbat_GAIN] += FindTarget(ADC_Avg[AD_VBAT]/10, SmileKey[0].Vbat, Vbat_GAIN_COEF );
        if(( SmileKey[0].SetValue[SET_SK_Vbat_GAIN] < -999) || (SmileKey[0].SetValue[SET_SK_Vbat_GAIN] > 999)) SmileKey[0].Error = ERR_GAIN_VBAT;
        else MakePktA(0x80 + SET_SK_Vbat_GAIN, SmileKey[0].SetValue[SET_SK_Vbat_GAIN] );

        if( SmileKey[0].SetValue[SET_SK_Vbat_GAIN] <-999 ) SmileKey[0].SetValue[SET_SK_Vbat_GAIN] =-999;
        if( SmileKey[0].SetValue[SET_SK_Vbat_GAIN] > 999 ) SmileKey[0].SetValue[SET_SK_Vbat_GAIN] = 999;

        if( SmileKey[0].Error != 0)
        {
            AutoCal_Step = AutoCal_Error;
            break;
        }

        if( SmileKey[0].Vbat == (ADC_Avg[AD_VBAT]/10) )
        {
            MakePktA(0x80 + SET_SK_IO, SMK_SET[0][DFT][SET_SK_IO] );      //No Idc control
            MakePktA(ID_CMD_RUN, 0xffff);
            printf( " ****  Run Command Transmit **** \n");
            AutoCal_Step = IRCalibration;
            reTryCnt = 0;
        }

        printf( " ****  Vbat Calibration **** \n");
        printf( "Vbat Gain  = %d \n" , SmileKey[0].SetValue[SET_SK_Vbat_GAIN]);
        printf( "smilekey Vbat  = %d, \t Jig Vbat = %d \n" , SmileKey[0].Vbat, ADC_Avg[AD_VBAT]/10);
        printf( "Retry Count  = %d \n" , reTryCnt++);
        fflush (stdout);

        break;
    case IRCalibration:
        success = 0;

        if(SmileKey[0].RunFlag == 1)
        {
            if( ECap1Regs.CAP1 != 0 )      SmileKey[0].Freq = (200000000/  ECap1Regs.CAP1)/1000;                // Get Freq.

            SmileKey[0].SetValue[SET_SK_IR_GAIN] += FindTarget(ADC_Avg[AD_IR], SmileKey[0].Ir, IR_GAIN_COEF );
            if(( SmileKey[0].SetValue[SET_SK_IR_GAIN] < -999) || (SmileKey[0].SetValue[SET_SK_IR_GAIN] > 999)) SmileKey[0].Error = ERR_GAIN_IR;
            else MakePktA(0x80 + SET_SK_IR_GAIN, SmileKey[0].SetValue[SET_SK_IR_GAIN] );

            if(SmileKey[0].Error != 0)
            {
                   SmileKey[0].Error = ERR_GAIN_IR;
                   AutoCal_Step = AutoCal_Error;
                   break;
            }

            printf( " ****  Ir Calibration **** \n");
            printf( "Run state  = %d \n" , SmileKey[0].RunFlag);
            printf( "Ir Gain  = %d \n" , SmileKey[0].SetValue[SET_SK_IR_GAIN]);
            printf( "smilekey Ir  = %d, \t Jig Ir = %d \n" , SmileKey[0].Ir, ADC_Avg[AD_IR]);
            printf( "Retry Count  = %d \n" , reTryCnt++);
            fflush (stdout);
        }

        if( SmileKey[0].Ir == ADC_Avg[AD_IR] ) { MakePktA(0x80 + SET_SK_IO, IDC_REF );    AutoCal_Step = IDCCalibration; reTryCnt = 0;}

        break;

    case IDCCalibration:
        success = 0;
        if((SmileKey[0].RunFlag == 1) && ( SmileKey[0].Idc != 0 ))
        {

            if( ECap1Regs.CAP1 != 0 )      SmileKey[0].Freq = (200000000/  ECap1Regs.CAP1)/1000;                // Get Freq.

            SmileKey[0].SetValue[SET_SK_IO_GAIN] += FindTarget(ADC_Avg[AD_IDC]/10, SmileKey[0].Idc, IDC_GAIN_COEF );
            if(( SmileKey[0].SetValue[SET_SK_IO_GAIN] < -999) || (SmileKey[0].SetValue[SET_SK_IO_GAIN] > 999)) SmileKey[0].Error = ERR_GAIN_IDC;
            else MakePktA(0x80 + SET_SK_IO_GAIN, SmileKey[0].SetValue[SET_SK_IO_GAIN] );


            // for debug.
            printf( " ****  Idc Calibration **** \n");
            printf( "Run state  = %d \n" , SmileKey[0].RunFlag);
            printf( "Idc Gain  = %d \n" , SmileKey[0].SetValue[SET_SK_IO_GAIN]);
            printf( "smilekey Idc  = %d, \t Jig Idc = %d \n" , SmileKey[0].Idc, (ADC_Avg[AD_IDC]/10));
            printf( "Retry Count  = %d \n" , reTryCnt++);
            fflush (stdout);
        }

        if(SmileKey[0].Error != 0)
        {
            AutoCal_Step = AutoCal_Error;
            break;
        }

        if( SmileKey[0].Idc == (ADC_Avg[AD_IDC]/10) )
        {
            MakePktA(0x80 + SET_SK_IO, SMK_SET[0][DFT][SET_SK_IO] );
            MakePktA(ID_CMD_STOP, 0xffff);
            ONOFF_RELAY1(ON);                   //충전 Relay On
            AutoCal_Step = IChageCalibration;
            reTryCnt = 0;
        }
        break;

    case IChageCalibration:
//        ADC_Avg[AD_I_Chg1] = 1920; // Test Code. should be delete.

        SmileKey[0].SetValue[SET_SK_ICHG_GAIN] += FindTarget(ADC_Avg[AD_I_Chg1]/10, SmileKey[0].I_Charge, I_CHARGE_GAIN_COEF );
        if(( SmileKey[0].SetValue[SET_SK_ICHG_GAIN] < -999) || (SmileKey[0].SetValue[SET_SK_ICHG_GAIN] > 999)) SmileKey[0].Error = ERR_GAIN_ICH;
        else MakePktA(0x80 + SET_SK_ICHG_GAIN, SmileKey[0].SetValue[SET_SK_ICHG_GAIN] );

        if(SmileKey[0].Error != 0)
        {
            AutoCal_Step = AutoCal_Error;
            break;
        }

        if( SmileKey[0].I_Charge == (ADC_Avg[AD_I_Chg1]/10) )
        {
            ONOFF_RELAY1(OFF);
            MakePktA(0x80 + SET_SK_AGING_COUNT, 1);
            MakePktA(0x80 + SET_SK_MODE_SEL, MODE_NORMAL);
            MakePktA(0x80 + SET_SK_STOP_TIME, 50);
            AutoCal_Step = Final_Run_cmd;
            reTryCnt = 0;
        }

        // for debug.
        printf( " ****  I charge Calibration **** \n");
        printf( "I Charge Gain  = %d \n" , SmileKey[0].SetValue[SET_SK_ICHG_GAIN]);
        printf( "smilekey Ic  = %d, \t Jig Ic = %d \n" , SmileKey[0].I_Charge, (ADC_Avg[AD_I_Chg1]/10));
        printf( "Retry Count  = %d \n" , reTryCnt++);
        fflush (stdout);
        break;

    case Final_Run_cmd :
        MakePktA(ID_CMD_RUN, 0xffff);
        AutoCal_Step = OutputCheck;
        wait = 0;
        printf( " ****  Run Command Transmit **** \n");
        fflush (stdout);
       break;

    case OutputCheck :
        success = 0;
        if( SmileKey[0].RunFlag == 1)
        {
            wait++;
            if(wait > 10)
            {
                if((SmileKey[0].Ir < tolerance_Ir_min) || (SmileKey[0].Ir  > tolerance_Ir_max))             {            SmileKey[0].Error = ERR_OUT_IR; AutoCal_Step = AutoCal_Error;}
                else success |= BIT0;

                if((SmileKey[0].Po < tolerance_Po_min) || (SmileKey[0].Po  > tolerance_Po_max))             {            SmileKey[0].Error = ERR_OUT_PO; AutoCal_Step = AutoCal_Error;}
                else success |= BIT1;
            }
        }
        else
        {
            reTryCnt++;
            wait = 0;
        }

        if( reTryCnt == 40) MakePktA(ID_CMD_RUN, 0xffff);           // Run Retry.
        if(reTryCnt > 80){ SmileKey[0].Error = ERR_RUN_ERROR; AutoCal_Step = AutoCal_Error; }

        // for debug.
        printf( " **** Output Check **** \n");
        printf( "Run state  = %d \n" , SmileKey[0].RunFlag);
        printf( "Ir Output  = %d, \t Power Output = %d \n" , SmileKey[0].Ir, SmileKey[0].Po);
        printf( "Retry Count  = %d \n" , reTryCnt);
        fflush (stdout);

        if(success == 3)
        {
//           MakePktA(ID_CMD_STOP, 0xffff);
           AutoCal_Step = AutoCal_End;
        }

        break;

    case AutoCal_End :
        MakePktA(0x80 + SET_SK_IO, SMK_SET[0][DFT][SET_SK_IO] );
        SmileKey[0].AutoCal_end = 1;
        SmileKey[0].AutoCal_ing = 0;
        reTryCnt = 0;

        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);
        AutoCal_Step = InitState;
        printf( " **** Success Calibration **** \n");

        break;

    case AutoCal_Error:
        //Relay Off Stop 등등...
        SmileKey[0].AutoCal_ing = 0;
        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);
        MakePktA(ID_CMD_STOP, 0xffff);
        MakePktA(0x80 + SET_SK_IO, SMK_SET[0][DFT][SET_SK_IO] );
        AutoCal_Step = InitState;
        reTryCnt = 0;
        printf( " **** Error Calibration **** \n");
        break;
    }

    Step_Cali = AutoCal_Step;
}

#pragma CODE_SECTION(AgingTest, "ramfuncs");
void AgingTest( void )
{
    int i;
    int check, wait;
    //step 1. MakepktA(ID_REQ_CMD, ALL) 전송 후  EOD 확인 하여 Ready 플래그 대응.

    //step 2. LCD 설정 변경 Aging Mode, Count 90, time 320

    //Step 3. RUN. 모든 모듈.

    //step 4. 에이징 완료시 까지 데이터만 갱신.

    //step 5. 충전 릴레이 On

    //step 6. 4시간 대기 충전 완료 결과 확인. ( 베터리 전압 4.1V 이상 & I charg  0.22mA 이하 확인)

    //step 7. 에이징 완료.

    if(( flag_RS485_data_new_C == 1 ) && ((wMb_control_data_C & BIT1) == 0) && (AutoAging_Step != InitStateAging ))            // Auto Aging Mode Stop Command.
    {
        AutoAging_Step = InitStateAging;
//        flag_RS485_data_new_C = 0;
        MakePktA(ID_CMD_STOP, 0xffff);

        printf("ShutDown Aging Mode \n");
        fflush (stdout);
    }

    switch( AutoAging_Step )
    {
    case InitStateAging:
        if( flag_RS485_data_new_C == 1 ){
            if( wMb_control_data_C & BIT1 ){                        // Auto Aging Start Cmd.
                for(i=0; i<MODULE_MAX; i++) if( SmileKey[i].Connected == 1) { AutoAging_Step = AgingSetting; break;}
                flag_RS485_data_new_C = 0;
            }
        }
        break;
    case AgingSetting :

        if( SmileKey[0].Connected == 1)
        {
            ONOFF_RELAY1(OFF);
            MakePktA(0x80 + SET_SK_AGING_COUNT, 90);
            MakePktA(0x80 + SET_SK_MODE_SEL, MODE_AGING);
            MakePktA(0x80 + SET_SK_STOP_TIME, 320);
            SmileKey[0].AutoAging = 1;
        }
        if( SmileKey[1].Connected == 1)
        {
            ONOFF_RELAY2(OFF);
            MakePktB(0x80 + SET_SK_AGING_COUNT, 90);
            MakePktB(0x80 + SET_SK_MODE_SEL, MODE_AGING);
            MakePktB(0x80 + SET_SK_STOP_TIME, 320);
            SmileKey[1].AutoAging = 1;
        }
        if( SmileKey[2].Connected == 1)
        {
            ONOFF_RELAY3(OFF);
            MakePktD(0x80 + SET_SK_AGING_COUNT, 90);
            MakePktD(0x80 + SET_SK_MODE_SEL, MODE_AGING);
            MakePktD(0x80 + SET_SK_STOP_TIME, 320);
            SmileKey[2].AutoAging = 1;
        }
        for(i = 0; i < MODULE_MAX; i++)
        {
            SmileKey[i].Aging_tic = 0;
            SmileKey[i].AgingTime = 0;
            SmileKey[i].AutoAging_End = 0;
        }

        if(( SmileKey[0].Connected == 0) && (SmileKey[1].Connected == 0) && (SmileKey[2].Connected == 0))
        {
            AutoAging_Step = InitStateAging;
        }
        else AutoAging_Step = RunCmdTransmitt;
        break;

    case RunCmdTransmitt:
        if( SmileKey[0].Connected == 1)         MakePktA(ID_CMD_RUN, 0xffff);
        if( SmileKey[1].Connected == 1)         MakePktB(ID_CMD_RUN, 0xffff);
        if( SmileKey[2].Connected == 1)         MakePktD(ID_CMD_RUN, 0xffff);
        AutoAging_Step = Aging;
        break;

    case Aging:
        SmileKey[0].Aging_tic++;
        if(SmileKey[0].Aging_tic == 60)
        {
            SmileKey[0].Aging_tic = 0;
            SmileKey[0].AgingTime++;
        }

        check = 0;
        for (i = 0; i < MODULE_MAX; i++ )
            if( ((SmileKey[i].Connected == 0) || (SmileKey[i].AutoAgingEndRx == 1)) && (SmileKey[i].RunFlag == 0)) check |= (BIT0 << i);

        if ( check == 7){ AutoAging_Step = NormalSetting;  break;}

        check = 0;
        for (i = 0; i < MODULE_MAX; i++ )
            if(SmileKey[i].Connected == 0)
                if( ++check == 3 ) {
                    SmileKey[i].Error = ERR_DISCONNECTED;
                    AutoAging_Step = AutoAging_Err;
                    break;
                }

        check = 0;
        for (i = 0; i < MODULE_MAX; i++ )
            if(SmileKey[i].fault != 0)
                if( ++check == 3 )
                {
                    SmileKey[i].Error = ERR_SMILEKEY;
                    AutoAging_Step = AutoAging_Err;
                    break;
                }

        break;
    case NormalSetting :
        if( SmileKey[0].Connected == 1)
        {
            MakePktA(0x80 + SET_SK_AGING_COUNT, 0);
            MakePktA(0x80 + SET_SK_MODE_SEL, MODE_NORMAL);
            MakePktA(0x80 + SET_SK_STOP_TIME, 50);
            ONOFF_RELAY1(ON);
            SmileKey[0].Charging_tic = 0;
            SmileKey[0].ChargingTime = 0;
            SmileKey[0].AutoAging =0;
            SmileKey[0].Charging =1;
        }
        if( SmileKey[1].Connected == 1)
        {
            MakePktB(0x80 + SET_SK_AGING_COUNT, 0);
            MakePktB(0x80 + SET_SK_MODE_SEL, MODE_NORMAL);
            MakePktB(0x80 + SET_SK_STOP_TIME, 50);
            ONOFF_RELAY2(ON);
            SmileKey[1].Charging_tic = 0;
            SmileKey[1].ChargingTime = 0;
            SmileKey[1].AutoAging =0;
            SmileKey[1].Charging =1;
        }
        if( SmileKey[2].Connected == 1)
        {
            MakePktD(0x80 + SET_SK_AGING_COUNT, 0);
            MakePktD(0x80 + SET_SK_MODE_SEL, MODE_NORMAL);
            MakePktD(0x80 + SET_SK_STOP_TIME, 50);
            ONOFF_RELAY3(ON);
            SmileKey[2].Charging_tic = 0;
            SmileKey[2].ChargingTime = 0;
            SmileKey[2].AutoAging =0;
            SmileKey[2].Charging =1;
        }

        AutoAging_Step = BatteryCharging;
        break;
    case BatteryCharging :
        check = 0;
        for( i =0; i < MODULE_MAX; i++ )
        {
            if( SmileKey[i].Charging_End == 0 )
            {
                if( ++SmileKey[i].Charging_tic == 60 )
                {
                    SmileKey[i].Charging_tic = 0;
                    SmileKey[i].ChargingTime++;
                }
            }
            else if(( SmileKey[i].Charging_End == 1 )||(SmileKey[i].Connected == 0 )) check++;
        }
        if(check == 3)
        {
            ONOFF_RELAY1(OFF);
            ONOFF_RELAY2(OFF);
            ONOFF_RELAY3(OFF);
            AutoAging_Step = ChargingSpecCheck;
        }
        break;
    case ChargingSpecCheck:
        check = 0; wait = 0;
        for( i=0; i < MODULE_MAX; i++ ) if((SmileKey[i].Charging_End == 1)||(SmileKey[i].Connected == 0) ) wait++;
        for( i=0; i < MODULE_MAX; i++ )
        {
            if( wait == 3)
            {

                if((SmileKey[i].Vbat < tolerance_Vbat_min) || (SmileKey[i].Vbat  > tolerance_Vbat_max)) {  SmileKey[i].Error = ERR_CHARGING_V; }
                else if(SmileKey[i].ChargingTime > HOUR * CHARGING_TIME) {SmileKey[i].Error = ERR_CHARGING_T; }

                if(( SmileKey[i].Error == 0) || (SmileKey[i].Connected == 0)) check++;

                if(check == 3)       AutoAging_Step = AgingEnd;
                else                 AutoAging_Step = Charging_Err;
            }
        }
        break;
    case Charging_Err:
        for( i=0; i < MODULE_MAX; i++ )
        {
            if((SmileKey[i].Error == 0) )
            {
                SmileKey[i].AutoAging_End = 1;
                SmileKey[i].Charging_End = 1;
                SmileKey[i].Charging     = 0;
            }
            SmileKey[i].AutoAging = 0;
        }
        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);

        AutoAging_Step = InitStateAging;
        break;
    case AgingEnd:
        for( i=0; i < MODULE_MAX; i++ ) if((SmileKey[i].Connected == 1) )
        {
            SmileKey[i].AutoAging_End = 1;
            SmileKey[i].Charging_End = 1;
            SmileKey[i].Charging     = 0;
            SmileKey[i].AutoAging = 0;
        }
        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);
        AutoAging_Step = InitStateAging;
        break;

    case AutoAging_Err:
        for( i=0; i < MODULE_MAX; i++  )
        {
            SmileKey[i].Charging  = 0;
            SmileKey[i].AutoAging = 0;
        }
        ONOFF_RELAY1(OFF);
        ONOFF_RELAY2(OFF);
        ONOFF_RELAY3(OFF);
        AutoAging_Step = InitStateAging;
        break;
    }
    Step_Aging = AutoAging_Step;
}


