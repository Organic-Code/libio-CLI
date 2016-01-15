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

#include <io/console_management.h>

static char* io_current_bg_color = NULL;
static char* io_current_txt_color = NULL;
static IO_BOOL io_cursor_visible = IO_TRUE;
static IO_BOOL io_echo_setting = IO_TRUE;

void io_setTextAttributes(const char* attribute)
{
	if (attribute != NULL) {
		switch (attribute[0])
		{
			case '+':
				++attribute;
				if (!strcmp(attribute, "bold"))               printf("\033[1m");/*break*/
				else if (!strcmp(attribute, "dim"))           printf("\033[2m");/*break*/
				else if (!strcmp(attribute, "underline"))     printf("\033[4m");/*break*/
				else if (!strcmp(attribute, "blink"))         printf("\033[5m");/*break*/
				else if (!strcmp(attribute, "invert"))        printf("\033[7m");/*break*/
				else if (!strcmp(attribute, "strike"))        printf("\033[8m");/*break*/
				--attribute;
				break;
			case '-':
				++attribute;
				if (!strcmp(attribute, "bold"))               printf("\033[21m");/*break*/
				else if (!strcmp(attribute, "dim"))           printf("\033[22m");/*break*/
				else if (!strcmp(attribute, "underline"))     printf("\033[24m");/*break*/
				else if (!strcmp(attribute, "blink"))         printf("\033[25m");/*break*/
				else if (!strcmp(attribute, "invert"))        printf("\033[27m");/*break*/
				else if (!strcmp(attribute, "strike"))        printf("\033[29m");/*break*/
				--attribute;
				break;
			default:
				if (!strcmp(attribute, "reset"))               printf("\033[0m");/*break*/
				break;
		}
	}

}
void io_setBgColor(const char* color)
{
	if (color != NULL) {
		if (!strcmp(color, "black"))                                  printf("\033[40m");/*break*/
		else if (!strcmp(color, "red"))                               printf("\033[41m");/*break*/
		else if (!strcmp(color, "green"))                             printf("\033[42m");/*break*/
		else if (!strcmp(color, "yellow"))                            printf("\033[43m");/*break*/
		else if (!strcmp(color, "blue"))                              printf("\033[44m");/*break*/
		else if (!strcmp(color, "magenta"))                           printf("\033[45m");/*break*/
		else if (!strcmp(color, "cyan"))                              printf("\033[46m");/*break*/
		else if (!strcmp(color, "light grey"))                        printf("\033[47m");/*break*/
		else if (!strcmp(color, "grey"))                              printf("\033[100m");/*break*/
		else if (!strcmp(color, "light red"))                         printf("\033[101m");/*break*/
		else if (!strcmp(color, "light green"))                       printf("\033[102m");/*break*/
		else if (!strcmp(color, "light yellow"))                      printf("\033[103m");/*break*/
		else if (!strcmp(color, "light blue"))                        printf("\033[104m");/*break*/
		else if (!strcmp(color, "light magenta"))                     printf("\033[105m");/*break*/
		else if (!strcmp(color, "light cyan"))                        printf("\033[106m");/*break*/
		else if (!strcmp(color, "white"))                             printf("\033[107m");/*break*/

		free(io_current_bg_color);
		io_current_bg_color = (char*) malloc((int)(strlen(color) + 1) * sizeof(char));
		strcpy(io_current_bg_color, color);
	}
}

void io_setTextColor(const char* color)
{
	if (color != NULL) {
		if (!strcmp(color, "black"))                                  printf("\033[8m"); /*break*/
		else if (!strcmp(color, "grey"))                              printf("\033[30m");/*break*/
		else if (!strcmp(color, "red"))                               printf("\033[31m");/*break*/
		else if (!strcmp(color, "green"))                             printf("\033[32m");/*break*/
		else if (!strcmp(color, "yellow"))                            printf("\033[33m");/*break*/
		else if (!strcmp(color, "blue"))                              printf("\033[34m");/*break*/
		else if (!strcmp(color, "magenta"))                           printf("\033[35m");/*break*/
		else if (!strcmp(color, "cyan"))                              printf("\033[36m");/*break*/
		else if (!strcmp(color, "light grey"))                        printf("\033[37m");/*break*/
		else if (!strcmp(color, "light red"))                         printf("\033[91m");/*break*/
		else if (!strcmp(color, "light green"))                       printf("\033[92m");/*break*/
		else if (!strcmp(color, "light yellow"))                      printf("\033[93m");/*break*/
		else if (!strcmp(color, "light blue"))                        printf("\033[94m");/*break*/
		else if (!strcmp(color, "light magenta"))                     printf("\033[95m");/*break*/
		else if (!strcmp(color, "light cyan"))                        printf("\033[96m");/*break*/
		else if (!strcmp(color, "white"))                             printf("\033[97m");/*break*/

		free(io_current_txt_color);
		io_current_txt_color = (char*) malloc((int)(strlen(color) + 1) * sizeof(char));
		strcpy(io_current_txt_color, color);

	}
}

void io_visibleCursor(IO_BOOL visible)
{
	io_cursor_visible = visible;
	if(visible)
		printf("\033[?25h");
	else
		printf("\033[?25l");
}

unsigned short io_consoleHeight()
{
	struct winsize ws = { 0, 0, 0, 0 };
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return 0;

	return ws.ws_row;
}

unsigned short io_consoleWidth()
{
	struct winsize ws = { 0, 0, 0, 0 };
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return 0;

	return ws.ws_col;
}

void io_setEcho(IO_BOOL on)
{
	struct termios tty;

	io_echo_setting = on;
	tcgetattr(STDIN_FILENO, &tty);
	if (on)
		tty.c_lflag |= ECHO;
	else
		tty.c_lflag &= ~ECHO;

	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

char* io_currentBgColor(){ return io_current_bg_color; }
char* io_currentTxtColor(){ return io_current_txt_color; }
IO_BOOL io_cursorVisible(){ return io_cursor_visible; }
IO_BOOL io_echoSetting(){ return io_echo_setting; }
