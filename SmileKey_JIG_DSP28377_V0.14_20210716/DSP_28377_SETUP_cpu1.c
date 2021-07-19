/*
	DSP_28377_SETUP_cpu1.c
 */
#include "F28x_Project.h"
#include "define.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "F2837xD_Ipc_drivers.h"


#define CORE1	0
#define CORE2	1

// stand alone
#define _STAND_ALONE	0		//CPU2 - Real time Emulation : 0 , Stand Alone : 1


extern void scia_fifo_init( void );
extern void scib_fifo_init( void );
extern void scic_fifo_init( void );
extern void scid_fifo_init( void );
extern void InitECapture(void);
extern void	GPIO_SETTING(void);
extern void	Initialize_Epwm(void);

extern void Initialize_ADC( void );
extern void InitCMPSS( void );
extern void InitCpuTimer( float period );
extern void InitCfgDAC( void );

//void	SetupADCEpwm(void);
void	I2CA_Init(void);

interrupt void epwm1_timer_isr(void);		// epwm12 ISR
interrupt void epwm4_timer_isr(void);		// epwm4 ISR
//interrupt void epwm12_timer_isr(void);		// epwm12 ISR
interrupt void ecap1_isr(void);
interrupt void ecap2_isr(void);
interrupt void dCANA_isr(void);
interrupt void dCANB_isr(void);

__interrupt void AdcA_isr(void);


void	InitDog(void);
void 	CAN_INIT(void);
void 	BootingCPU2(void);


//== can control

volatile tIpcController g_sIpcController1;
extern Uint16 BootFlag;

void Sys_init28377(void)
{
	//============================================================================================
	// 전역 인터럽트 비활성화
	//--------------------------------------------------------------------------------------------
		DINT;
	//============================================================================================

	//=============================================================
	// Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the F28M3Xx_SysCtrl.c file.
	//-------------------------------------------------------------
	InitSysCtrl();
	//=============================================================

	//=============================================================
	// Initialize GPIO:
	// This example function is found in the F28M3Xx_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	//-------------------------------------------------------------
	InitGpio();
	GPIO_SETTING();

	//--Transfer ownership to CPU02 ---//
	EALLOW;
	DevCfgRegs.CPUSEL0.bit.EPWM1 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM2 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM3 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM4 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM5 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM7 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM8 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM9 = CORE1;
	DevCfgRegs.CPUSEL0.bit.EPWM10 = CORE1;

	DevCfgRegs.CPUSEL1.bit.ECAP1 = CORE1;

	DevCfgRegs.CPUSEL1.bit.ECAP2 = CORE1;
	DevCfgRegs.CPUSEL1.bit.ECAP3 = CORE1;
	DevCfgRegs.CPUSEL1.bit.ECAP4 = CORE1;
	DevCfgRegs.CPUSEL1.bit.ECAP5 = CORE1;
	DevCfgRegs.CPUSEL1.bit.ECAP6 = CORE1;

	DevCfgRegs.CPUSEL11.bit.ADC_A = CORE1;
	DevCfgRegs.CPUSEL11.bit.ADC_B = CORE1;
	DevCfgRegs.CPUSEL11.bit.ADC_C = CORE1;
	DevCfgRegs.CPUSEL11.bit.ADC_D = CORE1;

	DevCfgRegs.CPUSEL14.bit.DAC_A = CORE1;
	DevCfgRegs.CPUSEL14.bit.DAC_B = CORE1;
	DevCfgRegs.CPUSEL14.bit.DAC_C = CORE1;

	EDIS;
	//---------------------------------//
	//=============================================================

	BootingCPU2();

	//== Give Memory Access to GS4 SARAM to CPU02============
	while( !(MemCfgRegs.GSxMSEL.bit.MSEL_GS4 ))
	{
		EALLOW;
		MemCfgRegs.GSxMSEL.bit.MSEL_GS4 = 1;
		EDIS;
	}

	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
	//=============================================================

	//=============================================================
	//XCLKOUT setting
	//-------------------------------------------------------------
	EALLOW;
	ClkCfgRegs.CLKSRCCTL3.bit.XCLKOUTSEL = 0x010;
	ClkCfgRegs.XCLKOUTDIVSEL.all = 0x0;
	ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
	EDIS;
	//============================================================

	//=============================================================
	// 인터럽트 초기화
	//-------------------------------------------------------------
	InitPieCtrl();
	// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	//Map ISR functions
	EALLOW;
	PieVectTable.EPWM1_INT = &epwm1_timer_isr;
//	PieVectTable.EPWM4_INT = &epwm4_timer_isr;

//	PieVectTable.ECAP1_INT = &ecap1_isr;
//	PieVectTable.ECAP2_INT = &ecap2_isr;

	// Interrupt Service Routine Re-mapping
	PieVectTable.DCANA_1_INT = &dCANA_isr;
	PieVectTable.DCANB_1_INT = &dCANB_isr;

//	PieVectTable.DMA_CH1_INT = &dmaCh1ISR;
	PieVectTable.ADCA1_INT = &AdcA_isr;

	// 외부 인터터트 포합된 백터 활성화
	PieCtrlRegs.PIEIER9.bit.INTx5 = 1;	// Enable PIE group 9 interrupt 7 for CANB0_INT
	PieCtrlRegs.PIEIER9.bit.INTx7 = 1;	// Enable PIE group 9 interrupt 7 for CANB0_INT
	IER |= M_INT9;						// Enable CPU INT9 for CANB0_INT
	EDIS;
	//=============================================================
//	IPCInitialize (&g_sIpcController1, IPC_INT1, IPC_INT1);

	//=============================================================
	// cpu timer
	//-------------------------------------------------------------

//	InitFlash();
	InitCpuTimer(555.55);
	//=============================================================

	//=============================================================
	// I2C 초기화
	//-------------------------------------------------------------
	I2CA_Init();
	//=============================================================

	//=============================================================
	// SCI 초기화
	//-------------------------------------------------------------
	scia_fifo_init();
	scib_fifo_init();
	scic_fifo_init();
	scid_fifo_init();
	//=============================================================

	//=============================================================
	// CAPTURE 초기화
	//-------------------------------------------------------------
	InitECapture();
	//=============================================================

	//=============================================================
	// ADC 초기화
	//-------------------------------------------------------------
	Initialize_ADC();
	//=============================================================

	EALLOW;
	//Enable global Interrupts and higher priority real-time debug events:
	IER |= M_INT1;
	IER |= M_INT3; //Enable group 1 interrupts
//	IER |= M_INT4;
	IER |= M_INT7;
//	IER |= M_INT10;
	//enable PIE interrupt
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;	// EPWM1_INT : INT3.1
//	PieCtrlRegs.PIEIER3.bit.INTx4 = 1;  // EPWM1_INT : INT3.4
	PieCtrlRegs.PIEIER7.bit.INTx1 = 1;  // EPWM1_INT : INT7.1
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;  // EPWM1_INT : INT7.1
	EDIS;
	//=============================================================
	// DAC 초기화
	//-------------------------------------------------------------
	//ConfigureDAC(); // DAC 초기화
	InitCfgDAC();
	//=============================================================

	//=============================================================
	// EPWM 초기화
	//-------------------------------------------------------------
	Initialize_Epwm(); // EPWM 초기화
//	ConfigureEPWM();
	//=============================================================

	//=============================================================
	// COMPARATOR // Configure Comparator COMP1H to accept POS input from pin and NEG input from DAC
	//-------------------------------------------------------------
	InitCMPSS();
	//=============================================================
	// McBSP 초기화
	InitMcbspa();
	InitMcbspa32bit();

	ERTM;   // Enable Global realtime interrupt DBGM
}

void I2CA_Init(void)
{
	// Initialize I2C
	I2caRegs.I2CSAR = 0x0050;		// Slave address - EEPROM control code
	I2caRegs.I2CPSC.all = 19;		// Prescaler - need 7-12 Mhz on module clk
	I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
	I2caRegs.I2CIER.all = 0x26;		// Enable SCD & ARDY & NACK interrupts
	I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
									// Stop I2C when suspended
	I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

	return;
}

void BootingCPU2( void )
{
#if( _STAND_ALONE )
	#ifdef _FLASH
	if(BootFlag == 0)
	{
		//  Send boot command to allow the CPU02 application to begin execution
		IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
	}
	#else
		//  Send boot command to allow the CPU02 application to begin execution
		IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
	#endif
	// stand alone end
#endif
}


void InitDog(void)
{
	EALLOW;
	WdRegs.WDCR.all = 0x2F;		//Enable Watch dog and clk /64 = 3Khz count *256 = 83msec Reset
//	WdRegs.SCSR |=BIT2;		//Watchdog overflow => CPU Reset init 1
	EDIS;
}

