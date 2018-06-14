#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	string a[4];
	a[0] = "Hi";
	a[1] = "Hello";
	a[2] = "How do you do";
	a[3] = "How are you";

	int count = 0;
	bool flag = false;

	string in;
	while(getline(cin, in)){
		for(int i = 0; i < 4; i++){
			if(a[i] == in){ flag = true; }
		}

		if(flag){
			cout << a[count % 4] << endl;
			count++;
		}

		else{ 
			cout << "Sorry" << endl;
			count--;
		}
		flag = false;
	}
	
	return 0;
}
