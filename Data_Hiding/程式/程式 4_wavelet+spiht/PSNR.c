#include <stdio.h>
//#include <math.h>
#include "ImageCompression.h"

main(){
	unsigned short *img1,*img2;
	char FileName1[50],FileName2[50];
	float psnr;
	
	img1 = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(unsigned short));
	img2 = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(unsigned short));
	
	printf("File1 name? ");
	scanf("%s", FileName1);
	printf("File2 name? ");
	scanf("%s", FileName2);
	
	ReadRaw(FileName1,img1);
	ReadRaw(FileName2,img2);
	
	psnr = PSNR(img1,img2);
	
	printf("psnr = %f\n",psnr);
	
	free(img1);
	free(img2);
	
	getch();
}
