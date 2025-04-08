/*
 * keypad.c
 *
 *  Created on: Mar 29, 2025
 *      Author: mickey
 */

#include "keypad.h"

static const uint8_t keypad_columns[4] =
{
     GPIO_NUM_27, GPIO_NUM_14,GPIO_NUM_12, GPIO_NUM_22,   
};

static const uint8_t keypad_rows[4] =
{
    GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_3, GPIO_NUM_26,
};

static const uint8_t keypad_values[4][4] =
{
		{0x01, 0x02, 0x03, 0x0A},
		{0x04, 0x05, 0x06, 0x0B},
		{0x07, 0x08, 0x09, 0x0C},
		{0x0E, 0x00, 0x0F, 0x0D},
};

static const gpio_config_t row_config =
{
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .mode = GPIO_MODE_DEF_OUTPUT,
    .pin_bit_mask = (1ULL<<keypad_rows[0]) | (1ULL<<keypad_rows[1]) | (1ULL<<keypad_rows[2]) | (1ULL<<keypad_rows[3]),
    .intr_type = GPIO_INTR_DISABLE,

}; 

static const gpio_config_t col_config =
{
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .mode = GPIO_MODE_DEF_INPUT,
    .pin_bit_mask = (1ULL<<keypad_columns[0]) | (1ULL<<keypad_columns[1]) | (1ULL<<keypad_columns[2]) | (1ULL<<keypad_columns[3]),
    .intr_type = GPIO_INTR_DISABLE,
}; 

static bool initialized = false;

void keypad_initialize(void)
{
    ESP_ERROR_CHECK(gpio_config(&row_config));
    ESP_ERROR_CHECK(gpio_config(&col_config));

	for (uint8_t i = 0; i < 4; i++)
	{
        ESP_ERROR_CHECK(gpio_set_level(keypad_columns[i], 0));
        ESP_ERROR_CHECK(gpio_set_level(keypad_rows[i], 0));
	}
}

uint16_t keypad_get_state(void)
{
	uint16_t state = 0x0000;

    if (!initialized)
    {
        keypad_initialize();
        initialized = true;
    }

	// pull all back low
	for (uint8_t i = 0; i < 4; i++)
	{
        ESP_ERROR_CHECK(gpio_set_level(keypad_rows[i], 0));
	}

    for (uint8_t r = 0; r < 4; r++)
	{
        ESP_ERROR_CHECK(gpio_set_level(keypad_rows[r], 1));

		{
            
        for (uint8_t c = 0; c < 4; c++)
			if (gpio_get_level(keypad_columns[c]) == 1)
			{
				state |= (1U << keypad_values[r][c]);
      //          printf("Detected short of row %u and column %u, GPIO %u and %u.\n", r, c, keypad_rows[r], keypad_columns[c]);
			}
		}

        ESP_ERROR_CHECK(gpio_set_level(keypad_rows[r], 0));
	}

    /*
    if (state != 0x00)
    {
        printf("Input state: ");
        printf(SHORT_TO_BINARY_PATTERN, SHORT_TO_BINARY(state));
    }
    */

	return state;
}
