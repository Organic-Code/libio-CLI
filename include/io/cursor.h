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

#ifndef IO_CURSOR_H_INCLUDED
#define IO_CURSOR_H_INCLUDED
/**
 * @file io/cursor.h
 * @brief Introduces functions related to cursor management.
 *
 * @author Lucas LAZARE
 */

#include <stdio.h>

/**
 * @brief Sets the cursor position
 * @param x The x coordinates of the cursor
 * @param y The y coordinates of the cursor
 */
void io_setCursorPos(unsigned short x, unsigned short y);

/**
 * @brief Moves the cursor horizontaly
 * @param x number of characters to move. Negative values to go right, positive values to go left
 */
void io_cursorHorizontalMove(int x);

/**
 * @brief Moves the cursor vertically
 * @param y number of characters to move. Negative values to go top, positive values to go down
 */
void io_cursorVerticalMove(int y);

#endif /* IO_CURSOR_H_INCLUDED */
