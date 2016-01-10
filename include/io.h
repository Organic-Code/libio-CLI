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

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#define IO_SPECIAL_CHAR 0x001B
#define IO_LEFT 0
#define IO_CENTER 1
#define IO_RIGHT 2

#include <bool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

typedef struct{
	unsigned short x;
	unsigned short y;
}io_Coordinates;

/*
 * @struct io_Sprite
 * @brief A structure containing a char* that can be passed to drawing functions
 */
typedef struct{
	io_Coordinates current_position;
	io_Coordinates ld_start_coo;
	io_Coordinates ld_end_coo;
	unsigned short x_size;
	unsigned short y_size;
	char* char_table;
	char* txt_color;
	char* bg_color;
	BOOL draw_spaces;
	BOOL ld_complete;
}io_Sprite_Struct;

typedef io_Sprite_Struct* io_Sprite;

/* pure output */

/* TODO */
/*
 * Draws a filled rectangle
 * @param beg       Coordinates of the rectangle's beginning
 * @param end       Coordinates of the rectangle's ending
 * @param draw_char Char to be drawn
 */
void io_drawFilledRectangle(io_Coordinates beg, io_Coordinates end, char draw_char);

/* TODO */
/*
 * Draws an empty rectangle
 * @param beg       Coordinates of the rectangle's beginning
 * @param end       Coordinates of the rectangle's ending
 * @param draw_char Char to be drawn
 */
void io_drawRectangle(io_Coordinates beg, io_Coordinates end, char draw_char);

/* TODO */
/*
 * Draws a line
 * @param beg       Coordinates of the line's beginning
 * @param end       Coordinates of the line's end
 * @param draw_char Char to be drawn
 */
void io_drawLine(io_Coordinates beg, io_Coordinates end, char draw_char);

/* TODO */
/*
 * Draws a doted line
 * @param beg       Coordinates of the line's beginning
 * @param end       Coordinates of the line's end
 * @param draw_char Char to be drawn
 */
void io_drawDotedLine(io_Coordinates beg, io_Coordinates end, char draw_char);

/* TODO */
/*
 * Prints a circle at the specified coordinates and with the specified char
 * @param center    Coordinates of the center of the circle.
 * @param radius    Radius of the circle
 * @param draw_char Char to draw
 */
void io_drawCircle(io_Coordinates center, unsigned short radius, char draw_char);

/* TODO */
/*
 * Draws a circle arch
 * @param center              Coordinates of the center of the arch
 * @param first_point_of_arch Coordinates of the first point of the arch
 * @param last_point_of_arch  Coordinates of the last point of the arch
 * @param draw_char           Character to draw
 * @return                    TRUE if successful, FALSE otherwise
 */
BOOL io_drawArch(io_Coordinates center, io_Coordinates first_point_of_arch, io_Coordinates last_point_of_arch, char draw_char);

/* TODO */
/*
 * Draws a Sprite at its coordinates. It may be cutted if it's too much on the edge
 * @param sprite Sprite to draw
 * @return       TRUE on success, FALSE otherwise
 */
BOOL io_printSprite(io_Sprite sprite);

/* TODO */
/*
 * Draws a Sprite at the specified coordinates
 * @param sprite     Sprite to draw
 * @param Coordinates Coordinates where to draw the sprite
 * @return       TRUE on success, FALSE otherwise
 */
BOOL io_printSpriteAt(io_Sprite sprite, io_Coordinates coordinates);

/* TODO */
/*
 * Clears the sprite from the screen
 * @param sprite Sprite to clean.
 * @return       TRUE on success, FALSE otherwise
 */
BOOL io_clearSprite(io_Sprite sprite);

/* TODO */
/*
 * Clears the sprite from the screen and moves it to the given location
 * @param sprite     Sprite to move
 * @param Coordinates Coordinates of where to move the sprite
 * @return       TRUE on success, FALSE otherwise
 */
BOOL io_moveSpriteTo(io_Sprite sprite, io_Coordinates coordinates);

/* Clears the screen */
void io_clear(void);

/*
 * Adds/Removes an attribute to the output text
 * @param attribute Attribute to set to the text. Blink may not be available on all terminals
 */
void io_setTextAttributes(const char* attribute);

/*
 * Sets a background color for the output text
 * @param color Color choosen as a background color, without any capital letter.
 */
void io_setBgColor(const char* color);

/*
 * Sets a font color for the output text
 * @param color Color choosen as a font color, without any capital letter.
 */
void io_setTextColor(const char* color);

/*
 * Prints a text at the center of the screen, given its height. Will output nothing if the screen's width is smaller than the text to print
 * @param text  Text to print at the screen
 * @param y_pos Height of the text to print
 */
void io_centerPrint(char* text, unsigned short y_pos);

/* input & output */

/*
 * Prints a nice menu where you can navigate using arrow keys, and select with Enter. Some args could be easily added, such as :
 *       border_color(const char*)[one function call to modify]
 *       alignement(enum)[uncommenting + adding if]
 * @param choices    char pointer to a list of the selectable choices. Each choice should end with the '\0' character
 * @param nb_choices number of choices to display. Should not be more than the number of '\0' in 'choices'
 * @param choice     the default selected choice
 * @param alignement Choices alignement. may be IO_LEFT, IO_CENTER, IO_RIGHT.
 * @param text_color font color of the unselected text
 * @param bg_color   background color of the unselected text
 * @return           the index of the choice selected, starting with index 0. 255 if the display was no possible.
 */
unsigned char io_menu(const char* choices, unsigned char nb_choices, unsigned char choice, char alignement, char* text_color, char* bg_color);

/* pure input */

/*
 * Retrieves a user answer to a yes/no question
 * @param question The quetion adressed to the user
 * @param default  1 for Yes as default, -1 for No as default, any other for no default.
 * @return True if user inputed yes, False otherwise
 */
BOOL io_yes(char* question, char default_ans);

/*
 * Retrieves a number inputed in base i_base
 * @param i_base       input base
 * @return             the inputed number
 */
char* io_getNumber(unsigned char i_base, BOOL with_brackets);

/* Gets a char without waiting for the user to input '\n' */
char io_instantGetChar(void);

/*
 * Gets a number within a given range
 * @param min minimum value to return
 * @param max maximum value to return
 * @return    value inputed by the user
 */
unsigned long int io_getNumberWithinRange(unsigned long int min, unsigned long int max);
/* inner functions */

/* TODO */
/*
 * Sets a new io_Sprite.
 * @param x_len      Number of characters per line
 * @param y_len      Number of lines in the sprite
 * @param char_table Set of characters that can be drawn by sprite's functions. No '\0' are required (address will be used).
 * @param txt_color  Color used for the text (address will be used).
 * @param bg_color   Color used for the background (address will be used).
 * @return           The created sprite.
 */
io_Sprite io_newSprite(unsigned short x_len, unsigned short y_len, char* char_table, char* txt_colors, char* bg_color);

/* TODO */
/*
 * Sets wether you want to print the spaces within a sprite or not
 * Default behavior is to not print spaces.
 * @param sprite      Sprite to set
 * @param print_space TRUE to print spaces, FALSE otherwise
 */
void io_printSpaces(io_Sprite sprite, BOOL print_space);

/* TODO */
/*
 * Sets the cursor visibility
 * @param visibility TRUE to display the cursor, FALSE to hide.
 * @return           TRUE on success, false otherwise.
 */
BOOL io_visibleCursor(BOOL visibility);

/* TODO */
/*
 * Sets the console's size (given in number of characters).
 * @param x Length of the console
 * @param y Width of the console
 * @return  TRUE on success, FALSE otherwise
 */
BOOL io_setConsoleSize(unsigned short x, unsigned short y);

/* TODO */
/*
 * Sets to draw a part of a sprite. ie, given the sprite
 * "#--#"
 * "|  |"
 * "#--#"
 * Calling this function may allow you to print, in further functions
 * "  |"
 * "--#"
 *
 * @param sprite
 * @param drawing_beg Where to start the drawing (within the table of characters. each coordinate must be greater or equal to 0, and smaller or equal to the sprite's x&y size)
 * @param drawing_end Where to end the drawing (x and y coordinates must be each greater or equal to beg_draw's x and y — and smaller or equal to the sprite's x&y size)
 * @retun             TRUE if coordinates where alright, false otherwise.
 */
BOOL io_usePartOfSprite(io_Sprite sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end);

/*
 * Retrieve the height of the terminal
 * @return height of the terminal
 */
unsigned short io_consoleHeight(void);

/*
 * Retrieve the width of the terminal
 * @return width of the terminal
 */
unsigned short io_consoleWidth(void);

/*
 * Sets the cursor position
 * @param x The x coordinates of the cursor
 * @param y The y coordinates of the cursor
 */
void io_setCursorPos(unsigned short x, unsigned short y);

/*
 * Moves the cursor horizontaly
 * @param x number of characters to move. Negative values to go right, positive values to go left
 */
void io_cursorHorizontalMove(int x);

/*
 * Moves the cursor vertically
 * @param y number of characters to move. Negative values to go top, positive values to go down
 */
void io_cursorVerticalMove(int y);

/*
 * Sets the output echo of user inputs
 * @param on TRUE to display, FALSE to hide
 */
void io_setEcho(BOOL on);

/*
 * Checks if a number stored as a char* is between two given values
 * @param val  Value to check
 * @param min  Lower bound (included)
 * @param max  Upper bound (included)
 * @param base Base in which val is stored
 * @return     TRUE if val is between min and max, FALSE otherwise
 */
BOOL io_isWithinRange(char* val,unsigned long int min, unsigned long int max, unsigned char base);

#endif /* IO_H_INCLUDED */
