/*
 * keypad.h
 *
 *  Created on: Mar 29, 2025
 *      Author: mickey
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include <stdbool.h>

uint16_t keypad_get_state(void);

typedef struct KeypadGPIO
{
	GPIO_TypeDef *port;
	uint16_t pin;
} KeypadGPIO_t;

#endif /* KEYPAD_H_ */
