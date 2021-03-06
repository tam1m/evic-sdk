/*
 * This file is part of eVic SDK.
 *
 * eVic SDK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * eVic SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with eVic SDK.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2015-2016 ReservedField
 * Copyright (C) 2015-2016 Jussi Timperi
 */

/**
 * NOTE: this low-level interface is not guaranteed to be thread/ISR-safe.
 */

#ifndef EVICSDK_DISPLAY_SSD_H
#define EVICSDK_DISPLAY_SSD_H

#include <stdint.h>
#include <stdbool.h>
#include <M451Series.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Commands shared by the SSDxxxx display controllers.
 */
#define SSD_SET_CONTRAST_LEVEL  0x81
#define SSD_SET_MULTIPLEX_RATIO 0xA8
#define SSD_DISPLAY_OFF         0xAE
#define SSD_DISPLAY_ON          0xAF

/**
 * Reset is at PA.0.
 */
#define DISPLAY_SSD_RESET PA0

/**
 * Vdd/Vci (logic voltage) enable is at PA.1.
 */
#define DISPLAY_SSD_VDD   PA1

/**
 * Vcc (matrix drive voltage) enable is at PC.4.
 * This is generated by a TPS61040 boost converter.
 */
#define DISPLAY_SSD_VCC   PC4

/**
 * D/C# is at PE.10.
 */
#define DISPLAY_SSD_DC    PE10

/**
 * Turns the display on or off.
 * This only acts on the pixels, the display will
 * still be powered. If you want to control the supply
 * rails, use Display_SSD_SetPowerOn().
 *
 * @param isOn True to turn the display on, false to turn it off.
 */
void Display_SSD_SetOn(uint8_t isOn);

/**
 * Powers the display on or off.
 * This turns the actual supply rails on/off, cutting
 * off all current draw from the display when off. It is
 * slower than Display_SSD_SetOn().
 *
 * @param isPowerOn True to power on the display, false to power it off.
 */
void Display_SSD_SetPowerOn(uint8_t isPowerOn);

/**
 * Flips the display according to the display orientation value in data flash.
 * An update must be issued afterwards.
 */
void Display_SSD_Flip();

/**
 * Sets whether the display colors are inverted.
 *
 * @param invert True for inverted display, false for normal display.
 */
void Display_SSD_SetInverted(bool invert);

/**
 * Sends the framebuffer to the controller and updates the display.
 *
 * @param framebuf Framebuffer.
 */
void Display_SSD_Update(const uint8_t *framebuf);

/**
 * Initializes the display controller.
 */
void Display_SSD_Init();

/**
 * Writes data to the display controller.
 *
 * @param isData True if writing GDDRAM data (D/C# high).
 * @param buf    Data buffer.
 * @param len    Size in bytes of the data buffer.
 */
void Display_SSD_Write(uint8_t isData, const uint8_t *buf, uint32_t len);

/**
 * Sends a command to the display controller.
 *
 * @param cmd Command.
 */
void Display_SSD_SendCommand(uint8_t cmd);

/**
 * Sets the display contrast (OLED current).
 * SSD1306: ~0.4uA/LSB
 * SSD1327: ~1.2uA/LSB
 *
 * @param contrast Contrast (0 - 255).
 */
void Display_SSD_SetContrast(uint8_t contrast);

#ifdef __cplusplus
}
#endif

#endif
