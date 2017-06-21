#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

char str[2][10001];

void getPartitions(char arr[], int pi[]) {
	int size = strlen(arr);
	int match = 0;
	for(int i=1; i<size; i++) {
		if(match != 0 && arr[match] != arr[i]) {
			match = pi[match-1];
		}
		if(arr[match] == arr[i]) {
			pi[i] = ++match;
		}
	}
}

int kmp(char arr1[], char arr2[]) {
	int size_a = strlen(arr1);
	int size_b = strlen(arr2);
	int* pi = new int[strlen(arr1)];
	getPartitions(arr1, pi);
	int match = 0;
	for(int i=0; i<size_b; i++) {
		if(match != 0 && arr1[match] != arr2[i]) {
			match = pi[match-1];
		}
		if(arr1[match] == arr2[i]) {
			if(++match == size_a)
				return i - size_a + 1;
		}
	}
	return -1;
}

int getShiftCount(char str[][10001], int s) {
	char str2[20001];
	int size = strlen(str[1]);
	for(int i=0; i<size; i++)
		str2[i] = str2[i+size] = str[1][i];
	int ret = kmp(str[0], str2);
	return ret;
}

int main() {
//	ifstream fs("input");
//	cin.rdbuf(fs.rdbuf());
	int tc;
	cin >> tc;
	while(tc-- > 0) {
		int n, shift = 0;
		cin >> n;
		cin >> str[0];
		for(int i=1; i<=n; i++) {
			cin >> str[i%2];
			shift += getShiftCount(str, i);
		}
		cout << shift << endl;
	}
	return 0;
}
