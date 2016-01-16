#ifndef IO_SPRITE_H_INCLUDED
#define IO_SPRITE_H_INCLUDED

#include <io/bool.h>
#include <io/coordinates_struct.h>

/**
 * @file io/console_management.h
 * @brief Defines the structure io_Sprite
 * @author Lucas LAZARE
 */

/**
 * @struct io_Sprite
 * @brief A structure containing a char* that can be passed to drawing functions
 */
typedef struct{
	io_Coordinates current_position; /*!< Coordinates to the current position of the sprite (0,0 if not drawed) */
	io_Coordinates drawing_start_coo; /*!< Coordinates of the beginning of the sub-sprite (default : 0,0)*/
	io_Coordinates drawing_end_coo; /*!< Coordinates of the end of the sub-sprite (default: x_size,y_size) */
	unsigned short x_size; /*!< Length of the sprite */
	unsigned short y_size; /*!< Height of the sprite */
	char* char_table; /*!< Sprite itself */
	char* txt_color; /*!< Color for the sprite's text. NULL for no particular color */
	char* bg_color; /*!< Color for the sprite's background. NULL for no particular color */
	IO_BOOL draw_spaces; /*!< true if displays functions should print the spaces, false otherwise. */
}io_Sprite;

#endif /* IO_SPRITE_H_INCLUDED */
