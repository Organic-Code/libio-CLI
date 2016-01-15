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

#include <io/input.h>
#include <io/cursor.h>
#include <io/console_management.h>

IO_BOOL io_yes(char* question, char default_ans)
{
	char answer;
	printf("%s [%c/%c]", question, default_ans == 1 ? 'Y' : 'y', default_ans == -1 ? 'N' : 'n');
	io_setEcho(IO_FALSE);
	do {
		answer = io_instantGetChar();
		answer = (char)tolower(answer);
		if (default_ans == 1) {
			if (answer != 'n') {
				answer = 'y';
			}
		} else {
			if (default_ans == -1) {
				if (answer != 'y') {
					answer = 'n';
				}
			}

		}
	}while (answer != 'y' && answer != 'n');
	io_setEcho(IO_TRUE);
	printf("%c\n", answer);
	return answer == 'y' ? IO_TRUE : IO_FALSE;

}
char* io_getNumber(unsigned char i_base, IO_BOOL with_brackets)
{
	unsigned short x_cursor_pos = 0;
	char user_input;
	char* output = NULL; /* char* to be returned by this function */

	if (i_base > 10)
		i_base = (unsigned char)(i_base + 'A' - 10); /* i_base is now the min char you may not input */
	else
		i_base = (unsigned char)(i_base + '0');

	io_setEcho( IO_FALSE );

	if (with_brackets)
	{
		++x_cursor_pos;
		printf("[ ]");
		io_cursorHorizontalMove( -2 );
	}

	do
	{
		user_input = io_instantGetChar();
		user_input = (char)toupper(user_input);

		/* Clearing any error message from the previous loop */
		printf("\n                              \r");

		/* Back to printing position */
		io_cursorVerticalMove( -1 );
		io_cursorHorizontalMove(x_cursor_pos);

		if (user_input != '\n' && (user_input < '0' || (user_input > '9' && user_input < 'A') || user_input > 'Z'))
		{
			/* if input == backspace */
			if (user_input == 127)
			{
				if ((x_cursor_pos > 1) || (!with_brackets && x_cursor_pos > 0)) /* If there is something to delete */
				{
					if (with_brackets)
						printf("\b ] \b\b\b"); /* '\b' has a similar effect to Cursorhorizontalmove( -1 ) */
					else
						printf("\b \b");
					--x_cursor_pos;

					output = (char*) realloc(output, (unsigned)(x_cursor_pos - (with_brackets ? 1 : 0))*sizeof(char)); /* Desallocating 1 char */
				}
			}
			else
			{
				printf("\n/!\\ %c : Not a Number\r", user_input);
				io_cursorVerticalMove( -1 );
				io_cursorHorizontalMove(x_cursor_pos);
			}

		}
		else
		{
			if (user_input != '\n')
			{
				if (user_input >= i_base)
				{
					printf("\n/!\\ %c : NaN in base %d\r", user_input, i_base >= 'A' ? i_base - 'A' + 10  : i_base - '0'); /* Display the base in decimal */
					io_cursorVerticalMove( -1 );
					io_cursorHorizontalMove(x_cursor_pos);
				}
				else
				{
					if (with_brackets)
						printf("%c ]\b\b", user_input);
					else
						printf("%c", user_input);
					++x_cursor_pos;
					output = (char*) realloc(output, (unsigned)(x_cursor_pos - (with_brackets ? 1 : 0))*sizeof(char)); /* Allocating 1 extra char */
					output[x_cursor_pos - 1 - (with_brackets ? 1 : 0)] = user_input; /* Adding 'user_input' at the end of the array */
				}
				user_input = 0;
			}
		}
	}while( user_input != '\n' );
	if (with_brackets)
		printf("] ");
	printf("\n");

	io_setEcho( IO_TRUE );

	if (x_cursor_pos > 1 || (x_cursor_pos > 0 && !with_brackets)) /* if the char* is not empty */
	{
		output = (char*) realloc(output, (unsigned)(x_cursor_pos + 1 - (with_brackets ? 1 : 0))*sizeof(char));
		output[x_cursor_pos - (with_brackets ? 1 : 0)] = '\0';
		return output;
	}
	else
	{
		free (output); /* Probably useless */
		return NULL;
	}
}

char io_instantGetChar()
{
	char key;
	struct termios original_settings, new_settings;
	tcgetattr(0, &original_settings);       /* retrieve the terminal settings */

	new_settings = original_settings;

	new_settings.c_lflag &= ~ICANON;        /* Allow getchar() to return without waiting '\n' */
	new_settings.c_cc[VMIN] = 1;            /* getchar() should read only 1 character */
	new_settings.c_cc[VTIME] = 0;           /* getchar() should wait for an input, forever. */
	tcsetattr(0, TCSANOW, &new_settings);   /* applies the new settings */

	key = (char)getchar();

	tcsetattr(0, TCSANOW, &original_settings); /* Back to original settings */
	return key;
}

unsigned long int io_getNumberWithinRange(unsigned long int min, unsigned long int max)
{
	char* input = NULL;
	unsigned long int output;

	do {
		input = io_getNumber(10, IO_FALSE);
		if (!io_isWithinRange(input, min, max, 10)) {
			printf("                                                     \r");
			free(input);
			input = NULL;
		}
	}while (input == 0);

	output = strtoul(input, NULL, 10);
	free(input);
	return output;
}

IO_BOOL io_isWithinRange(char* val, unsigned long int min, unsigned long int max, unsigned char base)
{
	unsigned long int value;

	if (val == NULL)
		return IO_FALSE;
	else
	{
		value = strtoul( val, NULL, base );

		if (value < min)
			return IO_FALSE;
		else if (value > max)
			return IO_FALSE;
		else
			return IO_TRUE;
	}
}
