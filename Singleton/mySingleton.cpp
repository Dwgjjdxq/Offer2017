#include <iostream>
using namespace std;

class mySingleton{
public:
	static mySingleton* GetInstance() {
		if (instance_ == NULL)
		{
			instance_ = new mySingleton;
		}
		return instance_;
	}

	 // 自身无法完成析构，存在内存泄漏风险；
	~mySingleton()
	{
		cout << "~mySingleton()" << endl;
	}

	// 此处用一个嵌套类，利用对象的确定性析构来释放。
	class Garbo{
	public:
		~Garbo()
		{
			if (mySingleton::instance_ != NULL)
				delete instance_;
		}
	};

private:
	// 不能进行拷贝构造和赋值
	mySingleton(const mySingleton& other);
	mySingleton& operator=(const mySingleton& other);

	mySingleton()
	{
		cout << "mySinglenton..." << endl;
	}
	static mySingleton* instance_;

	static Garbo garbo_;	// 利用对象的确定性析构
};

mySingleton* mySingleton::instance_;
mySingleton::Garbo mySingleton::garbo_;

int main() {
	mySingleton* s1 = mySingleton::GetInstance();
	mySingleton* s2 = mySingleton::GetInstance();

	// mySingleton s3(*s1);	// 不合法，因此要将拷贝构造和赋值运算符重载设为私有



	return 0;
}