#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


int main() {
    clock_t begin = clock();

    int res;
    int f;

    //TEST SINGOLA FUNZIONE
    for(int x = 0; x <= 2; x++) {
        for(int y = 0; y <= 2; y++) {

//                f = x*(2-x)+y*(2-y)+x*y*(2-x)*(2-y);
//                f = x*(2-x)+y*(2-y)+x*y*(2-x)*(2-y);
//                f = x*y*(2-x);
//                f = x*(2-x);
                f = x*(1-x)+y*(1-y);
//                f = (2*x*x + 2*y*y) + 2;
//                f = (x*x) + (2*y*y);
//                f = ((2*x) - (x*x)) + ((2*y) - (y*y)) + (x * y);

            res = f % 3;

            if ( res == -2) {
                printf("%3d", res + 3);
            } else if ( res == -1) {
                printf("%3d", res + 3);
            } else {
                printf("%3d", res);
            }

        }
        printf("\n");
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nTime: %f", time_spent);

//    getchar();
    return 0;

} //end main