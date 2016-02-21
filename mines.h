
enum Visibility {REVEALED, CONCEALED, MARKED, QUESTIONED}; //header to use the enum visibility and its associated elements

typedef struct TILE_STRUCT{ //header to use struct and access parts of the tile
    bool is_mine; //initializes variable is_mine
    enum Visibility curr_visibility; //initializes variable curr_visibility
    int num_surrounding_mines; //initializes variable num_surrounding_mines
    
}Tile; //have to use tile.(ToBeFilled) to access this struct


typedef struct BOARD_STRUCT{ //header to use struct and access parts of the board
    int rows; //initializes variable rows
    int cols; //initializes variable cols
    int num_mines; //initializes variable num_mines
    Tile** tiles; //initializes 2d array tiles
}Board; //have to use board.(ToBeFilled) to access this struct


void reveal(int row, int col, Board* board); //header to call function for revealing the tiles in a board
void read_args(int argc); //header to call function for checking the arguments
void print_inside(Board game_board); //header to call function for printing the inside of a board
void rand_mines(Board* game_board, int num_mines, int argc, int num_seed); //header to call function for randomizing the mines
void concealed_tile(Board* board, int cur_row, int cur_col, bool* game_on, int* num_mines, bool* cancel); //header to call function for checking a concealed tile
void marked_mine(Board* board, int cur_row, int cur_col, bool* cancel); //header to call function for checking a marked mine
void marked_question(Board* board, int cur_row, int cur_col, bool* cancel); //header to call function for checking a questioned mine
void check_mine(Board board); //header to call function for checking a tile for a mine
void action_played(Board* board, int cur_row, int cur_col, bool* game_on, int* num_mines, bool* cancel); //header to call function for asking an action from the user
void game_win(Board* board, bool* game_on); //header to call function for if the player wins and reveals the entire board
void calling_args(int argc, char* arg1, char* arg2, char* arg3, char* arg4); //header to call function for calling the arguments after checking them
