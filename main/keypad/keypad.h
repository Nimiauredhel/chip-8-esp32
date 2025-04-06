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

#include "driver/gpio.h"

void keypad_initialize(void);
uint16_t keypad_get_state(void);

#endif /* KEYPAD_H_ */
