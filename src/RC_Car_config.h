/*
 * RC_Car_Manual_config.h
 *
 *  Created on: Dec 7, 2024
 *      Author: elwady
 */

#ifndef RC_CAR_CONFIG_H_
#define RC_CAR_CONFIG_H_

#define UART_PORT			DIO_u8PORTD
#define RX_PIN				DIO_u8PIN0
#define TX_PIN				DIO_u8PIN1

#define MAX_SPEED 10
#define MIN_DISTANCE 15.0
#define SAFE_DISTANCE 20.0
#define LEFT_TURN_ANGLE 20
#define RIGHT_TURN_ANGLE 110
#define STRAIGHT_ANGLE 65

#define MANUAL_MODE					'K'
#define OBSTCALES_MODE				'N'
#define LINE_FOLLOWING_MODE			'@'
#define TOP_SPEED					'q'

extern u8 Global_u8Mode;


#endif /* RC_CAR_CONFIG_H_ */
