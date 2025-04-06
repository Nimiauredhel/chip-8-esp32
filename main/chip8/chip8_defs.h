#ifndef CHIP8_DEFS_H
#define CHIP8_DEFS_H

// *** VM definitions ***

// emulator constants
#define EMU_DEFAULT_STEP_DELAY_US (1666) // 500hz execution step frequency
#define EMU_SPEED_INCREMENT (0.1f)
#define EMU_MIN_SPEED_MOD (EMU_SPEED_INCREMENT) // 0 hz
#define EMU_MAX_SPEED_MOD (10.0f)
#define EMU_KEY_COUNT 17
#define CHIP8_KEY_COUNT 17

// *** CHIP-8 definitions ***

#define CHIP8_INSTRUCTION_COUNT (46)

// map of VM memory utilization up to the 0x200 program start point
// TODO: maybe tighten this up later when the sizes are stable
#define CHIP8_RAM_BYTES (4096)
#define CHIP8_RAM_SPRITES_START   (0x050) // 80 - 159, 80B
#define CHIP8_RAM_EMU_STATE_START (0x140) // 320 - 419, 100B
#define CHIP8_RAM_REGISTERS_START   (0x1BD) // 445 - 506, 62B
#define CHIP8_RAM_INSTRUCTION_START   (0x1FB) // 507 - 511, 5B parsed instruction storage
#define CHIP8_RAM_PROGRAM_START   (0x200) // 512 - 3840, 3328B
#define CHIP8_RAM_DISPLAY_START   (0xF00) // 3840 - 4095, 256B

// sprites
#define CHIP8_DEFAULT_SPRITES_COUNT (16)
#define CHIP8_DEFAULT_SPRITE_HEIGHT (5)
#define CHIP8_DEFAULT_SPRITES_SIZE (CHIP8_DEFAULT_SPRITES_COUNT * CHIP8_DEFAULT_SPRITE_HEIGHT)
#define CHIP8_DEFAULT_SPRITES_END (CHIP8_DEFAULT_SPRITES_START + CHIP8_DEFAULT_SPRITES_SIZE)

// display
#define CHIP8_DISPLAY_WIDTH (64)
#define CHIP8_DISPLAY_HEIGHT (32)
#define CHIP8_DISPLAY_ROW_BYTES (CHIP8_DISPLAY_WIDTH / 8)
#define CHIP8_DISPLAY_X_MAX (CHIP8_DISPLAY_WIDTH - 1)
#define CHIP8_DISPLAY_Y_MAX (CHIP8_DISPLAY_HEIGHT - 1)
#define CHIP8_DISPLAY_ROW_BYTE_MAX (CHIP8_DISPLAY_ROW_BYTES - 1)
#define CHIP8_DISPLAY_INDEX(x, y) (y + ((x / 8) * CHIP8_DISPLAY_HEIGHT))
#define CHIP8_DISPLAY_BYTES (CHIP8_DISPLAY_ROW_BYTES * CHIP8_DISPLAY_HEIGHT)

       // col = idx / CHIP8_DISPLAY_HEIGHT;
       // row = idx % CHIP8_DISPLAY_HEIGHT;
// super chip 48 defines are commented out for convenience
// until I actually implement super chip 48 support
/*
#define CHIP8_DISPLAY_SUPER_WIDTH 128
#define CHIP8_DISPLAY_SUPER_HEIGHT 64
#define CHIP8_DISPLAY_SUPER_X_MAX (CHIP8_DISPLAY_SUPER_WIDTH - 1)
#define CHIP8_DISPLAY_SUPER_Y_MAX (CHIP8_DISPLAY_SUPER_HEIGHT - 1)
#define CHIP8_DISPLAY_SUPER_SIZE CHIP8_DISPLAY_SUPER_WIDTH * CHIP8_DISPLAY_SUPER_HEIGHT
#define CHIP8_DISPLAY_SUPER_INDEX(x, y) (y + (x * CHIP8_DISPLAY_SUPER_HEIGHT))
*/

#endif
