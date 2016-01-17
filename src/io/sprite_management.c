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

/**
 * @brief computes the absolute value of a number
 * @param val Number
 * @return    The absolute value of val
 */
inline static double io_abs(double val);

/**
 * @brief Prints a vertical line in the given sprite
 * @param sprite    Sprite to edit
 * @param beg       Coordinate of an extremity of the line
 * @param height    Height of the line
 * @param draw_char Char to be drawn
 * @return          The sprite
 */
inline static void io_drawVerticalLineIn(io_Sprite* sprite, io_Coordinates beg, unsigned short height, char draw_char);

/**
 * @brief Prints an horizontal line in the given sprite
 * @param sprite    Sprite to edit
 * @param beg       Coordinates of an extremity of the line
 * @param width     width of the line
 * @param draw_char Char to be drawn
 */
inline static void io_drawHorizontalLineIn(io_Sprite* sprite, io_Coordinates beg, unsigned short width, char draw_char);

io_Sprite* io_newSprite(unsigned short x_len, unsigned short y_len, char** char_table, char* txt_color, char*bg_color)
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

inline static double io_abs(double val){
	if (val < 0) {
			return -val;
		}
	else {
			return val;
		}
}

io_Sprite* io_drawFilledRectangleIn(io_Sprite* sprite, io_Coordinates beg, io_Coordinates end, char draw_char){
	unsigned short width = end.x - beg.x, height = end.y - beg.y;
	unsigned short i;

	for (; height--;)
		for (i = width; i--;)
			sprite->char_table[beg.y + height][beg.x + i] = draw_char;
	return sprite;
}

io_Sprite* io_drawRectangleIn(io_Sprite* sprite, io_Coordinates beg, io_Coordinates end, char draw_char){
	io_drawVerticalLineIn(sprite, beg, end.y - beg.y, draw_char);
	io_drawVerticalLineIn(sprite, io_setCoordinates(end.x, beg.y), end.y - beg.y, draw_char);
	io_drawHorizontalLineIn(sprite, beg, end.x - beg.x, draw_char);
	io_drawHorizontalLineIn(sprite, io_setCoordinates(beg.x, end.y), end.x - beg.x + 1, draw_char);
	return sprite;
}

io_Sprite* io_drawLineIn(io_Sprite* sprite, io_Coordinates beg, io_Coordinates end, char draw_char){
	if (end.x == beg.x) {
		io_drawVerticalLineIn(sprite, beg.y > end.y ? end : beg, io_abs(end.y - beg.y), draw_char);
	}
	else if (end.y == beg.y) {
		io_drawHorizontalLineIn(sprite, beg.x > end.x ? end : beg, io_abs(end.x - beg.x), draw_char);
	}
	else {
		if (beg.x > end.x) {
			io_Coordinates tmp = beg;
			beg = end;
			end = tmp;
		}
		double i = 0, a = ((double)(end.y - beg.y)/(double)(end.x - beg.x));
		int j;

		for (; i < io_abs(a) ; ++i)
			for(j = 0 ; j <= io_abs(end.x - beg.x) ; ++j)
				sprite->char_table[(int)(a * j + beg.y + i)][j + beg.x] = draw_char;
	}
	return sprite;
}

inline static void io_drawVerticalLineIn(io_Sprite* sprite, io_Coordinates beg, unsigned short height, char draw_char){
	for (;height--;)
		sprite->char_table[beg.y + height][beg.x] = draw_char;
}

inline static void io_drawHorizontalLineIn(io_Sprite* sprite, io_Coordinates beg, unsigned short width, char draw_char){
	for(;width--;)
		sprite->char_table[beg.y][beg.x + width] = draw_char;
}

io_Sprite* io_drawCircleIn(io_Sprite* sprite, io_Coordinates center, unsigned short radius, char draw_char){
	/* Andres' circle Algorithm */

	int x = 0;
	int y = radius;
	int d = radius - 1;

	while(y >= x){
		sprite->char_table[center.y + y][center.x + x] = draw_char;
		sprite->char_table[center.y + x][center.x + y] = draw_char;
		sprite->char_table[center.y + y][center.x - x] = draw_char;
		sprite->char_table[center.y + x][center.x - y] = draw_char;
		sprite->char_table[center.y - y][center.x + x] = draw_char;
		sprite->char_table[center.y - x][center.x + y] = draw_char;
		sprite->char_table[center.y - y][center.x - x] = draw_char;
		sprite->char_table[center.y - x][center.x - y] = draw_char;

		if (d >= 2*x){
			d -= 2*x + 1;
			++x;
		}
		else if (d < 2 * (radius - y)){
			d += 2*y - 1;
			--y;
		}
		else{
			d += 2*(y - x - 1);
			--y;
			++x;
		}
	}
	return sprite;
}

io_Sprite* io_drawArchIn(io_Sprite* sprite, io_Coordinates center, io_Coordinates first_point_of_arch, io_Coordinates last_point_of_arch, char draw_char){
	
	unsigned short radius;
	double angle1;
	double angle2;

	double x1 = first_point_of_arch.x - center.x;
	double y1 = first_point_of_arch.y - center.y;
	double x2 = last_point_of_arch.x - center.x;
	double y2 = -(last_point_of_arch.y - center.y);

	radius = sqrt(pow(x1, 2) + pow(y1, 2));

	if (io_abs(radius - sqrt(pow(x2, 2) + pow(y2, 2))) < 0.00001) {
		angle1 = acos((double)(x1) / (double)(radius)) + (M_PI * (y1 < 0));
		angle2 = acos((double)(x2) / (double)(radius)) + (M_PI * (y2 < 0));
		angle2+= 2*M_PI*(angle1 > angle2);

		double stp = 2 * radius * (angle2 - angle1) + 1;

		double x, y, i;
		for (i = angle1 ; i < angle2 ; i += (angle2 - angle1 + 1) / stp)
		{
			x = radius*cos(i);
			y = radius*sin(i);
			sprite->char_table[(int)(center.y + y)][(int)(center.x + x)] = draw_char;
		}
	}
	return sprite;
}
