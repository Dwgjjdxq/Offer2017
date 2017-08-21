#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*�ַ���ȫ���_�ݹ�_���ظ�*/
/*
	δ�ų��ظ������
	��ͷ��βɨ���ַ����õ���һ���ַ�����Ե�һ���ַ���������ѡ��
	1.������ַ��ŵ�������ȥ��������������Ҫ��ʣ�µ�n-1���ַ���ѡȡm-1���ַ�;
	2.�����������ַ��ŵ������ȥ������Ҫ��ʣ�µ�n-1���ַ���ѡȡm���ַ�;
	���� n---�ַ�������  m---��ǰ�ַ�����ϸ���
*/

/*��һ���ַ�����ѡm��Ԫ��*/
void CombinationCore(char *str, int m, vector<char>& res) {
	
	/*�Ѿ�push��m��Ԫ�أ�������*/
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

	//	������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�n-1���ַ���ѡȡm-1���ַ�
	res.push_back(*str);
	CombinationCore(str + 1, m - 1, res);	

	//	��������ַ��ŵ�������ȥ������Ҫ��ʣ�µ�n-1���ַ���ѡȡm���ַ�
	res.pop_back();
	CombinationCore(str + 1, m, res);		
}

void Combination(char *str) {
	if (str == NULL || *str == '\0')
		return;

	int len = strlen(str);
	for (int m = 1; m <= len; ++m) {
		vector<char> res;
		CombinationCore(str, m, res);		//	ѡȡm���ַ���Ϊ���
	}
}

/*�ַ���ȫ���_ѭ����λͼ˼�룩_���ظ�*/
/*
	�ܽ᣺
		����һ����n���ַ�������ܵ���Ͻ��һ����2^n-1�֡�
		���磺����abc,�������3��λ����ʾ�����ҵ����ÿһλ�ֱ�������ʾa��b��c����λΪ1��ʾȥ��Ԫ�أ���λΪ0��ʾ��ȡ��Ԫ�ء�
		���磺���a��ʾ001,���b��ʾ010,���ac��ʾ101�����abc��ʾ111��000�������κ���ϡ�����һ����2^n-1����ϡ�
		��˴�1��ʼѭ����2^n-1�֡����ÿ��ֵ���������ϼ��ɡ�
*/
void Combination2(char *str) {
	if (str == nullptr)
		return;
	int j, tmp;
	int length = strlen(str);
	int n = 1 << length;
	for (int i = 1; i < n; ++i) {	// 2^n-1�����
		for (j = 0; j < length; ++j) {	// ȡ����+jʱ��Ĭ�ϴ�0��ʼ,��λ�ж�
			if (i & (1 << j))		// ����i=011,��jͬ��forѭ������ȡ0��1��011 & 1 == 1�� 011 & 10 == 1������ȡֵ����ab
				cout << *(str + j);
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