#include <iostream>
using namespace std;

/*去除字符串中的空格及翻转字符串语句*/

void myreverse(char * beg, char * end) {
	if (beg == NULL || end == NULL)
		return;
	while (beg < end) {
		char tmp = *beg;
		*beg = *end;
		*end = tmp;
		++beg; --end;
	}
}

char * reverseSentence(char *str) {
	if (str == NULL)
		return '\0';
	char *end = str;
	// 去多余空格，只保留一个空格
	// 首部
	while (*end == ' ')
		++end;
	// 中间
	int i = 0;
	while (*end != '\0') {
		if (*end != ' ')
			str[i++] = *end++;
		else {
			while (*end == ' ')
				++end;
			str[i++] = ' ';
		}
	}
	// 去除最后多余的一个空格
	if (str[i - 1] == ' ')
		str[i - 1] = '\0';
	else str[i] = '\0';

	end = str;
	while (*end != '\0') {
		++end;
	}
	--end;
	char *beg = str;
	myreverse(beg, end);
	beg = end = str;
	while (*beg != '\0') {
		if (*beg == ' ') {
			++beg; ++end;
		}
		else if (*end == ' ' || *end == '\0') {
			myreverse(beg, --end);
			beg = ++end;
		}
		else ++end;
	}
	return str;
}

int main(){
	char str[1024];
	while (gets(str)) {
		cout << reverseSentence(str) << endl;
	}
	return 0;
}