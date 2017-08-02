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

	 // �����޷���������������ڴ�й©���գ��˴���һ��Ƕ���࣬���ö����ȷ�����������ͷš�
	~mySingleton()
	{
		cout << "~mySingleton()" << endl;
	}

	class Garbo{
	public:
		~Garbo()
		{
			if (mySingleton::instance_ != NULL)
				delete instance_;
		}
	};

private:
	// ���ܽ��п�������͸�ֵ
	mySingleton(const mySingleton& other);
	mySingleton& operator=(const mySingleton& other);

	mySingleton()
	{
		cout << "mySinglenton..." << endl;
	}
	static mySingleton* instance_;

	static Garbo garbo_;	// ���ö����ȷ��������
};

mySingleton* mySingleton::instance_;
mySingleton::Garbo mySingleton::garbo_;

int main() {
	mySingleton* s1 = mySingleton::GetInstance();
	mySingleton* s2 = mySingleton::GetInstance();

	// mySingleton s3(*s1);	// ���Ϸ������Ҫ����������͸�ֵ�����������Ϊ˽��



	return 0;
}