/*
 * L298N_config.h
 *
 *  Created on: Dec 3, 2024
 *      Author: elwady
 */

#ifndef L298N_CONFIG_H_
#define L298N_CONFIG_H_

#define INPUT_PORT			DIO_u8PORTB
#define INPUT1				DIO_u8PIN7
#define INPUT2				DIO_u8PIN6
#define INPUT3				DIO_u8PIN5
#define INPUT4				DIO_u8PIN4

#define PWM_PORT			DIO_u8PORTB
#define PWM_PIN				DIO_u8PIN3

#define OC0_PORT				DIO_u8PORTB
#define OC0_PIN					DIO_u8PIN3
#define PIN_STATE				DIO_u8OUTPUT

#endif /* L298N_CONFIG_H_ */
