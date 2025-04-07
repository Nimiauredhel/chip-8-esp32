/*
 * app.c
 *
 *  Created on: Mar 29, 2025
 *      Author: mickey
 */

#include "app.h"

const uint8_t hello_bytes[25] =
{
		0b10001000, // H
		0b10001000,
		0b11111000,
		0b10001000,
		0b10001000,
		0b11111000, // E
		0b10000000,
		0b11111000,
		0b10000000,
		0b11111000,
		0b10000000, // L
		0b10000000,
		0b10000000,
		0b10000000,
		0b11111000,
		0b10000000, // L
		0b10000000,
		0b10000000,
		0b10000000,
		0b11111000,
		0b11111000, // O
		0b10001000,
		0b10001000,
		0b10001000,
		0b11111000,
};

const uint8_t world_bytes[25] =
{
		0b10001000, // W
		0b10101000,
		0b10101000,
		0b10101000,
		0b11111000,
		0b11111000, // O
		0b10001000,
		0b10001000,
		0b10001000,
		0b11111000,
		0b11110000, // R
		0b10001000,
		0b11110000,
		0b10010000,
		0b10001000,
		0b10000000, // L
		0b10000000,
		0b10000000,
		0b10000000,
		0b11111000,
		0b11110000, // D
		0b10001000,
		0b10001000,
		0b10001000,
		0b11110000,
};

const uint8_t alien_bytes[25] =
{
		0b00001000, // left side of alien
		0b00000100,
		0b00001111,
		0b00011011,
		0b00111111,
		0b00101111,
		0b00101000,
		0b00001100,

		0b00010000, // right side of alien
		0b00100000,
		0b11110000,
		0b11011000,
		0b11111100,
		0b11110100,
		0b00010100,
		0b00110000,
};

const TickType_t half_step_delay = pdMS_TO_TICKS(125);
const TickType_t step_delay = pdMS_TO_TICKS(250);
const TickType_t halfsec_delay = pdMS_TO_TICKS(500);
const TickType_t sec_delay = pdMS_TO_TICKS(1000);

GfxWindow_t * app_window = NULL;

Color565_t color;
uint8_t color_loop[32];
uint8_t color_loop_length = 32;

Color565_t hello_color;
Color565_t world_color;
Color565_t alien_color;
BinarySprite_t *hello_sprite;
BinarySprite_t *world_sprite;
BinarySprite_t *alien_sprite;

void app_init(void)
{
	app_window = gfx_create_window(0, 0, screen_get_x_size(), screen_get_y_size(), "Test Window");

	// init color loop
	for (int i = 0; i < color_loop_length; i+=2)
	{
		float percent = i/(float)color_loop_length;

		gfx_rgb_to_565_nonalloc(color, lerp(0, 100, percent) , 0, 0);
		color_loop[i] = color[0];
		color_loop[i+1] = color[1];
	}

	// init sprites and some colors
	gfx_rgb_to_565_nonalloc(hello_color, 100, 95, 100);
	gfx_rgb_to_565_nonalloc(world_color, 95, 100, 100);
	gfx_rgb_to_565_nonalloc(alien_color, 0, 100, 0);
	hello_sprite = gfx_bytes_to_binary_sprite(5, 5, hello_bytes);
	world_sprite = gfx_bytes_to_binary_sprite(5, 5, world_bytes);
	alien_sprite = gfx_bytes_to_binary_sprite(8, 2, alien_bytes);
}

void app_clean(void)
{
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_black);
    gfx_unselect_window(app_window);
    vTaskDelay(step_delay);

	// remove window reference from the refresh list before deallocating
	// TODO: extract window deallocation steps to function
	gfx_hide_window(app_window);
    gfx_dispose_window(app_window);
}

void app_loop(void)
{
	uint16_t pitch = A1;

    set_audio(0, 0);

    gfx_select_window(app_window, true);
	gfx_fill_screen(color_black);
    gfx_unselect_window(app_window);

	// add window to the refresh list
	gfx_show_window(app_window);

    vTaskDelay(step_delay);

	// font test!
    gfx_select_window(app_window, true);

	for (int i = 0; i < (128-32); i++)
	{
		int x = ((i) * 8 * 4) % 320;
		int y = ((i) * 8 * 4) / 320;

		gfx_fill_rect_single_color(x, y*5*4, default_font.width_bytes*8*3, default_font.height_pixels*3, color_blue);
		gfx_draw_binary_sprite_adhoc(
		default_font.height_pixels, default_font.width_bytes,
		&default_font.data[(i+32)*5], x, y*5*4, color_white, 3);
	}

    gfx_unselect_window(app_window);

    vTaskDelay(pdMS_TO_TICKS(halfsec_delay));

    gfx_select_window(app_window, true);
	gfx_fill_screen(color_black);
	gfx_print_string("Text test!", 0, 4, color_red, 3);
	gfx_print_string("Medium text...", 8, 32, color_magenta, 2);
	gfx_print_string("small text !@#$%^&*()", 16, 64, color_yellow, 1);
    gfx_unselect_window(app_window);

    vTaskDelay(sec_delay);

    set_audio(A1, 50);

    gfx_select_window(app_window, true);
	gfx_fill_screen(color_white);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(B1, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_red);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(Db2, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_green);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(D2, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_blue);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(E2, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_cyan);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(Gb2, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_yellow);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(Ab2, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_magenta);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(A2, 50);
    gfx_select_window(app_window, true);
	gfx_fill_screen(color_black);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    set_audio(0, 0);
/*
	gfx_rgb_to_565_nonalloc(color, 75, 25, 0);
	gfx_fill_rect_single_color(0, 0, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 50, 50, 0);
	gfx_fill_rect_single_color(80, 0, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 25, 75, 0);
	gfx_fill_rect_single_color(160, 0, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 100, 0);
	gfx_fill_rect_single_color(240, 0, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 75, 25);
	gfx_fill_rect_single_color(240, 60, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 50, 50);
	gfx_fill_rect_single_color(160, 60, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 25, 75);
	gfx_fill_rect_single_color(80, 60, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 0, 100);
	gfx_fill_rect_single_color(0, 60, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 75, 25, 0);
	gfx_fill_rect_single_color(0, 120, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 50, 50, 0);
	gfx_fill_rect_single_color(80, 120, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 25, 75, 0);
	gfx_fill_rect_single_color(160, 120, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 100, 0);
	gfx_fill_rect_single_color(240, 120, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 75, 25);
	gfx_fill_rect_single_color(240, 180, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 50, 50);
	gfx_fill_rect_single_color(160, 180, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 25, 75);
	gfx_fill_rect_single_color(80, 180, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);

	gfx_rgb_to_565_nonalloc(color, 0, 0, 100);
	gfx_fill_rect_single_color(0, 180, 80, 60, color);
	gfx_dirty = true;
	HAL_Delay(step_delay);
	HAL_Delay(step_delay);
*/
	float scale = 0.00f;

	while (scale < 1.0f)
	{
		scale += 0.125f;
        gfx_select_window(app_window, true);
		gfx_fill_rect_loop(color_loop, color_loop_length, 160 - (160 * scale), 120 - (120 * scale), 320 * scale, 240 * scale);
        gfx_unselect_window(app_window);

        set_audio(D2 / scale, 50);
        vTaskDelay(half_step_delay);
        set_audio(A1 / scale, 50);
        vTaskDelay(half_step_delay);
        set_audio(Gb1 / scale, 50);
        vTaskDelay(half_step_delay);
        set_audio(D1 / scale, 50);
        vTaskDelay(half_step_delay);
        set_audio(0, 0);

	}

    vTaskDelay(step_delay);

    gfx_select_window(app_window, true);
	gfx_draw_binary_sprite(hello_sprite, 160-20+2, 120-15, hello_color, 1);
	gfx_draw_binary_sprite(world_sprite, 160-20+2, 120+10, world_color, 1);
	gfx_draw_binary_sprite(alien_sprite, 16, 130, alien_color, 11);
    gfx_unselect_window(app_window);

    vTaskDelay(step_delay);

    gfx_select_window(app_window, true);
	gfx_fill_rect_loop(color_loop, color_loop_length, 0, 0, 320, 240);
	gfx_draw_binary_sprite(hello_sprite, 160-40+4, 120-20, hello_color, 2);
	gfx_draw_binary_sprite(world_sprite, 160-40+4, 120+10, world_color, 2);
	gfx_draw_binary_sprite(alien_sprite, 32, 130, alien_color, 10);
    gfx_unselect_window(app_window);
    set_audio(C2, 50);

    vTaskDelay(step_delay);

    gfx_select_window(app_window, true);
	gfx_fill_rect_loop(color_loop, color_loop_length, 0, 0, 320, 240);
	gfx_draw_binary_sprite(hello_sprite, 160-80+8, 120-30, hello_color, 4);
	gfx_draw_binary_sprite(world_sprite, 160-80+8, 120+10, world_color, 4);
	gfx_draw_binary_sprite(alien_sprite, 48, 130, alien_color, 9);

    gfx_unselect_window(app_window);
    set_audio(Gb2, 50);

    vTaskDelay(step_delay);

    gfx_select_window(app_window, true);
	gfx_fill_rect_loop(color_loop, color_loop_length, 0, 0, 320, 240);
	gfx_draw_binary_sprite(alien_sprite, 64, 130, alien_color, 8);
	gfx_draw_binary_sprite(hello_sprite, 24, 120-42, color_black, 8);
	gfx_draw_binary_sprite(world_sprite, 24, 120+18, color_black, 8);
	gfx_draw_binary_sprite(hello_sprite, 16, 120-50, hello_color, 8);
	gfx_draw_binary_sprite(world_sprite, 16, 120+10, world_color, 8);
    gfx_unselect_window(app_window);
    set_audio(C3, 50);

    vTaskDelay(halfsec_delay);

	int16_t alien_x = 152;

	while (alien_x < 328)
	{
        gfx_select_window(app_window, true);
		gfx_fill_rect_loop(color_loop, color_loop_length, 0, 120, 320, 120);
		gfx_draw_binary_sprite(alien_sprite, alien_x, 130, alien_color, 8);
        gfx_unselect_window(app_window);
        set_audio(Gb1 * ((1 + alien_x) / 320.0f), 50);
        vTaskDelay(half_step_delay);
        set_audio(0, 0);
		alien_x += 32;
        vTaskDelay(half_step_delay);
	}

    vTaskDelay(step_delay);
    set_audio(0, 0);
    vTaskDelay(halfsec_delay);
}
