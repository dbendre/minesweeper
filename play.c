//include stdio.h allows the use of print and other functions
#include <stdio.h>
//include stdlib.h allows the use of functions in that library
#include <stdlib.h>
//include ctype.h allows the use of character modification functions
#include <ctype.h>
//include stdbool.h allows the use of true or false and allows type bool
#include <stdbool.h>
//include time.h allows the use of time and rand
#include <time.h>
//includes the header file for mines
#include "mines.h"
//includes the header file for play
#include "play.h"

void play_valid(Board board, int* cur_row, int* cur_col){ //function designed to check if a play is valid
    int row; //intializes variable for row
    int column; //intializes variable for column
    bool K = true; //creates bool variable and intializes as true
    
    while (K){ //while k is true
        printf("Enter row a row between 0-%d and a column between 0-%d: ", board.rows - 1, board.cols -1); //prompt to ask user for two numbers, one for rows and one for columns
        scanf("%d %d", &row, &column); //scans the input and assigns the values to roww and columns
        if(row > (board.rows -1) || row < 0 || column > (board.cols -1) || column < 0){ //checks if they are not in the board
            K = true; //k is true so the while loop continues
        } //closes the if statement
        else if ((board.tiles[row][column]).curr_visibility == REVEALED){ //if the tile is already revealed
            printf("This tile is already revealed.\n"); //prints that the tiles has already been revealed and because k is still true, the while loop continues
        } //closes the else if statement
        else{ //if the other condtiions to not work
            K = false; //condition becomes false
        } //closes the else statemnt
        
    } //closes the while loop
    *cur_row = row; //cur_row is now equal to the current row
    *cur_col = column; //cur_col is now equal to the current column
    return; //leaves the function
} //closes the function
