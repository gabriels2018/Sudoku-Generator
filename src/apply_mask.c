#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../include/sudoku.h"
#define ROWS 9
#define COLS 9

/**
* Function apply_mask
* -------------------
* Function apply_mask creates unique masks in turn creates a unique Sudoku game.
* Numbers are masked from the rearranged 2D array locations based on diffculty level. 
* Language: C
* Author: Gabriel Seyoum, Group H member
* Date: May 31, 2020
*/

/**
* @param rearranged_sudoku [in], Array containing the rearranged Sudoku game.
* @param cells_to_remain [in], Number of cells that needed to be masked.
* @param masked_sudoku [out], Array containing the masked Sudoku game.
*/
void apply_mask(int rearranged_sudoku [ROWS][COLS], int diff_level, int masked_sudoku [ROWS][COLS])
{           
     int l = 0, m = 0, random_cell;                   /* l and m ... index location of cells to be used for masking, random_cell variable holds random number generated between 1 to 81 */
     int total_num_cells = 81, max_cell_masked = 57;   /* Total number of cells on the Sudoku game, maximum number masked */                                                       
     int random_cell_locations [81];                  /* All the randomly selected cell locations, used for masking */
     int cells_tobe_masked;
     int *ptr = random_cell_locations;
     int track_duplicate[57];
     int *track_duplicate_random_num = &track_duplicate [0];    /* To track no duplicate data is generated by random number generator, used for mapping Sudoku cell locations */                            

    
     /* Selecting the number of cells to be masked based on the difficulty levels */
     switch(diff_level)
     {        
        case 0:  
            cells_tobe_masked = 41;    /* 41 locations will be masked, dificulty level 0 */                              
            break;

        case 1:
            cells_tobe_masked = 47;    /* 47 locations will be masked, dificulty level 1 */
            break;

        case 2:
            cells_tobe_masked = 53;    /* 53 locations will be masked, dificulty level 2*/
            break;

        case 3:
            cells_tobe_masked = 57;    /* 57 locations will be masked, dificulty level 3*/
            break;

        default:
            printf("Wrong difficulty level value\n");    /* Dificulty level is not 0, 1, 2 or 3 */
    }

    /* Initialization */
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            *(*(masked_sudoku + i) + j) = rearranged_sudoku [i][j];
        }
    }

    for(int i = 0; i < total_num_cells; i++)
        random_cell_locations[i] = 0;

    for(int j = 0; j < max_cell_masked; j++) 
        track_duplicate[j] = 0;

    /* Cells are chosen radomly between 1 to 81 based on difficulty level, these values are then 
       used to mask Sudoku game cell locations */
    for(int k = 0; k < cells_tobe_masked; k++)
    {
        random_cell = (rand() % (81 - 1 + 1)) + 1;

        *(track_duplicate_random_num + k) = random_cell;

        if(k == 0)
        {
            random_cell_locations[random_cell - 1] = random_cell;
        }

        /* Checks if duplicate random numbers are generated, if yes re-enforces 
           no duplicate random numbers from being used to map cell locations */
        for(int y = k  ; y >0 ; y--)
        {
            if(*(track_duplicate_random_num + k) == track_duplicate_random_num[y-1])
            {
               --k;
            }
            else
            {
                random_cell_locations[random_cell - 1] = random_cell;
            }
       }
    }
   
    /* Randomly chosen cell locations are mapped to the actual Sudoku game cell locations to mask some 
       of the numbers that are selected randomly and based on the difficulty level */
    for(ptr = &random_cell_locations[0]; ptr <= &random_cell_locations[total_num_cells - 1]; ptr++)
    {
        if (*ptr != 0)
        {
             *(*(masked_sudoku + l) + m) = '\0';
        }

        m++;

        if(m == 9)
        {
            l++;
            m = 0;
        }
    }
}
