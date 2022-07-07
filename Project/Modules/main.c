#include "run_program.h"
#include "check_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char **argv)
{
        int is_input_correct = check_input(argc, argv);
        printf("%d\n", is_input_correct);
        if (is_input_correct == 1)
        {
                printf("The input data provided is not correct - the program is stopped.\n");
                exit(1);
        }

        run_program(argv, argc);

}