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

#include <io/basic.h>
#include <io/geometry.h>

int main(void);
void basic_sample(void);
void geometry_sample(void);


int main()
{
	unsigned char ans;
	io_setTextAttributes("+bold");
	io_clear();
	do{
		ans = io_menu("Geometry\0Basic\0Quit\0", "This is not a menu", 0, IO_CENTER, "white", "blue", "grey");
		switch(ans){
		case 0:
			geometry_sample();
			break;
		case 1:
			basic_sample();
			break;
		default:
			break;
		}
		io_visibleCursor(IO_TRUE);
		io_setEcho(IO_TRUE);
		io_setTextAttributes("reset");
		io_clear();
	}while(ans != 2);
	return 0;
}

void basic_sample(){
	char key = '\0';
	io_Coordinates text;
	char colors[16][14] = {	"black", "red", "green", "yellow", "blue",
		"magenta", "cyan", "light grey", "grey", "light red",
		"light green", "light yellow", "light blue", "light magenta",
		"light cyan", "white" };
	unsigned char txtcol = 15, bgcol = 0;

	text.x = io_consoleWidth()/2 - 27;
	text.y = io_consoleHeight()/2;

	io_visibleCursor(IO_FALSE);
	io_setEcho(IO_FALSE);
	do{
		io_setTextAttributes("reset");
		io_clear();
		io_setBgColor(colors[bgcol]);
		io_setTextColor(colors[txtcol]);
		io_setCursorPos(text.x, text.y);
		printf("Use WASD to move and +/- to change colors (q to quit)");
		key = toupper(io_instantGetChar());
		switch (key){
		case 'W':
			if (text.y > 1) {
				--text.y;
			}
			break;
		case 'A':
			if (text.x > 1) {
				--text.x;
			}
			break;
		case 'S':
			if (text.y < io_consoleHeight() - 1) {
				++text.y;
			}
			break;
		case 'D':
			if (text.x < io_consoleWidth() - 54) {
				++text.x;
			}
			break;
		case '+':
			bgcol = (bgcol+1)%16;
			break;
		case '-':
			txtcol = (txtcol+1)%16;
			break;
		default:
			break;
		}
	}while(key != 'Q');
	io_visibleCursor(IO_TRUE);
	io_setEcho(IO_TRUE);
}

void geometry_sample(){
	io_Coordinates coo, coo2, coo3;
	io_visibleCursor(IO_FALSE);
	io_setEcho(IO_FALSE);
	io_setTextAttributes("reset");
	io_clear();
	coo = io_setCoordinates(io_consoleWidth() - 1, io_consoleHeight() - 1);
	coo2 = io_setCoordinates(1,1);
	io_setTextColor("white");
	io_setBgColor("white");
	io_drawLine(coo, coo2, 'L');
	coo = io_setCoordinates(io_consoleWidth() - 1, 1);
	coo2 = io_setCoordinates(1, io_consoleHeight() - 1);
	io_drawLine(coo, coo2, 'L');
	coo = io_setCoordinates(30, 1);
	coo2 = io_setCoordinates(30, 1);
	io_drawLine(coo2, coo, 'M');
	coo = io_setCoordinates(1, 1);
	coo2 = io_setCoordinates(10, 8);
	io_setTextColor("blue");
	io_setBgColor("blue");
	io_drawFilledRectangle(coo, coo2, '~');
	io_setBgColor("light grey");
	io_setTextColor("light grey");
	io_drawRectangle(coo, coo2, '#');
	coo = io_setCoordinates(20,20);
	coo2 = io_setCoordinates(25,15);
	coo3 = io_setCoordinates(40,30);
	io_drawCircle(coo, 5, 'o');
	io_setBgColor("red");
	io_setTextColor("red");
	io_drawCircle(coo, 4, 'o');
	io_setBgColor("yellow");
	io_setTextColor("yellow");
	io_drawCircle(coo, 3, 'o');
	io_setBgColor("green");
	io_setTextColor("green");
	io_drawCircle(coo, 2, 'o');
	io_setBgColor("light green");
	io_setTextColor("light green");
	io_drawCircle(coo, 1, 'o');
	coo = io_setCoordinates(40,15);
	io_drawArch(coo, coo2, coo3, 'A');
	io_setEcho(IO_TRUE);
	(void)io_instantGetChar();
	io_visibleCursor(IO_TRUE);
}
