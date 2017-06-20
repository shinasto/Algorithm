#include <iostream>
#include <string.h>
using namespace std;

char arr[100001];
char reverse[100001];

void setPartitions(char str[], int pi[]) {
	int size = strlen(str);
	int matched = 0;
	for(int i=1; i<size; i++) {
		while(matched != 0 && str[i] != str[matched])
			matched = pi[matched-1];
		if(str[i] == str[matched])
			pi[i] = ++matched;
	}
}

int kmp(char str[]) {
	int size = strlen(str);
	// revere string
	for(int i=0; i<size; i++)
		reverse[size-i-1] = arr[i];
	reverse[size] = 0;

	int* pi = new int[size];
	setPartitions(reverse, pi);
	int matched = 0;
	for(int i=0; i<size; i++) {
		if(matched != 0 && str[i] != reverse[matched])
			matched = pi[matched-1];
		if(str[i] == reverse[matched]) {
			matched++;
		}
	}
	delete[] pi;
	return matched;
}

int main() {
	int tc;
	cin >> tc;
	while(tc-- > 0) {
		cin >> arr;
		int len = strlen(arr);
		int matched = kmp(arr);
		cout << len + (len - matched) << endl;
	}
	return 0;
}
