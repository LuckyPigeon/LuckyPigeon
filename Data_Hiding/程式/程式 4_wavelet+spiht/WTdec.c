/*=================================================*/
//作者：廖永傳
//Input：未壓縮的image
//Compiler：Dev 4.9.9.0 
/*=================================================*/
#include <stdio.h>
#include <math.h>

#include "ImageCompression.h"
//#define TEST
#define INV
//#define NORM
#define DEBUG
//#define SUBAVG
//#define QUANT

WTdec(int size,float *input,float *output){
    float InvLfilter[7]={-0.091271763,-0.057543526,0.591271763,1.115089052, 0.591271763, -0.057543526, -0.091271763};
    float InvHfilter[9]={0.026748757,0.016864118,-0.078223266,-0.268641184,0.602949018, -0.26864118, -0.078223266, 0.016864118, 0.026748757};

    float *Itemp,*IRtemp;
    int x,y;
    float *Htemp,*Ltemp,*temp;
    
    printf("size=%d\n",size);
    
    Itemp = calloc((IMAGESIZE+8),sizeof(float));
    Htemp = calloc((IMAGESIZE+8)*(IMAGESIZE+8),sizeof(float));
    Ltemp = calloc((IMAGESIZE+8)*(IMAGESIZE+8),sizeof(float));
    IRtemp = calloc((IMAGESIZE+8),sizeof(float));
    temp = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    if(Itemp == NULL || Htemp == NULL || Ltemp == NULL || IRtemp == NULL || temp == NULL){
    	printf("not enough memory\n");
    	return;
    }
    // initional
    for(y=0;y<size+8;y++){
        *(Itemp+y) = 0;
        *(IRtemp+y) = 0;
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
    //end initional
    
    //做Y軸 
    //InvLowFilter
    
    for(x=4;x<size+4;x++){
        for(y=0;y<size;y++){
            *(Itemp+y+4) = *(temp+IMAGESIZE*(x-4)+y);
        }
        for(y=0;y<size+8;y++){
            *(IRtemp+y) = 0;
        }
        for(y=8;y<size+8;y=y+2){
            *(IRtemp+y+1-4) = *(Itemp+y/2);
        }
        (*(IRtemp+3)) = (*(IRtemp+5));
        (*(IRtemp+2)) = (*(IRtemp+6));
        (*(IRtemp+1)) = (*(IRtemp+7));
        (*(IRtemp+0)) = (*(IRtemp+8));
        (*(IRtemp+size+4)) = (*(IRtemp+size+2));
        (*(IRtemp+size+5)) = (*(IRtemp+size+1));
        (*(IRtemp+size+6)) = (*(IRtemp+size));
        (*(IRtemp+size+7)) = (*(IRtemp+size-1));
        for(y=4;y<size+4;y++){
            *(Ltemp+(IMAGESIZE+8)*x+y) = InvLfilter[0]*(*(IRtemp+y-3))+InvLfilter[1]*(*(IRtemp+y-2))+InvLfilter[2]*(*(IRtemp+y-1))
                        +InvLfilter[3]*(*(IRtemp+y))+InvLfilter[4]*(*(IRtemp+y+1))+InvLfilter[5]*(*(IRtemp+y+2))+InvLfilter[6]*(*(IRtemp+y+3));
        }
    }
    //InvHighFilter
   
    for(x=4;x<size+4;x++){
        for(y=0;y<size;y++){
            *(Itemp+y+4) = *(temp+IMAGESIZE*(x-4)+y);
        }
        for(y=0;y<size+8;y++){
            (*(IRtemp+y)) = 0;
        }
        for(y=8;y<size+8;y=y+2){
            (*(IRtemp+y-4)) = *(Itemp+(y/2)+(size/2));
        }
        *(IRtemp+3) = *(IRtemp+5);
        *(IRtemp+2) = *(IRtemp+6);
        *(IRtemp+1) = *(IRtemp+7);
        *(IRtemp+0) = *(IRtemp+8);
        *(IRtemp+size+4) = *(IRtemp+size+2);
        *(IRtemp+size+5) = *(IRtemp+size+1);
        *(IRtemp+size+6) = *(IRtemp+size);
        *(IRtemp+size+7) = *(IRtemp+size-1);
        for(y=4;y<size+4;y++){
            *(Htemp+(IMAGESIZE+8)*x+y) = InvHfilter[0]*(*(IRtemp+y-4))+InvHfilter[1]*(*(IRtemp+y-3))+InvHfilter[2]*(*(IRtemp+y-2))+InvHfilter[3]*(*(IRtemp+y-1))
                        +InvHfilter[4]*(*(IRtemp+y))+InvHfilter[5]*(*(IRtemp+y+1))+InvHfilter[6]*(*(IRtemp+y+2))+InvHfilter[7]*(*(IRtemp+y+3))+InvHfilter[8]*(*(IRtemp+y+4));
        }
    }
     
    for(x=0;x<size;x++){
        for(y=0;y<size;y++){
            *(temp+IMAGESIZE*x+y) = *(Ltemp+(IMAGESIZE+8)*(x+4)+(y+4)) + *(Htemp+(IMAGESIZE+8)*(x+4)+(y+4));
            //*(output+IMAGESIZE*x+y) = H*(temp+IMAGESIZE*x+2+y+2);
        }
    }
    
    //做X軸 
    //InvLowFilter
    for(y=4;y<size+4;y++){
        for(x=0;x<size;x++){
            *(Itemp+x+4) = *(temp+IMAGESIZE*x+(y-4));
        }
        for(x=0;x<size+8;x++){
            *(IRtemp+x) = 0;
        }
        for(x=8;x<size+8;x=x+2){
            *(IRtemp+x+1-4) = *(Itemp+(x/2));
        }
        *(IRtemp+3) = *(IRtemp+5);
        *(IRtemp+2) = *(IRtemp+6);
        *(IRtemp+1) = *(IRtemp+7);
        *(IRtemp+0) = *(IRtemp+8);
        *(IRtemp+size+4) = *(IRtemp+size+2);
        *(IRtemp+size+5) = *(IRtemp+size+1);
        *(IRtemp+size+6) = *(IRtemp+size);
        *(IRtemp+size+7) = *(IRtemp+size-1);
        for(x=4;x<size+4;x++){
            *(Ltemp+(IMAGESIZE+8)*x+y) = InvLfilter[0]*(*(IRtemp+x-3))+InvLfilter[1]*(*(IRtemp+x-2))+InvLfilter[2]*(*(IRtemp+x-1))
                        +InvLfilter[3]*(*(IRtemp+x))+InvLfilter[4]*(*(IRtemp+x+1))+InvLfilter[5]*(*(IRtemp+x+2))+InvLfilter[6]*(*(IRtemp+x+3));
        }
    }
    
    //InvHighFilter
   
    for(y=4;y<size+4;y++){
        for(x=0;x<size;x++){
            *(Itemp+x+4) = *(temp+IMAGESIZE*x+y-4);
        }
        for(x=0;x<size+8;x++){
            *(IRtemp+x) = 0;
        }
        for(x=8;x<size+8;x=x+2){
            *(IRtemp+x-4) = *(Itemp+x/2+(size/2));
        }
        *(IRtemp+3) = *(IRtemp+5);
        *(IRtemp+2) = *(IRtemp+6);
        *(IRtemp+1) = *(IRtemp+7);
        *(IRtemp+0) = *(IRtemp+8);
        *(IRtemp+size+4) = *(IRtemp+size+2);
        *(IRtemp+size+5) = *(IRtemp+size+1);
        *(IRtemp+size+6) = *(IRtemp+size);
        *(IRtemp+size+7) = *(IRtemp+size-1);
        for(x=4;x<size+4;x++){
            *(Htemp+(IMAGESIZE+8)*x+y) = InvHfilter[0]*(*(IRtemp+x-4))+InvHfilter[1]*(*(IRtemp+x-3))+InvHfilter[2]*(*(IRtemp+x-2))+InvHfilter[3]*(*(IRtemp+x-1))
                        +InvHfilter[4]*(*(IRtemp+x))+InvHfilter[5]*(*(IRtemp+x+1))+InvHfilter[6]*(*(IRtemp+x+2))+InvHfilter[7]*(*(IRtemp+x+3))+InvHfilter[8]*(*(IRtemp+x+4));
        }
    } 
    
    
    
    for(x=0;x<size;x++){
        for(y=0;y<size;y++){
            *(output+IMAGESIZE*x+y) = *(Ltemp+(IMAGESIZE+8)*(x+4)+(y+4)) + *(Htemp+(IMAGESIZE+8)*(x+4)+(y+4));
            //*(output+IMAGESIZE*x+y) = H*(temp+IMAGESIZE*x+2)[y+2);
        }
    }
    free(Itemp);
    free(temp);
    free(Htemp);
    free(Ltemp);
    free(IRtemp);
}

    
main(){
    //unsigned short img[IMAGESIZE][IMAGESIZE]={0};
    //short sign[IMAGESIZE][IMAGESIZE]={0};
    float *Re1=NULL,*Re2=NULL,max;
    float *temp=NULL,scale;
    int x,y,tx,ty,sum,i,level,size;
    unsigned int value;
    char name[50];
    FILE *fp;
    
    Re1 = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    Re2 = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    temp = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(float));
    if(Re1 == NULL || Re2 == NULL || temp == NULL){
    	printf("not enough memory\n");
    	return;
    }
    printf("Enter File Name:");
    scanf("%s", name);
    fp = fopen(name, "r");
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
       	    fscanf(fp,"%f", &(*(Re1+IMAGESIZE*x+y)));
       	}
    }
    fclose(fp);
    printf("Enter Level:");
    scanf("%d", &level);
    max = 0;
    tx=0;
    ty=0;
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
       	    (*(Re2+IMAGESIZE*x+y)) = 0;
       	    (*(temp+IMAGESIZE*x+y)) = 0;
       	   
       		if(max<(*(Re1+IMAGESIZE*x+y))){
       		    max = (*(Re1+IMAGESIZE*x+y));
       		    tx = x;
       		    ty = y;
       		}    
       	}
    }
    printf("img[%d][%d]=%f\n",tx,ty,(*(Re1+IMAGESIZE*tx+ty)));
    printf("img[0][0]=%f\n",(*(Re1+IMAGESIZE*0+0)));
    
    #ifdef SUBAVG
    printf("mean = ?");
    scanf("%d", &sum);
    printf("\nsum=%d\n",sum);
    for(x=0;x<8;x++){
   	    for(y=0;y<8;y++){
       		(*(Re1+IMAGESIZE*x+y)) = (*(Re1+IMAGESIZE*x+y)) + sum;
       	}
    }
    #endif
    
/*    #ifdef QUANT
    
	for(x=0;x<IMAGESIZE;x++){
		for(y=0;y<IMAGESIZE;y++){
			if((*(Re1+IMAGESIZE*x+y))>0){
			    *(Re1+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y)*2;
			}else{
				*(Re1+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y)*2;
			}
		}
	}
    #endif*/
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
                *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)/(scale/2);
       	    }
        }
        for(x=size;x<size*2;x++){
       	    for(y=0;y<size;y++){
                *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)/scale;
       	    }
        }
        for(x=0;x<size;x++){
       	    for(y=size;y<size*2;y++){
                *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)/scale;
       	    }
        }
        
        size = size/2;
        scale = scale*2;
    }
    for(x=0;x<size*2;x++){
       	for(y=0;y<size*2;y++){
            *(Re1+IMAGESIZE*x+y) = *(temp+IMAGESIZE*x+y)/scale;       	    
       	}
    }
    
    #endif
    */
    #ifdef INV
    
    
    size = IMAGESIZE/pow(2,level-1);
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
       	    *(temp+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y);
       	    *(Re2+IMAGESIZE*x+y) = *(Re1+IMAGESIZE*x+y);
       	}
    }
    for(i=0;i<level;i++){
        for(x=0;x<size;x++){
            for(y=0;y<size;y++){
       	        *(temp+IMAGESIZE*x+y) = *(Re2+IMAGESIZE*x+y);
       	    }
        }
        WTdec(size,temp,Re2);
        size = size*2;
    }
    #endif

    max = 0;
    tx=0;
    ty=0;
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
       		if(max<*(Re2+IMAGESIZE*x+y)){
       		    max = *(Re2+IMAGESIZE*x+y);
       		    tx = x;
       		    ty = y;
       		}    
       	}
    }
    printf("Re2[%d][%d]=%f\n",tx,ty,*(Re2+IMAGESIZE*tx+ty));
    printf("Re2[0][0]=%f\n",*(Re2+IMAGESIZE*0+0));
    fp = fopen("Rlena.raw", "wb");
    for(x=0;x<IMAGESIZE;x++){
       	for(y=0;y<IMAGESIZE;y++){
           	//fprintf(fp,"%f ",*(Re2+IMAGESIZE*x+y));
           	value = round(*(Re2+IMAGESIZE*x+y));//由floor()改成round()
           	putc(value,fp);
       	}
       	//fprintf(fp,"\n");
    }
    fclose(fp);
    free(Re1);
    free(Re2);
    free(temp);
    printf("ok");
    getch();
}    
   
