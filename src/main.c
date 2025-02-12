#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include <string.h>

#include "DIO_interface.h"
#include "UART_interface.h"
#include "SERVO_interface.h"
#include "PWM_interface.h"
#include "L298N_interface.h"
#include "RC_Car_config.h"
#include "RC_Car_interface.h"
#include "TIMER0_interface.h"

u8 Global_u8Mode = 0;

int main(void)
{

	char Local_u8Mode = MANUAL_MODE;

	RC_Car_voidInit();

    while (1)
    {
    	Local_u8Mode = UART_u8ReceiveData();
    	switch (Local_u8Mode)
    	{
			case MANUAL_MODE:								//Manual Mode
				Global_u8Mode = 0;
				DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8LOW);
				_delay_ms(100);
				DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8HIGH);
				RC_Car_voidManualMode();
				break;
			case OBSTCALES_MODE:							//Obstcales mode
				Global_u8Mode = 1;
				DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8LOW);
				_delay_ms(200);
				DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8HIGH);
				RC_Car_voidObstcalesMode();
				break;
			case LINE_FOLLOWING_MODE:						//Line following mode
				Global_u8Mode = 2;
				//Line following mode function
				DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8LOW);
				_delay_ms(200);
				DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8HIGH);
				RC_Car_voidLineFollowingMode();
				break;
			default:
				UART_voidSendData('?');
				break;
		}

    }

}
