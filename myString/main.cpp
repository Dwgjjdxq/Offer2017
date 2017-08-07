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

// 首先介绍 char * strchr(const char *str, int character); 的功能
// 在字符串str中找到character这个字符的位置，返回一个指向str中第一个出现character字符的指针，如果没有找到该字符，则返回空指针；
// 再介绍 int strncmp(const char * str1, const char * str2, size_t num);
// 比较str1 和 str2这两个字符串是否相等，相等字符的个数最大是num个
// strstr功能：Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
// The matching process does not include the terminating null - characters, but it stops there.
char * myStrstr(char * s1, char * s2) {
	int n = strlen(s2);
	for (; (s1 = strchr(s1, *s2)) != NULL; s1++) // strchr---在s1字符串中第一个出现字符*s2的位置信息赋给s1
	{
		if (strncmp(s1, s2, n) == 0)	// strncmp---在s1中找s2，最大字符个数是n，找完就返回s1
			return s1;
	}
	return NULL;
}
// 细化版 暴力法
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

//C++版本 暴力法
#include <iostream>
int strStr(std::string str, std::string pattern) {
	//int len1 = strlen(str.c_str()), len2 = strlen(str.c_str()); // c_str() 返回一个指向数组的指针，并以'\0'结尾，即转为C形式
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
/*添加 字符串分割函数strtok 的使用方法*/
char *strtok(char *s, char *delim); // 里面有静态变量,所以下一次开始是从NULL删除的那个位置开始
/*
功能：分解字符串为一组字符串。s 为要分解的字符串，delim 为分隔符字符串。
说明：首次调用时，s 指向要分解的字符串，之后再次调用要把 s 设成 NULL。
strtok 在 s 中查找包含在 delim 中的字符并用 NULL('\0')来替换，直到找遍整个字
符串。
返回值：从 s 开头开始的一个个被分割的串。当没有被分割的串时则返回 NULL。
所有 delim 中包含的字符都会被滤掉，并将被滤掉的地方设为一处分割的节点。
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
