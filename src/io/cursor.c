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

#include <io/cursor.h>

void io_setCursorPos(unsigned short x, unsigned short y)
{
	printf("\033[%d;%dH", y + 1, x + 1);
	fflush(stdout);
}

void io_cursorHorizontalMove(int x)
{
	if (x < 0)
		printf("\033[%dD", -x);
	else if (x > 0)
		printf("\033[%dC", x);
	fflush(stdout);
}

void io_cursorVerticalMove(int y)
{
	if (y < 0)
		printf("\033[%dA", -y);
	else
		printf("\033[%dB", y);
	fflush(stdout);
}

void io_saveCursorPosition(void)
{
	printf("\033[s");
}

void io_restoreCursorPosition(void)
{
	printf("\033[u");
}