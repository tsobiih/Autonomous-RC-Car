/*
 * L298N_interface.h
 *
 *  Created on: Dec 3, 2024
 *      Author: elwady
 */

#ifndef L298N_INTERFACE_H_
#define L298N_INTERFACE_H_

void L298N_voidInit(void);
void L298N_voidSetSpeed(u8 Copy_u8Speed);
void L298N_voidMoveForward(void);
void L298N_voidMoveBackward(void);
void L298N_voidBrake(void);
void L298N_voidFreeBrake(void);
void L298N_voidEmergencyBrake(void);

void L298N_voidTurnRight(void);
void L298N_voidTurnLeft(void);

#endif /* L298N_INTERFACE_H_ */
