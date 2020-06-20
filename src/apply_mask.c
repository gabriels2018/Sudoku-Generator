#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifndef __MY_HEADER__
#define __MY_HEADER__
    #include "../include/sudoku.h"
#endif

#define ROWS 9
#define COLS 9


/**
* @file apply_mask.c
*
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
* @param diff_level [in], Difficulty level dectates how many numbers should be shown on Sudoku game.
* @param masked_sudoku [out], Array containing the masked Sudoku game.
*/
void apply_mask(int rearranged_sudoku [ROWS][COLS], int diff_level, int masked_sudoku [ROWS][COLS]){
     int l = 0, m = 0, random_cell;                    /* l and m ... index location of cells to be used for masking, random_cell variable holds random number generated between 1 to 81 */
     int total_num_cells = 81, max_cell_masked = 57;   /* Total number of cells on the Sudoku game, maximum number masked */
     int random_cell_locations [81];                   /* All the randomly selected cell locations, used for masking */
     int cells_tobe_masked;
     int *ptr = random_cell_locations;
     int track_duplicate[57];
     int *track_duplicate_random_num = &track_duplicate [0];    /* To track no duplicate data is generated by random number generator, used for mapping Sudoku cell locations */
     /* srand(time(0)); */                                      /* Initalizing the pseudo-random number generator by passing the argument seed */
     FILE *fp;


     fp = fopen ("../test/log/apply_mask_test_log.txt", "a");
     if (fp == NULL)
     {
        printf("Could not open the file");
        _Exit(EXIT_FAILURE);
     }

     /* PRECONDITION: The rearranged_sudoku array values need to contain numbers from 1 to 9 only */
     /* PRECONDITION: The rearranged_ sudoku array size need to be 9x9 */
     /* PRECONDITION: The rearranged_sudoku array data type need to be an integer */
     for(int i = 0; i < ROWS; i++){
         for(int j = 0; j < COLS; j++){
             /* This section will execute when the rearranged_sudoku array actual parameter
              * values are not from 1 to 9,  size is not 9x9 or data type is not integer.
              */
             if (!((rearranged_sudoku [i][j] >= 1) && (rearranged_sudoku [i][j] <= 9))){
                /* When all the above  cases arise the following message will display and the function will terminate */
                printf("The rearranged_sudoku array value(s), data type, or array size is incorrect\n");
                fprintf(fp, "%s", "Error message: The rearranged_sudoku array value(s), data type, or array size is incorrect\n");
                _Exit(EXIT_FAILURE);
             }
         }
     }

     /* PRECONDITION: diff_level need to be an integer data type and contain a value 0, 1, 2 or 3 only */
     switch(diff_level){
        /* The number of cells to be masked is determined based on the difficulty level */
        case 0:
            cells_tobe_masked = 41;    /* 41 locations will be masked and 40 numbers will be shown on the Sudoku game */
            break;

        case 1:
            cells_tobe_masked = 47;    /* 47 locations will be masked and 34 numbers will be shown on the Sudoku game */
            break;

        case 2:
            cells_tobe_masked = 53;    /* 53 locations will be masked and 28 numbers will be shown on the Sudoku game */
            break;

        case 3:
            cells_tobe_masked = 57;    /* 57 locations will be masked and 24 numbers will be shown on the Sudoku game */
            break;

        default:   /* Any diff_level actual parameter value that does not translate into 0, 1, 2, or 3 will fall under this default case */

            /* When the diff_level is not 0, 1, 2 or 3, the following message will display and the function will terminate */
            printf("The difficulty level entered is not 0, 1, 2, or 3\n");
            fprintf(fp, "%s", "Error message: The difficulty level entered is not 0, 1, 2, or 3\n");
            _Exit(EXIT_FAILURE);
    }

    /* Initialization */
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            *(*(masked_sudoku + i) + j) = rearranged_sudoku [i][j];
        }
    }

    for(int i = 0; i < total_num_cells; i++){
        random_cell_locations[i] = 0;
    }

    for(int j = 0; j < max_cell_masked; j++){
        track_duplicate[j] = 0;
    }

    /* Cell locations are chosen radomly between 1 to 81, based on difficulty level
       and these values are then used to mask Sudoku game cell locations */
    for(int k = 0; k < cells_tobe_masked; k++){
        random_cell = (rand() % 81) + 1;

        *(track_duplicate_random_num + k) = random_cell;

        if(k == 0){
            random_cell_locations[random_cell - 1] = random_cell;
        }

        /* It checks if duplicate random numbers are generated, if yes it re-enforces
           the rule no duplicate random numbers from being used to map cell locations */
        for(int y = k  ; y >0 ; y--){
            if(*(track_duplicate_random_num + k) == track_duplicate_random_num[y-1]){
               --k;
            }
            else{
                random_cell_locations[random_cell - 1] = random_cell;
            }
       }
    }

    /* Randomly chosen cell locations are mapped to the actual Sudoku game cell locations to mask some
       of the numbers that are selected randomly and based on the difficulty level */
    for(ptr = &random_cell_locations[0]; ptr <= &random_cell_locations[total_num_cells - 1]; ptr++){
        if (*ptr != 0){
             *(*(masked_sudoku + l) + m) = 0;
        }

        m++;

        if(m == 9){
            l++;
            m = 0;
        }
    }
}
