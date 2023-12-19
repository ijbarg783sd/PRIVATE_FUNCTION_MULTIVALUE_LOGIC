#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 3 //processa 19683 matrici (tempo di esecuzione indicativo: meno di un secondo)

// PROTOTIPI
void initMtx( int mtx[ NUM ][ NUM ] );
void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm );
void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3, int bitCentrale, int idx, int countRC3bit, int countStraight, int count1for2, int countCoppiaRow, int countCoppiaCol );
int checkMtx(int mtx[ NUM ][ NUM ]);
int checkMtx2x2(int mtx[ NUM ][ NUM ]);

int main() {
    clock_t begin = clock();

    int mtx[ NUM ][ NUM ];

    FILE *logPtr_ALL, *logPtr_CP, *logPtr_NCP;
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
    int countPos = 0;
    int idx = 0;
    int idx3 = 0;

    int arrBitWeight[] = {10, 11, 12, 13, 14, 15, 16, 17, 18};


    char filename_ALL[50], filename_CP[50], filename_NCP[50];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename_ALL, "01-ALL_3x3-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename_CP, "02-CP_3x3-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    sprintf( filename_NCP, "03-NCP_3x3-%04d%02d%02d-%02d%02d%02d.txt",
             tm -> tm_year + 1900, tm -> tm_mon + 1, tm -> tm_mday,
             tm -> tm_hour, tm -> tm_min, tm -> tm_sec );

    if ( ( logPtr_ALL = fopen( filename_ALL, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr_CP = fopen( filename_CP, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    if ( ( logPtr_NCP = fopen( filename_NCP, "w" ) ) == NULL ) {
        printf( "IMPOSSIBILE APRIRE IL FILE" );
        return 0;
    }

    initMtx( mtx );

    fflush( logPtr_ALL ); // rilascia dati ancora scritti
    fflush( logPtr_CP ); // rilascia dati ancora scritti
    fflush( logPtr_NCP ); // rilascia dati ancora scritti

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
                bitCentrale = -1;
                sign = 0;

                cont_Mtx++;


                idx++;
                cont_MtxNoDuplicate++;


                mtxType = checkMtx(mtx); //controllo MATRICI

                if (mtxType == 11) { //NON CP - VIETATA 2x2

                    cont_ncp_2x2++;
                    printMtxToFile(mtx, logPtr_NCP, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale,
                                   cont_ncp_2x2, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                   countCoppiaCol);

                } else { //CP - ammessa (perchè NON vietata)

                    cont_cp_NON_vietate++;
                    cont_cp++; //1 - CP - ammessa (perchè NON vietata)
                    idx3++;

                    printMtxToFile(mtx, logPtr_CP, cont_Mtx, mtxType, bit1, bit2, bit3, bitCentrale, idx3,
                                   countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol);


                }
                //stampa TUTTE LE MATRICI
                printMtxToFile(mtx, logPtr_ALL, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale, idx,
                               countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol);


            }
        }
    }

    fflush( logPtr_ALL ); // rilascia dati ancora scritti
    fclose( logPtr_ALL );
    fflush( logPtr_CP ); // rilascia dati ancora scritti
    fclose( logPtr_CP );
    fflush( logPtr_NCP ); // rilascia dati ancora scritti
    fclose( logPtr_NCP );

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

    for(int r = 0; r < 19683; r++) {
//        printf("\n%d|", r+1);
//        printf("\n");
        for(int c = 0; c < 9; c++) {
//            printf("%d", mtxWeight[r][c]);
        }

    }

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

int checkMtx(int mtx[ NUM ][ NUM ]) {

    if (checkMtx2x2(mtx) == 1) {
        return 11; //VIETATA TRUE - NON CP
    } else {      //VIETATA FALSE - CP
        return 1; //CP TRUE - AMMESSA (NON VIETATA)
    }
}

int checkMtx2x2(int mtx[ NUM ][ NUM ]) {

    int m[9][4] = {
            {0,1, 0, 1},
            {0,1, 0, 2},
            {0,1, 1, 2},
            {0,2, 0, 1},
            {0,2, 0, 2},
            {0,2, 1, 2},
            {1,2, 0, 1},
            {1,2, 0, 2},
            {1,2, 1, 2},
    };

    int count0 = 0;
    int count1 = 0;
    int count2 = 0;

//    printf("START\n");
    for(int i = 0; i <= 8; i++) {
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

                if (c+1 < m[i][3]) c = m[i][3] - 1;
            }
            if (r+1 < m[i][1]) r = m[i][1] - 1;
        }
//        printf("count0: %d | count1: %d | count2: %d\n", count0, count1, count2);
        if(count0 == 3 || count1 == 3 || count2 == 3) return 1;

    } //check 9 submatrix 2x2

    return 0; //VIETATA FALSE - CP
}

void printMtxToFile( int mtx[ NUM ][ NUM ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3, int bitCentrale, int idx, int countRC3bit, int countStraight, int count1for2, int countCoppiaRow, int countCoppiaCol ) {

//    *countInterno = *countInterno + 1;

//    fprintf( fPtr, "%d%d%d\n", countRC3bit, countStraight, count1for2);
    fprintf( fPtr, "%d | N° %d\nRC3:%d|STR:%d|1f2:%d\nCopR:%d | CopC:%d\n", idx, cont_Mtx, countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol );
    if (mtxType == 10 || mtxType == 11 || mtxType == 12 || mtxType == 13) {
        fprintf( fPtr, "VIETATA - NON CP\n");
    } else {
//        fprintf( fPtr, "AMMESSA - CP\n");
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
//            fprintf( fPtr, "%3d", mtx[ r ][ c ] ); //stampa il bit reale
            if (bitCentrale == bit1) {
                if( mtx[ r ][ c ] == bit1) {
                    fprintf( fPtr, "%3c", 'A' );
//                    fprintf( fPtr, "%3c", '-' );
                } else if(mtx[ r ][ c ] == bit2) {
                    fprintf( fPtr, "%3c", 'B' );
                } else if(mtx[ r ][ c ] == bit3) {
                    fprintf( fPtr, "%3c", 'C' );
                }
            } else if(bitCentrale == bit2) {
                if( mtx[ r ][ c ] == bit1) {
                    fprintf( fPtr, "%3c", 'A' );
                } else if(mtx[ r ][ c ] == bit2) {
                    fprintf( fPtr, "%3c", 'B' );
//                    fprintf( fPtr, "%3c", '-' );
                } else if(mtx[ r ][ c ] == bit3) {
                    fprintf( fPtr, "%3c", 'C' );
                }
            } else if(bitCentrale == bit3) {
                if( mtx[ r ][ c ] == bit1) {
                    fprintf( fPtr, "%3c", 'A' );
                } else if(mtx[ r ][ c ] == bit2) {
                    fprintf( fPtr, "%3c", 'B' );
                } else if(mtx[ r ][ c ] == bit3) {
                    fprintf( fPtr, "%3c", 'C' );
//                    fprintf( fPtr, "%3c", '-' );
                }
            }

        }
        fprintf( fPtr, "\n" );
    }

    fprintf( fPtr, "\n" );

} //end printMtxToFile