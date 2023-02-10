#include <iostream>
#include <functional>
#include <string>
using namespace std;
#if 0
/////////////////////////////////////////////////////////////
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
struct Test { int sum(int a, int b) { return a + b; } };
int main()
{
	// bind是函数模板 可以自动推演模板类型参数
	bind(hello, "hello bind!")();
	cout << bind(sum, 10, 10)() << endl;
	cout << bind(&Test::sum, Test(), 10, 10)() << endl;

	// 参数占位符 可以让binder多种多样,不再像bind1st那些只能绑定一个参数了
	// 绑定器出了语句，无法继续使用
	bind(hello, placeholders::_1)("hello bind2!");
	cout << bind(&Test::sum, Test(), 10, placeholders::_1)(20) << endl;

	// 将bind返回的绑定器binder复用起来
	function<void(string)> func = bind(hello, placeholders::_1);
	func("hello huawei");
	func("hello honor");

	return 0;
}
#endif