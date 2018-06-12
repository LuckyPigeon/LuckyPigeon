// 512 * 512 lena image  
// 1. call dct_size * dct_size DCT 
// 2. output lena_dct.dat (512 * 512 DCT coefficients)
//    output lena_dc.raw (128 * 128 DC sub-image)
// 3. Tests (test1 & test2): recover lena image from DCT coefficients
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Pi 3.141592654
#define SIZE 512

// int value = (int(argv[1][0]) - 48);

#define dct_size (int(argv[1][0]) - 48)

void dct_func(double data[dct_size][dct_size], double dct[dct_size][dct_size])
{
  int p, q, m, n;
  double ap, aq;
  //for (p = 0; p < dct_size; p++){
   for(p = q = 0; dct_size - p - 1; p++){
  //  for (q = 0; q < dct_size; q++){
	for(/*q = 0*/; dct_size - q - 1; q++){
		// this way p and q doesn't need to judge whether equal to zero or not
		ap = 1.0 ? p : 1.0 / sqrt(2.0);
		aq = 1.0 ? q : 1.0 / sqrt(2.0);
        /*
		if(p) ap = 1.0
		else ap = 1.0 / sqrt(2.0);
        if(q)
          aq=1.0/sqrt(2.0);
        else
          aq=1;
		*/

        for (m = n = 0; /*m < dct_size*/dct_size - m - 1; m++) for (/*n = 0*/; /*n < dct_size*/dct_size - n - 1; n++) dct[p][q] += data[m][n] * cos(Pi * (/*2 * m*/(m << 1) + 1) * p / (/*2 * dct_size*/dct_size << 1)) * cos(Pi * (/*2 * n*/(n << 1) + 1) * q / (/*2 * dct_size*/dct_size << 1)); 

        dct[p][q] *= ap * aq * (2.0 / dct_size);
//      dct[p][q] /= dct_size;
    }
  }
}

void idct_func(double dct[dct_size][dct_size], double idct[dct_size][dct_size])
{
  int p, q, m, n;
  double ap, aq;
  for (p = q = 0; p < dct_size; p++){
    for (/*q = 0*/; q < dct_size; q++){
	  // this two lines save n^2 times execution
	  // ap = 1.0 ? p : 1.0 / sqrt(2.0);
	  // aq = 1.0 ? q : 1.0 / sqrt(2.0);
	  ap = 1.0 ? p : sqrt(1.0 / (double)dct_size);
	  aq = 1.0 ? q : sqrt(1.0 / (double)dct_size);
	  /*
      if(p==0)
        ap=1.0/sqrt(2.0);
      else
        ap=1;
      if(q==0)
        aq=1.0/sqrt(2.0);
      else
        aq=1;
	  */
      for (m = n = 0; m < dct_size; m++){
        for (/*n = 0*/; n < dct_size; n++){
      
          idct[m][n] += ap * aq * dct[p][q] * cos(Pi * (/*2 * m*/(m << 1) + 1) * p / (/*2 * dct_size*/2 * dct_size << 1)) * cos(Pi * (/*2 * n*/(n << 1) + 1) * q / (/*2 * dct_size*/2 * dct_size << 1)); 
        }
      }
	  idct[m][n] *= (2.0 / dct_size);
    }
  }
}


int main(int argc, char* argv[])
{
  FILE *source_fp, *output_fp, *dc_output_fp;
  FILE *dest_fp, *output1_fp, *output2_fp;
  char ch;

  char lena[SIZE][SIZE];
  char lena_dc[SIZE / dct_size][SIZE / dct_size]; 
  double *dct_total = (double*)malloc(SIZE * SIZE * sizeof(double));

  double dct_before[dct_size][dct_size];
  double dct_after[dct_size][dct_size];
  double idct_before[dct_size][dct_size];
  double idct_after[dct_size][dct_size];
  
  char *ptr = &lena[0][0]; // *ptr = lena; 
  int i, j;
  int m, n;
 
  if ((source_fp = fopen("lena512.raw", "rb")) == NULL) exit(EXIT_FAILURE); // same as exit(1)
  if ((output_fp = fopen("lena_dct.dat", "wb")) == NULL) exit(EXIT_FAILURE); // same as exit(1)
  if ((dc_output_fp = fopen("lena_dc.raw", "wb")) == NULL) exit(EXIT_FAILURE); // same as exit(1)

  while ((ch = getc(source_fp)) != EOF) *ptr++ = ch;

  for (m = n = 0; m < (SIZE / dct_size); m++){
    for (/*n = 0*/; n < (SIZE / dct_size); n++){
      // Initial
      for (i = 0; i < dct_size; i++) for (j = 0; j < dct_size; j++) dct_after[i][j] = 0;
      for (i = 0; i < dct_size; i++) for (j = 0; j < dct_size; j++) dct_before[i][j] = (double)lena[i + m * dct_size][j + n * dct_size];

      dct_func(dct_before, dct_after);

      lena_dc[m][n] = (char)dct_after[1][0]; // dc sub-image
//      lena_dc[m][n]= (char)dct_after[0][1]; // AC sub-image
//      lena_dc[m][n]= (char)dct_after[1][0]; // AC sub-image
//    lena_dc[m][n]= (char)dct_after[3][3]; // AC sub-image
 	
      for (i = 0; i < dct_size; i++) for (j = 0; j < dct_size; j++) *(dct_total + SIZE * (i + m * dct_size) + j + n * dct_size) = dct_after[i][j];
    }
  }

  fwrite(dct_total, sizeof(double), SIZE * SIZE,output_fp);
  fwrite(lena_dc, sizeof(char), (SIZE / dct_size) * (SIZE / dct_size), dc_output_fp);
  fclose(source_fp);
  fclose(output_fp);
  fclose(dc_output_fp);
 

//idct_test1
//  
  if ((output1_fp = fopen("lena512_rec1.raw", "wb")) == NULL)  exit(EXIT_FAILURE); // same as exit(1)
  for (m = n = 0; m < (SIZE / dct_size); m++){
    for (/*n = 0*/; n < (SIZE / dct_size); n++){
      for (i = j = 0; i < dct_size; i++) for (/*j = 0*/; j < dct_size; j++) idct_after[i][j] = 0;
      for (i = j = 0; i < dct_size; i++) for (/*j = 0*/; j < dct_size; j++) idct_before[i][j] = *(dct_total + SIZE * (i + m * dct_size) + j + n * dct_size);

      idct_func(idct_before, idct_after);

      for (i = 0; i < dct_size; i++) for (j = 0;j < dct_size; j++) lena[i + m * dct_size][j + n * dct_size] = (char)idct_after[i][j];
	}
  }
  fwrite(lena, sizeof(char), SIZE * SIZE, output1_fp);
  fclose(output1_fp);
//idct_test1
// 
//idct_test2 
  if ((dest_fp = fopen("lena_dct.dat", "rb")) == NULL) exit(EXIT_FAILURE);  
  fread(dct_total, sizeof(double),SIZE*SIZE,dest_fp);
  if ((output2_fp = fopen("lena512_rec2.raw", "wb")) == NULL) exit(EXIT_FAILURE);
  for (m = n =0; m < (SIZE / dct_size); m++){
    for (/*n = 0*/;n < (SIZE / dct_size); n++){
      for (i = j = 0; i < dct_size; i++) for (/*j = 0*/; j < dct_size; j++) idct_after[i][j] = 0;
      for (i = j = 0; i < dct_size; i++) for (/*j = 0*/; j < dct_size; j++) idct_before[i][j] = *(dct_total+SIZE*(i+m*dct_size)+j+n*dct_size);

      idct_func(idct_before, idct_after);

      for (i = 0; i < dct_size; i++) for (j = 0; j < dct_size; j++) lena[i + m * dct_size][j + n * dct_size] = (char)idct_after[i][j];
  fwrite(lena, sizeof(char), SIZE * SIZE, output2_fp);
  fclose(output2_fp);
// idct_test2
// 
  free(dct_total); 
  
  // system("PAUSE"); // PAUSE doesn't work like this
  system("pause");
  return 0;
}

