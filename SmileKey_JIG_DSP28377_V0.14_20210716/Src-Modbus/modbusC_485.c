///////////////////////////////////////////////////////////////////////////////////////////////
//																							 //
//																							 //
//							Modbus_485.c													 //
//																							 //
//																							 //
/////////////////////////////////////////////////////////////////////////////////////////////// 
/*******************************************************************
 *
 *    DESCRIPTION: Modbus 485 communication service
 *
 *    AUTHOR:	  Yoo Kwang hyun
 *
 *    HISTORY:	  2011.03.03	
 *
 *******************************************************************/

/** Include file **/
//#include "DSP2803x_compact.h"
#include "F28x_Project.h"
#include "modbusC_485.h"
#include "../Src-TargetCommu/SmileKey_Define.h"

//*************************************************************************
// SCIA Function	for Remote Control
//*************************************************************************
extern TargetDB SmileKey[3];
extern int Step_Cali;
extern int Step_Aging;
 
//#pragma CODE_SECTION(MODBUS_FUNC_4, "ramfuncs");
void MODBUS_FUNC_4_C(void)
{
    Uint16 i, j, NumData;

    i=0;
    NumData = NUM_QUE_RD_C[start_point_C];
    j = ID_QUE_RD_C[start_point_C] + 0; //+ 30000;

    if(j<=MB_DATA_JIG_VERSION)  {
        switch(j) {
                    //--- Set Control value feedback : P.S-->Customer(Read)
            case    MB_DATA_STATUS:        wModData_C[i++]= GetJigStatus();             if(i>=NumData)  break;
            case    MB_DATA_WARNNIG:       wModData_C[i++]= 0;                          if(i>=NumData)  break;
            case    MB_DATA_FAULT:         wModData_C[i++]= GetJigFault();              if(i>=NumData)  break;
// Target 1
            case    MB_DATA_TARGET1_STATUS :    wModData_C[i++]= SmileKey[0].StautsInfo;        if(i>=NumData)  break;
            case    MB_DATA_TARGET1_FAULT :     wModData_C[i++]= SmileKey[0].Error;             if(i>=NumData)  break;
            case    MB_DATA_TARGET1_POWER :     wModData_C[i++]= SmileKey[0].Po;                if(i>=NumData)  break;
            case    MB_DATA_TARGET1_VOLTAGE :   wModData_C[i++]= SmileKey[0].Vo;                if(i>=NumData)  break;
            case    MB_DATA_TARGET1_IDC :       wModData_C[i++]= SmileKey[0].Idc;               if(i>=NumData)  break;
            case    MB_DATA_TARGET1_IR :        wModData_C[i++]= SmileKey[0].Ir;                if(i>=NumData)  break;
            case    MB_DATA_TARGET1_Vbat :      wModData_C[i++]= SmileKey[0].Vbat;              if(i>=NumData)  break;
            case    MB_DATA_TARGET1_IChg :      wModData_C[i++]= SmileKey[0].I_Charge;          if(i>=NumData)  break;
            case    MB_DATA_TARGET1_PHASE :     wModData_C[i++]= SmileKey[0].Phase;             if(i>=NumData)  break;
            case    MB_DATA_TARGET1_VERSION :   wModData_C[i++]= SmileKey[0].Version;           if(i>=NumData)  break;
            case    MB_DATA_TARGET1_OTP1 :      wModData_C[i++]= SmileKey[0].Temperature1;      if(i>=NumData)  break;
            case    MB_DATA_TARGET1_OTP2 :      wModData_C[i++]= SmileKey[0].Temperature2;      if(i>=NumData)  break;
            case    MB_DATA_TARGET1_ID_LSW :    wModData_C[i++]= SmileKey[0].UniqueID.Word.LSW; if(i>=NumData)  break;
            case    MB_DATA_TARGET1_ID_MSW :    wModData_C[i++]= SmileKey[0].UniqueID.Word.MSW; if(i>=NumData)  break;
            case    MB_DATA_TARGET1_FREQ :      wModData_C[i++]= SmileKey[0].Freq;              if(i>=NumData)  break;
            case    MB_DATA_TARGET1_RESERVED2 : wModData_C[i++]= Step_Cali;                     if(i>=NumData)  break;
            case    MB_DATA_TARGET1_RESERVED3 : wModData_C[i++]= Step_Aging;                    if(i>=NumData)  break;

// Auto Cali Report
            case    MB_DATA_REPORT_IR_OFFSET :  wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IR_OFFSET];    if(i>=NumData)  break;
            case    MB_DATA_REPORT_IR_GAIN :    wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IR_GAIN];      if(i>=NumData)  break;
            case    MB_DATA_REPORT_IDC_OFFSET : wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IO_OFFSET];    if(i>=NumData)  break;
            case    MB_DATA_REPORT_IDC_GAIN :   wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IO_GAIN];      if(i>=NumData)  break;
            case    MB_DATA_REPORT_Vbat_GAIN :  wModData_C[i++]= SmileKey[0].SetValue[SET_SK_Vbat_GAIN];    if(i>=NumData)  break;
            case    MB_DATA_REPORT_IChg_OFFSET :wModData_C[i++]= SmileKey[0].SetValue[SET_SK_ICHG_OFFSET];  if(i>=NumData)  break;
            case    MB_DATA_REPORT_IChg_GAIN :  wModData_C[i++]= SmileKey[0].SetValue[SET_SK_ICHG_GAIN];    if(i>=NumData)  break;

// Target 2
            case    MB_DATA_TARGET2_STATUS :    wModData_C[i++]= SmileKey[1].StautsInfo;        if(i>=NumData)  break;
            case    MB_DATA_TARGET2_FAULT :     wModData_C[i++]= SmileKey[1].Error;             if(i>=NumData)  break;
            case    MB_DATA_TARGET2_POWER :     wModData_C[i++]= SmileKey[1].Po;                if(i>=NumData)  break;
            case    MB_DATA_TARGET2_VOLTAGE :   wModData_C[i++]= SmileKey[1].Vo;                if(i>=NumData)  break;
            case    MB_DATA_TARGET2_IDC :       wModData_C[i++]= SmileKey[1].Idc;               if(i>=NumData)  break;
            case    MB_DATA_TARGET2_IR :        wModData_C[i++]= SmileKey[1].Ir;                if(i>=NumData)  break;
            case    MB_DATA_TARGET2_Vbat :      wModData_C[i++]= SmileKey[1].Vbat;              if(i>=NumData)  break;
            case    MB_DATA_TARGET2_IChg :      wModData_C[i++]= SmileKey[1].I_Charge;          if(i>=NumData)  break;
            case    MB_DATA_TARGET2_PHASE :     wModData_C[i++]= SmileKey[1].Phase;             if(i>=NumData)  break;
            case    MB_DATA_TARGET2_VERSION :   wModData_C[i++]= SmileKey[1].Version;           if(i>=NumData)  break;
            case    MB_DATA_TARGET2_OTP1 :      wModData_C[i++]= SmileKey[1].Temperature1;      if(i>=NumData)  break;
            case    MB_DATA_TARGET2_OTP2 :      wModData_C[i++]= SmileKey[1].Temperature2;      if(i>=NumData)  break;
            case    MB_DATA_TARGET2_ID_LSW :    wModData_C[i++]= SmileKey[1].UniqueID.Word.LSW; if(i>=NumData)  break;
            case    MB_DATA_TARGET2_ID_MSW :    wModData_C[i++]= SmileKey[1].UniqueID.Word.MSW; if(i>=NumData)  break;
            case    MB_DATA_TARGET2_FREQ :      wModData_C[i++]= SmileKey[1].Freq;              if(i>=NumData)  break;
            case    MB_DATA_TARGET2_RESERVED2 : wModData_C[i++]= 777;                           if(i>=NumData)  break;
            case    MB_DATA_TARGET2_RESERVED3 : wModData_C[i++]= 888;                           if(i>=NumData)  break;
// Target 3
            case    MB_DATA_TARGET3_STATUS :    wModData_C[i++]= SmileKey[2].StautsInfo;        if(i>=NumData)  break;
            case    MB_DATA_TARGET3_FAULT :     wModData_C[i++]= SmileKey[2].Error;             if(i>=NumData)  break;
            case    MB_DATA_TARGET3_POWER :     wModData_C[i++]= SmileKey[2].Po;                if(i>=NumData)  break;
            case    MB_DATA_TARGET3_VOLTAGE :   wModData_C[i++]= SmileKey[2].Vo;                if(i>=NumData)  break;
            case    MB_DATA_TARGET3_IDC :       wModData_C[i++]= SmileKey[2].Idc;               if(i>=NumData)  break;
            case    MB_DATA_TARGET3_IR :        wModData_C[i++]= SmileKey[2].Ir;                if(i>=NumData)  break;
            case    MB_DATA_TARGET3_Vbat :      wModData_C[i++]= SmileKey[2].Vbat;              if(i>=NumData)  break;
            case    MB_DATA_TARGET3_IChg :      wModData_C[i++]= SmileKey[2].I_Charge;          if(i>=NumData)  break;
            case    MB_DATA_TARGET3_PHASE :     wModData_C[i++]= SmileKey[2].Phase;             if(i>=NumData)  break;
            case    MB_DATA_TARGET3_VERSION :   wModData_C[i++]= SmileKey[2].Version;           if(i>=NumData)  break;
            case    MB_DATA_TARGET3_OTP1 :      wModData_C[i++]= SmileKey[2].Temperature1;      if(i>=NumData)  break;
            case    MB_DATA_TARGET3_OTP2 :      wModData_C[i++]= SmileKey[2].Temperature2;      if(i>=NumData)  break;
            case    MB_DATA_TARGET3_ID_LSW :    wModData_C[i++]= SmileKey[2].UniqueID.Word.LSW; if(i>=NumData)  break;
            case    MB_DATA_TARGET3_ID_MSW :    wModData_C[i++]= SmileKey[2].UniqueID.Word.MSW; if(i>=NumData)  break;
            case    MB_DATA_TARGET3_FREQ :      wModData_C[i++]= SmileKey[2].Freq;              if(i>=NumData)  break;
            case    MB_DATA_TARGET3_RESERVED2 : wModData_C[i++]= 777;                           if(i>=NumData)  break;
            case    MB_DATA_TARGET3_RESERVED3 : wModData_C[i++]= 888;                           if(i>=NumData)  break;
// JIG AD
            case    MB_DATA_JIG_IR :            wModData_C[i++]= ADC_Avg[AD_IR];                if(i>=NumData)  break;
            case    MB_DATA_JIG_V_BAT :         wModData_C[i++]= ADC_Avg[AD_VBAT];              if(i>=NumData)  break;
            case    MB_DATA_JIG_5V :            wModData_C[i++]= ADC_Avg[AD_P5V];               if(i>=NumData)  break;
            case    MB_DATA_JIG_3_3V :          wModData_C[i++]= ADC_Avg[AD_P3_3V];             if(i>=NumData)  break;
            case    MB_DATA_JIG_1_8V :          wModData_C[i++]= ADC_Avg[AD_P1_8V];             if(i>=NumData)  break;
            case    MB_DATA_JIG_6V :            wModData_C[i++]= ADC_Avg[AD_P6V];               if(i>=NumData)  break;
            case    MB_DATA_JIG_IDC :           wModData_C[i++]= ADC_Avg[AD_IDC];               if(i>=NumData)  break;
            case    MB_DATA_JIG_I_Chg1 :        wModData_C[i++]= ADC_Avg[AD_I_Chg1];            if(i>=NumData)  break;
            case    MB_DATA_JIG_I_Chg2 :        wModData_C[i++]= ADC_Avg[AD_I_Chg2];            if(i>=NumData)  break;
            case    MB_DATA_JIG_I_Chg3 :        wModData_C[i++]= ADC_Avg[AD_I_Chg3];            if(i>=NumData)  break;
            case    MB_DATA_JIG_2_5V :          wModData_C[i++]= ADC_Avg[AD_P2_5V];             if(i>=NumData)  break;
            case    MB_DATA_JIG_1_65V :         wModData_C[i++]= ADC_Avg[AD_P1_65V];            if(i>=NumData)  break;
// JIG Setting value
            case    MB_DATA_JIG_SET_IR_OFFSET :           wModData_C[i++]= C12.BUFF[SET_IR_OFFSET];               if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Vbat_OFFSET :         wModData_C[i++]= C12.BUFF[SET_Vbat_OFFSET ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_5V_OFFSET   :         wModData_C[i++]= C12.BUFF[SET_5V_OFFSET   ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_3_3V_OFFSET :         wModData_C[i++]= C12.BUFF[SET_3_3V_OFFSET ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_1_8V_OFFSET :         wModData_C[i++]= C12.BUFF[SET_1_8V_OFFSET ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_6V_OFFSET   :         wModData_C[i++]= C12.BUFF[SET_6V_OFFSET   ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Ic1_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_Ichg1_OFFSET];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_IDC_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_IDC_OFFSET  ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Ic2_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_Ichg2_OFFSET];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_2_5V_OFFSET :         wModData_C[i++]= C12.BUFF[SET_2_5V_OFFSET ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_1_65V_OFFSET :        wModData_C[i++]= C12.BUFF[SET_1_65V_OFFSET];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Ic3_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_Ichg3_OFFSET];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_IR_GAIN     :         wModData_C[i++]= C12.BUFF[SET_IR_GAIN     ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Vbat_GAIN   :         wModData_C[i++]= C12.BUFF[SET_Vbat_GAIN   ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_5V_GAIN     :         wModData_C[i++]= C12.BUFF[SET_5V_GAIN     ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_3_3V_GAIN   :         wModData_C[i++]= C12.BUFF[SET_3_3V_GAIN   ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_1_8V_GAIN   :         wModData_C[i++]= C12.BUFF[SET_1_8V_GAIN   ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_6V_GAIN     :         wModData_C[i++]= C12.BUFF[SET_6V_GAIN     ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Ic1_GAIN    :         wModData_C[i++]= C12.BUFF[SET_Ichg1_GAIN  ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_IDC_GAIN    :         wModData_C[i++]= C12.BUFF[SET_IDC_GAIN    ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Ic2_GAIN    :         wModData_C[i++]= C12.BUFF[SET_Ichg2_GAIN  ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_2_5V_GAIN   :         wModData_C[i++]= C12.BUFF[SET_2_5V_GAIN   ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_1_65V_GAIN  :         wModData_C[i++]= C12.BUFF[SET_1_65V_GAIN  ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_SET_Ic3_GAIN    :         wModData_C[i++]= C12.BUFF[SET_Ichg3_GAIN  ];            if(i>=NumData)  break;
            case    MB_DATA_JIG_VERSION         :         wModData_C[i++]= C12.BUFF[SET_VERSION     ];            if(i>=NumData)  break;

            //--- Set value feedback : P.S-->Customer(Read/Write)       // 60000 ~

        }

        if(i==NumData)
        {
            MakePkt2RD_C(NumData, wModData_C, FUNC_QUE_C[start_point_C]);
            flag_RS485_receive_C = 1;
        }
        else MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x04);     // error - Invalid data number Range

        if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
     }
     else { // error - ID range out
        MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x03);      // error - Invalid data address Range
        if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
     }
}

/****************************************************************
//  function 6 protocol
*****************************************************************/
//#pragma CODE_SECTION(MODBUS_FUNC_6, "ramfuncs");
void MODBUS_FUNC_6_C(void)
{
    Uint16 PtrData, i;

    Addrs_C   = ID_QUE_WR_C[start_point_C];
    PtrData = MB_SET_CONTROL + Addrs_C;     // +40000;

    if( PtrData <= MB_SET_I_Chg3_GAIN )     // Ready to start Added.
    {   // multi write o.k
        if( PtrData <= MB_SET_I_Chg3_GAIN )                              // Ready to start Added.
        {
            i=Addrs_C;// - MB_FUNC36_START;//ID_QUE_WR_C[start_point_C];
            if(i==0)            // set start point, 0 == 40000
            {
                wMb_control_data_C=DATA_QUE_WR_C[start_point_data_C];
                flag_RS485_data_new_C=1;

                MakePkt2WR_F6_C(Addrs_C, wMb_control_data_C);
                if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
            }
            else
            {
                if(i <= MB_SET_I_Chg3_GAIN ) {
                    switch( i )
                    {
                          case MB_SET_IR_OFFSET          :   UpdateBuff_C( SET_IR_OFFSET     );                 break;
                          case MB_SET_VBAT_OFFSET        :   UpdateBuff_C( SET_Vbat_OFFSET   );                 break;
                          case MB_SET_5V_OFFSET          :   UpdateBuff_C( SET_5V_OFFSET     );                 break;
                          case MB_SET_3_3V_OFFSET        :   UpdateBuff_C( SET_3_3V_OFFSET   );                 break;
                          case MB_SET_1_8V_OFFSET        :   UpdateBuff_C( SET_1_8V_OFFSET   );                 break;
                          case MB_SET_6V_OFFSET          :   UpdateBuff_C( SET_6V_OFFSET     );                 break;
                          case MB_SET_I_Chg1_OFFSET      :   UpdateBuff_C( SET_Ichg1_OFFSET  );                 break;
                          case MB_SET_IDC_OFFSET         :   UpdateBuff_C( SET_IDC_OFFSET    );                 break;
                          case MB_SET_I_Chg2_OFFSET      :   UpdateBuff_C( SET_Ichg2_OFFSET  );                 break;
                          case MB_SET_2_5V_OFFSET        :   UpdateBuff_C( SET_2_5V_OFFSET   );                 break;
                          case MB_SET_1_65V_OFFSET       :   UpdateBuff_C( SET_1_65V_OFFSET  );                 break;
                          case MB_SET_I_Chg3_OFFSET      :   UpdateBuff_C( SET_Ichg3_OFFSET  );                 break;
                          case MB_SET_IR_GAIN            :   UpdateBuff_C( SET_IR_GAIN       );                 break;
                          case MB_SET_VBAT_GAIN          :   UpdateBuff_C( SET_Vbat_GAIN     );                 break;
                          case MB_SET_5V_GAIN            :   UpdateBuff_C( SET_5V_GAIN       );                 break;
                          case MB_SET_3_3V_GAIN          :   UpdateBuff_C( SET_3_3V_GAIN     );                 break;
                          case MB_SET_1_8V_GAIN          :   UpdateBuff_C( SET_1_8V_GAIN     );                 break;
                          case MB_SET_6V_GAIN            :   UpdateBuff_C( SET_6V_GAIN       );                 break;
                          case MB_SET_I_Chg1_GAIN        :   UpdateBuff_C( SET_Ichg1_GAIN    );                 break;
                          case MB_SET_IDC_GAIN           :   UpdateBuff_C( SET_IDC_GAIN      );                 break;
                          case MB_SET_I_Chg2_GAIN        :   UpdateBuff_C( SET_Ichg2_GAIN    );                 break;
                          case MB_SET_2_5V_GAIN          :   UpdateBuff_C( SET_2_5V_GAIN     );                 break;
                          case MB_SET_1_65V_GAIN         :   UpdateBuff_C( SET_1_65V_GAIN    );                 break;
                          case MB_SET_I_Chg3_GAIN        :   UpdateBuff_C( SET_Ichg3_GAIN    );                 break;
                    }
                }
                MakePkt2WR_F6_C(Addrs_C, DATA_QUE_WR_C[start_point_data_C]);
                if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
            }
            flag_RS485_receive_C = 1;
        }
        else
        {
            MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x03);      // error - Invalid data number Range
            if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
        }

        if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
    }
    else
    {   // error - Invalid data address Range
        MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x02);      // error - Invalid data address Range
        if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
        if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
    }
}

//#pragma CODE_SECTION(MODBUS_FUNC_16, "ramfuncs");
void MODBUS_FUNC_16_C(void) 
{
	Uint16 PtrData, NumData, i, j, k;

 	Addrs_C   = ID_QUE_WR_C[start_point_C];
 	PtrData = MB_SET_CONTROL + Addrs_C;     // +40000;

 	if(PtrData <= MB_SET_I_Chg3_GAIN )
 	{	// multi write o.k
 		NumData = NUM_QUE_WR_C[start_point_C];
 		if((PtrData+NumData-1)<=MB_SET_I_Chg3_GAIN)
 		{
 			i=ID_QUE_WR_C[start_point_C]; 	// set start point, 0 == 59999
            if(i==0)
            {

                wMb_control_data_C=DATA_QUE_WR_C[start_point_data_C];
                flag_RS485_data_new_C=1;
                if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
                k=1; i=1;
            }
            else
            {
                k=0;    //i=i-1;      // Notice !!! it need to be -1
            }
			if(NumData>k) {
				for(j=0;(k+j)<NumData;j++) {
					if((i+j)<= MB_SET_I_Chg3_GAIN) {
					    switch( i+j )
					    {
                        case MB_SET_IR_OFFSET          :   UpdateBuff_C( SET_IR_OFFSET     );                 break;
                         case MB_SET_VBAT_OFFSET        :   UpdateBuff_C( SET_Vbat_OFFSET   );                 break;
                         case MB_SET_5V_OFFSET          :   UpdateBuff_C( SET_5V_OFFSET     );                 break;
                         case MB_SET_3_3V_OFFSET        :   UpdateBuff_C( SET_3_3V_OFFSET   );                 break;
                         case MB_SET_1_8V_OFFSET        :   UpdateBuff_C( SET_1_8V_OFFSET   );                 break;
                         case MB_SET_6V_OFFSET          :   UpdateBuff_C( SET_6V_OFFSET     );                 break;
                         case MB_SET_I_Chg1_OFFSET      :   UpdateBuff_C( SET_Ichg1_OFFSET  );                 break;
                         case MB_SET_IDC_OFFSET         :   UpdateBuff_C( SET_IDC_OFFSET    );                 break;
                         case MB_SET_I_Chg2_OFFSET      :   UpdateBuff_C( SET_Ichg2_OFFSET  );                 break;
                         case MB_SET_2_5V_OFFSET        :   UpdateBuff_C( SET_2_5V_OFFSET   );                 break;
                         case MB_SET_1_65V_OFFSET       :   UpdateBuff_C( SET_1_65V_OFFSET  );                 break;
                         case MB_SET_I_Chg3_OFFSET      :   UpdateBuff_C( SET_Ichg3_OFFSET  );                 break;
                         case MB_SET_IR_GAIN            :   UpdateBuff_C( SET_IR_GAIN       );                 break;
                         case MB_SET_VBAT_GAIN          :   UpdateBuff_C( SET_Vbat_GAIN     );                 break;
                         case MB_SET_5V_GAIN            :   UpdateBuff_C( SET_5V_GAIN       );                 break;
                         case MB_SET_3_3V_GAIN          :   UpdateBuff_C( SET_3_3V_GAIN     );                 break;
                         case MB_SET_1_8V_GAIN          :   UpdateBuff_C( SET_1_8V_GAIN     );                 break;
                         case MB_SET_6V_GAIN            :   UpdateBuff_C( SET_6V_GAIN       );                 break;
                         case MB_SET_I_Chg1_GAIN        :   UpdateBuff_C( SET_Ichg1_GAIN    );                 break;
                         case MB_SET_IDC_GAIN           :   UpdateBuff_C( SET_IDC_GAIN      );                 break;
                         case MB_SET_I_Chg2_GAIN        :   UpdateBuff_C( SET_Ichg2_GAIN    );                 break;
                         case MB_SET_2_5V_GAIN          :   UpdateBuff_C( SET_2_5V_GAIN     );                 break;
                         case MB_SET_1_65V_GAIN         :   UpdateBuff_C( SET_1_65V_GAIN    );                 break;
                         case MB_SET_I_Chg3_GAIN        :   UpdateBuff_C( SET_Ichg3_GAIN    );                 break;
                            default :   break;
 						}
	                    if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
					}
			        else
			        {
			            MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x03);        // error - Invalid data number Range
			            for(i=0;i<NumData;i++)
			            {
			                if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
			            }
			        }
 				}
 			}
			MakePkt2WR_C(Addrs_C, NumData);
			flag_RS485_receive_C = 1;
		}
		else 
		{
			MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x03);		// error - Invalid data number Range
			for(i=0;i<NumData;i++) 
			{
				if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
			}
		}
		if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
	}
	else {	// error - Invalid data address Range
		MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x02);		// error - Invalid data address Range
		for(i=0;i<NumData;i++) 
			if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
		if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
	} 
}

/****************************************************************
//	function 23 protocol
*****************************************************************/
//#pragma CODE_SECTION(MODBUS_FUNC_23, "ramfuncs");
void MODBUS_FUNC_23_C(void) 
{
 	Uint16	NumData, i, j, k;	//, flag_changed;

 	/* Received Command processing */
 	if (start_point_C != end_point_C)
 	{
 		if(FUNC_QUE_C[start_point_C]==0x17)
 		{	// Write/read Muliple data : Customer-->P.S
 			Addrs_C   = ID_QUE_WR_C[start_point_C];
 			NumData = NUM_QUE_WR_C[start_point_C];

 		   if( ID_QUE_WR_C[start_point_C] <= MB_SET_I_Chg3_GAIN )
 		   {
 				i=ID_QUE_WR_C[start_point_C]-MB_SET_CONTROL;	// set start point, 0 == 59999
 				if(i==0)
 				{
 					wMb_control_data_C=DATA_QUE_WR_C[start_point_data_C];
					//flag_RS485_data_new_C=1;
 					if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
 					k=1;
 				}
 				else {		k=0;	i=i-1;	}	// Notice !!! it need to be -1

 				if(NumData>k)
 				{
 					for(j=0;(k+j)<NumData;j++)
 					{
 	                    if((i+j)<= MB_SET_I_Chg3_GAIN) {
 	                        switch( i+j )
 	                        {
 	                          case MB_SET_IR_OFFSET          :   UpdateBuff_C( SET_IR_OFFSET     );                 break;
 	                          case MB_SET_VBAT_OFFSET        :   UpdateBuff_C( SET_Vbat_OFFSET   );                 break;
 	                          case MB_SET_5V_OFFSET          :   UpdateBuff_C( SET_5V_OFFSET     );                 break;
 	                          case MB_SET_3_3V_OFFSET        :   UpdateBuff_C( SET_3_3V_OFFSET   );                 break;
 	                          case MB_SET_1_8V_OFFSET        :   UpdateBuff_C( SET_1_8V_OFFSET   );                 break;
 	                          case MB_SET_6V_OFFSET          :   UpdateBuff_C( SET_6V_OFFSET     );                 break;
 	                          case MB_SET_I_Chg1_OFFSET      :   UpdateBuff_C( SET_Ichg1_OFFSET  );                 break;
 	                          case MB_SET_IDC_OFFSET         :   UpdateBuff_C( SET_IDC_OFFSET    );                 break;
 	                          case MB_SET_I_Chg2_OFFSET      :   UpdateBuff_C( SET_Ichg2_OFFSET  );                 break;
 	                          case MB_SET_2_5V_OFFSET        :   UpdateBuff_C( SET_2_5V_OFFSET   );                 break;
 	                          case MB_SET_1_65V_OFFSET       :   UpdateBuff_C( SET_1_65V_OFFSET  );                 break;
 	                          case MB_SET_I_Chg3_OFFSET      :   UpdateBuff_C( SET_Ichg3_OFFSET  );                 break;
 	                          case MB_SET_IR_GAIN            :   UpdateBuff_C( SET_IR_GAIN       );                 break;
 	                          case MB_SET_VBAT_GAIN          :   UpdateBuff_C( SET_Vbat_GAIN     );                 break;
 	                          case MB_SET_5V_GAIN            :   UpdateBuff_C( SET_5V_GAIN       );                 break;
 	                          case MB_SET_3_3V_GAIN          :   UpdateBuff_C( SET_3_3V_GAIN     );                 break;
 	                          case MB_SET_1_8V_GAIN          :   UpdateBuff_C( SET_1_8V_GAIN     );                 break;
 	                          case MB_SET_6V_GAIN            :   UpdateBuff_C( SET_6V_GAIN       );                 break;
 	                          case MB_SET_I_Chg1_GAIN        :   UpdateBuff_C( SET_Ichg1_GAIN    );                 break;
 	                          case MB_SET_IDC_GAIN           :   UpdateBuff_C( SET_IDC_GAIN      );                 break;
 	                          case MB_SET_I_Chg2_GAIN        :   UpdateBuff_C( SET_Ichg2_GAIN    );                 break;
 	                          case MB_SET_2_5V_GAIN          :   UpdateBuff_C( SET_2_5V_GAIN     );                 break;
 	                          case MB_SET_1_65V_GAIN         :   UpdateBuff_C( SET_1_65V_GAIN    );                 break;
 	                          case MB_SET_I_Chg3_GAIN        :   UpdateBuff_C( SET_Ichg3_GAIN    );                 break;

 	                            default :   break;
 	                        }
 	                        if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
 	                    }
 						if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
 					}
 				}
 				i=0;	NumData = NUM_QUE_RD_C[start_point_C];
 				if( ID_QUE_RD_C[start_point_C] <= MB_DATA_JIG_VERSION )
 				{
 					switch(ID_QUE_RD_C[start_point_C])
 					{
                     //--- Set Control value feedback : P.S-->Customer(Read)     // 59999
                     case    MB_DATA_STATUS:        wModData_C[i++]= GetJigStatus();             if(i>=NumData)  break;
                     case    MB_DATA_WARNNIG:       wModData_C[i++]= 0;                          if(i>=NumData)  break;
                     case    MB_DATA_FAULT:         wModData_C[i++]= GetJigFault();              if(i>=NumData)  break;
         // Target 1
                     case    MB_DATA_TARGET1_STATUS :    wModData_C[i++]= SmileKey[0].StautsInfo;        if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_FAULT :     wModData_C[i++]= SmileKey[0].Error;             if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_POWER :     wModData_C[i++]= SmileKey[0].Po;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_VOLTAGE :   wModData_C[i++]= SmileKey[0].Vo;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_IDC :       wModData_C[i++]= SmileKey[0].Idc;               if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_IR :        wModData_C[i++]= SmileKey[0].Ir;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_Vbat :      wModData_C[i++]= SmileKey[0].Vbat;              if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_IChg :      wModData_C[i++]= SmileKey[0].I_Charge;          if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_PHASE :     wModData_C[i++]= SmileKey[0].Phase;             if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_VERSION :   wModData_C[i++]= SmileKey[0].Version;           if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_OTP1 :      wModData_C[i++]= SmileKey[0].Temperature1;      if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_OTP2 :      wModData_C[i++]= SmileKey[0].Temperature2;      if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_ID_LSW :    wModData_C[i++]= SmileKey[0].UniqueID.Word.LSW; if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_ID_MSW :    wModData_C[i++]= SmileKey[0].UniqueID.Word.MSW; if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_FREQ :      wModData_C[i++]= SmileKey[0].Freq;              if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_RESERVED2 : wModData_C[i++]= 777;                           if(i>=NumData)  break;
                     case    MB_DATA_TARGET1_RESERVED3 : wModData_C[i++]= 888;                           if(i>=NumData)  break;

         // Auto Cali Report
                     case    MB_DATA_REPORT_IR_OFFSET :  wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IR_OFFSET];    if(i>=NumData)  break;
                     case    MB_DATA_REPORT_IR_GAIN :    wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IR_GAIN];      if(i>=NumData)  break;
                     case    MB_DATA_REPORT_IDC_OFFSET : wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IO_OFFSET];    if(i>=NumData)  break;
                     case    MB_DATA_REPORT_IDC_GAIN :   wModData_C[i++]= SmileKey[0].SetValue[SET_SK_IO_GAIN];      if(i>=NumData)  break;
                     case    MB_DATA_REPORT_Vbat_GAIN :  wModData_C[i++]= SmileKey[0].SetValue[SET_SK_Vbat_GAIN];    if(i>=NumData)  break;
                     case    MB_DATA_REPORT_IChg_OFFSET :wModData_C[i++]= SmileKey[0].SetValue[SET_SK_ICHG_OFFSET];  if(i>=NumData)  break;
                     case    MB_DATA_REPORT_IChg_GAIN :  wModData_C[i++]= SmileKey[0].SetValue[SET_SK_ICHG_GAIN];    if(i>=NumData)  break;

         // Target 2
                     case    MB_DATA_TARGET2_STATUS :    wModData_C[i++]= SmileKey[1].StautsInfo;        if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_FAULT :     wModData_C[i++]= SmileKey[1].Error;             if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_POWER :     wModData_C[i++]= SmileKey[1].Po;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_VOLTAGE :   wModData_C[i++]= SmileKey[1].Vo;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_IDC :       wModData_C[i++]= SmileKey[1].Idc;               if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_IR :        wModData_C[i++]= SmileKey[1].Ir;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_Vbat :      wModData_C[i++]= SmileKey[1].Vbat;              if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_IChg :      wModData_C[i++]= SmileKey[1].I_Charge;          if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_PHASE :     wModData_C[i++]= SmileKey[1].Phase;             if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_VERSION :   wModData_C[i++]= SmileKey[1].Version;           if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_OTP1 :      wModData_C[i++]= SmileKey[1].Temperature1;      if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_OTP2 :      wModData_C[i++]= SmileKey[1].Temperature2;      if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_ID_LSW :    wModData_C[i++]= SmileKey[1].UniqueID.Word.LSW; if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_ID_MSW :    wModData_C[i++]= SmileKey[1].UniqueID.Word.MSW; if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_FREQ :      wModData_C[i++]= SmileKey[1].Freq;              if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_RESERVED2 : wModData_C[i++]= 777;                           if(i>=NumData)  break;
                     case    MB_DATA_TARGET2_RESERVED3 : wModData_C[i++]= 888;                           if(i>=NumData)  break;
         // Target 3
                     case    MB_DATA_TARGET3_STATUS :    wModData_C[i++]= SmileKey[2].StautsInfo;        if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_FAULT :     wModData_C[i++]= SmileKey[2].Error;             if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_POWER :     wModData_C[i++]= SmileKey[2].Po;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_VOLTAGE :   wModData_C[i++]= SmileKey[2].Vo;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_IDC :       wModData_C[i++]= SmileKey[2].Idc;               if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_IR :        wModData_C[i++]= SmileKey[2].Ir;                if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_Vbat :      wModData_C[i++]= SmileKey[2].Vbat;              if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_IChg :      wModData_C[i++]= SmileKey[2].I_Charge;          if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_PHASE :     wModData_C[i++]= SmileKey[2].Phase;             if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_VERSION :   wModData_C[i++]= SmileKey[2].Version;           if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_OTP1 :      wModData_C[i++]= SmileKey[2].Temperature1;      if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_OTP2 :      wModData_C[i++]= SmileKey[2].Temperature2;      if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_ID_LSW :    wModData_C[i++]= SmileKey[2].UniqueID.Word.LSW; if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_ID_MSW :    wModData_C[i++]= SmileKey[2].UniqueID.Word.MSW; if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_FREQ :      wModData_C[i++]= SmileKey[2].Freq;              if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_RESERVED2 : wModData_C[i++]= 777;                           if(i>=NumData)  break;
                     case    MB_DATA_TARGET3_RESERVED3 : wModData_C[i++]= 888;                           if(i>=NumData)  break;
         // JIG AD
                     case    MB_DATA_JIG_IR :            wModData_C[i++]= ADC_Avg[AD_IR];                if(i>=NumData)  break;
                     case    MB_DATA_JIG_V_BAT :         wModData_C[i++]= ADC_Avg[AD_VBAT];              if(i>=NumData)  break;
                     case    MB_DATA_JIG_5V :            wModData_C[i++]= ADC_Avg[AD_P5V];               if(i>=NumData)  break;
                     case    MB_DATA_JIG_3_3V :          wModData_C[i++]= ADC_Avg[AD_P3_3V];             if(i>=NumData)  break;
                     case    MB_DATA_JIG_1_8V :          wModData_C[i++]= ADC_Avg[AD_P1_8V];             if(i>=NumData)  break;
                     case    MB_DATA_JIG_6V :            wModData_C[i++]= ADC_Avg[AD_P6V];               if(i>=NumData)  break;
                     case    MB_DATA_JIG_IDC :           wModData_C[i++]= ADC_Avg[AD_IDC];               if(i>=NumData)  break;
                     case    MB_DATA_JIG_I_Chg1 :        wModData_C[i++]= ADC_Avg[AD_I_Chg1];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_I_Chg2 :        wModData_C[i++]= ADC_Avg[AD_I_Chg2];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_I_Chg3 :        wModData_C[i++]= ADC_Avg[AD_I_Chg3];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_2_5V :          wModData_C[i++]= ADC_Avg[AD_P2_5V];             if(i>=NumData)  break;
                     case    MB_DATA_JIG_1_65V :         wModData_C[i++]= ADC_Avg[AD_P1_65V];            if(i>=NumData)  break;
         // JIG Setting value
                     case    MB_DATA_JIG_SET_IR_OFFSET :           wModData_C[i++]= C12.BUFF[SET_IR_OFFSET];               if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Vbat_OFFSET :         wModData_C[i++]= C12.BUFF[SET_Vbat_OFFSET ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_5V_OFFSET   :         wModData_C[i++]= C12.BUFF[SET_5V_OFFSET   ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_3_3V_OFFSET :         wModData_C[i++]= C12.BUFF[SET_3_3V_OFFSET ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_1_8V_OFFSET :         wModData_C[i++]= C12.BUFF[SET_1_8V_OFFSET ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_6V_OFFSET   :         wModData_C[i++]= C12.BUFF[SET_6V_OFFSET   ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Ic1_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_Ichg1_OFFSET];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_IDC_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_IDC_OFFSET  ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Ic2_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_Ichg2_OFFSET];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_2_5V_OFFSET :         wModData_C[i++]= C12.BUFF[SET_2_5V_OFFSET ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_1_65V_OFFSET :        wModData_C[i++]= C12.BUFF[SET_1_65V_OFFSET];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Ic3_OFFSET  :         wModData_C[i++]= C12.BUFF[SET_Ichg3_OFFSET];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_IR_GAIN     :         wModData_C[i++]= C12.BUFF[SET_IR_GAIN     ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Vbat_GAIN   :         wModData_C[i++]= C12.BUFF[SET_Vbat_GAIN   ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_5V_GAIN     :         wModData_C[i++]= C12.BUFF[SET_5V_GAIN     ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_3_3V_GAIN   :         wModData_C[i++]= C12.BUFF[SET_3_3V_GAIN   ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_1_8V_GAIN   :         wModData_C[i++]= C12.BUFF[SET_1_8V_GAIN   ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_6V_GAIN     :         wModData_C[i++]= C12.BUFF[SET_6V_GAIN     ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Ic1_GAIN    :         wModData_C[i++]= C12.BUFF[SET_Ichg1_GAIN  ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_IDC_GAIN    :         wModData_C[i++]= C12.BUFF[SET_IDC_GAIN    ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Ic2_GAIN    :         wModData_C[i++]= C12.BUFF[SET_Ichg2_GAIN  ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_2_5V_GAIN   :         wModData_C[i++]= C12.BUFF[SET_2_5V_GAIN   ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_1_65V_GAIN  :         wModData_C[i++]= C12.BUFF[SET_1_65V_GAIN  ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_SET_Ic3_GAIN    :         wModData_C[i++]= C12.BUFF[SET_Ichg3_GAIN  ];            if(i>=NumData)  break;
                     case    MB_DATA_JIG_VERSION         :         wModData_C[i++]= C12.BUFF[SET_VERSION     ];            if(i>=NumData)  break;
                    }

 					if(i==NumData) {MakePkt2Fc17_C(NumData, wModData_C); flag_RS485_receive_C=1;	}
 					else {	MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x04);	}	// error - Invalid RD data number Range

 					if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
 				}
 				else {	MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x03); }	// error - Invalid RD data address Range// error - ID range out
 			}
 			else
 			{	// error - ID range out
 				MakePkt2ERR_C(FUNC_QUE_C[start_point_C]|0x80, 0x02);		// error - Invalid WR data address Range
 				if(++start_point_C>=MAX_QUE_MB) start_point_C=0;
 				for(i=0;i<NumData;i++)
 				{
 					if(++start_point_data_C>=MAX_QUE_MB) start_point_data_C=0;
 				}
 			}
 		}
 		else
 		{	// there are no message left, so if error, reply error code response
 			if(err_flag_C && flag_rcv_frame_end_C)
 			{
 				MakePkt2ERR_C(err_ID_C, 0x01);			// error - Invalid Function
 				err_flag_C = flag_rcv_frame_end_C = 0;
 			}
 		}
	}
 	/* Transmit Data */
 	if(bCntRespDelay_C>TD_RESPONSE)	// wait until response delay 3.5 charactor times
	{
	 	if (transmit_flag_C==0 && (transmit_start_C != transmit_end_C))
	 	{
	 	    TXC_ENABLE;
	 		transmit_flag_C = 1;
	 		ScicRegs.SCIFFTX.bit.TXFFIENA=0;
	 		ScicRegs.SCITXBUF = TRANSMIT_QUE_C[transmit_start_C];
	 	}
	}
} 

void UpdateBuff_C( Uint16 index )
{
    Uint16 wTmp;
    wTmp=ChangeValue_485_C(index);
    if(C12.BUFF[index]!=wTmp)
    {
        C12.BUFF[index]=wTmp;
        if(index < 32) flag_set_save1|=(1L<<(index));
        else           flag_set_save2|=(1L<<((index)-32));
    }
}

int MaskMBData_C(Uint16 addr)
{	
/*
    if( C12.BUFF[SET_ONOFF] != INTERNAL )
    {
        if( addr < SET_ONOFF )																			    return 1;
    //	else if((addr>=SET_FREQUENCY)&&(addr<=SET_ONOFF))													return 0;
    //	if(addr==SET_LOCAL_ADDRESS)																			return 0;
    //	else if(addr<=SET_TIMER_RESET) 																		return 1;
        else 																								return 0;
    }
    else                                                                                                    return 0;
*/
    return 1;
} 

void SciCAutoBusReset ( void )
{
    if(ScicRegs.SCIRXST.all & 0x80)
    {
        ScicRegs.SCICTL1.all =0x0003;     // Relinquish SCI from Reset
        DELAY_US(1);
        ScicRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
    }
}
