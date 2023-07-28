#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define FLOWERS "                    _                     \n                  _(_)_                          wWWWw   _\n      @@@@       (_)@(_)   vVVVv     _     @@@@  (___) _(_)_\n     @@()@@ wWWWw  (_)\\    (___)   _(_)_  @@()@@   Y  (_)@(_)\n      @@@@  (___)     `|/    Y    (_)@(_)  @@@@   \\|/   (_)\\\n       /      Y       \\|    \\|/    /(_)    \\|      |/      |\n    \\ |     \\ |/       | / \\ | /  \\|/       |/    \\|      \\|/\n    \\\\|//   \\\\|///  \\\\\\|//\\\\\\|/// \\|///  \\\\\\|//  \\\\|//  \\\\\\|//\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
#define TITLE "NOTATNICZEK <3"
#define LINE "****************************************************************"
#define MID 64/2
#define MAX_SZYFR 5

#define OPT 8 //przy zmianie ilości opcji trzeba dodać kolejną do tablicy option w menu(), header i w main dodać przedział dla choice
#define OPT1 "1. Utworz"
#define OPT2 "2. Wyswietl"
#define OPT3 "3. Usun"
#define OPT4 "4. Importuj"
#define OPT5 "5. Eksportuj"
#define OPT6 "6. Szyfruj"
#define OPT7 "7. Rozszyfruj"
#define OPT8 "8. Zakoncz"

#define MIN_D 100 + 1 //nie moze być mniejsze niz 2!!
#define MIN_I 10

void menu();
void load();
char choice( const char one, const char two );
void clean();
bool utworz( const int, const int, char ** );
bool wyswietl( const int, const int, char ** );
bool edytuj( const int, const int, char ** );
bool usun(const int, const int, char **, int *, int *, int * );
bool importuj( const int, const int, char **, int *, int * );
bool eksportuj( const int, const int, char ** );
bool szyfruj(const int, const int, char **, int * );
bool rozszyfruj(const int, const int, char **, int * );
bool finish();
void rotate();
void header( const int );
char **alloc_w( const int );
char *alloc_n( const int );
char *realloc_n( const int, const int, char * );
char **realloc_w( const int, const int , char ** );
void alpha_sort( const int, char ** );
void date_sort( const int, const int, char ** );
int cmps( const void *, const void * );
int choice_n( const int, const char * );
int kropki( char **, const int );
int i_rand(int, int );

#endif