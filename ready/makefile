notatniczek.exe: main.o functions.o
	gcc -o notatniczek.exe main.o functions.o
functions.o: functions.c functions.h
	gcc -c functions.c -Wall
main.o: main.c functions.h
	gcc -c main.c -Wall