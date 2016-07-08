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

static char io_current_bg_color[14];
static char io_current_txt_color[14];
static bool io_cursor_visible = true;
static bool io_echo_setting = true;

void io_setTextAttributes(const char* attribute)
{	if (!strcmp(attribute, "reset")) {
		printf("\033[0m");
		io_current_bg_color[0] = '\0';
		io_current_txt_color[0] = '\0';
	} else {
		printf("%s", io_getTextAttributesString(attribute));
	}
	fflush(stdout);
}

const char* io_getTextAttributesString(const char* attribute)
{
	assert(attribute != NULL);
	switch (attribute[0])
	{
		case '+':
			++attribute;
			if (!strcmp(attribute, "bold"))               return "\033[1m";
			else if (!strcmp(attribute, "dim"))           return "\033[2m";
			else if (!strcmp(attribute, "underline"))     return "\033[4m";
			else if (!strcmp(attribute, "blink"))         return "\033[5m";
			else if (!strcmp(attribute, "invert"))        return "\033[7m";
			else if (!strcmp(attribute, "strike"))        return "\033[8m";
			break;
		case '-':
			++attribute;
			if (!strcmp(attribute, "bold"))               return "\033[21m";
			else if (!strcmp(attribute, "dim"))           return "\033[22m";
			else if (!strcmp(attribute, "underline"))     return "\033[24m";
			else if (!strcmp(attribute, "blink"))         return "\033[25m";
			else if (!strcmp(attribute, "invert"))        return "\033[27m";
			else if (!strcmp(attribute, "strike"))        return "\033[29m";
			break;
		default:
			if (!strcmp(attribute, "reset")) {
				return "\033[0m";
			}
			break;
	}
	return "";
}

void io_setBgColor(const char* color)
{
	printf("%s", io_getBgColorString(color));
	fflush(stdout);

	assert(strlen(color) < 14);
	strcpy(io_current_bg_color, color);
}

const char* io_getBgColorString(const char* color)
{
	assert(color != NULL);
	if (!strcmp(color, "black"))                                  return "\033[40m";
	else if (!strcmp(color, "red"))                               return "\033[41m";
	else if (!strcmp(color, "green"))                             return "\033[42m";
	else if (!strcmp(color, "yellow"))                            return "\033[43m";
	else if (!strcmp(color, "blue"))                              return "\033[44m";
	else if (!strcmp(color, "magenta"))                           return "\033[45m";
	else if (!strcmp(color, "cyan"))                              return "\033[46m";
	else if (!strcmp(color, "light grey"))                        return "\033[47m";
	else if (!strcmp(color, "grey"))                              return "\033[100m";
	else if (!strcmp(color, "light red"))                         return "\033[101m";
	else if (!strcmp(color, "light green"))                       return "\033[102m";
	else if (!strcmp(color, "light yellow"))                      return "\033[103m";
	else if (!strcmp(color, "light blue"))                        return "\033[104m";
	else if (!strcmp(color, "light magenta"))                     return "\033[105m";
	else if (!strcmp(color, "light cyan"))                        return "\033[106m";
	else if (!strcmp(color, "white"))                             return "\033[107m";
	return "";
}

void io_setTextColor(const char* color)
{
	printf("%s", io_getTextColorString(color));
	fflush(stdout);

	assert(strlen(color) < 14);
	strcpy(io_current_txt_color, color);
}

const char* io_getTextColorString(const char* color)
{
	assert(color != NULL);
	if (!strcmp(color, "black"))                                  return"\033[8m";
	else if (!strcmp(color, "grey"))                              return"\033[30m";
	else if (!strcmp(color, "red"))                               return"\033[31m";
	else if (!strcmp(color, "green"))                             return"\033[32m";
	else if (!strcmp(color, "yellow"))                            return"\033[33m";
	else if (!strcmp(color, "blue"))                              return"\033[34m";
	else if (!strcmp(color, "magenta"))                           return"\033[35m";
	else if (!strcmp(color, "cyan"))                              return"\033[36m";
	else if (!strcmp(color, "light grey"))                        return"\033[37m";
	else if (!strcmp(color, "light red"))                         return"\033[91m";
	else if (!strcmp(color, "light green"))                       return"\033[92m";
	else if (!strcmp(color, "light yellow"))                      return"\033[93m";
	else if (!strcmp(color, "light blue"))                        return"\033[94m";
	else if (!strcmp(color, "light magenta"))                     return"\033[95m";
	else if (!strcmp(color, "light cyan"))                        return"\033[96m";
	else if (!strcmp(color, "white"))                             return"\033[97m";
	return "";
}

void io_visibleCursor(bool visible)
{
	io_cursor_visible = visible;
	if(visible)
		printf("\033[?25h");
	else
		printf("\033[?25l");
	fflush(stdout);
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

void io_setEcho(bool on)
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
bool io_cursorVisible(){ return io_cursor_visible; }
bool io_echoSetting(){ return io_echo_setting; }
