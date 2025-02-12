#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "InfraRed_Interface.h"
#include "InfraRed_config.h"

void InfraRed_voidInit(void)
{
	DIO_voidSetPinDirection(IR_PORT , IR_F_PIN , DIO_u8INPUT);
	DIO_voidSetPinDirection(IR_PORT , IR_L_PIN , DIO_u8INPUT);
	DIO_voidSetPinDirection(IR_PORT , IR_R_PIN , DIO_u8INPUT);

}
u8 InfraRed_u8GetFrontRead(void)
{
	return DIO_u8GetPinValue(IR_PORT , IR_F_PIN );
}
u8 InfraRed_u8GetLeftRead(void)
{
	return DIO_u8GetPinValue(IR_PORT , IR_L_PIN );
}
u8 InfraRed_u8GetRightRead(void)
{
	return DIO_u8GetPinValue(IR_PORT , IR_R_PIN );
}
