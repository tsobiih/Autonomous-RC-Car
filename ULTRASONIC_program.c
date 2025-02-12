#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "UART_interface.h"
#include "DIO_interface.h"
#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_config.h"
#include "ULTRASONIC_private.h"
#include "TIMER2_interface.h"
#include "GIE_interface.h"


void ULTRASONIC_voidInit(void)
{
    // Configure Trigger pin as output
    DIO_voidSetPinDirection(US_PORT , US_F_TRIG, DIO_u8OUTPUT);
    DIO_voidSetPinDirection(US_PORT , US_L_TRIG, DIO_u8OUTPUT);
    DIO_voidSetPinDirection(US_PORT , US_R_TRIG, DIO_u8OUTPUT);

    // Configure Echo pin as input
    DIO_voidSetPinDirection(US_PORT , US_F_ECHO , DIO_u8INPUT);
    DIO_voidSetPinDirection(US_PORT , US_L_ECHO , DIO_u8INPUT);
    DIO_voidSetPinDirection(US_PORT , US_R_ECHO , DIO_u8INPUT);

    TIMER2_voidInit();
}

f32  ULTRASONIC_f32GetFrontDistance(void)
{
    f32 Distance = 0.0f;
    u32 Time = 0;
    u8 OverFlow=0;


    GIE_voidEnable();
    TIMER2_voidEnableOverFlowInterrupt();

    // Send 10탎 pulse to Trigger pin
    DIO_voidSetPinValue(US_PORT , US_F_TRIG , DIO_u8HIGH);
    _delay_us(11);
    DIO_voidSetPinValue(US_PORT , US_F_TRIG , DIO_u8LOW);

    // Wait for the Echo pin to go HIGH
    while (DIO_u8GetPinValue(US_PORT , US_F_ECHO) == DIO_u8LOW);

    TIMER2_voidResetTimer();
    TIMER2_voidResetOverFlow();

    // Measure the HIGH duration of Echo pin
    while (DIO_u8GetPinValue(US_PORT , US_F_ECHO) == DIO_u8HIGH);

    Time = TIMER2_u8ReadTimer();

    OverFlow = TIMER2_u8ReadOverFlow();

    TIMER2_voidDisableOverFlowInterrupt();
    GIE_voidDisable();

    // Calculate distance in cm
    Distance = ((Time+ (OverFlow*255.0)) * 0.0343) / 2.0;

    return Distance;
}

f32  ULTRASONIC_f32GetLeftDistance(void)
{
    f32 Distance = 0.0f;
    u32 Time = 0;
    u8 OverFlow=0;


    GIE_voidEnable();
    TIMER2_voidEnableOverFlowInterrupt();

    // Send 10탎 pulse to Trigger pin
    DIO_voidSetPinValue(US_PORT , US_L_TRIG , DIO_u8HIGH);
    _delay_us(11);
    DIO_voidSetPinValue(US_PORT , US_L_TRIG , DIO_u8LOW);

    // Wait for the Echo pin to go HIGH
    while (DIO_u8GetPinValue(US_PORT , US_L_ECHO) == DIO_u8LOW);

    TIMER2_voidResetTimer();
    TIMER2_voidResetOverFlow();

    // Measure the HIGH duration of Echo pin
    while (DIO_u8GetPinValue(US_PORT , US_L_ECHO) == DIO_u8HIGH);

    Time = TIMER2_u8ReadTimer();

    OverFlow = TIMER2_u8ReadOverFlow();

    TIMER2_voidDisableOverFlowInterrupt();
    GIE_voidDisable();

    // Calculate distance in cm
    Distance = ((Time+ (OverFlow*255.0)) * 0.0343) / 2.0;

    return Distance;
}

f32  ULTRASONIC_f32GetRightDistance(void)
{
    f32 Distance = 0.0f;
    u32 Time = 0;
    u8 OverFlow=0;


    GIE_voidEnable();
    TIMER2_voidEnableOverFlowInterrupt();

    // Send 10탎 pulse to Trigger pin
    DIO_voidSetPinValue(US_PORT , US_R_TRIG , DIO_u8HIGH);
    _delay_us(11);
    DIO_voidSetPinValue(US_PORT , US_R_TRIG , DIO_u8LOW);

    // Wait for the Echo pin to go HIGH
    while (DIO_u8GetPinValue(US_PORT , US_R_ECHO) == DIO_u8LOW);

    TIMER2_voidResetTimer();
    TIMER2_voidResetOverFlow();

    // Measure the HIGH duration of Echo pin
    while (DIO_u8GetPinValue(US_PORT , US_R_ECHO) == DIO_u8HIGH);

    Time = TIMER2_u8ReadTimer();

    OverFlow = TIMER2_u8ReadOverFlow();

    TIMER2_voidDisableOverFlowInterrupt();
    GIE_voidDisable();

    // Calculate distance in cm
    Distance = ((Time+ (OverFlow*255.0)) * 0.0343) / 2.0;

    return Distance;
}

//f32 ULTRASONIC_f32GetDistance(void)
//{
//	char str[10];
//	char ovr[10];
//    f32 Distance = 0.0f;
//    u32 Time = 0;
//    u8 OverFlow=0;
//
//
//    GIE_voidEnable();
//    TIMER0_voidEnableOverFlowInterrupt();
//
//    // Send 10탎 pulse to Trigger pin
//    DIO_voidSetPinValue(DIO_u8PORTA , DIO_u8PIN6 , DIO_u8HIGH);
//    _delay_us(11);
//    DIO_voidSetPinValue(DIO_u8PORTA , DIO_u8PIN6 , DIO_u8LOW);
//
//    // Wait for the Echo pin to go HIGH
//    while (DIO_u8GetPinValue(DIO_u8PORTA , DIO_u8PIN7) == DIO_u8LOW);
//
//    TIMER0_voidResetTimer();
//    TIMER0_voidResetOverFlow();
//
//    // Measure the HIGH duration of Echo pin
//    while (DIO_u8GetPinValue(DIO_u8PORTA , DIO_u8PIN7) == DIO_u8HIGH);
//
//    Time = TIMER0_u8ReadTimer();
//
//    OverFlow = TIMER0_u8ReadOverFlow();
//
//    TIMER0_voidDisableOverFlowInterrupt();
//    GIE_voidEnable();
//
//    sprintf(ovr , "%u" , OverFlow);
//    UART_voidSendString(ovr);
//    UART_voidSendString("\r\n");
//
//    sprintf(str , "%lu" , Time);
//    UART_voidSendString(str);
//    UART_voidSendString("\r\n");
//
//    // Calculate distance in cm
//    Distance = ((Time+ (OverFlow*255.0)) * 0.0343) / 2.0;
//
//    return Distance;
//}


