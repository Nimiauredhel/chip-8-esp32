#ifndef LCD_H
#define LCD_H

#include <string.h>
#include "driver/spi_master.h"
#include "esp_check.h"

#include "esp_lcd_panel_io.h"       // Header file dependency

#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_ili9341.h"

void lcd_initialize_bus(void);
void lcd_initialize_interface(void);
void lcd_initialize_screen(void);
void lcd_deinitialize_screen(void);

#endif
