/**\file wood_project1.c
 * Submission for project 1:

 * This program is the solution to project 1: It will solve the maze recursively

 *\author Kate Wood <kate.wood@hotmail.co.uk>
 *\version 1
 *\date 06 January 2017
 */


#include <stdio.h>
#include <stdbool.h>
#include "map.h"
#include "maze.h"

int main(int argc, char **argv)
{
    Map * newmap = NULL;
    /* Load the map */
    newmap = load_map(argv[1]);
    int start_x;
    int start_y;

    if (argc != 2)
	{
		printf(stderr, "Error Map file not found.\n");
		perror("Error");
        getchar();
        exit(1);
	}

    /* First print of map */
	print_map(newmap, true);

    /* If the start square of the map is not found print an error message */
    if (!find_start(newmap, &start_x, &start_y)){
		printf(stderr,"Start not found.\n");
		perror("Error");
        getchar();
        exit(1);
    }

    printf("found start at (%d,%d)\r\n", start_x, start_y);

    /* Program does not exit, S is found, solve the maze and print progress of the the map */
	if(solve_maze(newmap, start_x, start_y)){
    /* Print if successful */
		print_map(newmap, false);
		printf("Success - end has been found\n");
	}
	/* Print if maze not solved */
	else{
        printf(stderr,"Fail - end not found.\n");
        exit(1);
	}
    /* free map memory */
    free_map(newmap);
}
