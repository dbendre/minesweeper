//include stdio.h allows the use of print and other functions
#include <stdio.h>
//include stdlib.h allows the use of functions associated in that library
#include <stdlib.h>
//include ctypes.h allows the use of character modification functions
#include <ctype.h>
//include stdbool/h allows the use of true or false and creates type bool
#include <stdbool.h>
//include time.h allows the use of rand
#include <time.h>

#include "mines.h" //includes the header for mines and associated functions with mines
#include "board.h" //includes the header for the board, creating it
#include "play.h" //includes the header for plays/moves and continues while simultaneously printing the board
#include "board_print.h" //includes the header for printing the board and works at the same time as play.h




void reveal(int row, int col, Board* board){ //reveal function designed to reveal a designated spot in the board
    int m,n; //initializes m and n for use in for loops
    
    if (row < 0 || col < 0 || row >= (*board).rows || col >= (*board).cols){ //if statemenr for when it is out of bounds/not on the board
        return; //leaves function and returns to ask for another point/tile
    } //closes the if statement
    
    else{ //else statement for when it is in bounds/in the board
    
        if (((*board).tiles[row][col]).num_surrounding_mines > 0 && (((*board).tiles[row][col]).curr_visibility == CONCEALED)){ //if statement to check if it is concealed and that there is/are mines around the tile
        ((*board).tiles[row][col]).curr_visibility = REVEALED; //changes the tile to revealed
        return; //leaves the function and returns to ask for another tile
    
        } //closes the if statement
    
        else if(((*board).tiles[row][col]).is_mine == true){ //checks if the given tile is a mine
        return; //leaves the function and then prints game over in another function
    
        } //closes the else if statement
    
        else if(((*board).tiles[row][col]).curr_visibility == REVEALED){ //checks if the tile is already revealed
        return; //leaves the function and then prints that the tile has already been revealed
        } //closes the else if statement
        else if(((*board).tiles[row][col]).curr_visibility == QUESTIONED){ //checks if the tile has been questioned
            return; //leaves the function and gives the user a choice to either unquestion it or cancel
        } //closes the else if statement
        else if(((*board).tiles[row][col]).curr_visibility == MARKED){ //checks if the tile has been marked
            return; //leaves the function and gives the user a choice to either unmark it or cancel
        } //closes the else if statement
        else{ //else statement for when the above conditions are not used for example, when you lose or win
            ((*board).tiles[row][col]).curr_visibility = REVEALED; //reveals the current tile
            for(m = -1; m <= 1; m++){ //for loop to iterate through the rows of the eight tiles around the given tile
                for(n = -1; n <= 1; n++){ //for loop to iterate through the columns of the eight tiles around the given tile
                    reveal(row+m, col + n, board); //calls the function again for recursion
                } //closes the for loop for columns
            } //closes the for loop for rows
        } //closes the inner else statment
    } //closes the outer else statement
    return; //leaves the function
} //closes the function
void read_args(int argc){ //function designed to check the arguments
    if(argc < 4){ //if num of args is less than 4
        printf("Not enough arguments.\n"); //print statement to say there are not enough arguments
        printf("Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])"); //print statement to say what is needed for the function to work (parameters)
        exit(0); //terminates program
    } //closes the if statement
    else if(argc > 5){ //if there are more than 4 args
        printf("Too many arguments.\n"); //prints that there are too many arguments
        printf("Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])"); //print statement to say what is needed for the function to work (parameters)
        exit(0); //terminates program
    } //closes the else if statement
} //closes the function







void print_inside(Board game_board){ //function designed to print the game board
    int i,j; //initializes i and j variables
    
    for(i = 0; i < game_board.rows; ++i){ //for loop to iterate through the rows of the game board
        printf("%d ", game_board.rows-1-i); //prints the numbers on the side indicating the corresponding row
        for(j = 0; j < game_board.cols; ++j){ //for loop to iterate through the columns of the game board

            if ((game_board.tiles[i][j]).is_mine == true){ //checks if the tile is a mine
                printf("* "); //prints the symbol for a mine
            } //closes the if statement
            else{ //if it is not a mine
                printf("%d ", (game_board.tiles[i][j]).num_surrounding_mines); //prints the number of mines around that specific tile
            }} //closes the else statement and the inner for loop
        printf("\n");} //prints a new line for each new row and closes the outer for loop
    printf("  "); //print the space for the number of columns
    for(i = 0; i <game_board.cols; ++i){ //for loop to print the corresponding column
        printf("%d ", i); //prints the number for the corresponding column
    } //closes the for loop
    printf("\n"); //prints the new line after printing the board
    return; //leaves function
} //closes the function



void rand_mines(Board* game_board, int num_mines, int argc, int num_seed) { //function designed to randomize the mines
    int row; //initializes row
    int col; //initializes col
    int num_mine = num_mines; //initializes num_mine to the number of mines
    int i = 0; //initializes i to 0 to iterate
    //seed a number
 
    
    if(argc == 5){ //if the number of arguments is 5, use num seed
        srand(num_seed); //randomizes the mines using num_seed
    } //closes the if statement
    else if(argc == 4){ //if the number of arguments is 4, use time
        srand(time(0)); //randomizes the mines using time()
    } //closes the else if statement
    while(i < num_mine) { //while loop to plant x number of mines
        row= (rand() % ((*game_board).rows)); //row is assigned to a random row on the board
        col = rand() % ((*game_board).cols); //col is assigned to a random column on the board
        if((*game_board).tiles[row][col].is_mine != true){ //checks if the given tile is not a mine
            (*game_board).tiles[row][col].is_mine = true; //changes the tile to a mine
            i++; //iteartes the entire while loop
            printf("Placing mine at %d, %d\n", row, col); //prints the location of all the mines on the board
        } //closes the if statement
    } //closes the while loop
    return; //leaves the function
} //closes the function

void concealed_tile(Board* board, int cur_row, int cur_col, bool* game_on, int* num_mines, bool* cancel){ //function designed to check a concealed tile
    int action; //initializes action
    int i,j; //intializes i and j

    printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\nAction: "); //prompt asking user for an action of a number between 0 to 3
    scanf("%d", &action); //reads the input from the user and assigns the number to action
    
    if(action == 0){ //if the inputted action is equal to 0
        if((*board).tiles[cur_row][cur_col].is_mine == true){ //checks if the given tile is a mine
            ((*board).tiles[cur_row][cur_col]).curr_visibility = REVEALED; //reveals the current tile
            for(i = 0; i < (*board).rows;++i){ //for loop to iterate through the rows of the board
		for(j = 0; j < (*board).cols; ++j){ //for loop to iterate through the columns of the board
			((*board).tiles[i][j]).curr_visibility = REVEALED; //reveals all of the board
}} //closes the inner and outer for loops
print_board(*board); //prints the entire board
            printf("You Lost :( "); //prints that the player has lost
            *game_on = false; //changes game_on to false
            *cancel = false; //changes cancel to false
        } //closes the inner if statement
        else{ //if the above condition is not true
            reveal(cur_row, cur_col, board); //calls the function to reveal the current tile
            *cancel = false; //changes cancel to false
        } //closes the else statement
    } //closes the outer if statement
    else if(action == 1){ //if the inputted action is 1
        ((*board).tiles[cur_row][cur_col]).curr_visibility = QUESTIONED; //changes the visibility of the current tile to questioned
         *cancel = false; //changes cancel to false
    } //closes the else if statement
    else if(action == 2){ //if the inputted action is 2
        ((*board).tiles[cur_row][cur_col]).curr_visibility = MARKED; //changes the visibility of the current tile to marked
        (*num_mines)--; //reduces the number of mines by 1
         *cancel = false; //changes cancel to false
    } //closes the else if statement
    else if(action == 3){ //if the inputted action is 3
        return; //leaves the function
    } //closes the else if statement
    return; //leaves the function
} //closes the function

void marked_mine(Board* board, int cur_row, int cur_col, bool* cancel){ //function designed to ask an action from the user if the current tile has been marked
    int action; //intializes action
    
    printf("Enter Action\n0. UnMark\n1. Cancel\nAction: "); //prompt asking for an action to either unmark is or cancel
    scanf("%d", &action); //reads the input from the user and assigns the number to action
    
    if(action == 0){ //if the inputted action is 0
        ((*board).tiles[cur_row][cur_col]).curr_visibility = CONCEALED; //changes the current tile to concealed
(*board).num_mines++;//increases the number of mines by 1
*cancel = false; //changes cancel to false
        return; //leaves the function
    } //closes the if statement
    else if(action ==1){ //if the inputted action is 1
        return; //leaves the function
    } //closes the else if statement
    return; //leaves the function
} //closes the function

void marked_question(Board* board, int cur_row, int cur_col, bool* cancel){ //functions designed to ask for an action if the given tile's visibility is questioned
    int action; //initializes action
    
    printf("Enter Action\n0. UnQuestion\n1. Cancel\nAction: "); //prompt to ask the user for an action
    scanf("%d", &action); //reads the input from the user and assigns the number to action
    
    if(action ==0){ //if the inputted action is 0
        ((*board).tiles[cur_row][cur_col]).curr_visibility = CONCEALED; //changes the visibility back to concealed
        *cancel = false; //changes cancel to false
        return; //leaves the function
    } //closes the if statement
    else if(action == 1){ //if the inputted action is 1
        return; //leaves the function
    } //closes the else if statement
    return; //leaves the function
} //closes the function


void check_mine(Board board){ //function designed to check if a given tile is a mine
    int row, col; //initializes row and col
    printf("Write location to check mine: "); //prompt asking to write a location to check a mine
    scanf("%d, %d", &row, &col); //reads the input from the user and assigns the value to row and col
    
    if((board.tiles[row][col]).is_mine){ //if the current tile is a mine
        printf("It's a mine."); //prints that it is a mine
    } //closes the if statement
    else{ //if it is not  mine
        printf("It's not a mine."); //prints that it is not a mine
    } //closes the else statement
    return; //leaves the function
} //closes the function

void action_played(Board* board, int cur_row, int cur_col, bool* game_on, int* num_mines, bool* cancel){ //function designed to execute the action being played
    if(((*board).tiles[cur_row][cur_col]).curr_visibility == CONCEALED){ //if the visibility of the tile is concealed
        concealed_tile(board, cur_row, cur_col, game_on, num_mines, cancel); //calls the function to check a concealed tile
    } //closes the if statement
    else if(((*board).tiles[cur_row][cur_col]).curr_visibility == MARKED){ //if the visibility of the tile is marked
        marked_mine(board, cur_row, cur_col, cancel); //calls the function to check a marked mine tile
    } //closes the else if statement
    else if(((*board).tiles[cur_row][cur_col]).curr_visibility == QUESTIONED){ //if the visibility of the tile is questioned
        marked_question(board, cur_row, cur_col, cancel); //calls the function to check a questioned tile
    } //closes the else if statement
    else{ //if the conditions above are not used
        return; //leaves the function
    }//closes the else statement
} //closes the function

void game_win(Board* board, bool* game_on){ //function to check is the player has won
    int i,j; //initializes i and j
    
    for(i = 0; i < (*board).rows; i++){ //for loop to iterate through the rows of the board
        for(j =0; j< (*board).cols; j++){ //for loop to iterate through the columns of the board
            if(((*board).tiles[i][j]).is_mine == true){ //if the given tile is a mine
                if(((*board).tiles[i][j]).curr_visibility !=MARKED){ //if the tile is not marked
                    return; //leaves the function
                } //closes the inner if statement
            } //closes the outer if statement
            else{ //if the given tile is not a mine
                if(((*board).tiles[i][j]).curr_visibility != REVEALED){ //if the given tile is not revealed
                    return; //leaves the function
                } //closes the if statement
            } //closes the else statement
        } //closes the inner for loop
    } //closes the outer for loop

for(i=0; i < (*board).rows; ++i) { //for loop to iterate through the rows of the board
	for (j=0; j < ((*board).cols); ++j) { //for loop to iterate through the columns of the board
	((*board).tiles[i][j]).curr_visibility = REVEALED; //changes all of the visibility of the tiles to revealed
} //closes the inner for loop
} //closes the outer for loop


print_board(*board); //prints the entire board
    printf("You Won!!"); // prints that the player has won
    *game_on = false; //changes game_on to false
    return; //leaves the function
} //closes the function

void calling_args(int argc, char* arg1, char* arg2, char* arg3, char* arg4) { //function designed to call the arguments after checking them
    Board game_board; //calls the game_board
    int row; //intializes row
    int column; //intializes column
    int num_mines; //intializes num_mines 
    bool game_on = true; //intializes game_on to true
    int cur_row; //intializes cur_row
    int cur_col; //intializes cur_col
    bool cancel = true; //intializes cancel to true
    int num_seed = 0; //intializes num_seed to 0

    
    row = atoi(arg1); //changes the argument to a number and assigns it to row
    column = atoi(arg2); //changes the argument to a number and assigns it to column
    num_mines = atoi(arg3); //changes the argument to a number and assigns it to num_mines
    
    if(argc == 5){ //if there are 5 arguments
        num_seed = atoi(arg4); //changes the argument to a number and assigns it to num_seed
    } //closes the if statement
    
    game_board = create_board(row, column, num_mines); //creates the board and assigns it to game_board
    rand_mines(&game_board, num_mines, argc, num_seed); //calls the function to randomize the mines in the game_board
    check_mines_around(&game_board); //calls the function to check the mines around a given tile in the game_board
    
    while(game_on){ //while the game is not over
    cancel = true; //cancel is true
printf("There are %d mines left\n",game_board.num_mines);     //prints the number of mines that are left
print_board(game_board); //prints the entire board
        while(cancel){ //while cancel is true
            play_valid(game_board, &cur_row, &cur_col); //calls function and checks if a play is valid
            action_played(&game_board, cur_row, cur_col, &game_on, &game_board.num_mines, &cancel); //calls function and executes the given action
        } //closes the inner while loop
    game_win(&game_board, &game_on); //calls function and determines if the player has won
    } //closes the outer while loop
} //closes the function 


int main(int argc, char* argv[]){ //main function to call all of the other functions
    read_args(argc); //calls the function to check the arguments
    
    calling_args(argc, argv[1], argv[2], argv[3], argv[4]); //calls the function to call assign all of the arguments to a variable
    return 0; //terminates the main function
} //closes the main function
