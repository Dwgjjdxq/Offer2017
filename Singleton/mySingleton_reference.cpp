#include <iostream>
using namespace std;

class mySingleton{

public:
	static mySingleton& GetInstance()	// ����ģʽ�����ü���̬�ֲ�����ʵ�ֵ���ģʽ��Ȼ�򵥣������̲߳���ȫ��
	{
		static mySingleton instance;	// ��̬�ֲ����� �ڵڶ��ε���GetInstanceʱ��ֱ�ӷ���instance
		return instance;
	}

	~mySingleton()
	{
		cout << "~mySingleton()..." << endl;
	}

private:
	mySingleton(const mySingleton& other);
	mySingleton& operator=(const mySingleton& other);

	mySingleton()
	{
		cout << "mySingleton()..." << endl;
	}
};

int main() {
	mySingleton& s1 = mySingleton::GetInstance();	// �������&����Ϊ���ܽ��п�������
	mySingleton& s2 = mySingleton::GetInstance();

	return 0;
}