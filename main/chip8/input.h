#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "data.h"
#include "keypad.h"
#include "driver/gpio.h"

#define MAX_SIMULTANEOUS_KEYS 16
#define CHIP8_INPUT_BUFFER_CYCLES (64)
#define EMU_INPUT_BUFFER_CYCLES (2)

#define EMU_ALTSWITCH_GPIO_OUT 19
#define EMU_ALTSWITCH_GPIO_IN 21

typedef enum Chip8KeyIndex
{
    CHIP8_KEY_0_IDX = 0x00,
    CHIP8_KEY_1_IDX = 0x01,
    CHIP8_KEY_2_IDX = 0x02,
    CHIP8_KEY_3_IDX = 0x03,
    CHIP8_KEY_4_IDX = 0x04,
    CHIP8_KEY_5_IDX = 0x05,
    CHIP8_KEY_6_IDX = 0x06,
    CHIP8_KEY_7_IDX = 0x07,
    CHIP8_KEY_8_IDX = 0x08,
    CHIP8_KEY_9_IDX = 0x09,
    CHIP8_KEY_A_IDX = 0x0A,
    CHIP8_KEY_B_IDX = 0x0B,
    CHIP8_KEY_C_IDX = 0x0C,
    CHIP8_KEY_D_IDX = 0x0D,
    CHIP8_KEY_E_IDX = 0x0E,
    CHIP8_KEY_F_IDX = 0x0F,
    CHIP8_KEY_ANY_IDX = 0x10,
} Chip8KeyIndex_t;

typedef enum EmuKeyIndex
{
    EMU_KEY_QUIT_IDX = 0x0C,
    EMU_KEY_RESET_IDX = 0x0D,
    EMU_KEY_SPEED_UP_IDX = 0x0B,
    EMU_KEY_SPEED_DOWN_IDX = 0x0A,
    EMU_KEY_STEP_MODE_IDX = 0x0E,
    EMU_KEY_STEP_ONE_IDX = 0x0F,
    EMU_KEY_SHOW_STATE_IDX = 0x07,
    EMU_KEY_SHOW_REGS_IDX = 0x08,
    EMU_KEY_SHOW_DISASS_IDX = 0x09,
    EMU_KEY_SHOW_SUMMARY_IDX = 0x00,
    EMU_KEY_ANY_IDX = 0x10,
} EmuKeyIndex_t;

void read_input(uint16_t *emu_key_states, uint16_t *chip8_key_states);
uint16_t check_input_buffer(uint16_t *key_states, uint8_t key_idx);
bool check_input(uint16_t *key_states, uint8_t key_idx);

extern const char chip8_key_names[CHIP8_KEY_COUNT][4];
extern const char emu_key_names[EMU_KEY_COUNT][10];

#endif
