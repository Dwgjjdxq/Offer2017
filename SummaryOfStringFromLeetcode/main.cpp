/*
Summary of String from Leetcode
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**********************利用哈希表或者双指针类型*******************************/
/************3. Longest Substring Without Repeating Characters最长无重复字符的子串(不熟练)****************/
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

/**************************5. Longest Palindromic Substring 最长回文子串***************/
/*暴力法(O(N*3))*/
string longestPalindrome(string s) {
	int length = s.size();
	int maxLength = 0;
	int start = 0;
	for (int i = 0; i < s.size(); ++i) {
		for (int j = i + 1; j < s.size(); ++j) {
			int temp1, temp2;
			for (temp1 = i, temp2 = j; temp1 < temp2; temp1++, temp2) {
				if (s[temp1] != s[temp2])
					break;
			}//for
			if (temp1 >= temp2 && j - i > maxLength) {
				maxLength = j - i + 1;
				start = i;
			}//if
		}//for
	}//for
	return maxLength > 0 ? s.substr(start, maxLength) : NULL;
}

/*动态规划法(递推思想)*/
/*
	总结：
	1. 首先创建二维数组dp，初始化为0
	2. 边界条件：dp[i][i] = 1, dp[i][i+1] = (s[i] == s[i+1]) ? 1 : 0
	3. 状态转移方程：最长回文子串长度从3开始，dp[i][j] = dp[i+1][j-1] (== 1); 当s[i] == s[j]时
*/
string longestPalindromeDP(string s) {
	if (s.empty()) return "";
	if (s.size() == 1) return s;
	int maxLength = 1;
	int len = s.size();
	int dp[1024][1024] = { 0 }; // 1
	int start = 0;
	/*边界*/
	for (int i = 0; i < len; ++i) {
		dp[i][i] = 1;    // 2 单个元素对应的dp为1
		if (i < len - 1 && s[i] == s[i + 1]) { //2 相邻两个元素相同时，dp[i][i+1] = 1
			dp[i][i + 1] = 1;
			start = i;
			maxLength = 2;
		}//if
	}//for
	/*状态转移方程*/
	for (int L = 3; L <= len; ++L) {	// 子串长度
		for (int left = 0; left + L - 1 < len; ++left) { // 子串起始地址
			int right = left + L - 1;					 // 子串结束地址   然后向中间靠拢
			if (s[left] == s[right] && (dp[left + 1][right - 1] == 1)) { // 3.只要前后相等，并且上一层dp也相等，则回文构成
				dp[left][right] = 1;	// 3
				maxLength = L;
				start = left;
			}//if
		}//for
	}//for
	return (maxLength >= 1) ? s.substr(start, maxLength) : "";
}

/*lamacher算法（拉马车算法O(N)）*/
/*
	总结
	1. 首先预处理将原字符串处理为 在字符串首尾及字符间各插入一个字符'#'，为避免越界，在开始处插入一个其他字符'$',尾部是以'\0'结尾
	2. 
*/
#if 0
const int maxn = 3e5; // 字符串最大空间 1e5 = 100000, 3e5 = 300000
char str[maxn], newStr[maxn];// s 存放原始字符串， str 存放变化后的数据
int len1, len2, p[maxn], ans; // len1表示原始字符串长度，len2表示变换后的字符串长度，
							  // p[maxn] 表示当前字符的最长回文串长度,ans 表示最长回文串结果
/*预处理*/ 
void init() {
	newStr[0] = '$';
	newStr[1] = '#';
	for (int i = 0; i < len1; ++i) {
		newStr[2 * i + 2] = str[i];
		newStr[2 * i + 3] = '#';
	}
	len2 = len1 * 2 + 2;
	newStr[len2] = '\0';
}
void manacher(){
	int id = 0, mx = 0;	// id表示回文串中心，mx表示以id为中心的最长回文串的右边界
	for (int i = 1; i < len2; ++i) {
		/*核心代码，求出p[i]*/
		if (i < mx) 
			p[i] = min(p[2 * id - i], mx - i);
		else p[i] = 1;

		/*当i位置的回文串大小超过了mx，则后面暴力计算求回文串长度*/
		for (; newStr[i + p[i]] == newStr[i - p[i]]; p[i]++);

		// 更新id,mx值
		if (p[i] + i > mx) {
			mx = p[i] + i;
			id = i;
		}//if

		ans = max(ans, p[i] - 1);	// 因为字符串翻倍，所以 p[i]-1 即为原始字符串当前位置回文串长度
	}//for
}
// 求最长回文串长度
int main_lamacher() {
	while (scanf("%s", str) != EOF) {
		len1 = strlen(str);
		init();
		manacher();
		cout << ans << endl;
	}
	return 0;
}
#endif

/*求最长回文串字符串*/
string longestPalindromeLamacher(string s) {
	/*预处理*/
	string newS = "$#";
	for (int i = 0; i < s.size(); ++i) {
		newS += s[i]; newS += '#';
	}
	
	int p[300000] = { 0 }, id = 0, mx = 0, resId = 0, resMx = 0;
	for (int i = 0; i < newS.size(); ++i) {
		/*核心代码 p[i] 表示变形后字符串中以i为中心的回文串的半径*/
		p[i] = (i < mx) ? min(p[2 * id - i], mx - i) : 1; 
		/*暴力匹配i超过mx后面的*/
		while (newS[i + p[i]] == newS[i - p[i]]) ++p[i];
		/*更新当前回文串的 半径mx 和 中心点id */
		if (mx < (i + p[i])) {
			mx = i + p[i];
			id = i;
		}
		/*更新最长回文串的 半径resMx 和 中心点resId*/
		if (resMx < p[i]) {
			resMx = p[i];	
			resId = i;
		}
	}
	return s.substr((resId - resMx) / 2, resMx - 1);
}

/**************************14. 最长公共前缀***************/
/*
	总结：如果发现第一个字符串strs[0]的某个字符strs[0][j](j从0号开始查看)与后面所有的字符串对应字符不相等时，
		 就说明不会有更长的共同前缀.
*/
string longestCommonPrefix(vector<string>& strs) {
	if (strs.empty()) return "";
	const int lensOfStrs = strs.size();
	
	for (int j = 0; j < strs[0].size(); ++j) {
		for (int i = 1; i < lensOfStrs; ++i) {
			if (strs[0][j] != strs[i][j])
				return strs[0].substr(0, j);
		}//for
	}//for
	return strs[0];
}

/**************************65. 有效数字***************/
class Solution {
public:
	bool isNumber(string s) {
		/*index标记位*/
		int i = 0;
		/*去除前缀空格*/
		for (; s[i] == ' '; ++i);
		/*跳过标记号'+'或'-'*/
		if (s[i] == '+' || s[i] == '-') ++i;

		/*有效数字中包含最多一个小数点. 至少一个整数, 否则就是无效的*/
		int pointNum = 0, digitNum = 0;
		for (; s[i] >= '0' && s[i] <= '9' || s[i] == '.'; ++i) /*注意勿忘：|| s[i] == '.'*/
		{
			s[i] == '.' ? pointNum++ : digitNum++;
		}
		if (pointNum > 1 || digitNum < 1) return false;

		/*遇到e||E，后面可以紧跟一个'+'或'-'，然后再次开始计算digit的个数，必须大于一个*/
		if (s[i] == 'e' || s[i] == 'E') {
			++i;
			if (s[i] == '+' || s[i] == '-') ++i;

			int digitNum2 = 0;
			for (; s[i] >= '0' && s[i] <= '9'; ++i, digitNum2++); /*注意勿忘：digitNum2++*/
			if (digitNum2 < 1)
				return false;
		}
		/*去掉后缀空格*/
		for (; s[i] == ' '; ++i);
		return i == s.size();
	}
};



int main() {
	//string s = "";
	//cout << lengthOfLongestSubstring(s) << endl;
	//string text = "aabaaabaaac", pattern = "aabaaac";
	//cout << strStr(text, pattern) << endl;
	//string s = "a", t = "a";
	//cout << minWindow(s, t) << endl;
	//string s = "abcdasdfghjkldcba";
	//cout << longestPalindrome(s) << endl;
	//string s = "abbcaacdadada";
	///cout << longestPalindromeLamacher(s) << endl;
	string s = ".1";
	Solution sln;
	cout << sln.isNumber(s) << endl;
	return 0;
}