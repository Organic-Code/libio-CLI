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

/* TODO */
void io_drawFilledRectangle(io_Coordinates beg, io_Coordinates end, char draw_char){
	beg.x = 0;
	end.x = 0;
	draw_char = 'a';
}

/* TODO */
void io_drawRectangle(io_Coordinates beg, io_Coordinates end, char draw_char){
	beg.x = 0;
	end.x = 0;
	draw_char = 'a';
}

/* TODO */
void io_drawLine(io_Coordinates beg, io_Coordinates end, char draw_char){
	beg.x = 0;
	end.x = 0;
	draw_char = 'a';
}

/* TODO */
void io_drawDotedLine(io_Coordinates beg, io_Coordinates end, char draw_char){
	beg.x = 0;
	end.x = 0;
	draw_char = 'a';
}

/* TODO */
void io_drawCircle(io_Coordinates center, unsigned short radius, char draw_char){
	center.x = 0;
	radius = 0;
	draw_char = 'a';
}

/* TODO */
IO_BOOL io_drawArch(io_Coordinates center, io_Coordinates first_point_of_arch, io_Coordinates last_point_of_arch, char draw_char){
	center.x = 0;
	first_point_of_arch.x = 0;
	last_point_of_arch.x = 0;
	draw_char = 'a';
	return IO_TRUE;
}
