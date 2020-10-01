#include "chess.h"

int main(int argc, char ** argv){
    int i = 0;
    int player = 0;
    int bytes_read = 0;
    int origin_point = 0;
    int dest_point = 0;
    int valid = 0;
    char * input = NULL;

    menu();

    board = calloc(BOARD_LEN*BOARD_LEN, sizeof(piece));
    flush_board();
    initialize_board();
    print();

    while(1 != valid){
        valid = -1;
        while(-1 == valid){
            if(0 == player){
                printf("WHITE ");
            }
            else{
                printf("BLACK ");
            }
            bytes_read = get_raw_input("where would you like to go?\n", &input);
            if(-1 == bytes_read){
                goto cleanup;
            }

            bytes_read = parse_input(input, &origin_point, &dest_point);
            if(-1 == bytes_read){
                goto cleanup;
            }
            if(-1 == origin_point || -1 == dest_point){
                printf("INVALID FORMAT\n");
                continue;
            }

            valid = move_piece(origin_point, dest_point, player);
            if(-1 == valid){
                printf("\nINVALID MOVE\n");
            }
        }

        print();
        if(1 == valid){
            switch(player){
            case 0: printf("WHITE wins!\n"); break;
            case 1: printf("BLACK wins!\n"); break;
            }
        }
        player = (player + 1) % 2;
    }

cleanup:
    exit(0);
}
