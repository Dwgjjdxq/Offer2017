//暴力法
int strStr(const string & str, const string & pattern) {
	if (str.size() < pattern.size()) return -1;
	if (pattern.empty()) return 0;

	for (int i = 0; i < str.size(); ++i) {
		int j = 0;
		for (; j < pattern.size(); ++j) {
			if (str[i + j] != pattern[j])
				break;
		}//for
		if (j == pattern.size())
			return i;
	}//for
	return -1;
}

/*
	kmp算法
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*构建next数组*/
void getNext(const string & pattern, int next[]) {
	if (pattern.empty()) return;
	next[0] = 0;
	int start = 0, cur = 1;
	for (; cur < pattern.length(); ++cur) {
		while (start > 0 && pattern[start] != pattern[cur])
			start = next[start - 1];	// 公共前后缀的前缀的最后一位
		if (pattern[start] == pattern[cur]) ++start;
		next[cur] = start;
	}//for
}//getNext

int KMP(const string & text, const string & pattern) {
	if (text.length() < pattern.length()) return -1;
	if (pattern.empty()) return 0;
	int *next = new int[pattern.length()];

	getNext(pattern, next);
	
	int pi = 0;
	for (int ti = 0; ti < text.length(); ++ti) {
		while (pi > 0 && pattern[pi] != text[ti])
			pi = next[pi - 1];
		if (pattern[pi] == text[ti])
			pi++;
		if (pi == pattern.length()) {
			delete[]next;
			return ti - pi + 1;
		}//if 匹配完成
	}//for
	delete[]next;
	return -1;
}
 
int main() {
	string text = "aabaaabaaac", pattern = "aabaaac";
	cout << KMP(text, pattern) << endl;
	return 0;
}