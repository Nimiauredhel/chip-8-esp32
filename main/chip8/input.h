#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "data.h"
#include "keypad.h"
#include "driver/gpio.h"

#define MAX_SIMULTANEOUS_KEYS 16
#define CHIP8_INPUT_BUFFER_CYCLES (128)
#define EMU_INPUT_BUFFER_CYCLES (2)

#define EMU_ALTSWITCH_GPIO_OUT 19
#define EMU_ALTSWITCH_GPIO_IN 21

typedef enum Chip8KeyIndex
{
    CHIP8_KEY_0_IDX = 0,
    CHIP8_KEY_1_IDX = 1,
    CHIP8_KEY_2_IDX = 2,
    CHIP8_KEY_3_IDX = 3,
    CHIP8_KEY_4_IDX = 4,
    CHIP8_KEY_5_IDX = 5,
    CHIP8_KEY_6_IDX = 6,
    CHIP8_KEY_7_IDX = 7,
    CHIP8_KEY_8_IDX = 8,
    CHIP8_KEY_9_IDX = 9,
    CHIP8_KEY_A_IDX = 10,
    CHIP8_KEY_B_IDX = 11,
    CHIP8_KEY_C_IDX = 12,
    CHIP8_KEY_D_IDX = 13,
    CHIP8_KEY_E_IDX = 14,
    CHIP8_KEY_F_IDX = 15,
    CHIP8_KEY_ANY_IDX = 16,
} Chip8KeyIndex_t;

typedef enum EmuKeyIndex
{
    EMU_KEY_QUIT_IDX = 0xC,
    EMU_KEY_RESET_IDX = 0xD,
    EMU_KEY_SPEED_UP_IDX = 0xB,
    EMU_KEY_SPEED_DOWN_IDX = 0xA,
    EMU_KEY_STEP_MODE_IDX = 0xE,
    EMU_KEY_STEP_ONE_IDX = 0xF,
    EMU_KEY_SHOW_STATE_IDX = 0x7,
    EMU_KEY_SHOW_REGS_IDX = 0x8,
    EMU_KEY_SHOW_DISASS_IDX = 0x9,
    EMU_KEY_SHOW_SUMMARY_IDX = 0x0,
    EMU_KEY_ANY_IDX = 16,
} EmuKeyIndex_t;

void read_input(uint16_t *emu_key_states, uint16_t *chip8_key_states);
uint16_t check_input_buffer(uint16_t *key_states, uint8_t key_idx);
bool check_input(uint16_t *key_states, uint8_t key_idx);

extern const char chip8_key_names[CHIP8_KEY_COUNT][4];
extern const char emu_key_names[EMU_KEY_COUNT][10];

#endif
