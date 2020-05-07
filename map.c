/**\file map.c
 * Submission for project 1

 * This program is the solution to project 1: It will implement the map structure and contents

 *\author Kate Wood <kate.wood@hotmail.co.uk>
 *\version 1
 *\date 06 January 2017
 */

/** \file map.c
 * This file contains functions related to manipulating Map structures and their
 * contents. For the purposes of this project, a 'map' consists of a rectangular grid
 * of 'squares', with the top left square having the coordinate (0,0), the x axis
 * increasing to the right, and the y axis increasing downward. Each square contains
 * a character indicating what its contents are. Maps consist of the following characters:
 *
 * ' ' (space) indicates that a square is empty, and thus passable.
 * '#' (hash) indicates that a square contains a hedge/wall.
 * 'S' indicates the start location. A map may only contain one 'S', which may be anywhere.
 * 'E' indicates the exit location. A map may only contain one 'E', which may be anywhere.
 *
 * Maps are stored in plain text files, arranged in the same way that the Map is stored
 * in memory (x increasing to the right, y increasing downward). Please see some of the
 * provided test maze maps for examples.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

/* Include needed for the print_map() function on windows. You may safely ignore this */
#ifdef _WIN32
    #include <windows.h>
#endif


/* ============================================================================ *
 * Prototypes for functions not visible outside this file                       *
 * ============================================================================ */

static void file_widthheight(FILE *infile, int *width, int *height);
static char *chomp(char *string);


/* ============================================================================ *
 * Functions the student must fill in                                           *
 * ============================================================================ */

/** Allocate and set up a Map structure. This creates a Map which can then
 *  be filled in and manipulated by the rest of the code.
 *
 *  \param width The width of the map to allocate.
 *  \param height The height of the map to allocate.
 *  \return A pointer to an allocated and initialised Map structure.
 */
Map *create_map(int width, int height)
{
    // Allocate a Map structure, allocate enough space to store width*height
    // squares and store the pointer to the space in the Map structure,
    // ensure that the squares are all initialised to a sensible value (0 or a
    // space are good choices), fill in the width and height fields in the Map,
    // and return the pointer to the Map.

    Map *newmap = (Map *)malloc(sizeof(Map));

    /* Check there is enough memory */
    if(!newmap) {
        return NULL;
    }
     newmap -> squares = (char *)malloc(width*height);

    /* Check there is enough memory */
    if (!newmap -> squares){
            return NULL;
    }
    newmap -> width = width;
    newmap -> height = height;

    return newmap;
}


/** Release the memory used by a Map structure. Once a Map has been freed, the
 *  Map or its contents may not be used again.
 *
 *  \param release A pointer to the Map to free.
 */
void free_map(Map *release)
{
    // Free the squares data inside the map, then free the Map itself.
    free(release -> squares);
    free(release);
}

/** Determine the size of the map in the specified file. This will determine
 *  the number of lines in the file (the map height), the maximum line length
 *  (the map width), and set the memory pointed to by the specified width and
 *  height pointers to the width and height of the map in the file. This will
 *  rewind to the start of the file before finishing.
 *
 *  \param infile A pointer to the file whose width and heigh should be determined.
 *  \param width  A pointer to the location in which to store the width of the map.
 *  \param height A pointer to the location in which to store the height of the map.
 */
static void file_widthheight(FILE *infile, int *width, int *height)
{
    /* Height of the map */
    int total_lines = 0;

    int length;

    /* Width of the map */
    int max_length = 0;

    /* Array of characters in each line of the file to check */
    char line[128] = {0};

    // read each line from the file, keeping count of how many lines you have read
    // Work out the length of the line, and if it is longer than any line
    // you have encountered so far, record the length.
    // Once all the file has been read in, set the values in *width and *height and then ensure
    // that you go back to the start of the file.

    while (fgets(line, 128, infile)){
    /* Call the function to remove the newline from fgets function */
        chomp(line);
        length = strlen(line);
            if (length > max_length){
                max_length = length;
            }

        total_lines++;
    }

    *width = max_length;
    *height = total_lines;

    fseek(infile, 0, SEEK_SET);
}
    // NOTE: TO SIMPLIFY THE CODE REQUIRED HERE, YOU MAY ASSUME THAT A LINE
    // WILL NEVER BER MORE THAN 128 CHARACTERS IN LENGTH. LOOK AT fgets(), BUT
    // BE CAREFUL THAT YOU DO NOT COUNT THE NEWLINE!


/** Allocate a Map and load the contents of a file into ir. This will allocate
 *  a new map and then load the contents of the specified file into the map
 *  squares.
 *
 *  \param filename The name of the file to load the map data from.
 *  \return A pointer to a Map structure containing the map loaded from the file.
 */
Map *load_map(char *filename)
{
    /* file pointer */
    FILE * infile;
    int width;
    int height;
    /* Map structure pointer */
    Map * newmap;
    int y;
    int x;

    // Open the file and determine the width and height of the map it contains
    // Once you have the width and height, allocate a Map large enough to contain
    // the data, and load the contents of the file into the Map. Return the filled-
    // in Map.
    infile = fopen(filename, "r");
    if (!infile){
        fprintf(stderr, "file '%s' failed to open\n", filename);
        perror("Error");
        getchar();
        exit(1);
    }

    /* Call the function to determine the size of the map in the file */
    file_widthheight(infile, &width, &height);

    /* Call the function to create a map */
    newmap = create_map(width, height);

    char line[128];

    /* Nested loop to read the file into the map and set the content */
    for ( y = 0; y < height; y++){
		fgets(line, 128, infile);
		chomp(line);
            for (x = 0; x < strlen(line); x++){
     /* Call the function to set the value of the square */
                set_square(newmap, x, y, line[x]);
            }
    }
    return newmap;
}

/* ============================================================================ *
 * Functions provided for use by the student                                    *
 * ============================================================================ */

/** Remove the trailing newline from the specified string, if it has one. If the
 *  string does not end in a newline then this will not modify the string.
 *
 * \param string The string to remove the newline from.
 * \return A pointer to the string.
 */
char *chomp(char *string)
{
    int size = strlen(string);
    int pos;

    // move back down the string from the end, as there may be a CR, CR+LF or LF there...
    for(pos = (size - 1); pos >= 0; --pos) {
        // If the character is a CR or LF, replace it with null
        if(string[pos] == 0xD || string[pos] == 0xA) {
            string[pos] = 0;
        } else {
            return string;
        }
    }

    return string;
}

/** Obtain the value in the map at the specified location. This assumes that the
 *  provided Map structure contains correctly intialised map information - the
 *  width and height are set, and the squares pointer points to a valid chunk
 *  of memory containing map information.
 *
 *  \param mapdata  A pointer to the Map to pull the value from.
 *  \param x        The x coordinate of the map sqaure to return
 *  \param y        The y coordinate of the map sqaure to return
 *  \return         The value at the specified x and y coordinate on the map.
 */
char get_square(Map *mapdata, int x, int y)
{
    // Check that x and y are in range. Note that these lines could be removed
    // to increase the speed of the code, but during development it is a good
    // idea to check that the coordinates passed in are sane.
    if(x < 0) fprintf(stderr, "ERROR[get_square]: x is less than 0.\n");
    if(x >= mapdata -> width) fprintf(stderr, "ERROR[get_square]: x is out of range.\n");
    if(y < 0) fprintf(stderr, "ERROR[get_square]: y is less than 0.\n");
    if(y >= mapdata -> height) fprintf(stderr, "ERROR[get_square]: y is out of range.\n");

    // obtain the value at the requested location in the map data
    return mapdata -> squares[(y * mapdata -> width) + x];
}

/** Set the contents of a square in the map at the specified location to a given
 *  value. This assumes that the Map structure contains correctly initialised
 *  map information.
 *
 *  \param mapdata  A pointer to the Map to set the value in.
 *  \param x        The x coordinate of the map square to set.
 *  \param y        The y coordinate of the map square to set.
 *  \param value    The value to set the map square to.
 */
void set_square(Map *mapdata, int x, int y, char value)
{
    // Check that x and y are in range. Note that these lines could be removed
    // to increase the speed of the code, but during development it is a good
    // idea to check that the coordinates passed in are sane.
    if(x < 0) fprintf(stderr, "ERROR[get_square]: x is less than 0.\n");
    if(x >= mapdata -> width) fprintf(stderr, "ERROR[get_square]: x is out of range.\n");
    if(y < 0) fprintf(stderr, "ERROR[get_square]: y is less than 0.\n");
    if(y >= mapdata -> height) fprintf(stderr, "ERROR[get_square]: y is out of range.\n");

    // set the value at the requested location in the map data
    mapdata -> squares[(y * mapdata -> width) + x] = value;
}


/** Place a mark on the specified square to indicate it has been checked. This
 *  will set the character at the specified location to a character idicating
 *  that it has been passed over.
 *
 *  \param mapdata A pointer to the map containing the square to update.
 *  \param x       The x coordinate of the square to mark.
 *  \param y       The y coordinate of the square to mark.
 */
void mark_square(Map *mapdata, int x, int y)
{
    set_square(mapdata, x, y, '@');
}


/** Remove the mark from a square, leaving a 'checked' mark to ensure that
 *  paths that have been followed can be avoided.
 *
 *  \param mapdata A pointer to the map containing the square to update.
 *  \param x       The x coordinate of the square to mark.
 *  \param y       The y coordinate of the square to mark.
 */
void unmark_square(Map *mapdata, int x, int y)
{
    set_square(mapdata, x, y, '.');
}


/** Print the contents of the specified map to stdout. If the map
 *  has been printed already, this will erase the previous display
 *  and print the new map in its place. Note that first_print should
 *  be set to true each time you want to start drawing the map in
 *  place. Think of first_print as true as starting drawing the map,
 *  and false as updating the map that is there already. For example:
 *
 *  <pre>printf("print something here");
 *  print_map(mymap, 1);
 *  while(something) {
 *      ... do something ...
 *      print_map(mymap, 0); // false here as we're updating the map drawn above
 *  }
 *  printf("something else");
 *  print_map(mymap, 1); // prints out the map below 'somethign else'
 *  ... do something...
 *  printf("done something");
 *  print_map(mymap, 1);
 *  while(something) {
 *      ... do something...
 *      print_map(mymap, 0);
 *  }</pre>
 *
 *  \note This code contains some OS-specific Magic which you are not expected
 *  to understand, or even read closely - feel free to treat this function as a
 *  black box.
 *
 *  \param mapdata     A pointer to the Map structure containing the map to print.
 *  \param first_print Set this to true if this is the first print of the map, in
 *                     which case nothing is erased before the print. If this is
 *                     false then enough of the shell is cleared to contain the map
 *                     before it is printed again.
 */
void print_map(Map *mapdata, int first_print)
{
    int x, y;
    char square;

    // If this is not the first time we have printed the map, erase
    // the contents of the terminal
    if(!first_print) {
#ifndef _WIN32  // If we're not compiling on windows...
        // This incantation clears the terminal, and moves the cursor to the top left
        // It should work on any Remotely Sane terminal that understands ANSI
        printf("\033[2J\033[H");
#else // otherwise, we are on windows...
        // So does this mess, the equivalent for windows (windows command terminals do
        // not support ANSI or VT100 escape code sequences, and operations that would
        // be performed via them on other operating systems must be done directly via
        // the Windows API.)

        // A bunch of variables first...
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD written;

        // How many characters are there in the console?
        GetConsoleScreenBufferInfo(handle, &csbi);
        count = csbi.dwSize.X * csbi.dwSize.Y;

        // Now clear that many characters.
        // WARNING: This code is Full Of Spiders. You are not required or expected to
        // know what this is doing, and in fact your sanity is safter if you do not
        // attempt to.
        FillConsoleOutputCharacter(handle, ' ', count, coord, &written);
        GetConsoleScreenBufferInfo(handle, &csbi );
        FillConsoleOutputAttribute(handle, csbi.wAttributes, count, coord, &written);
        SetConsoleCursorPosition(handle, coord);
#endif
    }

    // Now print out the contents of the map
    for(y = 0; y < mapdata -> height; ++y) {
        for(x = 0; x < mapdata -> width; ++x) {
            // store the value to make the condition in the printf less fiddly
            square = get_square(mapdata, x, y);

            // Print out the chracter if set, otherwise print out a space.
            printf("%c", (square ? square : ' '));
        }
        printf("\n");
    }
}