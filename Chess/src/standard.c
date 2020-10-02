#include "standard.h"
#include <termios.h>
#include <unistd.h>

struct termios attributes;

//This file includes basic/standard functions (Here raw_input and lower)

int get_raw_input(char * prompt, char ** input){
    size_t size = 0;
    int bytes_read = 0;

    printf("%s", prompt);

    bytes_read = getline(input, &size, stdin);
    if(-1 == bytes_read){
        perror("Getline error");
    }

    return bytes_read;
}

int lower(char * string, int len){
    int i = 0;

    if(1 != len){
        len = strnlen(string, BUFFER_SIZE);
        if(-1 == len){
            perror("Strnlen function error");
            goto cleanup;
        }
    }

    for(i=0; i<len; i++){
        if('A' <= string[i] && string[i] <= 'Z'){
            string[i] += 32;
        }
    }

cleanup:
    return len;
}

int change_echo(bool on){
    int error_check = 0;

    error_check = tcgetattr(STDIN_FILENO, &attributes);
    if(-1 == error_check){
        perror("Failed to retrieve terminal attributes");
        goto cleanup;
    }

    if(on){
        attributes.c_lflag |= (ECHO | ICANON);
    }
    else{
        attributes.c_lflag &= ~(ECHO | ICANON);
    }
    error_check = tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
    if(-1 == error_check){
        perror("Failed to set terminal attributes");
        goto cleanup;
    }

cleanup:
    return error_check;
}
