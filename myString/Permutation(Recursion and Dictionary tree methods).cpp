#include <iostream>
using namespace std;

/*字典树法(by july)*/
/*
	总结：(二找、一交换、一翻转)
	1. 找到排列中最后(最右)一个升序的首位位置lastIncrease;
	2. 找到排列中第i位右边最后一个比str[lastIncrease]大的位置minLarge;
	3. 交换str[lastIncrease]和str[minLarge];
	4. 把第lastIncrease+1位到最后的部分翻转(执行此步骤之前，因为第lastIncrease位是最后一个升序的位置，所以从lastIncrease+1到n一定是降序排列的，而执行此步骤后，从i + 1到n变成升序排列)
	例：
	数组21543的下一个排列；
	1. x = 1
	2. y = 3
	3. 1和3交换，得23541
	4. 翻转541，得23145
*/
bool my_next_permutation(char * str, int num) {

	// 1. 找到排列中最后（最右）一个升序(还能增大)的首位位置lastIncrease
	// (lastIncrease从后往前扫描(倒数第二开始和后面一位依次比较)，找到数组中最后一个能增大的位置)
	int lastIncrease = num - 2;
	while (lastIncrease >= 0 && (str[lastIncrease] >= str[lastIncrease + 1])) {
		--lastIncrease;
	}

	// 已经找到所有排列
	if (lastIncrease < 0)
		return false;

	// 2. 找到排列中第lastIncrease位右边最后一个比str[lastIncrease]大的位置minLarge
	int minLarge = num - 1;
	while (minLarge > lastIncrease && (str[minLarge] <= str[lastIncrease])) {
		--minLarge;
	}

	// 3. 交换str[lastIncrease] 和 str[minLarge]  // swap(str[lastIncrease], str[minLarge]);
	str[lastIncrease] ^= str[minLarge];
	str[minLarge] ^= str[lastIncrease];
	str[lastIncrease] ^= str[minLarge];

	// 4. 将第lastIncrese + 1位开始到最后的部分翻转 // 因为从此位置到后面是降序，翻转后为升序，变为最小值
	reverse(str + lastIncrease + 1, str + num);
	return true;
}

/*字符串全排列_递归*/
void my_permutation(char* str, char* beg);

void my_permutation(char* str) {
	if (str == nullptr)
		return;
	my_permutation(str, str);
}

void my_permutation(char* str, char* beg) {
	if (*beg == '\0') {
		cout << str << endl;
	}
	else {
		for (char *ch = beg; *ch != '\0'; ++ch) {
			swap(*ch, *beg);
			my_permutation(str, beg + 1);
			swap(*ch, *beg);
		}//for
	}//if-else
}

/*字符串全排列_递归_去掉重复*/
bool NonDuplication(char* beg, char* end) {
	char* ch = beg;
	while (ch != end) {
		if (beg == end)
			return false;
		++ch;
	}
	return true;
}
void PermutationNonDuplication(char* str, char* beg) {
	if (*beg == '\0') {
		cout << str << endl;
	}
	else {
		for (char* ch = beg; *ch != '\0'; ++ch) {
			if (NonDuplication(beg, ch)) {
				swap(*ch, *beg);		// 此处交换的是*ch与*beg,不是ch 与 beg
				PermutationNonDuplication(str, beg + 1);
				swap(*ch, *beg);
			}
		}
	}
}
void PermutationNonDuplication(char* str){
	if (str == nullptr)
		return;
	PermutationNonDuplication(str, str);
}

int main()
{
	char str[] = "abc";
	do{
		cout << str << endl;
	} while (my_next_permutation(str, 3));
	cout << endl;

	char str1[] = "abc";
	my_permutation(str1);
	cout << endl;
	
	char str2[] = "abc";
	PermutationNonDuplication(str2);

	return 0;
}