#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Pi 3.141592654
#define SIZE 512
#define dct_size 4
void dct_func(double data[dct_size][dct_size],double dct[dct_size][dct_size])
{
int p,q,m,n;
double ap,aq;
for (p=0;p<dct_size;p++)
  {
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
  {
    for (n=0;n<dct_size;n++){
      dct[p][q]+=data[m][n]*cos(Pi*(2*m+1)*p/(2*dct_size))*cos(Pi*(2*n+1)*q/(2*dct_size)); 
}
} 
dct[p][q]*=ap*aq;
}
}
}

void idct_func(double dct[dct_size][dct_size],double idct[dct_size][dct_size])
{
int p,q,m,n;
double ap,aq;
for (m=0;m<dct_size;m++)
  {
    for (n=0;n<dct_size;n++){
  for (p=0;p<dct_size;p++)
  {
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
  FILE *source_fp, *dest_fp,*output_fp,*output2_fp;
  int ch;
  unsigned int lena[512][512];
 // unsigned int idct_total[512][512];
  //double dct_total[4][4];
 // double dct_total[512][512];
  double *dct_total = (double*)malloc(SIZE * SIZE * sizeof(double));
  //double *dct_total=new double[512*512];
  double dct_before[4][4];
  double dct_after[4][4];
  double dct_test[16][16];
  double idct_before[4][4];
  double idct_after[4][4];
  
  unsigned int *ptr=&lena[0][0]; 
  int i, j;
  int m,n;
 // int *lena = (int*)malloc(512 * 512 * sizeof(int));
  if ((source_fp = fopen("lena512.raw", "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }
   /* if ((dest_fp = fopen("lena_dct.dat", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }*/
      if ((output_fp = fopen("lena_dct.dat", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }
       /* if ((output2_fp = fopen("lena_emb.dat", "wb")) == NULL) {
    exit(EXIT_FAILURE);
  }*/
  while ((ch = getc(source_fp)) != EOF){
   // putc(ch, *lena);
    *ptr++ = ch;
  }
 /* for (i=0;i<512;i++)
    for (j=0;j<512;j++){
      printf("%d ",lena[i][j]);
      printf("\n");
    }*/
//Initial
  for (m=0;m<(SIZE/4);m++)
  {
  for (n=0;n<(SIZE/4);n++)
  {
  for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      dct_after[i][j] = 0;
    }
}
  for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      dct_before[i][j] = (double)lena[i+m*4][j+n*4];
   //   printf("%d ",lena[i+m*4][j+n*4]);
    }
 //   printf("\n");
}

dct_func(dct_before,dct_after);
  for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      dct_total[SIZE*(i+m*4)+j+n*4] = dct_after[i][j];
   //   printf("%f ",dct_total[SIZE*(i+m*4)+j+n*4]);
    }
  //  printf("\n");
}
}
}
//
/*for(j=0;j<512*512;j++)  
{
     fprintf(output_fp,"%lf",dct_total[j]);
} */
 fwrite(dct_total, sizeof(double),
	       SIZE*SIZE,output_fp);
  fclose(source_fp);
  fclose(output_fp); 
//idct  
/*for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      idct_after[i][j] = 0;
    }
}
  for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      idct_before[i][j] = *(dct_total +  j);
    }
}

idct_func(idct_before,idct_after);
  for (i=0;i<4;i++)
  {
    for (j=0;j<4;j++){
      idct_total[i][j] = (int)dct_after[i][j];
    }
}
fwrite(idct_total, sizeof(dct_total[0]),
	       sizeof(idct_total) / sizeof(idct_total[0]),output2_fp);*/
  free(dct_total);
//  
  /* if ((dest_fp = fopen("lena_dct.dat", "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }	       
  fread(dct_test, sizeof(dct_test[0]),
	       sizeof(dct_test) / sizeof(dct_test[0]),dest_fp);*/

  /* for (i=0;i<4;i++)
   {
    for (j=0;j<4;j++){
      printf("%f ", dct_test[i][j]);
    }   
    printf("\n");
    }*/
//fclose(dest_fp);   
//fclose(output2_fp);  
system("PAUSE");
  return 0;
}

