#define IMAGESIZE 512
#include <stdio.h>
#include <math.h>

void ReadRaw(char *FileName, unsigned short *img){
	int x,y;
	FILE *fp;

	fp = fopen(FileName,"rb");
	if(fp == NULL){
		printf("can't read the image\n");
		return;
	}else{
		printf("Open %s\n",FileName);
	}
	for(x=0;x<IMAGESIZE;x++){
		for(y=0;y<IMAGESIZE;y++){
			*(img+IMAGESIZE*(x)+(y)) = getc(fp);
		}
	}
	fclose(fp);
}

float PSNR(unsigned short *img1, unsigned short *img2){
	//unsigned short *diff;
	float psnr;
	int i,j;

	//diff = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(unsigned short));
	printf("%d %d\n",*img1,*img2);
	psnr = 0;
	for(i=0;i<IMAGESIZE;i++){
		for(j=0;j<IMAGESIZE;j++){
			//*(diff+IMAGESIZE*(i)+(j)) = (*(img1+IMAGESIZE*(i)+(j))) - (*(img2+IMAGESIZE*(i)+(j)));
			psnr = psnr + (((*(img1+IMAGESIZE*(i)+(j)))-(*(img2+IMAGESIZE*(i)+(j))))*((*(img1+IMAGESIZE*(i)+(j)))-(*(img2+IMAGESIZE*(i)+(j)))));
			//printf("%f\n",psnr);

		}

	}
	printf("%f\n",psnr);
	psnr = psnr/(IMAGESIZE*IMAGESIZE);
	printf("%f\n",psnr);
	if(psnr != 0){
		psnr = 10*log10((255*255)/psnr);
	}else{
		psnr = 999;
	}
	printf("%f\n",psnr);
	return psnr;
}

void WriteData(unsigned short *buffer,int *ptr,FILE *fp){
	int i,bit;
    	unsigned short tmp;

    	tmp = 0;
    	for(i=0;i<16;i++){
        	bit = *(buffer+i) & 0x01;
        	tmp = tmp + (bit<<(15-i));
        	#ifdef DEBUG
        	printf("*(buffer+%d)=%d tmp = %d\n",i,*(buffer+i),tmp);
        	#endif
        	*(buffer+i) = *(buffer+i+16);
        	*(buffer+i+16) = 0;
    	}

    	fwrite(&tmp,sizeof(unsigned short),1,fp);
    	*ptr = *ptr - 16;

}

void ReadData(unsigned short *buffer,int *ptr,FILE *fp){
    	int i,bit;
    	unsigned short tmp;

    	fread(&tmp,sizeof(unsigned short),1,fp);

    	for(i=0;i<16;i++){
       	 	bit = (tmp>>(15-i))&0x01;
        	*(buffer+(i+*ptr)) = bit;
        	#ifdef DEBUG
        	printf("*(buffer+%d)=%d tmp = %d\n",i+*ptr,*(buffer+(i+*ptr)),tmp);
        	#endif
    	}

    	*ptr = *ptr + 16;
}

int ReadImage(unsigned short *img,unsigned short *sign){
	unsigned short temp;
	float *input,max;
	int i,j,post,nest;
	char name[50];
	FILE *fp;

	input = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
	if(input == NULL){
    		printf("not enough memory\n");
    		return 0;
    	}
    	printf("Enter File Name:");
    	scanf("%s", name);
	fp = fopen(name, "r");
	max = 0;//影像內的最大值
	for(i=0;i<IMAGESIZE;i++){
       		for(j=0;j<IMAGESIZE;j++){
       	    		fscanf(fp,"%f", &*(input+IMAGESIZE*i+j));
       	    		*(sign+IMAGESIZE*i+j) = 9;
       	    		if(max<*(input+IMAGESIZE*i+j)){
       	    		    max = *(input+IMAGESIZE*i+j);
       	    		}
       		}
    }
    printf("read max = %f\n",max);
	fclose(fp);
	post = 0;
	nest = 0;
	for(i=0;i<IMAGESIZE;i++){
       		for(j=0;j<IMAGESIZE;j++){
       		    *(img+IMAGESIZE*i+j) = abs(*(input+IMAGESIZE*i+j));//得到整數的絕對值
       	    		if(*(input+IMAGESIZE*i+j)>=0){
       	    		    *(sign+IMAGESIZE*i+j) = 1;//好像反了，正數為零，負數為一才對
       	    		    post++;
       	    		}else{
                        *(sign+IMAGESIZE*i+j) = 0;
                        nest++;
                    }
              }
    	}
	printf("post = %d, nest = %d\n",post,nest);
	free(input);
	return max;
}


int FindK1(int k){
        int i,temp,K1;

        K1 = k/2;
        i = 1;
        temp = 1;
        while(temp <= K1){
                temp = temp*2;
                i++;
        }
        //printf("temp = %d, K1 = %d\n",temp,K1);
        if(K1 == temp/2){
                return K1;
        }
        if(K1 - temp/2 >= temp - K1){  //K1 is closed to temp
                return k - temp;
        }else{
                return temp/2;
        }
}

int Findk(double p){
        int k;
        float pk;


        if(p > 0.9998)
        	return 4096;
        k = 1;
        if(p >= 0.9){
        	k = 7;
        }else if(p >= 0.95){
        	k = 14;
        }else if(p >= 0.975){
        	k = 27;
        }else if(p >= 0.9875){
        	k = 55;
        }else if(p >= 0.99){
        	k = 69;
        }else if(p >= 0.999){
        	k = 693;
        }else if(p >= 0.9995){
        	k = 1386;
        }
        for( ;k<4096;k++){
        	pk = pow(p,k);
                if((pk+pow(p,k+1) <= 1 )&&( pk+pow(p,k-1) > 1)){
                        //printf("k=%d\n",k);
                        return k;
                        break;
                }
        }
        return 1;
}
