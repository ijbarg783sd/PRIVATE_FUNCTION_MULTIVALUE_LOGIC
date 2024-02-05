#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 3 //processa 19683 matrici (tempo di esecuzione indicativo: meno di un secondo)


void initMtx( int mtx[ 2 ][ 3 ] );
void rowPerm( int mtx[ 2 ][ 3 ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm );
void printMtxToFile( int mtx[ 2 ][ 3 ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3 );


int checkMtx(int mtx[ 2 ][ 3 ]);
int checkMtx2x3(int mtx[ 2 ][ 3 ]);
int checkMtx2x2(int mtx[ 2 ][ 3 ]);
int checkMono2x3_1(int mtx[ 2 ][ 3 ]);

int setBit2(int mtx[ 2 ][ 3 ]);
int setBit3(int mtx[ 2 ][ 3 ], int bit1, int bit2);

int main() {
    clock_t begin = clock();

    const unsigned long lim = 123333335;
    unsigned long *arrSign = malloc(lim * sizeof(unsigned long));

    int mtx[ 2 ][ 3 ];
    int cont_Mtx = 0;
    int mtxType = 0;
    int countPos = 0;
    unsigned long sign = 0;
    int bit1 = -1;
    int bit2 = -1;
    int bit3 = -1;

    int arr[] = {0, 1, 2};

    FILE *logPtr1;
    char filename[50];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename, "1-tot-mat-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    if ( ( logPtr1 = fopen( filename, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    fflush( logPtr1 ); // rilascia dati ancora scritti

    initMtx( mtx );

    for ( int i = 0; i < pow(NUM, NUM); i++ ) {
//    for ( int i = 0; i < 10; i++ ) {
        rowPerm( mtx, 0, i, arr, 3, 3 );

        for ( int j = 0; j < pow(NUM, NUM); j++ ) {
//        for ( int j = 0; j < 1; j++ ) {
            rowPerm( mtx, 1, j, arr, 3, 3 );

            bit1 = mtx[0][0];

            bit2 = setBit2( mtx);
            bit3 = setBit3( mtx, bit1, bit2);

            countPos = -1;
            sign = 0;

            int t = 5;

            //costruisci signature per evitare mtx duplicate
            for ( int r = 0; r < 2; r++ ) {
                for ( int c = 0; c < 3; c++ ) {

                    countPos = countPos + 1;


                    if(mtx[ r ][ c ] == bit1) {

                        int exp = t;
                        unsigned long value = 1;
                        unsigned long base = 10;
                        while (exp!=0) {
                            value *= base;  /* value = value*base; */
                            --exp;
                        }

                        sign = sign + 1 * value;

                    } else if(mtx[ r ][ c ] == bit2) {

                        int exp = t;
                        unsigned long value = 1;
                        unsigned long base = 10;

                        while (exp!=0) {
                            value *= base;  /* value = value*base; */
                            --exp;
                        }

                        sign = sign + 2 * value;

                    } else if(mtx[ r ][ c ] == bit3) {

                        int exp = t;
                        unsigned long value = 1;
                        unsigned long base = 10;

                        while (exp!=0) {
                            value *= base;  /* value = value*base; */
                            --exp;
                        }

                        sign = sign + 3 * value;

                    }


                    t = t - 1;

                }
            }

            arrSign[sign]++;

            if(arrSign[sign] != 1) continue; //evito di andare oltre come tutte le iterazioni di mtx duplicate



            mtxType = checkMtx(mtx);

                if (mtxType != -1) {
                    cont_Mtx++;
                    printMtxToFile(mtx, logPtr1, cont_Mtx, mtxType, bit1, bit2, bit3);
                    printf("%d %d %d\n", mtx[0][0], mtx[0][1], mtx[0][2]);
                    printf("%d %d %d\n", mtx[1][0], mtx[1][1], mtx[1][2]);
                    printf("\n");
                }

        }
    }

    fflush( logPtr1 ); // rilascia dati ancora scritti
    fclose( logPtr1 );

    printf("\n\nMatrici totali: %d", cont_Mtx);

    free(arrSign); // don't forget this!

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nTime: %f", time_spent);

//    getchar();
    return 0;

} //end main

void initMtx( int mtx[ 2 ][ 3 ] ) {

    int r, c;

    for ( r = 0; r < 2; r++ ) {
        for ( c = 0; c < 3; c++ ) {
            mtx[ r ][ c ] = 0;
        }
    }

} //end initMtx

void rowPerm( int mtx[ 2 ][ 3 ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm ) {

    for ( int i = 0; i < lenPerm; i++ ) {
        mtx[riga][i] = valori[numPerm % lenValori];
        numPerm = numPerm / lenValori;
    }

} //end rowPerm

int checkMtx(int mtx[ 2 ][ 3 ]) {
    if (checkMtx2x2(mtx) == 1) {
        return 11; //VIETATA TRUE - NON CP
    }
    if (checkMtx2x3(mtx) == 1) {
        return 12; //VIETATA TRUE - NON CP
    }


    return 1; //CP TRUE - AMMESSA (NON VIETATA)

}

int checkMtx2x2(int mtx[ 2 ][ 3 ]) {

    int m[3][4] = {
            {0,1, 0, 1},
            {0,1, 0, 2},
            {0,1, 1, 2},
//            {0,2, 0, 1},
//            {0,2, 0, 2},
//            {0,2, 1, 2},
//            {1,2, 0, 1},
//            {1,2, 0, 2},
//            {1,2, 1, 2},
    };

    int count0 = 0;
    int count1 = 0;
    int count2 = 0;

//    printf("START\n");
    for(int i = 0; i <= 2; i++) {
//        printf("INIZIO, %d-\n", i);
        count0 = 0;
        count1 = 0;
        count2 = 0;

        for(int r = m[i][0]; r <= m[i][1]; r++) {

            for(int c = m[i][2]; c <= m[i][3]; c++) {

//                printf("%d | %d\n", r, c );

                switch (mtx[r][c]) {
                    case 0 :
                        count0++;
                        break;
                    case 1 :
                        count1++;
                        break;
                    case 2 : {
                        count2++;
                        break;
                    }
                    default :
                        printf("hai inserito una scelta non valida \n");
                        break;
                }

                if (c+1 < m[i][3]) c = m[i][3] - 1; //salta colonna centrale
            }
            if (r+1 < m[i][1]) r = m[i][1] - 1; //salta riga centrale
        }
//        printf("count0: %d | count1: %d | count2: %d\n", count0, count1, count2);
        if(count0 == 3 || count1 == 3 || count2 == 3) return 1;

    } //check 9 submatrix 2x2

    return 0; //VIETATA FALSE - CP
}

int checkMtx2x3(int mtx[ 2 ][ 3 ]) {

    //1a 2a RIGA | TUTTE COLONNE
    for(int i = 0; i <= 2; i++) {
        if(mtx[0][i] == mtx[1][i]) {
            for(int q = 0; q <= 1; q++) {
                if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                    for(int w = 0; w <= 1; w++) {
                        if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                            if(checkMono2x3_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                    for(int e = 0; e <= 1; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                            if(checkMono2x3_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int e = 0; e <= 1; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
                            if(checkMono2x3_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            }
        }
    } //END 1a 2a RIGA | TUTTE COLONNE

    return 0; //VIETATA FALSE - CP

}

int checkMono2x3_1(int mtx[ 2 ][ 3 ]) {

    //1a 2a RIGA
    for(int ro1 = 0; ro1 <= 1; ro1++) {
        for(int co1 = 0; co1 <= 2; co1++) {
            if(mtx[0][0] != mtx[ro1][co1]) {
                return 0; //no mono
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int setBit2(int mtx[ 2 ][ 3 ]) {

    for ( int r = 0; r < 2; r++ ) {
        for ( int c = 0; c < 3; c++ ) {
            if( mtx[0][0] != mtx[r][c] ) {
                return mtx[r][c];
            }
        }
    }

    return -1;

}

int setBit3(int mtx[ 2 ][ 3 ], int bit1, int bit2) {

    for ( int r = 0; r < 2; r++ ) {
        for ( int c = 0; c < 3; c++ ) {
            if( mtx[r][c] != bit1 && mtx[r][c] != bit2 ) {
                return mtx[r][c];
            }
        }
    }

    return -1;

}

void printMtxToFile( int mtx[ 2 ][ 3 ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3 ) {

    if (mtxType == 12) {
//    *countInterno = *countInterno + 1;

//    fprintf( fPtr, "%d%d%d\n", countRC3bit, countStraight, count1for2);
    fprintf( fPtr, "| N° %d\n", cont_Mtx );
    if (mtxType == 12) {
        fprintf( fPtr, "VIETATA 2x3 - NON CP\n");
    } else if (mtxType == 11) {
        fprintf( fPtr, "VIETATA 2x2 - NON CP\n");
    } else {
        fprintf( fPtr, "AMMESSA - CP\n");
    }

    int r, c;

    fprintf( fPtr, "\n" );
    fprintf( fPtr, "    " );

    for ( c = 0; c < 3; c++ ) { // intestazione colonne
        fprintf( fPtr, "%3d", c );
    }

    fprintf( fPtr, "\n" );
    fprintf( fPtr, "    " );

    for ( c = 0; c < ( NUM * 3 ); c++ ) {
        fprintf( fPtr, "-" );
    }

    fprintf( fPtr, "\n" );

    for ( r = 0; r < 2; r++ ) {
        fprintf( fPtr, "%2d |", r );

        for ( c = 0; c < 3; c++ ) {
//            fprintf( fPtr, "%3d", mtx[ r ][ c ] ); //stampa il bit reale

                if( mtx[ r ][ c ] == bit1) {
                    fprintf( fPtr, "%3c", 'A' );
//                    fprintf( fPtr, "%3c", '-' );
                } else if(mtx[ r ][ c ] == bit2) {
                    fprintf( fPtr, "%3c", 'B' );
                } else if(mtx[ r ][ c ] == bit3) {
                    fprintf( fPtr, "%3c", 'C' );
                }

        }
        fprintf( fPtr, "\n" );
    }

    fprintf( fPtr, "\n" );
    }
} //end printMtxToFile