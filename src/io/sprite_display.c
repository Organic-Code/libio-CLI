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

#include <io/sprite_display.h>

void io_printSprite(const io_Sprite* sprite){
	char origin_bg_color[14];
	char origin_txt_color[14];

	if (sprite->bg_color != NULL) {
		strcpy(origin_bg_color, io_currentBgColor());
		io_setBgColor(sprite->bg_color);
	}
	if (sprite->txt_color != NULL) {
		strcpy(origin_txt_color, io_currentTxtColor());
		io_setTextColor(sprite->txt_color);
	}

	if (sprite->draw_spaces) {
		unsigned short i = 0, j;
		for (i = sprite->drawing_start_coo.y ; i <  sprite->drawing_end_coo.y ; ++i) {
			io_setCursorPos(sprite->current_position.x, i + sprite->current_position.y - sprite->drawing_start_coo.y);
			for (j = sprite->drawing_start_coo.x ; j < sprite->drawing_end_coo.x ; ++j) {
				if (sprite->char_table[i][j] != ' ') {
					printf("%c", sprite->char_table[i][j]);
				}
				else {
					io_setCursorPos(sprite->current_position.x + j - sprite->drawing_start_coo.x, i + sprite->current_position.y - sprite->drawing_start_coo.y);
				}
			}

		}
	}
	else {
		unsigned short i = 0, j;
		for ( i = sprite->drawing_start_coo.y ; i < sprite->drawing_end_coo.y ; ++i) {
			io_setCursorPos(sprite->current_position.x, i + sprite->current_position.y - sprite->drawing_start_coo.y);
			for ( j = sprite->drawing_start_coo.x ; j < sprite->drawing_end_coo.x ; ++j) {
				printf("%c", sprite->char_table[i][j]);
			}
		}
	}

	if (sprite->bg_color != NULL) {
		io_setBgColor(origin_bg_color);
	}
	if (sprite->txt_color != NULL) {
		io_setTextColor(origin_txt_color);
	}
}

void io_printSpriteAt(io_Sprite* sprite, io_Coordinates coordinates){
	sprite->current_position = coordinates;
	io_printSprite(sprite);
}

void io_clearSprite(const io_Sprite* sprite){
	unsigned short i, j;
	for (i = sprite->drawing_end_coo.y - sprite->drawing_start_coo.y ; i--;) {
		io_setCursorPos(sprite->current_position.x, sprite->current_position.y + i);
		for ( j = sprite->drawing_start_coo.x ; j < sprite->drawing_end_coo.x ; ++j) {
			printf(" ");
		}
	}
}

void io_moveSpriteTo(io_Sprite* sprite, io_Coordinates coordinates){
	io_clearSprite(sprite);
	sprite->current_position = coordinates;
	io_printSprite(sprite);
}

/* OPTIMIZE ME */
void io_moveSpriteRelativ(io_Sprite* sprite, int x, int y){
	io_clearSprite(sprite);
	sprite->current_position.x += x;
	sprite->current_position.y += y;
	io_printSprite(sprite);
}

void io_centerPrintSprite(io_Sprite* sprite){
	sprite->current_position.x = (io_consoleWidth() - sprite->drawing_end_coo.x + sprite->drawing_start_coo.x) / 2;
	sprite->current_position.y = (io_consoleHeight() - sprite->drawing_end_coo.y + sprite->drawing_start_coo.y) / 2;
	io_printSprite(sprite);
}
