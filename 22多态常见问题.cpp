#include <iostream>
using namespace std;

#if 0

//	基类
class Animal {
public:
	Animal(const string& str) :name(str) {}
	virtual void bark() {}
protected:
	string name;
};
//	狗
class Dog :public Animal {
public:
	Dog(const string& str) :Animal(str) { }
	virtual void bark() {
		cout << name << ": wangwang" << endl;
	}
};
//	猪
class Pig :public Animal{
public:
	Pig(const string& str) :Animal(str) { }
	virtual void bark() {
		cout << name << ": hengheng" << endl;
	}
};

//	基类
class Base
{
public:
	virtual void show(int i = 10) {
		cout << "call Base::show i:" << i << endl;
	}
	virtual void print() {
		cout << "call Base::print" << endl;
	}
};
//	派生类
class Derive : public Base
{
public:
	virtual void show(int i = 20) {
		cout << "call Derive::show i:" << i << endl;
	}
private:
	virtual void print() {
		cout << "call Derive::print" << endl;
	}
};

//	基类
class A
{
public:
	A() { 
		cout << "A::ctor" << endl; 
		clear(); 
	}
	virtual void show() { cout << "A::show" << endl; }
private:
	void clear() { memset(this, 0, sizeof(*this)); }
};
//	派生类
class B : public A
{
public:
	B() { cout << "B::ctor" << endl; }
	virtual void show() { cout << "B::show" << endl; }
};

//	
int main()
{
	//	问题一：交换对象的vfptr
	Animal* p1 = new Pig("pppp");
	Animal* p2 = new Dog("wwww");

	int temp = *(int*)p1;
	*(int*)p1 = *(int*)p2;
	*(int*)p2 = temp;

	p1->bark();
	p2->bark();
	delete p1;
	delete p2;

	//	问题二： 虚函数应该避免使用默认参数
	cout << "=======================" << endl;
	Base* b1 = new Derive();

	//	参数压栈是在编译阶段就已经确定好的；看指针类型是Base*，汇编指令上就会压栈10
	//	动态绑定是发生在运行阶段，在call ecx之前，参数就已经压入了 
	b1->show();			//	call Derive::show i:10
	delete b1;

	//	问题三： 编译阶段的访问限制
	cout << "=======================" << endl;
	Base* b2 = new Derive();

	//	为什么Derive里面私有的方法被调用了？
	//	因为调用是发生在运行阶段的；成员方法能不能调用，就是说方法的访问权限是否是public，是在编译阶段就确定好的
	//	首先看b2->print方法为“公有的虚函数”，就编译通过了，进行动态绑定；运行阶段就不会看什么public、private了
	b2->print();		//	call Derive::print
	delete b2;

	//	问题四： vfptr的写入时机
	cout << "=======================" << endl;
	
	// A* c1 = new A;
	// c1->show();
	// delete c1;
	
	//	为什么上面不可以下面可以？
	//	1.A构造函数里面会将vfptr清零，使用虚函数show是动态绑定，运行时vfptr没能指向正确的vftable
	//	2.B继承A，先调用A构造函数，清零vfptr，再调用B的构造函数，为vfptr赋值（指向B类的vftable），后面调用虚函数show就能正确调用
	A* c2 = new B;
	c2->show();			//	B::show
	delete c2;

	return 0;
}
#endif