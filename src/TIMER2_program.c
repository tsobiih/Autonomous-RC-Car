#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"

#include "TIMER2_config.h"
#include "TIMER2_interface.h"
#include "TIMER2_private.h"
#include "TIMER2_register.h"

static volatile u8 OverFlow=0;

void (*TIMER2_CallBackFn)(void);

void TIMER2_voidInit(void)
{
	//Select Timer mode
	#if (TIMER2_MODE == NORMAL_MODE)
		CLR_BIT(TCCR2 , 3);
		CLR_BIT(TCCR2 , 6);
	#elif (TIMER2_MODE == PHASE_PWM_MODE)
		CLR_BIT(TCCR2 , 3);
		SET_BIT(TCCR2 , 6);
	#elif (TIMER2_MODE == CTC_MODE)
		SET_BIT(TCCR2 , 3);
		CLR_BIT(TCCR2 , 6);
	#elif (TIMER2_MODE == FAST_MODE)
		SET_BIT(TCCR2 , 3);
		SET_BIT(TCCR2 , 6);
	#endif
	//Select Compare match Pin Action
	#if(COM0_MODE == Disconnected)
		{
			TCCR2 &= 0b11001111;
		}
	#elif(COM0_MODE == Reserved)
		{
			TCCR2 &= 0b11001111;
			Toggle_COM0_Bits

		}
	#elif(COM0_MODE == Clear_On_COM)
		{
			TCCR2 &= 0b11001111;
			TCCR2 |= Clear_COM0_Bits;
		}
	#elif(COM0_MODE == Set_On_COM)
		{
			TCCR2 &= 0b11001111;
			TCCR2 |= Set_COM1A_Bits;
		}
	#endif
	//Set Prescaler
	TCCR2 &=0b11111000;
	TCCR2 |= PRESCALER;
}

void TIMER2_voidSetCompareValue(u16 Copy_u16CompareValue)
{
	OCR2 = Copy_u16CompareValue;
}

void TIMER2_voidSetCallBackFunc(void (*Copy_pvCallBackFn)(void))
{
	TIMER2_CallBackFn = Copy_pvCallBackFn;
}

void TIMER2_voidResetTimer(void)
{
	TCNT2 = 0;
}

void TIMER2_voidDisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK , 6);
}

void TIMER2_voidEnableOverFlowInterrupt(void)
{
	SET_BIT(TIMSK , 6);
}

void TIMER2_voidEnableCOMInterrupt(void)
{
	SET_BIT(TIMSK , 7);
}

void TIMER2_voidDisableCOMInterrupt(void)
{
	CLR_BIT(TIMSK , 7);
}

u8   TIMER2_u8ReadOverFlow(void)
{
	return OverFlow;
}
void TIMER2_voidResetOverFlow(void)
{
	OverFlow = 0;
}

u8 	 TIMER2_u8ReadTimer(void)
{
	return TCNT2;
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	OverFlow++;
//	TIMER2_CallBackFn();
}



