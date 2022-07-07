#ifndef _BFS_H_
#define _BFS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct queue {

    int vertex;
    struct queue *next;

}   q_seat;

int BFS (double **graph, int rows, int columns);

#endif