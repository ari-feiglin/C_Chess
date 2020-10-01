#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUFFER_SIZE (1024)

int get_raw_input(char * prompt, char ** input);
int lower(char * string, int len);
int change_echo(bool on);
