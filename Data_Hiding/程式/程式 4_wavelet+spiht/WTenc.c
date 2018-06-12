 /*=================================================*/
//作者：廖永傳
//Input：未壓縮的image
//Compiler：Dev 4.9.9.0 
/*=================================================*/
#include <stdio.h>
#include <math.h>
#include "ImageCompression.h"
#define TEST
#define WRITEWT
//#define NORM
//#define SUBAVG
//#define QUANT

WTenc(int size,float *input,float *output){
    float Lfilter[9]={0.026748757,-0.016864118,-0.078223266,0.266864118,0.602949018,0.266864118,-0.078223266,-0.016864118,0.026748757};
    float Hfilter[7]={0.091271763,-0.0575435262,-0.591271763,1.115087052,-0.591271763,-0.0575435262,0.091271763};
    float *Itemp=NULL;
    int x,y;
    float *Htemp=NULL,*Ltemp=NULL,*temp=NULL;
    
    printf("size=%d\n",size);
   
    Itemp = calloc((IMAGESIZE+8),sizeof(float));
    Htemp = calloc((IMAGESIZE+8)*(IMAGESIZE+8),sizeof(float));
    Ltemp = calloc((IMAGESIZE+8)*(IMAGESIZE+8),sizeof(float));
    temp = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    if(Itemp == NULL || Htemp == NULL || Ltemp == NULL || temp == NULL){
    	printf("not enough memory\n");
    	return;
    }
    for(y=0;y<size+8;y++){//Itemp Htemp Ltemp歸零 
        *(Itemp+y) = 0;
        for(x=0;x<size+8;x++){
            *(Htemp+(IMAGESIZE+8)*x+y) = 0;
            *(Ltemp+(IMAGESIZE+8)*x+y) = 0;
        }
    }
    
    for(y=0;y<size;y++){
        for(x=0;x<size;x++){
            *(temp+IMAGESIZE*x+y) = *(input+IMAGESIZE*x+y);
            *(output+IMAGESIZE*x+y) = 0;
        }
    }
    
    //做X軸 
    
    for(y=4;y<size+4;y++){
        for(x=0;x<size;x++){
            *(Itemp+x+4) = *(temp+x*IMAGESIZE+y-4);
        }
        //擴展 
        *(Itemp+3) = *(temp+IMAGESIZE*1+(y-4));
        *(Itemp+2) = *(temp+IMAGESIZE*2+(y-4));
        *(Itemp+1) = *(temp+IMAGESIZE*3+(y-4));
        *(Itemp+0) = *(temp+IMAGESIZE*4+(y-4));
        *(Itemp+size+4) = *(temp+IMAGESIZE*(size-2)+(y-4));
        *(Itemp+size+5) = *(temp+IMAGESIZE*(size-3)+(y-4));
        *(Itemp+size+6) = *(temp+IMAGESIZE*(size-4)+(y-4));
        *(Itemp+size+7) = *(temp+IMAGESIZE*(size-5)+(y-4));
        for(x=4;x<size+4;x++){
            *(Ltemp+(IMAGESIZE+8)*x+y) = Lfilter[0]*(*(Itemp+x-4))+Lfilter[1]*(*(Itemp+x-3))+Lfilter[2]*(*(Itemp+x-2))+Lfilter[3]*(*(Itemp+x-1))
                        +Lfilter[4]*(*(Itemp+x))+Lfilter[5]*(*(Itemp+x+1))+Lfilter[6]*(*(Itemp+x+2))+Lfilter[7]*(*(Itemp+x+3))+Lfilter[8]*(*(Itemp+x+4));
        }
    }
    
    for(y=4;y<size+4;y++){
        for(x=0;x<size;x++){
            *(Itemp+x+4) = *(temp+IMAGESIZE*x+y-4);
        }
        //擴展 
        *(Itemp+3) = *(temp+IMAGESIZE*1+y-4);
        *(Itemp+2) = *(temp+IMAGESIZE*2+y-4);
        *(Itemp+1) = *(temp+IMAGESIZE*3+y-4);
        *(Itemp+0) = *(temp+IMAGESIZE*4+y-4);
        *(Itemp+size+4) = *(temp+IMAGESIZE*(size-2)+y-4);
        *(Itemp+size+5) = *(temp+IMAGESIZE*(size-3)+y-4);
        *(Itemp+size+6) = *(temp+IMAGESIZE*(size-4)+y-4);
        *(Itemp+size+7) = *(temp+IMAGESIZE*(size-5)+y-4);
        for(x=4;x<size+3;x++){
            *(Htemp+(IMAGESIZE+8)*x+y) = Hfilter[0]*(*(Itemp+x-3))+Hfilter[1]*(*(Itemp+x-2))+Hfilter[2]*(*(Itemp+x-1))
                        +Hfilter[3]*(*(Itemp+x))+Hfilter[4]*(*(Itemp+x+1))+Hfilter[5]*(*(Itemp+x+2))+Hfilter[6]*(*(Itemp+x+3));
        }
    } 
    
    for(y=0;y<size;y++){
        for(x=0;x<size;x=x+2){
            *(temp+IMAGESIZE*x/2+y) = *(Ltemp+(IMAGESIZE+8)*(x+4+1)+y+4);
            *(temp+IMAGESIZE*(x/2+size/2)+y) = *(Htemp+(IMAGESIZE+8)*(x+4)+y+4);
        }
    } 
    
    //做Y軸 
    
    for(x=4;x<size+4;x++){
        for(y=0;y<size;y++){
            *(Itemp+y+4) = *(temp+IMAGESIZE*(x-4)+y);
        }
        //擴展 
        *(Itemp+3) = *(temp+IMAGESIZE*(x-4)+1);
        *(Itemp+2) = *(temp+IMAGESIZE*(x-4)+2);
        *(Itemp+1) = *(temp+IMAGESIZE*(x-4)+3);
        *(Itemp+0) = *(temp+IMAGESIZE*(x-4)+4);
        *(Itemp+size+4) = *(temp+IMAGESIZE*(x-4)+size-2);
        *(Itemp+size+5) = *(temp+IMAGESIZE*(x-4)+size-3);
        *(Itemp+size+6) = *(temp+IMAGESIZE*(x-4)+size-4);
        *(Itemp+size+7) = *(temp+IMAGESIZE*(x-4)+size-5);
        
        for(y=4;y<size+4;y++){
            *(Ltemp+(IMAGESIZE+8)*x+y) = Lfilter[0]*(*(Itemp+y-4))+Lfilter[1]*(*(Itemp+y-3))+Lfilter[2]*(*(Itemp+y-2))+Lfilter[3]*(*(Itemp+y-1))
                        +Lfilter[4]*(*(Itemp+y))+Lfilter[5]*(*(Itemp+y+1))+Lfilter[6]*(*(Itemp+y+2))+Lfilter[7]*(*(Itemp+y+3))+Lfilter[8]*(*(Itemp+y+4));
        }
    }
    
    for(x=4;x<size+4;x++){
        for(y=0;y<size;y++){
            *(Itemp+y+4) = *(temp+IMAGESIZE*(x-4)+y);
        }
        //擴展 
        *(Itemp+3) = *(temp+IMAGESIZE*(x-4)+1);
        *(Itemp+2) = *(temp+IMAGESIZE*(x-4)+2);
        *(Itemp+1) = *(temp+IMAGESIZE*(x-4)+3);
        *(Itemp+0) = *(temp+IMAGESIZE*(x-4)+4);
        *(Itemp+size+4) = *(temp+IMAGESIZE*(x-4)+size-2);
        *(Itemp+size+5) = *(temp+IMAGESIZE*(x-4)+size-3);
        *(Itemp+size+6) = *(temp+IMAGESIZE*(x-4)+size-4);
        *(Itemp+size+7) = *(temp+IMAGESIZE*(x-4)+size-5);
        
        for(y=4;y<size+4;y++){
           *(Htemp+(IMAGESIZE+8)*x+y) = Hfilter[0]*(*(Itemp+y-3))+Hfilter[1]*(*(Itemp+y-2))+Hfilter[2]*(*(Itemp+y-1))
                        +Hfilter[3]*(*(Itemp+y))+Hfilter[4]*(*(Itemp+y+1))+Hfilter[5]*(*(Itemp+y+2))+Hfilter[6]*(*(Itemp+y+3));
        }
    } 
     
    for(x=0;x<size;x++){
        for(y=0;y<size;y=y+2){
            *(output+IMAGESIZE*x+y/2) = *(Ltemp+(IMAGESIZE+8)*(x+4)+(y+4+1));
            *(output+IMAGESIZE*x+(y/2+size/2)) = *(Htemp+(IMAGESIZE+8)*(x+4)+(y+4));
        }
    }
    free(Itemp);
    free(temp);
    free(Htemp);
    free(Ltemp);
}    


main(){
    unsigned short *img;
    float *Re1,*input,*Re2,max;
    float *temp,sum;
    int x,y,tx,ty,level,i,size,scale;
    unsigned int value;
    char name[20];
    FILE *fp;
    
    //ReadImage(img);
    img = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(unsigned short));
    Re1 = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    Re2 = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    input = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    temp = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    
    if(img == NULL || Re1 == NULL || Re2 == NULL || input == NULL || temp == NULL){
    	printf("not enough memory\n");
    	return;
    }
    printf("File name? ");
    scanf("%s", name);
    printf("File name is %s\n", name);
    fp = fopen(name,"rb");
    if(fp == NULL){
        printf("can't read the image\n");
    }    
    printf("ok\n");
    //fread(img, sizeof(char),(IMAGESIZE)*(IMAGESIZE) , fp);
    for(x=0;x<IMAGESIZE;x++){
    	for(y=0;y<IMAGESIZE;y++){
            *(img+IMAGESIZE*(x)+(y)) = getc(fp);
        }
    }
    printf("img[0][0] = %d\n",*(img+IMAGESIZE*0+0));
    fclose(fp);
    printf("1ok\n");
    max = 0;
    tx=0;
    ty=0;
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
       	    *(input+IMAGESIZE*x+y) = *(img+IMAGESIZE*x+y);
       	    *(Re1+IMAGESIZE*x+y) = 0;
       	    *(Re2+IMAGESIZE*x+y) = 0;
       	    *(temp+IMAGESIZE*x+y) = 0;
       		if(max<*(img+IMAGESIZE*x+y)){//max為img內的最大值 
       		    max = *(img+IMAGESIZE*x+y);
       		    tx = x;
       		    ty = y;
       		}    
       	}
    }
    printf("img[%d][%d]=%d\n",tx,ty,*(img+IMAGESIZE*tx+ty));
    printf("img[0][0]=%d\n",*(img+IMAGESIZE*0+0));
    printf("sizeof(unsigned short)=%d\n",sizeof(unsigned short));
    
    #ifdef TEST
    printf("level :");
    scanf("%d", &level);
    size = IMAGESIZE;
    WTenc(size,input,Re1);
    for(i=1;i<level;i++){
        
        for(x=0;x<IMAGESIZE;x++){
            for(y=0;y<IMAGESIZE;y++){
       	        *(temp+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y);
       	    }
        }
        size = size/2;
        WTenc(size,temp,Re1);
    }
 
    #endif
 /*   
    #ifdef NORM
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
            *(temp+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y);       	    
       	}
    }

    size = IMAGESIZE/2;
    scale = 1;
    for(i=1;i<level;i++){
    	for(x=size;x<size*2;x++){
       	    for(y=size;y<size*2;y++){
                *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)*(scale/2);
       	    }
        }
        for(x=size;x<size*2;x++){
       	    for(y=0;y<size;y++){
                *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)*scale;
       	    }
        }
        for(x=0;x<size;x++){
       	    for(y=size;y<size*2;y++){
                *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)*scale;
       	    }
        }
        
        size = size/2;
        scale = scale*2;
    }
    for(x=0;x<size*2;x++){
       	for(y=0;y<size*2;y++){
            *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)*scale;       	    
       	}
    }
    
    #endif   
    */
 /*   #ifdef QUANT
    

	for(x=0;x<IMAGESIZE;x++){//原來的code 
    		for(y=0;y<IMAGESIZE;y++){
       			if((*(Re1+IMAGESIZE*x+y))>=0){
            			*(Re1+IMAGESIZE*x+y) = floor(*(Re1+IMAGESIZE*x+y)/2);
			}else{
				*(Re1+IMAGESIZE*x+y) = ceil(*(Re1+IMAGESIZE*x+y)/2);
			}
		}
	}
    /*
     for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
            *(Re1+IMAGESIZE*x+y) = floor(*(Re1+IMAGESIZE*x+y)/4);       	    
       	}
    }
   
    #endif
 */   
    #ifdef SUBAVG
    sum = 0;
    for(x=0;x<8;x++){
       	for(y=0;y<8;y++){
    	    sum = sum + *(Re1+IMAGESIZE*x+y);
        	    //printf("img[%d][%d] = [%d]\n",x,y,*(img+IMAGESIZE*x+y));
       	}
    }
       
    sum = floor(sum/64);
    printf("mean=%f\n",sum);
    for(x=0;x<8;x++){
   	    for(y=0;y<8;y++){
       		*(Re1+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y) - sum;
       	}
    }
    #endif
    
    #ifdef WRITEWT
    fp = fopen("WT.raw", "w");
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
           	fprintf(fp,"%f ",*(Re1+IMAGESIZE*x+y));
           	//value = floor(*(Re1+IMAGESIZE*x+y));
           	//putc(value,fp);
       	}
       	fprintf(fp,"\n");
    }
    fclose(fp);
    #endif
    max = 0;
    for(x=0;x<16;x++){
       	for(y=0;y<16;y++){
    	    if( abs(*(Re1+IMAGESIZE*x+y)) > max){
    	    	max = abs(*(Re1+IMAGESIZE*x+y));
            }
	}
    }
    printf("max = %f\n",max);
    free(img);
    free(Re1);
    free(Re2);
    free(temp);
    free(input);
    printf("ok");
    getch();
}    
