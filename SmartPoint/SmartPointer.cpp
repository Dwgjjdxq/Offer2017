#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;

class Test{
public:
	Test()
	{
		cout << "Test()" << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
};

int main() {
	/*
		智能指针模板类要求：
		1. 指针生命周期结束时主动释放对空间；
		2. 一片堆空间最多只能由一个指针标识；
		3. 杜绝指针运算和指针比较。
	*/
	SmartPointer<Test> sp = new Test();

	SmartPointer<Test> nsp;

	nsp = sp;
	
	// nsp++; // 不能进行指针++运算

	cout << sp.isNull() << endl;
	cout << nsp.isNull() << endl;


	return 0;
}