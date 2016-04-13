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

#include <sample/game.h>

// because screw it it's just an example
static unsigned short console_height, console_width;
static bool long_jumped = false, super_jumped = false;

void startGame(){

    io_setTextAttributes("reset");
    io_clear();
    console_height = io_consoleHeight();
    console_width = io_consoleWidth();

    if ( console_width < 5 || console_height < 5){
        printf("Are you kidding ?");
        io_getChar();
    }
    else {
        // initializing variabes
        srand((unsigned int) time(0));
        io_Sprite* hero;
        char ground[console_width],* accel;
        unsigned int i = 0;
        load(&hero, ground, &accel);

        // displaying
        printGround(ground);
        io_printSprite(hero);
        io_setTextColor("white");
        io_print(IO_TYPEWRITE | IO_CENTER, console_height / 2 - 1, ' ', "Try to survive the longest time possible");
        usleep(500000);
        io_print(IO_TYPEWRITE | IO_CENTER, console_height / 2, ' ', "Press space to jump.");
        usleep(700000);
        io_print(IO_CENTER, console_height / 2 + 4, 0, "(nb : you are the red cross at the bottom left)");
        io_print(IO_CENTER | IO_BLINK, console_height / 2 + 3, 0, "PRESS ANY KEY"); // Make "PRESS ANY KEY" blinking and stay there until a key is pressed.
        io_print(IO_CENTER, console_height / 2 + 4, 0, "                                               ", console_height / 2 + 3); // Clears the note

        do{
            io_clearSprite(hero);
            updatePositions(hero, accel, ground);
            printGround(ground);
            io_printSprite(hero);
            ++i;
        }while(isAlive(hero,ground[1]) && jump(hero, accel));

        io_clear();
        io_setTextColor("white");
        io_print(IO_CENTER, console_height / 2, 0, "You Lost !");
        io_print(IO_CENTER, console_height / 2 + 1, 0, "Your score : %d", i);
        while(io_getCharTimed(0) == ' ');
        sleep(1);
        io_getChar();
        unload(hero, accel);
    }
}

void load(io_Sprite** hero, char ground[], char** accel){

    // Setting variables
    *accel = (char*) malloc(sizeof(char));
    **accel = 0;
    io_setEcho(false);
    io_visibleCursor(false);
    char* runner[] = {"*+"};
    *hero = io_newSpriteSheet(1, 1, runner, "red", NULL, 2, 1);
    *hero = io_setPosition(*hero, io_coordinates(2, (unsigned short) (console_height - (*hero)->y_size - 1)));
    *hero = io_printSpaces(*hero, true);
    int min = console_width < 10 ? console_width : 10, i;
    for (i = 0 ; i < min ; ++i){
        ground[i] = 0;
    }
    for (i = min ; i < console_width ; ++i){
        ground[i] = nextObstacle((ground + i - 4));
    }
}

void unload(io_Sprite* hero, char* accel){
    io_setEcho(true);
    io_visibleCursor(true);
    io_deleteSpriteSheet(hero);
    free(accel);
}

char nextObstacle(char previous_ground[3]){
    if (previous_ground[0]){
        if (previous_ground[1]){
            if (previous_ground[2]){
                return 0;
            }
            else{
                return (char) ((rand() % 10 == 0) * (rand() % 2 + 1));
            }
        }
        else{
            if (previous_ground[2]){
                return (char) ((rand() % 3 == 0) * (rand() % 2 + 1));
            }
            else{
                return (char) ((rand() % 3 != 0) * (rand() % 2 + 1));
            }
        }
    }
    else{
        if (previous_ground[1]){
            if (previous_ground[2]){
                return (char) ((rand() % 10 < 2) * (rand() % 2 + 1));
            }
            else{
                return (char) ((rand() % 3 != 0) * (rand() % 2 + 1));
            }
        }
        else{
            if (previous_ground[2]){
                return (char) ((rand() % 4 == 0) * (rand() % 2 + 1));
            }
            else{
                return (char) ((rand() % 3 != 0) * (rand() % 2 + 1));
            }
        }
    }
}

void updatePositions(io_Sprite* hero, char* accel, char ground[]){
    io_setCursorPos(0,0);
    if (hero->current_position.y < console_height - hero->y_size - 1){
        hero->current_position.y += *accel;
        ++(*accel);
    }
    else if (*accel < 0){
        hero->current_position.y += *accel;
        ++(*accel);
    }
    else{
        *accel = 0;
        io_spriteSheet_setSprite(hero, 1, 0);
    }

    if (*accel > 1){
        *accel = 1;
    }

    if (hero->current_position.y > console_height - hero->y_size - 1){
        hero->current_position.y = console_height - hero->y_size - 1;
    }
    unsigned short i = 0, width = (unsigned short) (console_width - 2);
    for(; i < width ; ++i){
        ground[i] = ground[i+1];
    }
    ground[width] = nextObstacle(ground + width - 4);
}

bool jump(io_Sprite* hero, char* accel) {
    struct timeb t1, t2;
    ftime(&t1);
    char key = io_getCharTimed(4);

    if (key == ' '){
        io_spriteSheet_setSprite(hero, 0, 0);
        if (hero->current_position.y == console_height - 2) {
            long_jumped = false;
            super_jumped = false;
            *accel = -2;
        }
        else if (!long_jumped){
            long_jumped = true;
            *accel = -1;
        }
        else if (!super_jumped){
            super_jumped = true;
            *accel = 0;
        }
    }
    else if (key == 'q' || key == 'Q'){
        return false;
    }

    while(io_getCharTimed(0) != -1);
    ftime(&t2);
    unsigned int time_enlapsed = (unsigned int)fabs(t2.millitm - t1.millitm);
    if (time_enlapsed < 300) {
        usleep((400 - time_enlapsed) * 1000);
    }
    while(io_getCharTimed(0) != -1);
    return true;
}

void printGround(char ground[]){
    io_setTextColor("green");
    io_setCursorPos(1, (unsigned short) (console_height - 2));
    unsigned short i = 0;
    for (; i < console_width - 1 ; ++i){
        switch (ground[i]){
            case 1:
            case 2:
                printf("×");
            default:
                printf(" ");
        }
    }
    io_setCursorPos(1, (unsigned short) (console_height - 1));
    for (i = 0; i < console_width - 1; ++i){
        switch (ground[i]){
            case 1:
            case 2:
                printf("#");
                break;
            default:
                printf("#");
                break;
        }
    }
}

bool isAlive(io_Sprite* hero, char ground){
    return !(hero->current_position.y == console_height - hero->y_size - 1 && ground);
}
