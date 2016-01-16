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

#ifndef IO_CONSOLE_MANAGEMENT_H_INCLUDED
#define IO_CONSOLE_MANAGEMENT_H_INCLUDED

/**
 * @file io/console_management.h
 * @brief Introduces functions associated to the
 * management of the console.
 *
 * @author Lucas LAZARE
 *
 * Header file for changing text printing settings,
 * cursor settings, getting terminal state, ...
 */

#include <io/bool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

/**
 * @brief Adds/Removes an attribute to the output text
 * @param attribute Attribute to set to the text. Blink may not be available on all terminals
 */
void io_setTextAttributes(const char* attribute);

/**
 * @brief Sets a background color for the output text
 * @param color Color choosen as a background color, without any capital letter.
 */
void io_setBgColor(const char* color);

/**
 * @brief Sets a font color for the output text
 * @param color Color choosen as a font color, without any capital letter.
 */
void io_setTextColor(const char* color);

/**
 * @brief Sets the cursor visibility
 * @param visible TRUE to display the cursor, FALSE to hide.
 */
void io_visibleCursor(IO_BOOL visible);

/**
 * @brief Retrieve the height of the terminal
 * @return height of the terminal
 */
unsigned short io_consoleHeight(void);

/**
 * @brief Retrieve the width of the terminal
 * @return width of the terminal
 */
unsigned short io_consoleWidth(void);

/**
 * @brief Sets the output echo of user inputs
 * @param on TRUE to display, FALSE to hide
 */
void io_setEcho(IO_BOOL on);

/**
 * @brief Returns the current text color. If no color was set, it will return NULL.
 * @return The text color
 */
char* io_currentTxtColor(void);

/**
 * @brief Returns the current background color. If no color was set, it will return NULL.
 * @return The background color
 */
char* io_currentBgColor(void);

/**
 * @brief Return the cursor's visibility
 * @return TRUE if the cursor is visible, FALSE if not.
 */
IO_BOOL io_cursorVisible(void);

/**
 * @brief Return echo's state.
 * @return TRUE if echo is enabled, FALSE if not
 */
IO_BOOL io_echoSetting(void);

#endif /* IO_CONSOLE_MANAGEMENT_H_INCLUDED */
