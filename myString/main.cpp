#include <stdio.h>

int myStrlen(const char * str);
char * myStrcpy(char * dest, const char * src);
int myStrcmp(const char * s1, const char * s2);
char * myStrcat(char * dest, const char * src);

int myStrlen(const char * str)
{
	int ret = 0;
	while (*str++)
		++ret;
	return ret;
}

char * myStrcpy(char * dest, const char * src)
{
	char * ret = dest;
	while (*dest++ = *src++);
	return ret;
}

int myStrcmp(const char * s1, const char * s2)
{
	for (; s1 && s2 && (*s1 == *s2); ++s1, ++s2);
	return (*s1 == *s2) ? 0 : (*s1 > *s2 ? 1 : -1);
}

char * myStrcat(char * dest, const char * src)
{
	char * ret = dest;
	while (*dest)
		++dest;
	while (*dest++ = *src++);
	return ret;
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