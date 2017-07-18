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




int main() {

	return 0;
}