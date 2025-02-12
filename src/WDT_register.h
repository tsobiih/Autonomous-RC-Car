/*
 * WDT_register.h
 *
 *  Created on: Oct 25, 2024
 *      Author: elwady
 */

#ifndef WDT_REGISTER_H_
#define WDT_REGISTER_H_

#define WDTCR       		*((volatile u8*)(0x41))
#define MCUCSR       		*((volatile u8*)(0x54))

#endif /* WDT_REGISTER_H_ */
