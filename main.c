#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


int main() {
    clock_t begin = clock();

    int abc[27][3] = {
            {0,0,0},
            {0,0,1},
            {0,0,2},
            {0,1,0},
            {0,1,1},
            {0,1,2},
            {0,2,0},
            {0,2,1},
            {0,2,2},
            {1,0,0},
            {1,0,1},
            {1,0,2},
            {1,1,0},
            {1,1,1},
            {1,1,2},
            {1,2,0},
            {1,2,1},
            {1,2,2},
            {2,0,0},
            {2,0,1},
            {2,0,2},
            {2,1,0},
            {2,1,1},
            {2,1,2},
            {2,2,0},
            {2,2,1},
            {2,2,2},
    };

    int res;

//    for(int i = 0; i<=26; i++) {
//        printf("a: %d | b: %d | c: %d\n", abc[i][0], abc[i][1], abc[i][2]);
//        for(int x = 0; x <= 2; x++) {
//            for(int y = 0; y <= 2; y++) {
//                res = (abc[i][0]*x + abc[i][1]*y + abc[i][2]) % 3;
////                printf("x:%d|y:%d\n", x, y);
//                printf("%3d", res);
//            }
//            printf("\n");
//        }
//        printf("\n");
//    }

    for(int i = 0; i<=26; i++) {
        printf("a: %d | b: %d | c: %d\n", abc[i][0], abc[i][1], abc[i][2]);
        for(int x = 0; x <= 2; x++) {
            for(int y = 0; y <= 2; y++) {
                res = (abc[i][0]*x*x + abc[i][1]*y*y + abc[i][2]) % 3;
//                printf("x:%d|y:%d\n", x, y);
                printf("%3d", res);
            }
            printf("\n");
        }
        printf("\n");
    }


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nTime: %f", time_spent);

//    getchar();
    return 0;

} //end main