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
//includes the header file for board_print
#include "board_print.h"



void print_board(Board game_board){ //function designed to print the board
    int i,j; //initializes i and j variable
    
    for(i = 0; i < game_board.rows; ++i){ //for loop to iterate through the rows
        printf("%d ", game_board.rows-1-i); //prints the numbers of the corresponding rows
        for(j = 0; j < game_board.cols; ++j){ //for loop to iterate through the columns
            if ((game_board.tiles[game_board.rows-1-i][j]).curr_visibility == CONCEALED){ //if the visibility of the given tile is concealed, prints the character associated for concealed
                printf("# "); //prints the associated character for concealed
            } //closes the if statement
            else if((game_board.tiles[game_board.rows-1-i][j]).curr_visibility == MARKED){ //if the visibility of the given tile is marked, prints the character associated for marked
                printf("! "); //prints the associated character for marked
            } //closes the else if statement
            else if((game_board.tiles[game_board.rows-1-i][j]).curr_visibility == QUESTIONED){ //if the visibility of the given tile is questioned, prints the character associated for questioned
                printf("? "); //prints the associated character for questioned
            } //closes the else if statement
            else if((game_board.tiles[game_board.rows-1-i][j]).curr_visibility == REVEALED){ //checks if the visibility of the given tiles is revealed
                if((game_board.tiles[game_board.rows-1-i][j]).is_mine == true){ //if the given tile is a mine
                    printf("* "); //prints the associated character for a mine
                } //closes the if statement
                else{ //if it's not a mine
                printf("%d ", (game_board.tiles[game_board.rows-1-i][j]).num_surrounding_mines); //prints the number of surrounding mines in the given tiles
                }} //closes the else and else if statement
    } //closes the inner for loop
        printf("\n");} //prints a new line for each row and closes the outer for loop
    printf("  "); //prints the space for the number of corresponding columns
    for(i = 0; i <game_board.cols; ++i){ //for loop to print the numbers of the corresponding columns
        printf("%d ", i); //prints the numbers of the corresponding columns
    } //closes the for loop
        printf("\n"); //prints the new line for the board
    return; //leaves the function
    } //closes the function
