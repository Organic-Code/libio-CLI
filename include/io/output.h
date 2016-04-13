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

/**
 * @file io/output.h
 * @brief Declares functions related to the
 * printing of elements on the terminal.
 *
 * @author Lucas LAZARE
 */

/*! code corresponding to ESC */
#define IO_SPECIAL_CHAR 0x001B
/*! io_menu(...) or io_print  : align to the left */
#define IO_LEFT 1
/*! io_menu(...) or io_print  : center */
#define IO_CENTER 2
/*! io_menu(...) or io_print : align to the right */
#define IO_RIGHT 4
/*! io_print : the text is blinking until a given key is pressed */
#define IO_BLINK 8
/*! io_print : the text is written char by char, with a little pause */
#define IO_TYPEWRITE 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdarg.h>
#include <sys/timeb.h>
#include <io/cursor.h>
#include <io/console_management.h>
#include <io/input.h>

/**
 * @brief Clears the screen
 */
void io_clear(void);

/**
 * @brief Prints a text in a formated way. nb : only for strings with at most 512 characters (TTY usually have at most 250 columns)
 * @param option Options for printing the text. Usable options: IO_BLINK, IO_TYPEWRITE, IO_CENTER, IO_LEFT, IO_RIGHT (for blinking centered text, use the argument 'IO_BLINK | IO_CENTER'). See define for more information
 *                  Note that IO_BLINK can be used only if either IO_CENTER, IO_LEFT or IO_RIGHT is set
 * @param y_pos  Height of the text to print.
 * @param key    If IO_BLINK is set, the text will blink until this key is pressed. If set to 0, any key press will work.
 *                  If IO_TYPEWRITE is set, the text will be printed instantly displayed. If set to 0, any key press will work.
 * @param format String formatted in the printf way.
 */
void io_print(int options, unsigned short y_pos, char key, const char* format, ...);

/* input & output */

/**
 * @brief Prints a nice menu where you can navigate using arrow keys, and select with Enter.
 * 	call example : example io_menu("One player\0Two players\0Quit\0", "Game mode", 0, IO_LEFT, "white", "blue", "light grey");
 * @param choices        char pointer to a list of the selectable choices. Each choice should end with a '\0' character, and the whole list should end with 2 '\0'
 * @param title          Menu's title. NULL for no title.
 * @param default_choice The default selected choice
 * @param alignment     Choices alignment. may be IO_LEFT, IO_CENTER, IO_RIGHT.
 * @param text_color     Font color of the unselected text. NULL for no particular color.
 * @param bg_color       Background color of the unselected text. NULL for no particular color.
 * @param border_color   Color of the menu's border. NULL for no border
 * @return               The index of the choice selected, starting with index 0. 255 if the display was no possible.
 */
unsigned char io_menu(const char* choices, const char* title, unsigned char default_choice, char alignement, const char* text_color, const char* bg_color, const char* border_color);

#endif /* IO_OUTPUT_H_INCLUDED */
