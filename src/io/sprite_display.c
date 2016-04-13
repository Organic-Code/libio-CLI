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

static unsigned short minimum(unsigned short a, unsigned short b);

static unsigned short minimum(unsigned short a, unsigned short b){
    if (a > b){
        return a;
    }
    else
        return b;
}

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

	unsigned short x_start_sp, x_end_sp, y_start_sp, y_end_sp;
	if (sprite->draw_part){
		x_start_sp = sprite->drawing_start_coo.x;
		y_start_sp = sprite->drawing_start_coo.y;
		x_end_sp   = sprite->drawing_end_coo.x;
		y_end_sp   = sprite->drawing_end_coo.y;
	}
	else{
		x_start_sp = 0;
		y_start_sp = 0;
		x_end_sp   = sprite->x_size;
		y_end_sp   = sprite->y_size;
	}

    assert(sprite->char_table != NULL);
	if (!sprite->draw_spaces) {
		unsigned short i, j;
		bool reset_pos = false;

		for (i = y_start_sp ; i <  y_end_sp ; ++i) {
			io_setCursorPos(sprite->current_position.x, i + sprite->current_position.y - y_start_sp);

			for (j = x_start_sp ; j < x_end_sp ; ++j) {
                assert(sprite->char_table[i] != NULL);

				if (sprite->char_table[i][j] != ' ') {
					if (reset_pos){
						reset_pos = false;
						io_setCursorPos(sprite->current_position.x + j - x_start_sp, i + sprite->current_position.y - y_start_sp);
					}
					printf("%c", sprite->char_table[i][j]);
				}
				else {
					reset_pos = true;
				}
			}

		}
	}
	else {
		unsigned short i = 0, j;
		for ( i = y_start_sp ; i < y_end_sp ; ++i) {
            assert(sprite->char_table[i] != NULL);
			io_setCursorPos(sprite->current_position.x, i + sprite->current_position.y - y_start_sp);
			for ( j = x_start_sp ; j < x_end_sp ; ++j) {
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
    unsigned short x_start_sp, x_end_sp, y_start_sp, y_end_sp;
    if (sprite->draw_part){
        x_start_sp = sprite->drawing_start_coo.x;
        y_start_sp = sprite->drawing_start_coo.y;
        x_end_sp   = sprite->drawing_end_coo.x;
        y_end_sp   = sprite->drawing_end_coo.y;
    }
    else{
        x_start_sp = 0;
        y_start_sp = 0;
        x_end_sp   = sprite->x_size;
        y_end_sp   = sprite->y_size;
    }

	unsigned short i, j;
	if (sprite->draw_spaces){
		for (i = y_end_sp - sprite->drawing_start_coo.y ; i--;) {
			io_setCursorPos(sprite->current_position.x, sprite->current_position.y + i);
			for ( j = x_start_sp ; j < x_end_sp ; ++j) {
				printf(" ");
			}
		}
	}
	else{
		bool reset_pos = false;
		for (i = y_start_sp ; i <  y_end_sp ; ++i) {
			io_setCursorPos(sprite->current_position.x, i + sprite->current_position.y - y_start_sp);
			for (j = x_start_sp ; j < x_end_sp ; ++j) {
				if (sprite->char_table[i][j] != ' ') {
					if (reset_pos){
						reset_pos = false;
						io_setCursorPos(sprite->current_position.x + j - x_start_sp, i + sprite->current_position.y - y_start_sp);
					}
					printf(" ");
				}
				else {
					reset_pos = true;
				}
			}

		}
	}
}

void io_moveSpriteTo(io_Sprite* sprite, io_Coordinates coordinates){
	if (sprite->current_position.x <= coordinates.x && sprite->current_position.y <= coordinates.y && coordinates.x < sprite->current_position.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x &&  coordinates.y < sprite->current_position.y + sprite->drawing_end_coo.y - sprite->drawing_start_coo.y){
        unsigned short i, j, mini = minimum(sprite->current_position.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x, coordinates.x);
		for (j = sprite->current_position.y ; j < sprite->current_position.y + sprite->drawing_end_coo.y - sprite->drawing_start_coo.y ; ++j)
			if (j < coordinates.y){
				for (i = sprite->current_position.x ; i < sprite->current_position.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x ; ++i){
					if (sprite->char_table[j + sprite->drawing_start_coo.y - sprite->current_position.y][i + sprite->drawing_start_coo.x - sprite->current_position.x] != ' ')
					{
						io_setCursorPos(i, j);
						printf(" ");
					}
				}
			}
			else{
				for (i = sprite->current_position.x ; i < mini; ++i) {
					if (sprite->char_table[j + sprite->drawing_start_coo.y - sprite->current_position.y][i + sprite->drawing_start_coo.x - sprite->current_position.x] != ' ') {
						io_setCursorPos(i, j);
						printf(" ");
					}
				}
			}
	}
	else if (coordinates.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x > sprite->current_position.x && coordinates.y + sprite->drawing_end_coo.y - sprite->drawing_start_coo.y > sprite->current_position.y && coordinates.x <= sprite->current_position.x && coordinates.y <= sprite->current_position.y)
	{
		unsigned int i, j;
		for (j = sprite->current_position.y ; j < sprite->current_position.y + sprite->drawing_end_coo.y - sprite->drawing_start_coo.y ; ++j)
            if (j > coordinates.y + sprite->drawing_end_coo.x - sprite->drawing_start_coo.y - 1){
                for (i = sprite->current_position.x; i < sprite->current_position.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x ; ++i){
                    if (sprite->char_table[j + sprite->drawing_start_coo.y - sprite->current_position.y][i + sprite->drawing_start_coo.x - sprite->current_position.x]  != ' ')
                    {
                        io_setCursorPos(i, j);
                        printf(" ");
                    }
                }
            }
            else {
                for (i = coordinates.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x - 1; i < sprite->current_position.x + sprite->drawing_end_coo.x - sprite->drawing_start_coo.x; ++i) {
                        if (sprite->char_table[j + sprite->drawing_start_coo.y - sprite->current_position.y][i + sprite->drawing_start_coo.x - sprite->current_position.x] != ' ') {
                            io_setCursorPos(i, j);
                            printf(" ");
                    }
                }
            }
	}
	else {
		io_clearSprite(sprite);
	}
	sprite->current_position = coordinates;
	io_printSprite(sprite);
}

void io_moveSpriteRelativ(io_Sprite* sprite, int x, int y){
	io_moveSpriteTo(sprite, io_coordinates(sprite->current_position.x + x, sprite->current_position.y + y));
	io_printSprite(sprite);
}

void io_centerPrintSprite(io_Sprite* sprite){
	sprite->current_position.x = (unsigned short) ((io_consoleWidth() - sprite->drawing_end_coo.x + sprite->drawing_start_coo.x) / 2);
	sprite->current_position.y = (unsigned short) ((io_consoleHeight() - sprite->drawing_end_coo.y + sprite->drawing_start_coo.y) / 2);
	io_printSprite(sprite);
}
