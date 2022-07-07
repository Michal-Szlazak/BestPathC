#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <stdlib.h>
#include <stdio.h>

int check_file_format(char *file_name);
double **graph_from_file( char *file_name, int *global_rows, int *global_columns );

#endif