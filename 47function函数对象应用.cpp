#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;
#if 0
void hello(string str)
{
	cout << str << endl;
}
class Test
{
public:
	void show(string str) { cout << str << endl; }
};
int main()
{
	// function保留函数类型
	function<void(string)> func1 = hello;
	func1("hello function");

	// 保留函数对象类型
	function<int(int, int)> func2 = [](int a, int b)->int {return a + b; };
	cout << func2(100, 100) << endl;

	// 保留类的成员方法类型
	function<void(Test*, string)> func3 = &Test::show;
	Test tmp;
	func3(&tmp, "Test::show() call");

	cout << "--------------------------" << endl;

	// C语言的函数指针接受lambda
	int(*fptr)(int,int) = [](int a, int b)->int {return a + b; };
	cout << fptr(100, 100) << endl;

	// C语言函数指针无法做到接收绑定器返回的函数对象；而强大的function就可以
	// bool(*fptr1)(int) = bind1st(less<int>(), 10);
	function<bool(int)> func4 = bind1st(less<int>(), 10);
	cout << func4(11) << endl;
	return 0;
}
#endif 