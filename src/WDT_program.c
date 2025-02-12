#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_config.h"
#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_register.h"


void WDT_voidInit(void)
{
	//Enable WDT
	SET_BIT(WDTCR , 3);

	//Set prescaler
	WDTCR &= 0b11111000;
	WDTCR |= PRESCALER;
}


void WDT_voidEnable(void)
{
	SET_BIT(WDTCR , 3);
}


void WDT_voidDisable(void)
{
	SET_BIT(WDTCR , 4);
	CLR_BIT(WDTCR , 3);
}

void WDT_voidReset(void)
{
	__asm__ __volatile__ ("wdr");
}
