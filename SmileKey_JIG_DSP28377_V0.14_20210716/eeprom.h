 /*****************************************************
	Project : Charger for SEIKO
	Version : 1.0
	Date    : 2006-03-03
	Author  : Hwan Ho Sung                  
	Company : PSTEK Co., Ltd .             
	Comments: MPPT Charger Control Program(ATmega168)
	
	Chip type           : ATmega168
	Program type        : Application
	Clock frequency     : 16.000 MHz
	Memory model        : Small
	External SRAM size  : 0
	Data Stack size     : 256

	2005.05.02	coded for external eeprom access
	2006.03.03	changed from eep.c to eep.h
	2008.12.15	RTC coding
				RTCReadTemp() : Read temperature in Celsius. 0.25C scale. 1234=12.34C
				RTCRead_Time() : Read time
				RTCSet_Time() : Write time set value
				Dec_to_BCD() : decimal to BCD code conversion
*****************************************************/

#include "define.h"

void	EEP_RW(void);

Uint16	i2cReadData(Uint16 wDevice, Uint16 wAddr);
Uint16	i2cWriteData(Uint16 wDevice, Uint16 wAddr, Uint16 wData);
void	RTCReadTemp(void);
void	RTCRead_Time(void);
void	RTCSet_Time(void);
Uint16	Dec_to_BCD(Uint16 Dec);

#define EEP_READ_CMD	0x03
#define EEP_WRITE_CMD	0x02
#define EEP_WRDIS_CMD	0x04
#define EEP_WRENA_CMD	0x06
#define EEP_RDSR_CMD	0x05
#define EEP_WRSR_CMD	0x01

//#define EEP_END_ADDR	255		// EEPROM last address(254=127*2)

// EEPROM ENABLE
#define	EEP_ENABLE				GpioDataRegs.GPACLEAR.bit.GPIO19=1		
#define	EEP_DISABLE				GpioDataRegs.GPASET.bit.GPIO19=1

#define	_25C160		// for 20kbyte address range

int		wReturn, Thermo;
Uint16	RTC_Sec, RTC_Min, RTC_Hour, RTC_Day, RTC_Date, RTC_Month, RTC_Year; // Read data(Present Value)	
Uint16  SET_SS, SET_MM, SET_HH, SET_DY, SET_DD, SET_MN, SET_YY;	// Write data(Data will set)
//SETTING  SEC,    MIN,   HOUR,    DAY,   DATE,  MONTH,   YEAR
//Range  00-59,  00-59,  00-24,    1-7,   0-31,   1-12,  00-99
Uint16	SET_RTC;

#pragma CODE_SECTION(i2cReadData, "ramfuncs");
Uint16 i2cReadData(Uint16 wDevice, Uint16 wAddr)
{
	Uint16	wStatus=0, IntSource=0;

	wAddr=(wAddr<<1);
	I2caRegs.I2CSAR = wDevice;
	while(wStatus==0) {
		while(I2caRegs.I2CMDR.bit.STP == 1) ;	// Wait until the STP bit is cleared
		while(I2caRegs.I2CSTR.bit.BB == 1) ;	// Check if bus busy  
		I2caRegs.I2CCNT = 2;					// number of memory address byte
		I2caRegs.I2CDXR = (wAddr>>8)&0xff;
		I2caRegs.I2CDXR = wAddr&0xff;
		I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address no stop

		while(IntSource != I2C_ARDY_ISRC) {		// Check if register-access ready
			IntSource = I2caRegs.I2CISRC.all;
		}

		if(I2caRegs.I2CSTR.bit.NACK == 1) {
			I2caRegs.I2CMDR.bit.STP = 1;
			I2caRegs.I2CSTR.bit.NACK = 1;
			while(IntSource != I2C_SCD_ISRC) {		// Check if stop condition
				IntSource = I2caRegs.I2CISRC.all;
			}
			DELAY_US(500);		// delay 0.5msec wait
		}
		else {
			wStatus=1;	// == ack received, go next step(read data)
		}
	}

	I2caRegs.I2CCNT = 2;				// Setup how many bytes to expect
	I2caRegs.I2CMDR.all = 0x2C20;		// Send restart as master receiver

	while(I2caRegs.I2CSTR.bit.SCD == 0) ;	// Wait until the STOP condition detected bit set
	I2caRegs.I2CSTR.bit.SCD = 1;			// Clear SCD bit in Status register
    wReturn = (I2caRegs.I2CDRR<<8) | I2caRegs.I2CDRR;

	return(wReturn);
}

#pragma CODE_SECTION(i2cWriteData, "ramfuncs");
Uint16 i2cWriteData(Uint16 wDevice, Uint16 wAddr, Uint16 wData)
{
	Uint16	wStatus=0, IntSource=0;

	wAddr=(wAddr<<1);
	I2caRegs.I2CSAR = wDevice;
	while(wStatus==0) {
		while(I2caRegs.I2CMDR.bit.STP == 1) ;	// Wait until the STP bit is cleared
		while(I2caRegs.I2CSTR.bit.BB == 1) ;	// Check if bus busy  
		I2caRegs.I2CCNT = 4;					// number of memory address byte
		I2caRegs.I2CDXR = (wAddr>>8) & 0xff;
		I2caRegs.I2CDXR =  wAddr & 0xff;
		I2caRegs.I2CDXR = (wData>>8) & 0xff;
		I2caRegs.I2CDXR =  wData & 0xff;
		I2caRegs.I2CMDR.all = 0x6E20;			// Send start as master transmitter

		for(;;) {
			IntSource = I2caRegs.I2CISRC.all;
			if(IntSource == I2C_SCD_ISRC) {		// Check if stop condition
				wStatus=1;
				break;
			}

			if(IntSource == I2C_NACK_ISRC) {	// No-acknoledgment
				I2caRegs.I2CMDR.bit.STP = 1;
				I2caRegs.I2CSTR.bit.NACK = 1;
				while(IntSource != I2C_SCD_ISRC) {		// Check if stop condition
					IntSource = I2caRegs.I2CISRC.all;
				}
				DELAY_US(500);		// delay 0.5msec wait
				break;
			}
		}
	}
	return(0);
}

#pragma CODE_SECTION(RTCReadTemp, "ramfuncs");
void RTCReadTemp(void)
{
	Uint16	wStatus=0, IntSource=0;

	I2caRegs.I2CSAR = 0x68;
	while(wStatus==0) {
		while(I2caRegs.I2CMDR.bit.STP == 1) ;	// Wait until the STP bit is cleared
		while(I2caRegs.I2CSTR.bit.BB == 1) ;	// Check if bus busy  
		I2caRegs.I2CCNT = 1;					// number of memory address byte
		I2caRegs.I2CDXR = 0x11;
		I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address no stop

		while(IntSource != I2C_ARDY_ISRC) {		// Check if register-access ready
			IntSource = I2caRegs.I2CISRC.all;
		}

		if(I2caRegs.I2CSTR.bit.NACK == 1) {
			I2caRegs.I2CMDR.bit.STP = 1;
			I2caRegs.I2CSTR.bit.NACK = 1;
			while(IntSource != I2C_SCD_ISRC) {		// Check if stop condition
				IntSource = I2caRegs.I2CISRC.all;
			}
			DELAY_US(500);		// delay 0.5msec wait
		}
		else {
			wStatus=1;	// == ack received, go next step(read data)
		}
	}

	I2caRegs.I2CCNT = 2;				// Setup how many bytes to expect
	I2caRegs.I2CMDR.all = 0x2C20;		// Send restart as master receiver

	while(I2caRegs.I2CSTR.bit.SCD == 0) ;	// Wait until the STOP condition detected bit set
	I2caRegs.I2CSTR.bit.SCD = 1;			// Clear SCD bit in Status register
    wReturn = ((I2caRegs.I2CDRR<<8) | I2caRegs.I2CDRR)>>6;
	Thermo=wReturn*25; // 0.25C scale

//	return(wReturn);
}

/*
#pragma CODE_SECTION(RTCRead_Time, "ramfuncs");
void RTCRead_Time(void)
{
	Uint16	wStatus=0, IntSource=0, Time_tmp, Century_tmp;

	I2caRegs.I2CSAR = 0x68;
	while(wStatus==0)
	{
		while(I2caRegs.I2CMDR.bit.STP == 1) ;	// Wait until the STP bit is cleared
		while(I2caRegs.I2CSTR.bit.BB == 1) ;	// Check if bus busy  
		I2caRegs.I2CCNT = 1;					// number of memory address byte
		I2caRegs.I2CDXR = 0x00;
		I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address no stop

		while(IntSource != I2C_ARDY_ISRC) {		// Check if register-access ready
			IntSource = I2caRegs.I2CISRC.all;
		}

		if(I2caRegs.I2CSTR.bit.NACK == 1) {
			I2caRegs.I2CMDR.bit.STP = 1;
			I2caRegs.I2CSTR.bit.NACK = 1;
			while(IntSource != I2C_SCD_ISRC) {		// Check if stop condition
				IntSource = I2caRegs.I2CISRC.all;
			}
			DELAY_US(500);		// delay 0.5msec wait
		}
		else wStatus=1;	// == ack received, go next step(read data)
	}

	I2caRegs.I2CCNT = 7;				// Setup how many bytes to expect
	I2caRegs.I2CMDR.all = 0x2C20;		// Send restart as master receiver

	while(I2caRegs.I2CSTR.bit.SCD == 0) ;	// Wait until the STOP condition detected bit set
	I2caRegs.I2CSTR.bit.SCD = 1;			// Clear SCD bit in Status register
	Time_tmp = I2caRegs.I2CDRR;
	RTC_Sec  = (Time_tmp&0x0f)+((Time_tmp&0xf0)>>4)*10;
	Time_tmp = I2caRegs.I2CDRR;
	RTC_Min  = (Time_tmp&0x0f)+((Time_tmp&0xf0)>>4)*10;
	Time_tmp = I2caRegs.I2CDRR;
	RTC_Hour = (Time_tmp&0x0f)+((Time_tmp&0x30)>>4)*10;
	RTC_Day  = I2caRegs.I2CDRR;
	Time_tmp = I2caRegs.I2CDRR;
	RTC_Date = (Time_tmp&0x0f)+((Time_tmp&0xf0)>>4)*10;
	Time_tmp = I2caRegs.I2CDRR;
	Century_tmp = Time_tmp&0x8000;
	RTC_Month= (Time_tmp&0x0f)+((Time_tmp&0xf0)>>4)*10;
	Time_tmp = I2caRegs.I2CDRR;
	RTC_Year = (Time_tmp&0x0f)+((Time_tmp&0xf0)>>4)*10+2000+Century_tmp*100;
}

#pragma CODE_SECTION(RTCSet_Time, "ramfuncs");
void RTCSet_Time(void) 
{
	Uint16	wStatus=0, IntSource=0;

	I2caRegs.I2CSAR = 0x68;		// RTC device ID
	while(wStatus==0) {
		while(I2caRegs.I2CMDR.bit.STP == 1) ;	// Wait until the STP bit is cleared
		while(I2caRegs.I2CSTR.bit.BB == 1) ;	// Check if bus busy  
		I2caRegs.I2CCNT = 7;					// number of memory address byte
		I2caRegs.I2CDXR = Dec_to_BCD(SET_SS);
		I2caRegs.I2CDXR = Dec_to_BCD(SET_MM);
		I2caRegs.I2CDXR = Dec_to_BCD(SET_HH);
		I2caRegs.I2CDXR = SET_DY;
		I2caRegs.I2CDXR = Dec_to_BCD(SET_DD);
		I2caRegs.I2CDXR = Dec_to_BCD(SET_MN);
		I2caRegs.I2CDXR = Dec_to_BCD(SET_YY);
		I2caRegs.I2CMDR.all = 0x6E20;			// Send start as master transmitter

		for(;;) {
			IntSource = I2caRegs.I2CISRC.all;
			if(IntSource == I2C_SCD_ISRC) {		// Check if stop condition
				wStatus=1;
				break;
			}

			if(IntSource == I2C_NACK_ISRC) {	// No-acknoledgment
				I2caRegs.I2CMDR.bit.STP = 1;
				I2caRegs.I2CSTR.bit.NACK = 1;
				while(IntSource != I2C_SCD_ISRC) {		// Check if stop condition
					IntSource = I2caRegs.I2CISRC.all;
				}
				DELAY_US(500);		// delay 0.5msec wait
				break;
			}
		}
	}
	//return(0);
}

#pragma CODE_SECTION(Dec_to_BCD, "ramfuncs");
Uint16	Dec_to_BCD(Uint16 Dec)
{
	Uint16	BCD, wTmp;

	wTmp = (Dec/10);
	BCD = ((wTmp<<4)&0xf0) + ((Dec%10)&0x0f);

	return(BCD);	
}
*/


