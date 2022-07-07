#include "help.h"

#include <stdio.h>
#include <stdlib.h>

void help_info()
{
    printf("====================== Instructions ======================\n");
    printf("### Dzialanie programu ###\n");
    printf("1# Kompilcja programu: komenda \"make\".\n\n");
    printf("2# Uruchomienie za pomocą terminala:\n");
    printf(" - Uruchomienie: ./a.out [insert_mode] [number_of_rows] [number_of_columns] [mode] [1# scope_of_scales] [2# scope_of_scales] [output_mode] [1# vertex] [2# vertex] ... (dowolnie więcej par wierzchołków).\n\n");
    printf(" - Informacje o zmiennych:\n");
    printf("\t [insert_mode] - przyjmuje wartosci {F, T}. F - wczytanie grafu z pliku, T - wygenerowanie grafu z terminala.\n");
    printf("\t [number_of_rows] - przyjmuje wartosci <2, 1000>.\n");
    printf("\t [number_of_columns] - przyjmuje wartosci <2, 1000>.\n");
    printf("\t [mode] - przyjmuje wartości {1, 2, 3} (Wybrany tryb uruchomienia programu - tryby opisane są w specyfikacji funkcjionalnej).\n");
    printf("\t [1# scope_of_scales] - przyjmuje wartosci w przedziale <1, 10000>.\n");
    printf("\t [2# scope_of_scales] - przyjmuje wartosci w przedziale <1, 10000>.\n");
    printf("\t [output_mode] - przyjmuje wartosci {B, E}. B - wyświetlanie Basic, E - Extended (więcej inforamcji w specyfikacji funkcjonalnej).\n");
    printf("\t [1# vertex] - przyjmuje wartosci <0, n>, gdzie n -> number_of_rows * number_of_columns -1 (najwiekszy mozliwy indeks).\n");
    printf("\t [2# vertex] - przyjmuje wartosci <0, n>, gdzie n -> number_of_rows * number_of_columns -1 (najwiekszy mozliwy indeks).\n");

    printf("\n");
    printf("3# Uruchomienie z użyciem pliku\n");
    printf(" - Uruchomienie: ./a.out [insert_mode] [file_name] [output_mode] [1# vertex] [2# vertex] ... (dowolnie więcej par wierzchołków).\n\n");
    printf(" - Informacje o zmiennych:\n");
    printf("\t [file_name] - przyjmuje nazwe pliku do 26 znakow.\n");
    printf("\t pozostale zmienne zostaly opisane w punkcie 2#\n");

    printf("\n\n### Makefile ###\n\n");
    printf("\tkomenda \"make\" -> tworzy plik a.out pozwalający uruchomić program.\n");
    printf("\tkomenda \"make test1\" -> wykonuje test poprawnego sprawdzenia danych wejsciowych przez program.\n");
    printf("\tkomenda \"make test2\" -> wykonuje test poprawnego sprawdzenia formatu pliku przez program.\n");
    printf("\tkomenda \"make test3\" -> wykonuje test zatrzymania programu, jesli podany plik przez uzytkownika nie istnieje.\n");

}