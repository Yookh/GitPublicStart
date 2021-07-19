/*******************************************************************
 *
 *	  main.c : This file implements the Project - Dual Frequency Induction Heating-.
 *
 *    @author : Kwang Hyun Yoo.(yoogh@pstek.co.kr)
 *
 *    @Version : V2.01 - coding start.
 *
 *
 *******************************************************************/

/** include files **/
#include "F28x_Project.h"
#include "define.h"
#include "eeprom.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "F2837xD_Ipc_drivers.h"
#include "SET_PARAM.h"

#include "DUAL_PARAM.h"
#include "Main_Func.h"
#include "DualCore_Select.h"
#include "Src-EPWM/EpwmRegs_Defs.h"		// 최악임. 시간이 없어서 불러 넣기 시작함.
#include "Src-Capture/ECap_Config.h"     // 최악임. 시간이 없어서 불러 넣기 시작함.

#include <stdio.h>
#include <time.h>

/** Main Data **/
C1_2    C12;
#pragma DATA_SECTION(C12,"SHARERAMGS2");
C2_1    C21;
#pragma DATA_SECTION(C21,"SHARERAMGS4");

Uint16  count_100msec, count_10msec, count_periodic;
Uint16  TIMER_SEC, TIMER_MIN, TIMER_HOUR;

Uint16	flag_LCD_alive;
Uint16  A_upload_flag, A_upload_count;
Uint16  B_upload_flag, B_upload_count;
Uint16  D_upload_flag, D_upload_count;
Uint16  cnt_waitsaveend, model, My_Address;
Uint16	system_status, warning_status;
int     reset_flag;

Uint16 	adc_count;
int16   ADC_Result[ADC_NUMBER];
int16	ADC_Avg[ADC_NUMBER], DISP_Avg[ADC_NUMBER];
long    ADC_Buf[ADC_NUMBER];

long	flag_set_save1, flag_set_save2;
long	flag_time_save;
long	Old_fault_status=0;
Uint32 	present_status;

Uint16	dlog_tx_index, flog_tx_index, dlog_index, flog_index, block_addr;
Uint16 	dlog_tx_flag, stop_comm, flog_tx_flag;

//== IPC : shared memory config
Uint16 BootFlag=0, bootcnt, delay_cnt;

Uint16 reset_delay_cnt;

Uint16 TestID_A, TestData_A, TestTx_A;
Uint16 TestID_B, TestData_B, TestTx_B;
Uint16 TestID_D, TestData_D, TestTx_D;

void main(void)
{
	BootFlag = 0;
	ResetService();
	BootFlag = 1;

	for(;;)
	{
	    RS485_Comm_check_C();
	    RS232_Comm_checkA();
	    RS232_Comm_checkB();
	    RS232_Comm_checkD();
	    Auto_save();

		//=====   periodic routine  ============ //
		if( Period_CpuTimer() )					 // Cpu Timer =  default : 1800 Hz	(fast routine)
		{
		    SCIC_CHECK();
		}

		if( Period_10ms() )
		{
			count_10msec++;
            count_periodic++;
		}

        if ( Period_50ms() )
        {
            ElectricalRequirementTest();
            AgingTest();
        }//end of period_50ms

		if( Period_100ms() )
		{
		    count_100msec++;    bootcnt++;
		    AutoConnectCheck();


            if(cnt_waitsaveend) cnt_waitsaveend--;

            if(TestTx_A == 1)
            {
                TestTx_A = 0;
                MakePktA(0x80 + TestID_A, TestData_A);
            }
            if(TestTx_B == 1)
            {
                TestTx_B = 0;
                MakePktB(TestID_B, TestData_B);
            }
            if(TestTx_D == 1)
            {
                TestTx_D = 0;
                MakePktD(TestID_D, TestData_D);
            }

		}	  //end of period_100ms

		if( Period_1000ms() )
		{
            Check_Model();
		}//end of period_1000ms

	}		  //end of for(;;)
}			  //end of main

#pragma CODE_SECTION(epwm1_timer_isr, "ramfuncs");
interrupt void epwm1_timer_isr(void)                // 160Khz
{
    AdcRead();

    if( adc_count >= 800)                             // 0.2Khz
    {
        AdcAverage();
    }
    EPwm1Regs.ETCLR.bit.INT = 1;                // Clear INT flag for EPWM1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;     // Acknowledge this interrupt to receive more interrupts from group 3
}
#pragma CODE_SECTION(AdcA_isr, "ramfuncs");
__interrupt void AdcA_isr(void)
{

    AdcaRegs.ADCINTFLGCLR.all = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Acknowledge this interrupt to receive more interrupts from group 10
}

#pragma CODE_SECTION(AdcRead, "ramfuncs");
void AdcRead(void)
{

    ADC_Result[AD_IR]       = ADC_CH(b,0);
    ADC_Result[AD_VBAT]     = ADC_CH(b,1);
    ADC_Result[AD_P5V]      = ADC_CH(b,2);
    ADC_Result[AD_P3_3V]    = ADC_CH(b,3);
    ADC_Result[AD_P1_8V]    = ADC_CH(c,2);
    ADC_Result[AD_P6V]      = ADC_CH(c,3);
    ADC_Result[AD_I_Chg1]   = ADC_CH(d,1);
    ADC_Result[AD_IDC]      = ADC_CH(d,2);
    ADC_Result[AD_I_Chg2]   = ADC_CH(d,3);
    ADC_Result[AD_P2_5V]    = ADC_CH(d,4);
    ADC_Result[AD_P1_65V]   = ADC_CH(c,4);
    ADC_Result[AD_I_Chg3]   = ADC_CH(d,0);
/*
    ADC_Result[AD_IR]      += C12.BUFF[SET_IR_OFFSET];
    ADC_Result[AD_VBAT]    += C12.BUFF[SET_Vbat_OFFSET];
    ADC_Result[AD_P5V]     += C12.BUFF[SET_5V_OFFSET];
    ADC_Result[AD_P3_3V]   += C12.BUFF[SET_3_3V_OFFSET];
    ADC_Result[AD_P1_8V]   += C12.BUFF[SET_1_8V_OFFSET];
    ADC_Result[AD_P6V]     += C12.BUFF[SET_6V_OFFSET];
    ADC_Result[AD_I_Chg1]  += C12.BUFF[SET_Ichg1_OFFSET];
    ADC_Result[AD_IDC]     += C12.BUFF[SET_IDC_OFFSET];
    ADC_Result[AD_I_Chg2]  += C12.BUFF[SET_Ichg2_OFFSET];
    ADC_Result[AD_P2_5V]   += C12.BUFF[SET_2_5V_OFFSET];
    ADC_Result[AD_P1_65V]  += C12.BUFF[SET_1_65V_OFFSET];
    ADC_Result[AD_I_Chg3]  += C12.BUFF[SET_Ichg3_OFFSET];
*/
    ADC_Buf[AD_IR]         += ADC_Result[AD_IR];
    ADC_Buf[AD_VBAT]       += ADC_Result[AD_VBAT];
    ADC_Buf[AD_P5V]        += ADC_Result[AD_P5V];
    ADC_Buf[AD_P3_3V]      += ADC_Result[AD_P3_3V];
    ADC_Buf[AD_P1_8V]      += ADC_Result[AD_P1_8V];
    ADC_Buf[AD_P6V]        += ADC_Result[AD_P6V];
    ADC_Buf[AD_I_Chg1]     += ADC_Result[AD_I_Chg1];
    ADC_Buf[AD_IDC]        += ADC_Result[AD_IDC];
    ADC_Buf[AD_I_Chg2]     += ADC_Result[AD_I_Chg2];
    ADC_Buf[AD_P2_5V]      += ADC_Result[AD_P2_5V];
    ADC_Buf[AD_P1_65V]     += ADC_Result[AD_P1_65V];
    ADC_Buf[AD_I_Chg3]     += ADC_Result[AD_I_Chg3];

    adc_count++;
}

#pragma CODE_SECTION(AdcAverage, "ramfuncs");
void AdcAverage(void)
{
    int i;
    int Adc_Gain_Cali[ADC_NUMBER];


    for(i=0; i< ADC_NUMBER; i++)
    {
        Adc_Gain_Cali[i] = ADC_GAIN[i] + C12.BUFF[i+12];

        ADC_Avg[i] = ADC_Buf[i] / adc_count;
        ADC_Avg[i] += C12.BUFF[i];
        ADC_Buf[i] = 0;
    }

    ADC_Avg[AD_IDC]     -= ADC_Avg[AD_P1_65V];
    ADC_Avg[AD_I_Chg1]  -= ADC_Avg[AD_P2_5V];
    ADC_Avg[AD_I_Chg2]  -= ADC_Avg[AD_P2_5V];
    ADC_Avg[AD_I_Chg3]  -= ADC_Avg[AD_P2_5V];

    for(i=0; i< ADC_NUMBER; i++)
    {
        ADC_Avg[i] = ((long)ADC_Avg[i] * Adc_Gain_Cali[i]) >> 12;
    }
    adc_count = 0;
}


void RUN(void)
{
	C12.run_flag = 1;
	MakePktB(ID_CMD_RUN, 0);
}

void STOP(void)
{
	MakePktB(ID_CMD_STOP,0xffff);
	system_status &= ~STATUS_RUNNING;

	C12.run_flag = 0;
}

void  Auto_save(void)
{
    int i;

    if((C12.run_flag==STOP0)&&(cnt_waitsaveend==0))
    {
        if(flag_set_save1) {
            for(i=0;i<32;i++) { if(flag_set_save1&(1L<<i)) break; }
            if(i2cWriteData(0x50, i, C12.BUFF[i])) { warning_status|=WARNING_EEP_WR_ERR; MakePktB(ID_WARNING,warning_status); }
            cnt_waitsaveend = (SAMPL_FREQ/200); // wait 5ms delay for serial eeprom write
            flag_set_save1 &= ~(1L<<i);
        }
        else if(flag_set_save2) {
            for(i=0;i<32;i++) { if(flag_set_save2&(1L<<i)) break; }
            if(i2cWriteData(0x50, i+32, C12.BUFF[i+32])) { warning_status|=WARNING_EEP_WR_ERR; MakePktB(ID_WARNING,warning_status); }
            cnt_waitsaveend = (SAMPL_FREQ/200); // wait 5ms delay for serial eeprom write
            flag_set_save2 &= ~(1L<<i);
        }
    }
}

void EEP_RW(void)
{
    int i;

    if(i2cReadData(0x50, EEP_END_ADDR)!=0x57)   // if: Loaded last address data from EEPROM is NOT 0x57
    {
        if(i2cWriteData(0x50, EEP_END_ADDR, 0x57)) warning_status|=WARNING_EEP_WR_ERR;

        for(i=0;i<SET_NUM;i++)  // EEPROM data is invalid, initialize registers & EEPROM with default data from ROM
        {
            C12.BUFF[i]=SET[model][i][DFT];
            if     (i<32)   flag_set_save1|=(1L<<i);
            else if(i<64)   flag_set_save2|=(1L<<(i-32));
        }
    }
    else
    {   // else: Load saved data from EEPROM
        for(i=0;i<SET_NUM;i++) C12.BUFF[i]=i2cReadData(0x50,i);
    }
}


void Check_Model(void)      //not used
{
    My_Address = 0 ;

    if( GpioDataRegs.GPADAT.bit.GPIO18 == 0 )  My_Address |=BIT0;
    if( GpioDataRegs.GPADAT.bit.GPIO19 == 0 )  My_Address |=BIT1;
    if( GpioDataRegs.GPADAT.bit.GPIO20 == 0 )  My_Address |=BIT2;
    if( GpioDataRegs.GPADAT.bit.GPIO21 == 0 )  My_Address |=BIT3;

    My_Address += 1;
    model=0;
}

void ResetService(void)
{
	DINT;
	C12.reset_flag = 1;
	Sys_init28377();

	Check_Model();
	SCIA_INIT_VAL();
	SCIB_INIT_VAL();
	SCID_INIT_VAL();
	INIT_485_VAR_C();
	InitializeCAN();

    GPIO_SetupPinMux(2, GPIO_MUX_CPU1, 1);
	GPIO_SetupPinMux(4, GPIO_MUX_CPU1, 1);

    GPIO_SetupPinMux(12, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(12, GPIO_OUTPUT, GPIO_PUSHPULL);

////////////////////////////////// INITIALIZE	COUNT	///////////////////////////////////////////////
	reset_flag = 0; 	    adc_count = 0;   	    B_upload_count = 0;
	warning_status = 0;     system_status = 0;	    present_status = 0;
	count_100msec=0;	    flag_LCD_alive = 0;
	flag_set_save1 = 0;	    flag_set_save2 = 0;	    flag_time_save = 0;
	cnt_waitsaveend = 0;    bootcnt = 0;
	system_status = 0;
	Old_fault_status = 0;   C12.run_flag = ST_STOP;   C12.fault_status = 0;
    reset_delay_cnt=0;

///////////////////////////////////////////////////////////////////////////////////////////////////////
	DELAY_US(100000);	// 1000
	STOP();

	InitTargetValue();

	EEP_RW();

	C12.BUFF[SET_MODEL] = SET[model][SET_MODEL][DFT];
	C12.BUFF[SET_VERSION] = SET[model][SET_VERSION][DFT];

//	Init_SCPI();

	EINT;
}
