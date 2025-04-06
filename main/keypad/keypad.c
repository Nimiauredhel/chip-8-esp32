/*
 * keypad.c
 *
 *  Created on: Mar 29, 2025
 *      Author: mickey
 */

#include "keypad.h"

static const uint8_t keypad_columns[4] =
{
    25, 26, 27, 14,

};

static const uint8_t keypad_rows[4] =
{
    34, 35, 32, 33,
};

static const uint8_t keypad_values[4][4] =
{
		{0x1, 0x2, 0x3, 0xA},
		{0x4, 0x5, 0x6, 0xB},
		{0x7, 0x8, 0x9, 0xC},
		{0xE, 0x0, 0xF, 0xD},
};

static const gpio_config_t row_config =
{
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .mode = GPIO_MODE_DEF_INPUT,
    .pin_bit_mask = keypad_rows[0] | keypad_rows[1] | keypad_rows[2] | keypad_rows[3],

}; 

static const gpio_config_t col_config =
{
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .mode = GPIO_MODE_DEF_OUTPUT,
    .pin_bit_mask = keypad_columns[0] | keypad_columns[1] | keypad_columns[2] | keypad_columns[3],
}; 

static bool initialized = false;

void keypad_initialize(void)
{
    gpio_config(&row_config);
    gpio_config(&col_config);
}

uint16_t keypad_get_state(void)
{
	uint8_t i;
	uint16_t state = 0x0000;

    if (!initialized)
    {
        keypad_initialize();
        initialized = true;
    }

	// pull all back low
	for (i = 0; i < 4; i++)
	{
        gpio_set_level(keypad_columns[i], 0);
	}

	for (uint8_t c = 0; c < 4; c++)
	{
        gpio_set_level(keypad_columns[c], 1);

		for (uint8_t r = 0; r < 4; r++)
		{
            
			if (gpio_get_level(keypad_rows[r]))
			{
				state |= (1 << keypad_values[r][c]);
			}
		}

        gpio_set_level(keypad_columns[c], 0);
	}

	return state;
}
