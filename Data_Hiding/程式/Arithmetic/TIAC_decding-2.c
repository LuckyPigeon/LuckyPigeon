/******************************************************
 * Research Group of Information Coding
 * Made by Jyun Ying Huang 2013/05/30
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

int t_star(int t, unsigned long int  LowBound, unsigned long int UpBound, unsigned long int TotalCount){
	auto int T;
	auto unsigned long int range=(UpBound-LowBound+1);
	T=floor( (double)((t-LowBound+1)*TotalCount-1)/(double)(range) );
	return T;
}

int shift(int codeword[],int SizeOfCodeword){
	auto int i;
	for(i=0;i<SizeOfCodeword;i++)
	codeword[i]=codeword[i+1];
	codeword[SizeOfCodeword-1]=3;
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
	char str_Inf[20]={"_inf.txt"};
	char str_icg[20]={".icg"};
	char str_Output[20]={"_icg"};
	char str_key[100]={".key"};
	char str[100];
		
	for(i_file=0;i_file<13;i_file++){
				
		FILE *fp,*output_fp,*read_fp,*key_fp;
		cleat_string(str);
		Merger(str,Inf_file[i_file]);
		Merger(str,str_Inf);
		fp=fopen(str,"r");
		
		if(!fp){
			printf("The file'%s' does not exist!!\n",str);
		}else{
			auto int i,j;
			auto int count=0; 
			auto unsigned long int count_output=0;
			
			unsigned long int *Register_Count_symbol;
			Register_Count_symbol=(unsigned long int*)malloc(sizeof(unsigned long int)*256);
/*			
			while(!feof(fp)){
				fscanf(fp,"%d",&Register_Count_symbol[count]);
				count++;
			}
*/			
//modified 2013/0728 
			while(1){                           
				fscanf(fp,"%d",&Register_Count_symbol[count]);
                if (feof(fp))break;				
                count++;
			}
			fclose(fp);
			remove(str);
			
			
			
			auto unsigned long int The_number_of_symbols_in_file=0;
			for(i=0;i<256;i++)
			The_number_of_symbols_in_file=The_number_of_symbols_in_file+Register_Count_symbol[i];
			
			auto unsigned long int The_number_of_species_of_symbols=0;
			for(i=0;i<256;i++){
				if(Register_Count_symbol[i]!=0)
				The_number_of_species_of_symbols++;
			}
			printf("The number of symbols in file is %d ( %d symbols )\n",The_number_of_symbols_in_file,The_number_of_species_of_symbols);
			
			count=0;
			auto unsigned long int Count_symbols[The_number_of_species_of_symbols][2];
			for(i=0;i<256;i++){
				if(Register_Count_symbol[i]!=0){
					Count_symbols[count][0]=i;
					Count_symbols[count][1]=Register_Count_symbol[i];
					count++;
				}
			}
			free(Register_Count_symbol);
			
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
				//printf("Count_symbols[%-3d]=%d\n",Count_symbols[i][0],Count_symbols[i][1]);
			}
			
			auto int Symbol_state[The_number_of_species_of_symbols][3];
			Symbol_state[0][0]=Count_symbols[0][0];
			Symbol_state[0][1]=0;
			Symbol_state[0][2]=0+Count_symbols[0][1]-1;
			for(i=1;i<The_number_of_species_of_symbols;i++){
				Symbol_state[i][0]=Count_symbols[i][0];
				Symbol_state[i][1]=Symbol_state[i-1][2]+1;
				Symbol_state[i][2]=Symbol_state[i][1]+Count_symbols[i][1]-1;
			}
			//for(i=0;i<The_number_of_species_of_symbols;i++)
			//printf("%-3d [%d,%d]\n",Symbol_state[i][0],Symbol_state[i][1],Symbol_state[i][2]);
			

			
			auto int Bit_of_interval= ceil(log((double)(The_number_of_symbols_in_file))/log(2.0))+2;
			auto unsigned long int Interval=pow(2.0,(double)Bit_of_interval);
			printf("The length of interval is %d ( %d bits )\n",Interval,Bit_of_interval);
			
			auto double Probabilities_symbols[The_number_of_species_of_symbols][2];
			for(i=0;i<The_number_of_species_of_symbols;i++){
				Probabilities_symbols[i][0]=(double)Count_symbols[i][0];
				Probabilities_symbols[i][1]=(double)((double)Count_symbols[i][1]/(double)The_number_of_symbols_in_file);//The Probabilities of symbol
			}
			
			auto unsigned long int Low_bound=0;
			auto unsigned long int Up_bound=Interval-1;
			auto unsigned long int The_length_of_interval=Up_bound-Low_bound+1;
			count=0;
			
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_icg);			
			read_fp=fopen(str,"rb");
			printf("Read the compressed file:%s\n",str);
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);	
			Merger(str,str_Output);		
			Merger(str,Inf_file_extension[i_file]);	
			output_fp=fopen(str,"wb");
			printf("Decode to %s\n",str);
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_key);
			key_fp=fopen(str,"rb");
			
			
			auto int codeword_index=0;
			auto int codeword[(Bit_of_interval+8)];
			for(i=0;i<(Bit_of_interval+8);i++)
			codeword[i]=3;
			
			auto unsigned long int Count_Output=0;
			auto unsigned long int The_remaining_number_of_symbols=The_number_of_symbols_in_file;
 
            
//Initialize reading the compressed data into the codeword buffer
/*
            while(codeword_index<Bit_of_interval){
					auto unsigned char read_char=getc(read_fp);
					auto int sum_char=read_char;
                    auto int input_codeword[8];
					for(i=0;i<8;i++){
						input_codeword[7-i]=sum_char%2;
						sum_char=sum_char-(sum_char%2);
						sum_char=sum_char/2;
					}
					for(i=0;i<8;i++)
					codeword[codeword_index+i]=input_codeword[i];
					codeword_index=codeword_index+8;
            }
*/            
//Start decoding
            auto unsigned long int T_Value;
//
			while(The_remaining_number_of_symbols!=0){
//				
//				if(codeword_index<Bit_of_interval){
				while(codeword_index<Bit_of_interval){
					auto unsigned char read_char=getc(read_fp);
					auto int sum_char=read_char;
                    auto int input_codeword[8];
					for(i=0;i<8;i++){
						input_codeword[7-i]=sum_char%2;
						sum_char=sum_char-(sum_char%2);
						sum_char=sum_char/2;
					}
					for(i=0;i<8;i++)
					codeword[codeword_index+i]=input_codeword[i];
					codeword_index=codeword_index+8;
				}
//
				T_Value=0;
				for(i=0;i<Bit_of_interval;i++){
					T_Value=T_Value+(int)(codeword[i]*pow(2.0,(double)(Bit_of_interval-1-i)));
				}
//
                if(The_length_of_interval>=(int)((double)Interval*1.0/4.0)){
//
						//Partition Algorithm
						auto unsigned long int Low_Bound_interval[The_number_of_species_of_symbols];
						auto unsigned long int UP_Bound_interval[The_number_of_species_of_symbols];
						auto double Cumulative_probability=0.0;
						for(i=0;i<The_number_of_species_of_symbols;i++){
							Low_Bound_interval[i]=Low_bound+floor((Up_bound-Low_bound+1)*Cumulative_probability);
							UP_Bound_interval[i]=Low_bound+floor((Up_bound-Low_bound+1)*(Cumulative_probability+Probabilities_symbols[i][1]))-1;
							if(UP_Bound_interval[i]<Low_Bound_interval[i]){
								printf("ERROR for the up bound and low bound of symbol\n");
								printf("ERROR for ASCII=%d\n",(int)Probabilities_symbols[i][0]);
								printf("ERROR for Low Bound=%d\n",Low_Bound_interval[i]);
								printf("ERROR for UP Bound=%d\n",UP_Bound_interval[i]);
								break;
							}
							Cumulative_probability=Cumulative_probability+Probabilities_symbols[i][1];
						}

// with key : update the lower bound & upper bound of each interval
                        auto int idnex_minimum=NULL;
                        for(i=0;i<The_number_of_species_of_symbols;i++){
							if((UP_Bound_interval[i]-Low_Bound_interval[i]+1)>=2){
								idnex_minimum=i;
							}
						}	                        
						auto unsigned char key_ch=getc(key_fp);
						auto int key = key_ch;

                        if (key==1){
                           for (i=0; i<The_number_of_species_of_symbols;i++){         
							  if(i==0){
								UP_Bound_interval[i]++;
							  }else if(i==idnex_minimum){
								Low_Bound_interval[i]++;
							  }else if ( i < idnex_minimum){
								Low_Bound_interval[i]++;
								UP_Bound_interval[i]++;
			    	          }
                           }	
                         }
//						
//Output the char what we will decode
//                        auto unsigned long int T_Star_Value=t_star(T_Value, Low_bound, Up_bound, The_number_of_symbols_in_file);

						auto int check_find_the_symbol=0;
						auto int Register_symbol_index=NULL;
						for(i=0;i<The_number_of_species_of_symbols;i++){
//                            if(T_Star_Value>=Symbol_state[i][1] && T_Star_Value<=Symbol_state[i][2]){
							if(T_Value>=Low_Bound_interval[i] && T_Value<=UP_Bound_interval[i]){
								Register_symbol_index=i;
								check_find_the_symbol=check_find_the_symbol+1;
							}
						}	
						if(check_find_the_symbol==1){
								auto unsigned char Output_ch=Symbol_state[Register_symbol_index][0];
								count_output++;
								//printf("Output[%d] %d\n",count_output,Output_ch);
								putc(Output_ch,output_fp);
								The_remaining_number_of_symbols=The_remaining_number_of_symbols-1;
								Count_Output++;
						}else{
								printf("ERROR for check_find_the_symbol=%d\n",check_find_the_symbol);
								break;
						}

//New Source interval
                   Low_bound=Low_Bound_interval[Register_symbol_index];
                   Up_bound=UP_Bound_interval[Register_symbol_index]; 

// Do E1, E2, or E3 Mapping
                   auto int stop = 0;   
                   while (!stop){
					 if(Low_bound>=0	&& Up_bound<(int)((double)Interval*2.0/4.0)){//E1
						//discard 0
						if(codeword[0]==0){
							Up_bound=2*Up_bound+1;
							Low_bound=2*Low_bound;
							shift(codeword,(Bit_of_interval+8));
							codeword_index=codeword_index-1;
						}else{
							printf("Error for E1 Mapping!\n");
							break;
						}
					
				  	 }else if(Low_bound>=(int)((double)Interval*2.0/4.0) && Up_bound<(int)Interval){//E2
						if(codeword[0]==1){
							Up_bound=2*Up_bound+1-pow(2.0,(double)Bit_of_interval);
							Low_bound=2*Low_bound-pow(2.0,(double)Bit_of_interval);
							shift(codeword,(Bit_of_interval+8));
							codeword_index=codeword_index-1;
						}else{
							printf("Error for E2 Mapping!\n");
							break;
						}
					
					 }else if(Low_bound>=(int)((double)Interval*1.0/4.0) && Up_bound<(int)((double)Interval*3.0/4.0)){//E3
					
						//discard 3
						if((codeword[1]+codeword[0])==1){
							Up_bound=2*Up_bound+1-pow(2.0,(double)(Bit_of_interval-1));
							Low_bound=2*Low_bound-pow(2.0,(double)(Bit_of_interval-1));
							auto int buf_1=codeword[0];
							codeword[0]=codeword[1];
							codeword[1]=buf_1;
							shift(codeword,(Bit_of_interval+8));
							codeword_index=codeword_index-1;
						}else{
							printf("Error for E3 Mapping!\n");
							break;
						}
                     }else stop = 1;	
                   } // while(!stop)
//
                }else{ //if(The_length_of_interval>=(int)((double)Interval*1.0/4.0))
					printf("The error for The_length_of_interval\n");
					break;				
				}				
             } //while(The_remaining_number_of_symbols!=0) 			
//
			printf("Count_Output=%d\n\n",Count_Output);
			
			fclose(read_fp);
			fclose(output_fp);
			fclose(key_fp);
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_icg);			
			remove(str);
			
			cleat_string(str);
			Merger(str,Inf_file[i_file]);
			Merger(str,str_key);
			remove(str);
						
		}//	if(fp)
		
	} //for(i_file=0;i_file<12;i_file++)	
	
	return 0;
}
