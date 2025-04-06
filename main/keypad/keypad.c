/*
 * keypad.c
 *
 *  Created on: Mar 29, 2025
 *      Author: mickey
 */

#include "keypad.h"

KeypadGPIO_t keypad_columns[4] =
{
		{ .pin = KEYPAD_C1_Pin, .port = KEYPAD_C1_GPIO_Port },
		{ .pin = KEYPAD_C2_Pin, .port = KEYPAD_C2_GPIO_Port },
		{ .pin = KEYPAD_C3_Pin, .port = KEYPAD_C3_GPIO_Port },
		{ .pin = KEYPAD_C4_Pin, .port = KEYPAD_C4_GPIO_Port },
};

KeypadGPIO_t keypad_rows[4] =
{
		{ .pin = KEYPAD_R1_Pin, .port = KEYPAD_R1_GPIO_Port },
		{ .pin = KEYPAD_R2_Pin, .port = KEYPAD_R2_GPIO_Port },
		{ .pin = KEYPAD_R3_Pin, .port = KEYPAD_R3_GPIO_Port },
		{ .pin = KEYPAD_R4_Pin, .port = KEYPAD_R4_GPIO_Port },
};

uint8_t keypad_values[4][4] =
{
		{0x1, 0x2, 0x3, 0xA},
		{0x4, 0x5, 0x6, 0xB},
		{0x7, 0x8, 0x9, 0xC},
		{0xE, 0x0, 0xF, 0xD},
};

uint16_t keypad_get_state(void)
{
	uint8_t i;
	uint16_t state = 0x0000;

	// pull all back low
	for (i = 0; i < 4; i++)
	{
		HAL_GPIO_WritePin(keypad_columns[i].port, keypad_columns[i].pin, GPIO_PIN_RESET);
	}

	for (uint8_t c = 0; c < 4; c++)
	{
		HAL_GPIO_WritePin(keypad_columns[c].port, keypad_columns[c].pin, GPIO_PIN_SET);

		for (uint8_t r = 0; r < 4; r++)
		{
			if (HAL_GPIO_ReadPin(keypad_rows[r].port, keypad_rows[r].pin))
			{
				state |= (1 << keypad_values[r][c]);
			}
		}

		HAL_GPIO_WritePin(keypad_columns[c].port, keypad_columns[c].pin, GPIO_PIN_RESET);
	}

	// pull all back low
	for (i = 0; i < 4; i++)
	{
		HAL_GPIO_WritePin(keypad_rows[i].port, keypad_rows[i].pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(keypad_columns[i].port, keypad_columns[i].pin, GPIO_PIN_RESET);
	}
	return state;
}
