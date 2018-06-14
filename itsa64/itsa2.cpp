#include <iostream>
#include <cmath>

using namespace std;

int main(){
	bool flag = true;
	int now_prime = 2, prime[1001];
	for(int i = 2; i <= 1000; i++){
		for(int j = 2; j <= floor(sqrt(i)); j++){
			if(i % j == 0){
				flag = false;
			}
		}
		
		if(flag){
			for(int j = now_prime; j <= i; j++){
				prime[j] = now_prime;
			}

			now_prime = i;
		}

		flag = true;
	}

	for(int i = now_prime; i <= 1000; i++){
		prime[i] = now_prime;
	}

	int input;
	while(cin >> input) cout << prime[input] << endl;

	return 0;
}
