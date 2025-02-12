/*
 * TIMER2_private.h
 *
 *  Created on: Oct 25, 2024
 *      Author: elwady
 */

#ifndef TIMER2_PRIVATE_H_
#define TIMER2_PRIVATE_H_

#define CTC_MODE			3
#define NORMAL_MODE			1
#define PHASE_PWM_MODE		2
#define FAST_MODE			4

#define Disconnected				1
#define Reserved	                2
#define Clear_On_COM                3
#define Set_On_COM                  4

#define Clear_COM0_Bits					0b00100000
#define Set_COM0_Bits					0b00110000
#define Toggle_COM0_Bits				0b00010000

#define DIVISION_BY_8		0b00000010

#define Overflow_Interrupt					1
#define CompareMatch_Interrupt				2

#endif /* TIMER2_PRIVATE_H_ */
