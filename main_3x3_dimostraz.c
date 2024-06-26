#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 3 //processa 19683 matrici (tempo di esecuzione indicativo: meno di un secondo)

// PROTOTIPI
void initMtx( int mtx[ NUM ][ NUM ] );
void initMtx2( int mtx[ NUM ][ NUM ] );
void rowPerm( int mtx[ NUM ][ NUM ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm );
void printMtxToFile( int mtx[ NUM ][ NUM ], int mtx2[ NUM ][ NUM ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3, int bitCentrale, int idx, int countRC3bit, int countStraight, int count1for2, int countCoppiaRow, int countCoppiaCol, int sign );
int checkMtx(int mtx[ NUM ][ NUM ], int mtx2[ NUM ][ NUM ], int* arrSign2);
int checkMtx3x3(int mtx[ NUM ][ NUM ], int mtx2[ NUM ][ NUM ]);
int checkMtxMono3x3(int mtx[ NUM ][ NUM ]);
int checkMono2x2C_AS(int mtx[ NUM ][ NUM ]); //CONTIGUE (4)
int checkMono2x2C_AD(int mtx[ NUM ][ NUM ]);
int checkMono2x2C_BS(int mtx[ NUM ][ NUM ]);
int checkMono2x2C_BD(int mtx[ NUM ][ NUM ]);
int checkMono2x2NC_1(int mtx[ NUM ][ NUM ]); //NON CONTIGUE (5)
int checkMono2x2NC_2(int mtx[ NUM ][ NUM ]);
int checkMono2x2NC_3(int mtx[ NUM ][ NUM ]);
int checkMono2x2NC_4(int mtx[ NUM ][ NUM ]);
int checkMono2x2NC_5(int mtx[ NUM ][ NUM ]);
int checkMono2x3_1(int mtx[ NUM ][ NUM ]);
int checkMono2x3_2(int mtx[ NUM ][ NUM ]);
int checkMono2x3_3(int mtx[ NUM ][ NUM ]);
int checkMono3x2_1(int mtx[ NUM ][ NUM ]);
int checkMono3x2_2(int mtx[ NUM ][ NUM ]);
int checkMono3x2_3(int mtx[ NUM ][ NUM ]);
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
    int mtx2[ NUM ][ NUM ];

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
    int arrSign2[10000] = {0};
    int sign2 = 0;


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
    initMtx2( mtx2 );

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
//    for ( int i = 0; i < 1; i++ ) {
        rowPerm( mtx, 2, i, arr, 3, 3 );
        for ( int j = 0; j < pow(NUM, NUM); j++ ) {
//        for ( int j = 0; j < 1; j++ ) {
            rowPerm( mtx, 1, j, arr, 3, 3 );
            for ( int k = 0; k < pow(NUM, NUM); k++ ) {
                rowPerm( mtx, 0, k, arr, 3, 3 );
//                printf("%d %d %d\n", mtx[0][0], mtx[0][1], mtx[0][2]);
                bit1 = mtx[0][0];

                bit2 = setBit2( mtx);
                bit3 = setBit3( mtx, bit1, bit2);

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

                if(checkMtxMono3x3(mtx) == 1) continue; //salta 3 monocromatiche
                if(cont_Mtx == 1) break; //salta 3 monocromatiche

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

                    }
                }

                // CHECK SIGNATURE
//                printf("%d | %lu\n", cont_Mtx, sign);

                arrSign[sign]++;

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

                if(countBitCentrale != -1) { //NUMERO DI OCCORRENZE BIT CENTRALE - PASSANO TUTTE LE MATRICI
//                if(countBitCentrale == 1) { //NUMERO DI OCCORRENZE BIT CENTRALE
//                if(countBitCentrale == 2) { //NUMERO DI OCCORRENZE BIT CENTRALE
//                if(countBitCentrale == 3) { //NUMERO DI OCCORRENZE BIT CENTRALE
//                if(countBitCentrale == 4) { //NUMERO DI OCCORRENZE BIT CENTRALE
//                if(countBitCentrale == 5) { //NUMERO DI OCCORRENZE BIT CENTRALE
//                if(countBitCentrale == 6) { //NUMERO DI OCCORRENZE BIT CENTRALE

                    //FORZA PATTERN

                    // FORZA PATTERN NEGATIVO
//                    if(
//                        //3 VERTICI
//                        (!(mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[0][0] && mtx[0][0] != mtx[2][0]) &&
//                         !(mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][2] && mtx[0][2] != mtx[0][0]) &&
//                         !(mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[2][2] && mtx[2][2] != mtx[0][2]) &&
//                         !(mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][0] && mtx[2][0] != mtx[2][2]) )
//                        &&
//                        //"L" UNITA
//                        (!(mtx[0][0] == mtx[0][1] && mtx[0][1] == mtx[1][1] && mtx[1][1] == mtx[0][0] && mtx[0][0] != mtx[1][0]) &&
//                         !(mtx[0][1] == mtx[1][1] && mtx[1][1] == mtx[1][0] && mtx[1][0] == mtx[0][1] && mtx[0][1] != mtx[0][0]) &&
//                         !(mtx[1][1] == mtx[1][0] && mtx[1][0] == mtx[0][0] && mtx[0][0] == mtx[1][1] && mtx[1][1] != mtx[0][1]) &&
//                         !(mtx[1][0] == mtx[0][0] && mtx[0][0] == mtx[0][1] && mtx[0][1] == mtx[1][0] && mtx[1][0] != mtx[1][1]) )
//                        &&
//                        (!(mtx[0][1] == mtx[0][2] && mtx[0][2] == mtx[1][2] && mtx[1][2] == mtx[0][1] && mtx[0][1] != mtx[1][1]) &&
//                         !(mtx[0][2] == mtx[1][2] && mtx[1][2] == mtx[1][1] && mtx[1][1] == mtx[0][2] && mtx[0][2] != mtx[0][1]) &&
//                         !(mtx[1][2] == mtx[1][1] && mtx[1][1] == mtx[0][1] && mtx[0][1] == mtx[1][2] && mtx[1][2] != mtx[0][2]) &&
//                         !(mtx[1][1] == mtx[0][1] && mtx[0][1] == mtx[0][2] && mtx[0][2] == mtx[1][1] && mtx[1][1] != mtx[1][2]) )
//                        &&
//                        (!(mtx[1][0] == mtx[1][1] && mtx[1][1] == mtx[2][1] && mtx[2][1] == mtx[1][0] && mtx[1][0] != mtx[2][0]) &&
//                         !(mtx[1][1] == mtx[2][1] && mtx[2][1] == mtx[2][0] && mtx[2][0] == mtx[1][1] && mtx[1][1] != mtx[1][0]) &&
//                         !(mtx[2][1] == mtx[2][0] && mtx[2][0] == mtx[1][0] && mtx[1][0] == mtx[2][1] && mtx[2][1] != mtx[1][1]) &&
//                         !(mtx[2][0] == mtx[1][0] && mtx[1][0] == mtx[1][1] && mtx[1][1] == mtx[2][0] && mtx[2][0] != mtx[2][1]) )
//                        &&
//                        (!(mtx[1][1] == mtx[1][2] && mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[1][1] && mtx[1][1] != mtx[2][1]) &&
//                         !(mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][2] && mtx[1][2] != mtx[1][1]) &&
//                         !(mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][1] && mtx[1][1] == mtx[2][2] && mtx[2][2] != mtx[1][2]) &&
//                         !(mtx[2][1] == mtx[1][1] && mtx[1][1] == mtx[1][2] && mtx[1][2] == mtx[2][1] && mtx[2][1] != mtx[2][2]) )
//                        &&
//                        //"L" STACCATA
//                        (!(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][0] && mtx[0][1] == mtx[2][0] && mtx[0][0] != mtx[2][1]) &&
//                         !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][1] && mtx[0][1] == mtx[2][1] && mtx[0][0] != mtx[2][0]) &&
//                         !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[0][2] == mtx[2][1] && mtx[0][1] != mtx[2][2]) &&
//                         !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[0][2] == mtx[2][2] && mtx[0][1] != mtx[2][1]) )
//                        &&
//                        (!(mtx[0][2] == mtx[1][2] && mtx[0][2] == mtx[0][0] && mtx[1][2] == mtx[0][0] && mtx[0][2] != mtx[1][0]) &&
//                         !(mtx[0][2] == mtx[1][2] && mtx[0][2] == mtx[1][0] && mtx[1][2] == mtx[1][0] && mtx[0][2] != mtx[0][0]) &&
//                         !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[1][0] && mtx[2][2] == mtx[1][0] && mtx[1][2] != mtx[2][0]) &&
//                         !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[2][0] && mtx[2][2] == mtx[2][0] && mtx[1][2] != mtx[1][0]) )
//                        &&
//                        (!(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][0] && mtx[2][1] == mtx[0][0] && mtx[2][0] != mtx[0][1]) &&
//                         !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1] && mtx[2][0] != mtx[0][0]) &&
//                         !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1] && mtx[2][1] != mtx[0][2]) &&
//                         !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[2][2] == mtx[0][2] && mtx[2][1] != mtx[0][1]) )
//                        &&
//                        (!(mtx[0][0] == mtx[1][0] && mtx[0][0] == mtx[0][2] && mtx[1][0] == mtx[0][2] && mtx[0][0] != mtx[1][2]) &&
//                         !(mtx[0][0] == mtx[1][0] && mtx[0][0] == mtx[1][2] && mtx[1][0] == mtx[1][2] && mtx[0][0] != mtx[0][2]) &&
//                         !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[1][2] && mtx[2][0] == mtx[1][2] && mtx[1][0] != mtx[2][2]) &&
//                         !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[2][2] && mtx[2][0] == mtx[2][2] && mtx[1][0] != mtx[1][2]) )
//                    ) { // END FORZA PATTERN NEGATIVO


                    // PATTERN 1.1 (x7)
//                    if(
//                            (bitCentrale != mtx[0][0] && bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[1][0] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][2]) &&
//
//                            //3 VERTICI
//                             !(mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[0][0] && mtx[0][0] != mtx[2][0]) &&
//                             !(mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][2] && mtx[0][2] != mtx[0][0]) &&
//                             !(mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[2][2] && mtx[2][2] != mtx[0][2]) &&
//                             !(mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][0] && mtx[2][0] != mtx[2][2]) &&
//                            //"L" UNITA
//                             !(mtx[1][0] == mtx[0][0] && mtx[0][0] == mtx[0][1] && mtx[0][1] == mtx[1][0]) &&
//
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][2] == mtx[1][2] && mtx[1][2] == mtx[0][1]) &&
//
//                             !(mtx[2][1] == mtx[2][0] && mtx[2][0] == mtx[1][0] && mtx[1][0] == mtx[2][1]) &&
//
//                             !(mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][2]) &&
//                            //"L" STACCATA
//                             !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][0] && mtx[0][1] == mtx[2][0] && mtx[0][0] != mtx[2][1]) &&
//                             !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][1] && mtx[0][1] == mtx[2][1] && mtx[0][0] != mtx[2][0]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[0][2] == mtx[2][1] && mtx[0][1] != mtx[2][2]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[0][2] == mtx[2][2] && mtx[0][1] != mtx[2][1]) &&
//
//                             !(mtx[0][2] == mtx[1][2] && mtx[0][2] == mtx[0][0] && mtx[1][2] == mtx[0][0] && mtx[0][2] != mtx[1][0]) &&
//                             !(mtx[0][2] == mtx[1][2] && mtx[0][2] == mtx[1][0] && mtx[1][2] == mtx[1][0] && mtx[0][2] != mtx[0][0]) &&
//                             !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[1][0] && mtx[2][2] == mtx[1][0] && mtx[1][2] != mtx[2][0]) &&
//                             !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[2][0] && mtx[2][2] == mtx[2][0] && mtx[1][2] != mtx[1][0]) &&
//
//                             !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][0] && mtx[2][1] == mtx[0][0] && mtx[2][0] != mtx[0][1]) &&
//                             !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1] && mtx[2][0] != mtx[0][0]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1] && mtx[2][1] != mtx[0][2]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[2][2] == mtx[0][2] && mtx[2][1] != mtx[0][1]) &&
//
//                             !(mtx[0][0] == mtx[1][0] && mtx[0][0] == mtx[0][2] && mtx[1][0] == mtx[0][2] && mtx[0][0] != mtx[1][2]) &&
//                             !(mtx[0][0] == mtx[1][0] && mtx[0][0] == mtx[1][2] && mtx[1][0] == mtx[1][2] && mtx[0][0] != mtx[0][2]) &&
//                             !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[1][2] && mtx[2][0] == mtx[1][2] && mtx[1][0] != mtx[2][2]) &&
//                             !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[2][2] && mtx[2][0] == mtx[2][2] && mtx[1][0] != mtx[1][2])
//                    ) {

                    // PATTERN 2.1 (x28 / 4 = x7)
//                    if(
//                            (bitCentrale != mtx[0][0] && bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][2] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][0]) &&
//                             //3 VERTICI
//                             !(mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[0][0] && mtx[0][0] != mtx[2][0]) &&
//                             !(mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][2] && mtx[0][2] != mtx[0][0]) &&
//                             !(mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[2][2] && mtx[2][2] != mtx[0][2]) &&
//                             !(mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][0] && mtx[2][0] != mtx[2][2]) &&
//
//                             //"L" UNITA
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][2] == mtx[1][2] && mtx[1][2] == mtx[0][1]) &&
//                             !(mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][2]) &&
//
//                             //"L" STACCATA
//                             !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][0] && mtx[0][1] == mtx[2][0] && mtx[0][0] != mtx[2][1]) &&
//                             !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][1] && mtx[0][1] == mtx[2][1] && mtx[0][0] != mtx[2][0]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[0][2] == mtx[2][1] && mtx[0][1] != mtx[2][2]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[0][2] == mtx[2][2] && mtx[0][1] != mtx[2][1]) &&
//
//                             !(mtx[0][2] == mtx[1][2] && mtx[0][2] == mtx[0][0] && mtx[1][2] == mtx[0][0]) &&
//                             !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[2][0] && mtx[2][2] == mtx[2][0]) &&
//
//                             !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][0] && mtx[2][1] == mtx[0][0] && mtx[2][0] != mtx[0][1]) &&
//                             !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1] && mtx[2][0] != mtx[0][0]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1] && mtx[2][1] != mtx[0][2]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[2][2] == mtx[0][2] && mtx[2][1] != mtx[0][1])
//
//                    ) {

                    // PATTERN 2.2 (x12 / 4 = x3)
//                    if(
//                                (bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[1][0] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][2]) &&
//                                //3 VERTICI
//                                !(mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][2]) &&
//
//                                //"L" UNITA
//                                !(mtx[0][1] == mtx[0][2] && mtx[0][2] == mtx[1][2] && mtx[1][2] == mtx[0][1]) &&
//                                !(mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][2]) &&
//                                !(mtx[2][0] == mtx[1][0] && mtx[1][0] == mtx[2][1] && mtx[2][1] == mtx[2][0]) &&
//
//                                //"L" STACCATA
//                                !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[0][2] == mtx[2][1] && mtx[0][1] != mtx[2][2]) &&
//                                !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[0][2] == mtx[2][2] && mtx[0][1] != mtx[2][1]) &&
//
//                                !(mtx[0][2] == mtx[1][2] && mtx[0][2] == mtx[1][0] && mtx[1][2] == mtx[1][0]) &&
//                                !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[1][0] && mtx[2][2] == mtx[1][0] && mtx[1][2] != mtx[2][0]) &&
//                                !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[2][0] && mtx[2][2] == mtx[2][0] && mtx[1][2] != mtx[1][0]) &&
//
//                                !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1]) &&
//                                !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1] && mtx[2][1] != mtx[0][2]) &&
//                                !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[2][2] == mtx[0][2] && mtx[2][1] != mtx[0][1]) &&
//
//                                !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[1][2] && mtx[2][0] == mtx[1][2] && mtx[1][0] != mtx[2][2]) &&
//                                !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[2][2] && mtx[2][0] == mtx[2][2] && mtx[1][0] != mtx[1][2])
//
//                    ) {

                    // PATTERN 3.1 (x16 / 2 = x8)
//                    if(
//                            (bitCentrale != mtx[0][0] && bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1]  && bitCentrale != mtx[2][2]) &&
//                             //3 VERTICI
//                             !(mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[0][0] && mtx[0][0] != mtx[2][0]) &&
//                             !(mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][2] && mtx[0][2] != mtx[0][0]) &&
//                             !(mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[2][2] && mtx[2][2] != mtx[0][2]) &&
//                             !(mtx[2][0] == mtx[0][0] && mtx[0][0] == mtx[0][2] && mtx[0][2] == mtx[2][0] && mtx[2][0] != mtx[2][2]) &&
//
//                             //"L" STACCATA
//                             !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][0] && mtx[0][1] == mtx[2][0] && mtx[0][0] != mtx[2][1]) &&
//                             !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][1] && mtx[0][1] == mtx[2][1] && mtx[0][0] != mtx[2][0]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[0][2] == mtx[2][1] && mtx[0][1] != mtx[2][2]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[0][2] == mtx[2][2] && mtx[0][1] != mtx[2][1]) &&
//
//                             !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][0] && mtx[2][1] == mtx[0][0] && mtx[2][0] != mtx[0][1]) &&
//                             !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1] && mtx[2][0] != mtx[0][0]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1] && mtx[2][1] != mtx[0][2]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[2][2] == mtx[0][2] && mtx[2][1] != mtx[0][1])
//
//                    ) {

                    // PATTERN 3.2 (x56 / 8 = x7)
//                    if(
//                            (bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[1][0] && bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1]  && bitCentrale != mtx[2][2]) &&
//                            //3 VERTICI
//                            !(mtx[0][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[0][2]) &&
//
//                            //"L" UNITA
//                            !(mtx[2][1] == mtx[2][0] && mtx[2][0] == mtx[1][0] && mtx[1][0] == mtx[2][1]) &&
//
//                            //"L" STACCATA
//                            !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[0][2] == mtx[2][1] && mtx[0][1] != mtx[2][2]) &&
//                            !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[0][2] == mtx[2][2] && mtx[0][1] != mtx[2][1]) &&
//
//                            !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1] && mtx[2][1] != mtx[0][2]) &&
//                            !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[2][2] == mtx[0][2] && mtx[2][1] != mtx[0][1]) &&
//
//                            !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[2][2] && mtx[2][0] == mtx[2][2]) &&
//                            !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1])
//
//                    ) {

                    // PATTERN 3.3 (x28 / 4 = x7)
//                    if(
//                            (bitCentrale != mtx[0][1] && bitCentrale != mtx[1][0] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1]  && bitCentrale != mtx[2][2]) &&
//
//                            //"L" UNITA
//                            !(mtx[2][1] == mtx[2][0] && mtx[2][0] == mtx[1][0] && mtx[1][0] == mtx[2][1]) &&
//                            !(mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][2]) &&
//
//                            //"L" STACCATA
//                            !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[1][2] && mtx[2][0] == mtx[1][2] && mtx[1][0] != mtx[2][2]) &&
//                            !(mtx[1][0] == mtx[2][0] && mtx[1][0] == mtx[2][2] && mtx[2][0] == mtx[2][2] && mtx[1][0] != mtx[1][2]) &&
//
//                            !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[1][0] && mtx[2][2] == mtx[1][0] && mtx[1][2] != mtx[2][0]) &&
//                            !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[2][0] && mtx[2][2] == mtx[2][0] && mtx[1][2] != mtx[1][0]) &&
//
//                            !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1]) &&
//                            !(mtx[2][0] == mtx[2][1] && mtx[2][0] == mtx[0][1] && mtx[2][1] == mtx[0][1])
//
//                    ) {

                    // PATTERN 3.4 (x20 / 2 = x10)
//                    if(
//                            (bitCentrale != mtx[0][0] && bitCentrale != mtx[0][1] && bitCentrale != mtx[1][0] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][1]  && bitCentrale != mtx[2][2]) &&
//
//                            //"L" UNITA
//                            !(mtx[0][0] == mtx[0][1] && mtx[0][1] == mtx[1][0] && mtx[1][0] == mtx[0][0]) &&
//                            !(mtx[2][2] == mtx[2][1] && mtx[2][1] == mtx[1][2] && mtx[1][2] == mtx[2][2]) &&
//
//                            //"L" STACCATA
//                            !(mtx[0][0] == mtx[0][1] && mtx[0][0] == mtx[2][1] && mtx[0][1] == mtx[2][1]) &&
//
//                            !(mtx[1][2] == mtx[2][2] && mtx[1][2] == mtx[1][0] && mtx[2][2] == mtx[1][0]) &&
//
//                            !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[2][2] == mtx[0][1]) &&
//
//                            !(mtx[0][0] == mtx[1][0] && mtx[0][0] == mtx[1][2] && mtx[1][0] == mtx[1][2])
//
//                    ) {

                    // PATTERN 4.1 (x28 / 4 = x7)
//                    if(
//                            (bitCentrale != mtx[0][2] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][2] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][0]) &&
//                             !(mtx[0][2] == mtx[2][2] && mtx[2][0] == mtx[2][2] && mtx[2][0] == mtx[0][2]) &&
//                             !(mtx[1][2] == mtx[2][2] && mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[1][2]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][2] == mtx[0][2] && mtx[0][2] == mtx[2][1]) &&
//                             !(mtx[1][2] == mtx[2][2] && mtx[2][2] == mtx[2][0] && mtx[2][0] == mtx[1][2])
//                    ) {

                    // PATTERN 4.2 (x32 / 4 = x8)
//                    if(
//                            (bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[1][0] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][2]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][1] && mtx[2][1] == mtx[0][2] && mtx[0][1] != mtx[2][2]) &&
//                             !(mtx[0][1] == mtx[0][2] && mtx[0][1] == mtx[2][2] && mtx[2][2] == mtx[0][2] && mtx[0][1] != mtx[2][1]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][1] && mtx[0][1] == mtx[2][2] && mtx[2][1] != mtx[0][2]) &&
//                             !(mtx[2][1] == mtx[2][2] && mtx[2][1] == mtx[0][2] && mtx[0][2] == mtx[2][2] && mtx[2][1] != mtx[0][1])
//                    ) {

                    // PATTERN 5.1 - NECESSARIO/SUFFICIENTE (x32 / 4 = x8)
//                    if(
//                       (bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2] && bitCentrale != mtx[1][0] && bitCentrale != mtx[2][0]) ||
//                       (bitCentrale != mtx[0][0] && bitCentrale != mtx[0][1] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][2]) ||
//                       (bitCentrale != mtx[0][2] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1]) ||
//                       (bitCentrale != mtx[0][0] && bitCentrale != mtx[1][0] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][2])
//                    ){

                    // PATTERN 5.2 - NECESSARIO/SUFFICIENTE (x8)
//                    if (bitCentrale != mtx[0][1] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][1] && bitCentrale != mtx[1][0]) {

                    // PATTERN 6.1 - NECESSARIO/SUFFICIENTE (x16 / 4 = x4)
//                    if(
//                       (bitCentrale != mtx[0][0] && bitCentrale != mtx[0][1] && bitCentrale != mtx[0][2]) ||
//                       (bitCentrale != mtx[0][0] && bitCentrale != mtx[1][0] && bitCentrale != mtx[2][0]) ||
//                       (bitCentrale != mtx[0][2] && bitCentrale != mtx[1][2] && bitCentrale != mtx[2][2]) ||
//                       (bitCentrale != mtx[2][0] && bitCentrale != mtx[2][1] && bitCentrale != mtx[2][2])
//                    ){


                        if (bitCentrale == bit1) {
                            for (int r = 0; r < NUM; r++) {
                                for (int c = 0; c < NUM; c++) {
                                    if (mtx[r][c] == bit2) {
                                        countBit2++;
                                    } else if (mtx[r][c] == bit3) {
                                        countBit3++;
                                    }
                                }
                            }
                        } else if (bitCentrale == bit2) {
                            for (int r = 0; r < NUM; r++) {
                                for (int c = 0; c < NUM; c++) {
                                    if (mtx[r][c] == bit1) {
                                        countBit1++;
                                    } else if (mtx[r][c] == bit3) {
                                        countBit3++;
                                    }
                                }
                            }
                        } else if (bitCentrale == bit3) {
                            for (int r = 0; r < NUM; r++) {
                                for (int c = 0; c < NUM; c++) {
                                    if (mtx[r][c] == bit1) {
                                        countBit1++;
                                    } else if (mtx[r][c] == bit2) {
                                        countBit2++;
                                    }
                                }
                            }
                        }

                        for (int r = 0; r < NUM; r++) {
                            if (mtx[r][0] != mtx[r][1] && mtx[r][0] != mtx[r][2] && mtx[r][1] != mtx[r][2]) {
                                countRC3bit++;
                            }
                        }

                        for (int c = 0; c < NUM; c++) {
                            if (mtx[0][c] != mtx[1][c] && mtx[0][c] != mtx[2][c] && mtx[1][c] != mtx[2][c]) {
                                countRC3bit++;
                            }
                        }

                        for (int r = 0; r < NUM; r++) {
                            if (mtx[r][0] == mtx[r][1] && mtx[r][0] == mtx[r][2] && mtx[r][1] == mtx[r][2]) {
                                countStraight++;
                            }
                        }

                        for (int c = 0; c < NUM; c++) {
                            if (mtx[0][c] == mtx[1][c] && mtx[0][c] == mtx[2][c] && mtx[1][c] == mtx[2][c]) {
                                countStraight++;
                            }
                        }

                        for (int r = 0; r < NUM; r++) {
                            if ((mtx[r][0] != mtx[r][1] && mtx[r][1] == mtx[r][2]) ||
                                (mtx[r][0] != mtx[r][1] && mtx[r][0] == mtx[r][2]) ||
                                (mtx[r][0] == mtx[r][1] && mtx[r][0] != mtx[r][2])) {
                                count1for2++;
                            }
                        }

                        for (int c = 0; c < NUM; c++) {
                            if ((mtx[0][c] != mtx[1][c] && mtx[1][c] == mtx[2][c]) ||
                                (mtx[0][c] != mtx[1][c] && mtx[0][c] == mtx[2][c]) ||
                                (mtx[0][c] == mtx[1][c] && mtx[0][c] != mtx[2][c])) {
                                count1for2++;
                            }
                        }


//                        if (countRC3bit == 0 && countStraight == 2 && count1for2 == 4) { //TIPO RC




//                            if ( //if countBit1 2 3
//                                    (countBit2 == 2 && countBit3 == 6) || (countBit2 == 6 && countBit3 == 2) ||
//                                    (countBit1 == 2 && countBit3 == 6) || (countBit1 == 6 && countBit3 == 2) ||
//                                    (countBit1 == 2 && countBit2 == 6) || (countBit1 == 6 && countBit2 == 2)

//                                                        (countBit2 == 4 && countBit3 == 4) ||
//                                                        (countBit1 == 4 && countBit3 == 4) ||
//                                                        (countBit1 == 4 && countBit2 == 4)
//
//
//
//                                    ) {

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

                                /********************************************/
                                /********************************************/
                                mtxType = checkMtx(mtx, mtx2, arrSign2); //controllo MATRICI
                                /********************************************/
                                /********************************************/
                                int arrNumCount[] = {0, 0, 0};
                                //                sumMtx(mtx, arrNumSum, arrNumCount, arrHowMany012, arrDistribution); //spostare in uno dei rami if seguenti per indagare le singole tipologie
                                if (mtxType > 999 && mtxType < 1100) { //NON CP - VIETATA 3x3
//                                if (mtxType > 1099 && mtxType < 1200) { //NON CP - VIETATA 3x3
//                                if (mtxType > 1199 && mtxType < 1300) { //NON CP - VIETATA 3x3
//                                if (mtxType > 1399 && mtxType < 1500) { //NON CP - VIETATA 3x3
//                                if (mtxType > 1499 && mtxType < 1600) { //NON CP - VIETATA 3x3
//                                if (mtxType > 1799 && mtxType < 1900) { //NON CP - VIETATA 3x3
//                                if (mtxType > 2099 && mtxType < 2200) { //NON CP - VIETATA 3x3
//                                if (mtxType > 2199 && mtxType < 2300) { //NON CP - VIETATA 3x3
//                                if (mtxType > 2499 && mtxType < 2600) { //NON CP - VIETATA 3x3
//                                if (mtxType > 3099 && mtxType < 3200) { //NON CP - VIETATA 3x3
//                                if (mtxType > 3199 && mtxType < 3300) { //NON CP - VIETATA 3x3
//                                if (mtxType > 3499 && mtxType < 3600) { //NON CP - VIETATA 3x3
//                                if (mtxType > 4099 && mtxType < 4200) { //NON CP - VIETATA 3x3
//                                if (mtxType > 4199 && mtxType < 4300) { //NON CP - VIETATA 3x3
//                                if (mtxType > 4499 && mtxType < 4600) { //NON CP - VIETATA 3x3
//                                if (mtxType > 5099 && mtxType < 5200) { //NON CP - VIETATA 3x3
//                                if (mtxType > 5199 && mtxType < 5300) { //NON CP - VIETATA 3x3
//                                if (mtxType > 5499 && mtxType < 5600) { //NON CP - VIETATA 3x3
//                                if (mtxType > 6099 && mtxType < 6200) { //NON CP - VIETATA 3x3
//                                if (mtxType > 6199 && mtxType < 6300) { //NON CP - VIETATA 3x3
//                                if (mtxType > 6499 && mtxType < 6600) { //NON CP - VIETATA 3x3

                                    cont_ncp_3x3++; //0 - NON CP - vietata o monocromatica
                                    printMtxToFile(mtx, mtx2, logPtr21, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale,
                                                   cont_ncp_3x3, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                                   countCoppiaCol, mtxType);


                                    //                    if(arrHowMany012[0] == 2 && arrHowMany012[1] == 3 && arrHowMany012[2] == 4) {
                                    //                        printMtxToFile( mtx, logPtr21, cont_Mtx, mtxType );
                                    //                    }
                                } else if (mtxType == 11) { //NON CP - VIETATA 2x2

                                    cont_ncp_2x2++;
                                    printMtxToFile(mtx, mtx2, logPtr22, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale,
                                                   cont_ncp_2x2, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                                   countCoppiaCol, sign2);


                                } else if (mtxType == 12) { //NON CP - VIETATA 2x3

                                    cont_ncp_2x3++;
                                    printMtxToFile(mtx, mtx2, logPtr23, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale,
                                                   cont_ncp_2x2, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                                   countCoppiaCol, sign2);

                                } else if (mtxType == 13) { //NON CP - VIETATA 3x2

                                    cont_ncp_3x2++;

                                    printMtxToFile(mtx, mtx2, logPtr24, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale,
                                                   cont_ncp_2x2, countRC3bit, countStraight, count1for2, countCoppiaRow,
                                                   countCoppiaCol, sign2);

                                } else { //CP - ammessa (perchè NON vietata)

                                    cont_cp_NON_vietate++;
                                    cont_cp++; //1 - CP - ammessa (perchè NON vietata)
                                    idx3++;

                                    //                        if(sumMtx(mtx, arrNumSum) == 15) {
                                    printMtxToFile(mtx, mtx2, logPtr3, cont_Mtx, mtxType, bit1, bit2, bit3, bitCentrale, idx3,
                                                   countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol, sign2);
                                    //
                                    //                        }

                                    //                        if(arrHowMany012[0] == 3 && arrHowMany012[1] == 3 && arrHowMany012[2] == 3) {
                                    //                            printMtxToFile( mtx, logPtr3, cont_Mtx, mtxType );
                                    //                        }



                                }
                                //stampa TUTTE LE MATRICI
                                printMtxToFile(mtx, mtx2, logPtr1, cont_MtxNoDuplicate, mtxType, bit1, bit2, bit3, bitCentrale, idx,
                                               countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol, sign2);

                                //                    }
                                //                    } //PATTERN 2 DIAGONALE/DRITTO

                                //                        } // countCoppiaRow countCoppiaCol
//                            } //END if countBit1 2 3
//                        } //END tipo RC
//                    } //END FORZA PATTERN
                } //END  //NUMERO OCCORRENZE BIT CENTRALE
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

void initMtx2( int mtx[ NUM ][ NUM ] ) {

    int r, c;

    for ( r = 0; r < NUM; r++ ) {
        for ( c = 0; c < NUM; c++ ) {
            mtx[ r ][ c ] = 13;
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


int checkMtx(int mtx[ NUM ][ NUM ], int mtx2[ NUM ][ NUM ], int* arrSign2) {
//    if (checkMtx2x3(mtx) == 1) {
//        return 12; //VIETATA TRUE - NON CP
//    }
//    if (checkMtx3x2(mtx) == 1) {
//        return 13; //VIETATA TRUE - NON CP
//    }
//    if (checkMtx2x2(mtx) == 1) {
//        return 11; //VIETATA TRUE - NON CP
//    }
    if (checkMtx3x3(mtx, mtx2) != 0) {

        arrSign2[checkMtx3x3(mtx, mtx2)]++;

        if(arrSign2[checkMtx3x3(mtx, mtx2)] != 1) return 1;

        return checkMtx3x3(mtx, mtx2); //VIETATA TRUE - NON CP

    }

    return 1; //CP TRUE - AMMESSA (NON VIETATA)

}

int checkMtx3x3(int mtx[ NUM ][ NUM ], int mtx2[ NUM ][ NUM ]) {

    int equivR = 0;
    int equivC = 0;
    char strEquivR[3] = {'\0'};
    char strEquivC[3] = {'\0'};
    char sign[6] = {'\0'};
    int intSign;
    int R1 = 0;
    int R2 = 0;
    int C1 = 0;
    int C2 = 0;


    initMtx2(mtx2);

//    if (checkMtxMono3x3(mtx) == 1) {
//        return 2; //MONO 3x3 TRUE
//    }
    //if NO MONOCROMATICA

    //check row
    for(int i = 0; i <= 2; i++) {

        if(mtx[0][i] == mtx[1][i]) { //relaz in prime 2 righe
            if (R1 == 1 && R2 == 1) goto endR;
            R1 = 1;
            for(int j = 0; j <= 2; j++) {
                if(mtx[1][j] == mtx[2][j]) { //relaz in 2a e 3a riga OPPURE in 1a e 3a riga
                    if (R1 == 1 && R2 == 1) goto endR;
                    R2 = 1;
                    mtx2[0][i] = mtx[0][i] + 10;
                    mtx2[1][i] = mtx[1][i] + 10;
                    mtx2[1][j] = mtx[1][j] + 10;
                    mtx2[2][j] = mtx[2][j] + 10;
                    if (i == 0 && j == 0) equivR = 10;
                    if (i == 0 && j == 1) equivR = 11;
                    if (i == 0 && j == 2) equivR = 12;
                    if (i == 1 && j == 0) equivR = 13;
                    if (i == 1 && j == 1) equivR = 14;
                    if (i == 1 && j == 2) equivR = 15;
                    if (i == 2 && j == 0) equivR = 16;
                    if (i == 2 && j == 1) equivR = 17;
                    if (i == 2 && j == 2) equivR = 18;
                } else if (mtx[0][j] == mtx[2][j]) {
                    if (R1 == 1 && R2 == 1) goto endR;
                    R2 = 1;
                    mtx2[0][i] = mtx[0][i] + 10;
                    mtx2[1][i] = mtx[1][i] + 10;
                    mtx2[0][j] = mtx[0][j] + 10;
                    mtx2[2][j] = mtx[2][j] + 10;
                    if (i == 0 && j == 0) equivR = 20;
                    if (i == 0 && j == 1) equivR = 21;
                    if (i == 0 && j == 2) equivR = 22;
                    if (i == 1 && j == 0) equivR = 23;
                    if (i == 1 && j == 1) equivR = 24;
                    if (i == 1 && j == 2) equivR = 25;
                    if (i == 2 && j == 0) equivR = 26;
                    if (i == 2 && j == 1) equivR = 27;
                    if (i == 2 && j == 2) equivR = 28;
                }
            }
        } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
            if (R1 == 1 && R2 == 1) goto endR;
            R1 = 1;
            for(int k = 0; k <= 2; k++) {
                if(mtx[0][k] == mtx[1][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                    if (R1 == 1 && R2 == 1) goto endR;
                    R2 = 1;
                    mtx2[1][i] = mtx[1][i] + 10;
                    mtx2[2][i] = mtx[2][i] + 10;
                    mtx2[0][k] = mtx[0][k] + 10;
                    mtx2[1][k] = mtx[1][k] + 10;
                    if (i == 0 && k == 0) equivR = 30;
                    if (i == 0 && k == 1) equivR = 31;
                    if (i == 0 && k == 2) equivR = 32;
                    if (i == 1 && k == 0) equivR = 33;
                    if (i == 1 && k == 1) equivR = 34;
                    if (i == 1 && k == 2) equivR = 35;
                    if (i == 2 && k == 0) equivR = 36;
                    if (i == 2 && k == 1) equivR = 37;
                    if (i == 2 && k == 2) equivR = 38;
                } else if (mtx[0][k] == mtx[2][k]) {
                    if (R1 == 1 && R2 == 1) goto endR;
                    R2 = 1;
                    mtx2[1][i] = mtx[1][i] + 10;
                    mtx2[2][i] = mtx[2][i] + 10;
                    mtx2[0][k] = mtx[0][k] + 10;
                    mtx2[2][k] = mtx[2][k] + 10;
                    if (i == 0 && k == 0) equivR = 40;
                    if (i == 0 && k == 1) equivR = 41;
                    if (i == 0 && k == 2) equivR = 42;
                    if (i == 1 && k == 0) equivR = 43;
                    if (i == 1 && k == 1) equivR = 44;
                    if (i == 1 && k == 2) equivR = 45;
                    if (i == 2 && k == 0) equivR = 46;
                    if (i == 2 && k == 1) equivR = 47;
                    if (i == 2 && k == 2) equivR = 48;
                }
            }
        }
        else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
            if (R1 == 1 && R2 == 1) goto endR;
            R1 = 1;

            for(int ku = 0; ku <= 2; ku++) {
                if(mtx[0][ku] == mtx[1][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                    if (R1 == 1 && R2 == 1) goto endR;
                    R2 = 1;
                    mtx2[0][i] = mtx[0][i] + 10;
                    mtx2[2][i] = mtx[2][i] + 10;
                    mtx2[0][ku] = mtx[0][ku] + 10;
                    mtx2[1][ku] = mtx[1][ku] + 10;
                    if (i == 0 && ku == 0) equivR = 50;
                    if (i == 0 && ku == 1) equivR = 51;
                    if (i == 0 && ku == 2) equivR = 52;
                    if (i == 1 && ku == 0) equivR = 53;
                    if (i == 1 && ku == 1) equivR = 54;
                    if (i == 1 && ku == 2) equivR = 55;
                    if (i == 2 && ku == 0) equivR = 56;
                    if (i == 2 && ku == 1) equivR = 57;
                    if (i == 2 && ku == 2) equivR = 58;
                } else if (mtx[1][ku] == mtx[2][ku]) {
                    if (R1 == 1 && R2 == 1) goto endR;
                    R2 = 1;
                    mtx2[0][i] = mtx[0][i] + 10;
                    mtx2[2][i] = mtx[2][i] + 10;
                    mtx2[1][ku] = mtx[1][ku] + 10;
                    mtx2[2][ku] = mtx[2][ku] + 10;
                    if (i == 0 && ku == 0) equivR = 60;
                    if (i == 0 && ku == 1) equivR = 61;
                    if (i == 0 && ku == 2) equivR = 62;
                    if (i == 1 && ku == 0) equivR = 63;
                    if (i == 1 && ku == 1) equivR = 64;
                    if (i == 1 && ku == 2) equivR = 65;
                    if (i == 2 && ku == 0) equivR = 66;
                    if (i == 2 && ku == 1) equivR = 67;
                    if (i == 2 && ku == 2) equivR = 68;
                }
            }
        }
    } //end check row

    endR:

    //check col
    if(equivR != 0) {
        for(int q = 0; q <= 2; q++) {
            if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                if (C1 == 1 && C2 == 1) goto endC;
                C1 = 1;

                for(int w = 0; w <= 2; w++) {
                    if(mtx[w][1] == mtx[w][2]) {
                        if (C1 == 1 && C2 == 1) goto endC;
                        C2 = 1;
                        if (mtx2[q][0] == 13) mtx2[q][0] += mtx[q][0] + 1;
                        if (mtx2[q][1] == 13) mtx2[q][1] += mtx[q][1] + 1;
                        if (mtx2[w][1] == 13) mtx2[w][1] += mtx[w][1] + 1;
                        if (mtx2[w][2] == 13) mtx2[w][2] += mtx[w][2] + 1;
                        mtx2[q][0] = mtx2[q][0] + 100;
                        mtx2[q][1] = mtx2[q][1] + 100;
                        mtx2[w][1] = mtx2[w][1] + 100;
                        mtx2[w][2] = mtx2[w][2] + 100;
                        if (q == 0 && w == 0) equivC = 10;
                        if (q == 0 && w == 1) equivC = 11;
                        if (q == 0 && w == 2) equivC = 12;
                        if (q == 1 && w == 0) equivC = 13;
                        if (q == 1 && w == 1) equivC = 14;
                        if (q == 1 && w == 2) equivC = 15;
                        if (q == 2 && w == 0) equivC = 16;
                        if (q == 2 && w == 1) equivC = 17;
                        if (q == 2 && w == 2) equivC = 18;
                    } else if (mtx[w][0] == mtx[w][2]) {
                        if (C1 == 1 && C2 == 1) goto endC;
                        C2 = 1;
                        if (mtx2[q][0] == 13) mtx2[q][0] += mtx[q][0] + 1;
                        if (mtx2[q][1] == 13) mtx2[q][1] += mtx[q][1] + 1;
                        if (mtx2[w][0] == 13) mtx2[w][0] += mtx[w][0] + 1;
                        if (mtx2[w][2] == 13) mtx2[w][2] += mtx[w][2] + 1;
                        mtx2[q][0] = mtx2[q][0] + 100;
                        mtx2[q][1] = mtx2[q][1] + 100;
                        mtx2[w][0] = mtx2[w][0] + 100;
                        mtx2[w][2] = mtx2[w][2] + 100;
                        if (q == 0 && w == 0) equivC = 20;
                        if (q == 0 && w == 1) equivC = 21;
                        if (q == 0 && w == 2) equivC = 22;
                        if (q == 1 && w == 0) equivC = 23;
                        if (q == 1 && w == 1) equivC = 24;
                        if (q == 1 && w == 2) equivC = 25;
                        if (q == 2 && w == 0) equivC = 26;
                        if (q == 2 && w == 1) equivC = 27;
                        if (q == 2 && w == 2) equivC = 28;
                    }
                }
            } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                if (C1 == 1 && C2 == 1) goto endC;
                C1 = 1;
                for(int e = 0; e <= 2; e++) {
                    if(mtx[e][0] == mtx[e][1]) {
                        if (C1 == 1 && C2 == 1) goto endC;
                        C2 = 1;
                        if (mtx2[q][1] == 13) mtx2[q][1] += mtx[q][1] + 1;
                        if (mtx2[q][2] == 13) mtx2[q][2] += mtx[q][2] + 1;
                        if (mtx2[e][0] == 13) mtx2[e][0] += mtx[e][0] + 1;
                        if (mtx2[e][1] == 13) mtx2[e][1] += mtx[e][1] + 1;
                        mtx2[q][1] = mtx2[q][1] + 100;
                        mtx2[q][2] = mtx2[q][2] + 100;
                        mtx2[e][0] = mtx2[e][0] + 100;
                        mtx2[e][1] = mtx2[e][1] + 100;
                        if (q == 0 && e == 0) equivC = 30;
                        if (q == 0 && e == 1) equivC = 31;
                        if (q == 0 && e == 2) equivC = 32;
                        if (q == 1 && e == 0) equivC = 33;
                        if (q == 1 && e == 1) equivC = 34;
                        if (q == 1 && e == 2) equivC = 35;
                        if (q == 2 && e == 0) equivC = 36;
                        if (q == 2 && e == 1) equivC = 37;
                        if (q == 2 && e == 2) equivC = 38;
                    } else if (mtx[e][0] == mtx[e][2]) {
                        if (C1 == 1 && C2 == 1) goto endC;
                        C2 = 1;
                        if (mtx2[q][1] == 13) mtx2[q][1] += mtx[q][1] + 1;
                        if (mtx2[q][2] == 13) mtx2[q][2] += mtx[q][2] + 1;
                        if (mtx2[e][0] == 13) mtx2[e][0] += mtx[e][0] + 1;
                        if (mtx2[e][2] == 13) mtx2[e][2] += mtx[e][2] + 1;
                        mtx2[q][1] = mtx2[q][1] + 100;
                        mtx2[q][2] = mtx2[q][2] + 100;
                        mtx2[e][0] = mtx2[e][0] + 100;
                        mtx2[e][2] = mtx2[e][2] + 100;
                        if (q == 0 && e == 0) equivC = 40;
                        if (q == 0 && e == 1) equivC = 41;
                        if (q == 0 && e == 2) equivC = 42;
                        if (q == 1 && e == 0) equivC = 43;
                        if (q == 1 && e == 1) equivC = 44;
                        if (q == 1 && e == 2) equivC = 45;
                        if (q == 2 && e == 0) equivC = 46;
                        if (q == 2 && e == 1) equivC = 47;
                        if (q == 2 && e == 2) equivC = 48;
                    }
                }
            }
            else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                if (C1 == 1 && C2 == 1) goto endC;
                C1 = 1;
                for(int ee = 0; ee <= 2; ee++) {
                    if(mtx[ee][0] == mtx[ee][1]) {
                        if (C1 == 1 && C2 == 1) goto endC;
                        C2 = 1;
                        if (mtx2[q][0] == 13) mtx2[q][0] += mtx[q][0] + 1;
                        if (mtx2[q][2] == 13) mtx2[q][2] += mtx[q][2] + 1;
                        if (mtx2[ee][0] == 13) mtx2[ee][0] += mtx[ee][0] + 1;
                        if (mtx2[ee][1] == 13) mtx2[ee][1] += mtx[ee][1] + 1;
                        mtx2[q][0] = mtx2[q][0] + 100;
                        mtx2[q][2] = mtx2[q][2] + 100;
                        mtx2[ee][0] = mtx2[ee][0] + 100;
                        mtx2[ee][1] = mtx2[ee][1] + 100;
                        if (q == 0 && ee == 0) equivC = 50;
                        if (q == 0 && ee == 1) equivC = 51;
                        if (q == 0 && ee == 2) equivC = 52;
                        if (q == 1 && ee == 0) equivC = 53;
                        if (q == 1 && ee == 1) equivC = 54;
                        if (q == 1 && ee == 2) equivC = 55;
                        if (q == 2 && ee == 0) equivC = 56;
                        if (q == 2 && ee == 1) equivC = 57;
                        if (q == 2 && ee == 2) equivC = 58;
                    } else if (mtx[ee][1] == mtx[ee][2]) {
                        if (C1 == 1 && C2 == 1) goto endC;
                        C2 = 1;
                        if (mtx2[q][0] == 13) mtx2[q][0] += mtx[q][0] + 1;
                        if (mtx2[q][2] == 13) mtx2[q][2] += mtx[q][2] + 1;
                        if (mtx2[ee][1] == 13) mtx2[ee][1] += mtx[ee][1] + 1;
                        if (mtx2[ee][2] == 13) mtx2[ee][2] += mtx[ee][2] + 1;
                        mtx2[q][0] = mtx2[q][0] + 100;
                        mtx2[q][2] = mtx2[q][2] + 100;
                        mtx2[ee][1] = mtx2[ee][1] + 100;
                        mtx2[ee][2] = mtx2[ee][2] + 100;
                        if (q == 0 && ee == 0) equivC = 60;
                        if (q == 0 && ee == 1) equivC = 61;
                        if (q == 0 && ee == 2) equivC = 62;
                        if (q == 1 && ee == 0) equivC = 63;
                        if (q == 1 && ee == 1) equivC = 64;
                        if (q == 1 && ee == 2) equivC = 65;
                        if (q == 2 && ee == 0) equivC = 66;
                        if (q == 2 && ee == 1) equivC = 67;
                        if (q == 2 && ee == 2) equivC = 68;
                    }
                }
            }
        }
    } //end check col

    endC:


//    printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
//           mtx2[0][0], mtx2[0][1], mtx2[0][2],
//           mtx2[1][0], mtx2[1][1], mtx2[1][2],
//           mtx2[2][0], mtx2[2][1], mtx2[2][2]);


    if(equivR != 0 && equivC != 0) {


        sprintf(strEquivR, "%d", equivR);
        sprintf(strEquivC, "%d", equivC);

        strcpy(sign, strEquivR);
        strcat(sign, strEquivC);

//        printf("%s\n", sign);
        intSign = atoi(sign);
//        printf("%d\n", intSign);

        return intSign; //VIETATA TRUE - NON CP
    } else {
//        printf("---------------%d | %d\n", equivR, equivC);
        return 0; //AMMESSA - VIETATA FALSE - CP

    }


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

int checkMono2x3_1(int mtx[ NUM ][ NUM ]) {

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

int checkMono2x3_2(int mtx[ NUM ][ NUM ]) {

    //1a 3a RIGA
    for(int ro1 = 0; ro1 <= 2; ro1++) {
        if(ro1 == 1) continue;
        for(int co1 = 0; co1 <= 2; co1++) {
            if(mtx[0][0] != mtx[ro1][co1]) {
                return 0; //no mono
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int checkMono2x3_3(int mtx[ NUM ][ NUM ]) {

    //2a 3a RIGA
    for(int ro1 = 1; ro1 <= 2; ro1++) {
        for(int co1 = 0; co1 <= 2; co1++) {
            if(mtx[1][0] != mtx[ro1][co1]) {
                return 0; //no mono
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int checkMono3x2_1(int mtx[ NUM ][ NUM ]) {

    //1a 2a COL
    for(int ro1 = 0; ro1 <= 2; ro1++) {
        for(int co1 = 0; co1 <= 1; co1++) {
            if(mtx[0][0] != mtx[ro1][co1]) {
                return 0; //no mono
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int checkMono3x2_2(int mtx[ NUM ][ NUM ]) {

    //1a 3a COL
    for(int ro1 = 0; ro1 <= 2; ro1++) {
        for(int co1 = 0; co1 <= 2; co1++) {
            if(co1 == 1) continue;
            if(mtx[0][0] != mtx[ro1][co1]) {
                return 0; //no mono
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int checkMono3x2_3(int mtx[ NUM ][ NUM ]) {

    //2a 3a COL
    for(int ro1 = 0; ro1 <= 2; ro1++) {
        for(int co1 = 1; co1 <= 2; co1++) {
            if(mtx[0][1] != mtx[ro1][co1]) {
                return 0; //no mono
            }
        }
    }

    return 1; //si monocromatica 2x2

}


int checkMono2x2C_AS(int mtx[ NUM ][ NUM ]) {

    //IN ALTO A SX
    for(int ro1 = 0; ro1 <= 1; ro1++) { //check monocromatica 2x2
        for(int co1 = 0; co1 <= 1; co1++) {
            if(mtx[0][0] != mtx[ro1][co1]) {
                return 0;
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int checkMono2x2C_AD(int mtx[ NUM ][ NUM ]) {

    //IN ALTO A DX
    for(int ro2 = 0; ro2 <= 1; ro2++) { //check monocromatica 2x2
        for(int co2 = 1; co2 <= 2; co2++) {
            if(mtx[0][1] != mtx[ro2][co2]) {
                return 0;
            }
        }
    }

    return 1; //si monocromatica 2x2

}

int checkMono2x2C_BS(int mtx[ NUM ][ NUM ]) {

    //IN BASSO A SX
    for(int ro3 = 1; ro3 <= 2; ro3++) { //check monocromatica 2x2
        for(int co3 = 0; co3 <= 1; co3++) {
            if(mtx[1][0] != mtx[ro3][co3]) {
                return 0;
            }
        }
    }

    return 1; //si monocromatica 2x2
}

int checkMono2x2C_BD(int mtx[ NUM ][ NUM ]) {

    //IN BASSO A DX
    for(int ro4 = 1; ro4 <= 2; ro4++) { //check monocromatica 2x2
        for(int co4 = 1; co4 <= 2; co4++) {
            if(mtx[1][1] != mtx[ro4][co4]) {
                return 0;
            }
        }
    }

    return 1; //si monocromatica 2x2
}

int checkMono2x2NC_1(int mtx[ NUM ][ NUM ]) {

    //(1) 1a 2a RIGA | 1a e 3a COL
    for(int r = 0; r <= 1; r++) {
        for(int c = 0; c <= 2; c++) {
            if(c == 1) continue;
            if(mtx[0][0] != mtx[r][c]) {
                return 0;
            }
        }
    } //END 1a 2a RIGA | 1a e 3a COL

    return 1; //si monocromatica 2x2

}

int checkMono2x2NC_2(int mtx[ NUM ][ NUM ]) {

    //(2) 1a 3a RIGA | 1a 2a COL
    for(int r = 0; r <= 2; r++) {
        if(r == 1) continue;
        for(int c = 0; c <= 1; c++) {
            if(mtx[0][0] != mtx[r][c]) {
                return 0;
            }
        }
    } //END 1a 3a RIGA | 1a 2a COL

    return 1; //si monocromatica 2x2

}

int checkMono2x2NC_3(int mtx[ NUM ][ NUM ]) {

    //(3) 1a 3a RIGA | 1a 3a COL
    for(int r = 0; r <= 2; r++) {
        if(r == 1) continue;
        for(int c = 0; c <= 2; c++) {
            if(c == 1) continue;
            if(mtx[0][0] != mtx[r][c]) {
                return 0;
            }
        }
    } //END 1a 3a RIGA | 1a 3a COL

    return 1; //si monocromatica 2x2

}

int checkMono2x2NC_4(int mtx[ NUM ][ NUM ]) {

    //(4) 1a 3a RIGA | 2a 3a COL
    for(int r = 0; r <= 2; r++) {
        if(r == 1) continue;
        for(int c = 1; c <= 2; c++) {
            if(mtx[0][1] != mtx[r][c]) {
                return 0;
            }
        }
    } //END 1a 3a RIGA | 2a 3a COL

    return 1; //si monocromatica 2x2

}

int checkMono2x2NC_5(int mtx[ NUM ][ NUM ]) {

    //(5) 2a 3a RIGA | 1a 3a COL
    for(int r = 1; r <= 2; r++) {
        for(int c = 0; c <= 2; c++) {
            if(c == 1) continue;
            if(mtx[1][0] != mtx[r][c]) {
                return 0;
            }
        }
    } //END 2a 3a RIGA | 1a 3a COL

    return 1; //si monocromatica 2x2

}



int checkMtx2x3(int mtx[ NUM ][ NUM ]) {



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

    //1a 3a RIGA | TUTTE COLONNE
    for(int i = 0; i <= 2; i++) {
        if(mtx[0][i] == mtx[2][i]) {

            for(int q = 0; q <= 2; q++) {
                if(q == 1) continue;
                if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                    for(int w = 0; w <= 2; w++) {
                        if(w == 1) continue;
                        if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                            if(checkMono2x3_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                    for(int e = 0; e <= 2; e++) {
                        if(e == 1) continue;
                        if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                            if(checkMono2x3_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int e = 0; e <= 2; e++) {
                        if(e == 1) continue;
                        if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
                            if(checkMono2x3_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            }


        }
    } //END 1a 3a RIGA | TUTTE COLONNE

    //2a 3a RIGA | TUTTE COLONNE
    for(int i = 0; i <= 2; i++) {
        if(mtx[1][i] == mtx[2][i]) {

            for(int q = 1; q <= 2; q++) {
                if(mtx[q][0] == mtx[q][1]) { //relaz in prime 2 colonne
                    for(int w = 1; w <= 2; w++) {
                        if(mtx[w][1] == mtx[w][2] || mtx[w][0] == mtx[w][2]) {
                            if(checkMono2x3_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[q][1] == mtx[q][2]) { //relaz in 2a e 3a colonna
                    for(int e = 1; e <= 2; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][0] == mtx[e][2]) {
                            if(checkMono2x3_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[q][0] == mtx[q][2]) { //relaz in 1a e 3a colonna - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int e = 1; e <= 2; e++) {
                        if(mtx[e][0] == mtx[e][1] || mtx[e][1] == mtx[e][2]) {
                            if(checkMono2x3_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
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
                            if(checkMono3x2_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
                    for(int k = 0; k <= 1; k++) {
                        if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                            if(checkMono3x2_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int ku = 0; ku <= 1; ku++) {
                        if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                            if(checkMono3x2_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
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
            for(int i = 0; i <= 2; i++) {
                if(i == 1) continue;
                if(mtx[0][i] == mtx[1][i]) { //relaz in prime 2 righe
                    for(int j = 0; j <= 2; j++) {
                        if(j == 1) continue;
                        if(mtx[1][j] == mtx[2][j] || mtx[0][j] == mtx[2][j]) { //relaz in 2a e 3a riga OPPURE in 1a e 3a riga
                            if(checkMono3x2_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
                    for(int k = 0; k <= 2; k++) {
                        if(k == 1) continue;
                        if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                            if(checkMono3x2_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int ku = 0; ku <= 2; ku++) {
                        if(ku == 1) continue;
                        if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                            if(checkMono3x2_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
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
                            if(checkMono3x2_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                } else if(mtx[1][i] == mtx[2][i]) { //relaz in 2a e 3a riga
                    for(int k = 1; k <= 2; k++) {
                        if(mtx[0][k] == mtx[1][k] || mtx[0][k] == mtx[2][k]) { //relaz in prime 2 righe OPPURE in 1a e 3a riga
                            if(checkMono3x2_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
                else if(mtx[0][i] == mtx[2][i]) { //relaz in 1a e 3a riga - RAMO PROBABILMENTE SUPERFLUO - NON CAMBIA RISULTATO
                    for(int ku = 1; ku <= 2; ku++) {
                        if(mtx[0][ku] == mtx[1][ku] || mtx[1][ku] == mtx[2][ku]) { //relaz in prime 2 righe OPPURE in 2a e 3a riga
                            if(checkMono3x2_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
                        }
                    }
                }
            } //end check row

        }
    } //END TUTTE RIGHE | 2a 3a COL

    return 0; //VIETATA FALSE - CP

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

//
//    //MTX 2x2 CONTIGUE
//    //IN ALTO A SX
//    for(int i = 0; i <= 1; i++) {
//        if(mtx[0][i] == mtx[1][i]) {
//            for(int j = 0; j <= 1; j++) {
//                if(mtx[j][0] == mtx[j][1]) {
//                    if(checkMono2x2C_AS(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END IN ALTO A SX
//
//    //IN ALTO A DX
//    for(int i = 1; i <= 2; i++) {
//        if(mtx[0][i] == mtx[1][i]) {
//            for(int j = 0; j <= 1; j++) {
//                if(mtx[j][1] == mtx[j][2]) {
//                    if(checkMono2x2C_AD(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END IN ALTO A DX
//
//    //IN BASSO A SX
//    for(int i = 0; i <= 1; i++) {
//        if(mtx[1][i] == mtx[2][i]) {
//            for(int j = 1; j <= 2; j++) {
//                if(mtx[j][0] == mtx[j][1]) {
//                    if(checkMono2x2C_BS(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END IN BASSO A SX
//
//    //IN BASSO A DX
//    for(int i = 1; i <= 2; i++) {
//        if(mtx[1][i] == mtx[2][i]) {
//            for(int j = 1; j <= 2; j++) {
//                if(mtx[j][1] == mtx[j][2]) {
//                    if(checkMono2x2C_BD(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END IN BASSO A DX
//
//
//// [0][0]   [0][1]  [0][2]
//// [1][0]   [1][1]  [1][2]
//// [2][0]   [2][1]  [2][2]
//
//    //MTX 2x2 NON CONTIGUE
//    //(1) 1a 2a RIGA | 1a 3a COL
//    for(int i = 0; i <= 2; i++) {
//        if(i == 1) continue;
//        if(mtx[0][i] == mtx[1][i]) {
//            for(int j = 0; j <= 1; j++) {
//                if(mtx[j][0] == mtx[j][2]) {
//                    if(checkMono2x2NC_1(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END 1a 2a RIGA | 1a e 3a COL
//
//    //(2) 1a 3a RIGA | 1a 2a COL
//    for(int i = 0; i <= 1; i++) {
//        if(mtx[0][i] == mtx[2][i]) {
//            for(int j = 0; j <= 2; j++) {
//                if(j == 1) continue;
//                if(mtx[j][0] == mtx[j][1]) {
//                    if(checkMono2x2NC_2(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END 1a 3a RIGA | 1a 2a COL
//
//    //(3) 1a 3a RIGA | 1a 3a COL
//    for(int i = 0; i <= 2; i++) {
//        if(i == 1) continue;
//        if(mtx[0][i] == mtx[2][i]) {
//            for(int j = 0; j <= 2; j++) {
//                if(j == 1) continue;
//                if(mtx[j][0] == mtx[j][2]) {
//                    if(checkMono2x2NC_3(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END 1a 3a RIGA | 1a 3a COL
//
//    //(4) 1a 3a RIGA | 2a 3a COL
//    for(int i = 1; i <= 2; i++) {
//        if(mtx[0][i] == mtx[2][i]) {
//            for(int j = 0; j <= 2; j++) {
//                if(j == 1) continue;
//                if(mtx[j][1] == mtx[j][2]) {
//                    if(checkMono2x2NC_4(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END 1a 3a RIGA | 2a 3a COL
//
//    //(5) 2a 3a RIGA | 1a 3a COL
//    for(int i = 0; i <= 2; i++) {
//        if(i == 1) continue;
//        if(mtx[1][i] == mtx[2][i]) {
//            for(int j = 1; j <= 2; j++) {
//                if(mtx[j][0] == mtx[j][2]) {
//                    if(checkMono2x2NC_5(mtx) == 0) return 1; //VIETATA TRUE - NON CP
//                }
//            }
//        }
//    } //END 2a 3a RIGA | 1a 3a COL


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

void printMtxToFile( int mtx[ NUM ][ NUM ], int mtx2[ NUM ][ NUM ], FILE *fPtr, int cont_Mtx, int mtxType, int bit1, int bit2, int bit3, int bitCentrale, int idx, int countRC3bit, int countStraight, int count1for2, int countCoppiaRow, int countCoppiaCol, int sign ) {

//    *countInterno = *countInterno + 1;

//    fprintf( fPtr, "%d%d%d\n", countRC3bit, countStraight, count1for2);
    fprintf( fPtr, "N° %d | %d", cont_Mtx, sign );
//    fprintf( fPtr, "%d | N° %d\nRC3:%d|STR:%d|1f2:%d\nCopR:%d | CopC:%d\n", idx, cont_Mtx, countRC3bit, countStraight, count1for2, countCoppiaRow, countCoppiaCol );
    if (mtxType == 10 || mtxType == 11 || mtxType == 12 || mtxType == 13) {
//        fprintf( fPtr, "VIETATA - NON CP\n");
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
//            fprintf( fPtr, "%3d", mtx2[ r ][ c ] ); //stampa il bit reale

            if (mtx2[ r ][ c ] == 13) {
                fprintf( fPtr, "%3c", '-' );
            } else if (mtx2[ r ][ c ] == 10) {
                fprintf(fPtr, "%2c%c", 'X', '1');
            } else if (mtx2[ r ][ c ] == 11) {
                fprintf( fPtr, "%2c%c", 'X', '2' );
            } else if (mtx2[ r ][ c ] == 12) {
                fprintf( fPtr, "%2c%c", 'X', '3' );
            } else if (mtx2[ r ][ c ] == 114 || mtx2[ r ][ c ] == 214) {
                fprintf( fPtr, "%2c%c", 'Y', '1' );
            } else if (mtx2[ r ][ c ] == 115 || mtx2[ r ][ c ] == 215) {
                fprintf( fPtr, "%2c%c", 'Y', '2' );
            } else if (mtx2[ r ][ c ] == 116 || mtx2[ r ][ c ] == 216) {
                fprintf( fPtr, "%2c%c", 'Y', '3' );
            } else if (mtx2[ r ][ c ] == 110 || mtx2[ r ][ c ] == 210) {
                fprintf( fPtr, "%2c%c", 'Z', '1' );
            } else if (mtx2[ r ][ c ] == 111 || mtx2[ r ][ c ] == 211) {
                fprintf( fPtr, "%2c%c", 'Z', '2' );
            } else if (mtx2[ r ][ c ] == 112 || mtx2[ r ][ c ] == 212) {
                fprintf( fPtr, "%2c%c", 'Z', '3' );
            }

//            if (mtx2[ r ][ c ] == 13) {
//                fprintf( fPtr, "%3c", '-' );
//            } else if (mtx2[ r ][ c ] == 10) {
//                fprintf( fPtr, "%3c", 'A');
//            } else if (mtx2[ r ][ c ] == 11) {
//                fprintf( fPtr, "%3c", 'B' );
//            } else if (mtx2[ r ][ c ] == 12) {
//                fprintf( fPtr, "%3c", 'C' );
//            } else if (mtx2[ r ][ c ] == 114 || mtx2[ r ][ c ] == 214) {
//                fprintf( fPtr, "%3c", 'A' );
//            } else if (mtx2[ r ][ c ] == 115 || mtx2[ r ][ c ] == 215) {
//                fprintf( fPtr, "%3c", 'B' );
//            } else if (mtx2[ r ][ c ] == 116 || mtx2[ r ][ c ] == 216) {
//                fprintf( fPtr, "%3c", 'C' );
//            } else if (mtx2[ r ][ c ] == 110 || mtx2[ r ][ c ] == 210) {
//                fprintf( fPtr, "%3c", 'A' );
//            } else if (mtx2[ r ][ c ] == 111 || mtx2[ r ][ c ] == 211) {
//                fprintf( fPtr, "%3c", 'B' );
//            } else if (mtx2[ r ][ c ] == 112 || mtx2[ r ][ c ] == 212) {
//                fprintf( fPtr, "%3c", 'C' );
//            }


//            else {
//                if (bitCentrale == bit1) {
//                    if( mtx[ r ][ c ] == bit1) {
//                        fprintf( fPtr, "%3c", 'A' );
////                    fprintf( fPtr, "%3c", '-' );
//                    } else if(mtx[ r ][ c ] == bit2) {
//                        fprintf( fPtr, "%3c", 'B' );
//                    } else if(mtx[ r ][ c ] == bit3) {
//                        fprintf( fPtr, "%3c", 'C' );
//                    }
//                } else if(bitCentrale == bit2) {
//                    if( mtx[ r ][ c ] == bit1) {
//                        fprintf( fPtr, "%3c", 'A' );
//                    } else if(mtx[ r ][ c ] == bit2) {
//                        fprintf( fPtr, "%3c", 'B' );
////                    fprintf( fPtr, "%3c", '-' );
//                    } else if(mtx[ r ][ c ] == bit3) {
//                        fprintf( fPtr, "%3c", 'C' );
//                    }
//                } else if(bitCentrale == bit3) {
//                    if( mtx[ r ][ c ] == bit1) {
//                        fprintf( fPtr, "%3c", 'A' );
//                    } else if(mtx[ r ][ c ] == bit2) {
//                        fprintf( fPtr, "%3c", 'B' );
//                    } else if(mtx[ r ][ c ] == bit3) {
//                        fprintf( fPtr, "%3c", 'C' );
////                    fprintf( fPtr, "%3c", '-' );
//                    }
//                }
//            }

        }
        fprintf( fPtr, "\n" );
    }

    fprintf( fPtr, "\n" );

} //end printMtxToFile