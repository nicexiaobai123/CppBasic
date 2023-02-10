#include <iostream>
#include <vector>
using namespace std;
#if 0
//	基类
class Base
{
public:
	virtual void show() { cout << "Base::show" << endl; }
};
//	派生类
class Derive01 : public Base
{
public:
	void show() { cout << "Derive01::show" << endl; }
};
class Derive02 : public Base
{
public:
	void show() { cout << "Derive02::show" << endl; }
	//	假设是新功能的API接口
	void Derive02Show() { cout << "Derive02::Derive02Show" << endl; }
};
//	提供接口
void showFunc(Base* ptr)
{
	//	功能：如果是Derive02类型的，则不调用show方法，而调用Derive02Show方法；其他则调用show方法
	//	dynamic_cast的使用，RTTI信息识别类型转换；	看RTTI信息可以转换，返回其对象的地址；不能转换返回nullptr
	//	p->vfptr->vftable RTTI信息，如果是，dynamic_cast转换成功
	Derive02* p = dynamic_cast<Derive02*>(ptr);		//	看ptr的RTTI信息是否是Derive02类型的
	if (p != nullptr) {
		p->Derive02Show();
	}
	else {
		ptr->show();
	}
}
//	提供接口
void showFunc02(Base* ptr)
{
	//	如果是使用static_cast类型转换，则是在属于编译时期的转换，不涉及识别RTTI信息；既每次都能转换成功
	Derive02* p = static_cast<Derive02*>(ptr);
	if (p != nullptr) {		//	始终都能转换成功，不会为nullptr
		p->Derive02Show();		//	有可能p2并不是Derive02*类型，而是Derive01*类型
	}
	else {
		ptr->show();
	}
}

int main()
{
	// =======================================
	//	1: const_cast的使用
	//	指针或者引用可用
	int a = 10;
	const int* p = &a;
	//	指针（引用）类型
	int* q0 = const_cast<int*>(p);
	
	const int b = 20;
	//	普通类型，不可用
	// int q1 = const_cast<int>(b);

	// =======================================
	//	2: static_cast的使用
	int num = 10;
	//	没有联系的类型不可用，编译器认为安全的类型才可用
	//short* q2 = static_cast<short*>(&num);

	// =======================================
	//	3: reinterpret_cast的使用，C风格的强转
	int num1 = 10;
	double* q3 = reinterpret_cast<double*>(&num);

	// =======================================
	Derive01 Der1;
	Derive02 Der2;
	showFunc(&Der1);
	showFunc(&Der2);
	cout << "==========================" << endl;
	showFunc02(&Der1);
	showFunc02(&Der2);

	return 0;
}
#endif