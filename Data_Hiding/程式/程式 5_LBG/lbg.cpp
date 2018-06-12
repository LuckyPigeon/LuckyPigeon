/**************
�Ǹ��G 90321003
�m�W�G �©��s
***************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

unsigned int sqtest[16384][16384]; // �s����N��V�q���Z������F�[�t PNN �B���
                                 // ������G�A�{���[�t�����ɶ��֤F 30 ��

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
        for (j = 0; j < 256; j++) { // Ū�J lena.raw �ɦ� 16384 �� 2x2 blocks
            m = j / 2;
            k = j % 2;
            for (i = 0; i < 256; i++)
                blocks[k * 2 + i % 2][128 * m + i / 2] = getc(rawPtr);
        } // �]�w 16384 �� 4-tuple �V�q

        if (fclose(rawPtr) != 0)
            printf("File \"%s\" could not be closed\n", argv[1]);

        for (i = 0; i < 4; i++) for (j = 0; j < 16384; j++) raw[i][j] = blocks[i][j];
                
        for (j = 0; j < 16384; j++) blocks[4][j] = 1; // �s�� PNN �һݪ��[�v�ȡA�_�l�Ȭ� 1 
  
        for (i = 0; i < 16384; i++) for (j = i + 1; j < 16384; j++) sqtest[i][j] = 0; // ���N��V�q���Z������w�]�� 0
  
        start = time(NULL); // PNN Start
        printf("\nPNN Start !\n\n");
        while(count > 1024) {
            printf("Merging %d vectors to 1024 codewords!\n", count);
            min = 0 - 1;
            for (i = 0; i < count; i++)
                for (j = i + 1; j < count; j++) {
                    sum = sqtest[i][j];
                    if (sum == 0) { // ��ܻݨD�X i, j ��V�q���Z��
                        for (k = 0; k < 4; k++) {
                            m = blocks[k][i] - blocks[k][j];
                            sum += m * m;
                        }
                        sum *= (float) blocks[4][i] * blocks[4][j] / (blocks[4][i] + blocks[4][j]);
                        sqtest[i][j] = sum; // �p�⧹�����G�s�J�Z������x�}�A�U���K���ݹB��i�������X
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
                blocks[k][minj] = blocks[k][count]; // �V�q i, j �X�֫��^ i; �� last �V�q���N j
            }
            blocks[4][mini] += blocks[4][minj];
            blocks[4][minj] = blocks[4][count];
  
            for (i = 0; i < minj; i++) sqtest[i][minj] = sqtest[i][count]; // ���@�V�q�P�� last �V�q���Z�� = ���@�V�q�P j �V�q���Z��
            for (j = minj + 1; j < count; j++) sqtest[minj][j] = sqtest[j][count]; 
            for (i = 0; i < mini; i++)              // �]�V�q i �w�ܬ��s�V�q�A�Z�����k�s���ݭ��s�p�� 
				sqtest[i][mini] = 0;
            for (j = mini + 1; j < count; j++) sqtest[mini][j] = 0;
            printf("the weight of vector #%u is %u\n\n", mini, blocks[4][mini]);
        }
        printf("\nPNN End !\n\n");
        end = time(NULL);
        printf("PNN time = %.2f seconds\n", difftime(end, start)); // PNN End
    
        for (i = 0; i < 4; i++) for (j = 0; j < 1024; j++) codebook[i][j] = blocks[i][j]; // �� PNN ��쪺 1024 codewords �� codebook

        printf("\nLBG Start !\n\n"); // LBG start
        while (1) {
            olddist = dist;
            dist = 0;
            // for (i = 0; i < 16384; i++) for (j = 0; j < 1024; j++) group[i][j] = -1;
			memset(group, -1, sizeof(int) * (16384 * 1024))

            for (j = 0; j < 1024; j++) group[16384][j] = 0; // �s��� codeword j �̱��� blocks �Ӽ�

            for (j = 0; j < 16384; j++) { // �Ҧ� blocks
                min = 0 - 1;
                for (i = 0; i < 1024; i++) { // �Ҧ� codebooks
                    sum = 0;
                    for (k = 0; k < 4; k++) { // �C�@ dimension
                        m = raw[k][j] - codebook[k][i];
                        sum += m * m;
                    }
                    if (sum < min) {
                        min = sum;
                        mini = i;
                    }
                }
                dist += (float) min;
                count = group[16384][mini]++; // group[16384][x] �s�� x group �� blocks �`��
                group[count][mini] = j;
            }

            dist /= 16384;
            printf("distortion = %f\n", dist);
            if ((olddist - dist) / dist < epison)
                break;

            for (k = 0; k < 4; k++)
                for (i = 0; i < 1024; i++) { // 1024 groups
                    codebook[k][i] = 0;
                    for (j = 0; j < group[16384][i]; j++) // i group ���� j �� block
                        codebook[k][i] += raw[k][group[j][i]];
                    codebook[k][i] /= group[16384][i];
                }
        }
        printf("\nLBG End !\n\n"); // LBG end

        psnr = 10 * log10(255 * 255 * 4 / dist);
        printf("\nPSNR = %f\n", psnr);

        for (i = 0; i < 1024; i++) // 1024 groups
            for (j = 0; j < group[16384][i]; j++) // i group ���� j �� block
                blocks[4][group[j][i]] = i;
  
        if ((lbgPtr = fopen(argv[2], "wb")) == NULL)
            printf("File \"%s\" could not be opened\n", argv[2]);
  
        for (j = 0; j < 4; j++) for (i = 0; i < 1024; i++) putc(codebook[i][j], lbgPtr); // �N codebook �g�J�ɮ�

        for (i = 0; i < 16384; i++) putc(blocks[4][i], lbgPtr);
      
        if (fclose(lbgPtr) != 0) printf("File \"%s\" could not be closed\n", argv[2]);
    } else
        printf("File \"%s\" could not be opened\n", argv[1]);
                                     
    return (0);
}
