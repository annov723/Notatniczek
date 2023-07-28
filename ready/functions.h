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

#define MIN_D 100 + 1 //nie moze byc mniejsze niz 2!!, the beginning size of every note created
#define MIN_I 10 //the beginning size of notes' array

/**
 * @brief shows menu
*/
void menu();

/**
 * @brief loading animation ...as we all know - good app must take a very long time to load ^^
*/
void load();

/**
 * @brief returns '\n' when user input is one sign >= first parameter and <= the second
 * 
 * @param one the lowest value from ASCII table
 * @param two the highest value from ASCII table
*/
char choice( const char one, const char two );

/**
 * @brief cleans buffer
*/
void clean();

/**
 * @brief returns true if user input is "Y"/"y" which ends the program
*/
bool finish();

/**
 * @brief a special function to create an animated text running from the right to the left side of the terminal <3 ...xD
*/
void rotate();

/**
 * @brief depending on the int given, the header for different options shows up
 * 
 * @param num number of chosen option
*/
void header( const int num );

/**
 * @brief allocates an array for n pointers to the notes and returns ppointer to this array
 * 
 * @param n how much pointers to new notes should be created
*/
char **alloc_w( const int n );

/**
 * @brief allocates an array for a note and returns a pointer to this array
 * 
 * @param n size of char type array
*/
char *alloc_n( const int n );

/**
 * @brief reallocates an array for n pointers to the notes and returns a pointer to this array
 * 
 * @param stare size of pointers to char type pointers array at the beginning
 * @param nowe number of pointers to add
 * @param ptr pointer to the array
*/
char **realloc_w( const int stare, const int nowe, char **ptr );

/**
 * @brief reallocates an array for a note and returns a pointer to this array
 * 
 * @param stare size of char type array at the beginning
 * @param nowe number of chars to add
 * @param ptr pointer to the array
*/
char *realloc_n( const int stare, const int nowe, char *ptr );

/**
 * @brief creates a new note and returns true if everything went well
 * 
 * @param cc number of chosen option
 * @param num place in array of pointers to arrays of chars (a "big" array) where the new note wil be placed
 * @param tab_p pointer to "big" array
*/
bool utworz( const int cc, const int num, char **tab_p );

/**
 * @brief shows a list of all notes and the one that user'd choose will be displayed and returns true if everything went well
 * there are 3 options of show notes - in alphabetical order, from the latest or form the oldest
 * 
 * @param cc number of chosen option
 * @param num how many notes do we have
 * @param tab_p pointer to "big" array 
*/
bool wyswietl( const int cc, const int num, char **tab_p );

/**
 * @brief sorts notes in cmps function's alphabumeric order and display all the notes
 * 
 * @param num how many notes do we have
 * @param tab_p pointer to "big" array
*/
void alpha_sort( const int num, char **tab_p );

/**
 * @brief returns user input when it belongs to the range
 * 
 * @param num how many notes do we have
 * @param string information on stdout to inform user what they should write
*/
int choice_n( const int num, const char *string );

/**
 * @brief returns integer like a strcmp, sorts by numbers -> letters, ignoring case -> other signs
 * 
 * @param a pointer to the first note
 * @param b pointer to the second note
*/
int cmps( const void *a, const void *b );

/**
 * @brief print all the notes from the latest
 * 
 * @param num how many notes do we have
 * @param tab_p pointer to "big" array
*/
void fast_print( int num, char **tab_p );

/**
 * @brief returns 0 if a note if empty, other way returns number of signs to print
 * 
 * @param tab_p pointer to "big" array
 * @param i the number of note to check
*/
int kropki( char **tab_p, const int i );

/**
 * @brief prints all notes in date order, from latest or from the oldest
 * 
 * @param n which sorting option user's chosen - 1 from latest, 2 from oldest note
 * @param num how many notes do we have
 * @param tab_p pointer to "big" array
*/
void date_sort( const int n, const int num, char **tab_p);

/**
 * @brief deletes a chosen note, returns true if everything went good
 * 
 * @param cc number of chosen option
 * @param num how many notes do we have
 * @param tab_p pointer to the "big" array
 * @param new_max pointer to number of available space for new notes (if we dalete 10th note, the "big" array is reallocated to the smaller one)
 * @param szyfr pointer to an array of numbers of encrypted notes, if a chosen note is encrypted, the data from the array will be deleted too
 * @param szy pointer to number of encrypted notes, should be decreased if chosen note is encrypted
*/
bool usun( const int cc, const int num, char **tab_p, int *new_max, int *szyfr, int *szy );

/**
 * @brief export chosen note (user input file path), returns true if everything went well
 * 
 * @param cc number of chosen option
 * @param num how many notes do we have
 * @param tab_p pointer to the "big" array
*/
bool eksportuj( const int cc, const int num, char **tab_p );

/**
 * @brief imports a note chosen by user and returns true if everything went well
 * 
 * @param cc number of chosen option
 * @param num how many notes do we have
 * @param tab_p pointer to the "big" array
 * @param szyfr pointer to an array of numbers of encrypted notes, if imported note is encrypted it's number should be add to this array
 * @param szy pointer to an integer counting encrypted notes
*/
bool importuj( const int cc, const int num, char **tab_p, int *szyfr, int *szy );

/**
 * @brief encrypts a chosen note and returns true if everything went well
 * 
 * @param cc number of chosen option
 * @param num how many notes do we have
 * @param tab_p pointer to the "big" array
 * @param szyfr pointer to an array of numbers of encrypted notes
*/
bool szyfruj( const int cc, const int num, char **tab_p, int *szyfr );

/**
 * @brief decrypts a note and returns true if everything went well
 * 
 * @param cc number of chosen option
 * @param num how many notes do we have
 * @param tab_p pointer to the "big" array
 * @param szyfr pointer to an array of numbers of encrypted notes
*/
bool rozszyfruj( const int cc, const int num, char **tab_p, int *szyfr );

/**
 * @brief Returns random int value.
 * 
 * @param min the lowest int number
 * @param max the highest int number
*/
int i_rand( int min, int max );

#endif