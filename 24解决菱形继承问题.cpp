#include <iostream>
using namespace std;
#if 0
// =======================================
// 最上的基类
class A {
public:
	A(int data) :ma(data) { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
protected:
	int ma;
};
// =======================================
// 一重继承
class B : virtual public A{
public:
	B(int data) :A(data), mb(data) { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
protected:
	int mb;
};
class C : virtual public A {
public:
	C(int data) :A(data), mc(data) { cout << "C()" << endl; }
	~C() { cout << "~C()" << endl; }
protected:
	int mc;
};
// =======================================
// 菱形继承，需要将上层继承改成虚继承
class D : public B, public C {
public:
	//	“A::A”: 没有合适的默认构造函数可用
	//	只有一份A::ma了，A::ma是靠在D上的，自然要D初始化
	//  B,C都虚继承的A，vbtable都存储int ma；当D普通继承B，C，发现两个vbtable里面的int ma是一样的，直接合成一个，靠在D上
	//	从语法上来理解：A::ma只有一份，而B和C都可以初始化，那我以谁为准呢；应该D自己来初始化，以D自己为准
	D(int data) :A(data), B(data), C(data), md(data) { cout << "D()" << endl; }
	~D() { cout << "~D()" << endl; }
protected:
	int md;
};

int main()
{
	//	菱形继承的问题，出现两个ma：ma，ma，mb，mc，md
	//	解决办法：B和C都虚继承A，让A变成虚基类
	cout << sizeof(D) << endl;
	D d1(10);

	//	D类实例对象内存布局(D并非虚继承，不会产生D的vbptr)：
	/*
	class D size(24) :
			+-- -
		0	| +--- (base class B)
		0	| | {vbptr}
		4   | | mb
			| +---
		8	| +--- (base class C)
		8   | | {vbptr}
		12  | | mc
			| +---
		16	| md
			+---
			+--- (virtual base A)
		20	| ma
			+ ---
	*/
	return 0;
}
#endif