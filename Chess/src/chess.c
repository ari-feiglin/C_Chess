#include "chess.h"

int parse_input(char * input, int * origin_point, int * dest_point){
    int len = 0;
    int i = 0;
    int origin_column = -1;
    int origin_row = -1;
    int dest_column = -1;
    int dest_row = -1;
    bool dest = false;

    len = strnlen(input, BUFFER_SIZE);
    if(-1 == len){
        perror("Strnlen error");
        goto cleanup;
    }
    
    lower(input, len);

    for(i=0; i<len-1; i++){
        if('a' <= input[i] && input[i] <= 'z'){
            if(dest){
                dest_column = input[i] - 'a';
            }
            else{
                origin_column = input[i] - 'a';
            }
        }
        else if('0' <= input[i] && input[i] <= '8'){
            if(dest){
                dest_row = input[i] - '0';
            }
            else{
                origin_row = input[i] - '0';
            }
        }
        else if('>' == input[i]){
            dest = true;
        }
        else if(' ' != input[i]){
            *origin_point = -1;
            *dest_point = -1;
            goto cleanup;
        }
    }

    if(!dest){
        *origin_point = -1;
        *dest_point = -1;
        goto cleanup;
    }

    *origin_point = origin_row * BOARD_LEN + origin_column;
    *dest_point = dest_row * BOARD_LEN + dest_column;

cleanup:
    return len;
}

int print(){
    int i = 0;
    int j = 0;
    char piece = 0;
    enum color bg_color = BG_BLACK;

    printf("\n  A B C D E F G H\n");
    for(i=0; i<BOARD_LEN; i++){
        printf("%i", i);
        for(j = 0; j<BOARD_LEN; j++){
           switch(board[i * BOARD_LEN + j].type){
            case PAWN:
                piece = 'P';
                break;
            case ROOK:
                piece = 'R';
                break;
            case KNIGHT:
                piece = 'H';
                break;
            case BISHOP:
                piece = 'B';
                break;
            case QUEEN:
                piece = 'Q';
                break;
            case KING:
                piece = 'K';
                break;
            default:
                piece = ' ';
                break;
           }
           printf(" \e[1m\033[%dm\033[%dm%c", bg_color, board[i*BOARD_LEN + j].color, piece);
           if(BG_RED == bg_color){
               bg_color = BG_BLACK;
           }
           else{
               bg_color = BG_RED;
           }
       }
       printf(" \033[%dm\n", NORMAL);
       if(BG_RED == bg_color){
            bg_color = BG_BLACK;
        }
        else{
            bg_color = BG_RED;
        }
    }

    printf("\n");
    return 0;
}

void flush_board(){
    int i = 0;
    struct piece blank_piece;
    blank_piece.type = EMPTY;
    blank_piece.color = CLEAR;

    for(i=0; i<BOARD_LEN*BOARD_LEN; i++){
        board[i] = blank_piece;
    }
}

void initialize_board(){
    int i = 0;
    struct piece piece;
    
    for(i=0; i<BOARD_LEN; i++){
        board[i + BOARD_LEN].type = PAWN;
        board[i + BOARD_LEN].color = WHITE;
        board[i + BOARD_LEN*6].type = PAWN;
        board[i + BOARD_LEN*6].color = BLACK;
    }
    for(i=0; i<5; i++){
        switch(i){
        case 0:
            piece.type = ROOK;
            break;
        case 1:
            piece.type = KNIGHT;
            break;
        case 2:
            piece.type = BISHOP;
            break;
        case 3:
            piece.type = QUEEN;
            break;
        case 4:
            piece.type = KING;
            break;
        default:
            printf("ERROR!\n");
            break;
        }

        if(i<3){
            piece.color = WHITE;
            board[i] = board[BOARD_LEN - i - 1] = piece;
            piece.color = BLACK;
            board[i + BOARD_LEN*(BOARD_LEN-1)] = board[BOARD_LEN - i - 1 + BOARD_LEN*(BOARD_LEN-1)] = piece;
        }
        else{
            piece.color = WHITE;
            board[i] = piece;
            piece.color = BLACK;
            board[i + BOARD_LEN*(BOARD_LEN-1)] = piece;
        }
    }
}

int move_piece(int origin_point, int dest_point, int player){
    int valid = -1;
    struct piece piece;
    if(0 == player){
        piece.color = WHITE;
    }
    else{
        piece.color = BLACK;
    }

    if( (board[origin_point].color != piece.color) || (board[dest_point].color == piece.color) ){
        goto cleanup;
    }
    
    piece.color = board[origin_point].color;
    piece.type = board[origin_point].type;
    board[origin_point].color = BLACK;
    board[origin_point].type = EMPTY;

    board[dest_point] = piece;
    valid = 0;

cleanup:
    return valid;
}
