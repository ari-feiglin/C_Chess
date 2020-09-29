#include "chess.h"

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
    int sum = -1;

    if(1 != len){
        len = strnlen(string, BUFFER_SIZE);
        if(-1 == len){
            perror("Strnlen function error");
            goto cleanup;
        }
    }

    sum = 0;
    for(i=0; i<len; i++){
        if('A' <= string[i] && string[i] <= 'Z'){
            string[i] += 32;
        }
        sum += string[i];
    }

cleanup:
    return sum;
}