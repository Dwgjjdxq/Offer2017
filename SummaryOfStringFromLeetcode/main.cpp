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
	Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

	For example,
	S = "ADOBECODEBANC"
	T = "ABC"
	Minimum window is "BANC".
*/
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

*/
#if 1
/*最长回文串子串的长度*/
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
	/*newS += '*'; 设置边界，首位不同即可,可省略*/
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
	return s.substr((resId - resMx) / 2, resMx - 1); /*因为之前间隔插入'#' '$' 全部更新为偶数个*/
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
/*
	总结：
		1. 首先跳过前缀空格；
		2. 检查有效位数；先跳过开头的标记位'+'或'-',然后计算小数点字符个数和整数个数, 小数点个数不能超过一个，整数个数至少一个；
		3. 检查指数部分的有效性；符号位出现'e'或者'E',跳过该符号位，计算整数部分，整数个数至少有一个;
		4. 跳过后缀空格，此时必须最终达到字符串尾部，即索引号为字符串长度(因为索引号从0开始的)（或者C中字符串遇到'\0'）
*/
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
		/*状态返回*/
		return i == s.size();
	}
};

/**************************20. Valid Parentheses(括号匹配问题)***************/
#include <stack>
bool isLeft(char c) {
	return (c == '(' || c == '[' || c == '{') ? true : false;
}
bool isRight(char c) {
	return (c == ')' || c == ']' || c == '}') ? true : false;
}
bool isPair(char c1, char c2) {
	return ((c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}')) ? true : false;
}
bool isValid(string s){
	if (s.empty()) return true;
	if ((s.size() >> 1) != 0) return false; /*不是偶数个字符，直接说明不匹配*/
	stack<char> sta;
	for (int i = 0; i < s.size(); ++i) {
		if (isLeft(s[i])) sta.push(s[i]);	/*该字符是左括号，入栈*/
		else if (isRight(s[i])){			/*该字符是右括号，准备判定是否出栈*/
			if (!sta.empty() && isPair(sta.top(), s[i])) {	/*注意 !sta.empty() 的判断,只有此时栈中有字符，才做后面匹配操作*/
				sta.pop();
			}
			else return false;
		}//else
		else return false;
	}
	return sta.empty();		/*注意返回sta.empty(); 只有此时栈全部出栈，才能说明全部匹配*/
}

/*更简洁版*/ 
bool isValid_web(string s) {
	stack<char> sta;
	for (int i = 0; i < s.size(); ++i) {
		if ((s[i] == ')') && (sta.empty() || sta.top() != '(')
			|| (s[i] == ']') && (sta.empty() || sta.top() != '[')
			|| (s[i] == '}') && (sta.empty() || sta.top() != '{'))
			return false;
		else if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			sta.push(s[i]);
		else sta.pop();
	}
	return sta.empty();
}

/**********************38. count and say  初始是1， 后面一次读字符个数和字符，共读n层***********/
/*
The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
*/
string countAndSay(int n) {
	if (n <= 0)
		return "";
	string res = "1";
	while (--n) {
		string cur = "";

		for (int i = 0; i < res.size(); ++i) {
			int cnt = 1;		/*注意：cnt放在for循环中 找后面是否有相同 的字符*/
			while (i + 1 < res.size() && res[i] == res[i + 1]) {
				++cnt; ++i;
			}
			cur += to_string(cnt) + res[i]; /*注意是将字符个数+字符赋给临时字符串*/
		}

		res = cur; /*更新每一层的结果*/
	}
	return res;
}

/**********************58. 字符串中最后一个单词的长度***********/
int lengthOfLastWord(string s) {
	if (s.empty()) return 0;
	int cnt = 0;
	int index = s.size() - 1;
	for (; s[index] == ' '; --index);	/*删除串尾的空格*/
	for (; index >= 0 && s[index] != ' '; --index)	/*注意勿忘： index >= 0  否则 将会出现负值，负值就会出现ffffffff有32位*/
		++cnt;
	return cnt;
}

/**********************67.大数求和(二进制)(非常不熟悉)*****************/
/*总结参见下一题 大数乘法*/
string addBinary(string a, string b) {
	if (a.empty()) return b;
	if (b.empty()) return a;

	int i = a.size() - 1, j = b.size() - 1;

	int carry = 0; /*进位*/
	string res = ""; /*余数*/

	while (i >= 0 && j >= 0) {
		/*
		核心句原型： 保留位 += (上一层的进位 + 当前两位之和) % 2;
					进位   =  (上一层的进位 + 当前两位之和) / 2;
		res += (carry + (a[i] - '0') + (b[j] - '0')) % 2 + '0';
		carry = (carry + (a[i] - '0') + (b[j] - '0')) << 1;
		*/
		
		carry += (a[i] - '0') + (b[j] - '0');	/*表示：上一层的进位 + 当前两位之和*/
		res += ((carry % 2) + '0');				/*保留位*/
		carry /= 2;								/*进位*/
		--i; --j;								/*移位*/
	}

	/*a还有余位*/
	while (i >= 0) {
		carry += (a[i] - '0');
		res += (carry % 2) + '0';
		carry /= 2;
		--i;
	}
	/*b还有余位*/
	while (j >= 0) {
		carry += (b[j] - '0');
		res += (carry % 2) + '0';
		carry /= 2;
		--j;
	}
	/*进位有余位*/
	if (carry) res += '1';
	/*注意需要翻转，因为之前res起始是后面，又是向后++*/
	reverse(res.begin(), res.end());
	return res;

}

/**********************43.大数的乘积*****************/
/*
	总结： 
		1. 核心思想：每一次相乘要先得出当前位产生的总和，再求余位，随后更新进位，作为下一层计算总和的一部分
		2. 首先判空与判零；
		3. 申请空间(大小为两个字符串大小之和，以便足够大)
		4. 翻转两个字符串，方便对其计算
		5. 指向第二个字符串的j作为整体向右移动的控制变量，指向第一个字符串的i作为每一层从0到串尾参与运算的位置
		6. 参与当前位计算总和包括有"当前位原有数据"+"当前位相乘数据"+"上一步求得的进位数据"
		7. 然后更新余位和进位
		8. 将多余的进位全部更新入坑
		9. 最后记得移除掉多申请的空间
		10. 最终翻转字符串，得到最终结果
*/
string multiply(string num1, string num2) {
	if (num1.empty() || num2.empty() || num1 == "0" || num2 == "0")
		return "0";
	int len1 = num1.size(), len2 = num2.size();
	string res(len1 + len2, '0');
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());

	int carry = 0;	/*进位*/
	int j = 0; // j:num2 用j来控制该层结果整体向右移动
	while (j < len2) {
		int i = 0;		/*每一层的i都是从0开始*/
		while (i < len1) {
			carry += res[i + j] - '0' + (num1[i] - '0') * (num2[j] - '0'); /*先计算出当前位参与运算的总和*/
			res[i + j] = (carry) % 10 + '0'; /*余位*/  /*用carry % 10来取余数*/
			carry /= 10; /*更新进位*/
			++i;
		}//每一层乘积的结果
		while (carry) {
			res[i + j] = carry % 10 + '0'; /*余位*/	/*用carry % 10来取余数*/
			carry /= 10; ++i;			   /*进位*/
		}
		++j;	// 到下一层，指向num2的光标向右移动一位
	}
	
	string::iterator iter = res.end() - 1;	/*删除尾部申请的多余的'0'*/
	while (*iter == '0') {
		res.erase(iter--);
	}
	/*
	for (int i = res.size() - 1; i >= 0; --i) {
		if (res[i] != '0')
			break;
		else res.pop_back();
	}*/
	reverse(res.begin(), res.end());
	return res;
	
}

/**********************22. 给一个整数n，求n对小括号的所有组合情况(回朔法backtracking)*****************/
/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:
[
"((()))","(()())","(())()","()(())","()()()"
]
	总结：
		1. 定义left和right分别记录'(' 和')'剩余出现的次数；
		2. 初步假设'('还可以出现n次，而')'还可出现0次；
		3. 回溯计算，当左右括号出现的次数为均为0次时，说明已经结束，将目前存的括号放进去；
		4. 当'('还可以出现时，即left>0,则将左括号入栈，即left -1, 但此时根据对应原则，此时记录')'的right+1,表示对应需要的次数
		4. 当')'还需要出现时，即right>0,则将右括号入栈，即right - 1
*/

void backtracking(vector<string> & res, string tmp, int left, int right) {
	if (left == 0 && right == 0) {
		res.push_back(tmp);
		return;
	}
	if (left > 0) backtracking(res, tmp + '(', left - 1, right + 1);/*入一个'(',即left -1 ,相应的再增加一个记录right+1*/
	if (right > 0) backtracking(res, tmp + ')', left, right - 1);
}
vector<string> generateParenthesis(int n) {
	if (n < 0) return vector<string>();
	vector<string> res;
	string tmp = "";
	backtracking(res, tmp, n, 0);	/*注意此时')'暂时不需要，动态地看'('入栈情况，入一个'(',相应的再增加一个记录right*/
}

/********************************151. 翻转字符串*******************************/
/*
	总结：
		1. 利用栈的先进后出策略，将字符串依次入栈，但要skip首尾出现的空格及单词之间空格，以便入栈操作
		2. 首先记得skip掉字符串头尾及单词与单词之间的空格，只为单词而生
		3. 清理过后，就开始存单词
		4. 果真存了单词，就入栈，然后清理临时单词字符串words，继续遍历
		5. 清理清理原来输入的字符串，准备翻转后的字符串；如果栈中存有单词，准备做出栈操作;
		6. 出栈的过程中记得每次出栈之后要加上一个' '.来分割单词
		7. 最后，将最后出栈后出现的多余的分隔符' ' 去除掉，用substr(0, s.size() - 1)。
*/
/*方法一：栈处理*/
void reverseWords(string & s) {
	if (s.empty()) return; /*当字符串只有一个字符时，要注意可能是空格，则不能直接返回，需要排除只有一个空格的字符串*/
	/* if (s.size() == 1 && s[0] != ' ') return; */	// 可省略
	string::iterator iter = s.begin();
	stack<string> strStack;		/*申请栈*/
	string words;				/*保存一个单词,准备入栈*/

	while (iter != s.end()) {
		while (*iter == ' ') ++iter;				/*skip各种空格，在循环的过程中，刚开始skip串头的空格，运行过程中再skip多余的空											格，同时在最后也会skip串尾空格*/
		while (iter != s.end() && *iter != ' ') {	/*记录一个单词*/
			words += *iter++;						/*此处的iter++，即出现了向后移动的操作*/
		}
		if (!words.empty())							/*存了一个单词，那就入栈*/
			strStack.push(words);
		words.clear();								/*单词入栈之后就及时清理临时字符串*/
	}//while 遍历整个字符串

	s.clear();										/*清空下原来的整个字符串，准备迎接栈内单词*/
	while (!strStack.empty()) {				
		s += strStack.top() + ' ';					/*开始迎接栈内单词，并以空格来隔开*/
		strStack.pop();								/*remember 出栈操作*/
	}
	s = s.substr(0, s.size() - 1); /*此处要注意！不能省略，因为在上面s += strStack.top() + ' ' 时，将会多加一个空格 ' ' */
}
/*方法二：输入流stringstream来处理*/
#include <sstream>
void reverseWords_1(string &s) {
	stringstream is(s);
	string tmp;
	string res;
	while (is >> tmp) {
		if (res.empty()) {
			res = tmp;
		}
		else res = tmp + ' ' + res;			/*按照这个顺序，即 (新(刚出炉) + ' ' + 老(之前已经出来了)) 可达到出栈的效果，*/
	}
	s = res;
}




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
	//string s = ".1";
	//Solution sln;
	//cout << sln.isNumber(s) << endl;
	//string s = "((";
	//cout << isValid(s) << endl;
	//cout << countAndSay(6) << endl;
	//string s = "hello world ";
	//cout << lengthOfLastWord(s) << endl;
	//string num1 = "1", num2 = "1";
	//cout << multiply(num1, num2) << endl;
	string s = " ";
	reverseWords(s);
	//cout << s << "12" << endl;
	return 0;
}