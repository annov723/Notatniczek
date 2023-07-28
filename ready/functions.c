#include "functions.h"

void menu(){
    puts( FLOWERS );
    printf( "\n%*s\n", MID + (int)( strlen( TITLE ) / 2 ), TITLE );
    
    char *option[] = { OPT1, OPT2, OPT3, OPT4, OPT5, OPT6, OPT7, OPT8 };
    for( int i = 0; i < OPT; i++ ){
        printf( "        %-30s", *( option + i ) );
        if( ( i + 1 ) % 2 == 0 )
            printf( "\n" );
    }
    printf( "\n\n" );
}

void load(){
        printf( "\n\n%*s", MID + (int)( strlen( "LOADING..." ) / 2 ), "LOADING" );
        fflush(stdout);
        for( int i = 0; i < 5; i++ ){
            printf ( "." );
            fflush(stdout);
            usleep( 1000000 / 2 );
            if( ( i + 1 ) % 3 == 0){
                printf( "\b\b\b" );
                printf( "   " );
                printf( "\b\b\b" );
                fflush(stdout);
                usleep( 1000000 / 2 );
            }
        }

    system( "clear" );
}

char choice( const char one, const char two ){
    char n;
    if( ( n = getchar() ) >= one && n <= two ){
        if( getchar() == '\n' )
            return n;
    }

    clean();
    return 0;
}

void clean(){
    while( getchar() != '\n' )
        continue;
}

bool finish(){
    char n;
    printf( "Czy na pewno chcesz wyjsc? Y/N\nPo zamknieciu programu wszystko zostanie niestety usuniete... jak na razie\n" );
    rotate();
    while( ( n = toupper( getchar() ) ) != 'N' && n != 'Y' ){
        clean();
        printf( "Czy na pewno chcesz wyjsc? Y/N\n" );
    }
    clean();
    puts( "\n" );

    if( n == 'Y' )
        return true;
    else
        return false;
}

void rotate(){
    char tab1[] = "Gotowi na wersje 2.0? Subskrybuj IG: NOTATNICZEK <3 zeby byc na biezaco :)\n";
    char tab2[ strlen( tab1 ) + 1 ];
    memset( tab2, ' ', sizeof( tab1 ) );
    *( tab2 + strlen( tab1 ) ) = '\0';
    
    for( int i = strlen( tab1 ) - 1; i >= 0; i-- ){ //dl 1 = 10, i = 9,
        strncpy( tab2+i, tab1, strlen( tab1 ) - i );
        printf( "%s", tab2 );
        fflush(stdout);
        usleep( 1000000 / 10 );
        printf( "\r" );
    }
}

void header( const int num ){
    char *option[] = { OPT1, OPT2, OPT3, OPT4, OPT5, OPT6, OPT7 };
    char k[( MID * 2 ) + 1] = { '\0' };
    int a = ( strlen( LINE ) / 2 ) - ( strlen( option[num - 1] ) / 2 ) - 1;
    strncpy( k, LINE, a );
    strcat( k, " " );
    strcat( k, option[num - 1] );
    strcat( k, " " );
    int b = ( MID * 2 ) - strlen( k );
    strncat( k, LINE, b);
    printf( "%s\n%s\n%s\n", LINE, k, LINE );

}

char **alloc_w( const int n ){
    char **ptr = calloc( n, sizeof( char * ) ); //ilosc notatek

    if( ptr != NULL )
        return ptr;
    else
        exit( EXIT_FAILURE );
}

char *alloc_n( const int n ){
    char *ptr = calloc( n, sizeof( char ) ); //wielkosc maksymalna jednej notatki
 
    if( ptr != NULL )
        return ptr;
    else
        exit( EXIT_FAILURE );
}

char **realloc_w( const int stare, const int nowe, char **ptr ){ //realokacja tablicy notatek
    ptr = realloc( ptr, ( stare + ( nowe ) ) * sizeof( char * ) ); //ilosc notatek

    if( ptr != NULL )
        return ptr;
    else
        exit( EXIT_FAILURE );
}

char *realloc_n( const int stare, const int nowe, char *ptr ){ //realokacja pojedynczej notatki
    ptr = realloc( ptr, ( stare + ( nowe ) ) * sizeof( char ) ); //powiekszamy rozmiar pojedynczej notatki, pojedyncze tablice notatek sa zapisane w innym miejscu w pamieci niz wielka tablica noatatek, wiec powiekszanie poszzegolnych noatatek nie powinno wplynac na wielka tablice notatek

    if( ptr != NULL )
        return ptr;
    else
        exit( EXIT_FAILURE );
}

bool utworz( const int cc, const int num, char **tab_p ){
    header( cc );
    bool ans = 0;
    int k = MIN_D; //ile znakow razem z zakonczeniem (1 znak) moze przyjac notatka
    *( tab_p + num ) = alloc_n( MIN_D );
    
    char c;
    int count = 0; //licznik wszystkich znakow
    int enter = 0; //licznik do przerzucania do nowej linii
    char *g = NULL; //zmienna pomocnicza potrzebna chwilowo do operowaniu na elementach tablicy

    printf("\nWprowadz notatke :)\nJedyne o czym musisz pamietac to zeby wpisac \"|\" i nacisnij\nENTER kiedy bedziesz chcial zakonczyc notatke, milego pisania!\n\n"  );

    while( ( c = getchar() ) != '|' ){
        *( *( tab_p + num ) + count ) = c;
        count++;
        enter++;

        *( *( tab_p + num ) + count ) = '\0'; //chwilowo zeby ulatwic sprawdzenie warunkow

        if( c == '\n' )
            enter = 0;
        
        if( c == '\t' ){ //tutaj musimy zalozyc, ze tab ma dlugosc 8 w terminalu (tyle ma jesli sprawdzimy echo $'\t' | wc -L), ale prawde jest taka, ze to jakos od czzapy wypisuje...
            for( int i = 0; i < 7; i++ ){
                if( enter == ( MID * 2 ) ){ //sprawdzamy czy nie trzeba przejsc do nowej linii
                    g = strrchr( *( tab_p + num ), ' ' ); //szukamy ostatniego wystapienia spacji
                    *g = '\n';
                    enter = strlen( g ) - 1;
                }
                enter = enter + 1;
            }
        }

        if( enter == ( MID * 2 ) ){ //sprawdzamy czy nie trzeba przejsc do nowej linii
            g = strrchr( *( tab_p + num ), ' ' ); //szukamy ostatniego wystapienia spacji
            *g = '\n';
            enter = strlen( g ) - 1;
        }
        //sprawdzamy czy nie trzeba realokowac tablicy, jesli dodawalismy '\n' to juz tego nie robimy bo tam tablica zostala realokowana
        if( ( count + 1 ) == k ){ //zawsze musi byc o 1 wiecej miejsca na wszelki wypadek (count + 1 to ilość miejsc, jedno miejsce dodaje nam inkrementacja count)
            *( tab_p + num ) = realloc_n( k, MIN_D - 1, *( tab_p + num ) ); //dodajemy kolejne 100 miejsc na znaki
            k = k + MIN_D - 1;
        }
    }

    clean();
    *( *( tab_p + num ) + count ) = '\0';
    *( tab_p + num ) = realloc_n( 0, count + 1, *( tab_p + num ) ); //zmniejszamy wielkosc notatki zeby pasowala
    g = NULL;
    ans = 1;
    return ans;
}

bool wyswietl( const int cc, const int num, char **tab_p ){
    header( cc );
    bool ans = 0;

    char c; //choice opcji

    printf("\nPosortowac liste alfabetycznie (1) czy w w kolejnosci utworzenia\nod najnowszej (2) czy od najstarszej (3) notatki? ");
    while( ( c = choice( 49, 51 ) ) == 0 )
        printf( "nie ma takiej opcji..." );

    switch( c ){
        case '1':
            alpha_sort( num, tab_p );
            break;
        case '2':
            date_sort( 0, num, tab_p );
            break;
        case '3':
            date_sort( 1, num, tab_p );
            break;
        default:
            return ans;
    }

    printf( "\n(nacisnij enter zeby wrocic do glownego menu)");
    getchar();
    clean();
    
    ans = 1;
    return ans;
}

void alpha_sort( const int num, char **tab_p ){

    char *tab_s[num];
    for( int i = 0; i < num; i++ )
        *( tab_s + i ) = *( tab_p + i );

    qsort( tab_s, num, sizeof( char * ), cmps );

    for( int i = 0; i < num; i++ ){
        int k = kropki( tab_s, i );
        if( k == 0 )
            printf( "%d. ...\n", i + 1 );
        else if( k == 10 )
            printf( "%d. %.10s...\n", i + 1, *( tab_s + i ) );
        else
            printf( "%d. %.*s...\n", i + 1, k,*( tab_s + i ) );
    }

    int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz otworzyc: " );
    system( "clear" );
    printf( "\n%s\n", *( tab_s + g - 1 ) );
}

int choice_n( const int num, const char *string ){
    int g;
    printf( "%s", string );
    while( scanf( "\n%d", &g ) != 1 || g < 1 || g > num ){
        printf( "nie ma takiej opcji...\n" );
        clean();
        printf( "%s", string );
    }
    return g;
}

//zeby kolejnosc sortowania byla cyfry -> litery bez wielkosci -> pozostale znaki - done
int cmps( const void *a, const void *b ){ //wrzucasz tam wskaźniki do pierwszych liter danych łańcuchów, czyli do strcmp wrzucamy już podane łańcuchy (*a), **a to litera
    const char *s1 = *( const char ** ) a;
    const char *s2 = *( const char ** ) b;

    int i = 0;
    while( true ){
        while( isdigit( *( s1 + i ) ) && isdigit( *( s2 + i ) ) ){
        int n = strncmp( s1 + i, s2 + i, 1 );
        if ( n != 0 ) return n;
        i++;
        }

        if( isdigit( *( s1 + i ) ) && *( s2 + i ) != '\0' ) return -1; //nie doszło do końca drugiego łańcucha, a do tej pory były identyczne i kolejny znak w 1 to cyfra
        else if( isdigit( *( s2 + i ) ) && *( s1 + i ) != '\0' ) return 1; //1 się nie skończył, a drugi ma cyfrę
        
        while( isalpha( *( s1 + i ) ) && isalpha ( *( s2 + i ) ) ){
            int n = ( int ) toupper( *( s1 + i ) ) - ( int ) toupper( *( s2 + i ) );
            if ( n != 0 ) return n;
            i++;
        }

        if( isalpha( *( s1 + i ) ) && *( s2 + i ) != '\0' && !isdigit( *( s2 + i ) ) ) return -1;
        else if( isalpha( *( s2 + i ) ) && *( s1 + i ) != '\0' && !isdigit( *( s1 + i ) ) ) return 1;
        
        while( !isalpha( *( s1 + i ) ) && !isalpha ( *( s2 + i ) ) && !isdigit( *( s1 + i ) ) && !isdigit( *( s2 + i ) ) && *( s1 + i ) != '\0' && *( s2 + i ) != '\0' ){
            int n = strncmp( s1 + i, s2 + i, 1 );
            if ( n != 0 ) return n;
            i++;
        }

        if( *( s1 + i ) == '\0' && *( s2 + i ) == '\0' ) return 0;
        else if( *( s1 + i ) == '\0' ) return -1;
        else if( *( s2 + i ) == '\0' ) return 1;
    }

    return 0;
}

//wypisywanie listy notatek na szybko do wszystkich funkcji - done
void fast_print( int num, char **tab_p ){ //*( tab_p + num - g ) to wybrana notatka
    for( int i = num - 1; i >= 0; i-- ){
        int k = kropki( tab_p, i );

        if( k == 0 )
            printf( "%d. ...\n", num - i );
        else if( k == 10 )
            printf( "%d. %.10s...\n", num - i, *( tab_p + i ) );
        else
            printf( "%d. %.*s...\n", num - 1, k,*( tab_p + i ) );
    }
}

int kropki( char **tab_p, const int i ){
    if( **( tab_p + i ) == '\0' ) //jeśli jest pusta notatka
        return 0;

    int j;
    for( j = 0; j < 10; j++ ){
            if( *( *( tab_p + i ) + j ) == '\n' || *( *( tab_p + i ) + j ) == '\t' ) //jeśli jest endline przed 10 to wypiszemy tylko do tego znaku
                return j;
    }

    return j; //jak j = 10 to znaczy, że można normalnie wypisać wszystko
}

void date_sort( const int n, const int num, char **tab_p ){
    if( n == 1 ){
        for( int i = 0; i < num; i++ ){
            int k = kropki( tab_p, i );

            if( k == 0 )
                printf( "%d. ...\n", i + 1 );
            else if( k == 10 )
                printf( "%d. %.10s...\n", i + 1, *( tab_p + i ) );
            else
                printf( "%d. %.*s...\n", i + 1, k,*( tab_p + i ) );
        }
        int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz otworzyc: " );
        system( "clear" );
        printf( "\n%s\n", *( tab_p + g - 1 ) );
    }
    else{
        for( int i = num - 1; i >= 0; i-- ){
            int k = kropki( tab_p, i );

            if( k == 0 )
                printf( "%d. ...\n", num - i );
            else if( k == 10 )
                printf( "%d. %.10s...\n", num - i, *( tab_p + i ) );
            else
                printf( "%d. %.*s...\n", num - 1, k,*( tab_p + i ) );
        }

        int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz otworzyc: " );
        system( "clear" );
        printf( "\n%s\n", *( tab_p + num - g ) );
    }
}

bool usun( const int cc, const int num, char **tab_p, int *new_max, int *szyfr, int *szy ){
    header( cc );
    bool ans = 0;
    fast_print( num, tab_p );
    int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz usunac: " );
    g = num - g;
    int chwila = g;

    if( *( tab_p + g ) != NULL ){ //czyścimy pointer do usuwanej notatki
        free( *( tab_p + g ) );
        *( tab_p + g ) = NULL;
    }

    for( ; g < ( num - 1 ); g++ )
        *( tab_p + g ) = *( tab_p + g + 1 ); //g = num - 1 czyli nowa ilosc notatek

    if( num !=  *new_max - ( MIN_I / 2 ) ){
        clean();
        ans = 1;
        return ans;
    }
    
    tab_p = realloc_w( *new_max, ( - MIN_I / 2 ), tab_p );
    *new_max = *new_max - ( MIN_I / 2 );

    clean();

    if( *szy > 0 ){
        for( int i = 0; i < MAX_SZYFR; i++ ){
            if ( szyfr[i] == chwila ){
                szyfr[i] = -1;
                *szy = *szy - 1;
            }
            if( szyfr[i] > g )
                szyfr[i] = szyfr[i] - 1;
        }
    }

    ans = 1;
    return ans;
}

bool eksportuj( const int cc, const int num, char **tab_p ){
    header( cc );
    bool ans = 0;
    fast_print( num, tab_p );
    int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz wyeksportowac: " );
    g = num - g;

    clean();
    char *sciezka = alloc_n( ( ( MIN_D * 5 ) - 4 ) );
    int x = 0;
    char ch;
    printf( "\nPodaj sciezke do utworzenia nowego pliku: " );
    while( ( ch = getchar() ) != '\n' ){
        *( sciezka + x ) = ch;
        x++;
    }
    *( sciezka + x ) = '\0';

    FILE *ftp;
    if( ( ftp = fopen( sciezka, "w" ) ) == NULL ) return ans;
    fprintf( ftp, "%s", *( tab_p + g ) );
    if( fclose( ftp ) != 0 ) return ans;

    system( "clear" );
    printf( "Zawartosc wyeksportowanego pliku %s:\n", sciezka );
    if( ( ftp = fopen( sciezka, "r" ) ) == NULL ) return ans;

    while(  ( ch = fgetc( ftp ) ) != '\0' && !feof( ftp ) ) //!feof( ftp ) zwraca prawdę jeśli wskazywany jest koniec pliku
        printf( "%c", ch );

    printf( "\n\n(nacisnij enter zeby wrocic do glownego menu)");
    getchar();

    if( fclose( ftp ) != 0 ) return ans;
    if( sciezka != NULL ){
        free( sciezka );
        sciezka = NULL;
    }

    ans = 1;
    return ans;
}

//zrobić importuj - done
bool importuj( const int cc, const int num, char **tab_p, int *szyfr, int *szy ){
    header( cc );
    bool ans = 0;
    int k = MIN_D; //ile znakow razem z zakonczeniem (1 znak) moze przyjac notatka

    char n;
    printf( "Czy notatka importowana jest zaszyfrowana (Y/N)? " );
    while( ( n = toupper( getchar() ) ) != 'N' && n != 'Y' ){
        clean();
        printf( "Czy jest to notatka zaszyfrowana (Y/N)?" );
    }
    clean();

    if( n == 'Y' ){
        if( *szy >= MAX_SZYFR ){
            system( "Osiagnieto maksymalna ilosc zaszyfrowanych notatek :(((\n" );
            return 1;
        }
        *szy = *szy + 1;
        for( int i = 0; i < MAX_SZYFR; i++ ){ //ustawiamy na pustej pozycji 
            if( szyfr[i] == -1 ){
                szyfr[i] = num;
                break;
            }
        }
    }

    *( tab_p + num ) = alloc_n( MIN_D );

    char *sciezka = alloc_n( ( ( MIN_D * 5 ) - 4 ) );
    int x = 0;
    char c;
    printf( "\nPodaj nazwe notatki, ktora chcesz zaimportowac: " );
    while( ( c = getchar() ) != '\n' ){
        *( sciezka + x ) = c;
        x++;
    }
    *( sciezka + x ) = '\0';

    FILE *ftp;
    if( ( ftp = fopen( sciezka, "r" ) ) == NULL ) return ans;

    int count = 0; //licznik wszystkich znakow
    int enter = 0; //licznik do przerzucania do nowej linii
    char *g = NULL; //zmienna pomocnicza potrzebna chwilowo do operowaniu na elementach tablicy
    while( ( c = getc( ftp ) ) != EOF ){
        *( *( tab_p + num ) + count ) = c;
        count++;
        enter++;

        *( *( tab_p + num ) + count ) = '\0'; //chwilowo zeby ulatwic sprawdzenie warunkow

        if( c == '\n' )
            enter = 0;

        if( c == '\t' ){ //tutaj musimy zalozyc, ze tab ma dlugosc 8 w terminalu (tyle ma jesli sprawdzimy echo $'\t' | wc -L), ale prawde jest taka, ze to jakos od czzapy wypisuje...
            for( int i = 0; i < 7; i++ ){
                if( enter == ( MID * 2 ) ){ //sprawdzamy czy nie trzeba przejsc do nowej linii
                    g = strrchr( *( tab_p + num ), ' ' ); //szukamy ostatniego wystapienia spacji
                    *g = '\n';
                    enter = strlen( g ) - 1;
                }
                enter = enter + 1;
            }
        }

        if( enter == ( MID * 2 ) ){ //sprawdzamy czy nie trzeba przejsc do nowej linii
            g = strrchr( *( tab_p + num ), ' ' ); //szukamy ostatniego wystapienia spacji
            *g = '\n';
            enter = strlen( g ) - 1;
        }

        //sprawdzamy czy nie trzeba realokowac tablicy, jesli dodawalismy '\n' to juz tego nie robimy bo tam tablica zostala realokowana
        if( ( count + 1 ) == k ){ //zawsze musi byc o 1 wiecej miejsca na wszelki wypadek (count + 1 to ilość miejsc, jedno miejsce dodaje nam inkrementacja count)
            *( tab_p + num ) = realloc_n( k, MIN_D - 1, *( tab_p + num ) ); //dodajemy kolejne 100 miejsc na znaki
            k = k + MIN_D - 1;
        }
    }

    *( *( tab_p + num ) + count ) = '\0';
    *( tab_p + num ) = realloc_n( 0, count + 1, *( tab_p + num ) ); //zmniejszamy wielkosc notatki zeby pasowala

    if( fclose( ftp ) != 0 ) return ans;
    if( sciezka != NULL ){
        free( sciezka );
        sciezka = NULL;
    }

    ans = 1;
    return ans;
}

/*
zrobić szyfruj - user podaje 3-cyfrowy kod, który musi zapamiętać żeby móc odszyfrować notatkę, losowo wybieramy:
♥ cyfrę wskazującą na jeden z elementów kodu - too będzie co ile znaków zmieniamy znak (na koniec notatki dopisujemy tą cyfrę, ale dopiero na koniec programu)
♥ w pętli od 1 el do "co ile" zmieniamy znaki o ustaloną wielkość do góry
♥ losujemy jakąś cyfrę z kodu - mnożymy ją razy 10 i dodajemy do tej pierwszej -> o ile przesuwamy znaki 
*/
bool szyfruj( const int cc, const int num, char **tab_p, int *szyfr ){
    header( cc );
    fast_print( num, tab_p );
    int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz zaszyfrowac: " );
    g = num - g;
    for( int i = 0; i < MAX_SZYFR; i++ ){ //ustawiamy na pustej pozycji
        if( szyfr[i] == -1 ){
            szyfr[i] = g;
            break;
        }
    }

    clean();
    int tab[3];
    char c;
    int licznik = 0;
    printf( "\nPodaj 3-cyfrowy kod skadajacy się z cyfr 1-9 w celu pozniejszego rozszyfrowania notatki: ");
    while( 1 ){
        c = getchar();
        licznik++;
        if( licznik == 4 && c == '\n' )
            break;
        if( c > 48 && c < 58 && licznik < 4 )
            tab[licznik - 1] = atoi( &c );            
        else{
            printf( "wprowadzono bledny kod...\n" );
            clean();
            printf( "Podaj 3-cyfrowy kod skadajacy się z cyfr 1-9 w celu pozniejszego rozszyfrowania notatki: ");
            licznik = 0;
        }
    }
    
    srand( time( NULL ) );
    int coile = i_rand( 0, 2 ); //cyfra kodu, która określa co ile powtarzamy schemat
    int dl = strlen( *( tab_p + g ) ); //długość notatki
    if( dl < 10 ) //w tym przypadku przy odszyfrowywaniu pierwsze sprawdzamy ten warunek
        tab[coile] = dl;
    int dl2 = dl;

    int ile = dl / tab[coile]; //ile razy musimy dany schemat odtworzyć
    int mod = dl % tab[coile]; //czy jest jakaś reszta
    *( tab_p + g ) = realloc_n( ( dl + 1 ), ( tab[coile] + 1 ), *( tab_p + g ) );
    for( int i = 0; i < tab[coile]; i++ ){
        int k = i_rand( 0, 2 ); //jaka liczbę dodajemy do tej pierwszej wybranej, to dopisujemy na koniec notatki
        int up = tab[k] + tab[coile]; //o ile podnosimy do góry
        int max = ile; //ile razy w całości powtarzamy dany schemat
        if( mod > i )
            max++;

        for( int j = 0; j < max; j++ ){
            if( *( *( tab_p + g ) + i + ( j * tab[coile] ) ) != '\n' && *( *( tab_p + g ) + i + ( j * tab[coile] ) ) != '\t' )
                *( *( tab_p + g ) + i + ( j * tab[coile] ) ) = *( *( tab_p + g ) + i + ( j * tab[coile] ) ) + up;
        }
        *( *( tab_p + g ) + dl ) = k + 48; //0, 1 lub 2
        dl++;
    }

    if( dl2 < 10 ){ //musimy mieć obie wartości - długość i który el kodu został zmieniony
        *( *( tab_p + g ) + dl ) = tab[coile] + 48;
        dl++;
        *( *( tab_p + g ) + dl ) = coile + 48;
        dl++;
        *( *( tab_p + g ) + dl ) = '\0';
    }
    else{
        *( *( tab_p + g ) + dl ) = coile + 48;
        dl++;
        *( *( tab_p + g ) + dl ) = '\0';
    }

    return true;
}

bool rozszyfruj( const int cc, const int num, char **tab_p, int *szyfr ){
    header( cc );
    fast_print( num, tab_p );
    int g = choice_n( num, "\nPodaj numer notatki, ktora chcesz rozszyfrowac: " );
    g = num - g;
    clean();

    int prawdziwe = 0;
    for( int i = 0; i <MAX_SZYFR; i++ ){
        if( szyfr[i] == g )
            prawdziwe = 1;
    }
    if( prawdziwe == 0 )
        return 0;

    //usuwamy z tab szyfr tą notatkę
    for( int i = 0; i < MAX_SZYFR; i++ ){
        if( szyfr[i] == g ){
            szyfr[i] = -1;
            break;
        }
    }

    int tab[3];
    char c;
    int licznik = 0;
    printf( "\nPodaj kod: ");
    while( 1 ){
        c = getchar();
        licznik++;
        if( licznik == 4 && c == '\n' )
            break;
        if( c > 48 && c < 58 && licznik < 4 )
            tab[licznik - 1] = atoi( &c );            
        else{
            printf( "wprowadzono bledny kod...\n" );
            clean();
            printf( "Podaj kod: ");
            licznik = 0;
        }
    }

    srand( time( NULL ) );
    int dl = strlen( *( tab_p + g ) ); //długość notatki
    int coile = *( *( tab_p + g ) + dl - 1 ) - 48; //cyfra kodu, która określa co ile powtarzamy schemat
    int prop = *( *( tab_p + g ) + dl - 2 ) - 48;
    //sprawdzamy czy notatka nie jest krótsza niż 10
    int dl2;
    if( dl - prop - prop - 2 == 0 ){
        tab[coile] = prop;
        dl2 = dl - tab[coile] - 2;
    }
    else
        dl2 = dl - tab[coile] - 1;    

    int ile = dl2 / tab[coile]; //ile razy musimy dany schemat odtworzyć
    int mod = dl2 % tab[coile]; //czy jest jakaś reszta

    for( int i = tab[coile] - 1; i >= 0; i-- ){
        int k = *( *( tab_p + g ) + dl2 + i ) - 48; //jaka liczbę dodajemy do tej pierwszej wybranej, to dopisujemy na koniec notatki
        int up = tab[k] + tab[coile]; //o ile podnosimy do góry
        int max = ile; //ile razy w całości powtarzamy dany schemat
        if( mod > i )
            max++;
        
        for( int j = 0; j < max; j++ ){
            if( *( *( tab_p + g ) + i + ( j * tab[coile] ) ) != '\n' && *( *( tab_p + g ) + i + ( j * tab[coile] ) ) != '\t' )
                *( *( tab_p + g ) + i + ( j * tab[coile] ) ) = *( *( tab_p + g ) + i + ( j * tab[coile] ) ) - up;
        }
    }
    *( *( tab_p + g ) + dl2 ) = '\0';
    *( tab_p + g ) = realloc_n( 1, dl2, *( tab_p + g ) );
    
    return true;
}

int i_rand( int min, int max ){
    return rand() % ( max - min + 1 ) + min;
}


