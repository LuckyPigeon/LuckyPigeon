#include <stdio.h>
#include <stdlib.h>
int main(){
	FILE *fp;
	fp=fopen("testSample.txt","rb");
	while(!feof(fp)){
		auto unsigned char ch=getc(fp);
		printf("%c [%-3d]\n",ch,ch);
		printf("===========\n");
	}
	fclose(fp);
	return 0;
}
