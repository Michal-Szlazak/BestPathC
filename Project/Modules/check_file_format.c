#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "write_error.h"


static int read_size_from_file(char *file_name, int *rows, int *columns){

        FILE *in = fopen( file_name, "r" );

        int num_of_digits = 0;
        int space_avialiable = 1;
        char digit = fgetc(in);

        char *file_rows = (char *)malloc(space_avialiable * sizeof(char));

        while(!isspace(digit)){

                num_of_digits++;

                if(num_of_digits > space_avialiable){
                        space_avialiable *= 2;
                        char *temp = file_rows;
                        file_rows = (char *)malloc(space_avialiable * sizeof(char));
                        /*strcpy(rows, temp);*/
                }
                else{
                        file_rows[num_of_digits -1] = digit;
                }

                digit = fgetc(in);

        }

        *rows = atoi(file_rows);

        num_of_digits = 0;
        space_avialiable = 1;

        char *file_columns = (char *)malloc(space_avialiable * sizeof(char));

        while(!isspace(digit)){

                num_of_digits++;

                if(num_of_digits > space_avialiable){
                        space_avialiable *= 2;
                        char *temp = file_columns;
                        file_columns = (char *)malloc(space_avialiable * sizeof(char));
                        /*strcpy(rows, temp);*/
                }
                else{
                        file_rows[num_of_digits -1] = digit;
                }

        }

        *columns = atoi(file_columns);

        fclose(in);
}

static char *read_string(FILE *in, char *space_after_string){

        char *string = (char *)malloc(50 * sizeof(char));
        char character;
        int index = 0;

        character = fgetc(in);

        if(character == EOF){
                return "EOF";
        }

        if(isspace(character) != 0){
                printf("char - \"%c\"\n", character);
                string[0] = character;
        }
        

        while(isspace(character) == 0){
                string[index] = character;
                character = fgetc(in);
                *space_after_string = character;
                index++;
        }

        return string;

}

static int check_size_file(char *number){

        int is_size_incorrect = 0;

        for(int index = 0; index < strlen(number); index++){
                if(!isdigit(number[index])){
                        printf("ERROR: \"%s\" is not a proper size of graph. It has to be an integer.\n", number);
                        is_size_incorrect = 1;
                }
        }

        return is_size_incorrect;

}

static int read_rows_and_columns(FILE *in, int *rows, int *columns){

        int is_input_incorrect = 0;
        char space_after_string;


        char *string;
        string = read_string(in, &space_after_string);

        printf("first char = \"%c\"", string[0]);

        if(isspace(string[0]) != 0){

                write_notification("WARNING: number of rows should be place at the begening of ther first line in given file. Additional space will be ignored.\n");
                
                while(isspace(string[0]) != 0 && (string[0] != '\n' || string[0] != '\r')){
                        string = read_string(in, &space_after_string);
                }

                if(string[0] == '\n' || string[0] == '\r'){

                        write_error("ERROR: first line of file has to contain size of graph (rows and columns). Program cannot work properly without them.\n");
                        return is_input_incorrect = 1;

                }

        }

        
        if(atoi(string) == 0 && strcmp(string, "0") != 0){
                is_input_incorrect = 1;
                write_error("ERROR: first argument in a file is not a number. It is suposed to be an integer (number of rows). Program cannot work properly without it.\n");
        }
        else if(atoi(string) < 2 || atoi(string) > 1000000){
                is_input_incorrect = 1;
                write_error("ERROR: %s is out of bounds. Number of rows has to be in range <2, 1 000 000>.\n");
        }
        else{
                *rows = atoi(string);
        }

        string = read_string(in, &space_after_string);


        if(isspace(string[0]) != 0){

                write_notification("WARNING: rows and columns should be separeted by one space. Surplus will be ignored. \n");
                
                while(isspace(string[0]) != 0 && string[0] != '\n'){
                        string = read_string(in, &space_after_string);
                }

                if(string[0] == '\n'){
                        write_error("ERROR: first line has to contain two integers (number of rows and columns). Program cannot work properly without them.\n");
                        return is_input_incorrect = 1;
                }

        }

        if(atoi(string) == 0 && strcmp(string, "0") != 0){
                is_input_incorrect = 1;
                write_error("ERROR: second argument given in a file is not a number. It is suposed to be an integer (number of columns). Program cannot work properly without it.\n");
        }
        else if(atoi(string) < 2 || atoi(string) > 1000000){
                is_input_incorrect = 1;
                write_error("ERROR: %s is out of bounds. Number of columns has to be in range <2, 1 000 000>.\n");
        }
        else{
                printf("columns - %s\n", string);
                *columns = atoi(string);
        }

        if(space_after_string != '\n' && space_after_string != '\r'){
                
                write_notification("WARNING: after number of columns ther should be end of line in the file. Additional data will be ignored.\n");

                while(space_after_string != '\n' || string[0] != '\n'){
                        string = read_string(in, &space_after_string);
                }

        }

        return is_input_incorrect;

}

int check_file_format_static(char *file_name){
        
        int is_file_format_incorrect = 0;

        FILE *in = fopen(file_name, "r");



        int rows, columns;

        is_file_format_incorrect = read_rows_and_columns(in, &rows, &columns);

        printf("rows - %d, columns - %d\n", rows, columns);



        
        printf("end of file - aborting\n");
        exit(1);

        return 1;
}