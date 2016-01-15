#include <io/basic.h>

int main(void);


int main()
{
	io_setTextAttributes("+bold");
	io_clear();
	io_menu("Choice 1\0Choice 2\0Choice 3\0\0", "This is not a menu", 0, IO_CENTER, "white", "blue", "grey");
	io_setTextAttributes("reset");
	io_clear();
	return 0;
}
