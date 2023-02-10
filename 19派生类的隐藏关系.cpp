#include <iostream>
using namespace std;
#if 0
class Base
{
public:
	Base(int data) :ma(data) {}
	void show() { cout << "Base::show()" << endl; }
	void show(int a) { cout << "Base::show(int)" << endl; }
protected:
	int ma;
};
class Drived : public Base
{
public:
	Drived(int data) :Base(data), mb(data) {}
	void show() { cout << "Drived::show()" << endl; }
protected:
	int mb;
};

int main()
{
	Base base(10);
	Drived dri(20);

	//	基类对象 <- 派生类对象	类型从下到上的转换，Y
	base = dri;	
	//	派生类对象 <- 基类对象	类型从上到下的转换，N
	//	dri = base;
	
	//	基类指针（引用） <- 派生类对象	类型从下到上的转换，Y
	Base* pb = &dri;
	pb->show();
	//	派生类指针（引用） <- 基类对象	类型从上到下的转换，N
	//	Drived* pd = (Drived*)&base;	//不安全，涉及到非法内存的访问

	cout << "======================" << endl;
	Drived dr1(10);
	//	dr1.show();			//	Drived::show()
	//	dr1.show(10);		//	派生类有基类同名方法，基类本同名方法全部被隐藏
	dr1.Base::show();	//	Base::show()	被隐藏
	dr1.Base::show(10);	//	Base::show(int)	被隐藏

	return 0;
}
#endif