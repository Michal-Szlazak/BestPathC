#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    printf("argc - %d, strlen - %ld\n", argc, sizeof(argv));
    printf("two dim ar - %d", (int) (sizeof(char**)));

}