#include "graph_maker.h"
#include "BFS.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void free_graph(double **graph, int rows, int columns)
{
    for (int i = 0; i < rows * columns; i++)
    {
        free(graph[i]);
    }
    free(graph);
}

double **malloc_graph(int rows, int columns)
{
    double **graph = (double **)malloc(rows * columns * sizeof(double*));

    if (graph == NULL)
    {
        printf("ERROR: memory allocation fail (malloc_graph.c).\n");
        exit(1);
    }

    for(int i = 0; i < rows * columns; i++)
    {
        graph[i] = (double *)malloc(4 * sizeof(double));

        if (graph[i] == NULL)
        {
            printf("ERROR: memory allocation fail (malloc_graph.c).\n");
            exit(1);
        }
    }
    
    return graph;

}

void draw_weights (double **graph, int start_weight, int end_weight, int rows, int columns)
{

    int smaller_weight = start_weight;
    int greater_weight = end_weight;

    if (smaller_weight > greater_weight)
    {
        int temp = smaller_weight;
        smaller_weight = greater_weight;
        greater_weight = temp;
    }

    for (int i = 0; i < rows * columns; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            graph[i][j] = (double)rand() / RAND_MAX * (greater_weight - smaller_weight) + smaller_weight;
        }
    }


    for (int i = 0; i < columns; i++)
    {
        graph[i][0] = -1;
        graph[columns * (rows - 1) + i][1] = -1;
    }

    for (int i = 0; i < rows; i++)
    {
        graph[i * columns][3] = -1;
        graph[i * columns + columns - 1][2] = -1;
    }
    
}

void draw_edges (double **graph, int rows, int columns, int chance)
{
    int count = 0, los; 
    for (int i = 0; i < rows * columns; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            los = rand();
            if(los % chance == 0)
            {
                graph[i][j] = -1;
                count++;
            }
        }
    }
}

double **make_graph(int mode, int start_weight, int end_weight, int rows, int columns)
{
    srand(time(0));
    double **graph = malloc_graph(rows, columns);
    int chance;

    if (mode == 1)
    {
        draw_weights(graph, start_weight, end_weight, rows, columns);      
    }

    if(mode == 2)
    {
        int is_consistent = 1;
        chance = 2;

        while( is_consistent == 1)
        {
            draw_weights(graph, start_weight, end_weight, rows, columns);
            draw_edges(graph, rows, columns, chance);

            is_consistent = BFS(graph, rows, columns);

            chance *= 2;
        }
    }

    if(mode == 3)
    {
        chance = 3;
        draw_weights(graph, start_weight, end_weight, rows, columns);
        draw_edges(graph, rows, columns, chance);   
    }

    return graph;
}
