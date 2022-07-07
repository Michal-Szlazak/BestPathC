#include "run_program.h"
#include "BFS.h"
#include "graph_maker.h"
#include "file_maker.h"
#include "File_reader.h"
#include "check_input.h"
#include "Dijkstra.h"
#include "help.h"

#include <stdio.h>
#include <string.h>

static void run_program_file(char **user_input, int number_of_arguments)
{
    int rows;
    int columns;
    char output_mode = user_input[3][0];

    double **graph = graph_from_file(user_input[2], &rows, &columns);

    for(int i = 4; i < number_of_arguments; i += 2)
    {
        int starting_vertex = atoi(user_input[i]);
        int ending_vertex = atoi(user_input[i +1]);

        dijkstra(graph, starting_vertex, ending_vertex, output_mode, &rows, &columns);
    }

    free_graph(graph, rows, columns);
}

static void run_program_terminal(char **user_input, int number_of_arguments)
{
    int  rows = atoi(user_input[2]);
    int  columns = atoi(user_input[3]);     
    int mode = atoi(user_input[4]);
    int first_scope_of_scale = atoi(user_input[5]);
    int second_scope_of_scale = atoi(user_input[6]);
    char output_mode = user_input[7][0];
    int index_of_first_vertex = 8;

    double **graph = make_graph(mode, first_scope_of_scale, second_scope_of_scale, rows, columns);

    for(int i = index_of_first_vertex; i < number_of_arguments; i += 2)
    {
        int starting_vertex = atoi(user_input[i]);
        int ending_vertex = atoi(user_input[i +1]);
        dijkstra(graph, starting_vertex, ending_vertex, output_mode, &rows, &columns);
    }
    file_maker(graph, rows, columns);

    free_graph(graph, rows, columns);
}

void run_program (char **user_input, int number_of_arguments)
{
    char *input_mode = user_input[1];

    if(strcmp(input_mode, "F") == 0)
        run_program_file(user_input, number_of_arguments);

    if(strcmp(input_mode, "T") == 0)
        run_program_terminal(user_input, number_of_arguments);

    if(strcmp(input_mode, "help") == 0)
        help_info();
}

