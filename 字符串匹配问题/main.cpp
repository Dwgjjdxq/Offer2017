
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void getNext(const string & pattern, int next[]) {
	if (pattern.empty()) return;
	next[0] = 0;
	int start = 0, cur = 1;
	for (; cur < pattern.length(); ++cur) {
		while (start > 1 && pattern[start] == pattern[cur])
			start = next[start - 1];
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
		}
	}
	delete[]next;
	return -1;
}

int main() {
	string text = "acdeacdf", pattern = "acde";
	cout << KMP(text, pattern) << endl;
	return 0;
}