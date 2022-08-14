#include "check_input.h"
#include "File_reader.h"
#include "help.h"

#include "check_file_format.h"
#include "write_error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct{

        char* tag_name;
        int count_tag_usage;
        int count_data;
        
} input_type;

typedef struct errors{
        int is_error_fatal;
        char *error_info;
        struct errors *next_error;
} error;

static void add_error (error *head, char *error_text, int is_fatal)
{
        error *temp = calloc(1, sizeof(error));

        if (temp == NULL)
        {
                printf("ERROR: memory allocation fail (BFS.c).\n");
                exit(1);
        }

        error *last = head;

        temp->error_info = malloc(sizeof(error_text));
        temp->error_info = error_text;
        temp->is_error_fatal = is_fatal;
        temp->next_error = NULL;

        while (last->next_error != NULL)
                last = last->next_error;

        last->next_error = temp;
}

static int remove_error (error **head_change, error *head)
{
    if(head_change == NULL)
        return 1;
    error *temp;
    temp = *head_change;
    *head_change = head->next_error;
    free(temp);
    free(temp->error_info);

    return 0;
}

static int error_exists (error *head, char *error_text)
{
    if(head == NULL)
        return 0;
    error *temp = head;

    while (temp->next_error != NULL)
    {
        if (temp->error_info == error_text)
            return 1;
        temp = temp->next_error;   
    }

    return 0;
}

static void free_error_memory(error *head_error){
        error *temp = head_error;

        while(head_error->next_error != NULL){
                head_error = head_error->next_error;
                free(temp);
                temp = head_error;
        }
}

static void print_error_info(error *head_error){

        error *temp = head_error;
        int count_errors = 0;


        printf("\n");
        printf("### FATAL ERRORS ###\n");

        while(temp->next_error != NULL){
                if(temp->is_error_fatal == 1){
                        printf(" %s\n", temp->error_info);
                        count_errors++;
                }

                temp = temp->next_error;
        }

        if(count_errors == 0){
                printf(" NONE\n");
        }

        count_errors = 0;
        temp = head_error;

        printf("\n");
        printf("### NOTIFICATIONS ###\n");
        while(temp->next_error != NULL){
                if(temp->is_error_fatal == 0){
                        printf(" %s\n", temp->error_info);
                        count_errors++;
                }

                temp = temp->next_error;
        }

        if(count_errors == 0){
                printf(" NONE\n");
        }

        free_error_memory(head_error);

}

static int is_a_tag(char *word_to_check){

        int result = 0;

        if(strcmp(word_to_check, "-input") == 0){
                result = 1;
        }
        if(strcmp(word_to_check, "-size") == 0){
                result = 1;
        }
        if(strcmp(word_to_check, "-mode") == 0){
                result = 1;
        }
        if(strcmp(word_to_check, "-weights") == 0){
                result = 1;
        }
        if(strcmp(word_to_check, "-output") == 0){
                result = 1;
        }
        if(strcmp(word_to_check, "-vertexes") == 0){
                result = 1;
        }
        if(strcmp(word_to_check, "-file") == 0){
                result = 1;
        }

        return result;
}

static void print_redundant_data(char **input, int tag_index, int argc){

        printf(" %s", input[tag_index]);

        if(tag_index + 1 != argc){
                tag_index++;
        }
        else{
                printf(".\n");
                return;
        }

        while(is_a_tag(input[tag_index]) != 1){
                printf(", %s", input[tag_index]);
                
                if(tag_index + 1 == argc){
                        break;
                }

                tag_index++;
        }

        printf(".\n");

}

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

static int check_file(input_type user_input, char** input, int argc, int index){

        int is_input_correct = 0;

        if(user_input.count_tag_usage > 1){
                printf("ERROR: Tag \"%s\" was used more than once, which is not unacceptable. Aborting program.", input[index]);
                exit(1);
        }

        if(!fopen(input[index + 1], "r")){
                printf("ERROR: cannot open given file (%s). Aborting program.\n", input[index + 1]);
                exit(1);
        }
        else{
                check_file_format_static(input[index + 1]);
        }

        if(is_a_tag(input[index + 1]) != 1){
                printf("To many arguments added for a tag \"%s\". Redundant data will be ignored. ", user_input.tag_name);
                printf("Ignored arguments:");
                print_redundant_data(input, index + 2, argc);
                is_input_correct = 1;
        }
        return is_input_correct;
}

static int check_size(input_type size, char** input, int index, int argc){

        int is_input_incorrect = 0;

        if(size.count_tag_usage > 1){
                printf("ERROR: Tag \"%s\" was used more than once, which is not unacceptable. Aborting program.", input[index]);
                exit(1);   
        }

        if(index + 1 < argc){
                if(atoi(input[index + 1]) < 2 || atoi(input[index + 1]) > 1000){
                        printf("ERROR: number \"%s\" after tag \"-size\" is incorrect. Aborting program.\n", input[index + 1]);
                        exit(1);
                }
        }
        else{
                printf("ERROR: too less arguments given after \"-size\" tag. program cannot work properly without a proper size. Aborting program.\n");
                exit(1);
        }

        if(index + 2 < argc){
                if(atoi(input[index + 2]) < 2 || atoi(input[index + 2]) > 1000){
                        printf("ERROR: number \"%s\" after tag \"-size\" is incorrect. Aborting program.\n", input[index + 2]);
                        exit(1);
                }
        }
        else{
                printf("ERROR: too less arguments given after \"-size\" tag. program cannot work properly without a proper size. Aborting program.\n");
                exit(1);
        }

        if (index + 3 < argc){
                printf("hello 2 %s \n", input[index + 3]);
                if(is_a_tag(input[index + 3]) != 1){
                        printf("To many arguments added for a tag \"%s\". Redundant data will be ignored. ", size.tag_name);
                        printf("Ignored arguments:");
                        print_redundant_data(input, index + 3, argc);
                        is_input_incorrect = 1;
                }
        }
        printf("check_size result - %d\n", is_input_incorrect);
        return is_input_incorrect;
}

static int check_mode(input_type mode, char **input, int argc, int index){
        
        int is_input_incorrect = 0;

        if(mode.count_tag_usage > 1){
                printf("ERROR: Tag \"%s\" was used more than once, which is not unacceptable. Aborting program.", input[index]);
                exit(1);   
        }

        if(index + 1 < argc){

                if (atoi(input[index + 1]) == 0 && strcmp(input[index + 1], "0") != 0)
                {
                        printf("ERROR: given mode is not a number. Given input \"%s\" will be ignored. Mode is set to 1. ", input[index + 1]);
                }
                else if(atoi(input[index + 1]) < 1 || atoi(input[index + 1]) > 3){
                        printf("ERROR: given mode is out of scale <1, 3>. Given number \"%s\" will be ignored. Mode is set to 1. ", input[index + 1]);
                        is_input_incorrect = 1;
                }
        }
        else
        {
                printf("ERROR: not enough data given for tag \"-mode\". Mode is set to 1.\n");
                is_input_incorrect = 1;
        }

        if(index + 2 < argc){
                if(is_a_tag(input[index + 2]) != 1){
                        printf("To many arguments added for a tag \"%s\". Redundant data will be ignored. ", mode.tag_name);
                        printf("Ignored arguments:");
                        print_redundant_data(input, index + 2, argc);
                }
        }
        return is_input_incorrect;
}

static int check_weight_scale(input_type weight_scale, char** input, int argc, int index){

        int is_input_correct = 0;

        if(weight_scale.count_tag_usage > 1){
                printf("ERROR: Tag \"%s\" was used more than once, which is not unacceptable. Aborting program.", input[index]);
                exit(1);   
        }

        if(atoi(input[index + 1]) < 0 || atoi(input[index + 1]) >= 1000){
                is_input_correct = 1;
        }

        if(atoi(input[index + 2]) < 0 || atoi(input[index + 2]) >= 1000){
                is_input_correct = 1;
        }

        if(is_a_tag(input[index + 3]) != 1){
                printf("To many arguments added for a tag \"%s\". Redundant data will be ignored. ", weight_scale.tag_name);
                printf("Ignored arguments:");
                print_redundant_data(input, index + 3, argc);
        }
        return is_input_correct;

}

static int check_output_mode(input_type output_mode, char** input, int argc, int index){

        int is_input_incorrect = 0;

        if(output_mode.count_tag_usage > 1){
                printf("ERROR: Tag \"%s\" was used more than once, which is not unacceptable. Aborting program.", input[index]);
                exit(1);   
        }

        if(index + 1 < argc){
                if(index + 1 < argc){
                        if(strcmp(input[index + 1], "B") != 0 && strcmp(input[index + 1], "E") != 0){
                                printf("ERROR: output mode can be set to Basic (\"-output B\") or Extended (\"-output E\"). Given input (\"%s\") was ignored. Output is set to Basic.\n", input[index + 1]);
                                is_input_incorrect = 1;
                        }
                }
        }
        else{
                printf("ERROR: not enough data given for tag \"-mode\". Mode is set to 1.\n");
                is_input_incorrect = 1;
        }

        if(index + 2 < argc){
                if(index + 2 < argc){
                        if(is_a_tag(input[index + 2]) != 1){
                                printf("To many arguments added for a tag \"-%s\". Redundant data will be ignored. ", output_mode.tag_name);
                                printf("Ignored arguments:");
                                print_redundant_data(input, index + 2, argc);
                        }
                }
        }

        return is_input_incorrect;

}

static int check_vertexes(input_type vertexes, char **input, int index, int argc, int rows, int columns){

        int is_input_incorrect = 0;
        int num_of_vertexes = 0;

        if(vertexes.count_tag_usage > 1){
                printf("ERROR: Tag \"%s\" was used more than once, which is not unacceptable. Aborting program.", input[index]);
                exit(1);   
        }

        if(index + 1 != argc){
                index++;
        }

        while(is_a_tag(input[index]) != 1){

                if(atoi(input[index]) == 0 && strcmp(input[index], "0") != 0){
                        printf("ERROR: Vertex \"%s\" is not an integer\n", input[index]);
                }
                else if(atoi(input[index]) >= rows * columns || atoi(input[index]) < 0){
                        num_of_vertexes++;
                        is_input_incorrect = 1;
                        printf("ERROR: Vertex \"%s\" is out of bounds.\n", input[index]);
                }
                else{
                        num_of_vertexes++;
                }

                if(index + 1 == argc){
                        break;
                }
                index++;
        }

        if(num_of_vertexes%2 != 0){
                is_input_incorrect = 1;
                printf("ERROR: The number of given vertexes cannot be odd.\n");
        }
        if(num_of_vertexes < 2){
                is_input_incorrect = 1;
                printf("ERROR: User has to give at least two vertexes.\n");
        }

        return is_input_incorrect;

}


static int check_input_no_file(int argc, char **input, int rows, int columns){

        error *top_error = (error *)malloc(sizeof(error));

        input_type size;
        input_type mode;
        input_type weight_scale;
        input_type output_mode;
        input_type vertexes;
        input_type file_name;
        
        size.tag_name = "-size";
        size.count_tag_usage = 0;
        size.count_data = 0;

        mode.tag_name = "-mode";
        mode.count_tag_usage = 0;
        mode.count_data = 0;

        weight_scale.tag_name = "-weights";
        weight_scale.count_tag_usage = 0;
        weight_scale.count_data = 0;

        output_mode.tag_name = "-output";
        output_mode.count_tag_usage = 0;
        output_mode.count_data = 0;

        vertexes.tag_name = "-vertexes";
        vertexes.count_tag_usage = 0;
        vertexes.count_data = 0;

        file_name.tag_name = "-file";
        file_name.count_tag_usage = 0;
        file_name.count_data = 0;

        int is_input_incorrect = 0;
        int fatal = 1;          //define?
        int not_fatal = 0;

        for(int i = 1; i < argc; i++){
                if(strcmp(input[i], mode.tag_name) == 0){
                        
                        mode.count_tag_usage++;
                        is_input_incorrect = check_mode(mode, input, argc, i);
                        
                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-mode\" mode is incorect. Mode will be set to 1.\n";
                                add_error(top_error, error_text, not_fatal);
                        }
                }
                if(strcmp(input[i], weight_scale.tag_name) == 0){

                        weight_scale.count_tag_usage++;
                        is_input_incorrect = check_weight_scale(weight_scale, input, argc, i);

                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-weights\" is incorrect. The scale will be set to: <0, 1>.\n";
                                add_error(top_error, error_text, not_fatal);
                        }
                }
                if(strcmp(input[i], output_mode.tag_name) == 0){
                        output_mode.count_tag_usage++;
                        is_input_incorrect = check_output_mode(output_mode, input, argc, i);

                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-mode\" is incorrect. Output mode will be set to basic.\n";
                                add_error(top_error, error_text, not_fatal);
                        }
                }
                if(strcmp(input[i], vertexes.tag_name) == 0){
                        vertexes.count_tag_usage++;
                        is_input_incorrect = check_vertexes(vertexes, input, i, argc, rows, columns);

                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-vertexes\" is incorrect.";
                                add_error(top_error, error_text, fatal);
                        }
                }

        }


        if(size.count_tag_usage =! 1){
                is_input_incorrect = 1;
                printf("ERROR: program needs size to work properly.\n");
        }
        if(vertexes.count_tag_usage != 1){
                printf("ERROR: program needs at least two vertexes to work properly.\n");
                is_input_incorrect = 1;
        }
        
        print_error_info(top_error);

        return is_input_incorrect;
}

static int check_input_file(int argc, char **input, int rows, int columns){

        error *top_error = (error *)malloc(sizeof(error));

        input_type size;
        input_type mode;
        input_type weight_scale;
        input_type output_mode;
        input_type vertexes;
        input_type file_name;
        
        size.tag_name = "-size";
        size.count_tag_usage = 0;
        size.count_data = 0;

        mode.tag_name = "-mode";
        mode.count_tag_usage = 0;
        mode.count_data = 0;

        weight_scale.tag_name = "-weights";
        weight_scale.count_tag_usage = 0;
        weight_scale.count_data = 0;

        output_mode.tag_name = "-output";
        output_mode.count_tag_usage = 0;
        output_mode.count_data = 0;

        vertexes.tag_name = "-vertexes";
        vertexes.count_tag_usage = 0;
        vertexes.count_data = 0;

        file_name.tag_name = "-file";
        file_name.count_tag_usage = 0;
        file_name.count_data = 0;

        int is_input_incorrect = 0;
        int fatal = 1;          //define?
        int not_fatal = 0;

        for(int i = 1; i < argc; i++){

                if(strcmp(input[i], size.tag_name) == 0){
                        char error_text[] = "ERROR: You cannot set size of the graph while reading graph info from file. Size of graph will be taken from file. Given data after tag \"-size\" will be ignored.";
                        add_error(top_error, error_text, not_fatal); 
                }
                if(strcmp(input[i], mode.tag_name) == 0){
                        char error_text[] = "ERROR: You cannot set generating graph mode while reading the graph from file. Given data after tag \"-mode\" will be ignored.";
                        add_error(top_error, error_text, not_fatal);
                }
                if(strcmp(input[i], weight_scale.tag_name) == 0){
                        char error_text[] = "ERROR: You cannot set scale of weights for generated paths while reading the graph from file. Given data after tag \"-weights\" will be ignored.";
                        add_error(top_error, error_text, not_fatal);
                }
                if(strcmp(input[i], output_mode.tag_name) == 0){
                        output_mode.count_tag_usage++;
                        is_input_incorrect = check_output_mode(output_mode, input, argc, i);

                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-mode\" is incorrect. Output mode will be set to basic.\n";
                                add_error(top_error, error_text, not_fatal);
                        }
                }
                if(strcmp(input[i], vertexes.tag_name) == 0){
                        vertexes.count_tag_usage++;
                        is_input_incorrect = check_vertexes(vertexes, input, i, argc, rows, columns);

                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-vertexes\" is incorrect.";
                                add_error(top_error, error_text, fatal);
                        }
                }
                if(strcmp(input[i], file_name.tag_name) == 0){
                        file_name.count_tag_usage++;
                        is_input_incorrect = check_file(file_name, input, argc, i);

                        if(is_input_incorrect == 1){
                                char error_text[] = "ERROR: input after tag \"-file\" is incorrect.";
                                add_error(top_error, error_text, fatal);
                        }
                }

        }

        if(file_name.count_tag_usage =! 1){
                is_input_incorrect = 1; 
        }
        if(vertexes.count_tag_usage =! 1){
                is_input_incorrect = 1;
        }

        return is_input_incorrect;

}

int check_input(int argc, char **input){

        remove_files();

        input_type size;
        input_type file_name;
        
        size.tag_name = "-size";
        size.count_tag_usage = 0;
        size.count_data = 0;

        file_name.tag_name = "-file";
        file_name.count_tag_usage = 0;
        file_name.count_data = 0;

        int number_of_used_tags = 0;
        int is_input_incorrect = 0;
        int graph_from_file = 0;
        int is_size_found = 0;

        int index = 0, rows, columns;

        if(argc == 1){
                printf("ERROR: there is no input. Aborting program.\n");
                exit(1);
        }

        for (int i = 1; i < argc; i++){
                if(strcmp(input[i], file_name.tag_name) == 0){
                        is_input_incorrect = check_file(file_name, input, argc, i);
                        graph_from_file = 1;
                        index = i;
                }
        }

        if(graph_from_file == 1){
                read_size_from_file(input[index], &rows, &columns);
                is_input_incorrect = check_file(file_name, input, argc, index);
        }
        
        if(graph_from_file == 0){
                for(int i = 1; i < argc; i++){
                        if(strcmp(input[i], size.tag_name) == 0){
                                size.count_tag_usage++;
                                is_input_incorrect = check_size(size, input, i, argc);
                                index = i;
                                is_size_found = 1;
                        }
                }

                if(is_size_found == 1){
                        rows = atoi(input[index + 1]);
                        columns = atoi(input[index + 2]);
                        is_input_incorrect = check_input_no_file(argc, input, rows, columns);                
                }
                else{
                        printf("ERROR: Program cannot work without given size. Aborting program.\n");
                        exit(1);
                }
        }

        return is_input_incorrect;

}