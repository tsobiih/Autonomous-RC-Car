/*
 * TIMER2_interface.h
 *
 *  Created on: Oct 25, 2024
 *      Author: elwady
 */

#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

void TIMER2_voidInit(void);
void TIMER2_voidSetCompareValue(u16 Copy_u16CompareValue);
u8 	 TIMER2_u8ReadTimer(void);
void TIMER2_voidSetCallBackFunc(void (*Copy_pvCallBackFn)(void));
void TIMER2_voidResetTimer(void);
void TIMER2_voidDisableOverFlowInterrupt(void);
void TIMER2_voidEnableOverFlowInterrupt(void);
void TIMER2_voidEnableCOMInterrupt(void);
void TIMER2_voidDisableCOMInterrupt(void);
u8   TIMER2_u8ReadOverFlow(void);
void TIMER2_voidResetOverFlow(void);

#endif /* TIMER2_INTERFACE_H_ */
