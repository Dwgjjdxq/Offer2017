/*
Summary of String from Leetcode
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**********************���ù�ϣ�����˫ָ������*******************************/
/************3. Longest Substring Without Repeating Characters(������)****************/
/*
��Ŀ������ظ��ַ����Ӵ�
����
���磬��"abcabcbb"�У������ظ��ַ�������ַ�����"abc"���䳤��Ϊ 3��
���ڣ�"bbbbb"�������ظ��ַ�������ַ���Ϊ"b"������Ϊ1��
*/

// Summary
/*
	1. ���ȴ���һ����СΪ256��bool���͵Ĺ�ϣ��;
	2. ��������ָ�룬һ����Ϊÿ���ҵ����ظ��ַ��Ӵ�����ʼλ�ã���һ����Ϊ�˶�ָ�룬��ǰ���ҵ�ǰ�ַ��Ƿ��ڹ�ϣ����;
	3. ����ǰָ����ָ�ַ��Ѿ����ڣ����˳�ѭ���������ǰָ������ʼָ���λ��֮�����֮ǰ�õ��Ľ��ȡ���;
	4. ��ʱҪ�ж�һ���˶�ָ���Ƿ��Ѿ������ַ���ĩ��;
	5. ������滹���ַ���������ʼָ�뿪ʼ����ƶ���ֱ���ҵ���һ�γ����ظ����Ǹ��ַ����ڴ��ڼ䣬���������ַ����޳���ϣ�����������Ϊfalse
	6. �ҵ� ��һ�γ����ظ����Ǹ��ַ�λ��֮�󣬽�����Ϊfalse, ��ʼָ�뵽��һ��λ�ÿ�����һ�ֲ������ظ��ַ����Ӵ�
*/
int lengthOfLongestSubstring(string s) {
	if (s.empty())
		return 0;
	vector<bool> have(256, false); // ����һ����ϣ��ȫ����Ϊ�����ڣ�����
	int res = 0;
	for (int start = 0, cur = 0;; ++start) {
		while (cur < s.size() && !have[s[cur]]) // �����жϵ�ǰ�ַ��Ƿ��ڱ���
			have[s[cur++]] = true;	// ���ھ���Ϊtrue
		res = max(res, cur - start);	// �Ƚϵ�ǰ�������ظ��ַ��Ӵ�
		if (cur >= s.length())	// ѭ���˳�����
			break;

		while (s[start] != s[cur])	// ��Ϊǰ���Ѿ��ҵ�һ�����ظ����Ӵ������������������ģ�
			have[s[start++]] = false;// �ͱ���ѱ��Ӵ��� "��һ�γ��ָ��ظ��ַ�֮ǰ���ַ�" ȫ�����
		// ��Ϊ�����ڣ�����
		have[s[start]] = false;		// �ҵ� ����һ�����ָ��ظ��ַ���λ�á�֮�󣬰Ѹ�λ�ö�Ӧ�Ĺ�ϣֵ��Ϊfalse
		// ��ʾ������,Ȼ����ת��forѭ���У�������һ���ַ����¿�ʼ����
	}// for
	return res;
}

/********************************* 28. Implement strStr()(�ǳ�������KMP�㷨)****************/
//������
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
//KMP�㷨
vector<int> getNext(const string & pattern) {
	if (pattern.empty()) return vector<int>();
	int start = 0, cur = 1;
	vector<int> next(pattern.size());
	next[0] = 0;
	for (; cur < pattern.size(); ++cur) {
		while (start > 0 && pattern[cur] != pattern[start])
			start = next[start - 1];
		if (pattern[cur] == pattern[start])
			start++;
		next[cur] = start;
	}
	return next;
}
int KMP(const string & str, const string & pattern) {
	if (str.size() < pattern.size()) return -1;
	if (pattern.empty()) return 0;

	int si = 0, pi = 0;
	auto next = getNext(pattern);
	for (; si < str.size(); ++si) {
		while (pi > 0 && str[si] != pattern[pi])
			pi = next[pi - 1];
		if (str[si] == pattern[pi])
			++pi;
		if (pi == pattern.size())
			return si - pi + 1;
	}
	return -1;
}

/********************************* 125. ��Ч���Ĵ�(������)****************/
/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.
*/
/*
���ú�����int isalnum(int c); // ���c�Ƿ�����ĸ�������֣�����Ϊtrue������Ϊfalse
		 int toupper(int c); // ���ַ�cת��Ϊ��д
		 int tolower(int c); // ���ַ�cת��ΪСд
*/
bool isPalindrome(string s) {
	if (s.empty() || s.size() == 1) return true;
	int left = 0, right = s.size() - 1;
	while (left <= right) {
		if (!isalnum(s[left]))
			++left;
		else if (!isalnum(s[right]))
			--right;
		else if (toupper(s[left++]) != toupper(s[right--])) return false;
	}
	return true;
}

/*********************************345. Reverse Vowels of a String****************/
/*
	��ת�ַ�����Ԫ����ĸ��˳��Ԫ����ĸ��a e i o u
*/
bool isVowels(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return true;
	else return false;
}
string reverseVowels(string s) {
	if (s.empty() || s.size() == 1) return s;
	int left = 0, right = s.size() - 1;
	while (left < right) {
		if (!isVowels(tolower(s[left])))
			++left;
		else if (!isVowels(tolower(s[right])))
			--right;
		else if (isVowels(tolower(s[left])) && isVowels(tolower(s[right]))) {
			int temp = s[left];
			s[left] = s[right];
			s[right] = temp;
		}//else
	}//while
	return s;
}




int main() {
	string s = "";
	//cout << lengthOfLongestSubstring(s) << endl;
	string text = "aabaaabaaac", pattern = "aabaaac";
	cout << strStr(text, pattern) << endl;
	return 0;
}