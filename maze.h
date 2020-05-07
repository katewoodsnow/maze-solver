/** \file maze.h
 *  This file contains the  prototypes for functions in maze.c that are visible
 *  to the rest of the code.
 *
 *  \author Chris Page <chris@starforge.co.uk>
 *  \date 3 June 2008
 *  \version 1
 */

#ifndef _MAZE_H // This is used to ensure that the header is only included once
#define _MAZE_H 1

#include "map.h"

/** Search the specified Map for a square containing 'S
 * If a square containing 'S' is located, the memory pointed to by start_x and start_y should be updated
 * to contain the x and y coordinates of the square in the map
 */
int find_start(Map *mapdata, int *start_x, int *start_y);

/** This is the recursive map solver itself.
 */
int solve_maze(Map *mapdata, int x, int y);

#endif
