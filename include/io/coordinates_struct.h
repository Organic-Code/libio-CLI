#ifndef IO_COORDINATES_STRUCT_H_INCLUDED
#define IO_COORDINATES_STRUCT_H_INCLUDED

/**
 * @struct io_Coordinates
 * @brief A structure defining a character's coordinates
 */
typedef struct{
	unsigned short x; /*!< Column of the character */
	unsigned short y; /*!< Row of the character */
}io_Coordinates;

io_Coordinates io_setCoordinates(unsigned short x, unsigned short y);
io_Coordinates io_setCoordinates(unsigned short x, unsigned short y){ io_Coordinates a; a.x = x; a.y = y; return a; }

#endif /* IO_COORDINATES_STRUCT_H_INCLUDED */
