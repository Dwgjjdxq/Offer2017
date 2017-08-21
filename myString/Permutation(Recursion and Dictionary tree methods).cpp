#include <iostream>
using namespace std;

/*�ֵ�����(by july)*/
/*
	�ܽ᣺(���ҡ�һ������һ��ת)
	1. �ҵ����������(����)һ���������λλ��lastIncrease;
	2. �ҵ������е�iλ�ұ����һ����str[lastIncrease]���λ��minLarge;
	3. ����str[lastIncrease]��str[minLarge];
	4. �ѵ�lastIncrease+1λ�����Ĳ��ַ�ת(ִ�д˲���֮ǰ����Ϊ��lastIncreaseλ�����һ�������λ�ã����Դ�lastIncrease+1��nһ���ǽ������еģ���ִ�д˲���󣬴�i + 1��n�����������)
	����
	����21543����һ�����У�
	1. x = 1
	2. y = 3
	3. 1��3��������23541
	4. ��ת541����23145
*/
bool my_next_permutation(char * str, int num) {

	// 1. �ҵ�������������ң�һ������(��������)����λλ��lastIncrease
	// (lastIncrease�Ӻ���ǰɨ��(�����ڶ���ʼ�ͺ���һλ���αȽ�)���ҵ����������һ���������λ��)
	int lastIncrease = num - 2;
	while (lastIncrease >= 0 && (str[lastIncrease] >= str[lastIncrease + 1])) {
		--lastIncrease;
	}

	// �Ѿ��ҵ���������
	if (lastIncrease < 0)
		return false;

	// 2. �ҵ������е�lastIncreaseλ�ұ����һ����str[lastIncrease]���λ��minLarge
	int minLarge = num - 1;
	while (minLarge > lastIncrease && (str[minLarge] <= str[lastIncrease])) {
		--minLarge;
	}

	// 3. ����str[lastIncrease] �� str[minLarge]  // swap(str[lastIncrease], str[minLarge]);
	str[lastIncrease] ^= str[minLarge];
	str[minLarge] ^= str[lastIncrease];
	str[lastIncrease] ^= str[minLarge];

	// 4. ����lastIncrese + 1λ��ʼ�����Ĳ��ַ�ת // ��Ϊ�Ӵ�λ�õ������ǽ��򣬷�ת��Ϊ���򣬱�Ϊ��Сֵ
	reverse(str + lastIncrease + 1, str + num);
	return true;
}

/*�ַ���ȫ����_�ݹ�*/
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

/*�ַ���ȫ����_�ݹ�_ȥ���ظ�*/
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
				swap(*ch, *beg);		// �˴���������*ch��*beg,����ch �� beg
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