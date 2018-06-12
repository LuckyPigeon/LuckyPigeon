#include <stdio.h>
#include "ImageCompression.h"

//#define DEBUG

struct node{
	int i;
	int j;
	struct node *nextPtr;
};
typedef struct node NODE;
typedef NODE *NODEPTR;

struct LISnode{
	int i;
	int j;
	char type;
	struct LISnode *nextPtr;
};
typedef struct LISnode LISNODE;
typedef LISNODE *LISNODEPTR;
/*
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
*/
int isEmpty(NODEPTR headPtr){
	return headPtr == NULL;
}

int isLISEmpty(LISNODEPTR headPtr){
	return headPtr == NULL;
}

void enqueue(NODEPTR *headPtr, NODEPTR *tailPtr, int ivalue, int jvalue){
	NODEPTR newPtr,currentPtr;
	
	newPtr = malloc(sizeof(NODE));
	
	if(newPtr != NULL){
		newPtr->i = ivalue;
		newPtr->j = jvalue;
		newPtr->nextPtr = NULL;
		
		if(isEmpty(*headPtr)){
			*headPtr = newPtr;
		}			
		else{
			(*tailPtr)->nextPtr = newPtr;
		}		
		*tailPtr = newPtr;
	}else{
		printf("No memory available.\n");
	}
}

void enlisqueue(LISNODEPTR *headPtr, LISNODEPTR *tailPtr, int ivalue, int jvalue,char type){
	LISNODEPTR newPtr,currentPtr;
	
	newPtr = malloc(sizeof(LISNODE));
	//printf("enque (%d %d)\n",ivalue,jvalue);
	if(newPtr != NULL){
		newPtr->i = ivalue;
		newPtr->j = jvalue;
		newPtr->type = type;
		newPtr->nextPtr = NULL;
		
		if(isLISEmpty(*headPtr)){
			*headPtr = newPtr;
		}			
		else{
			//printf("enque (%d %d), head=(%d %d), tail=(%d,%d)\n",ivalue,jvalue,(*headPtr)->i,(*headPtr)->j,(*tailPtr)->i,(*tailPtr)->j);
			(*tailPtr)->nextPtr = newPtr;
		}		
		*tailPtr = newPtr;
	}else{
		printf("No memory available.\n");
	}
}

int removenode(NODEPTR *headPtr, NODEPTR *tailPtr,int ivalue, int jvalue){
	NODEPTR previousPtr, currentPtr, tempPtr;
	
	if(ivalue==(*headPtr)->i && jvalue==(*headPtr)->j){	//move node = head
		if(ivalue==(*tailPtr)->i && jvalue==(*tailPtr)->j){	//&& head = tail
			*tailPtr = NULL;
		}
		tempPtr = *headPtr;
		*headPtr = (*headPtr)->nextPtr;
		free(tempPtr);
		#ifdef DEBUG
		printf("remove %d %d\n",ivalue,jvalue);
		#endif
		return 1;
	}else{
		previousPtr = *headPtr;
		currentPtr = (*headPtr)->nextPtr;
		while(currentPtr!=NULL && (currentPtr->i!=ivalue || currentPtr->j!=jvalue)){
			
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
		
		if(currentPtr != NULL){
			#ifdef DEBUG
			printf("remove %d %d,ivalue=%d,jvalue=%d\n",currentPtr->i,currentPtr->j,ivalue,jvalue);
			#endif
			if(ivalue==(*tailPtr)->i && jvalue==(*tailPtr)->j){
				*tailPtr = previousPtr;
			}
			tempPtr = currentPtr;
			
			previousPtr->nextPtr = currentPtr->nextPtr;
			free(tempPtr);
			return 1;
		}
	}
	return 0;
}

int removeLISnode(LISNODEPTR *headPtr,LISNODEPTR *tailPtr,int ivalue, int jvalue){
	LISNODEPTR previousPtr, currentPtr, tempPtr;
	
	//if(ivalue==(*tailPtr)->i && jvalue==(*tailPtr)->j){
		//printf("remove tail(%d,%d) head = (%d,%d)\n",(*tailPtr)->i,(*tailPtr)->j,(*headPtr)->i,(*headPtr)->j);
	//}
	//printf("tail = (%d,%d) head = (%d,%d) remove(%d,%d)\n",(*tailPtr)->i,(*tailPtr)->j,(*headPtr)->i,(*headPtr)->j,ivalue,jvalue);
	if(ivalue==(*headPtr)->i && jvalue==(*headPtr)->j){
		if(ivalue==(*tailPtr)->i && jvalue==(*tailPtr)->j && (*headPtr)->nextPtr == NULL){
			*tailPtr = NULL;
		}
		tempPtr = *headPtr;
		*headPtr = (*headPtr)->nextPtr;
		free(tempPtr);
					
		#ifdef DEBUG
		printf("remove %d %d\n",ivalue,jvalue);
		#endif
		return 1;
	}else{
		previousPtr = *headPtr;
		currentPtr = (*headPtr)->nextPtr;
		while(currentPtr!=NULL && (currentPtr->i!=ivalue || currentPtr->j!=jvalue)){
			//printf("previous = (%d,%d) current = (%d,%d)\n",(previousPtr)->i,(previousPtr)->j,(currentPtr)->i,(currentPtr)->j);
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
		
		if(currentPtr != NULL){
			//printf("current = (%d,%d)\n",(currentPtr)->i,(currentPtr)->j);
			#ifdef DEBUG
			printf("remove %d %d,ivalue=%d,jvalue=%d\n",currentPtr->i,currentPtr->j,ivalue,jvalue);
			#endif
			
			tempPtr = currentPtr;
			//if(ivalue==(*tailPtr)->i && jvalue==(*tailPtr)->j){
					//printf("tail = (%d,%d)\n",(*tailPtr)->i,(*tailPtr)->j);
			//}
			if(ivalue==(*tailPtr)->i && jvalue==(*tailPtr)->j && currentPtr->nextPtr == NULL){
			    
				*tailPtr = previousPtr;
			}
			previousPtr->nextPtr = currentPtr->nextPtr;
			
			free(tempPtr);
			return 1;
		}
	}
	return 0;
}

int SnD(unsigned short *img,int i,int j,int n){
	int bit;
	
	if(i==0 && j==0){
	    bit = ((*(img+IMAGESIZE*i+j)>>n)&0x01);
	    return bit;
	}    
	if(i>=IMAGESIZE || j>=IMAGESIZE){
		return 0;
	}else{
		bit = ((*(img+IMAGESIZE*i+j)>>n)&0x01);
		//printf("(%d %d)=%d\n",i,j,bit);
		if(bit == 1){
		    
			return 1;
		}else{
			if(SnD(img,2*i,2*j,n) || SnD(img,2*i+1,2*j,n) || SnD(img,2*i,2*j+1,n) || SnD(img,2*i+1,2*j+1,n)){
				return 1;
			}
		}
	}
	return 0;
}

int SnL(unsigned short *img,int i,int j,int n){
	unsigned short temp[4];
	
	temp[0] = *(img+IMAGESIZE*(2*i)+(2*j));
	temp[1] = *(img+IMAGESIZE*(2*i+1)+(2*j));
	temp[2] = *(img+IMAGESIZE*(2*i)+(2*j+1));
	temp[3] = *(img+IMAGESIZE*(2*i+1)+(2*j+1));
	*(img+IMAGESIZE*(2*i)+(2*j)) = 0;
	*(img+IMAGESIZE*(2*i+1)+(2*j)) = 0;
	*(img+IMAGESIZE*(2*i)+(2*j+1)) = 0;
	*(img+IMAGESIZE*(2*i+1)+(2*j+1)) = 0;
	if(SnD(img,2*i,2*j,n) || SnD(img,2*i+1,2*j,n) || SnD(img,2*i,2*j+1,n) || SnD(img,2*i+1,2*j+1,n)){
		*(img+IMAGESIZE*(2*i)+(2*j)) = temp[0];
		*(img+IMAGESIZE*(2*i+1)+(2*j)) = temp[1];
		*(img+IMAGESIZE*(2*i)+(2*j+1)) = temp[2];
		*(img+IMAGESIZE*(2*i+1)+(2*j+1)) = temp[3];
		return 1;
	}
	*(img+IMAGESIZE*(2*i)+(2*j)) = temp[0];
	*(img+IMAGESIZE*(2*i+1)+(2*j)) = temp[1];
	*(img+IMAGESIZE*(2*i)+(2*j+1)) = temp[2];
	*(img+IMAGESIZE*(2*i+1)+(2*j+1)) = temp[3];
	return 0;
}

main(){
	unsigned short *img,*sign,temp,temp1[4][4],temp2[4][4],temp3[4][4],temp4[4][4];
	int i,j,n,Snbit,SnDbit,SnLbit,k,l,buffptr,max;
	unsigned int LSPamount,LSPcount,thisLSP,bitcounter,bitrate;
	unsigned short buff[32] = {0};
	char type;
	float rate = 1.5;
	
	NODEPTR LIPheadPtr=NULL,LIPtailPtr=NULL,LSPheadPtr=NULL,LSPtailPtr=NULL,currentPtr=NULL,previousPtr=NULL;
	LISNODEPTR LISheadPtr=NULL,LIStailPtr=NULL,currentLISPtr=NULL,previousLISPtr=NULL;
	FILE *dbg,*Out;

	img = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(unsigned short));
	sign = calloc((IMAGESIZE)*(IMAGESIZE),sizeof(unsigned short));
	dbg = fopen("encdebug.txt","w");
	Out = fopen("spihtdata.bin","wb");
	buffptr = 0;
	
	for(i=0;i<32;i++){
		buff[i] = 0;
	}
	max = ReadImage(img,sign);
	printf("rate :");
	scanf("%f", &rate);
	bitrate = IMAGESIZE*IMAGESIZE*rate;

	printf("max=%d\n",max);
	n = 0;
	while(max>1){
		n++;
		max = max/2;
	}
	printf("n=%d\n",n);
	putc(n,Out);
	fprintf(Out,"%f",rate);

    printf("rate = %d\n",rate);

	//Initional
	bitcounter = 0;
	LSPheadPtr = NULL;
	LSPtailPtr = NULL;
	LIPheadPtr = NULL;
	LIPtailPtr = NULL;
	LISheadPtr = NULL;
	LIStailPtr = NULL;
	/*
	for(i=0;i<8;i=i++){
		for(j=0;j<8;j=j++){
			printf("%5d",*(img+IMAGESIZE*(i)+(j)));
		}
		printf("\n");
	}
	for(i=0;i<8;i=i+2){
		for(j=0;j<8;j=j+2){
			temp1[i/2][j/2] = (*(img+IMAGESIZE*(i)+(j)));
			temp2[i/2][j/2] = (*(img+IMAGESIZE*(i)+(j+1)));
			temp3[i/2][j/2] = (*(img+IMAGESIZE*(i+1)+(j)));
			temp4[i/2][j/2] = (*(img+IMAGESIZE*(i+1)+(j+1)));
		}
	}
	for(i=0;i<4;i=i++){
		for(j=0;j<4;j=j++){
			(*(img+IMAGESIZE*(i)+(j))) = temp1[i][j];
			(*(img+IMAGESIZE*(i+4)+(j))) = temp2[i][j];
			(*(img+IMAGESIZE*(i)+(j+4))) = temp3[i][j];
			(*(img+IMAGESIZE*(i+4)+(j+4))) = temp4[i][j];
		}
	}
	printf("\n");
	for(i=0;i<8;i=i++){
		for(j=0;j<8;j=j++){
			printf("%5d",*(img+IMAGESIZE*(i)+(j)));
		}
		printf("\n");
	}
	*/
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			enqueue(&LIPheadPtr,&LIPtailPtr,i,j);
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(i<4 && j<4){
				continue;
			}
			enlisqueue(&LISheadPtr,&LIStailPtr,i,j,'A');
		}
	}
	#ifdef DEBUG
	currentPtr = LIPheadPtr;
	while(currentPtr != NULL){
		printf("%d %d\n",currentPtr->i,currentPtr->j);
		currentPtr = currentPtr->nextPtr;
	}
	currentLISPtr = LISheadPtr;
	while(currentLISPtr != NULL){
		printf("%d %d %c\n",currentLISPtr->i,currentLISPtr->j,currentLISPtr->type);
		currentLISPtr = currentLISPtr->nextPtr;
	}
	#endif
	//Sort Pass
	LSPamount = 0;
	thisLSP = 0;
	for( ;n>=1;n--){
         if(bitcounter >= bitrate){
			break;
		}
		LSPamount = LSPamount + thisLSP;
		thisLSP = 0;
		//2.1
		currentPtr = LIPheadPtr;
		while(currentPtr != NULL && bitcounter < bitrate){
			i = currentPtr->i;
			j = currentPtr->j;
			Snbit = ((*(img+IMAGESIZE*i+j)>>n)&0x01);//將*(img+IMAGESIZE*i+j)往右移n位並和 0x01做and運算 
			currentPtr = currentPtr->nextPtr;
			//2.1.1 output Sn(i,j)
			fprintf(dbg,"Sn(%d,%d) = %d\n",i,j,Snbit);
			buff[buffptr] = Snbit;
			buffptr++;
			if(buffptr >= 16){
       		    		WriteData(buff,&buffptr,Out);//把sign值寫進spihtdata內 
       		    	}
       		    	
			bitcounter++;
			if(bitcounter >= bitrate){
			    break;
		    }
			//2.1.2
			if(Snbit == 1){
				enqueue(&LSPheadPtr,&LSPtailPtr,i,j);
				thisLSP++;
				removenode(&LIPheadPtr,&LIPtailPtr,i,j);
				//fprintf(dbg,"remove (%d,%d) from LIP\n",i,j);
				fprintf(dbg,"sign[%d][%d] = %d\n",i,j,*(sign+IMAGESIZE*i+j));
				buff[buffptr] = *(sign+IMAGESIZE*i+j);
				buffptr++;
				if(buffptr >= 16){
       		    			WriteData(buff,&buffptr,Out);
       		    		}
				bitcounter++;
				if(bitcounter >= bitrate){
                              break;
                }
			}
		}//while end
		//2.2
		currentLISPtr = LISheadPtr;
		while(currentLISPtr != NULL && bitcounter < bitrate){
			i = currentLISPtr->i;
			j = currentLISPtr->j;
			type = currentLISPtr->type;
			currentLISPtr = currentLISPtr->nextPtr;
			//2.2.1
			if(type == 'A'){
				temp = *(img+IMAGESIZE*i+j);
				*(img+IMAGESIZE*i+j) = 0;
				SnDbit = SnD(img,i,j,n);
				*(img+IMAGESIZE*i+j) = temp;
				fprintf(dbg,"Sn(D(%d,%d))=%d\n",i,j,SnDbit);
				buff[buffptr] = SnDbit;
				buffptr++;
				if(buffptr >= 16){
       		    			WriteData(buff,&buffptr,Out);
       		    		}
				bitcounter++;
				if(bitcounter >= bitrate){
                              break;
                }
				if(SnDbit == 1){
					//for each(k,l) in O(i,j)
					for(k=2*i;k<=2*i+1;k++){
						for(l=2*j;l<=2*j+1;l++){
							Snbit = ((*(img+IMAGESIZE*k+l)>>n)&0x01);
							fprintf(dbg,"Sn(%d,%d)=%d\n",k,l,Snbit);
							buff[buffptr] = Snbit;
							buffptr++;
							if(buffptr >= 16){
       		    						WriteData(buff,&buffptr,Out);
       		    					}
							bitcounter++;
							if(bitcounter >= bitrate){
                              break;
                           }
							if(Snbit==1){
								enqueue(&LSPheadPtr,&LSPtailPtr,k,l);
								fprintf(dbg,"sign(%d,%d)=%d\n",k,l,*(sign+IMAGESIZE*k+l));
								buff[buffptr] = *(sign+IMAGESIZE*k+l);
								buffptr++;
								if(buffptr >= 16){
       		    							WriteData(buff,&buffptr,Out);
       		    						}
								bitcounter++;
								if(bitcounter >= bitrate){
                                   break;
                                }
								thisLSP++;
							}else{
								enqueue(&LIPheadPtr,&LIPtailPtr,k,l);
								//fprintf(dbg,"move (%d,%d) to LIP\n",k,l);
							}
						}
					}
					//if L(i,j) != empty
					if(i<=IMAGESIZE/4 && j<=IMAGESIZE/4){
						enlisqueue(&LISheadPtr,&LIStailPtr,i,j,'B');
					}
					removeLISnode(&LISheadPtr,&LIStailPtr,i,j);
					//fprintf(dbg,"remove (%d,%d) from LIS\n",i,j);
				}
			//2.2.2	
			}else if(type == 'B'){
				SnLbit = SnL(img,i,j,n);
				fprintf(dbg,"Sn(L(%d,%d))=%d\n",i,j,SnLbit);
				buff[buffptr] = SnLbit;
				buffptr++;
				if(buffptr >= 16){
       		    			WriteData(buff,&buffptr,Out);
       		    		}
				bitcounter++;
				if(bitcounter >= bitrate){
                              break;
                }
				if(SnLbit == 1){
					//each (k,l) in O(i,j)
					for(k=2*i;k<=2*i+1;k++){
						for(l=2*j;l<=2*j+1;l++){
							enlisqueue(&LISheadPtr,&LIStailPtr,k,l,'A');
						}
					}
					removeLISnode(&LISheadPtr,&LIStailPtr,i,j);
				}
			}
		}
		//3
		LSPcount = 0;
		currentPtr = LSPheadPtr;
		while(currentPtr != NULL && LSPcount<LSPamount && bitcounter < bitrate){
			LSPcount++;
			i = currentPtr->i;
			j = currentPtr->j;
			currentPtr = currentPtr->nextPtr;
			Snbit = ((*(img+IMAGESIZE*i+j)>>n)&0x01);
			fprintf(dbg,"(%d,%d) = %d\n",i,j,Snbit);
			buff[buffptr] = Snbit;
			buffptr++;
			if(buffptr >= 16){
       		    		WriteData(buff,&buffptr,Out);
       		    	}
			bitcounter++;
			if(bitcounter >= bitrate){
                              break;
                }
		}
		printf("bitcounter = %d,LSPamount=%d\n",bitcounter,LSPamount);
		//printf LIP
		currentPtr = LIPheadPtr;
		fprintf(dbg,"LIPnode:\n");
		while(currentPtr != NULL){
			fprintf(dbg,"%d %d\n",currentPtr->i,currentPtr->j);
			currentPtr = currentPtr->nextPtr;
		}
		//printf LIS
		currentLISPtr = LISheadPtr;
		fprintf(dbg,"LISnode:\n");
		while(currentLISPtr != NULL){
			fprintf(dbg,"%d %d %c\n",currentLISPtr->i,currentLISPtr->j,currentLISPtr->type);
			currentLISPtr = currentLISPtr->nextPtr;
		}
		//printf LSP
		currentPtr = LSPheadPtr;
		fprintf(dbg,"LSPnode:\n");
		while(currentPtr != NULL){
			fprintf(dbg,"%d %d\n",currentPtr->i,currentPtr->j);
			currentPtr = currentPtr->nextPtr;
		}
	}
	if(buffptr > 0){
       	  	WriteData(buff,&buffptr,Out);
       	}
	fclose(Out);
	fclose(dbg);
	free(img);
	free(sign);
	printf("End of the problem.\n");
	getch();
}
