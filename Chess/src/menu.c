#include "chess.h"

int MENU_LEN = 75;

int center_text(char * text, char ** centered_text, int len){
    int return_val = -1;
    int text_len = 0;
    int delay_len = 0;

    free(*centered_text);
    *centered_text = malloc(len+1);
    if(NULL == centered_text){
        perror("Malloc error");
        goto cleanup;
    }
    memset(*centered_text, ' ', len);
    (*centered_text)[len] = 0;

    text_len = strnlen(text, BUFFER_SIZE);
    if(-1 == text_len){
        perror("Strnlen function error");
        goto cleanup;
    }

    delay_len = (len-text_len)/2;

    memcpy(*centered_text+delay_len, text, text_len);

cleanup:
    return return_val;
}

int rect_text(char * text, char ** rectangled_text, int len){
    int return_val = -1;
    int text_len = 0;

    free(*rectangled_text);
    *rectangled_text = malloc(len+1);
    if(NULL == rectangled_text){
        perror("Malloc error");
        goto cleanup;
    }
    memset(*rectangled_text, ' ', len);
    (*rectangled_text)[len] = 0;

    text_len = strnlen(text, BUFFER_SIZE);
    if(-1 == text_len){
        perror("Strnlen function error");
        goto cleanup;
    }

    memcpy(*rectangled_text, text, text_len);

cleanup:
    return return_val;
}

void print_menu(int cursor_pos){
    char * string = NULL;

    system("clear");

    center_text("WELCOME TO C CHESS!", &string, MENU_LEN);
    BIU(BOLD); COLOR(RED); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    BG_COLOR(BG_BLACK); rect_text("created by Ari Feiglin 2020", &string, MENU_LEN);
    BIU(ITALIC); printf("%s", string); NCLEAR_FORMAT();

    rect_text("", &string, MENU_LEN);
    BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    if(0 == cursor_pos){
        rect_text("HOW TO", &string, MENU_LEN-2);
        BIU(BOLD); BG_COLOR(BG_BLACK); printf("> "); CLEAR_FORMAT(); BG_COLOR(BG_WHITE); COLOR(RED); printf("%s", string); NCLEAR_FORMAT();

        rect_text("  CREDITS", &string, MENU_LEN);
        BG_COLOR(BG_BLACK); COLOR(B_WHITE); printf("%s", string); NCLEAR_FORMAT();

        rect_text("  PLAY", &string, MENU_LEN);
        BG_COLOR(BG_BLACK); COLOR(B_WHITE); printf("%s", string); NCLEAR_FORMAT();
    }
    else if(1 == cursor_pos){
        rect_text("  HOW TO", &string, MENU_LEN);
        BG_COLOR(BG_BLACK); COLOR(B_WHITE); printf("%s", string); NCLEAR_FORMAT();

        rect_text("CREDITS", &string, MENU_LEN-2);
        BIU(BOLD); BG_COLOR(BG_BLACK); printf("> "); CLEAR_FORMAT(); BG_COLOR(BG_WHITE); COLOR(RED); printf("%s", string); NCLEAR_FORMAT();

        rect_text("  PLAY", &string, MENU_LEN);
        BG_COLOR(BG_BLACK); COLOR(B_WHITE); printf("%s", string); NCLEAR_FORMAT();
    }
    else{
        rect_text("  HOW TO", &string, MENU_LEN);
        BG_COLOR(BG_BLACK); COLOR(B_WHITE); printf("%s", string); NCLEAR_FORMAT();

        rect_text("  CREDITS", &string, MENU_LEN);
        BG_COLOR(BG_BLACK); COLOR(B_WHITE); printf("%s", string); NCLEAR_FORMAT();

        rect_text("PLAY", &string, MENU_LEN-2);
        BIU(BOLD); BG_COLOR(BG_BLACK); printf("> "); CLEAR_FORMAT(); BG_COLOR(BG_WHITE); COLOR(RED); printf("%s", string); NCLEAR_FORMAT();
    }

}

void print_howto(){
    char input = 0;
    char * string = NULL;

    system("clear");

    center_text("HOW TO PLAY", &string, MENU_LEN);
    BIU(BOLD); COLOR(B_RED); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();
    
    rect_text("", &string, MENU_LEN);
    BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("This is a simple game of chess, written in C.", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("No rules will be given on how to play chess here.", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("If you do not know the rules, look them up.", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("When you start the game, you will be met with a board", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("and a prompt asking you where to go.", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("The format for a move is [origin point]>[end point]", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("Do not worry about the placement of letters vs numbers or spacing", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("So both a0>a1 and 0a >1a are valid moves.", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("", &string, MENU_LEN);
    BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("click any key to return to main menu", &string, MENU_LEN);
    BIU(ITALIC); COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    while(!input){
        input = getchar();
    }
}

void print_credits(){
    char input = 0;
    char * string = NULL;

    system("clear");

    center_text("CREDITS", &string, MENU_LEN);
    BIU(BOLD); COLOR(B_RED); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();
    
    rect_text("", &string, MENU_LEN);
    BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    center_text("Written in C by Ari Feiglin in 2020", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    center_text("Free to use, copy, and distribute", &string, MENU_LEN);
    COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("", &string, MENU_LEN);
    BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    rect_text("click any key to return to main menu", &string, MENU_LEN);
    BIU(ITALIC); COLOR(B_WHITE); BG_COLOR(BG_BLACK); printf("%s", string); NCLEAR_FORMAT();

    while(!input){
        input = getchar();
    }
}

voi menu(){
    char input = 0;
    int cursor_pos = 0;

    change_echo(false);

    while(true){
        print_menu(cursor_pos);
        input = getchar();
        if('\033' == input){
            input = getchar();
            if('[' == input){
                input = getchar();
                if('A' == input){
                    cursor_pos--;
                }
                else if('B' == input){
                    cursor_pos++;
                }
            }
        }
        else if('\n' == input){
            cursor_pos %= 3;
            if(0 == cursor_pos){
                print_howto();
            }
            else if(1 == cursor_pos){
                print_credits();
            }
            else{
                break;
            }
        }
    }

    change_echo(true);
}
