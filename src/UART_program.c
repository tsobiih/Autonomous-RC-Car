#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_register.h"

void (*UART_CallBackFn)(void);

void UART_voidInit(void)
{
	u8 Local_8uUCSRC = 0b10000110;
	//Register Select
	SET_BIT(Local_8uUCSRC , 7);

	//Select Asynchronous mode
	CLR_BIT(Local_8uUCSRC , 6);

	//Select Parity mode Even
	CLR_BIT(Local_8uUCSRC , 5);
	CLR_BIT(Local_8uUCSRC , 4);

	//Select one Stop Bit
	CLR_BIT(Local_8uUCSRC , 3);

	//Select Character Size 8 Bits
	CLR_BIT(UCSRB , 2);
	SET_BIT(Local_8uUCSRC , 1);
	SET_BIT(Local_8uUCSRC , 2);

	UCSRC = Local_8uUCSRC;

	//Select Baud Rate
	UBRRL = 51;

	//Enable Transmitter & Receiver
	SET_BIT(UCSRB , 4);
	SET_BIT(UCSRB , 3);
}

void UART_voidSendData(u8 Copy_u8Data)
{
	while((GET_BIT(UCSRA , 5)) != 1)    //check if data register empty this bit will be 1
	{
		asm("NOP");
	}
	UDR = Copy_u8Data;
}

u8	UART_u8ReceiveData(void)
{
	while((GET_BIT(UCSRA , 7)) != 1)    //check if Receive complete this bit will be 1
	{
		asm("NOP");
	}
	return UDR;
}


void UART_voidSendString(const char *Copy_u8Data)
{
    while (*Copy_u8Data != '\0')
    {
        while ((GET_BIT(UCSRA , 5)) != 1)
        {
            asm("NOP");
        }

        UDR = *Copy_u8Data;

        Copy_u8Data++;
    }
}



void UART_u8ReceiveString(u8* Copy_u8RecievedData)
{
    u8 i = 0;
    u8 MaxSize = 30; //

    while (1)
    {
        while ((GET_BIT(UCSRA, 7)) != 1); //
        Copy_u8RecievedData[i] = UDR; //

        if (Copy_u8RecievedData[i] == '\0')
        {
            break;
        }

        i++;

        if (i >= MaxSize - 1) //
        {
            Copy_u8RecievedData[i] = '\0'; //
            break;
        }
    }
}

void UART_voidRXCompleteInteruptEnable(void)
{
	SET_BIT(UCSRB , 7);
}

u8 UART_u8CheckForData(void)
{
	u8 State = GET_BIT(UCSRA , 7);
	return State;
}

void UART_voidSetCallBack(void (*Copy_pvCallBackFn)(void))
{
	UART_CallBackFn = Copy_pvCallBackFn;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	UART_CallBackFn();
}
