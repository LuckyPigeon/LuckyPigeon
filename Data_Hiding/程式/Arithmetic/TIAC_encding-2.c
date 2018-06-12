/******************************************************
 * Research Group of Information Coding
 * Written by Jyun Ying Huang 2013/05/30  Modified by ymhuang 2013/07/28
 *****************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
char cleat_string(char stra[]){
	int i;
	for(i=0;i<100;i++){
		stra[i]=NULL;
	}
}

char Merger(char stra[], char string1[]){
	int count, count1;
	count=0;
	count1=0;
	while(stra[count]!=NULL){
		if(stra[count]!=NULL)
		count++;
	}
	while(string1[count1]!=NULL){
		if(string1[count1]!=NULL){
			stra[count]=string1[count1];
			count1++;
			count++;
		}
	}
	while(count!=100){
		stra[count]=NULL;
		count++;
	}
}

int CodewordToChar(int codeword[]){
	auto int i,sum=0;
	for(i=0;i<8;i++)
	sum=sum+codeword[i]*((int)pow(2.0,(double)7-i));
	return sum;
}

int main(){
	int i_file;
	char Inf_file[13][20]={
	/*0*/	"alice29"
	/*1*/	,"asyoulik"	
	/*2*/	,"cp"
	/*3*/	,"fields"	
	/*4*/	,"grammar"
	/*5*/	,"kennedy" 
	/*6*/	,"lcet10"
	/*7*/	,"out"	
	/*8*/	,"plrabn12"
	/*9*/	,"ptt5"	
	/*10*/	,"sum"	
	/*11*/	,"xargs"
	/*12*/	,"test"
	};
	
	char Inf_file_extension[13][10]={
	/*0*/	".txt"
	/*1*/	,".txt"	
	/*2*/	,".html"
	/*3*/	,".c"	
	/*4*/	,".lsp"
	/*5*/	,".xls" 
	/*6*/	,".txt"
	/*7*/	,""	
	/*8*/	,".txt"
	/*9*/	,""	
	/*10*/	,""	
	/*11*/	,".1"
	/*12*/	,".docx"
	};
	char str_Inf[100]={"_inf.txt"};
	char str_Output[100]={".icg"};
	char str_key[100]={".key"};
	char str[100];
	
	for(i_file=0;i_file<13;i_file++){
		
		cleat_string(str);
		Merger(str,Inf_file[i_file]);
		Merger(str,Inf_file_extension[i_file]);		
		printf("%s be compressed : \n",str);
		
		FILE *fp,*output_fp,*read_fp,*key_fp,*inf_fp;
		fp=fopen(str,"rb");
		if(!fp){
			printf("The file'%s' has no exist!!\n",str);
		}else{
			auto int i,j,k;
			auto int count; 
			auto unsigned long int Count_Mapping=0;
			auto unsigned long int Count_Output=0;
			
			unsigned long int *Register_Count_symbol;
			Register_Count_symbol=(unsigned long int*)malloc(sizeof(unsigned long int)*256);
			for(i=0;i<256;i++)
			Register_Count_symbol[i]=0;
			
			auto unsigned long int The_number_of_symbols_in_file=0;
/*
			while(!feof(fp)){                           
				auto unsigned char ch=getc(fp);
				Register_Count_symbol[(int)ch]++;
				The_number_of_symbols_in_file++;
			}
*/
//modified 2013/07/28			
			while(1){                           
				auto unsigned char ch=getc(fp);
                if (feof(fp))break;				
				Register_Count_symbol[(int)ch]++;
				The_number_of_symbols_in_file++;
			}
			fclose(fp);
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_Inf);
			remove(str);
			inf_fp=fopen(str,"w");
			
			auto unsigned long int The_number_of_species_of_symbols=0;
			for(i=0;i<256;i++){
				if(Register_Count_symbol[i]!=0)
				The_number_of_species_of_symbols++;
				fprintf(inf_fp,"%d\n",Register_Count_symbol[i]);
			}
			fclose(inf_fp);
			
			printf("The number of symbols in file is %d ( %d different symbols )\n",The_number_of_symbols_in_file,The_number_of_species_of_symbols);
			
			count=0;
			auto int Count_symbols[The_number_of_species_of_symbols][2];//[256][0]=symbol  [256][1]=count
			for(i=0;i<256;i++){
				if(Register_Count_symbol[i]!=0){
					Count_symbols[count][0]=i;//ASCII
					Count_symbols[count][1]=Register_Count_symbol[i];//The number of symbol
					count++;
				}
			}
			free(Register_Count_symbol);
			
			//sort the Count_symbols
			for(i=0;i<The_number_of_species_of_symbols;i++){
				for(j=i+1;j<The_number_of_species_of_symbols;j++){
					if(Count_symbols[j][1]>Count_symbols[i][1]){
						auto unsigned long int a0=Count_symbols[i][0];
						auto unsigned long int a1=Count_symbols[i][1];
						Count_symbols[i][0]=Count_symbols[j][0];
						Count_symbols[i][1]=Count_symbols[j][1];
						Count_symbols[j][0]=a0;
						Count_symbols[j][1]=a1;
					}
				}
			}
//log2(interval size/4)>= log2(The_number_of_symbols_in_file))			
			auto int Bit_of_interval= ceil(log((double)(The_number_of_symbols_in_file))/log(2.0))+2;
			auto unsigned long int Interval=pow(2.0,(double)Bit_of_interval);
			printf("The length of interval is %d ( %d bits )\n",Interval,Bit_of_interval);
			
			auto double Probabilities_symbols[The_number_of_species_of_symbols][2];//[256][0]=symbol  [256][1]=Probabilities
			for(i=0;i<The_number_of_species_of_symbols;i++){
				Probabilities_symbols[i][0]=(double)Count_symbols[i][0];//ASCII
				Probabilities_symbols[i][1]=(double)((double)Count_symbols[i][1]/(double)The_number_of_symbols_in_file);//The Probabilities of symbol
			}
//Initially						
			auto unsigned long int Low_bound=0;
			auto unsigned long int Up_bound=Interval-1;
			auto unsigned long int The_length_of_interval=Up_bound-Low_bound+1;

			auto int codeword_index=0;
			auto int codeword[8];
			auto int Register_E3=0;
			count=0;
			
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,Inf_file_extension[i_file]);	
			read_fp=fopen(str,"rb");
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_Output);
			remove(str);
			output_fp=fopen(str,"wb");
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_key);
			remove(str);
			key_fp=fopen(str,"wb");
			
			auto unsigned long int The_remaining_number_of_symbols=The_number_of_symbols_in_file;
//Start encoding
			while( The_remaining_number_of_symbols!=0 ){
               if(The_length_of_interval>=(int)((double)Interval*1.0/4.0)){
//Read symbol
						auto unsigned char read_ch=getc(read_fp);
						The_remaining_number_of_symbols=The_remaining_number_of_symbols-1;

						auto unsigned long int Low_Bound_interval[The_number_of_species_of_symbols];
						auto unsigned long int UP_Bound_interval[The_number_of_species_of_symbols];
						
						auto double Cumulative_probability=0.0;
						for(i=0;i<The_number_of_species_of_symbols;i++){
							Low_Bound_interval[i]=Low_bound+floor((Up_bound-Low_bound+1)*Cumulative_probability);
							UP_Bound_interval[i]=Low_bound+floor((Up_bound-Low_bound+1)*(Cumulative_probability+Probabilities_symbols[i][1]))-1;
							Cumulative_probability=Cumulative_probability+Probabilities_symbols[i][1];
						}
									
						auto int check_find_the_symbol=0;
						auto int Register_symbol_index=NULL;
						for(i=0;i<The_number_of_species_of_symbols;i++){
							if((int)Probabilities_symbols[i][0]==(int)read_ch){
								if(check_find_the_symbol==0){
									Register_symbol_index=i;
									check_find_the_symbol=1;
								}else{
									printf("ERROR for Symbol repetition\n");
									break;
								}
							}
						}
						
						if(check_find_the_symbol==0){
							printf("ERROR for check_find_the_symbol \n");
							break;
						}

                        Low_bound=Low_Bound_interval[Register_symbol_index];
                        Up_bound=UP_Bound_interval[Register_symbol_index]; 

//modified 2013.7.26 mark the following statements for TIAC
/*							

            			auto int idnex_minimum=NULL;
//						for(i=The_number_of_species_of_symbols-1;i>=0;i--){
//modified 2013.7.26  Find the minimum index with its interval size >= 2                      
                        for(i=0;i<The_number_of_species_of_symbols;i++){
							if((UP_Bound_interval[i]-Low_Bound_interval[i]+1)>=2){
								idnex_minimum=i;
							}
						}

							srand(rand());
							auto int key = rand()%2;
							auto unsigned char key_char=key;							
// Save key							
                            putc(key_char,key_fp);

							if (key==1){
							  if(Register_symbol_index==0){
								Up_bound = Up_bound+1;
							  }else if(Register_symbol_index==idnex_minimum){
								Low_bound = Low_bound+1;
							  }else if (Register_symbol_index < idnex_minimum){
								Low_bound = Low_bound+1;
								Up_bound = Up_bound+1;
			    	          }			    	          
                            }
*/                            				
				}else{ //if(The_length_of_interval>=(int)((double)Interval*1.0/4.0))
					printf("Error for The_length_of_interval\n");
					printf("The_length_of_interval : %d\n",The_length_of_interval);
					printf("(int)((double)Interval*1.0/4.0) : %d\n",(int)((double)Interval*1.0/4.0));
					break;
				}
		
//Do E1, E2, or E3 Mapping
              auto int stop = 0;
              while (!stop){
				if(Low_bound>=0	&& Up_bound<(int)((double)Interval*2.0/4.0)){//E1
				    Count_Mapping++;
					Up_bound=2*Up_bound+1;
					Low_bound=2*Low_bound;
					codeword[codeword_index]=0;
					codeword_index++;
					if(codeword_index==8){
						auto unsigned char Register_char=CodewordToChar(codeword);
						putc(Register_char,output_fp);
						Count_Output++;
						codeword_index=0;
					}
					
					for(k=0;k<Register_E3;k++){
						codeword[codeword_index]=1;
						codeword_index++;
						if(codeword_index==8){
							auto unsigned char Register_char=CodewordToChar(codeword);
							putc(Register_char,output_fp);
							Count_Output++;
							codeword_index=0;
						}
					}
					Register_E3=0;
				
				}else if(Low_bound>=(int)((double)Interval*2.0/4.0) && Up_bound<(int)Interval){//E2
				    Count_Mapping++;
		  			Up_bound=2*Up_bound+1-pow(2.0,(double)Bit_of_interval);
					Low_bound=2*Low_bound-pow(2.0,(double)Bit_of_interval);
					codeword[codeword_index]=1;
					codeword_index++;
					if(codeword_index==8){
						auto unsigned char Register_char=CodewordToChar(codeword);
						putc(Register_char,output_fp);
						Count_Output++;
						codeword_index=0;
					}
					
					for(k=0;k<Register_E3;k++){
						codeword[codeword_index]=0;
						codeword_index++;
						if(codeword_index==8){
							auto unsigned char Register_char=CodewordToChar(codeword);
							putc(Register_char,output_fp);
							Count_Output++;
							codeword_index=0;
						}
					}
					Register_E3=0;
					
				}else if(Low_bound>=(int)((double)Interval*1.0/4.0) && Up_bound<(int)((double)Interval*3.0/4.0)){//E3
				    Count_Mapping++;
					Up_bound=2*Up_bound+1-pow(2.0,(double)(Bit_of_interval-1));
					Low_bound=2*Low_bound-pow(2.0,(double)(Bit_of_interval-1));
					Register_E3++;	
				}else stop =1 ;
               }// while(!stop)
            }// while (The_remaining_number_of_symbols!=0 )	

			printf("Finally, Lower=%d;Upper=%d\n",Low_bound,Up_bound);
/*
            if(Register_E3!=0){
                Count_Mapping++;
	    	    printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"); 
    			codeword[codeword_index]=1;
				codeword_index++;
				if(codeword_index==8){
					auto unsigned char Register_char=CodewordToChar(codeword);
					putc(Register_char,output_fp);
					Count_Output++;
					codeword_index=0;					
				}
            }else if (Low_bound > 0){
                Count_Mapping++;
   			    codeword[codeword_index]=1;
				codeword_index++;
				if(codeword_index==8){
					auto unsigned char Register_char=CodewordToChar(codeword);
					putc(Register_char,output_fp);
					Count_Output++;
					codeword_index=0;					
				}
            }   	
*/
//
                Count_Mapping++;
   			    codeword[codeword_index]=1;
				codeword_index++;
				if(codeword_index==8){
					auto unsigned char Register_char=CodewordToChar(codeword);
					putc(Register_char,output_fp);
					Count_Output++;
					codeword_index=0;					
				}
//		
			if(codeword_index!=0){
				for(i=codeword_index;i<8;i++){
                    codeword[i]=0;
//					codeword[i]=1;
					if(i==7){
						auto unsigned char Register_char=CodewordToChar(codeword);
						putc(Register_char,output_fp);
						Count_Output++;
						codeword_index=0;
					}
				}
			}
			
			printf("Count_Mapping=%d\n",Count_Mapping);
			printf("transfer byte is %d\n",(int)ceil((double)(double)Count_Mapping/8.0));
			printf("Count_Output=%d\n\n",Count_Output);
			
			fclose(read_fp);
			fclose(output_fp);
			fclose(key_fp);
		}//if(fp)	
		
	}//for(i_file=0;i_file<12;i_file++)
		
	return 0;
}
