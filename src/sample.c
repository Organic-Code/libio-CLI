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
	unsigned char ans = 0;
	io_setTextAttributes("+bold");
	io_clear();
	do{
		ans = io_menu("Geometry\0Basic\0Quit\0", "This is not a menu", ans, IO_CENTER, "white", "blue", "grey");
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
			if (text.y > 0) {
				--text.y;
			}
			break;
		case 'A':
			if (text.x > 0) {
				--text.x;
			}
			break;
		case 'S':
			if (text.y < io_consoleHeight() - 1) {
				++text.y;
			}
			break;
		case 'D':
			if (text.x < io_consoleWidth() - 53) {
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
	io_Coordinates coo, coo2, coo3, coo4;
	io_visibleCursor(IO_FALSE);
	io_setEcho(IO_FALSE);
	io_setBgColor("black");
	io_clear();

	coo = io_setCoordinates(io_consoleWidth() / 3, 0);
	coo2 = io_setCoordinates(2 * io_consoleWidth() / 3 + 1, io_consoleHeight() / 3);
	io_setBgColor("cyan");
	io_drawFilledRectangle(coo, coo2, ' ');

	coo.x = io_consoleWidth() / 3 + 1;
	coo2.y = coo3.y = 0;
	coo2.x = 1;
	coo3.x = io_consoleWidth();
	coo4.x = 2 * io_consoleWidth() / 3;
	coo4.y = io_consoleHeight() / 3;
	for(coo.y = coo4.y; coo.y ; --coo.y){
		io_drawLine(coo, coo2, ' ');
		coo4.y = coo.y;
		io_drawLine(coo4, coo3, ' ');
	}

	coo = io_setCoordinates(io_consoleWidth(), io_consoleHeight());
	coo2 = io_setCoordinates(0,0);
	io_setBgColor("grey");
	io_drawLine(coo, coo2, ' ');

	coo = io_setCoordinates(io_consoleWidth(), 0);
	coo2 = io_setCoordinates(0, io_consoleHeight());
	io_drawLine(coo, coo2, ' ');
	
	coo = io_setCoordinates(io_consoleWidth() / 3, io_consoleHeight() / 3);
	coo2 = io_setCoordinates(2 * io_consoleWidth() / 3, 2 * io_consoleHeight() / 3);
	io_setBgColor("blue");
	io_drawFilledRectangle(coo, coo2, ' ');

	io_setBgColor("light grey");
	io_drawRectangle(coo, coo2, ' ');

	coo = io_setCoordinates(io_consoleWidth()/2,io_consoleHeight()/2);

	io_drawCircle(coo, 5, ' ');
	io_setBgColor("red");
	io_drawCircle(coo, 4, ' ');
	io_setBgColor("yellow");
	io_drawCircle(coo, 3, ' ');
	io_setBgColor("green");
	io_drawCircle(coo, 2, ' ');
	io_setBgColor("light green");
	io_drawCircle(coo, 1, ' ');
	io_drawCircle(coo, 8, ' ');

	io_setEcho(IO_TRUE);
	if (io_instantGetChar() == IO_SPECIAL_CHAR)
		(void)io_instantGetChar();
	io_visibleCursor(IO_TRUE);
}
