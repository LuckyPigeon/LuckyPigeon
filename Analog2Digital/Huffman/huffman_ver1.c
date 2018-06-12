/****************************************************************************/
/*                A simple implementation of the Huffman coding             */
/*                author: danielscocco@gmail.com                            */
/*                                                                          */
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Node of the huffman tree */
struct node{
    int value;
    char letter;
    struct node *left,*right;
};

typedef struct node Node;

int englishLetterFrequencies[256] = {0};
int subtrees,N;
char CodeWord[256][30];

//int* function(void)
void function(void)
{
	int i;
	int count = 0;
	char c;
	FILE * pFile;
//    int buffer = 0;

    pFile = fopen ("alice.txt" , "r");
    if (pFile == NULL) printf("Error opening file");
    else
    {
//
      while( ( c = getc(pFile) ) != EOF )
        englishLetterFrequencies[c]++;
//      {
//		buffer = c;
//        englishLetterFrequencies[buffer]++;
//		}
//		
/*
	  while(1){                           
		c=getc(pFile);
        if (feof(pFile))break;				
		buffer = c;
        englishLetterFrequencies[buffer]++;				
	  }		
*/				
	}
	fclose (pFile);
}

/* 81 = 8.1%, 128 = 12.8% and so on. The 27th frequency is the space. Source is Wikipedia */
//int englishLetterFrequencies [54] = {81, 15, 28, 43, 128, 23, 20, 61, 71, 2, 1, 40, 24, 69, 76, 20, 1, 61, 64, 91, 28, 10, 24, 1, 20, 1, 130};
//char englishLetter[27] = "abcdefghijklmnopqrstuvwxyz ";

/*finds and returns the small sub-tree in the forrest*/
int findSmaller (Node *array[], int differentFrom){
    int smaller;
    int i = 0;

    while (array[i]->value==-1)
        i++;
    smaller=i;
    if (i==differentFrom){
        i++;
        while (array[i]->value==-1)
            i++;
        smaller=i;
    }

    for (i=1;i<N;i++){
        if (array[i]->value==-1)
            continue;
        if (i==differentFrom)
            continue;
        if (array[i]->value<array[smaller]->value)
            smaller = i;
    }

    return smaller;
}

/*builds the huffman tree and returns its address by reference*/
void buildHuffmanTree(Node **tree){
    Node *temp;
    int i,j;
    int smallOne,smallTwo;
    
//    int* englishLetterFrequencies;
//    englishLetterFrequencies = function();
    function();
    Node *array[256];
 
    j=0;
	for (i=0;i<256;i++){
		if (englishLetterFrequencies[i]>0){
          array[j] = malloc(sizeof(Node));
          array[j]->value = englishLetterFrequencies[i];
          array[j]->letter = i;
          array[j]->left = NULL;
          array[j]->right = NULL;
          j++;
		}        
    }
    for (i=0;i<j;i++)
//     printf("% d  %d %c \n",array[i]->value,array[i]->letter,array[i]->letter);

// Node *array = (Node*)malloc(j * sizeof(Node));
    subtrees = j;
    N = j;
//    printf("# of subtrees= %d\n",j);

    while (subtrees>1){
        smallOne=findSmaller(array,-1);
        smallTwo=findSmaller(array,smallOne);
// printf("% d % d\n",smallOne,smallTwo);
        temp = array[smallOne];
        array[smallOne] = malloc(sizeof(Node));
        array[smallOne]->value=temp->value+array[smallTwo]->value;
        array[smallOne]->letter=127; // why 255會有問題 
//        printf("999\n");
        array[smallOne]->left=array[smallTwo];
        array[smallOne]->right=temp;
        array[smallTwo]->value=-1;
        subtrees--;
//  system("pause");
    }

    *tree = array[smallOne];

return;
}

void printTree1(Node *tree){
    if (tree->letter<127)
        printf("letter=%d\n",tree->letter);
    else{
        printTree(tree->left);
        printTree(tree->right);
    }

    return;
}
/* print the tree*/
//
void printTree(Node *tree, char cod[]){

    if (tree->letter<127){//leaf node                
//        printf("debug\n");
        int outt = (int)tree->letter;
//        printf("code %s  %c\n", cod, (char)outt); 
        strcpy(CodeWord[outt], cod);
    }
    else{
        char cod0[30];
        char cod1[30];
        strcpy(cod0, cod);
        strcat(cod0, "0");
        strcpy(cod1, cod);
        strcat(cod1, "1");
        printTree(tree->left, cod0);
        printTree(tree->right, cod1);
    }   
}
//


/*function to compress the input*/
void compressFile(FILE *input, FILE *output){
    char bit, c, x = 0;
    int i,j,length,tlen,bitsLeft = 8;
    int originalBytes = 0, compressedBits = 0;
    char mask = 1 << 7; //10000000

    while ((c=fgetc(input))!=EOF){
        originalBytes++;

        length = strlen(CodeWord[c]);tlen=length;
//        printf("char1= %c %s %d\n",c,CodeWord[c],length);
		        
        i=0;
        while (length>0){
            compressedBits++;
//            bit = CodeWord[c][i];
            if (CodeWord[c][i]=='0')bit=0;
            else bit=1;
            i++;
            x = x | bit;
            bitsLeft--;
            length--;
            if (bitsLeft==0){
                fputc(x,output);
//                printf("char2=");
//                for (j=0;j<8;j++){
//                   printf("%d ",x&mask);
//                   x = x << 1;
//                }
//                printf("\n");
                x = 0;
                bitsLeft = 8;
            }
            x = x << 1;
        }
    }

    if (bitsLeft!=8){
        x = x << (bitsLeft-1);
        fputc(x,output);
    }

    //print details of compression on the screen

    fprintf(stderr,"Original bytes = %d\n",originalBytes);
    fprintf(stderr,"Compressed bits = %d\n",compressedBits);
    fprintf(stderr,"Saved %.2f%% of memory\n",((float)compressedBits/(originalBytes*8))*100);

    return;
}


/*function to decompress the input*/
void decompressFile (FILE *input, FILE *output, Node *tree){
    Node *current = tree;
    char c,bit;
    char mask = 1 << 7; //10000000
    int i,j=148480;

//    while ((c=fgetc(input))!=EOF){
//
//      while ((c=fgetc(input))!=EOF){
        while(j>0){
        	c=fgetc(input);
//      while(1){
//		c=getc(input);
//        c=fgetc(input);
//        if (feof(input))break;	
//
//        printf("char1= %c %d\n",c,sizeof(c));
        for (i=0;i<8;i++){
            bit = c & mask;
            c = c << 1;
            if (bit==0){
                current = current->left;
                if (current->letter!=127){
                    fputc(current->letter,output);j--;
//                    printf("char2=%c\n",current->letter ); 
                    current = tree;
                }
            }

            else{
                current = current->right;
                if (current->letter!=127){
                    fputc(current->letter,output);j--;
//                    printf("char2=%c\n",current->letter ); 
                    
                    current = tree;
                }
            }
        }
      }

    return;
}


int main(){
    Node *tree;

    int compress;
    char filename[20];
    char code[30];
    FILE *input, *output;
    int i,j, n, temp = 0;


    buildHuffmanTree(&tree);
    printTree1(tree);
	system("pause");

    for(i=0; i<256; i++)
	  CodeWord[i][0]='\0';
	code[0]='\0';
//	code[0]='a';
//	printf("string=%s %d\n",code,strlen(code));
	printTree(tree,code);	    
    j=0;
    for(i=0; i<256; i++)
      if (strlen(CodeWord[i])>0){
	     printf("%d %c %s %d\n",i, i,CodeWord[i],strlen(CodeWord[i]));
	     j++;
      }
    printf("# of subtrees = %d\n",j);  
	system("pause");

    /*get input details from user*/
    printf("Type the name of the file to process:\n");
    scanf("%s",filename);
    printf("Type 1 to compress and 2 to decompress:\n");
    scanf("%d",&compress);

//    input = fopen(filename, "r");
//    output = fopen("output.txt","w");

    if (compress==1){
      input = fopen(filename, "r");
      output = fopen("output1","wb");
      compressFile(input,output);
    }
    else{
      input = fopen(filename, "rb");
      output = fopen("output.txt","w");
      decompressFile(input,output, tree);
    }

    return 0;
}

