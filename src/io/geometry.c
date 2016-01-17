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

#include <io/geometry.h>

/**
 * @brief computes the absolute value of a number
 * @param val Number
 * @return    The absolute value of val
 */
inline static double io_abs(double val);

/**
 * @brief Draws a vertical line
 * @param beg       Coordinate of an extremity of the line
 * @param height    Height of the line
 * @param draw_char Char to be drawn
 */
inline static void io_drawVerticalLine(io_Coordinates beg, unsigned short height, char draw_char);

/**
 * @brief Draws an horizontal line
 * @param beg       Coordinates of an extremity of the line
 * @param width     width of the line
 * @param draw_char Char to be drawn
 */
inline static void io_drawHorizontalLine(io_Coordinates beg, unsigned short width, char draw_char);

void io_drawFilledRectangle(io_Coordinates beg, io_Coordinates end, char draw_char){
	unsigned short width = end.x - beg.x, height = end.y - beg.y;
	unsigned short i;

	for (; height--;){
		io_setCursorPos(beg.x, beg.y + height);
		for (i = width; i--;)
			printf("%c", draw_char);
	}
}

void io_drawRectangle(io_Coordinates beg, io_Coordinates end, char draw_char){
	io_drawVerticalLine(beg, end.y - beg.y, draw_char);
	io_drawVerticalLine(io_setCoordinates(end.x, beg.y), end.y - beg.y, draw_char);
	io_drawHorizontalLine(beg, end.x - beg.x, draw_char);
	io_drawHorizontalLine(io_setCoordinates(beg.x, end.y), end.x - beg.x + 1, draw_char);
}

void io_drawLine(io_Coordinates beg, io_Coordinates end, char draw_char){
	if (end.x == beg.x) {
		io_drawVerticalLine(beg.y > end.y ? end : beg, io_abs(end.y - beg.y), draw_char);
	}
	else if (end.y == beg.y) {
		io_drawHorizontalLine(beg.x > end.x ? end : beg, io_abs(end.x - beg.x), draw_char);
	}
	else {
		double i = 0, a = ((double)(end.y - beg.y)/(double)(end.x - beg.x));
		int j;

		if (beg.x > end.x) {
			io_Coordinates tmp = beg;
			beg = end;
			end = tmp;
		}

		for (; i < io_abs(a) ; ++i) {
			for(j = 0 ; j <= io_abs(end.x - beg.x) ; ++j) {
				io_setCursorPos(j + beg.x, a * j + beg.y + i);
				printf("%c", draw_char);
			}
		}
	}
}

inline static void io_drawVerticalLine(io_Coordinates beg, unsigned short height, char draw_char){
	for (;height--;) {
		io_setCursorPos(beg.x, beg.y + height);
		printf("%c", draw_char);
	}
}

inline static void io_drawHorizontalLine(io_Coordinates beg, unsigned short width, char draw_char){
	io_setCursorPos(beg.x, beg.y);
	for(;width--;){
		printf("%c", draw_char);
	}
}

void io_drawCircle(io_Coordinates center, unsigned short radius, char draw_char){
	/* Andres' circle Algorithm */

	int x = 0;
	int y = radius;
	int d = radius - 1;

	while(y >= x){
		io_setCursorPos(center.x + x, center.y + y);
		printf("%c", draw_char);
		io_setCursorPos(center.x + y, center.y + x);
		printf("%c", draw_char);
		io_setCursorPos(center.x - x, center.y + y);
		printf("%c", draw_char);
		io_setCursorPos(center.x - y, center.y + x);
		printf("%c", draw_char);
		io_setCursorPos(center.x + x, center.y - y);
		printf("%c", draw_char);
		io_setCursorPos(center.x + y, center.y - x);
		printf("%c", draw_char);
		io_setCursorPos(center.x - x, center.y - y);
		printf("%c", draw_char);
		io_setCursorPos(center.x - y, center.y - x);
		printf("%c", draw_char);

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
}

void io_drawArch(io_Coordinates center, io_Coordinates first_point_of_arch, io_Coordinates last_point_of_arch, char draw_char){
	unsigned short radius;
	double angle1;
	double angle2;

	double x1 = first_point_of_arch.x - center.x;
	double y1 = first_point_of_arch.y - center.y;
	double x2 = last_point_of_arch.x - center.x;
	double y2 = -(last_point_of_arch.y - center.y);

	radius = sqrt(pow(x1, 2) + pow(y1, 2));

	if (io_abs(radius - sqrt(pow(x2, 2) + pow(y2, 2))) < 0.00001) {
		double stp;

		double x, y, i;

		angle1 = acos((double)(x1) / (double)(radius)) + (M_PI * (y1 < 0));
		angle2 = acos((double)(x2) / (double)(radius)) + (M_PI * (y2 < 0));
		angle2+= 2*M_PI*(angle1 > angle2);

		stp = 2 * radius * (angle2 - angle1) + 1;

		for (i = angle1 ; i < angle2 ; i += (angle2 - angle1 + 1) / stp)
		{
			x = radius*cos(i);
			y = radius*sin(i);
			io_setCursorPos((unsigned short)(center.x + x), (unsigned short)(center.y + y));
			printf("%c", draw_char);
		}
	}
}

inline static double io_abs(double val){
	if (val < 0) {
		return -val;
	}
	else {
		return val;
	}
}
