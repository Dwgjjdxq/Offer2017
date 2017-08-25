/*������������������������Զ��壩*/
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
	int days = d.day;	// �����Ѿ���������
	for (int year = 1970; year < d.year; ++year) // ��1970�꿪ʼ���㣬������֮ǰ����������
		days += 365 + isLeap(year);
	for (int month = 1; month < d.month; ++month)// ���㱾��ǰ�����µ�����
		days += GetDayOneMonth(d.year, month);
	return days;
}

int main() {
	Date d1, d2;
	cout << "���������գ�\n";
	cin >> d1.year >> d1.month >> d1.day;
	cin >> d2.year >> d2.month >> d2.day;
	int days1 = GetDay(d2);
	int days2 = GetDay(d1);
	cout << "������" << abs(days1 - days2) << endl;

	return 0;
}