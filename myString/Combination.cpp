#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
	δ�ų��ظ������
	�ݹ�---C(n,m)��ʾ�󳤶�Ϊn���ַ�����m���ַ�����ϣ���ΪC(n,1),C(n,2)...C(n, n)���ܺ͡�
	�ӵ�һ���ַ���ʼɨ�裬ÿ���ַ��������������Ҫô��ѡ�У����ݹ����C(n - 1, m - 1);
	Ҫô����ѡ�У����ݹ����C(n - 1, m)�����������n��ֵ������٣��ݹ����ֹ����n==0��m==0
*/

/*��һ���ַ�����ѡm��Ԫ��*/
void CombinationCore(char *str, int m, vector<char>& res) {
	/*�ַ���Ϊ�գ����߳��ȴﲻ��m*/
	if (str == NULL || (*str == '\0' && m != 0))
		return;
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