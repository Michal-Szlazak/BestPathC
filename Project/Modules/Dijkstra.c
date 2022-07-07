#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Dijkstra.h"

void dijkstra (double **graph, int starting_vertex, int ending_vertex, char output_mode, int *Rows, int *Columns)
{
    int R = *Rows;
    int C = *Columns;
    int *visited = malloc(R*C * sizeof(int));
    double *path = malloc(R*C * sizeof(double));
    int *prev = malloc(R*C * sizeof(int));
    int is_able_to_move = 0;
    double curr_path_len;
    double lowest = -1;
    int vert_lowest = -1;
    int vert_next;
    
 

    for(int i = 0; i < R*C; i++)
    {
        visited[i] = 0;
        path[i] = -1;
        prev[i] = -1;

        if( i == starting_vertex )
        {
            visited[i] = 1;
            path[i] = 0;
            prev[i] = starting_vertex;
        }
    }

    for(int g = 0; g < R*C; g++)
    {
        lowest = -1;
        vert_lowest = -1;

        for(int i = 0; i < R*C; i++)
        {
            
            if( visited[i] == 1)
            {
                for( int m = 0; m < 4; m++ )
                {

                    if( m == 0 )
                    {
                        vert_next = i - C; 
                    }    

                    if( m == 1 )                                               
                    {
                        vert_next = i + C;
                    }  

                    if( m == 2 )
                    {
                        vert_next = i + 1;
                    }   

                    if( m == 3 )
                    {
                        vert_next = i - 1;
                    } 

                    if( graph[i][m] != -1 )
                    {
                        curr_path_len = path[i] + graph[i][m];
                        if( (curr_path_len <= path[vert_next]) || path[vert_next] == -1 )
                        {
                            path[vert_next] = curr_path_len;
                            prev[vert_next] = i;
                        }

                        if( visited[vert_next] == 0 )
                        {
                            if( lowest == -1 )
                            {
                                lowest = path[vert_next];
                                vert_lowest = vert_next;
                            }
                            else
                            {
                                if( path[vert_next] <= lowest )
                                {
                                    lowest = path[vert_next];
                                    vert_lowest = vert_next;
                                }
                            }
                        }

                    }

                }
            } 


            

        }

        if(vert_lowest == -1)
        {
            break;
        }
        visited[vert_lowest] = 1;
    }

    int vert_act;
    int write_path[1000];
    double scale_weight[999];
    int g = 0;

        
    vert_act = ending_vertex;

    if(prev[ending_vertex] == -1)
    {
        printf("Error: There is no path for the given pair of vertexes.\n");
    }
    else
    {
        if( output_mode == 'E' )
        {
            if( starting_vertex == ending_vertex )
            {
                printf("(%d, %d) : ", starting_vertex, ending_vertex);
                printf("%d -> %d\n", starting_vertex, ending_vertex);
            }
            else
            {
                while( vert_act != starting_vertex )
                {
                    
                    scale_weight[g] = path[vert_act] - path[prev[vert_act]];
                    write_path[g] = vert_act;
                    vert_act = prev[vert_act];
                    g++;


                }

                write_path[g] = vert_act;

                printf("(%d, %d) : ", starting_vertex, ending_vertex);

                while( g != 0)
                {
                    printf("%d(%f)", write_path[g], scale_weight[g-1]);
                    printf(" -> ");
                    g--;
                }

                printf("%d\n", write_path[g]);

                }

            

        }

        if( output_mode == 'B' )
        {
            if( starting_vertex == ending_vertex )
            {
                printf("(%d, %d) : ", starting_vertex, ending_vertex);
                printf("%d -> %d\n", starting_vertex, ending_vertex);
            }
            else
            {
                while( vert_act != starting_vertex )
                {
                    write_path[g] = vert_act;
                    vert_act = prev[vert_act];
                    g++;
                }

                write_path[g] = vert_act;

                printf("(%d, %d) : ", starting_vertex, ending_vertex);

                while( g != 0 )
                {
                    printf("%d", write_path[g]);
                    printf(" -> ");
                    g--;
                }

                printf("%d\n", write_path[g]);

                }

            

        }

    }
    

    
    free(path);
    free(visited);
    free(prev);
       
       
}