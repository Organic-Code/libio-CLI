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

#include <io/output.h>

void io_clear()
{
	printf("\033[2J");	/* ANSI escape for clearing the screen */
	io_setCursorPos( 0, 0);
	fflush(stdout);
}

void io_print(int options, unsigned short y_pos, char key, const char* format, ...)
{
	char text[512];
	va_list valist;
	va_start(valist, format);
	unsigned char char_length;
	if ((char_length = vsprintf(text, format, valist)) < 0){
		va_end(valist);
		return;
	}
	va_end(valist);
    unsigned short x_pos;

    if (options & IO_CENTER){
        unsigned short console_width = io_consoleWidth();

        assert(char_length <= console_width);
        x_pos = (unsigned short) ((console_width - char_length) / 2);
        io_setCursorPos(x_pos, y_pos); /* sets the x cursor's coordinate at the center minus half of the char length. */
    } else if (options & IO_RIGHT){
        unsigned short console_width = io_consoleWidth();

        assert(char_length <= console_width);
        x_pos = console_width - char_length;
        io_setCursorPos(x_pos , y_pos); /* sets the x cursor's coordinate at the center minus half of the char length. */
    } else {
        x_pos = 1;
        io_setCursorPos(1 , y_pos);
    }

    if (options & IO_BLINK){
        char press;
        unsigned short i;
		fflush(stdin);

        if (options & IO_TYPEWRITE){
            unsigned short j = 1;
            do {
				struct timeb t1, t2;
                io_setCursorPos(x_pos, y_pos);
                for (i = 0 ; i < j ; ++i) {
                    printf("%c", text[i]);
                    fflush(stdout);
                }
				ftime(&t1);
                press = io_getCharTimed(5);
				if (key == 0 && press != -1){
					press = key;
				}

				if (press != -1 && press != key){
					ftime(&t2);
					unsigned int time_enlapsed = (unsigned int)fabs(t2.millitm - t1.millitm);
					if (time_enlapsed < 500) {
						usleep((500 - time_enlapsed) * 1000);
					}
				}
				io_setCursorPos(x_pos, y_pos);
				for (i = 0 ; i < j ; ++i){
					printf(" ");
				}
				fflush(stdout);
				if (press != key) {
					ftime(&t1);
					press = io_getCharTimed(5);
					if (key == 0 && press != -1) {
						press = 0;
					}

					if (press != -1 && press != key){
						ftime(&t2);
						unsigned int time_enlapsed = (unsigned int)fabs(t2.millitm - t1.millitm);
						if (time_enlapsed < 500) {
							usleep((500 - time_enlapsed) * 1000);
						}
					}
				}
                j += 2;
				if (j > char_length){
					j = char_length;
				}
            }while(press != key);
		}
        else{
            do {
                io_setCursorPos(x_pos, y_pos);
                printf("%s", text);
                fflush(stdout);
                press = io_getCharTimed(5);
				if (key == 0 && press != -1){
					press = 0;
				}
                io_setCursorPos(x_pos, y_pos);
                for (i = 0 ; i < char_length ; ++i){
					printf(" ");
				}
				fflush(stdout);
				if (press != key) {
					press = io_getCharTimed(5);
					if (key == 0 && press != -1) {
						press = 0;
					}
				}
            }while(press != key);
        }
    }
    else{
        if (options & IO_TYPEWRITE){
            bool previous_param = io_cursorVisible();
            io_visibleCursor(true);
            unsigned short i;
			char press = -1;
            for (i = 0 ; i < char_length ; ++i) {
                printf("%c", text[i]);
                fflush(stdout);
				if (press != key){
					press = io_getCharTimed(1);
				}
            }
            io_visibleCursor(previous_param);
        }
        else{
            printf("%s", text);
            fflush(stdout);
        }
    }
}
unsigned char io_menu(const char* choices, const char* title, unsigned char default_choice, char alignement, const char* text_color, const char* bg_color, const char* border_color)
{
	const char** text;

	unsigned short max_length=0; /* Maximum size of a choice */
	unsigned short* length;

	unsigned short term_width = io_consoleWidth();
	unsigned short term_height = io_consoleHeight();

	unsigned short* x_text; /* x coordinate of each choice to print */
	unsigned short* y_text; /* same with y coo */
	unsigned short x_box; /* x coordinate of the menu's box */
	unsigned short y_box; /* same with y coo */

	unsigned short i = 0, j = 0;
	
	unsigned char nb_choices = 1;

	char key_pressed;

	char* origin_bg_color = io_currentBgColor();
	char* origin_txt_color = io_currentTxtColor();
	bool origin_cursor_visibility = io_cursorVisible();
	bool origin_echo_setting = io_echoSetting();

	if (origin_bg_color != NULL){
		origin_bg_color = (char*) malloc((int)(strlen(origin_bg_color) + 1) * sizeof(char));
		strcpy(origin_bg_color, io_currentBgColor());
	}

	if (origin_txt_color != NULL){
		origin_txt_color = (char*) malloc((int)(strlen(origin_txt_color) + 1) * sizeof(char));
		strcpy(origin_txt_color, io_currentTxtColor());
	}

	io_visibleCursor(false);

	while (choices[i] != '\0' || choices[i+1] != '\0'){
		if (choices[i] == '\0') {
			++nb_choices;
		}
		++i;
	}
	length = (unsigned short*)calloc(nb_choices, sizeof(unsigned short));
	text = malloc(nb_choices*sizeof(char*));


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

	if (title != NULL) {
		j = (unsigned short) strlen(title);
	}
	else{
		j = 0;
	}
	if (j > max_length) {
		max_length = j;
	}

	x_text = (unsigned short*) calloc(nb_choices, sizeof(unsigned short));
	y_text = (unsigned short*) calloc(nb_choices, sizeof(unsigned short));
	x_box = (unsigned short)((term_width - max_length - 2) / 2);
	y_box = (unsigned short)((term_height - nb_choices - 2) / 2);

	/* Border */
	if (border_color != NULL) {
		io_setCursorPos( x_box, (unsigned short)(y_box-1));
		io_setBgColor(border_color);
		for (i = 0 ; i < max_length + 3 ; ++i)
			printf(" ");

		for (i = 0 ; i < nb_choices + 2 ; ++i)
		{
			io_setCursorPos( (unsigned short)(x_box + max_length + 2) , (unsigned short)(i + y_box) );
			printf(" ");
		}
	}

	if (title != NULL) {
		io_print(IO_CENTER, (unsigned short)(y_box-1), 0, title);
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
	io_setCursorPos(x_text[default_choice], y_text[default_choice]);
	printf("%s", text[default_choice]);
	io_setTextAttributes("-invert");
	io_setCursorPos(x_text[default_choice], y_text[default_choice]);

	/* We don't want arrow keys to display their weird stuff on the screen */
	io_setEcho( false );

	/* j is used to store the current selected text */
	do
	{
		if (term_height != io_consoleHeight() || term_width != io_consoleWidth())
		{
			io_setCursorPos(0, 0);
			printf("Changing console size now is discouraged");
		}

		key_pressed = io_getChar();
		if ((key_pressed == IO_SPECIAL_CHAR && io_getChar() == '[') || key_pressed == '[') /* pressing an arrow inputs both SPECIAL, [, and a letter ; pressing pge up/down inputs [, a number, and ~ */
		{
			/* deselecting text */
			key_pressed = io_getChar();
			io_setCursorPos(x_text[default_choice], y_text[default_choice]);
			printf("%s", text[default_choice]);

			switch (key_pressed)
			{
				case 'A':	/* Arrow up */
					if (default_choice == 0)
						default_choice = (unsigned char)(nb_choices - 1);
					else --default_choice;
					break;

				case 'B':	/* Arrow down */
					if (default_choice == nb_choices - 1)
						default_choice = 0;
					else ++default_choice;
					break;

				case '5':
					/* Page up */
					if (io_getChar() == '~') {
						default_choice = 0;
					}
					break;

				case '6':
					/* Page Down */
					if (io_getChar() == '~') {
						default_choice = (unsigned char)(nb_choices - 1);
					}
					break;

				default:
					break;
			}

			/* selecting text */
			io_setCursorPos(x_text[default_choice], y_text[default_choice]);
			io_setTextAttributes("+invert");
			printf("%s", text[default_choice]);
			io_setTextAttributes("-invert");
			io_setCursorPos(x_text[default_choice], y_text[default_choice]);
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
	return default_choice;
}
