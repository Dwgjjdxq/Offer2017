#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

namespace DTLib
{
	template <typename T>
	class SmartPointer{
	protected:
		T* m_pointer;	// 成员变量，原生的指针
	public:
		/*初始化的构造函数*/
		explicit SmartPointer(T* p = NULL) {
			m_pointer = p;
		}

		/*拷贝构造函数*/
		SmartPointer(const SmartPointer<T>& obj) {
			m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&> (obj).operator = NULL;
		}

		/*赋值运算符重载*/
		SmartPointer<T>& operator = (const SmartPointer<T> & obj) {
			if (this != &obj)
			{
				delete m_pointer;
				m_pointer = obj.m_pointer;
				const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
			}
			return *this;
		}

		/*重载指针的特征操作符 '->' */
		T* operator->() {
			return m_pointer;
		}

		/*重载指针的特征操作符 '*' */
		T& operator* () {
			return *m_pointer;
		}

		/*普通成员函数isNull*/
		bool isNull() {
			return (m_pointer == NULL);
		}

		/*普通成员函数get*/
		T* get() {
			return m_pointer;
		}

		/*析构函数*/
		~SmartPointer()
		{
			delete m_pointer;
		}

	};
}

#endif // SMARTPOINTER_H