/*
 * SERVO_program.c
 *
 *  Created on: Oct 18, 2024
 *      Author: elwady
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "PWM_interface.h"

#include "SERVO_config.h"
#include "SERVO_interface.h"
#include "SERVO_private.h"


void SERVO_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_u8PORTD , ChannelA , DIO_u8OUTPUT);

	PWM_voidInit();

	PWM_voidSetTopValue(20000);
}

void SERVO_voidSetPosition(u8 Copy_u8Position)
{
	u16 Local_u16CompareValueA = 500 + (Copy_u8Position * (190/18));
	PWM_voidSetCompareValue(Local_u16CompareValueA , 0);
	_delay_ms(500);
}
