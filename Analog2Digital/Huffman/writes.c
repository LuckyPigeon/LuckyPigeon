/* writes.c */
/* writes strings typed at keyboard to file */ 
#include <stdio.h>

void main(){
	char string[81];
	FILE *fptr;

    fptr = fopen("textfile.txt", "w");
	while(strlen(gets(string))>0){
		fputs(string,fptr);
		fputs("\n",fptr);		
	}
	fclose(fptr);
}
