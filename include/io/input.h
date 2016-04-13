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

#ifndef IO_INPUT_H_INCLUDED
#define IO_INPUT_H_INCLUDED

/**
 * @file io/input.h
 * @brief Introduces functions used to retrieve
 * inputs from the user.
 *
 * @author Lucas LAZARE
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <io/cursor.h>
#include <io/console_management.h>


/**
 * @brief Retrieves a user answer to a yes/no question
 * @param question     The question addressed to the user
 * @param default_ans  1 for Yes as default, -1 for No as default, any other for no default.
 * @return             True if user inputted yes, False otherwise
 */
bool io_yes(char* question, char default_ans);

/**
 * @brief Retrieves a number inputted in base i_base
 * @param i_base        input base
 * @param with_brackets TRUE to display the input between brackets, FALSE otherwise
 * @return              the inputted number
 */
char* io_getNumber(unsigned char i_base, bool with_brackets);

/**
 * @brief Gets a char without waiting for the user to input '\n'
 * @return The char inputted by the user.
 */
char io_getChar(void);


/**
 * @brief Gets a char with timeout
 * @param timeout Time to wait in tenth of seconds.
 * @return        The char inputted by the user. -1 if no input
 */
char io_getCharTimed(unsigned char timeout);


/**
 * @brief Gets a number within a given range
 * @param min minimum value to return
 * @param max maximum value to return
 * @return    value inputted by the user
 */
unsigned long int io_getNumberWithinRange(unsigned long int min, unsigned long int max);

/**
 * @brief Checks if a number stored as a char* is between two given values
 * @param val  Value to check
 * @param min  Lower bound (included)
 * @param max  Upper bound (included)
 * @param base Base in which val is stored
 * @return     TRUE if val is between min and max, FALSE otherwise
 */
bool io_isWithinRange(char* val,unsigned long int min, unsigned long int max, unsigned char base);

#endif /* IO_INPUT_H_INCLUDED */
