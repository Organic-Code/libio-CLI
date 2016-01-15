#include <io/basic.h>
#include <io/geometry.h>

int main(void);


int main()
{
	io_Coordinates coo;
	io_Coordinates coo2;
	io_Coordinates coo3;
	io_setTextAttributes("+bold");
	io_clear();
	io_visibleCursor(IO_FALSE);
	switch(io_menu("Geometry\0Choice 2\0Choice 3\0", "This is not a menu", 0, IO_CENTER, "white", "blue", "grey"))
	{
	case 0:
		io_setTextColor("white");
		io_setBgColor("black");
		io_clear();
		coo = io_setCoordinates(1, 1);
		coo2 = io_setCoordinates( 10, 8);
		io_setTextColor("blue");
		io_setBgColor("blue");
		io_drawFilledRectangle(coo, coo2, '~');
		io_setBgColor("black");
		io_drawRectangle(coo, coo2, '#');
		coo = io_setCoordinates(20,20);
		coo2 = io_setCoordinates(15,20);
		coo3 = io_setCoordinates(20,15);
		io_drawCircle(coo, 5, 'o');
		io_setTextColor("red");
		io_drawArch(coo, coo2, coo3, 'A');
		coo = io_setCoordinates(io_consoleWidth(), io_consoleHeight());
		coo2 = io_setCoordinates(0,0);
		io_setTextColor("white");
		io_setBgColor("white");
		io_drawLine(coo, coo2, '*');
		coo = io_setCoordinates(io_consoleWidth(), 0);
		coo2 = io_setCoordinates(io_consoleHeight(), 0);
		(void)io_instantGetChar();
		break;
	}
	io_setTextAttributes("reset");
	io_clear();
	return 0;
}
