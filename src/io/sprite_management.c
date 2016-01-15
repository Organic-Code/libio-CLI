/************************************************************************
 *
 * libio - A CLI project
 *
 * Copyright (C) 2016 LAZARE Lucas (lazarelucas@yahoo.fr)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 * you must not claim that you wrote the original software.
 * If you use this software in a product, an acknowledgment
 * in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 * and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ***********************************************************************/
 
#include <io/sprite_management.h>

io_Sprite* io_newSprite(unsigned short x_len, unsigned short y_len, char* char_table, char* txt_color, char*bg_color)
{
	io_Sprite* newsp = (io_Sprite*)malloc(sizeof(io_Sprite));

	newsp->current_position.x = newsp->current_position.y = 0;
	newsp->drawing_start_coo.x = newsp->drawing_start_coo.y = 0;
	newsp->drawing_end_coo.x = x_len;
	newsp->drawing_end_coo.y = y_len;
	newsp->x_size = x_len;
	newsp->y_size = y_len;
	newsp->char_table = char_table;
	newsp->txt_color = txt_color;
	newsp->bg_color = bg_color;
	newsp->draw_spaces = IO_FALSE;

	return newsp;
}

io_Sprite* io_deleteSprite(io_Sprite* sprite)
{
	free(sprite);
	return NULL;
}

io_Sprite* io_printSpaces(io_Sprite* sprite, IO_BOOL print_spaces)
{
	sprite->draw_spaces = print_spaces;
	return sprite;
}

io_Sprite* io_changeSpriteColor(io_Sprite* sprite, char* txt_color, char* bg_color)
{
	sprite->txt_color = txt_color;
	sprite->bg_color = bg_color;
	return sprite;
}

io_Sprite* io_usePartOfSprite(io_Sprite* sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end)
{
	if (drawing_beg.x <= sprite->x_size && drawing_beg.y <= sprite->y_size &&
		drawing_end.x <= sprite->x_size && drawing_end.y <= sprite->y_size &&
		drawing_beg.x <= drawing_end.x && drawing_beg.y <= drawing_beg.y) {

		sprite->drawing_start_coo = drawing_beg;
		sprite->drawing_end_coo = drawing_end;
	}

	return sprite;
}

io_Sprite* io_clearAndUsePart(io_Sprite* sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end)
{
	io_clearSprite(sprite);
	return io_usePartOfSprite(sprite, drawing_beg, drawing_end);
}
