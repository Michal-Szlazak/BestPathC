#include "BFS.h"
#include "graph_maker.h"

#include <stdio.h>
#include <stdlib.h>



static int q_is_empty (q_seat *index)
{
    if (index == NULL)
        return 1;
    return 0;
}

static void add_to_q (q_seat *head, int vertex)
{
    q_seat *temp = calloc(1, sizeof(q_seat));

    if (temp == NULL)
    {
        printf("ERROR: memory allocation fail (BFS.c).\n");
        exit(1);
    }

    q_seat *last = head;

    temp->vertex = vertex;
    temp->next = NULL;

    while (last->next != NULL)
        last = last->next;

    last->next = temp;
}

static int remove_from_q (q_seat **head_change, q_seat *head)
{
    if(head_change == NULL)
        return 1;
    q_seat *temp;
    temp = *head_change;
    *head_change = head->next;
    free(temp);

    return 0;
}

static int is_in_q (q_seat *head, int vertex)
{
    if(head == NULL)
        return 0;
    q_seat *temp = head;

    while (temp->next != NULL)
    {
        if (temp->vertex == vertex)
            return 1;
        temp = temp->next;   
    }

    return 0;
}

int BFS (double **graph, int rows, int columns)
{
    int *visited = (int *)calloc(rows * columns, sizeof(int));

    for (int index = 0; index < rows * columns; index++)
    {

        if (visited == NULL)
        {
            printf("ERROR: memory allocation fail (BFS.c).\n");
            exit(1);
        }

        int is_consistent = 0;

        q_seat *head = (q_seat *)malloc(sizeof(q_seat));

        if (head == NULL)
        {
            printf("ERROR: memory allocation fail (BFS.c).\n");
            exit(1);
        }

        head->vertex = index;
        head->next = NULL;

        while(q_is_empty(head) != 1)
        {
            if (graph[head->vertex][0] != -1 && visited[head->vertex - columns] != 1 && is_in_q(head, head->vertex - columns) == 0)
                add_to_q( head, head->vertex - columns);

            if (graph[head->vertex][1] != -1 && visited[head->vertex + columns] != 1 && is_in_q(head, head->vertex + columns) == 0)
               add_to_q( head, head->vertex + columns);

            if (graph[head->vertex][2] != -1 && visited[head->vertex +1] != 1 && is_in_q(head, head->vertex +1) == 0)
                add_to_q( head, head->vertex + 1);

            if (graph[head->vertex][3] != -1 && visited[head->vertex -1] != 1 && is_in_q(head, head->vertex -1) == 0)
                add_to_q( head, head->vertex -1);


            visited[head->vertex] = 1;

            if(head->vertex < index) // Jeżeli z wierzchołka X dla którego sprawdzamy spójność dotarliśmy               1 2 3
            {                        // do wierzchołka Y dla którego spójność została już sprawdzona ->
                is_consistent = 1;   // to oznacza że wierzchołek X jest spójny. (wierzchołki sprawdzane
                break;               // są po kolei więc wierzchołki sprawdzone są < index.
            }
            
        
            if (remove_from_q(&head, head) == 1)
                break;

        }

        if(is_consistent == 1)
        {
            is_consistent = 0;

            while(!q_is_empty(head))
            {
                remove_from_q(&head, head);
            }

            for(int j = 0; j < rows * columns; j++)
                visited[j] = 0;

            continue;
        }
        
    
        
        for (int j = 0; j < rows * columns; j++)
        {  
            if(visited[j] != 1)
            {               
                free(visited);
                free(head);
                return 1;
            }
        
        }
        for(int j = 0; j < rows * columns; j++)
            visited[j] = 0;

        free(head);
    }
    free(visited);
    return 0;
}