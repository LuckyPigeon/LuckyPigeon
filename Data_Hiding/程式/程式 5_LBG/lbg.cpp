/**************
學號： 90321003
姓名： 謝明龍
***************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

unsigned int sqtest[16384][16384]; // 存放任意兩向量之距離平方；加速 PNN 運算用
                                 // 實測結果，程式加速後執行時間快了 30 倍

int main(int argc, char *argv[]){
    FILE *rawPtr, *lbgPtr;
    unsigned int raw[4][16384], blocks[5][16384], codebook[4][1024], min, sum, mini, minj, count = 16384;
    int i, j, k, m, group[16385][1024];
    float dist = 65535, olddist, psnr, epison;
    time_t start, end;

    if (argc < 4) {
        printf("Syntax: LBG input output epison!\nNotice: 1 > epison > 0\n");
        return (0);
    }

    epison = atof(argv[3]); 

    if ((rawPtr = fopen(argv[1], "rb")) != NULL) {
        for (j = 0; j < 256; j++) { // 讀入 lena.raw 檔成 16384 個 2x2 blocks
            m = j / 2;
            k = j % 2;
            for (i = 0; i < 256; i++)
                blocks[k * 2 + i % 2][128 * m + i / 2] = getc(rawPtr);
        } // 設定 16384 個 4-tuple 向量

        if (fclose(rawPtr) != 0)
            printf("File \"%s\" could not be closed\n", argv[1]);

        for (i = 0; i < 4; i++) for (j = 0; j < 16384; j++) raw[i][j] = blocks[i][j];
                
        for (j = 0; j < 16384; j++) blocks[4][j] = 1; // 存放 PNN 所需的加權值，起始值為 1 
  
        for (i = 0; i < 16384; i++) for (j = i + 1; j < 16384; j++) sqtest[i][j] = 0; // 任意兩向量之距離平方預設為 0
  
        start = time(NULL); // PNN Start
        printf("\nPNN Start !\n\n");
        while(count > 1024) {
            printf("Merging %d vectors to 1024 codewords!\n", count);
            min = 0 - 1;
            for (i = 0; i < count; i++)
                for (j = i + 1; j < count; j++) {
                    sum = sqtest[i][j];
                    if (sum == 0) { // 表示需求出 i, j 兩向量之距離
                        for (k = 0; k < 4; k++) {
                            m = blocks[k][i] - blocks[k][j];
                            sum += m * m;
                        }
                        sum *= (float) blocks[4][i] * blocks[4][j] / (blocks[4][i] + blocks[4][j]);
                        sqtest[i][j] = sum; // 計算完之結果存入距離平方矩陣，下次便不需運算可直接取出
                    }
                    if (sum < min) {
                        min = sum;
                        mini = i;
                        minj = j;
                    }
                }
            printf("Vector #%u and vector #%u have the minimal distance %u, \n", mini, minj, min);
            count--;
            for (k = 0; k < 4; k++) {
                blocks[k][mini] = (blocks[k][mini] * blocks[4][mini] + blocks[k][minj] * blocks[4][minj]) / (blocks[4][mini] + blocks[4][minj]);
                blocks[k][minj] = blocks[k][count]; // 向量 i, j 合併後放回 i; 讓 last 向量取代 j
            }
            blocks[4][mini] += blocks[4][minj];
            blocks[4][minj] = blocks[4][count];
  
            for (i = 0; i < minj; i++) sqtest[i][minj] = sqtest[i][count]; // 任一向量與原 last 向量之距離 = 任一向量與 j 向量之距離
            for (j = minj + 1; j < count; j++) sqtest[minj][j] = sqtest[j][count]; 
            for (i = 0; i < mini; i++)              // 因向量 i 已變為新向量，距離需歸零等待重新計算 
				sqtest[i][mini] = 0;
            for (j = mini + 1; j < count; j++) sqtest[mini][j] = 0;
            printf("the weight of vector #%u is %u\n\n", mini, blocks[4][mini]);
        }
        printf("\nPNN End !\n\n");
        end = time(NULL);
        printf("PNN time = %.2f seconds\n", difftime(end, start)); // PNN End
    
        for (i = 0; i < 4; i++) for (j = 0; j < 1024; j++) codebook[i][j] = blocks[i][j]; // 把 PNN 找到的 1024 codewords 當做 codebook

        printf("\nLBG Start !\n\n"); // LBG start
        while (1) {
            olddist = dist;
            dist = 0;
            // for (i = 0; i < 16384; i++) for (j = 0; j < 1024; j++) group[i][j] = -1;
			memset(group, -1, sizeof(int) * (16384 * 1024))

            for (j = 0; j < 1024; j++) group[16384][j] = 0; // 存放跟 codeword j 最接近的 blocks 個數

            for (j = 0; j < 16384; j++) { // 所有 blocks
                min = 0 - 1;
                for (i = 0; i < 1024; i++) { // 所有 codebooks
                    sum = 0;
                    for (k = 0; k < 4; k++) { // 每一 dimension
                        m = raw[k][j] - codebook[k][i];
                        sum += m * m;
                    }
                    if (sum < min) {
                        min = sum;
                        mini = i;
                    }
                }
                dist += (float) min;
                count = group[16384][mini]++; // group[16384][x] 存放 x group 的 blocks 總數
                group[count][mini] = j;
            }

            dist /= 16384;
            printf("distortion = %f\n", dist);
            if ((olddist - dist) / dist < epison)
                break;

            for (k = 0; k < 4; k++)
                for (i = 0; i < 1024; i++) { // 1024 groups
                    codebook[k][i] = 0;
                    for (j = 0; j < group[16384][i]; j++) // i group 的第 j 個 block
                        codebook[k][i] += raw[k][group[j][i]];
                    codebook[k][i] /= group[16384][i];
                }
        }
        printf("\nLBG End !\n\n"); // LBG end

        psnr = 10 * log10(255 * 255 * 4 / dist);
        printf("\nPSNR = %f\n", psnr);

        for (i = 0; i < 1024; i++) // 1024 groups
            for (j = 0; j < group[16384][i]; j++) // i group 的第 j 個 block
                blocks[4][group[j][i]] = i;
  
        if ((lbgPtr = fopen(argv[2], "wb")) == NULL)
            printf("File \"%s\" could not be opened\n", argv[2]);
  
        for (j = 0; j < 4; j++) for (i = 0; i < 1024; i++) putc(codebook[i][j], lbgPtr); // 將 codebook 寫入檔案

        for (i = 0; i < 16384; i++) putc(blocks[4][i], lbgPtr);
      
        if (fclose(lbgPtr) != 0) printf("File \"%s\" could not be closed\n", argv[2]);
    } else
        printf("File \"%s\" could not be opened\n", argv[1]);
                                     
    return (0);
}
