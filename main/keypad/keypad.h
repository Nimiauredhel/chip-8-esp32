/*
 * keypad.h
 *
 *  Created on: Mar 29, 2025
 *      Author: mickey
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\r\n"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

#define SHORT_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\r\n"
#define SHORT_TO_BINARY(byte)  \
  ((byte) & 0x8000 ? '1' : '0'), \
  ((byte) & 0x4000 ? '1' : '0'), \
  ((byte) & 0x2000 ? '1' : '0'), \
  ((byte) & 0x1000 ? '1' : '0'), \
  ((byte) & 0x0800 ? '1' : '0'), \
  ((byte) & 0x0400 ? '1' : '0'), \
  ((byte) & 0x0200 ? '1' : '0'), \
  ((byte) & 0x0100 ? '1' : '0'), \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

#include <stdint.h>
#include <stdbool.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

uint16_t keypad_get_state(void);

#endif /* KEYPAD_H_ */
