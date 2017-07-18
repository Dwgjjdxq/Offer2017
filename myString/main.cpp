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
	return (s1 == s2) ? 0 : (s1 > s2 ? 1 : -1);
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

	return 0;
}