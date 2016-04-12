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

#ifndef IO_SPRITE_MANAGEMENT_H_INCLUDED
#define IO_SPRITE_MANAGEMENT_H_INCLUDED



/**
 * @file io/sprite_management.h
 * @brief Introduces functions related to the
 * management of an io_Sprite structure
 *
 * @author Lucas LAZARE
 */

#include <stdbool.h>
#include <stdlib.h>
#include <io/sprite_struct.h>
#include <io/sprite_display.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

/**
 * @brief Sets a new io_Sprite.
 * @param x_len      Number of characters per line
 * @param y_len      Number of lines in the sprite
 * @param char_table Set of characters that can be drawn by sprite's functions. No '\0' are required (by copy).
 * @param txt_color  Color used for the text (by copy) if txt_color is set to NULL, color won't be changed to print the sprite.
 * @param bg_color   Color used for the background (by copy) if bg_color is set to NULL, color won't be changed to print the sprite.
 * @return           The created sprite.
 */
io_Sprite* io_newSprite(unsigned short x_len, unsigned short y_len, char** char_table, char* txt_color, char* bg_color);

/**
 * @brief Sets the position of the sprite
 * @param sprite Sprite to set
 * @param coord  New coordinates for the sprite
 * @return       The sprite
 */
io_Sprite* io_setPosition(io_Sprite* sprite, io_Coordinates coord);

/**
 * @brief Deletes an io_Sprite
 * @param sprite Concerned sprite
 * @return       NULL
 */
io_Sprite* io_deleteSprite(io_Sprite* sprite);

/**
 * @brief Sets wether you want to print the spaces within a sprite or not
 * Default behavior is to not print spaces.
 * @param sprite      Sprite to set
 * @param print_space TRUE to print spaces, FALSE otherwise
 * @return            The sprite
 */
io_Sprite* io_printSpaces(io_Sprite* sprite, bool print_spaces);

/**
 * @brief Changes the sprite's color
 * @param sprite    Sprite to edit
 * @param txt_color Color used for the text (by copy). If txt_color is set to NULL, color won't be changed to print the sprite.
 * @param bg_color  Color used for the background (by copy). If bg_color is set to NULL, color won't be changed to print the sprite.
 * @return          The sprite
 */
io_Sprite* io_changeSpriteColor(io_Sprite* sprite, char* txt_color, char* bg_color);

/**
 * @brief Sets to draw a part of a sprite. ie, given the sprite. Doesn't actually print it
 * "#--#"
 * "|  |"
 * "#--#"
 * Calling this function may allow you to print, in further functions
 * "  |"
 * "--#"
 *
 * @param sprite      Sprite to set
 * @param drawing_beg Where to start the drawing (within the table of characters. each coordinate must be greater or equal to 0, and smaller or equal to the sprite's x&y size)
 * @param drawing_end Where to end the drawing (x and y coordinates must be each greater or equal to beg_draw's x and y — and smaller or equal to the sprite's x&y size)
 * @retun             The sprite
 */
io_Sprite* io_usePartOfSprite(io_Sprite* sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end);

/**
 * @brief Revoke io_usePartOfSprite effects
 * @param sprite The sprite to set
 * @return       The sprite
 */
io_Sprite* io_useAll(io_Sprite* sprite);

/**
 * @brief Does the same than io_usePartOfSprite, but clears the sprite first
 * @param sprite      Sprite to set
 * @param drawing_beg Where to start the drawing (within the table of characters)
 * @param drawing_end Where to end the drawing (within the table of characters)
 * @return            The sprite
 */
io_Sprite* io_clearAndUsePart(io_Sprite* sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end);

/**
 * @brief Prints a filled rectangle in the given sprite, at the given coordinates
 * @param sprite    Sprite to edit
 * @param beg       Coordinates of the rectangle's top left corner (within the sprite)
 * @param end       Coordinates of the rectangle's bottom right corner (within the sprite)
 * @param draw_char Char to be drawn
 * @return          The sprite
 */
io_Sprite* io_drawFilledRectangleIn(io_Sprite* sprite, io_Coordinates beg, io_Coordinates end, char draw_char);

/**
 * @brief Prints an empty rectangle in the given sprite, at the given coordinates
 * @param sprite    Sprite to edit
 * @param beg       Coordinates of the rectangle's top left corner (within the sprite)
 * @param end       Coordinates of the rectangle's bottom right corner (within the sprite)
 * @param draw_char Char to be drawn
 * @return          The sprite
 */
io_Sprite* io_drawRectangleIn(io_Sprite* sprite, io_Coordinates beg, io_Coordinates end, char draw_char);

/**
 * @brief Prints a line in the given sprite
 * @param sprite    Sprite to edit
 * @param beg       Coordinates of the line's beginning
 * @param end       Coordinates of the line's end
 * @param draw_char Char to be drawn
 * @return          The sprite
 */
io_Sprite* io_drawLineIn(io_Sprite* sprite, io_Coordinates beg, io_Coordinates end, char draw_char);

/**
 * @brief Prints a circle in the given sprite
 * @param sprite    Sprite to edit
 * @param center    Coordinates of the center of the circle.
 * @param radius    Radius of the circle
 * @param draw_char Char to draw
 * @return          The sprite
 */
io_Sprite* io_drawCircleIn(io_Sprite* sprite, io_Coordinates center, unsigned short radius, char draw_char);

/**
 * @brief Draws a circle arch (clockwise) in the given sprite
 * @param sprite              Sprite to edit
 * @param center              Coordinates of the center of the arch
 * @param first_point_of_arch Coordinates of the first point of the arch
 * @param last_point_of_arch  Coordinates of the last point of the arch
 * @param draw_char           Character to draw
 * @return                    The sprite
 */
io_Sprite* io_drawArchIn(io_Sprite* sprite, io_Coordinates center, io_Coordinates first_point_of_arch, io_Coordinates last_point_of_arch, char draw_char);

#endif /* IO_SPRITE_MANAGEMENT_H_INCLUDED */
