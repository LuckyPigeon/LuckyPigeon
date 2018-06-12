/**************
學號： 90321003
姓名： 謝明龍
***************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *rawPtr, *lbgPtr;
    unsigned int raw[16][4096], codebook[16][16];
    int i, j, k, m;
    float ratio;

    if (argc < 3) {
        printf("Syntax: DELBG input output!\n");
        return (0);
    }

    printf("\nStart decoding LBG file %s to RAW file %s......\n", argv[1], argv[2]);

    if ((lbgPtr = fopen(argv[1], "rb")) != NULL) {
        for (j = 0; j < 16; j++)
            for (i = 0; i < 16; i++)
                codebook[i][j] = getc(lbgPtr);
        for (i = 0; i < 4096; i++) {
            k = getc(lbgPtr);
            for (j = 0; j < 16; j++)
                raw[j][i] = codebook[j][k];
        }

        if (fclose(lbgPtr) != 0)
            printf("File \"%s\" could not be closed\n", argv[1]);

        if ((rawPtr = fopen(argv[2], "wb")) == NULL)
            printf("File \"%s\" could not be opened\n", argv[2]);

        for (j = 0; j < 256; j++) {
            m = j / 4;
            k = j % 4;
            for (i = 0; i < 256; i++)
                putc(raw[k * 4 + i % 4][m * 64 + i / 4], lbgPtr);
        }

        if (fclose(rawPtr) != 0)
            printf("File \"%s\" could not be closed\n", argv[1]);
        
        printf("\nDecoding succeeded!!\n");

        ratio = (float) (16 * 16 + 4096) / (16 * 4096);
        printf("\nCompression Ratio = %f\n", ratio);
    } else
        printf("File \"%s\" could not be opened\n", argv[1]);

    return(0);
}
