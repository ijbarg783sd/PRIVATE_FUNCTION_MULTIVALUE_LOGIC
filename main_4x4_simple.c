#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 4 //N.B. da 5 in su dura minuti/ore

// PROTOTIPI
void initMtx( int mtx[ NUM ][ NUM ] );
void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[NUM], int lenValori, int lenPerm );
int checkMtx(int mtx[ NUM ][ NUM ]);
int checkMtx2x2(int mtx[ NUM ][ NUM ]);
void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, unsigned long long cont_Mtx, int cp, unsigned long long *countInterno );



int main() {
    clock_t begin = clock();


    int mtx[ NUM ][ NUM ];


    int arr[] = {0, 1, 2, 3}; //NUM = 4 bit
    unsigned long long cont_Mtx = 0;
    int cp = 0; //computabile privatamente
    unsigned long long cont_cp = 0;
    unsigned long long cont_non_cp = 0;
    unsigned long long countInterno = 0;

    FILE *logPtr_CP;
    char filename_CP[50];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename_CP, "1-CP-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    if ( ( logPtr_CP = fopen( filename_CP, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }





    //inizializza matrice tutta a zero
    initMtx( mtx );

    fflush( logPtr_CP ); // rilascia dati ancora scritti

    //begin CHECK MASSIVO
    for ( int i = 0; i < pow(NUM, NUM); i++ ) {
        rowPerm(mtx, 0, i, arr, NUM, NUM);
        for (int j = 0; j < pow(NUM, NUM); j++) {
            rowPerm(mtx, 1, j, arr, NUM, NUM);
            for (int k = 0; k < pow(NUM, NUM); k++) {
                rowPerm(mtx, 2, k, arr, NUM, NUM);
                for (int y = 0; y < pow(NUM, NUM); y++) {
                    rowPerm(mtx, 3, y, arr, NUM, NUM);

                    cont_Mtx++;

//                    if (cont_Mtx >= 100000000) { //limitare matrici da processare
//                        goto end;
//                    }

                    cp = checkMtx( mtx ); //controllo MATRICI

                    if (cp == 11) {

                        cont_non_cp++; //0 - NON CP - vietata o monocromatica

                    } else {

                        cont_cp++; //1 - CP - ammessa (perchè NON vietata)
                        printMtxToFile( mtx, logPtr_CP, cont_Mtx, cp, &countInterno );

                    }
                } //end riga 4
            } //end riga 3
        } //end riga 2
    }//end riga 1 - end CHECK MASSIVO

    fflush( logPtr_CP ); // rilascia dati ancora scritti
    fclose( logPtr_CP );


    end:

    printf("TOT. MTX: %llu\nMAT AMMESSE CP: %llu | MAT VIETATE: %llu\n",
           cont_Mtx, cont_cp, cont_non_cp);


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f", time_spent);

//    getchar();
    return 0;

} //end main










void initMtx( int mtx[ NUM ][ NUM ] ) {

    int r, c;

    for ( r = 0; r < NUM; r++ ) {
        for ( c = 0; c < NUM; c++ ) {
            mtx[ r ][ c ] = 0;
        }
    }

} // end initMtx

void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[NUM], int lenValori, int lenPerm ) {
    for ( int i = 0; i < lenPerm; i++ ) {
        mtx[riga][i] = valori[numPerm % lenValori];
        numPerm = numPerm / lenValori; // 4/4
    }
}

int checkMtx(int mtx[ NUM ][ NUM ]) {

    if (checkMtx2x2(mtx) == 1) {
        return 11; //VIETATA TRUE - NON CP
    } else {      //VIETATA FALSE - CP
        return 1; //CP TRUE - AMMESSA (NON VIETATA)
    }
}

int checkMtx2x2(int mtx[ NUM ][ NUM ]) {

    int m[36][4] = {
            {0, 1, 0, 1},{0, 1, 1, 2},{0, 1, 2, 3},{0, 1, 0, 2},{0, 1, 0, 3},{0, 1, 1, 3},
            {1, 2, 0, 1},{1, 2, 1, 2},{1, 2, 2, 3},{1, 2, 0, 2},{1, 2, 0, 3},{1, 2, 1, 3},
            {2, 3, 0, 1},{2, 3, 1, 2},{2, 3, 2, 3},{2, 3, 0, 2},{2, 3, 0, 3},{2, 3, 1, 3},
            {0, 2, 0, 1},{0, 2, 1, 2},{0, 2, 2, 3},{0, 2, 0, 2},{0, 2, 0, 3},{0, 2, 1, 3},
            {0, 3, 0, 1},{0, 3, 1, 2},{0, 3, 2, 3},{0, 3, 0, 2},{0, 3, 0, 3},{0, 3, 1, 3},
            {1, 3, 0, 1},{1, 3, 1, 2},{1, 3, 2, 3},{1, 3, 0, 2},{1, 3, 0, 3},{1, 3, 1, 3},

    };

    int count0;
    int count1;
    int count2;
    int count3;

//    printf("START\n");
    for(int i = 0; i <= 35; i++) {
//        printf("INIZIO, %d-\n", i);
        count0 = 0;
        count1 = 0;
        count2 = 0;
        count3 = 0;

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
                    case 3 : {
                        count3++;
                        break;
                    }
                    default :
                        printf("hai inserito una scelta non valida \n");
                        break;
                }

                if (c+1 < m[i][3]) c = m[i][3] - 1;
            }
            if (r+1 < m[i][1]) r = m[i][1] - 1;
        }
//        printf("count0: %d | count1: %d | count2: %d\n", count0, count1, count2);
        if(count0 == 3 || count1 == 3 || count2 == 3 || count3 == 3) return 1;

    } //check 9 submatrix 2x2

    return 0; //VIETATA FALSE - CP
}

void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, unsigned long long cont_Mtx, int cp, unsigned long long* countInterno ) {

    *countInterno = *countInterno + 1;

    fprintf( fPtr, "%llu | N° %llu***\n", *countInterno, cont_Mtx);
    if (cp == 11) {
        fprintf( fPtr, "VIETATA - NON CP\n");
    } else {
        fprintf( fPtr, "AMMESSA - CP\n");
    }

    int r, c;

    fprintf( fPtr, "\n" );
    fprintf( fPtr, "    " );

    for ( c = 0; c < NUM; c++ ) { // intestazione colonne
        fprintf( fPtr, "%3d", c );
    }

    fprintf( fPtr, "\n" );
    fprintf( fPtr, "    " );

    for ( c = 0; c < ( NUM * 3 ); c++ ) {
        fprintf( fPtr, "-" );
    }

    fprintf( fPtr, "\n" );

    for ( r = 0; r < NUM; r++ ) {
        fprintf( fPtr, "%2d |", r );

        for ( c = 0; c < NUM; c++ ) {
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