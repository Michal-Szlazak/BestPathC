#include "run_program.h"
#include "BFS.h"
#include "graph_maker.h"
#include "file_maker.h"
#include "File_reader.h"
#include "check_input.h"
#include "Dijkstra.h"
#include "help.h"
#include "check_input.h"

#include <stdio.h>
#include <string.h>

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


static char get_output_mode(char **user_input, int number_of_arguments){

    char default_output_mode = 'B';

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-output") == 0){
            return user_input[i + 1][0];                    //output_mode is a one letter so
        }                                                   //we only need the first char after "-output"

    }

    return default_output_mode;
}

static char *get_file_name(char **user_input, int number_of_arguments){

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-file") == 0){
            return user_input[i + 1];                    
        }

    }

    return NULL;
    
}

static int get_number_of_vertexes(char **user_input, int number_of_arguments){

    int num_of_vertexes = 0;

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-vertexes") == 0){

            i++;
            while(is_a_tag(user_input[i]) != 1){
                
                i++;
                num_of_vertexes++;

                if(i == number_of_arguments){
                    break;
                }

            }
            return num_of_vertexes;
        }
    }

    return num_of_vertexes;
}

static int get_vertex(char **user_input, int number_of_arguments, int vertex_number){

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-vertexes") == 0){
            return atoi(user_input[i + vertex_number]);
        }

    }
}

static void run_program_file(char **user_input, int number_of_arguments)
{
    int rows;
    int columns;
    int number_of_vertexes = get_number_of_vertexes(user_input, number_of_arguments);
    char output_mode = get_output_mode(user_input, number_of_arguments);
    char *file_name = get_file_name(user_input, number_of_arguments);

    double **graph = graph_from_file(file_name, &rows, &columns);

    for(int i = 1; i < number_of_vertexes; i += 2)
    {
        int starting_vertex = get_vertex(user_input, number_of_arguments, i);
        int ending_vertex = get_vertex(user_input, number_of_arguments, i + 1);

        dijkstra(graph, starting_vertex, ending_vertex, output_mode, &rows, &columns);
    }

    free_graph(graph, rows, columns);
}


static int get_rows(char** user_input, int number_of_arguments){

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-size") == 0){
            return atoi(user_input[i + 1]);                    
        }

    }
}

static int get_columns(char** user_input, int number_of_arguments){

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-size") == 0){
            return atoi(user_input[i + 2]);                    
        }

    }
}

static int get_mode(char** user_input, int number_of_arguments){

    int default_mode = 1;

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-mode") == 0){
            return atoi(user_input[i + 1]);                    
        }

    }

    return default_mode;
}

static int get_weigh_limit(char **user_input, int number_of_arguments, char* down_or_up){

    int first_limit;
    int second_limit;

    int is_weight_given = 0;

    for(int i = 1; i < number_of_arguments; i++){
        
        if(strcmp(user_input[i], "-weight") == 0){
            first_limit = atoi(user_input[i + 1]);
            second_limit = atoi(user_input[i + 2]);
            is_weight_given = 1;
        }
    }

    if(strcmp(down_or_up, "down") == 0){
        
        if(is_weight_given == 0){
            first_limit = 0;
            return first_limit;
        }
        else{
            if(first_limit < second_limit)
                return first_limit;
            else
                return second_limit;
        }
    }

    if(strcmp(down_or_up, "up") == 0){
        
        if(is_weight_given == 0){
            second_limit = 1;
            return second_limit;
        }
        else{
            if(first_limit > second_limit)
                return first_limit;
            else
                return second_limit;
        }
    }

}

static void run_program_terminal(char **user_input, int number_of_arguments)
{
    int  rows = get_rows(user_input, number_of_arguments);
    int  columns = get_columns(user_input, number_of_arguments);
    int mode = get_mode(user_input, number_of_arguments);
    int first_scope_of_scale = get_weigh_limit(user_input, number_of_arguments, "down");
    int second_scope_of_scale = get_weigh_limit(user_input, number_of_arguments, "up");
    char output_mode = get_output_mode(user_input, number_of_arguments);
    int number_of_vertexes = get_number_of_vertexes(user_input, number_of_arguments);

    double **graph = make_graph(mode, first_scope_of_scale, second_scope_of_scale, rows, columns);
    for(int i = 1; i < number_of_vertexes; i += 2)
    {
        int starting_vertex = get_vertex(user_input, number_of_arguments, i);
        int ending_vertex = get_vertex(user_input, number_of_arguments, i + 1);
        dijkstra(graph, starting_vertex, ending_vertex, output_mode, &rows, &columns);
    }
    file_maker(graph, rows, columns);

    free_graph(graph, rows, columns);
}

void run_program (char **user_input, int number_of_arguments)
{

    int input_from_file = 0;

    for(int i = 1; i < number_of_arguments; i++){

        if(strcmp(user_input[i], "-file") == 0){
            input_from_file = 1;
            break;
        }
    }

    if(input_from_file == 1){
        run_program_file(user_input, number_of_arguments);
    }
    else{
        run_program_terminal(user_input, number_of_arguments);
    }
/*
    if(strcmp(input_mode, "help") == 0)
        help_info();
*/
}

