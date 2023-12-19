#include <stdio.h>
//#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include <string.h>

#define NUM 3 //N.B. da 5 in su dura minuti/ore
#define ROWS 3
#define COLS 3

// PROTOTIPI
void initMtx( int mtx[ ROWS ][ COLS ] );
void rowPerm( int mtx[ ROWS ][ COLS ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm );
void printMtx( int mtx[ ROWS ][ COLS ] );
void printMtxToFile( int mtx[ ROWS ][ COLS ], FILE *fPtr, int cont_Mtx, int cp );
int check(int mtx[ ROWS ][ COLS ]);
int check3(int mtx[ ROWS ][ COLS ]);
int check2(int mtx[ ROWS ][ COLS ]);
//int monocromatica(int mtx[ n ][ n ]);
void sumMtx(int matrix[][COLS], int* arrNumSum);

int main() {
    clock_t begin = clock();

    int mtx[ ROWS ][ COLS ]; // commento se voglio testare una matrice fissa
    FILE *logPtr;
    int arr[] = {0, 1, 2};
    int cont_Mtx = 0;
    int cp = 0; //computabile privatamente
    int mono = 0; //monocromatica - NON vietata
    int cont_cp = 0;
    int cont_non_cp = 0;
    int n;
    int arrNumSum[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    char filename[27];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename, "log-BB-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    if ( ( logPtr = fopen( filename, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    initMtx( mtx );

    fflush( logPtr ); // rilascia dati ancora scritti


    for ( int i = 0; i < pow(NUM, NUM); i++ ) {
        rowPerm( mtx, 0, i, arr, 3, 3 );
        for ( int j = 0; j < pow(NUM, NUM); j++ ) {
            rowPerm( mtx, 1, j, arr, 3, 3 );
            for ( int k = 0; k < pow(NUM, NUM); k++ ) {
                rowPerm( mtx, 2, k, arr, 3, 3 );
                cont_Mtx++;
                cp = check( mtx ); //controllo MATRICI
                sumMtx(mtx, arrNumSum);
                if (cp == 0) cont_non_cp++; //0 - NON CP
                else cont_cp++; //1 - CP

                printMtxToFile( mtx, logPtr, cont_Mtx, cp );
            }
        }
    }

    fflush( logPtr ); // rilascia dati ancora scritti
    fclose( logPtr );

    printf("TOT. MTX: %d | MAT AMMESSE CP: %d | MAT VIETATE NON_CP: %d\n", cont_Mtx, cont_cp, cont_non_cp);
    for(int z = 0; z <=18; z++) {
        printf("SOMMA PARI A %d: %d\n", z, arrNumSum[z]);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f", time_spent);

//    getchar();
    return 0;

} //end main

void initMtx( int mtx[ ROWS ][ COLS ] ) {

    int r, c;

    for ( r = 0; r < ROWS; r++ ) {
        for ( c = 0; c < COLS; c++ ) {
            mtx[ r ][ c ] = 0;
        }
    }

} // end initMtx

void rowPerm( int mtx[ ROWS ][ COLS ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm ) {
    for ( int i = 0; i < lenPerm; i++ ) {
        mtx[riga][i] = valori[numPerm % lenValori];
        numPerm = numPerm / lenValori;
    }
}

int check(int mtx[ ROWS ][ COLS ]) {
    if (check3(mtx) == 1) { //SE VIETATA TRUE - NON CP
        return 0; //SE VIETATA TRUE - NON CP
//    } else if (check2(mtx) == 1) {
//        return 0; //CP FALSE - NON CP
    } else { //SE VIETATA FALSE - CP
        return 1; //CP TRUE
    }
}

int check3(int mtx[ ROWS ][ COLS ]) {

    int equivR = 0;
    int equivC = 0;

    //check row
    for(int i = 0; i <= 2; i++) {
        if(mtx[0][i] == mtx[1][i]) {
            for(int j = 0; j <= 2; j++) {
                if(mtx[1][j] == mtx[2][j] || mtx[0][j] == mtx[2][j]) {
                    equivR = 1;
                }
            }
        } else if(mtx[1][i] == mtx[2][i]) {
            for(int k = 0; k <= 2; k++) {
                if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) {
                    equivR = 1;
                }
            }
        }
    } //end check row

    //check col
    if(equivR == 1) {
        for(int q = 0; q <= 2; q++) {
            if(mtx[q][0] == mtx[q][1]) {
                for(int w = 0; w <= 2; w++) {
                    if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                        equivC = 1;
                    }
                }
            } else if(mtx[q][1] == mtx[q][2]) {
                for(int e = 0; e <= 2; e++) {
                    if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                        equivC = 1;
                    }
                }
            }
        }
    } //end check col

    if(equivR == 1 && equivC == 1) {
        return 1; //VIETATA TRUE - NON CP

    }

    return 0; //VIETATA FALSE - CP

}

int check2(int mtx[ ROWS ][ COLS ]) {

    int equivR = 0;
    int equivC = 0;

    //IN ALTO A SX
    for(int i = 0; i <= 1; i++) {
        if(mtx[0][i] == mtx[1][i]) {
            for(int j = 0; j <= 1; j++) {
                if(mtx[j][0] == mtx[j][1]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END IN ALTO A SX

    //IN ALTO A DX
    for(int i = 1; i <= 2; i++) {
        if(mtx[0][i] == mtx[1][i]) {
            for(int j = 0; j <= 1; j++) {
                if(mtx[j][1] == mtx[j][2]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END IN ALTO A DX

    //IN BASSO A SX
    for(int i = 0; i <= 1; i++) {
        if(mtx[1][i] == mtx[2][i]) {
            for(int j = 1; j <= 2; j++) {
                if(mtx[j][0] == mtx[j][1]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END IN ALTO A SX

    //IN BASSO A DX
    for(int i = 1; i <= 2; i++) {
        if(mtx[1][i] == mtx[2][i]) {
            for(int j = 1; j <= 2; j++) {
                if(mtx[j][1] == mtx[j][2]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END IN BASSO A DX



    return 0; //VIETATA FALSE - CP
}

//int monocromatica(int mtx[ n ][ n ]) {
//    int n;
//    for(int i = 0; i < n; i++) {
//        for(int j = 0; j < n; j++) {
//            if( mtx[0][0] != mtx[i][j] ) {
//                return 0;
//            }
//        }
//    }
//    return -1;
//}

void printMtx( int mtx[ ROWS ][ COLS ]) {

    int r, c;

    printf("\n");
    printf("    ");

    for ( c = 0; c < COLS; c++ ) { // intestazione colonne
        printf("%3d", c);
    }

    printf("\n");
    printf("    ");

    for ( c = 0; c < ( COLS * 3 ); c++ ) {
        printf("-");
    }

    printf("\n");

    for ( r = 0; r < ROWS; r++ ) {
        printf("%2d |", r);

        for ( c = 0; c < COLS; c++ ) {
            if( mtx[ r ][ c ] == 0) {
                printf("  -");
                continue;
            }
            printf("%3d", mtx[ r ][ c ]); // stampo tutte le celle
        }
        printf("\n");
    }

    printf("\n");

} //end printMtx

void sumMtx(int matrix[][COLS], int* arrNumSum) {

    int sum = 0;

    for(int i = 0; i < NUM; i++){
        for(int j = 0; j < NUM; j++){
            sum += matrix[i][j];
        }
    }

    arrNumSum[sum]++;

}

void printMtxToFile( int mtx[ ROWS ][ COLS ], FILE *fPtr, int cont_Mtx, int cp ) {


    fprintf( fPtr, "*MTX N° %d***\n", cont_Mtx);
    if (cp == 0) {
        fprintf( fPtr, "AMMESSA - CP\n");
    } else {
        fprintf( fPtr, "VIETATA - NON CP\n");
    }

    int r, c;

    fprintf( fPtr, "\n" );
    fprintf( fPtr, "    " );

    for ( c = 0; c < COLS; c++ ) { // intestazione colonne
        fprintf( fPtr, "%3d", c );
    }

    fprintf( fPtr, "\n" );
    fprintf( fPtr, "    " );

    for ( c = 0; c < ( COLS * 3 ); c++ ) {
        fprintf( fPtr, "-" );
    }

    fprintf( fPtr, "\n" );

    for ( r = 0; r < ROWS; r++ ) {
        fprintf( fPtr, "%2d |", r );

        for ( c = 0; c < COLS; c++ ) {
            if( mtx[ r ][ c ] == 0 ) {
                fprintf( fPtr, "  0" );
                continue;
            }
            fprintf( fPtr, "%3d", mtx[ r ][ c ] ); // stampo tutte le celle in ordine
        }
        fprintf( fPtr, "\n" );
    }

    fprintf( fPtr, "\n" );

} //end printMtxToFile