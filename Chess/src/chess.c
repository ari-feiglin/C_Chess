#include "chess.h"

typedef enum {UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT}direction;

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

    if(!dest || -1 == origin_column || -1 == origin_row || -1 == dest_column || -1 == dest_row){
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
    game_colors bg_color = TILE1_COLOR;

    system("clear");

    printf("\n  A B C D E F G H\n");
    for(i=0; i<BOARD_LEN; i++){
        printf("%i ", i);
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
           printf("\e[%dm\033[%dm\033[%dm%c \033[%dm", BOLD, bg_color, board[i*BOARD_LEN + j].color, piece, NORMAL);
           if(TILE2_COLOR == bg_color){
               bg_color = TILE1_COLOR;
           }
           else{
               bg_color = TILE2_COLOR;
           }
       }
       printf(" \033[%dm\n", NORMAL);
       if(TILE2_COLOR == bg_color){
            bg_color = TILE1_COLOR;
        }
        else{
            bg_color = TILE2_COLOR;
        }
    }

    printf("\n");
    return 0;
}

void flush_board(){
    int i = 0;
    piece blank_piece;
    blank_piece.type = EMPTY;
    blank_piece.color = CLEAR;

    for(i=0; i<BOARD_LEN*BOARD_LEN; i++){
        board[i] = blank_piece;
    }
}

void initialize_board(){
    int i = 0;
    piece piece;
    
    for(i=0; i<BOARD_LEN; i++){
        board[i + BOARD_LEN].type = PAWN;
        board[i + BOARD_LEN].color = PLAYER1_COLOR;
        board[i + BOARD_LEN*6].type = PAWN;
        board[i + BOARD_LEN*6].color = PLAYER2_COLOR;
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
            piece.color = PLAYER1_COLOR;
            board[i] = board[BOARD_LEN - i - 1] = piece;
            piece.color = PLAYER2_COLOR;
            board[i + BOARD_LEN*(BOARD_LEN-1)] = board[BOARD_LEN - i - 1 + BOARD_LEN*(BOARD_LEN-1)] = piece;
        }
        else{
            piece.color = PLAYER1_COLOR;
            board[i] = piece;
            piece.color = PLAYER2_COLOR;
            board[i + BOARD_LEN*(BOARD_LEN-1)] = piece;
        }
    }
}

int move_piece(int origin_point, int dest_point, int player){
    int valid = -1;
    piece piece;
    int first_boost = 0;
    int i = 0;
    direction direction = 0;

    if(0 == player){
        piece.color = PLAYER1_COLOR;
    }
    else{
        piece.color = PLAYER2_COLOR;
    }

    if( (board[origin_point].color != piece.color) || ((board[dest_point].color == piece.color) && (board[dest_point].type != EMPTY)) ){
        goto cleanup;
    }

    switch(board[origin_point].type){
    case PAWN:
        if(PLAYER1_COLOR == board[origin_point].color){
            if(BOARD_LEN <= origin_point && origin_point < BOARD_LEN * 2){
                first_boost = 1;
            }
            if( ((dest_point != origin_point + BOARD_LEN) &&                        //(If not a 1 spot jump and
            ((dest_point != origin_point + BOARD_LEN + first_boost * BOARD_LEN) ||  //(Not a 2 spot jump on first move or
            (board[dest_point+BOARD_LEN].type != EMPTY)) ||                         //The spot before the two jump is inhabited) or
            (board[dest_point].type != EMPTY)) &&                                   //Not an empty space) and
            ((dest_point - origin_point - BOARD_LEN !=  1) &&                       //(Not a kill and
            (dest_point - origin_point - BOARD_LEN !=  -1) ||                       //Not a kill (again) or
            (board[dest_point].color != PLAYER2_COLOR)) ){                                  //Oponent isn't opponent's color)
                goto cleanup;
            }
        }
        else{
            if(BOARD_LEN * 6 <= origin_point && origin_point < BOARD_LEN * 7){
                first_boost = 1;
            }
            if( ((dest_point != origin_point - BOARD_LEN) &&                        //(If not a 1 spot jump and
            ((dest_point != origin_point - BOARD_LEN - first_boost * BOARD_LEN) ||  //(Not a 2 spot jump on first move or
            (board[dest_point+BOARD_LEN].type != EMPTY)) ||                         //The spot before the two jump is inhabited) or
            (board[dest_point].type != EMPTY)) &&                                   //Not an empty space) and
            ((origin_point - dest_point - BOARD_LEN !=  1) &&                       //(Not a kill and
            (origin_point - dest_point - BOARD_LEN !=  -1) ||                       //Not a kill (again) or
            (board[dest_point].color != PLAYER2_COLOR)) ){                                  //Check if opponenent is correct color)
                goto cleanup;
            }
        }
        break;

    case ROOK:
       if(dest_point % BOARD_LEN == origin_point % BOARD_LEN){                     //If on same column
            if(dest_point > origin_point){
                direction = DOWN;                                                   //direction is down on the board
            }
            else{
                direction = UP;                                                     //direction is up on the board
            }
        }
        else if(dest_point / BOARD_LEN == origin_point / BOARD_LEN){                //If on same row
            if(dest_point > origin_point){
                direction = RIGHT;                                                  //direction is right on board
            }
            else{
                direction = LEFT;                                                   //direction is left on board
            }
        }
        else{
            goto cleanup;                                                           //Not on same row or column; Illegal rook move.
        }

        switch(direction){
        case DOWN:
            for(i=origin_point+BOARD_LEN; i<dest_point; i+=BOARD_LEN){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case UP:
            for(i=origin_point-BOARD_LEN; i>dest_point; i-=BOARD_LEN){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case RIGHT:
            for(i=origin_point+1; i<dest_point; i++){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        default:
            for(i=origin_point-1; i<dest_point; i--){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        }

    case KNIGHT:
        if( (abs(dest_point - origin_point - BOARD_LEN * 2) != 1) &&                //Not down 2 left/right 1
        (abs(origin_point - dest_point - BOARD_LEN * 2) != 1) &&                    //Not up 2 left/right 1
        (abs(dest_point - origin_point - BOARD_LEN) != 2) &&                        //Not down 1 left/right 2
        (abs(origin_point - dest_point - BOARD_LEN) != 2) ){                        //Not up 1 left/right 2
            goto cleanup;
        }
        break;

    case BISHOP:
        if(dest_point/BOARD_LEN - origin_point/BOARD_LEN == dest_point%BOARD_LEN - origin_point%BOARD_LEN){                 //If the difference in rows equals the difference in columns
            if(dest_point > origin_point){
                direction = DOWNRIGHT;                                              //Direction is diagonal- down + right
            }
            else{
                direction = UPLEFT;                                                 //Direction is diagonal up + left
            }
        }
        else if(dest_point/BOARD_LEN - origin_point/BOARD_LEN == -1 * (dest_point%BOARD_LEN - origin_point%BOARD_LEN)){     //If the difference in rows equals the negative difference in columns
            if(dest_point > origin_point){
                direction = DOWNLEFT;                                               //Direction is diagonal- down + right
            }
            else{
                direction = UPRIGHT;                                                //Direction is diagonal up + left
            }
        }
        else{
            goto cleanup;
        }

        switch(direction){
        case DOWNRIGHT:
            for(i=origin_point+BOARD_LEN+1; i<dest_point; i+=BOARD_LEN+1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case DOWNLEFT:
            for(i=origin_point+BOARD_LEN-1; i<dest_point; i+=BOARD_LEN-1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case UPRIGHT:
            for(i=origin_point-BOARD_LEN+1; i>dest_point; i-=BOARD_LEN-1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        default:
            for(i=origin_point-BOARD_LEN-1; i>dest_point; i-=BOARD_LEN+1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        }
        break;

    case QUEEN:
        if(dest_point % BOARD_LEN == origin_point % BOARD_LEN){                     //If on same column
            if(dest_point > origin_point){
                direction = DOWN;                                                   //direction is down on the board
            }
            else{
                direction = UP;                                                     //direction is up on the board
            }
        }
        else if(dest_point / BOARD_LEN == origin_point / BOARD_LEN){                //If on same row
            if(dest_point > origin_point){
                direction = RIGHT;                                                  //direction is right on board
            }
            else{
                direction = LEFT;                                                   //direction is left on board
            }
        }
        else if(dest_point/BOARD_LEN - origin_point/BOARD_LEN == dest_point%BOARD_LEN - origin_point%BOARD_LEN){                 //If the difference in rows equals the difference in columns
            if(dest_point > origin_point){
                direction = DOWNRIGHT;                                              //Direction is diagonal- down + right
            }
            else{
                direction = UPLEFT;                                                 //Direction is diagonal up + left
            }
        }
        else if(dest_point/BOARD_LEN - origin_point/BOARD_LEN == -1 * (dest_point%BOARD_LEN - origin_point%BOARD_LEN)){     //If the difference in rows equals the negative difference in columns
            if(dest_point > origin_point){
                direction = DOWNLEFT;                                               //Direction is diagonal- down + right
            }
            else{
                direction = UPRIGHT;                                                //Direction is diagonal up + left
            }
        }
        else{
            goto cleanup;                                                           //Not on same row or column; Illegal rook move.
        }

        switch(direction){
        case DOWN:
            for(i=origin_point+BOARD_LEN; i<dest_point; i+=BOARD_LEN){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case UP:
            for(i=origin_point-BOARD_LEN; i>dest_point; i-=BOARD_LEN){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case RIGHT:
            for(i=origin_point+1; i<dest_point; i++){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case LEFT:
            for(i=origin_point-1; i<dest_point; i--){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case DOWNRIGHT:
            for(i=origin_point+BOARD_LEN+1; i<dest_point; i+=BOARD_LEN+1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case DOWNLEFT:
            for(i=origin_point+BOARD_LEN-1; i<dest_point; i+=BOARD_LEN-1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        case UPRIGHT:
            for(i=origin_point-BOARD_LEN+1; i>dest_point; i-=BOARD_LEN-1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        default:
            for(i=origin_point-BOARD_LEN-1; i>dest_point; i-=BOARD_LEN+1){
                if(board[i].type != EMPTY){
                    goto cleanup;
                }
            }
            break;
        }
        break;

    case KING:
        if( (abs(dest_point - origin_point) != BOARD_LEN) &&                        //Not moving up or down and            
        (abs(dest_point - origin_point) != 1) &&                                    //Not moving left or right and
        (abs(dest_point - origin_point) != BOARD_LEN + 1) &&                        //Not moving up+right or down+left and
        (abs(dest_point - origin_point) != BOARD_LEN - 1) ){                        //Not moving up+left or down+right
            goto cleanup;
        }
        break;

    }

    valid = 0;
    if(KING == board[dest_point].type ){
        valid = 1;                                                                  //Game won
    }
    piece.color = board[origin_point].color;
    piece.type = board[origin_point].type;
    board[origin_point].color = CLEAR;
    board[origin_point].type = EMPTY;

    board[dest_point] = piece;


cleanup:
    return valid;
}
