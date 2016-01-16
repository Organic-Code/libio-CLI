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
 

#ifndef IO_COORDINATES_STRUCT_H_INCLUDED
#define IO_COORDINATES_STRUCT_H_INCLUDED

/**
 * @file io/coordinates_struct.h
 * @brief Introduces functions and structures associated to io_Coordinates.
 *
 * @author Lucas LAZARE
 */

/**
 * @struct io_Coordinates
 * @brief A structure defining a character's coordinates
 */
typedef struct{
	unsigned short x; /*!< Column of the character */
	unsigned short y; /*!< Row of the character */
}io_Coordinates;

/**
 * @brief Returns an io_Coordinates according to the inputed parameters
 * @param x Row
 * @param y Column
 * @return  The generated io_Coordinates
io_Coordinates io_setCoordinates(unsigned short x, unsigned short y);

#endif /* IO_COORDINATES_STRUCT_H_INCLUDED */
