/* reads.c */
/* reads strings from file, and then display them on screen */ 
#include <stdio.h>

void main(){
	char string[81];
	FILE *fptr;

    fptr = fopen("textfile.txt","r");
	while(fgets(string,80,fptr)!=NULL) // read string
		printf("%s",string);	
	fclose(fptr);
}
