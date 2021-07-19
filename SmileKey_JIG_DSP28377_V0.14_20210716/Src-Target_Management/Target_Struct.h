/*
 * Target_Struct.h
 *
 *  Created on: 2021. 6. 21.
 *      Author: YooKH
 */

#ifndef SRC_TARGET_MANAGEMENT_TARGET_STRUCT_H_
#define SRC_TARGET_MANAGEMENT_TARGET_STRUCT_H_

#define SMILEKEY_SET_NUMBER          22

struct ID_WORD{
    unsigned int LSW;
    unsigned int MSW;
};

union UniqueID_Word{
    unsigned long  All;
    struct ID_WORD Word;
};


typedef struct TargetData
{
    int Po;
    int Vo;
    int Idc;
    int Ir;
    unsigned int Version;
    int Vbat;
    int I_Charge;
    unsigned int Phase;
    unsigned int RunFlag;
    unsigned int Freq;
    unsigned int Temperature1;
    unsigned int Temperature2;
    union UniqueID_Word UniqueID;
    union UniqueID_Word Unique_ID_OLD;

    unsigned int StautsInfo;

    unsigned int Listen;
    unsigned int Connected;
    unsigned int CommTic;


    unsigned int AutoCal_ing;
    unsigned int AutoCal_end;

    unsigned int AutoAging;
    unsigned int AutoAging_End;
    unsigned int AutoAgingEndRx;
    unsigned int Charging;
    unsigned int Charging_End;
    unsigned int Aging_Cnt;

    unsigned int Aging_tic;
    unsigned int AgingTime;
    unsigned int Charging_tic;
    unsigned int ChargingTime;

    unsigned int Error;

    int          SetValue[SMILEKEY_SET_NUMBER];

    unsigned int fault;
}TargetDB;

#define HOUR            60

#define ERR_NO          0
#define ERR_INIT        1
#define ERR_5V          2
#define ERR_6V          3
#define ERR_3_3V        4
#define ERR_1_8V        5
#define ERR_FREQ_CAP    6
#define ERR_OFFSET_IDC  7
#define ERR_OFFSET_IR   8
#define ERR_OFFSET_ICH  9
#define ERR_GAIN_VBAT   10
#define ERR_GAIN_IR     11
#define ERR_GAIN_IDC    12
#define ERR_GAIN_ICH    13

#define ERR_OUT_IR      14
#define ERR_OUT_PO      15
#define ERR_RUN_ERROR   16
#define ERR_CHARGING_V  17
#define ERR_CHARGING_T  18

#define ERR_DISCONNECTED    99
#define ERR_SMILEKEY        100


#endif /* SRC_TARGET_MANAGEMENT_TARGET_STRUCT_H_ */
