#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int a, b, c;
		cin >> a >> b >> c;
		if((a >= 60) && (b >= 60) && (c >= 60)) cout << "P" << endl;
		else if((a < 60 && b >= 60 && c >= 60) || (a >= 60 && b < 60 && c >= 60) || (a >= 60 && b >= 60 && c < 60)){
			if(a + b + c >= 220) cout << "P" << endl;
			else cout << "M" << endl;
		}
		else if((a < 60 && b < 60 && c >= 80) || (a < 60 && b >= 80 && c < 60) || (a >= 80 && b < 60 && c < 60)) cout << "M" << endl;
		else cout << "F" << endl;
	}
	return 0;
}
