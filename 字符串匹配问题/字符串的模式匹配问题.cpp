#include<iostream>
#include <memory>
using namespace std;
/*字符串的模式匹配问题*/
/*
http://blog.csdn.net/v_july_v/article/details/7041827
*/
/*暴力匹配法(朴素字符串匹配算法) O(mn)*/
int ViolentMatch(char* P, char* S) {
	int lenP = strlen(P);
	int lenS = strlen(S);
	int i = 0, j = 0;
	while (i < lenP && j < lenS) {
		if (P[i] == S[j]) {
			++i; ++j;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == lenS)
		return i - j;
	else return -1;
}

/*KMP算法 O(m+n)*/
void GetNext(char * P, int next[]) {
	int lenP = strlen(P);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < lenP - 1){
		if (k == -1 || P[j] == P[k]) {
			++j; ++k;
			if (P[j] != P[k]) {
				next[j] = k;
			}
			else {
				next[j] = next[k];
			}
		}
		else {
			k = next[k]; // 递推求k，即将next
		}
	}
}
int KMP(char* S, char* P) {
	int lenS = strlen(S);
	int lenP = strlen(P);
	int i = 0, j = 0;
	int *next = new int[lenP];
	GetNext(P, next);
	for (int i = 0; i < 7; ++i) {
		cout << next[i] << " ";
	}
	cout << endl;
	while (i < lenS && j < lenP) {
		if (j == -1 || S[i] == P[j]) {
			++i; ++j;
		}
		else j = next[j];
	}
	if (j == lenP) {
		delete[] next;
		return i - j;
	}
	else {
		delete[] next;
		return -1;
	}
}

int main() {
	char S[] = "bbcabcdababcdabcdabde"; 
	char P[] = "abcdabd";

	cout << ViolentMatch(S, P) << endl;
	cout << KMP(S, P) << endl;
	return 0;
}