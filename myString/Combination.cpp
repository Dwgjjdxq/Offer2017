#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
	未排除重复的情况
	递归---C(n,m)表示求长度为n的字符串中m个字符的组合，即为C(n,1),C(n,2)...C(n, n)的总和。
	从第一个字符开始扫描，每个字符都有两种情况，要么被选中，即递归求解C(n - 1, m - 1);
	要么不被选中，即递归求解C(n - 1, m)。两种情况，n的值都会减少，递归的终止条件n==0或m==0
*/

/*从一个字符串中选m个元素*/
void CombinationCore(char *str, int m, vector<char>& res) {
	/*字符串为空，或者长度达不到m*/
	if (str == NULL || (*str == '\0' && m != 0))
		return;
	/*已经push了m个元素，输出组合*/
	if (m == 0) {
		static int cnt = 0;
		cout << ++cnt << ":";
		for (int i = 0; i < res.size(); ++i) {
			cout << res[i];
		}
		cout << endl;
		return;
	}

	res.push_back(*str);
	CombinationCore(str + 1, m - 1, res);
	res.pop_back();
	CombinationCore(str + 1, m, res);
}

void Combination(char *str) {
	if (str == NULL || *str == '\0')
		return;

	int len = strlen(str);
	for (int m = 1; m <= len; ++m) {
		vector<char> res;
		CombinationCore(str, m, res);
	}
}

int main() {
	char str[20];
	cin >> str;
	Combination(str);
	return 0;
}