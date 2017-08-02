#include <iostream>
using namespace std;

class mySingleton{

public:
	static mySingleton& GetInstance()	// 这种模式用引用及静态局部对象实现单例模式虽然简单，但是线程不安全的
	{
		static mySingleton instance;	// 静态局部对象 在第二次调用GetInstance时，直接返回instance
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
	mySingleton& s1 = mySingleton::GetInstance();	// 必须加上&，因为不能进行拷贝构造
	mySingleton& s2 = mySingleton::GetInstance();

	return 0;
}