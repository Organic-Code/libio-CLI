#ifndef IO_SPRITE_H_INCLUDED
#define IO_SPRITE_H_INCLUDED

#include <stdbool.h>
#include <io/coordinates_struct.h>

/**
 * @file io/sprite_struct.h
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
    bool draw_part;
	unsigned short x_size; /*!< Length of the sprite */
	unsigned short y_size; /*!< Height of the sprite */
	char** char_table; /*!< Sprite itself */
	char* txt_color; /*!< Color for the sprite's text. NULL for no particular color */
	char* bg_color; /*!< Color for the sprite's background. NULL for no particular color */
	bool draw_spaces; /*!< true if displays functions should print the spaces, false otherwise. */

	bool is_spriteSheet; /*!< true if created the sprite with io_newSpriteSheet. */
	unsigned short sprite_width; /*!< Width of a sprite in a sprite sheet. */
	unsigned short sprite_height; /*!< Height of a sprite in a sprite sheet. */
	unsigned char x_sprite_nbr; /*!< Number of sprites in a line. */
	unsigned char y_sprite_nbr; /*!< Number of sprites in a column. */
	unsigned char  x_current_sprite;   /*!< Line of the currently selected sprite. */
	unsigned char  y_current_sprite;   /*!< Column of the currently selected sprite. */
}io_Sprite;

#endif /* IO_SPRITE_H_INCLUDED */
