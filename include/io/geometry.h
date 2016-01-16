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

#ifndef IO_GEOMETRY_H_INCLUDED
#define IO_GEOMETRY_H_INCLUDED

#include <io/bool.h>
#include <stdio.h>
#include <io/coordinates_struct.h>
#include <io/cursor.h>
#include <math.h>

/**
 * @brief Draws a filled rectangle
 * @param beg       Coordinates of the rectangle's top left corner
 * @param end       Coordinates of the rectangle's bottom right corner
 * @param draw_char Char to be drawn
 */
void io_drawFilledRectangle(io_Coordinates beg, io_Coordinates end, char draw_char);

/**
 * @brief Draws an empty rectangle
 * @param beg       Coordinates of the rectangle's top left corner
 * @param end       Coordinates of the rectangle's bottom right corner
 * @param draw_char Char to be drawn
 */
void io_drawRectangle(io_Coordinates beg, io_Coordinates end, char draw_char);

/**
 * @brief Draws a line
 * @param beg       Coordinates of the line's beginning
 * @param end       Coordinates of the line's end
 * @param draw_char Char to be drawn
 */
void io_drawLine(io_Coordinates beg, io_Coordinates end, char draw_char);

/**
 * @brief Draws a vertical line
 * @param beg       Coordinate of an extremity of the line
 * @param height    Height of the line
 * @param draw_char Char to be drawn
 */
void io_drawVerticalLine(io_Coordinates beg, unsigned short height, char draw_char);

/**
 * @brief Draws an horizontal line
 * @param beg       Coordinates of an extremity of the line
 * @param width     width of the line
 * @param draw_char Char to be drawn
 */
void io_drawHorizontalLine(io_Coordinates beg, unsigned short width, char draw_char);

/**
 * @brief Prints a circle at the specified coordinates and with the specified char
 * @param center    Coordinates of the center of the circle.
 * @param radius    Radius of the circle
 * @param draw_char Char to draw
 */
void io_drawCircle(io_Coordinates center, unsigned short radius, char draw_char);

/**
 * @brief Draws a circle arch (clockwise)
 * @param center              Coordinates of the center of the arch
 * @param first_point_of_arch Coordinates of the first point of the arch
 * @param last_point_of_arch  Coordinates of the last point of the arch
 * @param draw_char           Character to draw
 */
void io_drawArch(io_Coordinates center, io_Coordinates first_point_of_arch, io_Coordinates last_point_of_arch, char draw_char);

/**
 * @brief computes the absolute value of a number
 * @param val Number
 * @return    The absolute value of val
 */
double io_abs(double val);

#endif /* IO_GEOMETRY_H_INCLUDED */
