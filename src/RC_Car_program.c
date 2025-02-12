#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "DIO_interface.h"
#include "UART_interface.h"
#include "SERVO_interface.h"
#include "PWM_interface.h"
#include "L298N_interface.h"
#include "RC_Car_config.h"
#include "RC_Car_interface.h"
#include "TIMER0_interface.h"
#include "ULTRASONIC_interface.h"
#include "WDT_interface.h"
#include "InfraRed_Interface.h"
#include "GIE_interface.h"


void RC_Car_voidInit(void)
{
	//Init UART pins
	DIO_voidSetPinDirection(UART_PORT , RX_PIN , DIO_u8INPUT);
	DIO_voidSetPinDirection(UART_PORT , TX_PIN , DIO_u8OUTPUT);

	//Init Led PIN
	DIO_voidSetPinDirection(DIO_u8PORTB , DIO_u8PIN2 , DIO_u8OUTPUT);

	//Init buzzer pin
	DIO_voidSetPinDirection(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8OUTPUT);
	DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8HIGH);

	SERVO_voidInit();	//Init the servo
	UART_voidInit();	//Init UART
	L298N_voidInit();   //Init Motor driver

}

void RC_Car_voidLineFollowingMode(void)
{
	u8 Local_u8Switch;
	u8 Local_u8Speed = 5;
	u8 Buffer_State=0;

	u8 Local_u8Middle;
	u8 Local_u8Left;
	u8 Local_u8Right;

	u8 CompinedReading;
	//Set motor speed to suitable speed
	L298N_voidSetSpeed(Local_u8Speed);

	//Set Wheels position
	SERVO_voidSetPosition(STRAIGHT_ANGLE);

	//init ir sensors
	InfraRed_voidInit();

	while(Global_u8Mode == 2)
	{
		Buffer_State = UART_u8CheckForData();
		if(Buffer_State == 1)
		{
			//get input from Smart Phone
			Local_u8Switch = UART_u8ReceiveData();

			// To modify speed according to input
			if(Local_u8Switch >= '0' && Local_u8Switch <= '9')
			{
				//convert from "ASCI" to "int"
				Local_u8Speed = Local_u8Switch - '0';
				L298N_voidSetSpeed(Local_u8Speed);
			}
			else
			{
				switch (Local_u8Switch)
				{
					case TOP_SPEED:                   //to set speed to max
						L298N_voidSetSpeed(MAX_SPEED);
						break;
					case MANUAL_MODE:  					//to exit the mode
						UART_voidSendString("Exit line following mode");
						Global_u8Mode = 0;
						break;
					case OBSTCALES_MODE:					//to exit the mode
						UART_voidSendString("Exit line following mode");
						Global_u8Mode = 2;
						break;
					default:
						break;
				}
			}
		}
    	//Get sensors readings
    	Local_u8Middle = InfraRed_u8GetFrontRead();
    	Local_u8Left = InfraRed_u8GetLeftRead();
    	Local_u8Right = InfraRed_u8GetRightRead();

    	//Compine values in one pinary number
    	CompinedReading = (Local_u8Left << 2) | (Local_u8Middle << 1) | Local_u8Right;

    	switch (CompinedReading)
    	{
			case 000:
				break;
			case 010:
				break;
			case 110:
				break;
			case 011:
				break;
			case 100:
				break;
			case 001:
				break;
			case 101:
				break;
			case 111:
				break;
			default:
				break;
		}
	}
}


void RC_Car_voidManualMode(void)
{
	u8 Local_u8Switch;
	u8 Local_u8Speed = 5;

	//Set speed to suitable speed
	L298N_voidSetSpeed(Local_u8Speed);

	//set position of the wheels
	SERVO_voidSetPosition(STRAIGHT_ANGLE);

	 while (Global_u8Mode == 0)
	    {
		 	 //Read data from smart phone
	    	Local_u8Switch = UART_u8ReceiveData();

	    	// if condition for speed variation
	    	if(Local_u8Switch >= '0' && Local_u8Switch <= '9')
	    	{
	    		//convert from "ASCI" to int
	    		Local_u8Speed = Local_u8Switch - '0';
	    		L298N_voidSetSpeed(Local_u8Speed);
	    	}
	    	else
	    	{
				switch (Local_u8Switch)
				{
					case 'q':
						L298N_voidSetSpeed(10);
						break;
					case 'F':		//Moving Forward
						SERVO_voidSetPosition(STRAIGHT_ANGLE);
						L298N_voidSetSpeed(Local_u8Speed);
						L298N_voidMoveForward();
						break;
					case 'B':		//Moving backward
						SERVO_voidSetPosition(65);
						L298N_voidSetSpeed(Local_u8Speed);
						L298N_voidMoveBackward();
						break;
					case 'R':		//turn wheels right
						L298N_voidSetSpeed(0);
						SERVO_voidSetPosition(110);
						break;
					case 'L':		//turn wheels left
						L298N_voidSetSpeed(0);
						SERVO_voidSetPosition(20);
						break;
					case 'G':		//moving left forward
						L298N_voidSetSpeed(Local_u8Speed);
						SERVO_voidSetPosition(LEFT_TURN_ANGLE);
						L298N_voidMoveForward();
						break;
					case 'I':		//moving right forward
						L298N_voidSetSpeed(Local_u8Speed);
						SERVO_voidSetPosition(RIGHT_TURN_ANGLE);
						L298N_voidMoveForward();
						break;
					case 'H':		//moving left backward
						L298N_voidSetSpeed(Local_u8Speed);
						SERVO_voidSetPosition(LEFT_TURN_ANGLE);
						L298N_voidMoveBackward();
						break;
					case 'J':		//moving right backward
						L298N_voidSetSpeed(Local_u8Speed);
						SERVO_voidSetPosition(RIGHT_TURN_ANGLE);
						L298N_voidMoveBackward();
						break;
					case 'S':			//stop and return wheels straight
						SERVO_voidSetPosition(STRAIGHT_ANGLE);
						L298N_voidBrake();
						break;
					case 'W':			//Led on
						DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN2 , DIO_u8HIGH);
						break;
					case 'w':			//led off
						DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN2 , DIO_u8LOW);
						break;
					case 'V':			//buzzer on
						DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8LOW);
						break;
					case 'v':		//buzzer off
						DIO_voidSetPinValue(DIO_u8PORTB , DIO_u8PIN1 , DIO_u8HIGH);
						break;
					default:		//to exit the mode
						if (Local_u8Switch == 'N') Global_u8Mode = 1;
						if (Local_u8Switch == '@') Global_u8Mode = 2;
						break;
				}
	    	}
	    }
}




void RC_Car_voidObstcalesMode(void)
{
	u8 Local_u8Switch;
	u8 Local_u8Speed = 8;
	u8 Buffer_State=0;

	f32 Local_f32FrontDistance;
	f32 Local_f32LeftDistance;
	f32 Local_f32RightDistance;

	//Set motor speed to suitable speed
	L298N_voidSetSpeed(Local_u8Speed);

	//Set Wheels position
	SERVO_voidSetPosition(STRAIGHT_ANGLE);

	//Init ultrasonic sensors
	ULTRASONIC_voidInit();

	while(Global_u8Mode == 1)
	{
		//Check if there new data in UART buffer
		Buffer_State = UART_u8CheckForData();

		if (Buffer_State == 1)
		{
			//get input from Smart Phone
			Local_u8Switch = UART_u8ReceiveData();

			// To modify speed according to input
			if(Local_u8Switch >= '0' && Local_u8Switch <= '9')
			{
				//convert from "ASCI" to "int"
				Local_u8Speed = Local_u8Switch - '0';
				L298N_voidSetSpeed(Local_u8Speed);
			}
			else
			{
				switch (Local_u8Switch)
				{
					case TOP_SPEED :                   //to set speed to max
						L298N_voidSetSpeed(MAX_SPEED);
						break;
					case MANUAL_MODE:  					//to exit the mode
						UART_voidSendString("Exit obstacles mode");
						Global_u8Mode = 0;
						break;
					case LINE_FOLLOWING_MODE:					//to exit the mode
						UART_voidSendString("Exit obstacles mode");
						Global_u8Mode = 2;
						break;
					default:
						break;
				}
			}
		}
    	//get front distance
    	Local_f32FrontDistance = ULTRASONIC_f32GetFrontDistance();
    	_delay_ms(20);		//wait sensor to read

    	if (Local_f32FrontDistance > MIN_DISTANCE)	//minimum distance is 10cm
    	{
			L298N_voidMoveForward();
			while (Local_f32FrontDistance > MIN_DISTANCE)
			{
				//update sensor reading while moving
				Local_f32FrontDistance = ULTRASONIC_f32GetFrontDistance();
				_delay_ms(20);
			}
			L298N_voidBrake();
			UART_voidSendData('!');	//test Character
		}
    	else
    	{
    		L298N_voidBrake();

    		//get left distance
    		Local_f32LeftDistance = ULTRASONIC_f32GetLeftDistance();
    		_delay_ms(20);		//wait sensor to read

    		//get right distance
    		Local_f32RightDistance = ULTRASONIC_f32GetRightDistance();
    		_delay_ms(20);		//wait sensor to read

    		while(Local_f32FrontDistance < SAFE_DISTANCE)
    		{
    			L298N_voidMoveBackward();
    			Local_f32FrontDistance = ULTRASONIC_f32GetFrontDistance();
    			_delay_ms(20);
    		}
    		L298N_voidBrake();
    		UART_voidSendData('@'); //test character

    		if(Local_f32LeftDistance > Local_f32RightDistance)
    		{
    			//To turn the wheels left
    			L298N_voidTurnLeft();
    		}
    		else
    		{
    			//to teurn the wheels to right
    			L298N_voidTurnRight();
    		}
    		UART_voidSendData('#'); //test character
    	}
	}
}


//void RC_Car_voidObstcalesMode(void)
//{
//	u8 Local_u8Speed = 8;
//
//	f32 Local_f32FrontDistance;
//	f32 Local_f32LeftDistance;
//	f32 Local_f32RightDistance;
//
//	//Set motor speed to suitable speed
//	L298N_voidSetSpeed(Local_u8Speed);
//
//	//Set Wheels position
//	SERVO_voidSetPosition(STRAIGHT_ANGLE);
//
//	UART_voidRXCompleteInteruptEnable();
//	GIE_voidEnable();
//
//	UART_voidSetCallBack(UpdateMotorData);
//	//Init ultrasonic sensors
//	ULTRASONIC_voidInit();
//	UART_voidSendData('L'); //test character
//	while(Global_u8Mode == 1)
//	{
//    	//get front distance
//    	Local_f32FrontDistance = ULTRASONIC_f32GetFrontDistance();
//    	_delay_ms(20);		//wait sensor to read
//
//    	if (Local_f32FrontDistance > MIN_DISTANCE)	//minimum distance is 10cm
//    	{
//			while (Local_f32FrontDistance > MIN_DISTANCE)
//			{
//				L298N_voidMoveForward();
//				//update sensor reading while moving
//				Local_f32FrontDistance = ULTRASONIC_f32GetFrontDistance();
//				_delay_ms(20);
//			}
//			L298N_voidBrake();
//			UART_voidSendData('!');	//test Character
//		}
//    	else
//    	{
//    		L298N_voidBrake();
//
//    		//get left distance
//    		Local_f32LeftDistance = ULTRASONIC_f32GetLeftDistance();
//    		_delay_ms(20);		//wait sensor to read
//
//    		//get right distance
//    		Local_f32RightDistance = ULTRASONIC_f32GetRightDistance();
//    		_delay_ms(20);		//wait sensor to read
//
//    		while(Local_f32FrontDistance < SAFE_DISTANCE)
//    		{
//    			L298N_voidMoveBackward();
//    			Local_f32FrontDistance = ULTRASONIC_f32GetFrontDistance();
//    			_delay_ms(20);
//    		}
//
//    		L298N_voidBrake();
//    		UART_voidSendData('@'); //test character
//
//    		if(Local_f32LeftDistance > Local_f32RightDistance)
//    		{
//    			//To turn the wheels left
//    			L298N_voidTurnLeft();
//    		}
//    		else
//    		{
//    			//to teurn the wheels to right
//    			L298N_voidTurnRight();
//    		}
//    		UART_voidSendData('#'); //test character
//    	}
//	}
//}
