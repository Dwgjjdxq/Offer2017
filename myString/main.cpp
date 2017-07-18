/*
自实现字符串常见操作函数
包括：strlen, strcat, strcpy, strcmp, strstr

// 小结：
1. char * p;        char*类型表示字符串常量，不能被修改;
2. char buf[1024];  字符数组中的字符可以被修改;
3. 标准库就不做入参检查了;

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myStrlen(const char * str);
char * myStrcat(char * dest, const char * src);
char * myStrcpy(char * dest, const char * src);	// 返回char* 的目的，在于实现连续拷贝
int myStrcmp(const char * str1, const char * str2);
char * myStrstr(char * str, char * pattern);

// 计算字符串长度，直到遇到'\0'为止
int myStrlen(const char * str) {
	int cnt = 0;
	while (*str++)	// 先判断*str是否存在（即当*str != '\0'时，即刻进行循环）；再做++右移一位操作
		++cnt;
	return cnt;
}

// 链接两个字符串，注意将第二个字符串的第一个字符覆盖到第一个字符串的'\0'位置
char * myStrcat(char * dest, const char * src) {
	char * ret = dest;
	while (*dest)
		++dest;		// 必须这样在循环中做移动操作，循环结束的时候dest刚好指向'\0'位置，等待后期被覆盖
	while (*dest++ = *src++);
	return ret;
}

// 将src字符串拷贝到dest字符串中，直接覆盖型，为了达到连续覆盖的作用，类似于连等(a = b = c), 
// 返回char* 的目的，在于实现连续拷贝
char * myStrcpy(char * dest, const char * src) {
	char * res = dest;
	while (*dest++ = *src++);
	return res;
}

// 比较两个字符串相同位的大小
// 如果两个字符串完全一样，则返回0;(如: "abcde" 与 "abcde")
// 如果当前指针指向的第一个字符串的字符大于第二个字符串当前指向的字符，则返回1; (如: "ebc" > "abcdef")
// 如果当前指针指向的第一个字符串的字符小于第二个字符串当前指向的字符，则返回-1;(如: "abcdef" < "ea")
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