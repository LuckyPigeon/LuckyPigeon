#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define n1 3       //output bits from encoder
#define n2 4  
#define k 2      //input bits to encoder
#define m1 2      //memory order
#define m2 3
#define NS 32    //no. of state = 2^6
#define Degree 4  // number of branch = 2^k
#define L 8	 //length of information sequence
#define N 105   //N=(L+m)*n
#define Y 5.0	 //signal noise ratio in dB
#define n_output 4
#define Zero 1.0   // bit 0
#define One (-1.0) // bit 1
#define Pi 3.141592654
#define EXP 2.71828183
#define Inf 99999999
#define debug
#define R (double)L/(double)N
#define N0 1.0/(pow(10,Y/10.0)*R)
// note it's not used in the subroutine get_word()
// r[i] = r[i] / (float)(sqrt(2.0 * R * pow(10.0, Y / 10.0)));
#define C1 log2(1.0/sqrt(Pi*N0))
#define C2 log2(EXP)/N0
#define CF pow(10.0,Y/10.0)*R*4.0
// see lecture note intro_lin_code.pdf, pp. 24   4sqrt(E)/N0 * rj let E=1 
#define max_random_value 65536.0
#define SIZE 512


int main(){
    FILE *source_fp, *dest_fp,*output_fp,*output2_fp,*code_fp;
    int i,j,m,n;
    int ran[L], t[N], f[N];	
    float r[N];
    int output[L]; // final decoded bits sequence 
    double output_quan[L];
    int count_of_computation,max_count[5],total_count[5]; 
    int codeword[L];
   // int message[16384];
    int *message = (int*)malloc(32768 * sizeof(int)); 
    // ran[L] random information bits 
    // t[N] codewords seq. after encoding ( N= (L+m)*n)
    // r[N] received vector after AWGN channel
    // f[N] hard-decision bits seq.
int G1[n1][m1+k]=
{1,1,1,1,
0,1,1,0,
1,1,0,1};
int G2[n2][m2+n1]=
{0,0,1,0,1,1,
0,1,0,1,0,1,
1,1,0,0,0,1,
1,0,0,1,1,1};
double dct_emb_tmp[8][8];
double host[8];
double dct_emb_after[8][8];
  if ((source_fp = fopen("lena_dct.dat", "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }
    if ((code_fp = fopen("message.txt", "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }
  if ((output2_fp = fopen("lena_emb.dat", "wb")) == NULL) {
    exit(EXIT_FAILURE);
}
double *dct_total = (double*)malloc(SIZE * SIZE * sizeof(double)); 
 double *emb_total = (double*)malloc(SIZE * SIZE * sizeof(double));   
int input_code[L];
 fread(dct_total, sizeof(double),SIZE*SIZE,source_fp);
  fread(message, sizeof(int),32768,code_fp);
  for (m=0;m<(SIZE/8);m++)
  {
  for (n=0;n<(SIZE/8);n++)
  {
 // printf("原始dct");
  for (i=0;i<8;i++)
  {
    for (j=0;j<8;j++)
    {
      dct_emb_tmp[i][j] = dct_total[SIZE*(i+m*8)+j+n*8];
      dct_emb_after[i][j] = dct_total[SIZE*(i+m*8)+j+n*8];
   //   printf("%f ",dct_emb_tmp[i][j]);
    }
  //  printf("\n");
}
 host[0]=dct_emb_tmp[0][7];
  host[1]=dct_emb_tmp[1][6];
   host[2]=dct_emb_tmp[2][5];
    host[3]=dct_emb_tmp[3][4];
      host[4]=dct_emb_tmp[4][3];
       host[5]=dct_emb_tmp[5][2];
         host[6]=dct_emb_tmp[6][1];
           host[7]=dct_emb_tmp[7][0];
     
   // printf("code=");
      for (i=0;i<8;i++)
    {  
    input_code[i]=message[i+m*8*64+n*8];
 //   printf("%d ",input_code[i]);
}
//printf("\n");
viterbi_decode(host,G1,G2,output,&count_of_computation,output_quan,input_code);
     /* for (i=0;i<4;i++)
    { 
          printf("%d %f ",output[i],output_quan[i]);
          }*/
dct_emb_after[0][7]=output_quan[0];
 dct_emb_after[1][6]=output_quan[1];
  dct_emb_after[2][5]=output_quan[2];
   dct_emb_after[3][4]=output_quan[3];
     dct_emb_after[4][3]=output_quan[4];
       dct_emb_after[5][2]=output_quan[5];
        dct_emb_after[6][1]=output_quan[6];
          dct_emb_after[7][0]=output_quan[7];
 /* for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      printf("%f ",dct_emb_after[i][j]);
    }
    printf("\n");
}*/
for (i=0;i<8;i++)
  {
    for (j=0;j<8;j++){
    emb_total[SIZE*(i+m*8)+j+n*8]=dct_emb_after[i][j];
    //  printf("%f ",emb_total[SIZE*(i+m*4)+j+n*4]);
    }
 //   printf("\n");
}
}
}
//輸出隱藏過後的dct值 
fwrite(emb_total, sizeof(double),
	       SIZE*SIZE,output2_fp);
free(dct_total);
free(emb_total);
free(message);
	   fclose(fpti);
	   fclose(source_fp);
	   fclose(code_fp);
	   fclose(output2_fp);
	   system("PAUSE");
}
