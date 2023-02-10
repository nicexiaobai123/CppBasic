#include <iostream>
#include <vector>
using namespace std;
#if 0
// 类模板
template<typename T>
class Vector
{
public:
	Vector() { cout << "call Vector template init" << endl; }
};
// 完全特例化版本
template<>
class Vector<char*>
{
public:
	Vector() { cout << "call Vector template Vector<char*>" << endl; }
};
// 对于指针的部分特例化
template<typename Ty>
class Vector<Ty*>
{
public:
	Vector() { cout << "call Vector template Vector<Ty*>" << endl; }
};
// 对于函数指针的特例化
template<typename R,typename A1,typename A2>
class Vector<R(*)(A1, A2)>
{
public:
	Vector() { cout << "call Vector template Vector<R(*)(A1, A2)>" << endl; }
};
// 对于函数类型的特例化
template <typename R, typename A1, typename A2>
class Vector<R(A1, A2)>
{
public:
	Vector() { cout << "call Vector template Vector<R(A1, A2)>" << endl; }
};
// 主函数
int sum(int a, int b) { return a + b; }
int main()
{
	Vector<int> ve1;
	Vector<int*> ve2;
	Vector<char*> ve3;
	Vector<int(*)(int, int)> ve4;	// 函数指针类型
	Vector<int(int, int)> ve5;		// 函数类型

	// 函数指针类型 与 函数类型的区分
	using PFUNC1 = int(*)(int, int);
	PFUNC1 func1 = sum;
	cout << "sum = " << func1(10, 20) << endl;

	using PFUNC2 = int(int, int);
	PFUNC2* func2 = sum;			// 函数名是函数指针类型
	cout << "sum = " << func2(20, 20) << endl;
	// 也可以(*func2)(20, 20)

	return 0;
}
#endif