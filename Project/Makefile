compile: main.o BFS.o graph_maker.o file_maker.o File_reader.o check_input.o Dijkstra.o help.o run_program.o
	$(CC) main.o BFS.o graph_maker.o file_maker.o File_reader.o check_input.o Dijkstra.o help.o run_program.o

debug: a.out
	$(CC) -g Modules/main.c Modules/BFS.c Modules/graph_maker.c Modules/file_maker.c Modules/File_reader.c Modules/check_input.c Modules/Dijkstra.c Modules/help.c Modules/run_program.c

Dijkstra.o: Modules/Dijkstra.h
	$(CC) -c Modules/Dijkstra.c

check_input.o: Modules/check_input.h
	$(CC) -c Modules/check_input.c

BFS.o: Modules/BFS.h
	$(CC) -c Modules/BFS.c

graph_maker.o: Modules/BFS.h Modules/graph_maker.h
	$(CC) -c Modules/graph_maker.c

file_maker.o: Modules/graph_maker.h Modules/file_maker.h
	$(CC) -c Modules/file_maker.c

File_reader.o: Modules/File_reader.h
	$(CC) -c Modules/File_reader.c

main.o: Modules/BFS.h Modules/graph_maker.h Modules/file_maker.h Modules/File_reader.h Modules/graph_maker.h Modules/check_input.h Modules/Dijkstra.h
	$(CC) -c Modules/main.c

help.o: Modules/help.h
	$(CC) -c Modules/help.c

run_program.o: Modules/run_program.h Modules/BFS.h Modules/graph_maker.h Modules/file_maker.h Modules/File_reader.h Modules/graph_maker.h Modules/check_input.h Modules/Dijkstra.h
	$(CC) -c Modules/run_program.c


.PHONY: clean

clean:
	-rm *.o

test1:
	clear
	@echo "### Wykrywanie bledow we wczytanych danych. ###\n\n[Przyklad 1]\n"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out G 7 8 2 1 1 B 4 5
	@echo "\nWYJAŚNIENIE: Zwrócony został Error, ponieważ użytkownik podał jako pierwszą zmienną G. Jest to zmienna insert mode, która przyjmuje wartości T (od Terminal) i F (od File).\n"
	@echo "\n[Przyklad 2]\n"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out T 0 1 -1 -4 -3 A 4 5 6
	@echo "\nWYJAŚNENIE: Zwrócony został Error, ponieważ użytkownik podał:\n"
	@echo " - jako pierwszą zmienną 0, która przyjmuje wartości <2, 1000> (Ilość rzędów).\n"
	@echo " - jako drugą zmienną 1, która przyjmuje wartości <2, 1000> (Ilość kolumn).\n"
	@echo " - jako trzecią zmienną -1, która przyjmuje wartości {1, 2, 3} (tryb uruchomienia).\n"
	@echo " - jako czwartą zmienną -4, która przyjmuje wartości >\= 0 (pierwsza granica wag).\n"
	@echo " - jako piątą zmienną -3, która przyjmuje wartości >\= (druga granica wag).\n"
	@echo " - jako szóstą zmienną A, która przyjmuje wartości {B, E} (tryb wyświetlania).\n"
	@echo " - jako siódmą zmienną 4, która przyjmuje wartości <0, n>, gdzie n to liczba_rzędów * liczba_kolumn -1 (wierzchołek początkowy) -> w tym przypadku byłoby to od <0, 0>.\n"
	@echo " - jako ósmą zmienną 5, która przyjmuje wartości <0, n>, gdzie n to liczba_rzędów * liczba_kolumn -1 (wierzchołek końcowy) -> w tym przypadku byłoby to od <0, 0>.\n"
	@echo " - jako dziewiątą zmienną 6, która analogicznie ma złą wartość, jest wierzchołkiem początkowym bez podanego końcowego -> ERROR: incorrect data - the number of vertices must be an even number.\n"

	@echo "[Przyklad poprawnie wprowadzonych danych]"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out T 7 8 2 1 1 B 4 5

test2:
	clear
	@echo "### Wykrywanie bledow w podanym pliku do wczytania. ###\n"
	@echo "[Przyklad 1]\n"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out F Files/file_test1 B 1 2
	@echo "\nPlik file_test1 został odrzucony ze względu na błędny format.\n"
	@echo "Błąd: inijka 1, słowo \"example\" powinno być liczbą z przedziału <2, 1000>.\n"

	@echo "\n[Przyklad 2]\n"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out F Files/file_test2 B 1 2
	@echo "\nPlik file_test2 został odrzucony ze względu na błędny format.\n"
	@echo "Błąd: dwie pierwsze liczby to 2 i 2, więc rozmiar wierzchołków powinno być 4. Natomiast wartości są podane dla 16 wierzchołków czego wynikiem jest error.\n"

	@echo "\n[Przyklad 3]\n"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out F Files/file_test_no_file B 1 2
	@echo "\nPlik file_test_no_file został odrzucony ponieważ nie istnieje plik o takiej nazwie (w folderze z programem).\n"
	
	
	@echo "\n[Przyklad 4]\n"
	@echo "Sposób kompilacji programu oraz spowodowane przez to komunikaty:\n"
	-./a.out F Files/file_test3 B 1 2
	@echo "\nPlik file_test3 został zaakceptowany, ponieważ ma poprawny format. Jest to plik przykładowy zawierający dane z pliku mygraph.\n"

	@echo "# Wszystkie wykorzystane pliki testowe znajdują się w folederze \"Files\"."



help:
	@echo "### Makefile help info ###\n"
	@echo "\"make compile\" - kompiluje wszystkie pliki programu."
	@echo "\"make clean\" - usuwa wszystkie pliki o rozszerzeniu \".o\"."
	@echo "\"make test1\" - wykonuje test poprawnego sprawdzenia danych wejsciowych przez program."
	@echo "\"make test2\" - wykonuje test poprawnego sprawdzenia formatu pliku przez program."

