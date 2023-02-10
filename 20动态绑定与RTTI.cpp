#include <iostream>
#include <typeinfo>
using namespace std;
#if 0
class Base
{
public:
	Base(int data) :ma(data) {}
	virtual void show() { cout << "Base::show()" << endl; }
	virtual void show(int a) { cout << "Base::show(int)" << endl; }
	void print() { cout << "Base::print()" << endl; }
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
	Drived d(20);
	Base* bp = &d;
	bp->print();		//	静态绑定
	bp->show();			//	动态绑定

	//	信息
	cout << "================" << endl;
	cout << sizeof(Base) << endl;
	cout << sizeof(Drived) << endl;
	cout << typeid(bp).name() << endl;
	cout << typeid(*bp).name() << endl;		//	如果类有虚函数，*pd识别的就是运行时期的类型；就是找RTTI
	return 0;
}
#endif