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
		����ָ��ģ����Ҫ��
		1. ָ���������ڽ���ʱ�����ͷŶԿռ䣻
		2. һƬ�ѿռ����ֻ����һ��ָ���ʶ��
		3. �ž�ָ�������ָ��Ƚϡ�
	*/
	SmartPointer<Test> sp = new Test();

	SmartPointer<Test> nsp;

	nsp = sp;
	
	// nsp++; // ���ܽ���ָ��++����

	cout << sp.isNull() << endl;
	cout << nsp.isNull() << endl;


	return 0;
}