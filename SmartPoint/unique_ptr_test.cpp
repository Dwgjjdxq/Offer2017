#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;


// unique_ptr����
/*
	1. ��Ҫ��new���������ص�ָ�봫�ݸ�unique_ptr�Ĺ��캯��
	2. 
*/

struct Foo{
	Foo(){ cout << "Foo::Foo\n"; }
	~Foo(){ cout << "Foo::~Foo\n"; }
	void bar() { cout << "Foo::bar\n"; }
};

void func(const Foo &){
	cout << "func(const Foo&)\n";
}

struct D{
	void operator()(Foo* foo)
	{
		cout << "D operator()" << endl;
		delete foo;
	}
};

void TestAutoDestory() {
	// 1. ��δ���unique_ptr
	// ��new���������ص�ָ�봫�ݸ�unique_ptr�Ĺ��캯��
	cout << "TestAutoDestory........." << endl;
	{
		unique_ptr<Foo> p1(new Foo);
	}

	// 2. ����̬���飬��������operator[]
	{
		unique_ptr<Foo[]> p2(new Foo[4]);
	}
	// 3. �����Զ���deleter
	{
		unique_ptr<Foo, D> p3(new Foo);
	}
}

void TestOwner() {
	cout << "TestOwner.........." << endl;
	// 1. �µĶ���
	unique_ptr<Foo> p1(new Foo); // p1ӵ��Foo
	if (p1)
		p1->bar();
	{
		unique_ptr<Foo> p2(move(p1));
		func(*p2);

		p1 = move(p2);
		p2->bar();
		cout << "destorying p2...\n";
	}
	p1->bar();
}

void TestArrayOwner() {
	cout << "TestArrayOwner......." << endl;
	// 1. new[] operator
	unique_ptr<Foo[]> p1(new Foo[4]); // p1 ӵ��һ������Foo
	if (p1)
		p1[0].bar();
	{
		unique_ptr<Foo[]> p2(move(p1));
		func(p2[0]);

		p1 = move(p2);
		p2[0].bar();
		cout << "destorying p2..." << endl;
	}
	p1[0].bar();
}

int main() {
	TestAutoDestory();
	TestOwner();
	TestArrayOwner();
	return 0;
}