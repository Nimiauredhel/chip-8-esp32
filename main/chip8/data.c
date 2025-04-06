#include "data.h"

const uint8_t chip8_default_sprites[CHIP8_DEFAULT_SPRITES_SIZE] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    0x90, 0x90, 0xF0, 0x10, 0x10,
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40,
    0xF0, 0x90, 0xF0, 0x90, 0xF0,
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,
    0xF0, 0x80, 0x80, 0x80, 0xF0,
    0xE0, 0x90, 0x90, 0x90, 0xE0,
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80
};

Chip8_t *create_instance(uint16_t *rom)
{
    printf("Initializing CHIP-8 instance.\n");
    Chip8_t *chip8 = malloc(sizeof(Chip8_t));
    explicit_bzero(chip8, sizeof(Chip8_t));

    printf("Storing %u bytes of interpreter data in the lower 512 bytes of CHIP-8 memory.\n",
            (uint32_t)(sizeof(Chip8Instruction_t) + sizeof(Chip8Registers_t) + sizeof(EmulatorState_t) + 80));
    vTaskDelay(pdMS_TO_TICKS(100));

    /*printf("The size of EmulatorState_t is %lu.\n", sizeof(EmulatorState_t));
    printf("The size of Chip8Registers_t is %lu.\n", sizeof(Chip8Registers_t));
    printf("The size of Chip8Instruction_t is %lu.\n", sizeof(Chip8Instruction_t));*/

    chip8->display_memory = (chip8->RAM + CHIP8_RAM_DISPLAY_START);
    chip8->instruction = (Chip8Instruction_t *)(chip8->RAM + CHIP8_RAM_INSTRUCTION_START);
    chip8->registers = (Chip8Registers_t *)(chip8->RAM + CHIP8_RAM_REGISTERS_START);
    chip8->emu_state = (EmulatorState_t *)(chip8->RAM + CHIP8_RAM_EMU_STATE_START);

    load_default_sprites(chip8);
    printf("Loaded default sprites.\n");
    vTaskDelay(pdMS_TO_TICKS(100));

    load_rom(rom, chip8->RAM + CHIP8_RAM_PROGRAM_START);
    chip8->registers->PC = CHIP8_RAM_PROGRAM_START;
    printf("Loaded program.\n");
    vTaskDelay(pdMS_TO_TICKS(100));

    return chip8;
}

void load_default_sprites(Chip8_t *chip8)
{
    for (uint16_t i = 0; i < CHIP8_DEFAULT_SPRITES_SIZE; i++)
    {
        chip8->RAM[CHIP8_RAM_SPRITES_START + i] = chip8_default_sprites[i];
    }
}


size_t load_rom(uint16_t *rom, uint8_t *dest_ptr)
{
	// TODO: implement size check
	// 3328 bytes is simply the accepted maximum size
	memcpy(dest_ptr, rom, 3328);
}

