#include <stdio.h>
#include <stdlib.h>

void write_error(char *error_text){

    FILE *error_file = fopen("error_file.txt", "w");

    fprintf(error_file, "%s", error_text);

    fclose(error_file);
}

void write_notification(char *notification_text){

    FILE *notification_file = fopen("notification_file.txt", "w");

    fprintf(notification_file, "%s",notification_text);

    fclose(notification_file);
}

void remove_files(){
    remove("error_file.txt");
    remove("notification_file.txt");
}
