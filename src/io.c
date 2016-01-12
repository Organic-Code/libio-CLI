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

#include <io.h>

static char* io_current_bg_color = NULL;
static char* io_current_txt_color = NULL;
static BOOL io_cursor_visible = TRUE;
static BOOL io_echo_setting = TRUE;

/* pure output */
void io_clear()
{
	printf("\033[2J");	/* ANSI escape for clearing the screen */
	io_setCursorPos( 0, 0);
}

void io_centerPrint(char* text, unsigned short y_pos)
{
	unsigned short char_length = (unsigned short)strlen(text);
	unsigned short console_width = io_consoleWidth();

	if (char_length <= console_width)
	{
		io_setCursorPos((unsigned short)((console_width-char_length)/2), y_pos); /* sets the x cursor's coordinate at the center minus half of the char length. */
		printf("%s", text);
	}
}

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

/* input & output */

unsigned char io_menu(const char* choices, unsigned char nb_choices, unsigned char choice, char alignement, const char* text_color, const char* bg_color, const char* border_color)
{
	const char** text = malloc(nb_choices*sizeof(char*)); /* Array of pointers that will point on each choice */

	unsigned short max_length=0; /* Maximum size of a choice */
	unsigned short* length = (unsigned short*) calloc(nb_choices, sizeof(unsigned short)); /* Array containing each text's length. */

	unsigned short term_width = io_consoleWidth();
	unsigned short term_height = io_consoleHeight();

	unsigned short* x_text; /* x coordinate of each choice to print */
	unsigned short* y_text; /* same with y coo */
	unsigned short x_box; /* x coordinate of the menu's box */
	unsigned short y_box; /* same with y coo */

	unsigned short i, j = 0;

	char key_pressed;

	char* origin_bg_color;
	char* origin_txt_color;
	BOOL origin_cursor_visibility = io_cursor_visible;
	BOOL origin_echo_setting = io_echo_setting;

	if (io_current_bg_color != NULL){
		origin_bg_color = (char*) malloc((int)(strlen(io_current_bg_color) + 1) * sizeof(char));
		strcpy(origin_bg_color, io_current_bg_color);
	}
	else
		origin_bg_color = NULL;

	if (io_current_txt_color != NULL){
		origin_txt_color = (char*) malloc((int)(strlen(io_current_txt_color) + 1) * sizeof(char));
		strcpy(origin_txt_color, io_current_txt_color);
	}
	else
		origin_txt_color = (char*) malloc(sizeof(char));
	io_visibleCursor(FALSE);

	for (i = 0; i < nb_choices; ++i)
	{
		text[i] = choices+j; /* Points right after the last '\0' encountered */

		length[i] = (unsigned short)strlen(text[i]);
		if (length[i] > max_length)
		{
			max_length = length[i];
		}

		for (; choices[++j] != '\0';); /* increment until reaching a '\0' */
		++j; /* the next string starts right after that */
	}

	if (term_height < (nb_choices + 3) || term_width < (max_length + 3))
	{
		printf("Your screen is too small to have a nice display.\n");
		return 255;
	} /*else*/

	x_text = (unsigned short*) calloc(nb_choices, sizeof(unsigned short));
	y_text = (unsigned short*) calloc(nb_choices, sizeof(unsigned short));
	x_box = (unsigned short)(term_width - max_length - 2) / 2;
	y_box = (unsigned short)((term_height - nb_choices - 2) / 2);

	/* Border */
	io_setCursorPos( x_box, (unsigned short)(y_box-1));
	io_setBgColor(border_color);
	for (i = 0 ; i < max_length + 3 ; ++i)
		printf(" ");

	for (i = 0 ; i < nb_choices + 2 ; ++i)
	{
		io_setCursorPos( (unsigned short)(x_box + max_length + 2) , (unsigned short)(i + y_box) );
		printf(" ");
	}
	io_setBgColor(bg_color);
	io_setTextColor(text_color);

	/* The inside of the box */
	for (i = 0 ; i < nb_choices + 2 ; ++i)
	{
		io_setCursorPos( x_box, (unsigned short)(y_box + i));
		for (j = 0 ; j < max_length + 2 ; ++j)
		{
			printf(" ");
		}
	}

	/* Computation of each text coordinate and display */
	for (i = 0 ; i < nb_choices ; ++i)
	{
		switch(alignement)
		{
		case IO_CENTER:
			x_text[i] = (unsigned short) ((max_length + 2 - length[i]) / 2 + x_box);
			break;
		case IO_RIGHT:
			x_text[i] = (unsigned short) (x_box + max_length + 1 - length[i]);
			break;
		case IO_LEFT:
		default:
			x_text[i] = (unsigned short) (x_box + 1);
			break;
		}
		y_text[i] = (unsigned short) (y_box + i + 1);
		io_setCursorPos(x_text[i], y_text[i]);
		printf("%s", text[i]);
	}

	/* Printing default selection */
	io_setTextAttributes("+invert");
	io_setCursorPos(x_text[choice], y_text[choice]);
	printf("%s", text[choice]);
	io_setTextAttributes("-invert");
	io_setCursorPos(x_text[choice], y_text[choice]);

	/* We don't want arrow keys to display their weird stuff on the screen */
	io_setEcho( FALSE );

	/* j is used to store the current selected text */
	do
	{
		if (term_height != io_consoleHeight() || term_width != io_consoleWidth())
		{
			io_setCursorPos(0, 0);
			printf("Changing console size now is discouraged");
		}

		key_pressed = io_instantGetChar();
		if ((key_pressed == IO_SPECIAL_CHAR && io_instantGetChar() == '[') || key_pressed == '[') /* pressing an arrow inputs both SPECIAL, [, and a letter ; pressing pge up/down inputs [, a number, and ~ */
		{
			/* deselecting text */
			key_pressed = io_instantGetChar();
			io_setCursorPos(x_text[choice], y_text[choice]);
			printf("%s", text[choice]);

			switch (key_pressed)
			{
				case 'A':	/* Arrow up */
					if (choice == 0)
						choice = (unsigned char)(nb_choices - 1);
					else --choice;
					break;

				case 'B':	/* Arrow down */
					if (choice == nb_choices - 1)
						choice = 0;
					else ++choice;
					break;

				case '5':
					/* Page up */
					if (io_instantGetChar() == '~') {
						choice = 0;
					}
					break;

				case '6':
					/* Page Down */
					if (io_instantGetChar() == '~') {
						choice = (unsigned char)(nb_choices - 1);
					}
					break;

				default:
					break;
			}

			/* selecting text */
			io_setCursorPos(x_text[choice], y_text[choice]);
			io_setTextAttributes("+invert");
			printf("%s", text[choice]);
			io_setTextAttributes("-invert");
			io_setCursorPos(x_text[choice], y_text[choice]);
		}
	/* loop until the user press Enter */
	}while( key_pressed != '\n' );

	/* echo back to normal */
	io_setEcho(origin_echo_setting);
	io_setBgColor(origin_bg_color);
	io_setTextColor(origin_txt_color);
	io_visibleCursor(origin_cursor_visibility);
	free(text);
	free(x_text);
	free(y_text);
	free(length);
	free(origin_bg_color);
	free(origin_txt_color);
	return choice;
}

/* pure input */

BOOL io_yes(char* question, char default_ans)
{
	char answer;
	printf("%s [%c/%c]", question, default_ans == 1 ? 'Y' : 'y', default_ans == -1 ? 'N' : 'n');
	io_setEcho(FALSE);
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
	io_setEcho(TRUE);
	printf("%c\n", answer);
	return answer == 'y' ? TRUE : FALSE;

}
char* io_getNumber(unsigned char i_base, BOOL with_brackets)
{
	unsigned short x_cursor_pos = 0;
	char user_input;
	char* output = NULL; /* char* to be returned by this function */

	if (i_base > 10)
		i_base = (unsigned char)(i_base + 'A' - 10); /* i_base is now the min char you may not input */
	else
		i_base = (unsigned char)(i_base + '0');

	io_setEcho( FALSE );

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

	io_setEcho( TRUE );

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
		input = io_getNumber(10, FALSE);
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

/* inner functions */

io_Sprite* io_newSprite(unsigned short x_len, unsigned short y_len, char* char_table, char* txt_color, char*bg_color)
{
	io_Sprite* newsp = (io_Sprite*)malloc(sizeof(io_Sprite));

	newsp->current_position.x = newsp->current_position.y = 0;
	newsp->drawing_start_coo.x = newsp->drawing_start_coo.y = 0;
	newsp->drawing_end_coo.x = x_len;
	newsp->drawing_end_coo.y = y_len;
	newsp->x_size = x_len;
	newsp->y_size = y_len;
	newsp->char_table = char_table;
	newsp->txt_color = txt_color;
	newsp->bg_color = bg_color;
	newsp->draw_spaces = FALSE;

	return newsp;
}

io_Sprite* io_deleteSprite(io_Sprite* sprite)
{
	free(sprite);
	return NULL;
}

io_Sprite* io_printSpaces(io_Sprite* sprite, BOOL print_spaces)
{
	sprite->draw_spaces = print_spaces;
	return sprite;
}

io_Sprite* io_changeSpriteColor(io_Sprite* sprite, char* txt_color, char* bg_color)
{
	sprite->txt_color = txt_color;
	sprite->bg_color = bg_color;
	return sprite;
}

void io_visibleCursor(BOOL visible)
{
	io_cursor_visible = visible;
	if(visible)
		printf("\033[?25h");
	else
		printf("\033[?25l");
}

io_Sprite* io_usePartOfSprite(io_Sprite* sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end)
{
	if (drawing_beg.x <= sprite->x_size && drawing_beg.y <= sprite->y_size &&
		drawing_end.x <= sprite->x_size && drawing_end.y <= sprite->y_size &&
		drawing_beg.x <= drawing_end.x && drawing_beg.y <= drawing_beg.y) {

		sprite->drawing_start_coo = drawing_beg;
		sprite->drawing_end_coo = drawing_end;
	}

	return sprite;
}

io_Sprite* io_clearAndUsePart(io_Sprite* sprite, io_Coordinates drawing_beg, io_Coordinates drawing_end)
{
	io_clear();
	return io_usePartOfSprite(sprite, drawing_beg, drawing_end);
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

void io_setCursorPos(unsigned short x, unsigned short y)
{
	printf("\033[%d;%dH", (int)(y+1), (int)(x+1));
}

void io_cursorHorizontalMove(int x)
{
	if (x < 0)
		printf("\033[%dD", -x);
	else
		printf("\033[%dC", x);
	if (x == 0)
		printf("\b");

}

void io_cursorVerticalMove(int y)
{
	if (y < 0)
		printf("\033[%dA", -y);
	else
		printf("\033[%dB", y);
}

void io_setEcho(BOOL on)
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

BOOL io_isWithinRange(char* val, unsigned long int min, unsigned long int max, unsigned char base)
{
	unsigned long int value;

	if (val == NULL)
		return FALSE;
	else
	{
		value = strtoul( val, NULL, base );

		if (value < min)
			return FALSE;
		else if (value > max)
			return FALSE;
		else
			return TRUE;
	}
}
