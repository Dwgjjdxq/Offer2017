/*
��ʵ���ַ���������������
������strlen, strcat, strcpy, strcmp, strstr

// С�᣺
1. char * p;        char*���ͱ�ʾ�ַ������������ܱ��޸�;
2. char buf[1024];  �ַ������е��ַ����Ա��޸�;
3. ��׼��Ͳ�����μ����;

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myStrlen(const char * str);
char * myStrcat(char * dest, const char * src);
char * myStrcpy(char * dest, const char * src);	// ����char* ��Ŀ�ģ�����ʵ����������
int myStrcmp(const char * str1, const char * str2);
char * myStrstr(char * str, char * pattern);

// �����ַ������ȣ�ֱ������'\0'Ϊֹ
int myStrlen(const char * str) {
	int cnt = 0;
	while (*str++)	// ���ж�*str�Ƿ���ڣ�����*str != '\0'ʱ�����̽���ѭ����������++����һλ����
		++cnt;
	return cnt;
}

// ���������ַ�����ע�⽫�ڶ����ַ����ĵ�һ���ַ����ǵ���һ���ַ�����'\0'λ��
char * myStrcat(char * dest, const char * src) {
	char * ret = dest;
	while (*dest)
		++dest;		// ����������ѭ�������ƶ�������ѭ��������ʱ��dest�պ�ָ��'\0'λ�ã��ȴ����ڱ�����
	while (*dest++ = *src++);
	return ret;
}

// ��src�ַ���������dest�ַ����У�ֱ�Ӹ����ͣ�Ϊ�˴ﵽ�������ǵ����ã�����������(a = b = c), 
// ����char* ��Ŀ�ģ�����ʵ����������
char * myStrcpy(char * dest, const char * src) {
	char * res = dest;
	while (*dest++ = *src++);
	return res;
}

// �Ƚ������ַ�����ͬλ�Ĵ�С
// ��������ַ�����ȫһ�����򷵻�0;(��: "abcde" �� "abcde")
// �����ǰָ��ָ��ĵ�һ���ַ������ַ����ڵڶ����ַ�����ǰָ����ַ����򷵻�1; (��: "ebc" > "abcdef")
// �����ǰָ��ָ��ĵ�һ���ַ������ַ�С�ڵڶ����ַ�����ǰָ����ַ����򷵻�-1;(��: "abcdef" < "ea")
int myStrcmp(const char * dest, const char * src) {
	for (; *dest && *src && (*dest == *src); ++dest, ++src)
		;
	return (*dest == *src ? 0 : (*dest > *src ? 1 : -1));
}
int main() {

	// myStrlen
	char * buf_1 = "china";
	int len = myStrlen(buf_1);
	printf("myStrlen(buf_1) = %d\n", len);

	// myStrcpy
	char buf_2[1024];
	char buf_3[1024] = "china is great";
	myStrcpy(buf_2, buf_3);
	printf("buf_2 = %s\n", buf_2);

	// myStrcmp
	char buf_4[1024] = "abc";
	char buf_5[1024] = "dbcef";
	int ret_cmp = myStrcmp(buf_4, buf_5);
	printf("myStrcmp = %d\n", ret_cmp);

	// myStrcat
	char buf_6[1024] = "china";
	char buf_7[1024] = " is great";
	char * ret_cat = myStrcat(buf_6, buf_7);
	printf("ret_cat = %s\n", ret_cat);

	return 0;
}