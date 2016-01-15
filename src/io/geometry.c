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

void io_drawFilledRectangle(io_Coordinates beg, io_Coordinates end, char draw_char){
	unsigned short width, height;
	unsigned short i, j;
	if (beg.x > end.x && end.y > beg.y){
		io_Coordinates tmp = end;
		end = beg;
		beg = tmp;
	}
	width = end.x - beg.x;
	height = end.y - beg.y;
	io_setCursorPos(beg.x, beg.y);

	for (i = height; i--;){
		io_setCursorPos(beg.x, beg.y + i);
		for (j = width; j--;)
			printf("%c", draw_char);
	}
	end.x = 0;
	draw_char = 'a';
}

void io_drawRectangle(io_Coordinates beg, io_Coordinates end, char draw_char){
	io_Coordinates out;
	out.x = end.x;
	out.y = beg.y;
	io_drawLine(beg, out, draw_char);
	io_drawLine(out, end, draw_char);
	out.x = beg.x;
	out.y = end.y;
	io_drawLine(beg, out, draw_char);
	io_drawLine(out, end, draw_char);
}

void io_drawLine(io_Coordinates beg, io_Coordinates end, char draw_char){
	unsigned short j, i, a;

	if (end.x == beg.x) {
		io_drawVerticalLine(beg, end.y - beg.y, draw_char);
	}

	a = (unsigned short)((double)(end.y - beg.y)/(double)(end.x - beg.x));

	for (i = a; i-- ;){
		for(j = end.x - beg.x ; j-- ;)
		{
			io_setCursorPos(j + beg.x, a * j + beg.y + i);
			printf("%c", draw_char);
		}
	}
}

void io_drawVerticalLine(io_Coordinates beg, unsigned short height, char draw_char){
	unsigned short i;
	
	for (i = height ; i--;) {
		io_setCursorPos(beg.x, beg.y + i);
		printf("%c", draw_char);
	}
}

void io_drawDotedLine(io_Coordinates beg, io_Coordinates end, char draw_char){
	unsigned short a, i;

	if (end.x == beg.x) {
		io_drawVerticalLine(beg, end.y - beg.y, draw_char);
	}

	a=(unsigned short)((end.y - beg.y) / (end.x - beg.x));

	for (i = end.x - end.y ; i-- ;)
	{
		io_setCursorPos(i + beg.x, a * i + beg.y);
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

	first_point_of_arch.x-=center.x;
	first_point_of_arch.y-=center.y;
	last_point_of_arch.x-=center.x;
	last_point_of_arch.y-=center.y;
	radius = sqrt(pow((double)first_point_of_arch.x, 2)+pow((double)first_point_of_arch.y, 2));
	angle1 = acos((double)(first_point_of_arch.x/radius)) + (M_PI*(first_point_of_arch.y<0));
	angle2 = acos((double)(last_point_of_arch.x/radius)) + (M_PI*(last_point_of_arch.y<0));
	angle2+= 2*M_PI*(angle1>angle2);

	double x, y, i;
	for (i = angle1 ; i < angle2 ; i += (angle2 - angle1 + 1) / (3.5 * radius))
	{
		x = radius*cos(i);
		y = radius*sin(i);
		io_setCursorPos(center.x + x, center.y + y);
		printf("%c", draw_char);
	}
}
