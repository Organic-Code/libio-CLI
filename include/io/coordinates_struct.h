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

#endif /* IO_COORDINATES_STRUCT_H_INCLUDED */
