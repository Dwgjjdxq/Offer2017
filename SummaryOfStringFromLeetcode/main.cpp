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

/********************************* 28. Implement strStr()(非常不熟练KMP算法)****************/
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

/********************************* 125. 有效回文串(不熟练)****************/
/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.
*/
/*
常用函数：int isalnum(int c); // 检查c是否是字母或者数字，是则为true，否则为false
		 int toupper(int c); // 将字符c转换为大写
		 int tolower(int c); // 将字符c转换为小写
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
	翻转字符串中元音字母的顺序，元音字母：a e i o u
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

/*********************************哈希表方法**************************/
/**********************************49. Group Anagrams颠倒的字符串分组***************/
/*
将颠倒后的字符串分别分为一组
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:
[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/
/*	// 默认字符串字符均为小写字母
	总结：
	1. 在一堆零散的字符串数组中将含有相同个数相同字符的字符串分为一组，考虑利用哈希思想构建一个map
	2. 该map的key值应为排好序之后的字符串str, 对应value应是vector<string>,即一个子数组
	3. 
*/
#include <map>
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	if (strs.empty())
		return vector<vector<string>>();
	vector<vector<string>> res;

	//sort(strs.begin(), strs.end());
	/*利用哈希思想构建一张map映射关系， string表示表示当前字符串排好序的临时字符串， vector<string>表示存放当前原始字符串*/
	map<string, vector<string>> mp;

	for (int i = 0; i < strs.size(); ++i) {
		string str = strs[i];
		/*对临时字符串排序，作为map的key值， 将原始字符串作为对应value值*/
		sort(str.begin(), str.end());
		mp[str].push_back(strs[i]);
	}
	/*将map相同key对应的value数组，整合在大数组中*/
	for (auto a : mp) {
		res.push_back(a.second);
	}
	/* 另一种指针写法
	for (map<string, vector<string>>::iterator iter = mp.begin(); iter != mp.end(); ++iter)
		res.push_back(iter->second);
	*/
	return res;	
}

/**************************76. Minimum Window Substring最小包含模板串的长度***************/
/*
	 总结：
	1. 设置两张表，一张表示字符出现次数，另一张表示字符是否出现；
	2. 首先初始化这两张表；
	3. 设置两个指针，均指向待查字符串，从头开始，并设置一个最小长度和最小长度的起始下标，作为记录更新
	4. 遍历查找S，如果表中出现的字符个数还有，则进行类似于出队列操作，否则就做类似进队列操作，更新两张表
	5. 只有当当前字符在这两张表中均表示存在，则将次数做减操作；同理，已经不存在的情况下，如果重新来到，则做加操作
*/
string minWindow(string s, string t) {
	if (s.empty() || t.empty())
		return "";
	int require[128] = { 0 };		// 表示模式串字符出现的次数，默认为0，出现一次加一次---1
	bool appearCh[128] = { false }; // 表示模式串中的字符是否出现， 默认为false，出现则为true---1
	int count = t.size(); // 模板串字符个数

	for (int i = 0; i < count; ++i) {	// 2
		require[t[i]]++;
		appearCh[t[i]] = true;
	}

	int left = 0, right = -1; // left、right 从0开始变量s主串，left一般直接指向匹配字符窗口的最左边那个字符，right一直遍历
	int minLen = INT_MAX, minIdx = 0; // minLen 表示匹配窗口大小，minIdx表示left值，但只表示最小情况下的left值

	while (right < (int)s.size() && left < (int)s.size()) {
		if (count) {	/// 类似于出栈
			++right;
			require[s[right]]--;	// 如果该字符不是需要的字符，则减过之后变为-1，
			if (appearCh[s[right]] && (require[s[right]] >= 0)) {//此条件判断后表明该字符是所求字符； 匹配
				count--;	//出栈
			}
		}
		else {			/// 类似于进栈
			if (minLen > right - left + 1) {
				minLen = right - left + 1;
				minIdx = left;
			}
			require[s[left]]++;		// 类似出队列操作，根据上面的情况，如果当前字符不是所求字符，则require值重新回到0，
			if (appearCh[s[left]] && require[s[left]] > 0) {// 只有当该字符是所求字符，才进行++count操作 匹配
				++count;	// 进栈
			}
			++left;
		}//else
	}//while
	return (minLen == INT_MAX) ? "" : (s.substr(minIdx, minLen));// string substr(pos, pos+len) const;
	
}


int main() {
	//string s = "";
	//cout << lengthOfLongestSubstring(s) << endl;
	string text = "aabaaabaaac", pattern = "aabaaac";
	//cout << strStr(text, pattern) << endl;
	string s = "a", t = "a";
	cout << minWindow(s, t) << endl;
	return 0;
}