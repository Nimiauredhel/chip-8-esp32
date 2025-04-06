#include "renderer.h"

#define REG8MID 64
#define REG8HIGH 128
#define REG16MID 16384
#define REG16HIGH 32768

#define REG_CONDITIONAL_COLOR_ON(reg, mid_thresh, high_thresh) \
	(memcpy(text_color, reg > mid_thresh ? reg > high_thresh ? color_red : color_yellow : color_white, 2))

#define KEY_CONDITIONAL_COLOR_ON(key) \
	(memcpy(text_color, emu_state->chip8_key_states[key] > 0 ? color_yellow : color_white, 2))

#define COLOR_OFF (memcpy(text_color, color_white, 2))

void init_display(DisplayLayout_t *layout)
{
	gfx_init(0);

	layout->window_chip8 = gfx_create_window(0, 0, 320, 160);
	layout->display_chip8 = gfx_bytes_to_binary_sprite(32, 8, NULL);
	layout->window_emu = gfx_create_window(0, 160, 320, 80);

	gfx_select_window(layout->window_chip8);
	gfx_fill_screen(color_blue);
	layout->window_chip8->state = GFXWIN_DIRTY;
	gfx_show_window(layout->window_chip8);

	gfx_show_window(layout->window_emu);
	render_summary(layout->window_emu);
}

void deinit_display(DisplayLayout_t *layout)
{
	gfx_select_window(NULL);

	gfx_hide_window(layout->window_chip8);
	gfx_hide_window(layout->window_emu);

	free(layout->window_chip8);
	layout->window_chip8 = NULL;
	free(layout->display_chip8);
	layout->display_chip8 = NULL;
	free(layout->window_emu);
	layout->window_emu = NULL;
}

void render_display(Chip8_t *chip8, WINDOW *window_chip8)
{
	gfx_bytes_to_binary_sprite_nonalloc(chip8->layout.display_chip8, 32, 8, chip8->display_memory);

	gfx_select_window(window_chip8);
	window_chip8->state = GFXWIN_WRITING;
	gfx_fill_screen(color_blue);
	gfx_draw_binary_sprite(chip8->layout.display_chip8, 0, 0, color_green, 5);
	window_chip8->state = GFXWIN_DIRTY;
}

void render_summary(WINDOW *window_summary)
{
	gfx_select_window(window_summary);
	window_summary->state = GFXWIN_WRITING;
	gfx_fill_screen(color_black);
	gfx_print_string("Mickey's CHIP-8 Emu", 8, 35, color_magenta, 2);
	window_summary->state = GFXWIN_DIRTY;
}

void render_disassembly(Chip8Instruction_t *instruction, WINDOW *window_disassembly)
{
    /*static char line_memory[16][16] = {0};
    static int8_t tail_idx = 0;
    int8_t idx = tail_idx;

    snprintf_instruction(line_memory[tail_idx], 16, instruction);
    */

	char disassembled_instruction[16] = {0};
    snprintf_instruction(disassembled_instruction, 16, instruction);

	gfx_select_window(window_disassembly);
	window_disassembly->state = GFXWIN_WRITING;
	gfx_fill_screen(color_black);
	gfx_print_string(disassembled_instruction, 0, 0, color_yellow, 3);
	//gfx_print_string(line_memory[idx], 2, 3, color_yellow, 1);

	/*
    for (uint8_t i = 1; i < 16; i++)
    {
        idx = tail_idx - i;
        if (idx < 0) idx += 16;
		gfx_print_string(line_memory[idx], 2 + (12*(i/4)), 3-(i%4), color_yellow, 1);
    }
    */

    /*
    tail_idx++;
    if (tail_idx > 15) tail_idx = 0;
    */

	window_disassembly->state = GFXWIN_DIRTY;
}

void render_registers(Chip8Registers_t *registers, WINDOW *window_registers)
{
	const uint8_t line_length_px = 128;
	const uint8_t line_height_px = 6;
    Color565_t text_color;
    char text_buffer[32];

	gfx_select_window(window_registers);
	window_registers->state = GFXWIN_WRITING;
	gfx_fill_screen(color_black);

    for (int i = 0; i < 16; i++)
    {
    	snprintf(text_buffer, 32, "V%d[%u]", i, registers->V_REGS[i]);
        REG_CONDITIONAL_COLOR_ON(registers->V_REGS[i], REG8MID, REG8HIGH);
		gfx_print_string(text_buffer, line_length_px*2, (i*line_height_px), text_color, 1);

    	snprintf(text_buffer, 32, "STACK_RET%d[%u]", i, registers->STACK_RET[i]);
        REG_CONDITIONAL_COLOR_ON(registers->STACK_RET[i], REG16MID, REG16HIGH);
		gfx_print_string(text_buffer, 0, (i*line_height_px), text_color, 1);
    }

    REG_CONDITIONAL_COLOR_ON(registers->PC, REG16MID, REG16HIGH);
	snprintf(text_buffer, 32, "PC[%u] ", registers->PC);
	gfx_print_string(text_buffer, line_length_px, 0, text_color, 1);

    REG_CONDITIONAL_COLOR_ON(registers->SP, REG8MID, REG8HIGH);
	snprintf(text_buffer, 32, "SP[%u] ", registers->PC);
	gfx_print_string(text_buffer, line_length_px, line_height_px, text_color, 1);

    REG_CONDITIONAL_COLOR_ON(registers->I_REG, REG16MID, REG16HIGH);
	snprintf(text_buffer, 32, "I[%u] ", registers->I_REG);
	gfx_print_string(text_buffer, line_length_px, line_height_px*2, text_color, 1);

    REG_CONDITIONAL_COLOR_ON(registers->DT, REG8MID, REG8HIGH);
	snprintf(text_buffer, 32, "DT[%u] ", registers->DT);
	gfx_print_string(text_buffer, line_length_px, line_height_px*3, text_color, 1);

    REG_CONDITIONAL_COLOR_ON(registers->ST, REG8MID, REG8HIGH);
	snprintf(text_buffer, 32, "ST[%u] ", registers->ST);
	gfx_print_string(text_buffer, line_length_px, line_height_px*4, text_color, 1);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
			REG_CONDITIONAL_COLOR_ON(registers->EMU_TEMP[i].bytes[j], REG8MID, REG8HIGH);
			snprintf(text_buffer, 32, "TEMP%u_BYTE%u[%u] ", i, j, registers->EMU_TEMP[i].bytes[j]);
			gfx_print_string(text_buffer, line_length_px, ((i+2)*line_height_px*3) + (j*line_height_px), text_color, 1);
        }

		REG_CONDITIONAL_COLOR_ON(registers->EMU_TEMP[i].word, REG16MID, REG16HIGH);
		snprintf(text_buffer, 32, "TEMP%u_WORD[%u] ", i, registers->EMU_TEMP[i].word);
		gfx_print_string(text_buffer, line_length_px, ((i+2)*line_height_px*3) + (line_height_px*2), text_color, 1);
    }

	window_registers->state = GFXWIN_DIRTY;
}

void render_emulator_state(EmulatorState_t *emu_state, WINDOW *window_emu)
{
	const uint8_t line_length_px = 56;
	const uint8_t line_height_px = 10;
    Color565_t text_color;
    char text_buffer[32];

    COLOR_OFF;

	gfx_select_window(window_emu);
	window_emu->state = GFXWIN_WRITING;
	gfx_fill_screen(color_black);

    snprintf(text_buffer, 32, "Speed[%.2f]", emu_state->speed_modifier);
    gfx_print_string(text_buffer, 0, 0, text_color, 1);

    snprintf(text_buffer, 32, "Step Counter[%u]", emu_state->step_counter);
    gfx_print_string(text_buffer, 0, line_height_px, text_color, 1);

    snprintf(text_buffer, 32, "Runtime[%.2fs]", emu_state->runtime_seconds_counter);
    gfx_print_string(text_buffer, 0, line_height_px*2, text_color, 1);

    snprintf(text_buffer, 32, "Avg. FPS[%.2f]", emu_state->avg_cps);
    gfx_print_string(text_buffer, 0, line_height_px*3, text_color, 1);

    for (int i = 0; i < CHIP8_KEY_COUNT; i++)
    {
        KEY_CONDITIONAL_COLOR_ON(i);
        snprintf(text_buffer, 32, "%s[%u] ", chip8_key_names[i], emu_state->chip8_key_states[i]);
        gfx_print_string(text_buffer, (i/4) * (line_length_px), (line_height_px*(i%4))+(line_height_px*4), text_color, 1);
    }

	window_emu->state = GFXWIN_DIRTY;
}
