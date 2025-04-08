#include "input.h"

const char chip8_key_names[CHIP8_KEY_COUNT][4] =
{ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "Any" };

const char emu_key_names[EMU_KEY_COUNT][10] =
{ "Quit", "Reset", "Speed +", "Speed -", "Step Mode", "Step One", "Any" };

static bool initialized = false;

static void initialize_input(void)
{
    gpio_config_t alt_config =
    {
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .mode = GPIO_MODE_DEF_OUTPUT,
        .pin_bit_mask = 1 << EMU_ALTSWITCH_GPIO_OUT,
        .intr_type = GPIO_INTR_DISABLE,
    }; 

    ESP_ERROR_CHECK(gpio_config(&alt_config));

    alt_config.mode = GPIO_MODE_DEF_INPUT;
    alt_config.pin_bit_mask = 1 << EMU_ALTSWITCH_GPIO_IN;
    alt_config.pull_down_en = GPIO_PULLDOWN_ENABLE;

    ESP_ERROR_CHECK(gpio_config(&alt_config));

    gpio_set_level(EMU_ALTSWITCH_GPIO_OUT, 1);

    initialized = true;
}

void read_input(uint16_t *emu_key_states, uint16_t *chip8_key_states)
{
#define REGISTER_EMU_KEY_DOWN(key)\
	emu_key_states[key] = EMU_INPUT_BUFFER_CYCLES;\
	emu_key_states[EMU_KEY_ANY_IDX] = EMU_INPUT_BUFFER_CYCLES
#define REGISTER_CHIP8_KEY_DOWN(key)\
	chip8_key_states[key] = CHIP8_INPUT_BUFFER_CYCLES;\
	chip8_key_states[CHIP8_KEY_ANY_IDX] = CHIP8_INPUT_BUFFER_CYCLES

    if (!initialized)
    {
        initialize_input();
    }

    uint8_t idx;
    volatile uint16_t key_state_current = keypad_get_state();
    volatile bool emu_input = gpio_get_level(EMU_ALTSWITCH_GPIO_IN);

	for (idx = 0; idx < EMU_KEY_COUNT; idx++)
	{
		if (emu_input && (key_state_current & (1U << idx)))
		{
			REGISTER_EMU_KEY_DOWN(idx);
		}
		else if (emu_key_states[idx] > 0)
            emu_key_states[idx] -= 1;
	}

	for (idx = 0; idx < CHIP8_KEY_COUNT; idx++)
	{
		if (!emu_input && (key_state_current & (1U << idx)))
		{
			REGISTER_CHIP8_KEY_DOWN(idx);
		}
		else if (chip8_key_states[idx] > 0)
            chip8_key_states[idx] -= 1;
	}
#undef REGISTER_EMU_KEY_DOWN
#undef REGISTER_CHIP8_KEY_DOWREGSN
}

bool check_input(uint16_t *key_states, uint8_t key_idx)
{
    bool result = key_states[key_idx] > 0;
    return result;
}

uint16_t check_input_buffer(uint16_t *key_states, uint8_t key_idx)
{
    uint8_t result = key_states[key_idx];
    return result;
}
