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

#include <io/all.h>
#include <io/sprite_struct.h>

int main(void);
void basic_sample(void);
void geometry_sample(void);
void sprites_sample(void);


int main()
{
	unsigned char ans = 0;

    //Clearing screen
	io_clear();

	do{
        //Setting a bold font, for good measure
        io_setTextAttributes("+bold");

        //Invoking a basic menu with a title
		ans = io_menu("Geometry\0Basic\0Sprites\0Quit\0", "This is not a menu", ans, IO_CENTER, "white", "blue", "grey");

		switch(ans){
		case 0:
			geometry_sample();
			break;
		case 1:
			basic_sample();
			break;
		case 2:
			sprites_sample();
		default:
			break;
		}

        // It is important to reset the colors before clearing the screen, otherwise you may not have the default clearing color (for instance, you may have some green, purple,...)
        io_setTextAttributes("reset");
        io_clear();
	}while(ans != 3);

    io_visibleCursor(true);
    io_setEcho(true);
	return 0;
}

void basic_sample(){

	char key;
	io_Coordinates text;
	char colors[16][14] = {	"black", "red", "green", "yellow", "blue",
		"magenta", "cyan", "light grey", "grey", "light red",
		"light green", "light yellow", "light blue", "light magenta",
		"light cyan", "white" };
	unsigned char txtcol = 15, bgcol = 0;

	text.x = (unsigned short) (io_consoleWidth() / 2 - 27);
	text.y = (unsigned short) (io_consoleHeight() / 2);

	io_visibleCursor(false);
	io_setEcho(false);
	do{
		io_setTextAttributes("reset");
		io_clear();
		io_setBgColor(colors[bgcol]);
		io_setTextColor(colors[txtcol]);
		io_setCursorPos(text.x, text.y);
		printf("Use WASD to move and +/- to change colors (q to quit)");
		key = (char) toupper(io_getChar());

        //Avoiding people pressing arrow up (arrow up sends IO_SPECIAL_CHAR (escape), then A)
        if (key == IO_SPECIAL_CHAR)
            io_getCharTimed(0);

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
			bgcol = (unsigned char) ((bgcol + 1) % 16);
			break;
		case '-':
			txtcol = (unsigned char) ((txtcol + 1) % 16);
			break;
		default:
			break;
		}
	}while(key != 'Q');
	io_visibleCursor(true);
	io_setEcho(true);
}

void geometry_sample(){
	io_Coordinates coo, coo2, coo3, coo4;
	io_visibleCursor(false);
	io_setEcho(false);
	io_setBgColor("black");
	io_clear();

	coo = io_setCoordinates((unsigned short) (io_consoleWidth() / 3), 0);
	coo2 = io_setCoordinates((unsigned short) (2 * io_consoleWidth() / 3 + 1), (unsigned short) (io_consoleHeight() / 3));
	io_setBgColor("cyan");
	io_drawFilledRectangle(coo, coo2, ' ');

	coo.x = (unsigned short) (io_consoleWidth() / 3 + 1);
	coo2.y = coo3.y = 0;
	coo2.x = 1;
	coo3.x = io_consoleWidth();
	coo4.x = (unsigned short) (2 * io_consoleWidth() / 3);
	coo4.y = (unsigned short) (io_consoleHeight() / 3);
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
	
	coo = io_setCoordinates((unsigned short) (io_consoleWidth() / 3), (unsigned short) (io_consoleHeight() / 3));
	coo2 = io_setCoordinates((unsigned short) (2 * io_consoleWidth() / 3), (unsigned short) (2 * io_consoleHeight() / 3));
	io_setBgColor("blue");
	io_drawFilledRectangle(coo, coo2, ' ');

	io_setBgColor("light grey");
	io_drawRectangle(coo, coo2, ' ');

	coo = io_setCoordinates((unsigned short) (io_consoleWidth() / 2), (unsigned short) (io_consoleHeight() / 2));

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

	io_setEcho(true);
	if (io_getChar() == IO_SPECIAL_CHAR)
		(void) io_getCharTimed(0);
	io_visibleCursor(true);
}

void sprites_sample(){
	io_setTextAttributes("reset");
	io_clear();
    io_setEcho(false);
    io_visibleCursor(false);
    printf("Same as before : use WASD to move, and Q to quit");
    char* yolosprite[] = {
                "x--------x",
                "| o    o |",
                "|   oo   |",
                "|   o    |",
                "|    o   |",
                "|   o    |",
                "|        |",
                "|   oo   |",
                "| o    o |",
                "x--------x"
            };
    io_Sprite* yolo = io_newSprite(10, 10, yolosprite, "light blue", NULL);
    yolo = io_setPosition(yolo, io_setCoordinates(4,4));
    io_printSprite(yolo);
    char key;
    do {
        key = (char) toupper(io_getChar());

        //Avoiding people pressing arrow up (arrow up sends IO_SPECIAL_CHAR (escape), then A)
        if (key == IO_SPECIAL_CHAR)
            io_getCharTimed(0);

        switch (key){
            case 'W':
                if (yolo->current_position.y > 0) {
                    io_moveSpriteRelativ(yolo, 0, -1);
                }
                break;
            case 'A':
                if (yolo->current_position.x > 0) {
                    io_moveSpriteRelativ(yolo, -1, 0);
                }
                break;
            case 'S':
                if (yolo->current_position.y < io_consoleHeight() - yolo->y_size) {
                    io_moveSpriteRelativ(yolo, 0, 1);
                }
                break;
            case 'D':
                if (yolo->current_position.x < io_consoleWidth() - yolo->x_size) {
                    io_moveSpriteRelativ(yolo, 1, 0);
                }
            default:
                break;
        }
    }while(key != 'Q');
    io_setEcho(true);
	if (io_getChar() == IO_SPECIAL_CHAR)
		(void) io_getCharTimed(0);
    io_visibleCursor(true);
}
