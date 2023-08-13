#include "functions.h"

int main( void ){

    char c;
    int num = 0;
    int new_max = MIN_I;
    int szy = 0; //ilość zaszyfrowanych notatek
    int szyfr[MAX_SZYFR];
    for( int i = 0; i < MAX_SZYFR; i++ )
        szyfr[i] = -1;

    system( "clear" );

    load();
    menu();

    char **tab_p = alloc_w( new_max ); //robimy tablice wskaznikow dla 10 notatek (rozmiar minimalny)
    
    while( 1 ){
        printf( "(podaj numer zadania od 1 do %d ) ", OPT );
        while( ( c = choice( 49, 56 ) ) == 0 ){
            printf( "nie ma takiej opcji...\n" );
            printf( "(podaj numer zadania od 1 do %d ) ", OPT );
        }

        int cc = c - '0';
        switch( c ){
            case '1':
                system( "clear" );
                if( utworz( cc, num, tab_p ) ){
                    system( "clear" );
                    printf( "Notatka utworzona pomyslnie :)\n");
                    num = num + 1; //robi juz miejsce dla kolejnej notatki, num = ilosc notatek aktualnie
                    if( num >= new_max ){
                        tab_p = realloc_w( new_max, ( MIN_I / 2 ), tab_p );
                        new_max = new_max + ( MIN_I / 2 );
                    } //sprawdza czy nie trzeba powiekszyc tablicy wszystkich notatek
                }
                else{
                    system( "clear" );
                    printf( "Wystapil blad podczas zapisywania :(((\n" );
                }
                break;

            case '2':
                if( num < 1 ){
                    system( "clear" );
                    printf( "Brak notatek do wyswietlenia :(\n");
                    break;
                }
                system( "clear" );
                if( !wyswietl( cc, num, tab_p ) ){
                    system( "clear" );
                    printf( "Wystapil blad podczas wyswietlania :(((\n");
                }
                system( "clear" );
                break;

            case '3':
                if( num < 1 ){
                    system( "clear" );
                    printf( "Brak notatek do usuniecia :(\n");
                    break;
                }
                system( "clear" );
                if( usun( cc, num, tab_p, &new_max, szyfr, &szy ) ){
                    system( "clear" );
                    printf( "Notatka usunieta pomyslnie :)\n");
                    num = num - 1;
                }
                else{
                    system( "clear" );
                    printf( "Wystapil blad podczas usuwania :(((\n" );
                }
                break;

            case '4':
                system( "clear" );
                if( importuj( cc, num, tab_p, szyfr, &szy ) ){
                    system( "clear" );
                    printf( "Notatka zaimportowana pomyslnie :)\n" );
                    num = num + 1; //robi juz miejsce dla kolejnej notatki, num = ilosc notatek aktualnie
                    if( num >= new_max ){
                        tab_p = realloc_w( new_max, ( MIN_I / 2 ), tab_p );
                        new_max = new_max + ( MIN_I / 2 );
                    } //sprawdza czy nie trzeba powiekszyc tablicy wszystkich notatek
                }
                else{
                    system( "clear" );
                    printf( "Wystapil blad podczas importowania :(((\n" );
                }
                break;

            case '5':
                if( num < 1 ){
                    system( "clear" );
                    printf( "Brak notatek do wyeksportowania :(\n");
                    break;
                }
                system( "clear" );
                if( eksportuj( cc, num, tab_p ) ){
                    system( "clear" );
                    printf( "Notatka wyeksportowana pomyslnie :)\n" );
                }
                else{
                    system( "clear" );
                    printf( "Wystapil blad podczas eksportowania :(((\n" );
                }
                break;

            case '6':
                if( num < 1 ){
                    system( "clear" );
                    printf( "Brak notatek do zaszyfrowania :(\n" );
                    break;
                }
                system( "clear" );
                if( szy < MAX_SZYFR && szyfruj( cc, num, tab_p, szyfr ) ){
                    system( "clear" );
                    printf( "Notatka zaszyfrowana pomyslnie :)\n" );
                    szy = szy + 1;
                }
                else if( szy >= MAX_SZYFR ){
                    system( "clear" );
                    printf( "Osiagnieto maksymalna ilosc zaszyfrowanych notatek :(((\n" );
                }
                else{
                    system( "clear" );
                    printf( "Wystapil blad podczas szyfrowania :(((\n" );
                }
                break;

            case '7':
                if( num < 1 || szy < 1 ){
                    system( "clear" );
                    printf( "Brak notatek do rozszyfrowywania :(\n" );
                    break;
                }
                system( "clear" );
                if( szy > 0 && rozszyfruj( cc, num, tab_p, szyfr ) ){
                    system( "clear" );
                    printf( "Notatka rozszyfrowana pomyslnie :)\n" );
                    szy = szy - 1;
                }
                else{
                    system( "clear" );
                    printf( "Wystapil blad podczas rozszyfrowywania :(((\n" );
                }
                break;

            case '8':
                system( "clear" );
                if( finish() ){
                    system( "clear" );

                    for( int i = 0; i < num; i++ ){ //uwalniamy zaalokowana pamiec dla kazdej noatatki osobno, bo kazda notatka to zaalokowana tablica
                        if( *( tab_p + i ) != NULL ){
                            free( *( tab_p + i ) );
                            *( tab_p + i ) = NULL;
                        } 
                    }

                    if( tab_p != NULL ){ //uwalniamy wielka tablice notatek
                        free( tab_p );
                        tab_p = NULL;
                    }
                    
                    return 0;
                }
                system( "clear" );
                break;

            default:
                exit( EXIT_FAILURE );
        } 

        menu();
    }

    return 0;
}