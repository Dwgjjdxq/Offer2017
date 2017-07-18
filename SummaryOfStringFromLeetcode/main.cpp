/*
Summary of String from Leetcode
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**********************���ù�ϣ�����˫ָ������*******************************/
/************3. Longest Substring Without Repeating Characters(������)****************/
/*
��Ŀ������ظ��ַ����Ӵ�
����
���磬��"abcabcbb"�У������ظ��ַ�������ַ�����"abc"���䳤��Ϊ 3��
���ڣ�"bbbbb"�������ظ��ַ�������ַ���Ϊ"b"������Ϊ1��
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




int main() {

	return 0;
}