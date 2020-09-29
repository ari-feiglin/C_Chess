#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_LEN (8)
#define BUFFER_SIZE (1024)

enum piece_type {EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
enum color {NORMAL = 0, BG_BLACK = 40, BG_RED = 41, BLACK = 90, WHITE = 97, CLEAR = 31}; 
struct piece{
    enum piece_type type;
    enum color color;
};

struct piece * board;

int get_raw_input(char * prompt, char ** input);
int lower(char * string, int len);
int parse_input(char * input, int * origin_point, int * dest_point);
int print();
void flush_board();
void initialize_board();
int move_piece(int origin_point, int dest_point, int player);

