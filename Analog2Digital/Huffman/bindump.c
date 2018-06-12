/* bindump.c */
/* does binary dump of disk file*/ 
/* each line is ten ASCII codes followed by ten characters */

#include <stdio.h>
#define LENGTH 10
#define TRUE 0
#define FALSE -1

void main(argc,argv)
int argc;
char *argv[];
{
//	int argc;
//	char *argv[];
	FILE *fileptr;	//pointer to file
	unsigned int ch;
	int j, not_eof;
	unsigned char string[LENGTH+1]; //buffer for chars
	if (argc != 2){
		printf("Format: bindump file.xxx");
		exit(0);
	}
	if ( (fileptr = fopen(argv[1], "rb"))==NULL ){ //binary read
		printf("Can't open file %s.", argv[1]);
		exit(0);
	}
	not_eof = TRUE;
	do {
		for (j=0; j<LENGTH; j++){
			if ( (ch=getc(fileptr))==EOF ){
				not_eof = FALSE;
				printf("EOF=%x\n",EOF);
			}
			printf("%c ",ch);	 //print ASCII code in 16 ¶i¦ì 
//			if (ch!=EOF)printf("%3x ",ch);
			if (ch > 31) *(string+j)=ch; // ASCII (<=31) denotes nonprintable char
			else *(string+j)='.';
		}
		*(string+j)='\0';
		printf("    %s\n",string);
	}while (not_eof == TRUE);
	fclose(fileptr);		
}

