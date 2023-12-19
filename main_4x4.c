#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 4 //N.B. da 5 in su dura minuti/ore

// PROTOTIPI
void initMtx( int mtx[ NUM ][ NUM ] );
void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[NUM], int lenValori, int lenPerm );
void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, unsigned long long cont_Mtx, int cp, unsigned long long *countInterno );
int checkMtx(int mtx[ NUM ][ NUM ]);
int checkMtx2x2(int mtx[ NUM ][ NUM ]);
int sumMtx(int matrix[][NUM], int* arrNumSum, int* arrNumCount, int* arrHowMany012, int *arrDistribution);
int concat(int x, int y, int z);

int setBit2(int mtx[ NUM ][ NUM ]);
int setBit3(int mtx[ NUM ][ NUM ], int bit1, int bit2);
int setBit4(int mtx[ NUM ][ NUM ], int bit1, int bit2, int bit3);
int checkMtxMono4x4(int mtx[ NUM ][ NUM ]);

int main() {
    clock_t begin = clock();

    const unsigned long long lim = 1233333333333335;
                                                     //1000000000000000
//    const unsigned long long lim = 1233;
    unsigned long long *arrSign = malloc(lim * sizeof(unsigned long long));

    int mtx[ NUM ][ NUM ];

    FILE *logPtr1, *logPtr2, *logPtr3, *logPtr4, *logPtr5;
    int arr[] = {0, 1, 2, 3}; //NUM = 4 bit
    unsigned long long cont_Mtx = 0;
    unsigned long long countFiltro = 0;
    int cp = 0; //computabile privatamente
    unsigned long long cont_cp = 0;
    unsigned long long cont_cp_mono_3x3 = 0;
    unsigned long long cont_cp_mono_2x2 = 0;
    unsigned long long cont_cp_NON_vietate = 0;
    unsigned long long cont_non_cp = 0;
    unsigned long long countInterno = 0;
    unsigned long long countInterno2 = 0;
    int n;
    int arrNumSum[50] = {0};
    int arrHowMany012[3] = {0};
    int arrDistribution[999] = {0};

    int bit1 = -1;
    int bit2 = -1;
    int bit3 = -1;
    int bit4 = -1;
    unsigned long long sign = 0;
    int countPos = 0;

    char filename1[50], filename2[50], filename3[50], filename4[50], filename5[50];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename1, "1-tot-mat-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename2, "2-vietate-NCP-%04d%02d%02d-%02d%02d%02d.txt",
         tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
         tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename3, "3-ammesse-non-vietate-CP-%04d%02d%02d-%02d%02d%02d.txt",
         tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
         tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

      sprintf( filename4, "4-ammesse-mono-3x3-CP-%04d%02d%02d-%02d%02d%02d.txt",
         tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
         tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

      sprintf( filename5, "5-ammesse-mono-2x2-CP-%04d%02d%02d-%02d%02d%02d.txt",
         tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
         tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    if ( ( logPtr1 = fopen( filename1, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr2 = fopen( filename2, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr3 = fopen( filename3, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr4 = fopen( filename4, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr5 = fopen( filename5, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    //inizializza matrice tutta a zero
    initMtx( mtx );

    fflush( logPtr1 ); // rilascia dati ancora scritti
    fflush( logPtr2 ); // rilascia dati ancora scritti
    fflush( logPtr3 ); // rilascia dati ancora scritti
    fflush( logPtr4 ); // rilascia dati ancora scritti
    fflush( logPtr5 ); // rilascia dati ancora scritti

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

                    //stampa TUTTE LE MATRICI
//                    printMtxToFile( mtx, logPtr1, cont_Mtx, cp, &countInterno2 );

                    if (cont_Mtx >= 10) { //limitare matrici da processare
                        goto end;
                    }

//                    if (cont_Mtx % 500000000 == 0) {
//                        printf(">>> %llu", cont_Mtx);
//                    }


                    bit1 = mtx[0][0];
                    bit2 = setBit2( mtx);
                    bit3 = setBit3( mtx, bit1, bit2);
                    bit4 = setBit4( mtx, bit1, bit2, bit3);
                    sign = 0;
                    countPos = -1;

                    if(checkMtxMono4x4(mtx) == 1) continue; //salta 3 monocromatiche


                    int t = 15;


                    //costruisci signature per evitare mtx duplicate
                    for ( int r = 0; r < NUM; r++ ) {
                        for ( int c = 0; c < NUM; c++ ) {

                            countPos = countPos + 1;


                            if(mtx[ r ][ c ] == bit1) {

                                int exp = t;
                                unsigned long long value = 1;
                                unsigned long long base = 10;
                                while (exp!=0) {
                                    value *= base;  /* value = value*base; */
                                    --exp;
                                }

                                sign = sign + 1 * value;

                            } else if(mtx[ r ][ c ] == bit2) {

                                int exp = t;
                                unsigned long long value = 1;
                                unsigned long long base = 10;

                                while (exp!=0) {
                                    value *= base;  /* value = value*base; */
                                    --exp;
                                }

                                sign = sign + 2 * value;

                            } else if(mtx[ r ][ c ] == bit3) {

                                int exp = t;
                                unsigned long long value = 1;
                                unsigned long long base = 10;

                                while (exp!=0) {
                                    value *= base;  /* value = value*base; */
                                    --exp;
                                }

                                sign = sign + 3 * value;

                            } else if(mtx[ r ][ c ] == bit4) {

                                int exp = t;
                                unsigned long long value = 1;
                                unsigned long long base = 10;

                                while (exp!=0) {
                                    value *= base;  /* value = value*base; */
                                    --exp;
                                }

                                sign = sign + 4 * value;

                            }


                            t = t - 1;

                        }
                    }






                    // CHECK SIGNATURE
//                    printf("%llu | %llu | %llu\n", cont_Mtx, sign, arrSign[sign]);

                    arrSign[sign-1000000000000000]++;

                    if(arrSign[sign-1000000000000000] != 1) continue; //evito di andare oltre come tutte le iterazioni di mtx duplicate

                    countFiltro++;



                    cp = checkMtx( mtx ); //controllo MATRICI
                    int arrNumCount[] = {0,0,0,0};
    //                sumMtx(mtx, arrNumSum, arrNumCount, arrHowMany012, arrDistribution); //spostare in uno dei rami if seguenti per indagare le singole tipologie
                    if (cp == 0) {
//                        sumMtx(mtx, arrNumSum, arrNumCount, arrHowMany012, arrDistribution); //spostare in uno dei rami if seguenti per indagare le singole tipologie


                        cont_non_cp++; //0 - NON CP - vietata o monocromatica

//                        if(arrHowMany012[0] == 2 && arrHowMany012[1] == 3 && arrHowMany012[2] == 4) {
//                            printMtxToFile( mtx, logPtr2, cont_Mtx, cp, &countInterno2 );
//                        }
                    } else if (cp == 2) { //MONOCROMATICA 3x3 4x4

                        cont_cp++;
                        cont_cp_mono_3x3++;
    //                    printMtxToFile( mtx, logPtr4, cont_Mtx, cp, &countInterno2 );
                    } else if (cp == 3) { //MONOCROMATICA 2x2

                        cont_cp++;
                        cont_cp_mono_2x2++;
    //                    printMtxToFile( mtx, logPtr5, cont_Mtx, cp, &countInterno2 );
                    } else {

                        cont_cp_NON_vietate++;
                        cont_cp++; //1 - CP - ammessa (perchè NON vietata)

    //                        if(sumMtx(mtx, arrNumSum) == 15) {
    //                            printMtxToFile( mtx, logPtr3, cont_Mtx, cp );
    //
    //                        }

//                            if(arrHowMany012[0] == 3 && arrHowMany012[1] == 3 && arrHowMany012[2] == 3) {
//                                printMtxToFile( mtx, logPtr3, cont_Mtx, cp, &countInterno );
//                            }



                    }
                } //end riga 4
            } //end riga 3
        } //end riga 2
    }//end riga 1 - end CHECK MASSIVO


    end:
    fflush( logPtr1 ); // rilascia dati ancora scritti
    fclose( logPtr1 );
    fflush( logPtr2 ); // rilascia dati ancora scritti
    fclose( logPtr2 );
    fflush( logPtr3 ); // rilascia dati ancora scritti
    fclose( logPtr3 );
    fflush( logPtr4 ); // rilascia dati ancora scritti
    fclose( logPtr4 );
    fflush( logPtr5 ); // rilascia dati ancora scritti
    fclose( logPtr5 );

    printf("TOT. MTX: %llu\nMAT AMMESSE CP: %llu | MAT AMMESSE MONO 3x3: %llu | MAT AMMESSE MONO 2x2: %llu\nMAT AMMESSE NON VIETATE: %llu\nMAT VIETATE NON_CP: %llu\n", countFiltro, cont_cp, cont_cp_mono_3x3, cont_cp_mono_2x2, cont_cp_NON_vietate, cont_non_cp);
    for(int z = 0; z <=18; z++) {
//        printf("SOMMA PARI A %d: %d\n", z, arrNumSum[z]);
    }

    int sumDist = 0;
    for(unsigned long long zzz = 0; zzz <= 999; zzz++) {
        sumDist = sumDist + arrDistribution[zzz];
        if(arrDistribution[zzz] != 0) {
//            printf("MATRICI CON %llu <012>: %llu | TOTALE MAT: %llu\n", zzz, arrDistribution[zzz], sumDist);
        }

    }

    free(arrSign); // don't forget this!


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f", time_spent);

//    getchar();
    return 0;

} //end main


int setBit2(int mtx[ NUM ][ NUM ]) {

    for ( int r = 0; r < NUM; r++ ) {
        for ( int c = 0; c < NUM; c++ ) {
            if( mtx[0][0] != mtx[r][c] ) {
                return mtx[r][c];
            }
        }
    }

    return -1;

}

int setBit3(int mtx[ NUM ][ NUM ], int bit1, int bit2) {

    for ( int r = 0; r < NUM; r++ ) {
        for ( int c = 0; c < NUM; c++ ) {
            if( mtx[r][c] != bit1 && mtx[r][c] != bit2 ) {
                return mtx[r][c];
            }
        }
    }

    return -1;

}

int setBit4(int mtx[ NUM ][ NUM ], int bit1, int bit2, int bit3) {

    for ( int r = 0; r < NUM; r++ ) {
        for ( int c = 0; c < NUM; c++ ) {
            if( mtx[r][c] != bit1 && mtx[r][c] != bit2 && mtx[r][c] != bit3 ) {
                return mtx[r][c];
            }
        }
    }

    return -1;

}

int checkMtxMono4x4(int mtx[ NUM ][ NUM ]) {

    for(int r = 0; r <= 3; r++) {
        for(int c = 0; c <= 3; c++) {
            if(mtx[0][0] != mtx[r][c]) {
                return 0; //MONO FALSE
            }
        }
    }

    return 1; //MONO TRUE

} //end checkMtxMono4x4

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
    return 0;
}

int sumMtx(int matrix[][NUM], int* arrNumSum, int* arrNumCount, int* arrHowMany012, int *arrDistribution) {

    int sum = 0;

    for(int a = 0; a < NUM; a++) {
        arrHowMany012[a] = 0;
    }

    for(int i = 0; i < NUM; i++){
        for(int j = 0; j < NUM; j++){
            if(matrix[i][j] == 0) {
                arrHowMany012[0]++;
            } else if(matrix[i][j] == 1) {
                arrHowMany012[1]++;
            } else if(matrix[i][j] == 2) {
                arrHowMany012[2]++;
            }

            sum += matrix[i][j]; //calcolo somma valori matrice corrente
            arrNumCount[matrix[i][j]]++; //incremento array delle somme
        }
    }

    arrDistribution[concat(arrHowMany012[0],arrHowMany012[1],arrHowMany012[2])]++;
    arrNumSum[sum]++;
    return sum;
}

int concat(int x, int y, int z){
    char str1[3];
    char str2[3];
    char str3[3];

    sprintf(str1,"%d",x);
    sprintf(str2,"%d",y);
    sprintf(str3,"%d",z);

    strcat(str1,str2);
    strcat(str1,str3);

    int a = atoi(str1);

    return a;
}

void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, unsigned long long cont_Mtx, int cp, unsigned long long* countInterno ) {

    *countInterno = *countInterno + 1;

    fprintf( fPtr, "%llu | N° %llu***\n", *countInterno, cont_Mtx);
    if (cp == 0) {
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