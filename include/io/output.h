/************************************************************************************************************
 *                                                                                                          *
 * libio - A CLI project implementing input and output functions.                                           *
 * Copyright (C) 2016 LAZARE Lucas (lazarelucas@yahoo.fr)                                                   *
 *                                                                                                          *
 * This software is provided 'as-is', without any express or implied warranty.                              *
 * In no event will the authors be held liable for any damages arising from the use of this software.       *
 *                                                                                                          *
 * Permission is granted to anyone to use this software for any purpose,                                    *
 * including commercial applications, and to alter it and redistribute it freely,                           *
 * subject to the following restrictions:                                                                   *
 *                                                                                                          *
 * 1. The origin of this software must not be misrepresented;                                               *
 * you must not claim that you wrote the original software.                                                 *
 * If you use this software in a product, an acknowledgment                                                 *
 * in the product documentation would be appreciated but is not required.                                   *
 *                                                                                                          *
 * 2. Altered source versions must be plainly marked as such,                                               *
 * and must not be misrepresented as being the original software.                                           *
 *                                                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                               *
 *                                                                                                          *
 ************************************************************************************************************/

#ifndef IO_OUTPUT_H_INCLUDED
#define IO_OUTPUT_H_INCLUDED

#define IO_SPECIAL_CHAR 0x001B
#define IO_LEFT 0
#define IO_CENTER 1
#define IO_RIGHT 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io/bool.h>
#include <io/cursor.h>
#include <io/console_management.h>
#include <io/input.h>

/**
 * @brief Clears the screen
 */
void io_clear(void);

/**
 * @brief Prints a text at the center of the screen, given its height. Will output nothing if the screen's width is smaller than the text to print
 * @param text  Text to print at the screen
 * @param y_pos Height of the text to print
 */
void io_centerPrint(const char* text, unsigned short y_pos);

/* input & output */

/**
 * @brief Prints a nice menu where you can navigate using arrow keys, and select with Enter. Some args could be easily added, such as :
 * @param choices      char pointer to a list of the selectable choices. Each choice should end with a '\0' character, and the whole list should end with 2 '\0' (eg : "choice 1\0choice 2\0choice 3\0")
 * @param title        Menu's title. NULL for no title.
 * @param choice       The default selected choice
 * @param alignement   Choices alignement. may be IO_LEFT, IO_CENTER, IO_RIGHT.
 * @param text_color   Font color of the unselected text. NULL for no particular color.
 * @param bg_color     Background color of the unselected text. NULL for no particular color.
 * @param border_color Color of the menu's border. NULL for no border
 * @return             The index of the choice selected, starting with index 0. 255 if the display was no possible.
 */
unsigned char io_menu(const char* choices, const char* title, unsigned char choice, char alignement, const char* text_color, const char* bg_color, const char* border_color);

#endif /* IO_OUTPUT_H_INCLUDED */
