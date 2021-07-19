/*
 * DualCore_Select.h
 *
 *  Created on: 2016. 11. 7.
 *      Author: Kwang Hyun Yoo
 */

#ifndef DUALFREQ_F28377D_CPU1_V1_02_DUALCORE_SELECT_H_
#define DUALFREQ_F28377D_CPU1_V1_02_DUALCORE_SELECT_H_

#define CPU1	1
#define CPU2	0

#if( CPU1 + CPU2  == 2)
#error "Core를 하나만 선택해 주세요."
#elif(CPU1 + CPU2  == 0)
#error "현재 프로그램이 무슨 코어인지 선택해 주세요."
#endif

#endif /* DUALFREQ_F28377D_CPU1_V1_02_DUALCORE_SELECT_H_ */
