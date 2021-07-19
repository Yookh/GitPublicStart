/*
 * ECap_Config.c
 *
 *  Created on: 2016. 9. 9.
 *      Author: Yoo Kwang Hyun
 */
#include "F28x_Project.h"
#include "ECap_Config.h"
#include "..\DualCore_Select.h"

void InitECapture(void);
void InitECapGPIO(void);
void ECap1Cfg(void);
void ECap2Cfg(void);
void ECap3Cfg(void);
void ECap4Cfg(void);
void ECap5Cfg(void);
void ECap6Cfg(void);

#define CAPTURE         0
#define APWM            1

// Configuration MODE
#define ECAP1_MODE      CAPTURE
#define ECAP2_MODE      CAPTURE
#define ECAP3_MODE      CAPTURE
#define ECAP4_MODE      CAPTURE
#define ECAP5_MODE      APWM
#define ECAP6_MODE      APWM

//---------------------------------------------------------------------------
// InitECap:
//---------------------------------------------------------------------------
void InitECapture(void)
{

#if(CPU1)
    InitECapGPIO();
#endif
EALLOW;
    ECap1Cfg();
    ECap2Cfg();
//  ECap3Cfg();
//  ECap4Cfg();
//  ECap5Cfg();
//  ECap6Cfg();
EDIS;
}

// This function initializes the eCAP(s) to a known state.
void InitECapGPIO(void)
{
    //Parameter : Pin number
    InitECap1Gpio(48);
//    InitECap2Gpio(64);
//  InitECap3Gpio(18);
//  InitECap4Gpio(7);
//  InitECap5Gpio(87);
//  InitECap6Gpio(86);


    // Initialize eCAP1/2/3/4/5/6
//  InitAPwm1Gpio();
    //tbd...

}

void ECap1Cfg(void)
{
#if(ECAP1_MODE)
       ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
       ECap1Regs.ECCTL1.bit.CAPLDEN = EC_DISABLE; // Disable CAP1-CAP4 register loads
       ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

       // Setup APWM mode on CAP1, set period and compare registers
       ECap1Regs.ECCTL1.bit.PRESCALE = 0;       // Event Prescaler(not clock) Divided by 1
       ECap1Regs.ECCTL2.bit.CAP_APWM = 1;       // Enable APWM mode
       ECap1Regs.ECCTL2.bit.APWMPOL = 0;        // 0: Active High, Duty is high time    1: Active Low, Duty is low time
       ECap1Regs.CAP3 = 10000000L;              // Set Period value as 10Hz
       ECap1Regs.CAP4 = 200;                    // Set Compare value as 1usec
       ECap1Regs.ECCLR.all = 0x0FF;             // Clear pending interrupts
       ECap1Regs.ECCTL2.bit.SYNCI_EN = 0;       // 1:ENABLE SYNC IN, 0 : DISABLE SYNC IN
       ECap1Regs.ECCTL2.bit.SYNCO_SEL = 1;      // 00:Bypass, 01:counter=period, 10,11:disable
       ECap1Regs.ECEINT.bit.CTR_EQ_PRD = 1;     // enable Compare Equal Int

       ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;      // TSCNT free running. start Counter
#else
       // ECAP module 1 config
       ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags

       ECap1Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
       ECap1Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;

       ECap1Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
       ECap1Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;

       ECap1Regs.ECCTL1.bit.CAP1POL = EC_RISING;
       ECap1Regs.ECCTL1.bit.CAP2POL = EC_FALLING;
       ECap1Regs.ECCTL1.bit.CAP3POL = EC_FALLING;
       ECap1Regs.ECCTL1.bit.CAP4POL = EC_FALLING;

       ECap1Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;
       ECap1Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
       ECap1Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
       ECap1Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;

       ECap1Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;

       ECap1Regs.ECCTL2.bit.STOP_WRAP = EC_STOP_EVT2;

       ECap1Regs.ECEINT.bit.CEVT1 = EC_INT_EN;
//     ECap1Regs.ECEINT.bit.CEVT2 = EC_INT_EN;
//     ECap1Regs.ECEINT.bit.CEVT3 = EC_INT_EN;
//     ECap1Regs.ECEINT.bit.CEVT4 = EC_INT_EN;

       ECap1Regs.ECCLR.bit.CEVT1 = 1;
       ECap1Regs.ECCLR.bit.CEVT2 = 1;
       ECap1Regs.ECCLR.bit.CEVT3 = 1;
       ECap1Regs.ECCLR.bit.CEVT4 = 1;
       ECap1Regs.ECCLR.bit.INT = 1;


       ECap1Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
       ECap1Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

#endif
}


void ECap2Cfg(void)
{
#if(ECAP2_MODE)
       ECap2Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap2Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
       ECap2Regs.ECCTL1.bit.CAPLDEN = EC_DISABLE; // Disable CAP1-CAP4 register loads
       ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

       // Setup APWM mode on CAP1, set period and compare registers
       ECap2Regs.ECCTL1.bit.PRESCALE = 0;       // Event Prescaler(not clock) Divided by 1
       ECap2Regs.ECCTL2.bit.CAP_APWM = 1;       // Enable APWM mode
       ECap2Regs.ECCTL2.bit.APWMPOL = 0;        // 0: Active High, Duty is high time    1: Active Low, Duty is low time
       ECap2Regs.CAP3 = 10000000L;              // Set Period value as 10Hz
       ECap2Regs.CAP4 = 200;                    // Set Compare value as 1usec
       ECap2Regs.ECCLR.all = 0x0FF;             // Clear pending interrupts
       ECap2Regs.ECCTL2.bit.SYNCI_EN = 0;       // 1:ENABLE SYNC IN, 0 : DISABLE SYNC IN
       ECap2Regs.ECCTL2.bit.SYNCO_SEL = 1;      // 00:Bypass, 01:counter=period, 10,11:disable
       ECap2Regs.ECEINT.bit.CTR_EQ_PRD = 1;     // enable Compare Equal Int

       ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;      // TSCNT free running. start Counter
#else
        // ECAP module 1 config
       ECap2Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap2Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags

       ECap2Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
       ECap2Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;

       ECap2Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
       ECap2Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;

       ECap2Regs.ECCTL1.bit.CAP1POL = EC_FALLING;
       ECap2Regs.ECCTL1.bit.CAP2POL = EC_FALLING;
       ECap2Regs.ECCTL1.bit.CAP3POL = EC_FALLING;
       ECap2Regs.ECCTL1.bit.CAP4POL = EC_FALLING;

       ECap2Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
       ECap2Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
       ECap2Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
       ECap2Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;

       ECap2Regs.ECCTL2.bit.CONT_ONESHT = EC_ONESHOT;

       ECap2Regs.ECCTL2.bit.STOP_WRAP = EC_STOP_EVT1;

       ECap2Regs.ECEINT.bit.CEVT1 = EC_INT_EN;
 //    ECap2Regs.ECEINT.bit.CEVT2 = EC_INT_EN;

       ECap2Regs.ECCLR.bit.CEVT1 = 1;
       ECap2Regs.ECCLR.bit.CEVT2 = 1;
       ECap2Regs.ECCLR.bit.CEVT3 = 1;
       ECap2Regs.ECCLR.bit.CEVT4 = 1;
       ECap2Regs.ECCLR.bit.INT = 1;


       ECap2Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
       ECap2Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

#endif
}

void ECap3Cfg(void)
{
#if(ECAP3_MODE)
       ECap3Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap3Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
       ECap3Regs.ECCTL1.bit.CAPLDEN = EC_DISABLE; // Disable CAP1-CAP4 register loads
       ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

       // Setup APWM mode on CAP1, set period and compare registers
       ECap3Regs.ECCTL1.bit.PRESCALE = 0;       // Event Prescaler(not clock) Divided by 1
       ECap3Regs.ECCTL2.bit.CAP_APWM = 1;       // Enable APWM mode
       ECap3Regs.ECCTL2.bit.APWMPOL = 0;        // 0: Active High, Duty is high time    1: Active Low, Duty is low time
       ECap3Regs.CAP3 = 10000000L;              // Set Period value as 10Hz
       ECap3Regs.CAP4 = 200;                    // Set Compare value as 1usec
       ECap3Regs.ECCLR.all = 0x0FF;             // Clear pending interrupts
       ECap3Regs.ECCTL2.bit.SYNCI_EN = 0;       // 1:ENABLE SYNC IN, 0 : DISABLE SYNC IN
       ECap3Regs.ECCTL2.bit.SYNCO_SEL = 1;      // 00:Bypass, 01:counter=period, 10,11:disable
       ECap3Regs.ECEINT.bit.CTR_EQ_PRD = 1;     // enable Compare Equal Int

       ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;      // TSCNT free running. start Counter
#else
        // ECAP module 1 config

        ECap3Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
        ECap3Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;

        ECap3Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
        ECap3Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;

        ECap3Regs.ECCTL1.bit.CAP1POL = EC_RISING;
        ECap3Regs.ECCTL1.bit.CAP2POL = EC_FALLING;
        ECap3Regs.ECCTL1.bit.CAP3POL = EC_RISING;
        ECap3Regs.ECCTL1.bit.CAP4POL = EC_RISING;

        ECap3Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;
        ECap3Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
        ECap3Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
        ECap3Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;

        ECap3Regs.ECCTL2.bit.CONT_ONESHT = EC_ONESHOT;

        ECap3Regs.ECCTL2.bit.STOP_WRAP = EC_STOP_EVT2;

        ECap3Regs.ECEINT.bit.CEVT1 = EC_INT_EN;
        ECap3Regs.ECEINT.bit.CEVT2 = EC_INT_EN;
//      ECap3Regs.ECEINT.bit.CEVT3 = EC_INT_EN;
//      ECap3Regs.ECEINT.bit.CEVT4 = EC_INT_EN;

        ECap3Regs.ECCLR.bit.CEVT1 = 1;
        ECap3Regs.ECCLR.bit.CEVT2 = 1;
        ECap3Regs.ECCLR.bit.CEVT3 = 1;
        ECap3Regs.ECCLR.bit.CEVT4 = 1;
        ECap3Regs.ECCLR.bit.INT = 1;

        ECap3Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;

        ECap3Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

#endif
}

void ECap4Cfg(void)
{
#if(ECAP4_MODE)
       ECap4Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap4Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
       ECap4Regs.ECCTL1.bit.CAPLDEN = EC_DISABLE; // Disable CAP1-CAP4 register loads
       ECap4Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

       // Setup APWM mode on CAP1, set period and compare registers
       ECap4Regs.ECCTL1.bit.PRESCALE = 0;       // Event Prescaler(not clock) Divided by 1
       ECap4Regs.ECCTL2.bit.CAP_APWM = 1;       // Enable APWM mode
       ECap4Regs.ECCTL2.bit.APWMPOL = 0;        // 0: Active High, Duty is high time    1: Active Low, Duty is low time
       ECap4Regs.CAP3 = 10000000L;              // Set Period value as 10Hz
       ECap4Regs.CAP4 = 200;                    // Set Compare value as 1usec
       ECap4Regs.ECCLR.all = 0x0FF;             // Clear pending interrupts
       ECap4Regs.ECCTL2.bit.SYNCI_EN = 0;       // 1:ENABLE SYNC IN, 0 : DISABLE SYNC IN
       ECap4Regs.ECCTL2.bit.SYNCO_SEL = 1;      // 00:Bypass, 01:counter=period, 10,11:disable
       ECap4Regs.ECEINT.bit.CTR_EQ_PRD = 1;     // enable Compare Equal Int

       ECap4Regs.ECCTL2.bit.TSCTRSTOP = 1;      // TSCNT free running. start Counter
#else
        // ECAP module 1 config

        ECap4Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
        ECap4Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;

        ECap4Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
        ECap4Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;

        ECap4Regs.ECCTL1.bit.CAP1POL = EC_FALLING;
//      ECap4Regs.ECCTL1.bit.CAP2POL = EC_FALLING;
//      ECap4Regs.ECCTL1.bit.CAP3POL = EC_FALLING;
//      ECap4Regs.ECCTL1.bit.CAP4POL = EC_FALLING;

        ECap4Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
//      ECap4Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
//      ECap4Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
//      ECap4Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;

        ECap4Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;

        ECap4Regs.ECCTL2.bit.STOP_WRAP = EC_STOP_EVT1;

        ECap4Regs.ECEINT.bit.CEVT1 = EC_INT_EN;
//      ECap4Regs.ECEINT.bit.CEVT2 = EC_INT_EN;
//      ECap4Regs.ECEINT.bit.CEVT3 = EC_INT_EN;
//      ECap4Regs.ECEINT.bit.CEVT4 = EC_INT_EN;

        ECap4Regs.ECCLR.bit.CEVT1 = 1;
//      ECap4Regs.ECCLR.bit.CEVT2 = 1;
//      ECap4Regs.ECCLR.bit.CEVT3 = 1;
//      ECap4Regs.ECCLR.bit.CEVT4 = 1;
        ECap4Regs.ECCLR.bit.INT = 1;

        ECap4Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
        ECap4Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

#endif
}

void ECap5Cfg(void)
{
#if(ECAP5_MODE)
       ECap5Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap5Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
       ECap5Regs.ECCTL1.bit.CAPLDEN = EC_DISABLE; // Disable CAP1-CAP4 register loads
       ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_FREEZE;// Make sure the counter is stopped

       // Setup APWM mode on CAP1, set period and compare registers
       ECap5Regs.ECCTL1.bit.PRESCALE = EC_DIV1; // Event Prescaler(not clock) Divided by 2
       ECap5Regs.ECCTL2.bit.CAP_APWM = 1;       // Enable APWM mode
       ECap5Regs.ECCTL2.bit.APWMPOL = 0;        // 0: Active High, Duty is high time    1: Active Low, Duty is low time
       ECap5Regs.CAP1 = 0xffffffff;             // Set Period value as 10Hz
       ECap5Regs.CAP2 = 0;                      // Set Compare value as 1usec
       ECap5Regs.CAP3 = 0xffffffff;             // Set Period value as 10Hz
       ECap5Regs.CAP4 = 0;                      // Set Compare value as 1usec
       ECap5Regs.ECCLR.all = 0x0FF;             // Clear pending interrupts
       ECap5Regs.ECCTL2.bit.SYNCI_EN = 0;       // 1:ENABLE SYNC IN, 0 : DISABLE SYNC IN
       ECap5Regs.ECCTL2.bit.SYNCO_SEL = 1;      // 00:Bypass, 01:counter=period, 10,11:disable
       ECap5Regs.ECEINT.bit.CTR_EQ_CMP = 1;     // enable Compare Equal Int

       ECap5Regs.ECCLR.bit.INT = 1;
       ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_FREEZE;      // TSCNT free running. start Counter
       PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
#else
        // ECAP module 1 config

        ECap5Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
        ECap5Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;

        ECap5Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
        ECap5Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;

        ECap5Regs.ECCTL1.bit.CAP1POL = EC_RISING;
        ECap5Regs.ECCTL1.bit.CAP2POL = EC_RISING;
        ECap5Regs.ECCTL1.bit.CAP3POL = EC_RISING;
        ECap5Regs.ECCTL1.bit.CAP4POL = EC_RISING;

        ECap5Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
        ECap5Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
        ECap5Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
        ECap5Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;

        ECap5Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;

        ECap5Regs.ECCTL2.bit.STOP_WRAP = EC_STOP_EVT1;

        ECap5Regs.ECEINT.bit.CEVT1 = EC_INT_EN;
        ECap5Regs.ECEINT.bit.CEVT2 = EC_INT_EN;
        ECap5Regs.ECEINT.bit.CEVT3 = EC_INT_EN;
        ECap5Regs.ECEINT.bit.CEVT4 = EC_INT_EN;

        ECap5Regs.ECCLR.bit.CEVT1 = 1;
        ECap5Regs.ECCLR.bit.CEVT2 = 1;
        ECap5Regs.ECCLR.bit.CEVT3 = 1;
        ECap5Regs.ECCLR.bit.CEVT4 = 1;
        ECap5Regs.ECCLR.bit.INT = 1;

        ECap5Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;

        ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

#endif
}

void ECap6Cfg(void)
{
#if(ECAP6_MODE)
       ECap6Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
       ECap6Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
       ECap6Regs.ECCTL1.bit.CAPLDEN = EC_DISABLE; // Disable CAP1-CAP4 register loads
       ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_FREEZE;        // Make sure the counter is stopped

       // Setup APWM mode on CAP1, set period and compare registers
       ECap6Regs.ECCTL1.bit.PRESCALE = EC_DIV1; // Event Prescaler(not clock) Divided by 1
       ECap6Regs.ECCTL2.bit.CAP_APWM = 1;       // Enable APWM mode
       ECap6Regs.ECCTL2.bit.APWMPOL = 0;        // 0: Active High, Duty is high time    1: Active Low, Duty is low time
       ECap6Regs.CAP1 = 0xffffffff;             // Set Period value as 10Hz
       ECap6Regs.CAP2 = 1;                      // Set Compare value as 1usec
       ECap6Regs.CAP3 = 0xffffffff;             // Set Period value as 10Hz
       ECap6Regs.CAP4 = 1;                      // Set Compare value as 1usec
       ECap6Regs.ECCLR.all = 0x0FF;             // Clear pending interrupts
       ECap6Regs.ECCTL2.bit.SYNCI_EN = 0;       // 1:ENABLE SYNC IN, 0 : DISABLE SYNC IN
       ECap6Regs.ECCTL2.bit.SYNCO_SEL = 1;      // 00:Bypass, 01:counter=period, 10,11:disable
       ECap6Regs.ECEINT.bit.CTR_EQ_CMP = 1;     // enable Compare Equal Int

       ECap6Regs.ECCTL2.bit.TSCTRSTOP = 1;      // TSCNT free running. start Counter
       PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

#else
        // ECAP module 1 config

        ECap6Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
        ECap6Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;

        ECap6Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
        ECap6Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;

        ECap6Regs.ECCTL1.bit.CAP1POL = EC_RISING;
        ECap6Regs.ECCTL1.bit.CAP2POL = EC_RISING;
        ECap6Regs.ECCTL1.bit.CAP3POL = EC_RISING;
        ECap6Regs.ECCTL1.bit.CAP4POL = EC_RISING;

        ECap6Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
        ECap6Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
        ECap6Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
        ECap6Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;

        ECap6Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;

        ECap6Regs.ECCTL2.bit.STOP_WRAP = EC_STOP_EVT1;

        ECap6Regs.ECEINT.bit.CEVT1 = EC_INT_EN;
        ECap6Regs.ECEINT.bit.CEVT2 = EC_INT_EN;
        ECap6Regs.ECEINT.bit.CEVT3 = EC_INT_EN;
        ECap6Regs.ECEINT.bit.CEVT4 = EC_INT_EN;

        ECap6Regs.ECCLR.bit.CEVT1 = 1;
        ECap6Regs.ECCLR.bit.CEVT2 = 1;
        ECap6Regs.ECCLR.bit.CEVT3 = 1;
        ECap6Regs.ECCLR.bit.CEVT4 = 1;
        ECap6Regs.ECCLR.bit.INT = 1;

        ECap6Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;

        ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

#endif
}
