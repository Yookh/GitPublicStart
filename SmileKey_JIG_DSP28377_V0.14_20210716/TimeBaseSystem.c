/*
 * TimeBaseSystem.c
 *
 *  Created on: 2016. 4. 1.
 *      Author: Yoo Kwang hyun
 *
 */

#include "F28x_Project.h"     // F2806x Headerfile Include File
#include "define.h"
#include "time.h"

#define CPU_TIME_FREQ		SAMPL_FREQ
#define CONTROL_FREQ		360		// 360Hz

void InitCpuTimer( float period );
int Period_CpuTimer( void );
int Period_10ms( void );
int Period_50ms( void );
int Period_100ms( void );
int Period_1000ms( void );
int Period_Control( void );

Uint16 CpuTimeCnt;
Uint16 Tic10ms;
Uint16 Tic100ms;
Uint16 Tic50ms;
Uint16 Tic1000ms;
Uint16 TicControl;

void InitCpuTimer( float period )
{
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 200, period); 		// CpuTimer0, 200MHz, 555.55usec, 1800Hz Timer
	StartCpuTimer0();
}

int Period_CpuTimer( void )
{
	if(CpuTimer0Regs.TCR.bit.TIF==1)
	{
		CpuTimer0Regs.TCR.bit.TIF=1;

		CpuTimeCnt++;
		Tic10ms++;
		Tic50ms++;
		Tic100ms++;
		Tic1000ms++;
		TicControl++;
		return 1;
	}
	return 0;
}

int Period_10ms( void )
{
	if(Tic10ms > CPU_TIME_FREQ/100)
	{
		Tic10ms = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

int Period_50ms( void )
{
    if(Tic50ms > CPU_TIME_FREQ/20)
    {
        Tic50ms = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int Period_100ms( void )
{
	if(Tic100ms > CPU_TIME_FREQ/10)
	{
		Tic100ms = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}


int Period_1000ms( void )
{
    if(Tic1000ms > CPU_TIME_FREQ)
    {
        Tic1000ms = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int Period_Control( void )
{
	if(TicControl >= CPU_TIME_FREQ/CONTROL_FREQ)
	{
		TicControl = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}
/*
clock_t Time_Check(void)
{
    static clock_t newTime, oldTime, diffTime;
    newTime = clock();
    diffTime = oldTime - newTime;
    oldTime = newTime;

    return diffTime;
}
*/
