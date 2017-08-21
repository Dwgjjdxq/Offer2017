#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*字符串全组合_递归_有重复*/
/*
	未排除重复的情况
	从头到尾扫描字符串得到第一个字符，针对第一个字符，有两种选择
	1.把这个字符放到数组中去，接下来我们需要在剩下的n-1个字符中选取m-1个字符;
	2.如果不把这个字符放到组合中去，则需要在剩下的n-1个字符中选取m个字符;
	其中 n---字符串长度  m---当前字符串组合个数
*/

/*从一个字符串中选m个元素*/
void CombinationCore(char *str, int m, vector<char>& res) {
	
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
	if (*str == '\0')
		return;

	//	把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选取m-1个字符
	res.push_back(*str);
	CombinationCore(str + 1, m - 1, res);	

	//	不把这个字符放到数组中去，则需要在剩下的n-1个字符中选取m个字符
	res.pop_back();
	CombinationCore(str + 1, m, res);		
}

void Combination(char *str) {
	if (str == NULL || *str == '\0')
		return;

	int len = strlen(str);
	for (int m = 1; m <= len; ++m) {
		vector<char> res;
		CombinationCore(str, m, res);		//	选取m个字符作为组合
	}
}

/*字符串全组合_循环（位图思想）_有重复*/
/*
	总结：
		假设一共有n个字符，则可能的组合结果一共有2^n-1种。
		例如：输入abc,则可以用3个位来表示，从右到左的每一位分别用来表示a、b、c，该位为1表示选取该元素，该位为0表示不选取该元素。
		例如：组合a表示001,组合b表示010,组合ac表示101，组合abc表示111。000不代表任何组合。所以一共有2^n-1种组合。
		因此从1开始循环到2^n-1种。输出每个值所代表的组合即可。
*/
void Combination2(char *str) {
	if (str == nullptr)
		return;
	int length = strlen(str);
	int n = 1 << length;	// 2^n
	for (int bitmap = 1; bitmap < n; ++bitmap) {	// 从1开始，共2^n-1种情况, 
		for (int offset = 0; offset < length; ++offset) {	// 对每一种bitmap偏移量offset均从0开始,按位选取判断。
			if (bitmap & (1 << offset))	//bitmap=011,则j通过for循环依次取0和1，011 & 1 == 1； 011 & 10 == 1。两个取值。即ab
				cout << *(str + offset);
		}
		cout << endl;
	}
}

int main() {
	char str[20];
	cin >> str;
	Combination(str);
	Combination2(str);
	return 0;
}