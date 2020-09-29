#include "chess.h"

int main(int argc, char ** argv){
    int i = 0;
    int player = 0;
    int bytes_read = 0;
    int origin_point = 0;
    int dest_point = 0;
    int valid;
    char * input = NULL;

    board = calloc(BOARD_LEN*BOARD_LEN, sizeof(struct piece));
    flush_board();
    initialize_board();
    print();

    while(true){
        while(true){
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
                printf("*******************\nInvalid request. FORMAT:\norigin > dest\nEg. A0 > B0 (Capitilization and arrangement of letter vs number doesn't matter)\n*******************\n");
                continue;
            }

            valid = move_piece(origin_point, dest_point, player);
            if(-1 == valid){
                printf("\nINVALID MOVE\n");
                continue;
            }
            break;
        }

        print();
        player = (player + 1) % 2;
    }

cleanup:
    exit(0);
}
