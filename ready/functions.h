#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//sorry for all the polish comments and that the whole project is in polish but it is kinda it's vibe so I don't wanna change this
//hope you understand ;)
//I just decided that I'd clean it up and add to GitHub because, despite it isn't the best C project hah, it is pretty important to me
//and it was the beginning of my whole Computer Science future ;)
//...if there will be any IT future for me xD

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

#define MID 64/2 //one line size
#define MAX_SZYFR 5 //max encrypted notes amount

#define OPT 8 //przy zmianie ilości opcji trzeba dodać kolejną do tablicy option w menu(), header i w main dodać przedział dla choice
#define OPT1 "1. Utworz"
#define OPT2 "2. Wyswietl"
#define OPT3 "3. Usun"
#define OPT4 "4. Importuj"
#define OPT5 "5. Eksportuj"
#define OPT6 "6. Szyfruj"
#define OPT7 "7. Rozszyfruj"
#define OPT8 "8. Zakoncz"

#define MIN_D 100 + 1 //nie moze być mniejsze niz 2!!, the beginning size of every note created
#define MIN_I 10 //the beginning size of notes' array

/**
 * @brief Shows menu.
*/
void menu();

/**
 * @brief Loading animation ...as we all know - good app must take a very long time to load ^^
*/
void load();

/**
 * @brief Returns '\n' when user input is one sign >= first parameter and <= the second.
 * 
 * @param one the lowest value from ASCII table
 * @param two the highest value from ASCII table
*/
char choice( const char one, const char two );

/**
 * @brief Cleans buffer.
*/
void clean();

/**
 * @brief Returns true if user input is "Y"/"y" which ends the program
*/
bool finish();

/**
 * @brief A special function to create an animated text running from the right to the left side of the terminal <3 ...xD
*/
void rotate();

bool utworz( const int, const int, char ** );

bool wyswietl( const int, const int, char ** );

bool edytuj( const int, const int, char ** );

bool usun(const int, const int, char **, int *, int *, int * );

bool importuj( const int, const int, char **, int *, int * );

bool eksportuj( const int, const int, char ** );

bool szyfruj(const int, const int, char **, int * );

bool rozszyfruj(const int, const int, char **, int * );

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

/**
 * @brief Returns random int value.
 * 
 * @param min the lowest int number
 * @param max the highest int number
*/
int i_rand( int min, int max );

#endif