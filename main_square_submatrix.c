#include <stdio.h>

int main() {
    int mtrx_size = 4;
    int mat[4][4] = {
            { 1, 2, 3, 4,},
            { 5,6,7,8,},
            {9,10,11,12,},
            {13,14,15,16},
    };
    int count = 0;

    int i, j, ioff, joff, off_cnt;
    int sub_mtrx_size;

    for(sub_mtrx_size = mtrx_size; sub_mtrx_size > 1 ; sub_mtrx_size--) {
        off_cnt = mtrx_size - sub_mtrx_size + 1;
        for (ioff = 0; ioff < off_cnt; ioff++) {
            for (joff = 0; joff < off_cnt; joff++) {
                count++;
                printf("count: %d\n", count);
                for (i = 0; i < sub_mtrx_size; i++) {
                    for (j = 0; j < sub_mtrx_size; j++) {
                        printf("%3d ", mat[i+ioff][j+joff]);
                    }
                    printf("\n");
                }
                printf("\n");

            }

        }
        count = 0;
    }

    return 0;
}