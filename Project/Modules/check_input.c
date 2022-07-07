#include "check_input.h"
#include "File_reader.h"
#include "help.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int check_input (int argc, char **input)
{

        int if_error = 0;
        int not_enough_data = 0;

        
        if(argc == 1)
        {
                printf("ERROR: Too little data is given.\n");
                return 1;
        }

        if (argc < 2)
        {
                not_enough_data = 1;
        }
        else if( strcmp(input[1], "F") && strcmp(input[1], "T") && strcmp(input[1], "help"))
        {
                printf("ERROR: incorrect data - insert mode, use \"help\" for more information.\n");
                if_error = 1;
        }
         else if( !strcmp(input[1], "help") )
        {
                help_info();
                exit(0);
        }


        char rows_from_file[4] = "0";
        char columns_from_file[4] = "0";
        FILE *f;
        if (argc < 3)
        {
                not_enough_data = 1;
        }
        else if (!strcmp(input[1], "T") && atoi(input[2]) == 0 && strcmp(input[2], "0") )
        {
                printf("ERROR: incorrect data - number of rows, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if( !strcmp(input[1], "T") && (atoi(input[2]) < 2 || atoi(input[2]) > 1000) )
        {
                printf("ERROR: incorrect data - number of rows, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if (!strcmp(input[1], "F") && !( f = fopen(input[2], "r")) || sizeof(input[2]) > 26)
        {
                printf("ERROR: incorrect data - file name, use \"help\" for more informatione.\n");
                printf("The input data provided is not correct - the program is stopped.\n");
                if_error = 1;
                exit(1);
        }
        else if( !strcmp(input[1], "F") && check_file_format(input[2]) == 1)
	{
		return 1;
	}
	else if( !strcmp(input[1], "F"))
        {
                char znak;
                int index = 0;
                while( isspace(znak = fgetc(f)) == 0)
                {
                        rows_from_file[index] = znak;
                        index++;
                }
                index = 0;
                while( isspace(znak = fgetc(f)) == 0)
                {
                        columns_from_file[index] = znak;
                        index++;
                }

                fclose(f);
                
        }


         if (argc < 4)
        {
                not_enough_data = 1;
        }
        else if ( !strcmp(input[1], "T") && atoi(input[3]) == 0 && strcmp(input[3], "0"))
        {
                printf("ERROR: incorrect data - number of columns, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if( !strcmp(input[1], "T") && (atoi(input[3]) < 2 || atoi(input[3]) > 1000))
        {
                printf("ERROR: incorrect data - number of columns, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if( !strcmp(input[1], "F") && (strcmp(input[3], "B") && strcmp(input[3], "E")))
        {
                printf("ERROR: incorrect data - output mode, use \"help\" for more information.\n");
                if_error = 1;
        }


        if (!strcmp(input[1], "F") && argc < 5)
                not_enough_data = 1;
        else if ( !strcmp(input[1], "F"))
        {
                if ((argc - 4) % 2 != 0)
                {
                        printf("ERROR: incorrect data - the number of vertices must be an even number.\n");
                        if_error = 1;
                }

                for (int i = 4; i < argc; i++)
                {
                        if ( (atoi(input[i]) > atoi(rows_from_file) * atoi(columns_from_file) - 1 || atoi(input[i]) < 0) || (atoi(input[i]) == 0 && strcmp(input[i], "0")) )
                        {
                                printf("ERROR: incorrect data - vertex, use \"help\" for more information.\n");
                                if_error = 1;
                        }
                }

        }


        if (not_enough_data == 1 && !strcmp(input[1], "F"))
        {
                printf("ERROR: Too little data is given.\n");
                if_error = 1;
        }



        if (argc < 5)
        {
                not_enough_data = 1;
        }
        else if (!strcmp(input[1], "T") && atoi(input[4]) == 0 && strcmp(input[4], "0"))
        {
                printf("ERROR: incorrect data - mode, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if( !strcmp(input[1], "T") && atoi(input[4]) != 1 && atoi(input[4]) != 2 && atoi(input[4]) != 3)
        {
                printf("ERROR: incorrect data - mode, use \"help\" for more information.\n");
                if_error = 1;
        }
        


        if ( argc < 6)
        {
                not_enough_data = 1;
        }
        else if ( !strcmp(input[1], "T") && atoi(input[5]) == 0 && strcmp(input[5], "0") && sizeof(input[5])/sizeof(input[5][0]) < 10)
        {
                printf("ERROR: incorrect data - scope of scales, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if( !strcmp(input[1], "T") && atoi( input[5]) < 0 || atoi(input[5]) > 10000)
        {
                printf("ERROR: incorrect data - scope of scales, use \"help\" for more information.\n");
                if_error = 1;
        }



        if ( argc < 7)
        {
                not_enough_data = 1;
        }
        else if ( !strcmp(input[1], "T") && atoi(input[6]) == 0 && strcmp(input[6], "0"))
        {
                printf("ERROR: incorrect data - scope of scales, use \"help\" for more information.\n");
                if_error = 1;
        }
        else if( !strcmp(input[1], "T") && atoi(input[6]) <= 0 || atoi(input[6]) > 10000)
        {
                printf("ERROR: incorrect data - scope of scales, use \"help\" for more information.\n");
                if_error = 1;
        }

         if ( argc < 8)
        {
                not_enough_data = 1;
        }
        else if( !strcmp(input[1], "T") && (strcmp(input[7], "B") && strcmp(input[7], "E")))
        {
                printf("ERROR: incorrect data - output mode, use \"help\" for more information.\n");
                if_error = 1;
        }



        if ( argc < 9)
        {
                not_enough_data = 1;
        }
        else if ( !strcmp(input[1], "T"))
        {
                if ((argc - 8) % 2 != 0)
                {
                        printf("ERROR: incorrect data - the number of vertices must be an even number.\n");
                        if_error = 1;
                }

                for (int i = 8; i < argc; i++)
                {
                        if ( (atoi(input[i]) > atoi(input[2])*atoi(input[3]) - 1 || atoi(input[i]) < 0) || (atoi(input[i]) == 0 && strcmp(input[i], "0")) )
                        {
                                printf("ERROR: incorrect data - vertex, use \"help\" for more information.\n");
                                if_error = 1;
                        }
                }
        }

        if (not_enough_data == 1 && !strcmp(input[1], "T"))
        {
                printf("ERROR: Too little data is given.\n");
                if_error = 1;
        }

        if (if_error == 1)
                return 1;

        return 0;

}
