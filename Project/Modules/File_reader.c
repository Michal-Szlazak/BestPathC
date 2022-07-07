#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "File_reader.h"

int check_file_format(char *file_name)
{   

    int which_vertex = 0;
    int R;
    int C;
    double num;
    char *end;
    char c;
    char read_chars[101];
    int i = 0;
    int is_dot = 0;
    
    FILE *in = fopen( file_name, "r" );

    if( in == NULL )
    {
        fclose(in);
        printf("Error: Problem occurred while opening given file.\n");
        return 1;
    }

    if( !(c = fgetc(in)) )
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }

    read_chars[i++] = c;
   

    if ( !(c>'0' && c<='9') )
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }

    
    
    while(  (c = fgetc(in)) && (c>='0' && c<='9') )
    {
        if( i > 99)
        {
            fclose(in);
            printf("Error: Given file has a wrong format.\n");
            return 1;
        }

        read_chars[i++] = c;
    }

    if(c!=' ') 
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }

    read_chars[i++] = '\0';
    num = strtod(read_chars, &end);
    R = num;
    i = 0;

    if( !(num>=2 && num<=1000) )
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }
    

    if( !(c = fgetc(in)) )
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }

    read_chars[i++] = c;

    if ( !(c>'0'&&c<='9') )
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }

    while(  (c=fgetc(in)) && (c>='0'&&c<='9') )
    {
        if( i > 99)
        {
            fclose(in);
            printf("Error: Given file has a wrong format.\n");
            return 1;
        }
        read_chars[i++]=c;
    }

    read_chars[i++] = '\0';
    num = strtod(read_chars, &end);
    C = num;
    i = 0;

    if( !(num>=2 && num<=1000))
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }

    if( c == '\r' )
    c = fgetc(in);

    if( c!='\n' )
    {
        fclose(in);
        printf("Error: Given file has a wrong format.\n");
        return 1;
    }



    while(1)
    {
        while(  (c=fgetc(in)) && (c == '\t' || c == ' ') )
        {   
            continue;
        }

        if( c == '\r' || c =='\n' )
        {
            if(c == '\r')
            c = fgetc(in);

            if( c == '\n' )
            {
                which_vertex++;
                continue;
            }
            else
            {
                fclose(in);
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }

        }

        if( c == EOF )
        {
            if( which_vertex == R * C ) 
            {
                fclose(in);
                return 0;
            }
            else
            {      
                fclose(in);                                                   
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
        }
                

        while(1)
        {
            
            if ( !(c>='0' && c<='9') )
            {
                fclose(in);
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
            read_chars[i++] = c;

            while(  (c=fgetc(in)) && (c>='0' && c<='9') )
            {
                if( i > 99)
                {
                    fclose(in);
                    printf("Error: Given file has a wrong format.\n");
                    return 1;
                }
                read_chars[i++] = c;  
                
            }
            read_chars[i++] = '\0';
            num = strtod(read_chars, &end);
            i = 0;
            

            
            if( num <  0 || num > R * C - 1 )
            {
                fclose(in);
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
            
            
            if( (which_vertex + C)%C == 0 && num == which_vertex - 1) 
            {       
                fclose(in);                                                  
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }

            if( (which_vertex + 1)%C == 0 && num == which_vertex + 1 ) 
            {   
                fclose(in);                                                      
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
           
            if( num == which_vertex + 1 || num == which_vertex - 1 || num == which_vertex + C || num == which_vertex - C )
            {

            }
            else
            {     
                fclose(in);                                                    
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
            
        

            if( c!=' ' )
            {     
                fclose(in);                                                    
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }


            if( !(c = fgetc(in)) || c!= ':')
            {                        
                fclose(in);                               
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
          
           
            while(  (c = fgetc(in))  && ((c>='0'&&c<='9') || c == '.') && is_dot < 2 )
            {
                if( i > 99)
                {
                    fclose(in);
                    printf("Error: Given file has a wrong format.\n");
                    return 1;
                }
                read_chars[i++] = c;
                if(c == '.')
                is_dot++;
              
            }
            
            if( is_dot > 1)
            {      
                fclose(in);                                                   
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }

            is_dot = 0; 

            if( read_chars[i-1] == '.' ) 
            {    
                fclose(in);                                                     
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }
            i = 0;

           

            if( c == ' ' ) 
            {

                c = fgetc(in);
                
                if( c == ' ' || c == '\n' || c =='\r' )
                {

                    if( c == '\r' )
                    c = fgetc(in);

                    if( c == '\n' )
                    {
                        which_vertex++;
                        break;
                    }
                    else 
                    break;

                }
                   
                else
                {     
                    fclose(in);                                                    
                    printf("Error: Given file has a wrong format.\n");
                    return 1;
                }
                    
            }
            else
            {      
                fclose(in);                                                   
                printf("Error: Given file has a wrong format.\n");
                return 1;
            }

                
            

        }
    }    
    
    fclose(in);
    return 0; 

}


double **graph_from_file( char *file_name, int *global_rows, int *global_columns )
{
    int neig_vertex;
    int which_vertex = 0;
    double **graph;
    int R;
    int C; 
    double num; 
    char *end; 
    char c;
    char read_chars[101];
    int i=0; 

    FILE *in = fopen( file_name, "r" );

    if(in == NULL)
    {
        fclose(in);
        printf("Error: Problem occurred while opening given file.\n");
        return NULL;
    }

    while(  (c = fgetc(in)) && ( c>='0'&&c<='9' ) ) 
    {
        read_chars[i++]=c;
    }
    read_chars[i++] = '\0';
    num = strtod(read_chars, &end);
    R = num;
    *global_rows = num; 
    i = 0;



    while(  (c = fgetc(in)) && ( c>='0'&&c<='9' ) ) 
    {
        read_chars[i++]=c;
    }
    read_chars[i++] = '\0';
    num = strtod(read_chars, &end);
    C = num;
    *global_columns = num; 
    i = 0;
    

    graph = malloc(R*C * sizeof(double*));
    if (graph == NULL)
    {
        fclose(in);
        printf("ERROR: cant allocate memory (malloc_graph).\n");
        exit(1);
    }

    for( int m=0; m < R*C; m++ )
    {
        graph[m] = malloc(4 * sizeof(double));
        if (graph[m] == NULL)
        {
            fclose(in);
            printf("ERROR: cant allocate memory (malloc_graph[i]).\n");
            exit(1);
        }
        graph[m][0] = -1;
        graph[m][1] = -1;
        graph[m][2] = -1;
        graph[m][3] = -1;
    }

    if( c == '\r' )
    c = fgetc(in);

    while(1)
    {
    
        while(  (c = fgetc(in)) && (c == '\t' || c == ' ') )
        {   
            continue;
        }

        if( c == '\r' || c =='\n' )
        {
            if( c == '\r' )
            c = fgetc(in);

            if( c == '\n' )
            {
                which_vertex++;
                continue;
            }
        }
        
        if( c == EOF ) 
        {
            fclose(in);
            return graph;
        }

        while(1)
        {
            
            read_chars[i++] = c;

            while(  (c = getc(in)) && (c>='0' && c<='9') )
            {
                read_chars[i++]=c;
                
            }
            read_chars[i++] = '\0';
            num = strtod(read_chars, &end);
            i = 0;
            neig_vertex = num;

            c = fgetc(in);
           
            while(  (c = getc(in))  && ( (c>='0' && c<='9') || c == '.' ) )
            {
                read_chars[i++]=c;

              
            }
            read_chars[i++] = '\0';
            num = strtod(read_chars, &end);
            i = 0;

            if(num == 0)
            {
                printf("Error: Given file has a wrong format.\n");
                printf("The input data provided is not correct - the program is stopped.\n");
                exit(1);
            }

            if( neig_vertex == which_vertex - C)
            graph[which_vertex][0] = num;

            if( neig_vertex == which_vertex + C)
            graph[which_vertex][1] = num;

            if( neig_vertex == which_vertex + 1)
            graph[which_vertex][2] = num;

            if( neig_vertex == which_vertex - 1)
            graph[which_vertex][3] = num;

            
            if( c == ' ' ) 
            {
                c = fgetc(in);
                if( c == ' ' || c == '\n' || c == '\r' )
                {

                    if( c == '\r' )
                    c = fgetc(in);

                    if( c == '\n' )
                    {
                        which_vertex++;
                        break;
                    }
                    else 
                    break;

                }
                    
            }

                
            

        }
    }    
    
    fclose(in);
    return NULL; 

}