#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 3 //processa 19683 matrici (tempo di esecuzione indicativo: meno di un secondo)

// PROTOTIPI
void initMtx( int mtx[ NUM ][ NUM ] );
void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm );
void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3, int idx, int sumWeight, int countRC3bit, int countStraight, int count1for2, int countCoppiaRow, int countCoppiaCol );
int checkMtx(int mtx[ NUM ][ NUM ]);
int checkMtx3x3(int mtx[ NUM ][ NUM ]);
int checkMtxMono3x3(int mtx[ NUM ][ NUM ]);
int checkMtx2x3(int mtx[ NUM ][ NUM ]);
int checkMtx3x2(int mtx[ NUM ][ NUM ]);
int checkMtx2x2(int mtx[ NUM ][ NUM ]);
int sumMtx(int matrix[][NUM], int* arrNumSum, int* arrNumCount, int* arrHowMany012, int *arrDistribution);
int concat(int x, int y, int z);

int setBit2(int mtx[ NUM ][ NUM ]);
int setBit3(int mtx[ NUM ][ NUM ], int bit1, int bit2);


int main() {
    clock_t begin = clock();

    const unsigned long lim = 123333335;
    unsigned long *arrSign = malloc(lim * sizeof(unsigned long));


    int mtx[ NUM ][ NUM ];

    FILE *logPtr1, *logPtr21, *logPtr22, *logPtr23, *logPtr24, *logPtr3, *logPtr4, *logPtr5;
    int arr[] = {0, 1, 2};
    int cont_Mtx = 0;
    int cont_MtxNoDuplicate = 0;
    int mtxType = 0; //0: computabile privatamente | 1: | 2: | 3: | 4
    int cont_cp = 0;
    int cont_cp_mono_3x3 = 0;
    int cont_cp_mono_2x2 = 0;
    int cont_cp_NON_vietate = 0;
    int cont_ncp_3x3 = 0;
    int cont_ncp_2x2 = 0;
    int cont_ncp_2x3 = 0;
    int cont_ncp_3x2 = 0;
    int countInterno = 0;
    int countInterno2 = 0;
    int arrNumSum[18] = {0};
    int arrHowMany012[3] = {0};
    int arrDistribution[999] = {0};
//    unsigned long arrSign[lim] = {0};

    int bit1 = -1;
    int bit2 = -1;
    int bit3 = -1;
    int bitCentrale = -1;
    int countBitCentrale = 0;
    int countBit1 = 0;
    int countBit2 = 0;
    int countBit3 = 0;
    int countRC3bit = 0;
    int countStraight = 0;
    int count1for2 = 0;
    int countCoppiaRow = 0;
    int countCoppiaCol = 0;
    unsigned long sign = 0;
    int sumWeight = 0;
    int countPos = 0;
    int idx = 0;
    int idx3 = 0;
    int arrPattern[20000] = {0};
    int mtxWeight[19683][9] = {0};

    int arrBitWeight1[] = {1907, 1013, 461, 1753, 1877, 317, 1597, 967, 157};
    int arrBitWeight2[] = { 463, 523, 337, 1699, 401, 1933, 1069, 379, 283};
    int arrBitWeight3[] = {293, 499, 421, 1439, 277, 1783, 769, 1051, 1523};


    int arrBitWeight[] = {10, 11, 12, 13, 14, 15, 16, 17, 18};


    char filename[50], filename21[50], filename22[50], filename23[50], filename24[50], filename3[50], filename4[50], filename5[50];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename, "1-tot-mat-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename21, "21-NCP_3x3-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename22, "22-NCP_2x2-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename23, "23-NCP_2x3-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename24, "24-NCP_3x2-%04d%02d%02d-%02d%02d%02d.txt",
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

    if ( ( logPtr1 = fopen( filename, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr21 = fopen( filename21, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr22 = fopen( filename22, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr23 = fopen( filename23, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr24 = fopen( filename24, "w" ) ) == NULL ) {
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

    initMtx( mtx );

    fflush( logPtr1 ); // rilascia dati ancora scritti
    fflush( logPtr21 ); // rilascia dati ancora scritti
    fflush( logPtr22 ); // rilascia dati ancora scritti
    fflush( logPtr23 ); // rilascia dati ancora scritti
    fflush( logPtr24 ); // rilascia dati ancora scritti
    fflush( logPtr3 ); // rilascia dati ancora scritti
    fflush( logPtr4 ); // rilascia dati ancora scritti
    fflush( logPtr5 ); // rilascia dati ancora scritti




//BEGIN controllo selettivo
//    cont_Mtx++;
//    mtxType = checkMtx( mtx ); //controllo MATRICI
////                sumMtx(mtx, arrNumSum);
//    if (mtxType == 0) {
//        cont_non_cp++; //0 - NON CP - vietata o monocromatica
////                    printMtxToFile( mtx, logPtr21, cont_Mtx, mtxType );
//    } else if (mtxType == 2) {
//        cont_cp++;
//        cont_cp_mono_3x3++;
////                    printMtxToFile( mtx, logPtr4, cont_Mtx, mtxType );
//    } else if (mtxType == 3) {
//
//        cont_cp++;
//        cont_cp_mono_2x2++;
////                    printMtxToFile( mtx, logPtr5, cont_Mtx, mtxType );
//    } else {
//        cont_cp_NON_vietate++;
//        cont_cp++; //1 - CP - ammessa (perchè NON vietata)
//
//        if(sumMtx(mtx, arrNumSum) == 4) {
//            printMtxToFile( mtx, logPtr3, cont_Mtx, mtxType );
//
//        }
//
//
//    }
////END controllo selettivo
//
//return 0; //interrompi prima di controllo MASSIVO

    for ( int i = 0; i < pow(NUM, NUM); i++ ) {
        rowPerm( mtx, 2, i, arr, 3, 3 );
        for ( int j = 0; j < pow(NUM, NUM); j++ ) {
            rowPerm( mtx, 1, j, arr, 3, 3 );
            for ( int k = 0; k < pow(NUM, NUM); k++ ) {
                rowPerm( mtx, 0, k, arr, 3, 3 );

                bit1 = mtx[0][0];

                bit2 = setBit2( mtx);
                bit3 = setBit3( mtx, bit1, bit2);

                sumWeight = 0;
                countBitCentrale = 0;
                countBit1 = 0;
                countBit2 = 0;
                countBit3 = 0;
                countRC3bit = 0;
                countStraight = 0;
                count1for2 = 0;
                countCoppiaRow = 0;
                countCoppiaCol = 0;
                countPos = -1;
                sign = 0;

                cont_Mtx++;

                if(checkMtxMono3x3(mtx) == 1) continue; //salta 3 monocromatiche



                int t = 8;


                //costruisci signature per evitare mtx duplicate
                for ( int r = 0; r < NUM; r++ ) {
                    for ( int c = 0; c < NUM; c++ ) {

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

                        if(cont_Mtx == 3865) {
//                            printf("%d\n", sumWeight);
                        }

                    }
                }

//                printf("%d | %lu\n", cont_Mtx, sign);
//                printf("%lu\n", sign);

                arrSign[sign]++;
                arrPattern[sumWeight]++;

                if(arrSign[sign] != 1) continue; //evito di andare oltre come tutte le iterazioni di mtx duplicate

                idx++;
                cont_MtxNoDuplicate++;

                if(mtx[1][1] == bit1) {
                    bitCentrale = bit1;
                } else if(mtx[1][1] == bit2) {
                    bitCentrale = bit2;
                } else if(mtx[1][1] == bit3) {
                    bitCentrale = bit3;
                }

                for ( int r = 0; r < NUM; r++ ) {
                    for ( int c = 0; c < NUM; c++ ) {
                        if(mtx[r][c] == bitCentrale) {
                            countBitCentrale++;
                        }
                    }
                }

                if(countBitCentrale == 2) { //NUMERO DI OCCORRENZE BIT CENTRALE


//                    if(bitCentrale == mtx[0][0] || bitCentrale == mtx[0][2] || bitCentrale == mtx[2][0] || bitCentrale == mtx[2][2]) {
//                    if(bitCentrale == mtx[0][0]) {

//                    if(bitCentrale == mtx[0][1] || bitCentrale == mtx[1][2] || bitCentrale == mtx[2][1] || bitCentrale == mtx[1][0]) {

                    if(bitCentrale == mtx[0][1]) {


                    if(bitCentrale == bit1) {
                        for ( int r = 0; r < NUM; r++ ) {
                            for ( int c = 0; c < NUM; c++ ) {
                                if(mtx[r][c] == bit2) {
                                    countBit2++;
                                } else if (mtx[r][c] == bit3) {
                                    countBit3++;
                                }
                            }
                        }
                    } else if(bitCentrale == bit2) {
                        for ( int r = 0; r < NUM; r++ ) {
                            for ( int c = 0; c < NUM; c++ ) {
                                if(mtx[r][c] == bit1) {
                                    countBit1++;
                                } else if (mtx[r][c] == bit3) {
                                    countBit3++;
                                }
                            }
                        }
                    } else if(bitCentrale == bit3) {
                        for ( int r = 0; r < NUM; r++ ) {
                            for ( int c = 0; c < NUM; c++ ) {
                                if(mtx[r][c] == bit1) {
                                    countBit1++;
                                } else if (mtx[r][c] == bit2) {
                                    countBit2++;
                                }
                            }
                        }
                    }

                for ( int r = 0; r < NUM; r++ ) {
                    if(mtx[r][0] != mtx[r][1] && mtx[r][0] != mtx[r][2] && mtx[r][1] != mtx[r][2]) {
                        countRC3bit++;
                    }
                }

                for ( int c = 0; c < NUM; c++ ) {
                    if(mtx[0][c] != mtx[1][c] && mtx[0][c] != mtx[2][c] && mtx[1][c] != mtx[2][c]) {
                        countRC3bit++;
                    }
                }

                for ( int r = 0; r < NUM; r++ ) {
                    if(mtx[r][0] == mtx[r][1] && mtx[r][0] == mtx[r][2] && mtx[r][1] == mtx[r][2]) {
                        countStraight++;
                    }
                }

                for ( int c = 0; c < NUM; c++ ) {
                    if(mtx[0][c] == mtx[1][c] && mtx[0][c] == mtx[2][c] && mtx[1][c] == mtx[2][c]) {
                        countStraight++;
                    }
                }

                for ( int r = 0; r < NUM; r++ ) {
                    if((mtx[r][0] != mtx[r][1] && mtx[r][1] == mtx[r][2]) ||
                        (mtx[r][0] != mtx[r][1] && mtx[r][0] == mtx[r][2]) ||
                        (mtx[r][0] == mtx[r][1] && mtx[r][0] != mtx[r][2])) {
                        count1for2++;
                    }
                }

                for ( int c = 0; c < NUM; c++ ) {
                    if((mtx[0][c] != mtx[1][c] && mtx[1][c] == mtx[2][c]) ||
                       (mtx[0][c] != mtx[1][c] && mtx[0][c] == mtx[2][c]) ||
                       (mtx[0][c] == mtx[1][c] && mtx[0][c] != mtx[2][c])) {
                        count1for2++;
                    }
                }


//                if( countRC3bit == 2 && countStraight == 0 && count1for2 == 4) { //numero bit




                    if(
                        (countBit2 == 3 && countBit3 == 4) || (countBit2 == 4 && countBit3 == 3) ||
                        (countBit1 == 3 && countBit3 == 4) || (countBit1 == 4 && countBit3 == 3) ||
                        (countBit1 == 3 && countBit2 == 4) || (countBit1 == 4 && countBit2 == 3)
                        ) {

                        for (int r = 0; r < NUM; r++) {
                            if (mtx[r][0] == mtx[r][1]) countCoppiaRow++;
                            if (mtx[r][1] == mtx[r][2]) countCoppiaRow++;
                            if (mtx[r][0] == mtx[r][2]) countCoppiaRow++;
                        }

                        for (int c = 0; c < NUM; c++) {
                            if (mtx[0][c] == mtx[1][c]) countCoppiaCol++;
                            if (mtx[1][c] == mtx[2][c]) countCoppiaCol++;
                            if (mtx[0][c] == mtx[2][c]) countCoppiaCol++;
                        }

//                        if(countCoppiaRow == 1 && countCoppiaCol == 1) {

                        mtxType = checkMtx(mtx); //controllo MATRICI
                        int arrNumCount[] = {0, 0, 0};
                        //                sumMtx(mtx, arrNumSum, arrNumCount, arrHowMany012, arrDistribution); //spostare in uno dei rami if seguenti per indagare le singole tipologie
                        if (mtxType == 10) { //NON CP - VIETATA 3x3

                            cont_ncp_3x3++; //0 - NON CP - vietata o monocromatica
                            printMtxToFile(mtx, logPtr21, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, cont_ncp_3x3,
                                           sumWeight, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                           countCoppiaCol);


                            //                    if(arrHowMany012[0] == 2 && arrHowMany012[1] == 3 && arrHowMany012[2] == 4) {
                            //                        printMtxToFile( mtx, logPtr21, cont_Mtx, mtxType );
                            //                    }
                        } else if (mtxType == 11) { //NON CP - VIETATA 2x2

                            cont_ncp_2x2++;
                            printMtxToFile(mtx, logPtr22, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, cont_ncp_2x2,
                                           sumWeight, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                           countCoppiaCol);


                        } else if (mtxType == 12) { //NON CP - VIETATA 2x3

                            cont_ncp_2x3++;
                            printMtxToFile(mtx, logPtr23, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, cont_ncp_2x3,
                                           sumWeight, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                           countCoppiaCol);


                        } else if (mtxType == 13) { //NON CP - VIETATA 3x2

                            cont_ncp_3x2++;
                            printMtxToFile(mtx, logPtr24, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, cont_ncp_3x2,
                                           sumWeight, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                           countCoppiaCol);


                        } else { //CP - ammessa (perchè NON vietata)

                            cont_cp_NON_vietate++;
                            cont_cp++; //1 - CP - ammessa (perchè NON vietata)
                            idx3++;

                            //                        if(sumMtx(mtx, arrNumSum) == 15) {
                            printMtxToFile(mtx, logPtr3, cont_Mtx, mtxType, bit1, bit2, bit3, idx3, sumWeight,
                                           countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol);
                            //
                            //                        }

                            //                        if(arrHowMany012[0] == 3 && arrHowMany012[1] == 3 && arrHowMany012[2] == 3) {
                            //                            printMtxToFile( mtx, logPtr3, cont_Mtx, mtxType );
                            //                        }



                        }
                        //stampa TUTTE LE MATRICI
                        //                if(sumWeight == 10049) printMtxToFile( mtx, logPtr1, cont_Mtx, mtxType, bit1, bit2, bit3, sumWeight );
                        printMtxToFile(mtx, logPtr1, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, idx, sumWeight,
                                       countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol);

//                    }
                    } //PATTERN 2 DIAGONALE/DRITTO

//                        } // countCoppiaRow countCoppiaCol
                    } //END if countBit1 2 3

                } //END if NUMERO DI OCCORRENZE BIT CENTRALE
//                } //END  //numero bit
            }
        }
    }

    fflush( logPtr1 ); // rilascia dati ancora scritti
    fclose( logPtr1 );
    fflush( logPtr21 ); // rilascia dati ancora scritti
    fclose( logPtr21 );
    fflush( logPtr22 ); // rilascia dati ancora scritti
    fclose( logPtr22 );
    fflush( logPtr23 ); // rilascia dati ancora scritti
    fclose( logPtr23 );
    fflush( logPtr24 ); // rilascia dati ancora scritti
    fclose( logPtr24 );
    fflush( logPtr3 ); // rilascia dati ancora scritti
    fclose( logPtr3 );
    fflush( logPtr4 ); // rilascia dati ancora scritti
    fclose( logPtr4 );
    fflush( logPtr5 ); // rilascia dati ancora scritti
    fclose( logPtr5 );

//    printf("TOT. MTX: %d\nMAT AMMESSE CP: %d | MAT AMMESSE MONO 3x3: %d | MAT AMMESSE MONO 2x2: %d | MAT AMMESSE NON VIETATE: %d\nMAT VIETATE NON_CP: %d\n", idx, cont_cp, cont_cp_mono_3x3, cont_cp_mono_2x2, cont_cp_NON_vietate, cont_non_cp);
    printf("TOT. MTX:           %d\nMTX AMMESSE CP:     %d\nMTX VIETATE NON_CP: %d\n"
           "di cui VIETATE 3x3: %d\n       VIETATE 2x2: %d\n       VIETATE 2x3: %d\n       VIETATE 3x2: %d\n",
           idx, cont_cp_NON_vietate, cont_ncp_3x3 + cont_ncp_2x2 + cont_ncp_2x3 + cont_ncp_3x2, cont_ncp_3x3, cont_ncp_2x2, cont_ncp_2x3, cont_ncp_3x2);
    for(int z = 0; z <=18; z++) {
//        printf("SOMMA PARI A %d: %d\n", z, arrNumSum[z]);
    }

    int sumDist = 0;
    for(int zzz = 0; zzz <= 999; zzz++) {
        sumDist = sumDist + arrDistribution[zzz];
        if(arrDistribution[zzz] != 0) {
//            printf("MATRICI CON %d <012>: %d | TOTALE MAT: %d\n", zzz, arrDistribution[zzz], sumDist);
        }

    }

    for(int zzz = 0; zzz < 20000; zzz++) {
        if(arrPattern[zzz] != 0 && arrPattern[zzz] != 6) {
//            printf("ARRAY PATTERN POSIZIONE %d: %d\n", zzz, arrPattern[zzz]);
//            printf("%d\n", arrPattern[zzz]);
        }

    }

    for(int r = 0; r < 19683; r++) {
//        printf("\n%d|", r+1);
//        printf("\n");
        for(int c = 0; c < 9; c++) {
//            printf("%d", mtxWeight[r][c]);
        }

    }

    free(arrSign); // don't forget this!

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nTime: %f", time_spent);

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

} //end initMtx

void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm ) {

    for ( int i = 0; i < lenPerm; i++ ) {
        mtx[riga][i] = valori[numPerm % lenValori];
        numPerm = numPerm / lenValori;
    }

} //end rowPerm

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

int checkMtx(int mtx[ NUM ][ NUM ]) {
    if (checkMtx3x3(mtx) == 1) {
        return 10; //VIETATA TRUE - NON CP
    }
    else if (checkMtx3x3(mtx) == 2) {
        return 2; //MONO 3x3 TRUE - AMMESSA
    }
    else if (checkMtx2x2(mtx) == 1) {
        return 11; //VIETATA TRUE - NON CP
    }
    else if (checkMtx2x2(mtx) == 3) {
        return 3; //MONO 2x2 TRUE - AMMESSA
    }
    else if (checkMtx2x3(mtx) == 1) {
        return 12; //VIETATA TRUE - NON CP
    }
    else if (checkMtx3x2(mtx) == 1) {
        return 13; //VIETATA TRUE - NON CP
    }
    else {      //VIETATA FALSE - CP
        return 1; //CP TRUE - AMMESSA (NON VIETATA)
    }
}

int checkMtx3x3(int mtx[ NUM ][ NUM ]) {

    int equivR = 0;
    int equivC = 0;

//    if (checkMtxMono3x3(mtx) == 1) {
//        return 2; //MONO 3x3 TRUE
//    }
    //if NO MONOCROMATICA

    //check row
    for(int i = 0; i <= 2; i++) {
        if(mtx[0][i] == mtx[1][i]) { //relaz in prime 2 righe
            for(int j = 0; j <= 2; j++) {
                if(mtx[1][j] == mtx[2][j] || mtx[0][j] == mtx[2][j]) { //relaz in 2a e 3a riga OPPURE in 1a e 3a riga
                    equivR = 1;
                }
            }
        } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
            for(int k = 0; k <= 2; k++) {
                if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                    equivR = 1;
                }
            }
        }
        else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
            for(int ku = 0; ku <= 2; ku++) {
                if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                    equivR = 1;
                }
            }
        }
    } //end check row

    //check col
    if(equivR == 1) {
        for(int q = 0; q <= 2; q++) {
            if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                for(int w = 0; w <= 2; w++) {
                    if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                        equivC = 1;
                    }
                }
            } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                for(int e = 0; e <= 2; e++) {
                    if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                        equivC = 1;
                    }
                }
            }
            else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                for(int e = 0; e <= 2; e++) {
                    if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
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

int checkMtxMono3x3(int mtx[ NUM ][ NUM ]) {

    for(int r = 0; r <= 2; r++) {
        for(int c = 0; c <= 2; c++) {
            if(mtx[0][0] != mtx[r][c]) {
                return 0; //MONO FALSE
            }
        }
    }

    return 1; //MONO TRUE

} //end checkMtxMono3x3

int checkMtx2x3(int mtx[ NUM ][ NUM ]) {


    //1a 2a RIGA | TUTTE COLONNE
    for(int i = 0; i <= 1; i++) {
        if(mtx[0][i] == mtx[1][i]) {
            for(int q = 0; q <= 1; q++) {
                if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                    for(int w = 0; w <= 1; w++) {
                        if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                    for(int e = 0; e <= 1; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int e = 0; e <= 1; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            }
        }
    } //END 1a 2a RIGA | TUTTE COLONNE



    //1a 3a RIGA | TUTTE COLONNE
    for(int i = 0; i != 1 && i <= 2; i++) {
        if(mtx[0][i] == mtx[2][i]) {

            for(int q = 0; q != 1 && q <= 2; q++) {
                if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                    for(int w = 0; w != 1 && w <= 2; w++) {
                        if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                    for(int e = 0; e != 1 && e <= 2; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int e = 0; e != 1 && e <= 2; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            }


        }
    } //END 1a 3a RIGA | TUTTE COLONNE




    //2a 3a RIGA | TUTTE COLONNE
    for(int i = 1; i <= 2; i++) {
        if(mtx[1][i] == mtx[2][i]) {

            for(int q = 1; q <= 2; q++) {
                if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                    for(int w = 1; w <= 2; w++) {
                        if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                    for(int e = 1; e <= 2; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int e = 1; e <= 2; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            }

        }
    } //END 2a 3a RIGA | TUTTE COLONNE

    return 0; //VIETATA FALSE - CP

}

int checkMtx3x2(int mtx[ NUM ][ NUM ]) {


    //TUTTE RIGHE | 1a 2a COL
    for(int i = 0; i <= 2; i++) {
        if(mtx[i][0] == mtx[i][1]) {
            //check row
            for(int i = 0; i <= 1; i++) {
                if(mtx[0][i] == mtx[1][i]) { //relaz in prime 2 righe
                    for(int j = 0; j <= 1; j++) {
                        if(mtx[1][j] == mtx[2][j] || mtx[0][j] == mtx[2][j]) { //relaz in 2a e 3a riga OPPURE in 1a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
                    for(int k = 0; k <= 1; k++) {
                        if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int ku = 0; ku <= 1; ku++) {
                        if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            } //end check row
        }
    } //END TUTTE RIGHE | 1a 2a COL



    //TUTTE RIGHE | 1a 3a COL
    for(int i = 0; i <= 2; i++) {
        if(mtx[i][0] == mtx[i][2]) {

            //check row
            for(int i = 0; i != 1 && i <= 2; i++) {
                if(mtx[0][i] == mtx[1][i]) { //relaz in prime 2 righe
                    for(int j = 0; j != 1 && j <= 2; j++) {
                        if(mtx[1][j] == mtx[2][j] || mtx[0][j] == mtx[2][j]) { //relaz in 2a e 3a riga OPPURE in 1a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
                    for(int k = 0; k != 1 && k <= 2; k++) {
                        if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int ku = 0; ku != 1 && ku <= 2; ku++) {
                        if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            } //end check row


        }
    } //END TUTTE RIGHE | 1a 3a COL




    //TUTTE RIGHE | 2a 3a COL
    for(int i = 0; i <= 2; i++) {
        if(mtx[i][1] == mtx[i][2]) {

            //check row
            for(int i = 1; i <= 2; i++) {
                if(mtx[0][i] == mtx[1][i]) { //relaz in prime 2 righe
                    for(int j = 1; j <= 2; j++) {
                        if(mtx[1][j] == mtx[2][j] || mtx[0][j] == mtx[2][j]) { //relaz in 2a e 3a riga OPPURE in 1a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
                    for(int k = 1; k <= 2; k++) {
                        if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int ku = 1; ku <= 2; ku++) {
                        if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                            return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            } //end check row

        }
    } //END TUTTE RIGHE | 2a 3a COL

    return 0; //VIETATA FALSE - CP

}


int checkMtx2x2(int mtx[ NUM ][ NUM ]) {

//    if (checkMono2_1(mtx) == 1 ||
//        checkMono2_2(mtx) == 1 ||
//        checkMono2_3(mtx) == 1 ||
//        checkMono2_4(mtx) == 1) {
//        return 3;
//    }



    //MTX 2x2 CONTIGUE
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


// [0][0]   [0][1]  [0][2]
// [1][0]   [1][1]  [1][2]
// [2][0]   [2][1]  [2][2]

    //MTX 2x2 NON CONTIGUE
    //1a 2a RIGA | 1a 3a COL
    for(int i = 0; i != 1 && i <= 2; i++) {
        if(mtx[0][i] == mtx[1][i]) {
            for(int j = 0; j <= 1; j++) {
                if(mtx[j][0] == mtx[j][2]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END 1a 2a RIGA | 1a e 3a COL

    //1a 3a RIGA | 1a 2a COL
    for(int i = 0; i <= 1; i++) {
        if(mtx[0][i] == mtx[2][i]) {
            for(int j = 0; j != 1 && j <= 2; j++) {
                if(mtx[j][0] == mtx[j][1]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END 1a 3a RIGA | 1a 2a COL

    //1a 3a RIGA | 1a 3a COL
    for(int i = 0; i != 1 && i <= 2; i++) {
        if(mtx[0][i] == mtx[2][i]) {
            for(int j = 0; j != 1 && j <= 2; j++) {
                if(mtx[j][0] == mtx[j][2]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END 1a 3a RIGA | 1a 3a COL

    //1a 3a RIGA | 2a 3a COL
    for(int i = 1; i <= 2; i++) {
        if(mtx[0][i] == mtx[2][i]) {
            for(int j = 0; j != 1 && j <= 2; j++) {
                if(mtx[j][1] == mtx[j][2]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END 1a 3a RIGA | 2a 3a COL

    //2a 3a RIGA | 1a 3a COL
    for(int i = 0; i != 1 && i <= 2; i++) {
        if(mtx[1][i] == mtx[2][i]) {
            for(int j = 1; j <= 2; j++) {
                if(mtx[j][0] == mtx[j][2]) {
                    return 1; //VIETATA TRUE - NON CP
                }
            }
        }
    } //END 2a 3a RIGA | 1a 3a COL


    return 0; //VIETATA FALSE - CP
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

void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3, int idx, int sumWeight, int countRC3bit, int countStraight, int count1for2, int countCoppiaRow, int countCoppiaCol ) {

//    *countInterno = *countInterno + 1;

//    fprintf( fPtr, "%d%d%d\n", countRC3bit, countStraight, count1for2);
    fprintf( fPtr, "%d | N° %d\nRC3:%d | STRAIGHT:%d | 1for2:%d\nCoppiaRow:%d | CoppiaCol:%d\nA:%d | B:%d | C:%d\n", idx, cont_Mtx, countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol, bit1, bit2, bit3);
    if (mtxType == 10 || mtxType == 11 || mtxType == 12 || mtxType == 13) {
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
            if( mtx[ r ][ c ] == bit1 ) {
                fprintf( fPtr, "%3c", 'A' );
            } else if(mtx[ r ][ c ] == bit2) {
                fprintf( fPtr, "%3c", 'B' );
            } else if(mtx[ r ][ c ] == bit3) {
                fprintf( fPtr, "%3c", 'C' );
            }

        }
        fprintf( fPtr, "\n" );
    }

    fprintf( fPtr, "\n" );

} //end printMtxToFile