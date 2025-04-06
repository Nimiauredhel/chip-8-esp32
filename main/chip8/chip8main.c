#include "chip8main.h"

int chip8start(void)
{
	int16_t rom_index = 0;

    bool reset = false;

    for(;;)
    {
		Chip8_t *chip8 = create_instance(chip8_programs[rom_index]);
		bool reset = run(chip8);
		free(chip8);

		should_terminate = false;

    	if (!reset)
    	{
			rom_index++;
			if (rom_index > CHIP_8_PROGRAM_COUNT) rom_index = 0;
    	}
    }

    return EXIT_SUCCESS;
}
