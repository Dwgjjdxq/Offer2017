/*About Stack*/
#include <iostream>
#include <stack>

using namespace std;
 
class Solution{
public:
	/*
	˼·������stackA�������stackBΪ����ջ��stackAԪ�ظ���ΪN��
	��1�β�������ȡstackAջ��Ԫ�أ���Ϊtmp��Ȼ���ʣ��N-1��Ԫ��ת�Ƶ�stackB�У����Ű�tmp��stackB��N-1��Ԫ������ѹ��stackA�У����������stackAԭջ���ķ�ת��
	��2�β�������ȡstackAջ��Ԫ�أ���Ϊtmp����Ϊջ����һ��Ԫ������ɷ�ת����ֻ��Ҫ��ʣ���N-2��Ԫ��ת�Ƶ�stackB�����Ű�tmp��stackB��N-2��Ԫ������ѹ��stackA�У����������stackAԭջ���ڶ���Ԫ�صķ�ת��
	...

	��i�β�������ȡstackAջ��Ԫ�أ���Ϊtmp��֮ǰ����i-1��Ԫ����ɷ�ת��ֻ��Ҫ��ջ����N-i+1��Ԫ��ת�Ƶ�stackB�����Ű�tmp��stackB��N-i+1����ѹ��stackA�С�
	ע�⣺��N�β���ʱ����Ϊǰ��N-1�β�������ɣ�����ʱ��ջ�����ǳ�ʼ��ջ�ף��ʵ�N�β�������Ҫ�����ܵĹ���ֻ��ҪN-1�β�����
	*/
	/*��������ջ����ת����һ��ջ*/
	void ReverseStack(stack<int> &A, stack<int>&B) {
		if (A.empty())
			return;
		// ����Ҫ���� A.size() - 1 ��
		for (int i = 0; i < A.size() - 1; ++i) {
			// 1.ȡ��A��ջ��Ԫ��
			int tmp = A.top();
			A.pop();
			// 2.�����Ѿ�A�з�ת���Ԫ�أ�����Ԫ��ת�Ƶ�Bջ�С�
			while (A.size() > i) {
				B.push(A.top());
				A.pop();
			}
			// 3.����ѹ��tmp��B��Ԫ�ص�A��ȥ
			A.push(tmp);
			while (!B.empty()) {
				A.push(B.top());
				B.pop();
			}//while B
		}// for
	}//ReverseStack

	void TestReverseStack() {
		stack<int> A;
		stack<int> B;
		cout << "��ջ˳��" << endl;
		for (int i = 5; i > 0; --i) {
			cout << i << " ";
			A.push(i);
		}
		cout << endl;
		cout << "��ת���ջ����ջ�׵�˳��" << endl;
		ReverseStack(A, B);
		while (!A.empty()) {
			cout << A.top() << " ";
			A.pop();
		}//while
		cout << endl;
	}
};

int main() {
	Solution sln;
	sln.TestReverseStack();
	return 0;
}