#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define HEX2I(X) (((X)<'A')?(X-'0'):(X-'A'+10))
#define I2HEX(X) (((X)<10)?('0'+X):(X-10+'A'))
#define MIN(X,Y) (((X)<(Y))?(X):(Y))
#define MAX(X,Y) (((X)<(Y))?(Y):(X))
typedef long long ll;
const int HEX_N = 36;
const int HEX_POW[4] = {1, 36, 1296, 46656};

void normalize(vector<int>& num) {
    num.push_back(0);
    for (int i = 0; i < num.size(); i++) {
        if (num[i] < 0) {
            int borrow = (abs(num[i]) + 35) / HEX_N;
            num[i + 1] -= borrow;
            num[i] += borrow * HEX_N;
        } else if (num[i] >= HEX_N) {
            num[i + 1] += num[i] / HEX_N;
            num[i] %= HEX_N;
        }
    }
    if (num.back() == 0) num.pop_back();
}

vector<int> multiple(vector<int> a, vector<int> b) {
    vector<int> c;
    long long al = 0l, bl = 0l;
    for (int i = 0; i < a.size(); i++)
        al += a[i] * HEX_POW[i];
    for (int j = 0; j < b.size(); j++)
        bl += b[j] * HEX_POW[j];
    long long ret = al * bl;
    while(ret > 0) {
        c.push_back(ret % HEX_N);
        ret = ret / HEX_N;
    }
    return c;
}

void addTo(vector<int>& a, vector<int>& b) {
    a.resize(MAX(a.size(), b.size()));
    for(int i=0; i<b.size(); i++) a[i] += b[i];
    normalize(a);
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
    a.resize(MAX(a.size(), b.size() + k));
    for (int i = 0; i < b.size(); i++) a[i + k] += b[i];
    normalize(a);
}

void subFrom(vector<int>& a, vector<int>& b) {
    a.resize(MAX(a.size(), b.size()) + 1);
    for(int i=0; i<b.size(); i++) a[i] -= b[i];
    normalize(a);
}

vector<int> karatsuba(vector<int> a, vector<int> b) {
    int a_s = a.size();
    int b_s = b.size();
    if(a_s < b_s) return karatsuba(b, a);
    if(a_s == 0 || b.size() == 0) return vector<int>();
    if(a_s <= 4) return multiple(a, b);
    
    int half = a_s / 2;
    vector<int> a0(a.begin(), a.begin()+half);
    vector<int> a1(a.begin()+half, a.end());
    vector<int> b0(b.begin(), b.begin() + MIN(b.size(), half));
    vector<int> b1(b.begin() + MIN(b.size(), half), b.end());
    
    vector<int> z0 = karatsuba(a0, b0);
    vector<int> z2 = karatsuba(a1, b1);
    addTo(a0, a1);
    addTo(b0, b1);
 
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    
    vector<int> ret;
    addTo(ret, z0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);
    return ret;
}

void multi(char* result, char* h1, char* h2) {
    vector<int> a1, a2;
    int index = 0;
    while(h1[index] != '\0'){
        a1.push_back(HEX2I(h1[index]));
        index++;
    }
    index = 0;
    while(h2[index] != '\0'){
        a2.push_back(HEX2I(h2[index]));
        index++;
    }
    
    vector<int> ret = karatsuba(a1, a2);
    
    index = 0;
    for(int i=ret.size()-1; i>=0; i--) {
        result[index] = I2HEX(ret[i]);
        index++;
    }
    result[index] = '\0';
    
    cout << "multi function" << endl;
}
