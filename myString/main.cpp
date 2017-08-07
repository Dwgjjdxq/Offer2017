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

// ���Ƚ��� char * strchr(const char *str, int character); �Ĺ���
// ���ַ���str���ҵ�character����ַ���λ�ã�����һ��ָ��str�е�һ������character�ַ���ָ�룬���û���ҵ����ַ����򷵻ؿ�ָ�룻
// �ٽ��� int strncmp(const char * str1, const char * str2, size_t num);
// �Ƚ�str1 �� str2�������ַ����Ƿ���ȣ�����ַ��ĸ��������num��
// strstr���ܣ�Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
// The matching process does not include the terminating null - characters, but it stops there.
char * myStrstr(char * s1, char * s2) {
	int n = strlen(s2);
	for (; (s1 = strchr(s1, *s2)) != NULL; s1++) // strchr---��s1�ַ����е�һ�������ַ�*s2��λ����Ϣ����s1
	{
		if (strncmp(s1, s2, n) == 0)	// strncmp---��s1����s2������ַ�������n������ͷ���s1
			return s1;
	}
	return NULL;
}
// ϸ���� ������
char * myStrstr_1(char * s1, char * s2) {
	if (*s2) {
		while (*s1) {
			for (int i = 0; *(s1 + i) == *(s2 + i); ++i)
			{
				if (*(s2 + i + 1) == '\0')
					return s1;
			}//for
			s1++;
		}//while
		return NULL;
	}//if
	else return NULL;
}

//C++�汾 ������
#include <iostream>
int strStr(std::string str, std::string pattern) {
	//int len1 = strlen(str.c_str()), len2 = strlen(str.c_str()); // c_str() ����һ��ָ�������ָ�룬����'\0'��β����תΪC��ʽ
	int lenStr = str.length(), lenPattern = pattern.length();
	if (lenStr < lenPattern) return -1;
	if (lenPattern == 0) return 0;

	int i = 0, j = 0;
	while (i < lenStr && j < lenPattern) {
		if (str[i] == pattern[j]) {
			++i; ++j;
		}
		else {
			i = j - i + 1; 
			j = 0;
		}//else
	}//while

	return (j == lenPattern) ? (i - lenPattern) : -1;
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

	// myStrstr
	char buf_8[1024] = "i am a chinese man";
	char buf_9[1024] = "chinese";
	char * ret_Strstr = myStrstr(buf_8, buf_9);
	strncpy(ret_Strstr, "young", 5);
	//puts(buf_8);
	printf("buf_8 = %s\n", buf_8);
	return 0;


}
/*��� �ַ����ָ��strtok ��ʹ�÷���*/
char *strtok(char *s, char *delim); // �����о�̬����,������һ�ο�ʼ�Ǵ�NULLɾ�����Ǹ�λ�ÿ�ʼ
/*
���ܣ��ֽ��ַ���Ϊһ���ַ�����s ΪҪ�ֽ���ַ�����delim Ϊ�ָ����ַ�����
˵�����״ε���ʱ��s ָ��Ҫ�ֽ���ַ�����֮���ٴε���Ҫ�� s ��� NULL��
strtok �� s �в��Ұ����� delim �е��ַ����� NULL('\0')���滻��ֱ���ұ�������
������
����ֵ���� s ��ͷ��ʼ��һ�������ָ�Ĵ�����û�б��ָ�Ĵ�ʱ�򷵻� NULL��
���� delim �а������ַ����ᱻ�˵����������˵��ĵط���Ϊһ���ָ�Ľڵ㡣
*/
int main1() {
	char buf[] = "aaaaaaaa&bbbbbbbbbb*ccccccccccc@ddddddd";
	char delim[] = "&*@";
	char *p = strtok(buf, delim);
	while (p) {
		printf("&s\n", p);
		p = strtok(NULL, delim);
	}
}
