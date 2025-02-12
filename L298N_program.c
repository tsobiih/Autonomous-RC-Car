#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "TIMER0_interface.h"

#include "SERVO_interface.h"
#include "L298N_config.h"
#include "L298N_interface.h"
#include "L298N_private.h"
#include "RC_Car_config.h"

void L298N_voidInit(void)
{
	//MOTOR PINS
	DIO_voidSetPinDirection(INPUT_PORT , INPUT1 , DIO_u8OUTPUT);
	DIO_voidSetPinDirection(INPUT_PORT , INPUT2 , DIO_u8OUTPUT);
	DIO_voidSetPinDirection(INPUT_PORT , INPUT3 , DIO_u8OUTPUT);
	DIO_voidSetPinDirection(INPUT_PORT , INPUT4 , DIO_u8OUTPUT);

	//PWM PIN
	DIO_voidSetPinDirection(OC0_PORT , OC0_PIN , PIN_STATE);

	TIMER0_voidInit();
}
void L298N_voidSetSpeed(u8 Copy_u8Speed)
{
    u8 i = (Copy_u8Speed * 255) / 10;
    TIMER0_voidSetCompareValue(i);
}

void L298N_voidMoveForward(void)
{

	DIO_voidSetPinValue(INPUT_PORT , INPUT1 , DIO_u8HIGH);
	DIO_voidSetPinValue(INPUT_PORT , INPUT2 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT3 , DIO_u8HIGH);
	DIO_voidSetPinValue(INPUT_PORT , INPUT4 , DIO_u8LOW);

}
void L298N_voidMoveBackward(void)
{
	DIO_voidSetPinValue(INPUT_PORT , INPUT1 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT2 , DIO_u8HIGH);
	DIO_voidSetPinValue(INPUT_PORT , INPUT3 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT4 , DIO_u8HIGH);
}
void L298N_voidBrake(void)
{
	DIO_voidSetPinValue(INPUT_PORT , INPUT1 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT2 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT3 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT4 , DIO_u8LOW);

}
void L298N_voidFreeBrake(void)
{
	L298N_voidSetSpeed(0);
}
void L298N_voidEmergencyBrake(void)
{

}

void L298N_voidTurnLeft(void)
{
	SERVO_voidSetPosition(LEFT_TURN_ANGLE);
	L298N_voidSetSpeed(10);
	DIO_voidSetPinValue(INPUT_PORT , INPUT1 , DIO_u8HIGH);
	DIO_voidSetPinValue(INPUT_PORT , INPUT2 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT3 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT4 , DIO_u8LOW);
	_delay_ms(750);
	L298N_voidBrake();
	SERVO_voidSetPosition(STRAIGHT_ANGLE);
	L298N_voidSetSpeed(8);
}

void L298N_voidTurnRight(void)
{
	SERVO_voidSetPosition(RIGHT_TURN_ANGLE);
	L298N_voidSetSpeed(10);
	DIO_voidSetPinValue(INPUT_PORT , INPUT1 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT2 , DIO_u8LOW);
	DIO_voidSetPinValue(INPUT_PORT , INPUT3 , DIO_u8HIGH);
	DIO_voidSetPinValue(INPUT_PORT , INPUT4 , DIO_u8LOW);
	_delay_ms(750);
	L298N_voidBrake();
	SERVO_voidSetPosition(STRAIGHT_ANGLE);
	L298N_voidSetSpeed(8);
}

