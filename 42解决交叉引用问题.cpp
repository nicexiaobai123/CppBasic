#include <iostream>
#include <memory>
using namespace std;

#if 0

// 定义对象时，用强智能指针shared_ptr，在其它地方引用对象时，使用弱智能指针weak_ptr

class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
public:
	// 弱智能指针
	weak_ptr<B> ptr_b;
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
public:
	// 弱智能指针
	weak_ptr<A> ptr_a;
};

int main()
{
	//	一个计数器对应一个对象资源
	shared_ptr<A> ptr1(new A);		// A的引用计数为1
	shared_ptr<B> ptr2(new B);		// B的引用计数为1

	ptr1->ptr_b = ptr2;				// 弱智能指针不会更改引用计数，它只是一个观察者的作用
	ptr2->ptr_a = ptr1;				// 弱智能指针不会更改引用计数，它只是一个观察者的作用

	cout << ptr1.use_count() << endl;
	cout << ptr2.use_count() << endl;

	//	出作用域：A与B的引用计数-1，引用计数为0；正确释放资源
	/*
		A()
		B()
		1
		1
		~B()
		~A()
	*/
	return 0;
}
#endif