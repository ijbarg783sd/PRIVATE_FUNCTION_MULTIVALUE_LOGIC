#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


int main() {
    clock_t begin = clock();

    const unsigned long lim = 123333335;
    unsigned long *arrSign = malloc(lim * sizeof(unsigned long));

    int mtx[ 2 ][ 3 ];











    free(arrSign); // don't forget this!

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nTime: %f", time_spent);

//    getchar();
    return 0;

} //end main