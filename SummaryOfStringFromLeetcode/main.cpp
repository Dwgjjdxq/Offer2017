/*
Summary of String from Leetcode
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**********************利用哈希表或者双指针类型*******************************/
/************3. Longest Substring Without Repeating Characters(不熟练)****************/
/*
题目：最长无重复字符的子串
样例
例如，在"abcabcbb"中，其无重复字符的最长子字符串是"abc"，其长度为 3。
对于，"bbbbb"，其无重复字符的最长子字符串为"b"，长度为1。
*/

// Summary
/*
	1. 首先创建一个大小为256的bool类型的哈希表;
	2. 设置两个指针，一个作为每次找到无重复字符子串的起始位置，另一个作为运动指针，向前查找当前字符是否在哈希表中;
	3. 当当前指针所指字符已经存在，则退出循环，求出当前指针与起始指针的位置之差，并与之前得到的结果取最大;
	4. 此时要判断一下运动指针是否已经到了字符串末端;
	5. 如果后面还有字符，则让起始指针开始向后移动，直到找到第一次出现重复的那个字符，在此期间，将遇到的字符做剔除哈希表操作，即置为false
	6. 找到 第一次出现重复的那个字符位置之后，将其置为false, 起始指针到下一个位置开启新一轮查找无重复字符的子串
*/
int lengthOfLongestSubstring(string s) {
	if (s.empty())
		return 0;
	vector<bool> have(256, false); // 构建一个哈希表，全部置为不存在，即否
	int res = 0;
	for (int start = 0, cur = 0;; ++start) {
		while (cur < s.size() && !have[s[cur]]) // 依次判断当前字符是否在表中
			have[s[cur++]] = true;	// 存在就置为true
		res = max(res, cur - start);	// 比较当前最大的无重复字符子串
		if (cur >= s.length())	// 循环退出出口
			break;

		while (s[start] != s[cur])	// 因为前面已经找到一个不重复的子串，如果想继续找其他的，
			have[s[start++]] = false;// 就必须把本子串中 "第一次出现该重复字符之前的字符" 全部清空
		// 置为不存在，即否
		have[s[start]] = false;		// 找到 “第一个出现该重复字符的位置”之后，把该位置对应的哈希值置为false
		// 表示不存在,然后跳转到for循环中，换到下一个字符重新开始查找
	}// for
	return res;
}

/********************************* 28. Implement strStr()(不熟练)****************/
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
//KMP算法
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