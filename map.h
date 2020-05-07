** \file map.h
 *  This file contains the datatypes needed to implement the maze map, and the
 *  prototypes for functions visible to the rest of the code inside map.c
 *
 *  \author Chris Page <chris@starforge.co.uk>
 *  \date 28 May 2008
 *  \version 1
 */

#ifndef _MAP_H    // This is used to ensure that the header is only ever included once
#define _MAP_H 1

/** A structure to store the information about a maze map. This structure
 *  contains the map data, and width and heigh information.
 */
typedef struct {
    char *squares; //!< A pointer to a block of memory to hold the map.
    int   width;   //!< The width of the map pointed to by squares.
    int   height;  //!< The height of the map pointed to by suares.
} Map;

    // Functions the student must fill in

/** Creates a map and allocates enough memory to store it
 *  \param width The width of the map
 *         height The height of the map
 *  \return A pointer to the Map structure.
 */
Map *create_map(int width, int height);

/** Release the memory used by a Map structure
 *  \param release A pointer to the Map to free
 */
void free_map(Map *release);

/** Allocate a Map and load the contents of a file into the map squares
 *  \param filename The name of the file to load the map data from.
 *  \return A pointer to a Map structure containing the map loaded from the file.
 */
Map *load_map(char *filename);

// Functions provided for the student to use

/** Obtain the value in the map at the specified location
 *  \param mapdata A pointer to the map to get the value from
 *          x The x coordinate of the map square to return
 *          y The y coordinate of the map square to return
 *  \return The value at the specified x and y coordinate on the map.
 */
char get_square(Map *mapdata, int x, int y);

/** Set the contents of a square in the map at the specified location to a given value
 *  \param mapdata A pointer to the Map to set the value in
 *  x The x coordinate of the map square to set
 *  y The y coordinate of the map square to set
 *  value The value to set the map square to.
 */
void set_square(Map *mapdata, int x, int y, char value);

/** Place a mark on the specified square to indicate it has been checked
 *  \param mapdata A pointer to the map containing the square to update
 *  x The x coordinate of the square to mark
 *  y The y coordinate of the square to mark
 */
void mark_square(Map *mapdata, int x, int y);

/** Remove the mark from a square, leaving a 'checked' mark to ensure that paths
 *  that have been followed can be avoided
 *  \param mapdata A pointer to the map containing the square to update
 *  x The x coordinate of the square to mark
 *  y The y coordinate of the square to mark
 */
void unmark_square(Map *mapdata, int x, int y);

/** Print the contents of the specified map to stdout
 *  If the map has already been printed, this will erase the previous display and print the new map in its place
 *  \param mapdata 	A pointer to the Map structure containing the map to print
           First_print Set this to true if this is the first print of the map, in which case nothing is erased before
           the print. If this is false then enough of the shell is cleared to contain the map before it is printed again.
 */
void print_map(Map *mapdata, int first_print);

#endif