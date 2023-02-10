#include <iostream>
using namespace std;
#if 0
template<typename T>
class CSmartPtr
{
public:
	// 使用explicit避免智能指针使用隐式转换，不能这样使用：CSmartPtr<int> p = new int
	explicit CSmartPtr(T* ptr = nullptr)
		:mptr(ptr) {}
	~CSmartPtr() { delete mptr; }
	T& operator * () { return *mptr; }
	const T& operator * () const { return *mptr; }
	T* operator -> () { return mptr; }
	const T* operator -> () const { return mptr; }
private:
	T* mptr;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	内置类型
	CSmartPtr<int> p(new int);
	const CSmartPtr<int> p1(new int);
	*p = 10;
	*p1;

	//	自定义类型
	struct Test {
		void test() { cout << "Test::test()" << endl; }
	};
	CSmartPtr<Test> p3(new Test);
	(*p3).test();

	//	指向符运算符重载解析：对象调用指向运算符的重载函数，返回的结果会自动再加上一个->
	//	( p3.operator->() ) ->
	p3->test();

	return 0;
}
#endif