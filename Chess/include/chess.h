#include "standard.h"
#include "standard_color.h"

#define BOARD_LEN (8)

typedef enum piece_type {EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING}piece_type;
typedef enum game_colors {NORMAL = 0, TILE1_COLOR = BG_BLACK, TILE2_COLOR = BG_RED, PLAYER1_COLOR = B_WHITE, PLAYER2_COLOR = B_BLACK, CLEAR = B_CYAN}game_colors; 

typedef struct piece{
    piece_type type;
    game_colors color;
}piece;

struct piece * board;

void menu();
int parse_input(char * input, int * origin_point, int * dest_point);
int print();
void flush_board();
void initialize_board();
int move_piece(int origin_point, int dest_point, int player);

