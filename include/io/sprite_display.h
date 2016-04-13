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

#ifndef IO_SPRITE_DISPLAY_H_INCLUDED
#define IO_SPRITE_DISPLAY_H_INCLUDED

/**
 * @file io/sprite_display.h
 * @brief Intruduces functions related to the
 * printing of 'sprites' at the screen
 *
 * @author Lucas LAZARE
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <io/console_management.h>
#include <io/cursor.h>
#include <io/sprite_struct.h>

/**
 * @brief Draws a Sprite at its coordinates. It may be cutted if it's too much on the edge
 * @param sprite Sprite to draw
 */
void io_printSprite(const io_Sprite* sprite);

/**
 * @brief Draws a Sprite at the specified coordinates
 * @param sprite     Sprite to draw
 * @param coordinates Coordinates where to draw the sprite
 * @return       TRUE on success, FALSE otherwise
 */
void io_printSpriteAt(io_Sprite* sprite, io_Coordinates coordinates);

/**
 * @brief Clears the sprite from the screen
 * @param sprite Sprite to clean.
 * @return       TRUE on success, FALSE otherwise
 */
void io_clearSprite(const io_Sprite* sprite);

/**
 * @brief Clears the sprite from the screen and reprints it to the given location
 * @param sprite     Sprite to move
 * @param coordinates Coordinates of where to move the sprite
 */
void io_moveSpriteTo(io_Sprite* sprite, io_Coordinates coordinates);

/**
 * @brief Clears the sprite from the screen and reprints to a position relative to its previous location.
 * @param sprite The conserned sprite
 * @param x      Horizontal movement of the sprite. May be negative.
 * @param y      Vertical movement of the sprite. May be negative.
 */
void io_moveSpriteRelativ(io_Sprite* sprite, int x, int y);

/**
 * @brief Prints a sprite at the center of the screen. If the screen is too small, the sprite will be cutted.
 * @param sprite Sprite to draw
 * @return       TRUE on success, FALSE otherwise
 */
void io_centerPrintSprite(io_Sprite* sprite);

#endif /* IO_SPRITE_DISPLAY_H_INCLUDED */
