#include <cstdio>

#define dct_size static_cast<int>(argv[1][0]) - 48
void dct_func(double data[dct_size][dct_size], double dct[dct_size][dct_size]);

int main(int argc, char* argv[]){
	printf("%s\n", argv[1]);
	printf("%d\n", static_cast<int>(argv[1][0]) - 48);
	printf("%d\n", dct_size);
	int data[dct_size];
	data[0] = 1;
	return 0;
}
