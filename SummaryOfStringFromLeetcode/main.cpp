/*
Summary of String from Leetcode
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**********************���ù�ϣ�����˫ָ������*******************************/
/************3. Longest Substring Without Repeating Characters����ظ��ַ����Ӵ�(������)****************/
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

/*********************************��ϣ����**************************/
/**********************************49. Group Anagrams�ߵ����ַ�������***************/
/*
���ߵ�����ַ����ֱ��Ϊһ��
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:
[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/
/*	// Ĭ���ַ����ַ���ΪСд��ĸ
	�ܽ᣺
	1. ��һ����ɢ���ַ��������н�������ͬ������ͬ�ַ����ַ�����Ϊһ�飬�������ù�ϣ˼�빹��һ��map
	2. ��map��keyֵӦΪ�ź���֮����ַ���str, ��ӦvalueӦ��vector<string>,��һ��������
	3. 
*/
#include <map>
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	if (strs.empty())
		return vector<vector<string>>();
	vector<vector<string>> res;

	//sort(strs.begin(), strs.end());
	/*���ù�ϣ˼�빹��һ��mapӳ���ϵ�� string��ʾ��ʾ��ǰ�ַ����ź������ʱ�ַ����� vector<string>��ʾ��ŵ�ǰԭʼ�ַ���*/
	map<string, vector<string>> mp;

	for (int i = 0; i < strs.size(); ++i) {
		string str = strs[i];
		/*����ʱ�ַ���������Ϊmap��keyֵ�� ��ԭʼ�ַ�����Ϊ��Ӧvalueֵ*/
		sort(str.begin(), str.end());
		mp[str].push_back(strs[i]);
	}
	/*��map��ͬkey��Ӧ��value���飬�����ڴ�������*/
	for (auto a : mp) {
		res.push_back(a.second);
	}
	/* ��һ��ָ��д��
	for (map<string, vector<string>>::iterator iter = mp.begin(); iter != mp.end(); ++iter)
		res.push_back(iter->second);
	*/
	return res;	
}

/**************************76. Minimum Window Substring��С����ģ�崮�ĳ���***************/
/*
	Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

	For example,
	S = "ADOBECODEBANC"
	T = "ABC"
	Minimum window is "BANC".
*/
/*
	 �ܽ᣺
	1. �������ű�һ�ű�ʾ�ַ����ִ�������һ�ű�ʾ�ַ��Ƿ���֣�
	2. ���ȳ�ʼ�������ű�
	3. ��������ָ�룬��ָ������ַ�������ͷ��ʼ��������һ����С���Ⱥ���С���ȵ���ʼ�±꣬��Ϊ��¼����
	4. ��������S��������г��ֵ��ַ��������У�����������ڳ����в���������������ƽ����в������������ű�
	5. ֻ�е���ǰ�ַ��������ű��о���ʾ���ڣ��򽫴�������������ͬ���Ѿ������ڵ�����£�������������������Ӳ���
*/
string minWindow(string s, string t) {
	if (s.empty() || t.empty())
		return "";
	int require[128] = { 0 };		// ��ʾģʽ���ַ����ֵĴ�����Ĭ��Ϊ0������һ�μ�һ��---1
	bool appearCh[128] = { false }; // ��ʾģʽ���е��ַ��Ƿ���֣� Ĭ��Ϊfalse��������Ϊtrue---1
	int count = t.size(); // ģ�崮�ַ�����

	for (int i = 0; i < count; ++i) {	// 2
		require[t[i]]++;
		appearCh[t[i]] = true;
	}

	int left = 0, right = -1; // left��right ��0��ʼ����s������leftһ��ֱ��ָ��ƥ���ַ����ڵ�������Ǹ��ַ���rightһֱ����
	int minLen = INT_MAX, minIdx = 0; // minLen ��ʾƥ�䴰�ڴ�С��minIdx��ʾleftֵ����ֻ��ʾ��С����µ�leftֵ

	while (right < (int)s.size() && left < (int)s.size()) {
		if (count) {	/// �����ڳ�ջ
			++right;
			require[s[right]]--;	// ������ַ�������Ҫ���ַ��������֮���Ϊ-1��
			if (appearCh[s[right]] && (require[s[right]] >= 0)) {//�������жϺ�������ַ��������ַ��� ƥ��
				count--;	//��ջ
			}
		}
		else {			/// �����ڽ�ջ
			if (minLen > right - left + 1) {
				minLen = right - left + 1;
				minIdx = left;
			}
			require[s[left]]++;		// ���Ƴ����в������������������������ǰ�ַ����������ַ�����requireֵ���»ص�0��
			if (appearCh[s[left]] && require[s[left]] > 0) {// ֻ�е����ַ��������ַ����Ž���++count���� ƥ��
				++count;	// ��ջ
			}
			++left;
		}//else
	}//while
	return (minLen == INT_MAX) ? "" : (s.substr(minIdx, minLen));// string substr(pos, pos+len) const;
	
}

/**************************5. Longest Palindromic Substring ������Ӵ�***************/
/*������(O(N*3))*/
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

/*��̬�滮��(����˼��)*/
/*
	�ܽ᣺
	1. ���ȴ�����ά����dp����ʼ��Ϊ0
	2. �߽�������dp[i][i] = 1, dp[i][i+1] = (s[i] == s[i+1]) ? 1 : 0
	3. ״̬ת�Ʒ��̣�������Ӵ����ȴ�3��ʼ��dp[i][j] = dp[i+1][j-1] (== 1); ��s[i] == s[j]ʱ
*/
string longestPalindromeDP(string s) {
	if (s.empty()) return "";
	if (s.size() == 1) return s;
	int maxLength = 1;
	int len = s.size();
	int dp[1024][1024] = { 0 }; // 1
	int start = 0;
	/*�߽�*/
	for (int i = 0; i < len; ++i) {
		dp[i][i] = 1;    // 2 ����Ԫ�ض�Ӧ��dpΪ1
		if (i < len - 1 && s[i] == s[i + 1]) { //2 ��������Ԫ����ͬʱ��dp[i][i+1] = 1
			dp[i][i + 1] = 1;
			start = i;
			maxLength = 2;
		}//if
	}//for
	/*״̬ת�Ʒ���*/
	for (int L = 3; L <= len; ++L) {	// �Ӵ�����
		for (int left = 0; left + L - 1 < len; ++left) { // �Ӵ���ʼ��ַ
			int right = left + L - 1;					 // �Ӵ�������ַ   Ȼ�����м俿£
			if (s[left] == s[right] && (dp[left + 1][right - 1] == 1)) { // 3.ֻҪǰ����ȣ�������һ��dpҲ��ȣ�����Ĺ���
				dp[left][right] = 1;	// 3
				maxLength = L;
				start = left;
			}//if
		}//for
	}//for
	return (maxLength >= 1) ? s.substr(start, maxLength) : "";
}

/*lamacher�㷨�������㷨O(N)��*/
/*
	�ܽ�
	1. ����Ԥ����ԭ�ַ�������Ϊ ���ַ�����β���ַ��������һ���ַ�'#'��Ϊ����Խ�磬�ڿ�ʼ������һ�������ַ�'$',β������'\0'��β

*/
#if 1
/*����Ĵ��Ӵ��ĳ���*/
const int maxn = 3e5; // �ַ������ռ� 1e5 = 100000, 3e5 = 300000
char str[maxn], newStr[maxn];// s ���ԭʼ�ַ����� str ��ű仯�������
int len1, len2, p[maxn], ans; // len1��ʾԭʼ�ַ������ȣ�len2��ʾ�任����ַ������ȣ�
							  // p[maxn] ��ʾ��ǰ�ַ�������Ĵ�����,ans ��ʾ����Ĵ����
/*Ԥ����*/ 
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
	int id = 0, mx = 0;	// id��ʾ���Ĵ����ģ�mx��ʾ��idΪ���ĵ�����Ĵ����ұ߽�
	for (int i = 1; i < len2; ++i) {
		/*���Ĵ��룬���p[i]*/
		if (i < mx) 
			p[i] = min(p[2 * id - i], mx - i);
		else p[i] = 1;

		/*��iλ�õĻ��Ĵ���С������mx������汩����������Ĵ�����*/
		for (; newStr[i + p[i]] == newStr[i - p[i]]; p[i]++);

		// ����id,mxֵ
		if (p[i] + i > mx) {
			mx = p[i] + i;
			id = i;
		}//if

		ans = max(ans, p[i] - 1);	// ��Ϊ�ַ������������� p[i]-1 ��Ϊԭʼ�ַ�����ǰλ�û��Ĵ�����
	}//for
}
// ������Ĵ�����
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

/*������Ĵ��ַ���*/
string longestPalindromeLamacher(string s) {
	/*Ԥ����*/
	string newS = "$#";
	for (int i = 0; i < s.size(); ++i) {
		newS += s[i]; newS += '#';
	}
	/*newS += '*'; ���ñ߽磬��λ��ͬ����,��ʡ��*/
	int p[300000] = { 0 }, id = 0, mx = 0, resId = 0, resMx = 0;
	for (int i = 0; i < newS.size(); ++i) {

		/*���Ĵ��� p[i] ��ʾ���κ��ַ�������iΪ���ĵĻ��Ĵ��İ뾶*/
		p[i] = (i < mx) ? min(p[2 * id - i], mx - i) : 1; 

		/*����ƥ��i����mx�����*/
		while (newS[i + p[i]] == newS[i - p[i]]) ++p[i];

		/*���µ�ǰ���Ĵ��� �뾶mx �� ���ĵ�id */
		if (mx < (i + p[i])) {
			mx = i + p[i];
			id = i;
		}

		/*��������Ĵ��� �뾶resMx �� ���ĵ�resId*/
		if (resMx < p[i]) {
			resMx = p[i];	
			resId = i;
		}
	}
	return s.substr((resId - resMx) / 2, resMx - 1); /*��Ϊ֮ǰ�������'#' '$' ȫ������Ϊż����*/
}

/**************************14. �����ǰ׺***************/
/*
	�ܽ᣺������ֵ�һ���ַ���strs[0]��ĳ���ַ�strs[0][j](j��0�ſ�ʼ�鿴)��������е��ַ�����Ӧ�ַ������ʱ��
		 ��˵�������и����Ĺ�ͬǰ׺.
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

/**************************65. ��Ч����***************/
/*
	�ܽ᣺
		1. ��������ǰ׺�ո�
		2. �����Чλ������������ͷ�ı��λ'+'��'-',Ȼ�����С�����ַ���������������, С����������ܳ���һ����������������һ����
		3. ���ָ�����ֵ���Ч�ԣ�����λ����'e'����'E',�����÷���λ�������������֣���������������һ��;
		4. ������׺�ո񣬴�ʱ�������մﵽ�ַ���β������������Ϊ�ַ�������(��Ϊ�����Ŵ�0��ʼ��)������C���ַ�������'\0'��
*/
class Solution {
public:
	bool isNumber(string s) {
		/*index���λ*/
		int i = 0;
		/*ȥ��ǰ׺�ո�*/
		for (; s[i] == ' '; ++i);
		/*������Ǻ�'+'��'-'*/
		if (s[i] == '+' || s[i] == '-') ++i;

		/*��Ч�����а������һ��С����. ����һ������, ���������Ч��*/
		int pointNum = 0, digitNum = 0;
		for (; s[i] >= '0' && s[i] <= '9' || s[i] == '.'; ++i) /*ע��������|| s[i] == '.'*/
		{
			s[i] == '.' ? pointNum++ : digitNum++;
		}
		if (pointNum > 1 || digitNum < 1) return false;

		/*����e||E��������Խ���һ��'+'��'-'��Ȼ���ٴο�ʼ����digit�ĸ������������һ��*/
		if (s[i] == 'e' || s[i] == 'E') {
			++i;
			if (s[i] == '+' || s[i] == '-') ++i;

			int digitNum2 = 0;
			for (; s[i] >= '0' && s[i] <= '9'; ++i, digitNum2++); /*ע��������digitNum2++*/
			if (digitNum2 < 1)
				return false;
		}
		/*ȥ����׺�ո�*/
		for (; s[i] == ' '; ++i);
		/*״̬����*/
		return i == s.size();
	}
};

/**************************20. Valid Parentheses(����ƥ������)***************/
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
	if ((s.size() >> 1) != 0) return false; /*����ż�����ַ���ֱ��˵����ƥ��*/
	stack<char> sta;
	for (int i = 0; i < s.size(); ++i) {
		if (isLeft(s[i])) sta.push(s[i]);	/*���ַ��������ţ���ջ*/
		else if (isRight(s[i])){			/*���ַ��������ţ�׼���ж��Ƿ��ջ*/
			if (!sta.empty() && isPair(sta.top(), s[i])) {	/*ע�� !sta.empty() ���ж�,ֻ�д�ʱջ�����ַ�����������ƥ�����*/
				sta.pop();
			}
			else return false;
		}//else
		else return false;
	}
	return sta.empty();		/*ע�ⷵ��sta.empty(); ֻ�д�ʱջȫ����ջ������˵��ȫ��ƥ��*/
}

/*������*/ 
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

/**********************38. count and say  ��ʼ��1�� ����һ�ζ��ַ��������ַ�������n��***********/
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
			int cnt = 1;		/*ע�⣺cnt����forѭ���� �Һ����Ƿ�����ͬ ���ַ�*/
			while (i + 1 < res.size() && res[i] == res[i + 1]) {
				++cnt; ++i;
			}
			cur += to_string(cnt) + res[i]; /*ע���ǽ��ַ�����+�ַ�������ʱ�ַ���*/
		}

		res = cur; /*����ÿһ��Ľ��*/
	}
	return res;
}

/**********************58. �ַ��������һ�����ʵĳ���***********/
int lengthOfLastWord(string s) {
	if (s.empty()) return 0;
	int cnt = 0;
	int index = s.size() - 1;
	for (; s[index] == ' '; --index);	/*ɾ����β�Ŀո�*/
	for (; index >= 0 && s[index] != ' '; --index)	/*ע�������� index >= 0  ���� ������ָ�ֵ����ֵ�ͻ����ffffffff��32λ*/
		++cnt;
	return cnt;
}

/**********************67.�������(������)(�ǳ�����Ϥ)*****************/
/*�ܽ�μ���һ�� �����˷�*/
string addBinary(string a, string b) {
	if (a.empty()) return b;
	if (b.empty()) return a;

	int i = a.size() - 1, j = b.size() - 1;

	int carry = 0; /*��λ*/
	string res = ""; /*����*/

	while (i >= 0 && j >= 0) {
		/*
		���ľ�ԭ�ͣ� ����λ += (��һ��Ľ�λ + ��ǰ��λ֮��) % 2;
					��λ   =  (��һ��Ľ�λ + ��ǰ��λ֮��) / 2;
		res += (carry + (a[i] - '0') + (b[j] - '0')) % 2 + '0';
		carry = (carry + (a[i] - '0') + (b[j] - '0')) << 1;
		*/
		
		carry += (a[i] - '0') + (b[j] - '0');	/*��ʾ����һ��Ľ�λ + ��ǰ��λ֮��*/
		res += ((carry % 2) + '0');				/*����λ*/
		carry /= 2;								/*��λ*/
		--i; --j;								/*��λ*/
	}

	/*a������λ*/
	while (i >= 0) {
		carry += (a[i] - '0');
		res += (carry % 2) + '0';
		carry /= 2;
		--i;
	}
	/*b������λ*/
	while (j >= 0) {
		carry += (b[j] - '0');
		res += (carry % 2) + '0';
		carry /= 2;
		--j;
	}
	/*��λ����λ*/
	if (carry) res += '1';
	/*ע����Ҫ��ת����Ϊ֮ǰres��ʼ�Ǻ��棬�������++*/
	reverse(res.begin(), res.end());
	return res;

}

/**********************43.�����ĳ˻�*****************/
/*
	�ܽ᣺ 
		1. ����˼�룺ÿһ�����Ҫ�ȵó���ǰλ�������ܺͣ�������λ�������½�λ����Ϊ��һ������ܺ͵�һ����
		2. �����п������㣻
		3. ����ռ�(��СΪ�����ַ�����С֮�ͣ��Ա��㹻��)
		4. ��ת�����ַ���������������
		5. ָ��ڶ����ַ�����j��Ϊ���������ƶ��Ŀ��Ʊ�����ָ���һ���ַ�����i��Ϊÿһ���0����β���������λ��
		6. ���뵱ǰλ�����ܺͰ�����"��ǰλԭ������"+"��ǰλ�������"+"��һ����õĽ�λ����"
		7. Ȼ�������λ�ͽ�λ
		8. ������Ľ�λȫ���������
		9. ���ǵ��Ƴ���������Ŀռ�
		10. ���շ�ת�ַ������õ����ս��
*/
string multiply(string num1, string num2) {
	if (num1.empty() || num2.empty() || num1 == "0" || num2 == "0")
		return "0";
	int len1 = num1.size(), len2 = num2.size();
	string res(len1 + len2, '0');
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());

	int carry = 0;	/*��λ*/
	int j = 0; // j:num2 ��j�����Ƹò������������ƶ�
	while (j < len2) {
		int i = 0;		/*ÿһ���i���Ǵ�0��ʼ*/
		while (i < len1) {
			carry += res[i + j] - '0' + (num1[i] - '0') * (num2[j] - '0'); /*�ȼ������ǰλ����������ܺ�*/
			res[i + j] = (carry) % 10 + '0'; /*��λ*/  /*��carry % 10��ȡ����*/
			carry /= 10; /*���½�λ*/
			++i;
		}//ÿһ��˻��Ľ��
		while (carry) {
			res[i + j] = carry % 10 + '0'; /*��λ*/	/*��carry % 10��ȡ����*/
			carry /= 10; ++i;			   /*��λ*/
		}
		++j;	// ����һ�㣬ָ��num2�Ĺ�������ƶ�һλ
	}
	
	string::iterator iter = res.end() - 1;	/*ɾ��β������Ķ����'0'*/
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

/**********************22. ��һ������n����n��С���ŵ�����������(��˷��backtracking)*****************/
/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:
[
"((()))","(()())","(())()","()(())","()()()"
]
	�ܽ᣺
		1. ����left��right�ֱ��¼'(' ��')'ʣ����ֵĴ�����
		2. ��������'('�����Գ���n�Σ���')'���ɳ���0�Σ�
		3. ���ݼ��㣬���������ų��ֵĴ���Ϊ��Ϊ0��ʱ��˵���Ѿ���������Ŀǰ������ŷŽ�ȥ��
		4. ��'('�����Գ���ʱ����left>0,����������ջ����left -1, ����ʱ���ݶ�Ӧԭ�򣬴�ʱ��¼')'��right+1,��ʾ��Ӧ��Ҫ�Ĵ���
		4. ��')'����Ҫ����ʱ����right>0,����������ջ����right - 1
*/

void backtracking(vector<string> & res, string tmp, int left, int right) {
	if (left == 0 && right == 0) {
		res.push_back(tmp);
		return;
	}
	if (left > 0) backtracking(res, tmp + '(', left - 1, right + 1);/*��һ��'(',��left -1 ,��Ӧ��������һ����¼right+1*/
	if (right > 0) backtracking(res, tmp + ')', left, right - 1);
}
vector<string> generateParenthesis(int n) {
	if (n < 0) return vector<string>();
	vector<string> res;
	string tmp = "";
	backtracking(res, tmp, n, 0);	/*ע���ʱ')'��ʱ����Ҫ����̬�ؿ�'('��ջ�������һ��'(',��Ӧ��������һ����¼right*/
}

/********************************151. ��ת�ַ���*******************************/
/*
	�ܽ᣺
		1. ����ջ���Ƚ�������ԣ����ַ���������ջ����Ҫskip��β���ֵĿո񼰵���֮��ո��Ա���ջ����
		2. ���ȼǵ�skip���ַ���ͷβ�������뵥��֮��Ŀո�ֻΪ���ʶ���
		3. ������󣬾Ϳ�ʼ�浥��
		4. ������˵��ʣ�����ջ��Ȼ��������ʱ�����ַ���words����������
		5. ��������ԭ��������ַ�����׼����ת����ַ��������ջ�д��е��ʣ�׼������ջ����;
		6. ��ջ�Ĺ����мǵ�ÿ�γ�ջ֮��Ҫ����һ��' '.���ָ��
		7. ��󣬽�����ջ����ֵĶ���ķָ���' ' ȥ��������substr(0, s.size() - 1)��
*/
/*����һ��ջ����*/
void reverseWords(string & s) {
	if (s.empty()) return; /*���ַ���ֻ��һ���ַ�ʱ��Ҫע������ǿո�����ֱ�ӷ��أ���Ҫ�ų�ֻ��һ���ո���ַ���*/
	/* if (s.size() == 1 && s[0] != ' ') return; */	// ��ʡ��
	string::iterator iter = s.begin();
	stack<string> strStack;		/*����ջ*/
	string words;				/*����һ������,׼����ջ*/

	while (iter != s.end()) {
		while (*iter == ' ') ++iter;				/*skip���ֿո���ѭ���Ĺ����У��տ�ʼskip��ͷ�Ŀո����й�������skip����Ŀ�											��ͬʱ�����Ҳ��skip��β�ո�*/
		while (iter != s.end() && *iter != ' ') {	/*��¼һ������*/
			words += *iter++;						/*�˴���iter++��������������ƶ��Ĳ���*/
		}
		if (!words.empty())							/*����һ�����ʣ��Ǿ���ջ*/
			strStack.push(words);
		words.clear();								/*������ջ֮��ͼ�ʱ������ʱ�ַ���*/
	}//while ���������ַ���

	s.clear();										/*�����ԭ���������ַ�����׼��ӭ��ջ�ڵ���*/
	while (!strStack.empty()) {				
		s += strStack.top() + ' ';					/*��ʼӭ��ջ�ڵ��ʣ����Կո�������*/
		strStack.pop();								/*remember ��ջ����*/
	}
	s = s.substr(0, s.size() - 1); /*�˴�Ҫע�⣡����ʡ�ԣ���Ϊ������s += strStack.top() + ' ' ʱ��������һ���ո� ' ' */
}
/*��������������stringstream������*/
#include <sstream>
void reverseWords_1(string &s) {
	stringstream is(s);
	string tmp;
	string res;
	while (is >> tmp) {
		if (res.empty()) {
			res = tmp;
		}
		else res = tmp + ' ' + res;			/*�������˳�򣬼� (��(�ճ�¯) + ' ' + ��(֮ǰ�Ѿ�������)) �ɴﵽ��ջ��Ч����*/
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