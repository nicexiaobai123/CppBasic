#include <iostream>
#include <vector>
using namespace std;

#if 0

//	基类
class Base {
public:
	virtual void show() { cout << "A::show()" << endl; }
	void operator delete(void* p)
	{
		cout << "free地址：" << p << endl;
		free(p);
	}
private:
	int ma;
};
//	派生类 Derive，虚继承，这时讲Base是虚基类
class Derive : virtual public Base {
public:
	void show() { cout << "B::show()" << endl; }
	void* operator new (size_t size)
	{
		void* p = malloc(size);
		cout << "malloc申请地址: " << p << endl;
		return p;
	}
private:
	int mb;
};
int main()
{
	//	如果是普通的继承
	// cout << sizeof(Base) << endl;	//	vfptr，ma 8字节
	// cout << sizeof(Derive) << endl;	//	vfptr，ma，mb 12字节

	//	如果是虚继承，会多一个vbptr，指向vbtable
	//	vbtable[0]是vbptr的向上偏移，vbtable[1]是虚基类内容的偏移

	cout << sizeof(Derive) << endl;	//	vbptr，mb，虚基类内容（vfptr，ma），16字节

	cout << "=====================" << endl;
	//	虚继承+虚函数在vs编译器上会出现错误，Linux中g++上不会
	//	错误原因: 释放内存地址与申请的内存地址不一样
	Base* p = new Derive;

	cout << "new返回的地址：" << p << endl;
	p->show();

	delete p;
	/*
		malloc申请地址: 00B6DCF8
		new返回的地址：00B6DD00
		B::show()
		free地址：00B6DD00
	*/
	return 0;
}
#endif