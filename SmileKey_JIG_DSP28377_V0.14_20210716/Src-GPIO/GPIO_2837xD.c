/*
 * GPIO_2837xD.c
 *
 *  Created on: 2016. 9. 9.
 *      Author: Yoo Kwang hyun
 */
#include "F28x_Project.h"

void GPIO_SETTING(void);

	void GPIO_SETTING(void)
	{
		Uint16 i;

		//== CPU1 =======================================================//

        GPIO_SetupPinMux(0, GPIO_MUX_CPU1, 1);                  //Test Pwm Out1
        GPIO_SetupPinOptions(0, GPIO_OUTPUT, GPIO_PUSHPULL);

		for(i=1; i<=22; i++)			                        //GPIO0 ~ 23 -
		{
			GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 0);
			GPIO_SetupPinOptions(i, GPIO_INPUT, GPIO_SYNC);
		}

        GPIO_SetupPinMux(16, GPIO_MUX_CPU1, 0);                 //GPIO16 - RELAY 3 OUT
        GPIO_SetupPinOptions(16, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(22, GPIO_MUX_CPU1, 0);                 //GPIO22 - RELAY 1 OUT
        GPIO_SetupPinOptions(22, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(22, GPIO_MUX_CPU1, 0);                 //GPIO23 - RELAY 2 OUT
        GPIO_SetupPinOptions(23, GPIO_OUTPUT, GPIO_PUSHPULL);

        for(i=24; i<=32; i++)                                   //GPIO24 ~ 32 - FAN_PHASE1~6 and not used.
        {
            GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 0);
            GPIO_SetupPinOptions(i, GPIO_INPUT, GPIO_SYNC);
        }

        for(i=33; i<=49; i++)                                   //GPIO33 ~ 49 - ON/OFF MD23~39
        {
            GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 0);
            GPIO_SetupPinOptions(i, GPIO_INPUT, GPIO_SYNC);
        }

        GPIO_SetupPinMux(36, GPIO_MUX_CPU1, 6);                 //GPIO70 - CANRXA
        GPIO_SetupPinOptions(36, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(37, GPIO_MUX_CPU1, 6);                 //GPIO71 - CANTXA
        GPIO_SetupPinOptions(37, GPIO_OUTPUT, GPIO_PUSHPULL);

        GPIO_SetupPinMux(38, GPIO_MUX_CPU1, 6);                 //GPIO72 - CANTXB
        GPIO_SetupPinOptions(38, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(39, GPIO_MUX_CPU1, 6);                 //GPIO73 - CANRXB
        GPIO_SetupPinOptions(39, GPIO_INPUT, GPIO_PUSHPULL);

        for(i=50; i<=61; i++)                                   //GPIO48 ~ 57(Not Used)
        {
            GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 0);
            GPIO_SetupPinOptions(i, GPIO_INPUT, GPIO_SYNC);
        }

        //---- SPI ---------------------------------------------------
/*        GPIO_SetupPinMux(58, GPIO_MUX_CPU1, 1);                 //GPIO58 - SPISIMO
        GPIO_SetupPinOptions(58, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(59, GPIO_MUX_CPU1, 1);                 //GPIO59 - SPISOMIA
        GPIO_SetupPinOptions(59, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(60, GPIO_MUX_CPU1, 1);                 //GPIO60 - SPICLKA
        GPIO_SetupPinOptions(60, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(61, GPIO_MUX_CPU1, 1);                 //GPIO61 - SPISTEA
        GPIO_SetupPinOptions(61, GPIO_OUTPUT, GPIO_PUSHPULL);*/

        for(i=62; i<=77; i++)                                   //GPIO62 ~ 69(Not Used) GPIO73 ~ 77(DIN1,2 FROM MD1,2,3,4,5)
        {
            GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 0);
            GPIO_SetupPinOptions(i, GPIO_INPUT, GPIO_PUSHPULL);
        }

		GPIO_SetupPinMux(78, GPIO_MUX_CPU1, 0);                 //GPIO78 - TXDBEN
		GPIO_SetupPinOptions(78, GPIO_OUTPUT, GPIO_PUSHPULL);
	    for(i=79; i<=82; i++)                                   //GPIO79 ~ 81
		{
			GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 0);
			GPIO_SetupPinOptions(i, GPIO_INPUT, GPIO_PUSHPULL);
		}

        GPIO_SetupPinMux(83, GPIO_MUX_CPU1, 0);     //GPIO83 - SCI TXDAEN
        GPIO_SetupPinOptions(83, GPIO_OUTPUT, GPIO_PUSHPULL);

		GPIO_SetupPinMux(84, GPIO_MUX_CPU1, 5);                 //GPIO84 - SCITXDA
		GPIO_SetupPinOptions(84, GPIO_OUTPUT, GPIO_PUSHPULL);
		GPIO_SetupPinMux(85, GPIO_MUX_CPU1, 5);                 //GPIO85 - SCIRXDA
		GPIO_SetupPinOptions(85, GPIO_INPUT, GPIO_ASYNC);

        GPIO_SetupPinMux(86, GPIO_MUX_CPU1, 5);                 //GPIO86 - SCITXDB
        GPIO_SetupPinOptions(86, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(87, GPIO_MUX_CPU1, 5);                 //GPIO87 - SCIRXDB
        GPIO_SetupPinOptions(87, GPIO_INPUT, GPIO_ASYNC);

        GPIO_SetupPinMux(88, GPIO_MUX_CPU1, 0);     //GPIO88 - SCI TXDBEN
        GPIO_SetupPinOptions(8, GPIO_OUTPUT, GPIO_PUSHPULL);

        GPIO_SetupPinMux(89, GPIO_MUX_CPU1, 6);                 //GPIO89 - SCITXDC
        GPIO_SetupPinOptions(89, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(90, GPIO_MUX_CPU1, 6);                 //GPIO90 - SCIRXDC
        GPIO_SetupPinOptions(90, GPIO_INPUT, GPIO_ASYNC);

		//---- I2C ---------------------------------------------------
		GPIO_SetupPinMux(91, GPIO_MUX_CPU1, 6);	                //SDAA
		GPIO_SetupPinOptions(91, GPIO_OUTPUT, GPIO_PUSHPULL);
		GPIO_SetupPinMux(92, GPIO_MUX_CPU1, 6);                 //SCLA
		GPIO_SetupPinOptions(92, GPIO_OUTPUT, GPIO_PUSHPULL);

        GPIO_SetupPinMux(93, GPIO_MUX_CPU1, 6);                 //GPIO93 - SCITXDD
        GPIO_SetupPinOptions(93, GPIO_OUTPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(94, GPIO_MUX_CPU1, 6);                 //GPIO94 - SCIRXDD
        GPIO_SetupPinOptions(94, GPIO_INPUT, GPIO_ASYNC);

		GPIO_SetupPinMux(99, GPIO_MUX_CPU1, 0);
		GPIO_SetupPinOptions(99, GPIO_OUTPUT, GPIO_PUSHPULL);   //GPIO99 - SCI TXDCEN

		GPIO_SetupPinMux(133, GPIO_MUX_CPU1, 0);
		GPIO_SetupPinOptions(133, GPIO_INPUT, GPIO_SYNC);
	}
