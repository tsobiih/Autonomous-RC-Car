/*
 * WDT_interface.h
 *
 *  Created on: Oct 25, 2024
 *      Author: elwady
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#define wdr()  __asm__ __volatile__ ("wdr")

void WDT_voidInit(void);
void WDT_voidEnable(void);
void WDT_voidDisable(void);
void WDT_voidReset(void);

#endif /* WDT_INTERFACE_H_ */
