#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM 3 //N.B. da 5 in su dura minuti/ore
#define ROWS 3
#define COLS 3

// PROTOTIPI
void initMtx( int mtx[ ROWS ][ COLS ] );
void rowPerm( int mtx[ ROWS ][ COLS ], int riga, int numPerm, int valori[3], int lenValori, int lenPerm );
void printMtx( int mtx[ ROWS ][ COLS ] );
void printMtxToFile( int mtx[ ROWS ][ COLS ], FILE *fPtr, int cont_Mtx, int cp, int *countInterno );
int check(int mtx[ ROWS ][ COLS ]);
int check3(int mtx[ ROWS ][ COLS ]);
int checkMono3(int mtx[ ROWS ][ COLS ]);
int check2(int mtx[ ROWS ][ COLS ]);
int checkMono2_1(int mtx[ ROWS ][ COLS ]);
int checkMono2_2(int mtx[ ROWS ][ COLS ]);
int checkMono2_3(int mtx[ ROWS ][ COLS ]);
int checkMono2_4(int mtx[ ROWS ][ COLS ]);
int sumMtx(int matrix[][COLS], int* arrNumSum, int* arrNumCount, int* arrHowMany012, int *arrDistribution);
int concat(int x, int y, int z);


int main() {
    clock_t begin = clock();

    int mtx[ ROWS ][ COLS ];

    FILE *logPtr;
    FILE *logPtr2;
    FILE *logPtr3;
    FILE *logPtr4;
    FILE *logPtr5;
    int arr[] = {0, 1, 2};
    int cont_Mtx = 0;
    int cp = 0; //computabile privatamente
    int mono = 0; //monocromatica - NON vietata
    int cont_cp = 0;
    int cont_cp_mono_3x3 = 0;
    int cont_cp_mono_2x2 = 0;
    int cont_cp_NON_vietate = 0;
    int cont_non_cp = 0;
    int countInterno = 0;
    int countInterno2 = 0;
    int n;
    int arrNumSum[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int arrHowMany012[3] = {0};
    int arrDistribution[999] = {0};


    char filename[50], filename2[50], filename3[50], filename4[50], filename5[50];
    struct tm* tm;
    time_t timeFileCreation;
    timeFileCreation = time(0); // get current time
    tm = localtime(&timeFileCreation);
    sprintf( filename, "1-tot-mat-%04d%02d%02d-%02d%02d%02d.txt",
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

    if ( ( logPtr = fopen( filename, "w" ) ) == NULL ) {
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

    initMtx( mtx );

    fflush( logPtr ); // rilascia dati ancora scritti
    fflush( logPtr2 ); // rilascia dati ancora scritti
    fflush( logPtr3 ); // rilascia dati ancora scritti
    fflush( logPtr4 ); // rilascia dati ancora scritti
    fflush( logPtr5 ); // rilascia dati ancora scritti




//BEGIN controllo selettivo
//    cont_Mtx++;
//    cp = check( mtx ); //controllo MATRICI
////                sumMtx(mtx, arrNumSum);
//    if (cp == 0) {
//        cont_non_cp++; //0 - NON CP - vietata o monocromatica
////                    printMtxToFile( mtx, logPtr2, cont_Mtx, cp );
//    } else if (cp == 2) {
//        cont_cp++;
//        cont_cp_mono_3x3++;
////                    printMtxToFile( mtx, logPtr4, cont_Mtx, cp );
//    } else if (cp == 3) {
//
//        cont_cp++;
//        cont_cp_mono_2x2++;
////                    printMtxToFile( mtx, logPtr5, cont_Mtx, cp );
//    } else {
//        cont_cp_NON_vietate++;
//        cont_cp++; //1 - CP - ammessa (perchè NON vietata)
//
//        if(sumMtx(mtx, arrNumSum) == 4) {
//            printMtxToFile( mtx, logPtr3, cont_Mtx, cp );
//
//        }
//
//
//    }
////END controllo selettivo
//
//return 0; //interrompi prima di controllo MASSIVO

    for ( int i = 0; i < pow(NUM, NUM); i++ ) {
        rowPerm( mtx, 0, i, arr, 3, 3 );
        for ( int j = 0; j < pow(NUM, NUM); j++ ) {
            rowPerm( mtx, 1, j, arr, 3, 3 );
            for ( int k = 0; k < pow(NUM, NUM); k++ ) {
                rowPerm( mtx, 2, k, arr, 3, 3 );
                cont_Mtx++;
                cp = check( mtx ); //controllo MATRICI
                int arrNumCount[] = {0,0,0};
//                sumMtx(mtx, arrNumSum, arrNumCount, arrHowMany012, arrDistribution); //spostare in uno dei rami if seguenti per indagare le singole tipologie
                if (cp == 0) {
                    sumMtx(mtx, arrNumSum, arrNumCount, arrHowMany012, arrDistribution); //spostare in uno dei rami if seguenti per indagare le singole tipologie


                    cont_non_cp++; //0 - NON CP - vietata o monocromatica

                    if(arrHowMany012[0] == 2 && arrHowMany012[1] == 3 && arrHowMany012[2] == 4) {
                        printMtxToFile( mtx, logPtr2, cont_Mtx, cp, &countInterno2 );
                    }
                } else if (cp == 2) { //MONOCROMATICA 3x3

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

                        if(arrHowMany012[0] == 3 && arrHowMany012[1] == 3 && arrHowMany012[2] == 3) {
                            printMtxToFile( mtx, logPtr3, cont_Mtx, cp, &countInterno );
                        }



                }
                //stampa TUTTE LE MATRICI
//                printMtxToFile( mtx, logPtr, cont_Mtx, cp, &countInterno2 );


            }
        }
    }

    fflush( logPtr ); // rilascia dati ancora scritti
    fclose( logPtr );
    fflush( logPtr2 ); // rilascia dati ancora scritti
    fclose( logPtr2 );
    fflush( logPtr3 ); // rilascia dati ancora scritti
    fclose( logPtr3 );
    fflush( logPtr4 ); // rilascia dati ancora scritti
    fclose( logPtr4 );
    fflush( logPtr5 ); // rilascia dati ancora scritti
    fclose( logPtr5 );

    printf("TOT. MTX: %d\nMAT AMMESSE CP: %d | MAT AMMESSE MONO 3x3: %d | MAT AMMESSE MONO 2x2: %d | MAT AMMESSE NON VIETATE: %d\nMAT VIETATE NON_CP: %d\n", cont_Mtx, cont_cp, cont_cp_mono_3x3, cont_cp_mono_2x2, cont_cp_NON_vietate, cont_non_cp);
    for(int z = 0; z <=18; z++) {
//        printf("SOMMA PARI A %d: %d\n", z, arrNumSum[z]);
    }

    int sumDist = 0;
    for(int zzz = 0; zzz <= 999; zzz++) {
        sumDist = sumDist + arrDistribution[zzz];
        if(arrDistribution[zzz] != 0) {
            printf("MATRICI CON %d <012>: %d | TOTALE MAT: %d\n", zzz, arrDistribution[zzz], sumDist);
        }

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
    } else if (check3(mtx) == 2) {
        return 2; //monocromatica 3x3
    } else if (check2(mtx) == 1) {
        return 0; //SE VIETATA TRUE - NON CP
    } else if (check2(mtx) == 3) {
        return 3; //monocromatica 2x2
    } else { //SE VIETATA FALSE - CP
        return 1; //CP TRUE ammessa non vietata
    }
}

int check3(int mtx[ ROWS ][ COLS ]) {

    int equivR = 0;
    int equivC = 0;

    if (checkMono3(mtx) == 1) {
        return 2;
    }

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

int checkMono3(int mtx[ ROWS ][ COLS ]) {
    for(int ro = 0; ro <= 2; ro++) { //check monocromatica 3x3
        for(int co = 0; co <= 2; co++) {
            if(mtx[0][0] != mtx[ro][co]) {
                return 0;
            }
        }
    }
    return 1; //si monocromatica 3x3
}

int check2(int mtx[ ROWS ][ COLS ]) {

    if (checkMono2_1(mtx) == 1 ||
        checkMono2_2(mtx) == 1 ||
        checkMono2_3(mtx) == 1 ||
        checkMono2_4(mtx) == 1) {
        return 3;
    }

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

int checkMono2_1(int mtx[ ROWS ][ COLS ]) {

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

int checkMono2_2(int mtx[ ROWS ][ COLS ]) {

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

int checkMono2_3(int mtx[ ROWS ][ COLS ]) {

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

int checkMono2_4(int mtx[ ROWS ][ COLS ]) {

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

int sumMtx(int matrix[][COLS], int* arrNumSum, int* arrNumCount, int* arrHowMany012, int *arrDistribution) {

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

void printMtxToFile( int mtx[ ROWS ][ COLS ], FILE *fPtr, int cont_Mtx, int cp, int* countInterno ) {

    *countInterno = *countInterno + 1;

    fprintf( fPtr, "%d | N° %d***\n", *countInterno, cont_Mtx);
    if (cp == 0) {
        fprintf( fPtr, "VIETATA - NON CP\n");
    } else {
        fprintf( fPtr, "AMMESSA - CP\n");
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