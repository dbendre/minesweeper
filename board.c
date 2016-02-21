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
//includes the header file for board
#include "board.h"




Board create_board(int rows, int cols, int num_mine){ //function designed to creates the board
    Board board; //accesses the board
    int i,j; //initializes i and j
    
    board.rows = rows; //number of rows is equal to rows
    board.cols = cols; //numbesr of columns is equal to cols
    board.num_mines = num_mine; //number of mines is equal to num_mine
    
    board.tiles = (Tile**)malloc(rows * sizeof(Tile*)); //uses malloc to create rows in the array/board equal to the number of rows
    
    for(i = 0; i <rows; i++){ //for loop to create space in the columns using the rows
        board.tiles[i] = (Tile*)malloc(cols*sizeof(Tile)); //uses malloc to create columns in the array/board equal to the number of columns
    } //closes the for loop
    for (i = 0; i < rows; i++){ //for loop to iterate through the rows
        for(j = 0; j < cols; j++){ //for loop to iterate through the columns
            (board.tiles[i][j]).curr_visibility = CONCEALED; //changes the visibility of the tile to conceales
            (board.tiles[i][j]).is_mine = false; //changes the tile to not be a mine
            (board.tiles[i][j]).num_surrounding_mines = 0; //changes the number of surrounding mines in the tile to 0
            
        } //closes the inner for loop
    } //closes the outer for loop
    return board; //leaves the function and returns the current condition of the board
} //closes the function

void mines_around(Board* board, int i, int j){ //function designed to check the number of mines around a given tile
    int m,n; //initializes m and n
    
    for(m = (i-1); m <= (i+1); m++){ //for loop to iterate through the rows in the eight tiles around the given tile
        for(n = (j-1); n <= (j+1); n++){ //for loop to iterate through the columns in the eight tiles around the given tile
            if (m < 0 || n < 0 || m >= (*board).rows || n >= (*board).cols || (m == i && n == j)){ //checks if the tile is in the board
                continue; //skips the current iteration and goes to the next iteration
            } //closes teh if statement
            else{ //if it is in the board
                if(((*board).tiles[m][n]).is_mine == true){ //if there is a mine around the tile
                    ((*board).tiles[i][j]).num_surrounding_mines++; //adds one to the number of surrounding mines
                } //closes the if statement
            } //closes the else statement
        } //closes the inner for loop
    } //closes the outer for loop
        return; //leaves the function
    } //closes the function

void check_mines_around(Board* board){ //function designed to check the number of mines around a given tile
    int i,j; //initializes i and j
    int num_tiles =0; //intializes the number of tile to 0
        
    for (i = 0; i < (*board).rows; i++){ //for loop to iterate through the rows
        for(j = 0; j < (*board).cols; j++){ //for loop to iterate through the columns
            mines_around(board, i, j); //calls the function to check the number of mines around the given tile
            num_tiles++; //adds one to the number of tiles
            
        } //closes the inner for loop
    } //closes the outer for loop
    return; //leaves the function
} //closes the function
