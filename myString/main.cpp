#include <stdio.h>

int myStrlen(const char * str);
char * myStrcpy(char * dest, const char * src);
char * myStrcmp(const char * s1, const char * s2);
char * myStrcat(char * dest, const char * src);

int myStrlen(const char * str)
{
	int ret = 0;
	while (*str++)
		++ret;
	return ret;
}



int main() {
	return 0;
}