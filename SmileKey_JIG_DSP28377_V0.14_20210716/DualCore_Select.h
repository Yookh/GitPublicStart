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
#error "Core�� �ϳ��� ������ �ּ���."
#elif(CPU1 + CPU2  == 0)
#error "���� ���α׷��� ���� �ھ����� ������ �ּ���."
#endif

#endif /* DUALFREQ_F28377D_CPU1_V1_02_DUALCORE_SELECT_H_ */
