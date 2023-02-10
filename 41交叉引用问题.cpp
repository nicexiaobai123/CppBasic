#include <iostream>
#include <memory>
using namespace std;

#if 0

class B;

class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
public:
	shared_ptr<B> ptr_b;
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
public:
	shared_ptr<A> ptr_a;
};

int main()
{
	//	一个计数器对应一个对象资源
	shared_ptr<A> ptr1(new A);		// A的引用计数为1
	shared_ptr<B> ptr2(new B);		// B的引用计数为1

	ptr1->ptr_b = ptr2;				// 强智能指针拷贝赋值，B的引用计数++，为2
	ptr2->ptr_a = ptr1;				// 强智能指针拷贝赋值，A的引用计数++，为2

	cout << ptr1.use_count() << endl;
	cout << ptr2.use_count() << endl;

	//	出作用域：A与B的引用计数-1，引用计数不为0；无法正确释放资源
	/*
		A()
		B()
		2
		2 
	*/
	return 0;
}
#endif