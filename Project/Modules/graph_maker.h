#ifndef _GRAPH_MAKER_H
#define _GRAPH_MAKER_H

#include <stdio.h>

void free_graph (double **graph, int rows, int columns);

double **malloc_graph (int rows, int columns);

void draw_weights(double **graph, int start_weight, int end_weight, int rows, int columns);

void draw_edges (double **graph, int rows, int columns, int chance);

double **make_graph(int mode, int start_weight, int end_weight, int rows, int columns);

#endif