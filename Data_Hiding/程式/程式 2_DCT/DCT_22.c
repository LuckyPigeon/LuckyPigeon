// 512*512 lena image  
// 1. call 4*4 DCT 
// 2. output lena_dct.dat (512*512 DCT coefficients)
//    output lena_dc.raw (128*128 DC sub-image)
// 3. Tests (test1 & test2): recover lena image from DCT coefficients
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Pi 3.141592654
#define SIZE 512
#define dct_size 2

void dct_func(double data[dct_size][dct_size],double dct[dct_size][dct_size])
{
  int p,q,m,n;
  double ap,aq;
  for (p=0;p<dct_size;p++){
    for (q=0;q<dct_size;q++){
        if(p==0)
          ap=sqrt(1/(double)dct_size);
        else
          ap=sqrt(2/(double)dct_size);
        if(q==0)
          aq=sqrt(1/(double)dct_size);
        else
          aq=sqrt(2/(double)dct_size);

        for (m=0;m<dct_size;m++)
          for (n=0;n<dct_size;n++)
            dct[p][q]+=data[m][n]*cos(Pi*(2*m+1)*p/(2*dct_size))*cos(Pi*(2*n+1)*q/(2*dct_size)); 


//        dct[p][q]*= ap*aq;
        dct[p][q]/= 2;
    }
  }
}

void idct_func(double dct[dct_size][dct_size],double idct[dct_size][dct_size])
{
  int p,q,m,n;
  double ap,aq;
  for (m=0;m<dct_size;m++){
    for (n=0;n<dct_size;n++){
      for (p=0;p<dct_size;p++){
        for (q=0;q<dct_size;q++){
          if(p==0)
            ap=sqrt(1/(double)dct_size);
          else
            ap=sqrt(2/(double)dct_size);
          if(q==0)
            aq=sqrt(1/(double)dct_size);
          else
            aq=sqrt(2/(double)dct_size);
          idct[m][n]+=ap*aq*dct[p][q]*cos(Pi*(2*m+1)*p/(2*dct_size))*cos(Pi*(2*n+1)*q/(2*dct_size)); 
        }
      } 
    }
  }
}

int main()
{
  FILE *source_fp,*output_fp,*dc_output_fp;
  FILE *dest_fp,*output1_fp,*output2_fp;
  char ch;

  char lena[SIZE][SIZE];
  char lena_dc[SIZE/dct_size][SIZE/dct_size]; 
  double *dct_total = (double*)malloc(SIZE * SIZE * sizeof(double));

  double dct_before[2][2];
  double dct_after[2][2];
  double idct_before[2][2];
  double idct_after[2][2];
  
  char *ptr=&lena[0][0]; // *ptr = lena; 
  int i, j;
  int m,n;
 
  if ((source_fp = fopen("lena512.raw", "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }
  if ((output_fp = fopen("lena_dct.dat", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }
  if ((dc_output_fp = fopen("lena_dc.raw", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }

  while ((ch = getc(source_fp)) != EOF)
    *ptr++ = ch;

  for (m=0;m<(SIZE/2);m++){
    for (n=0;n<(SIZE/2);n++){
      //Initial
      for (i=0;i<2;i++){
        for (j=0;j<2;j++){
          dct_after[i][j] = 0;
        }
      }
      for (i=0;i<2;i++){
        for (j=0;j<2;j++){
          dct_before[i][j] = (double)lena[i+m*dct_size][j+n*dct_size];
        }
      }

      dct_func(dct_before,dct_after);

      lena_dc[m][n]= (char)dct_after[0][0]; // dc sub-image
//      lena_dc[m][n]= (char) dct_after[1][1]; // AC sub-image
//    lena_dc[m][n]= dct_after[3][3]; // AC sub-image

      for (i=0;i<2;i++){
        for (j=0;j<2;j++){
           *(dct_total+SIZE*(i+m*2)+j+n*2) = dct_after[i][j];         
        }
      }
    }
  }

  fwrite(dct_total, sizeof(double),
	       SIZE*SIZE,output_fp);
  fwrite(lena_dc, sizeof(char),
	       (SIZE/dct_size)*(SIZE/dct_size),dc_output_fp);
  fclose(source_fp);
  fclose(output_fp);
  fclose(dc_output_fp);
 

//idct_test1
//  
  if ((output1_fp = fopen("lena512_rec1.raw", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }
  for (m=0;m<(SIZE/2);m++){
    for (n=0;n<(SIZE/2);n++){
      for (i=0;i<2;i++)
        for (j=0;j<2;j++)
          idct_after[i][j] = 0;
      for (i=0;i<2;i++)
        for (j=0;j<2;j++)
          idct_before[i][j] = *(dct_total+SIZE*(i+m*2)+j+n*2);

      idct_func(idct_before,idct_after);

      for (i=0;i<2;i++)
        for (j=0;j<2;j++)
          lena[i+m*2][j+n*2] = (char)idct_after[i][j];
    }
  }
  fwrite(lena, sizeof(char),SIZE*SIZE,output1_fp);
  fclose(output1_fp);
//idct_test1
// 
//idct_test2 
  if ((dest_fp = fopen("lena_dct.dat", "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }	       
  fread(dct_total, sizeof(double),SIZE*SIZE,dest_fp);
  if ((output2_fp = fopen("lena512_rec2.raw", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }
  for (m=0;m<(SIZE/2);m++){
    for (n=0;n<(SIZE/2);n++){
      for (i=0;i<2;i++)
        for (j=0;j<2;j++)
          idct_after[i][j] = 0;
      for (i=0;i<2;i++)
        for (j=0;j<2;j++)
          idct_before[i][j] = *(dct_total+SIZE*(i+m*2)+j+n*2);

      idct_func(idct_before,idct_after);

      for (i=0;i<2;i++)
        for (j=0;j<2;j++)
          lena[i+m*2][j+n*2] = (char)idct_after[i][j];
    }
  }
  fwrite(lena, sizeof(char),SIZE*SIZE,output2_fp);
  fclose(output2_fp);
// idct_test2
// 
  free(dct_total); 
  
  system("PAUSE");
  return 0;
}

