#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;
#if 0
//	===== 主题：利用实参推演+函数模板 可以将一个大类型的细分类型进行类型的参数化 =====
// T包含所有大类型
template <typename T>
void func(T arg)
{
	cout << typeid(T).name() << endl;
}
// 我给个函数指针类型，想把返回值，参数类型取出来
template <typename R, typename A1, typename A2>
void func2( R(*a)(A1, A2) )
{
	cout << "分离: ";
	cout << typeid(R).name() << "  ";
	cout << typeid(A1).name() << "  ";
	cout << typeid(A2).name() << endl;
}
// 还可以识别类中的方法: 分开识别所属类、返回值、参数
template <typename R, typename T,typename A1, typename A2>
void func3(R(T::*a)(A1, A2))
{
	cout << "类方法分离: ";
	cout << typeid(R).name() << "  ";
	cout << typeid(T).name() << "  ";
	cout << typeid(A1).name() << "  ";
	cout << typeid(A2).name() << endl;
}
// 主函数
class Test
{
public:
	void show(char, int) { cout << "Test::show()" << endl; }
};
int sum(int a, int b) { return a + b; }
int main()
{
	func(20);
	func("aaa");
	// 函数指针
	cout << endl;
	func(sum);
	func2(sum);
	// 类中的方法
	cout << endl;
	func(&Test::show);
	func3(&Test::show);
	return 0;
}
#endif