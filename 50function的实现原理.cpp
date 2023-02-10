#include <iostream>
#include <functional>
#include <string>
using namespace std;
#if 0

////////////////////////////////////////
template<typename Fty>
class myfunction
{ };

//// 部分特例化,函数类型:一个参数
//template<typename R,typename A1>
//class myfunction<R(A1)>
//{
//public:
//	using PFUNC = R(*)(A1);
//	myfunction(PFUNC ptr = nullptr) :pfunc(ptr) { }
//	R operator()(A1 arg)
//	{
//		return pfunc(arg);
//	}
//private:
//	PFUNC pfunc;
//};
//// 部分特例化,函数类型:两个参数
//template<typename R, typename A1, typename A2>
//class myfunction<R(A1, A2)>
//{
//public:
//	using PFUNC = R(*)(A1, A2);
//	myfunction(PFUNC ptr = nullptr) :pfunc(ptr) { }
//	R operator()(A1 arg1, A2 arg2)
//	{
//		return pfunc(arg1, arg2);
//	}
//private:
//	PFUNC pfunc;
//};
// 
// 
// 部分特例化+可变模板参数（表示的不是一个类型，而是一组类型）
template<typename R,typename... A>
class myfunction<R(A...)>
{
public:
	using PFUNC = R(*)(A...);
	myfunction(PFUNC ptr = nullptr) :pfunc(ptr) { }
	R operator()(A... args)
	{
		return pfunc(args...);
	}
private:
	PFUNC pfunc;
};

//////////////////////////////////////////////////////////////
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
int main()
{
	myfunction<void(string)> func1 = hello;
	func1("hello world");		// 调用 func1.operator()

	myfunction<int(int,int)> func2 = sum;
	cout << func2(10, 10) << endl;

	return 0;
}
#endif
