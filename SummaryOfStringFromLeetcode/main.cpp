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

/********************************* 28. Implement strStr()(������)****************/
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

int main() {
	string s = "";
	//cout << lengthOfLongestSubstring(s) << endl;
	string text = "aabaaabaaac", pattern = "aabaaac";
	cout << strStr(text, pattern) << endl;
	return 0;
}