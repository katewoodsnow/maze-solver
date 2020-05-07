/**\file maze.c
 * Submission for project 1

 * This program is the solution to project 1: It will implement the maze solver

 *\author Kate Wood <kate.wood@hotmail.co.uk>
 *\version 1
 *\date 06 January 2017
 */

#include <stdbool.h>
#include "map.h"

    /* Call the function to find the specified square "s" */
int find_start(Map *mapdata, int *start_x, int *start_y)
{
   int x;
   int y;

   /* Check the content of the map
    * Call the function to obtain the value of the square
    * If the value is "S" set the memory pointed to by the
    * x and y coordinate of that square
    */
    for (y = 0; y < mapdata->height; y++){
        for (x = 0; x < mapdata->width; x++){
            if (get_square(mapdata, x, y) == 'S'){
                *start_x = x;
                *start_y = y;
                return true;
            }
        }
    }
    return false;
}

    /* Call the function to solve the map recursively */
int solve_maze(Map *mapdata, int x, int y)
{
   /* Check if x and y are out of bounds */
   if (x < 0 || x >= mapdata->width || y < 0 || y >= mapdata->height)
   {
       printf("start is out of bounds\r\n");
       return false;
   }

    /* Check if end has been located */
    if (get_square(mapdata, x, y) == 'E')
    {
        printf("end has been located\r\n");
        return true;
    }

    /* Check if square has been filled */
    if (get_square(mapdata, x, y) != ' ' && get_square(mapdata, x, y) != 'S')
    {
        printf("filled square located\r\n");
        return false;
    }

    /* If not mark the square and print progress */
    printf("marking square\r\n");
    mark_square(mapdata, x, y);

    print_map(mapdata, false);

    /* Check surrounding squares if true or false */
    if (solve_maze(mapdata, x, y - 1))
        return true;

    if (solve_maze(mapdata, x+1, y))
        return true;

    if (solve_maze(mapdata, x, y + 1))
        return true;

    if (solve_maze(mapdata, x - 1, y))
        return true;
    /* call the function to remove the mark from a square if false */
    unmark_square(mapdata, x, y);
        return false;
}
