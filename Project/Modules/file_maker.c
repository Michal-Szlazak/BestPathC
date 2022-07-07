#include "file_maker.h"
#include "graph_maker.h"

#include <stdio.h>
#include <stdlib.h>

void file_maker (double **graph, int rows, int columns)
{
    FILE *file = fopen("generated_graph", "w");

    fprintf(file, "%d %d\n", rows, columns);

    for (int i = 0; i < rows * columns; i++)
    {
        fprintf(file, "\t");

        if(graph[i][0] != -1)
            fprintf(file, " %d :%f ", i - columns, graph[i][0]);

        if(graph[i][1] != -1)
            fprintf(file, " %d :%f ", i + columns, graph[i][1]);

        if(graph[i][2] != -1)
            fprintf(file, " %d :%f ", i + 1, graph[i][2]);
        
        if(graph[i][3] != -1)
            fprintf(file, " %d :%f ", i - 1, graph[i][3]);

        fprintf(file, "\n");
    }

    fclose(file);

}