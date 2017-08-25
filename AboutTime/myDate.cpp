/*计算两个年月日相隔天数（自定义）*/
#include <iostream>
using namespace std;

struct Date{
	int year;
	int month;
	int day;
};

bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 100 == 0);
}

int GetDayOneMonth(int y, int m) {
	int day[12] = { 31, 28, 31, 30, 31, 30, 30, 31, 30, 31, 30, 31 };
	if (m != 2)
		return day[m - 1];
	else return 28 + isLeap(y);
}
int GetDay(Date d) {
	int days = d.day;	// 本月已经过的天数
	for (int year = 1970; year < d.year; ++year) // 从1970年开始计算，到今年之前的所有天数
		days += 365 + isLeap(year);
	for (int month = 1; month < d.month; ++month)// 计算本年前几个月的天数
		days += GetDayOneMonth(d.year, month);
	return days;
}

int main() {
	Date d1, d2;
	cout << "输入年月日：\n";
	cin >> d1.year >> d1.month >> d1.day;
	cin >> d2.year >> d2.month >> d2.day;
	int days1 = GetDay(d2);
	int days2 = GetDay(d1);
	cout << "天数：" << abs(days1 - days2) << endl;

	return 0;
}