#include <iostream>
#include <vector>
using namespace std;

class CTest {
public:
	void func() {
		cout << "CTest::func" << endl;
	}
	static void static_func() {
		cout << "CTest::static_func" << endl;
	}
	int ma;
	static int mb;
};
int CTest::mb = 12;

#if 0
int main()
{
	CTest t1;
	CTest* t2 = new CTest;

	//“初始化”: 无法从“void (__thiscall CTest::* )(void)”转换为“void (__cdecl *)(void)”
	void (CTest::*p1func)() = &CTest::func;
	(t1.*p1func)();		//	CTest::func
	(t2->*p1func)();	//	CTest::func
	
	void (*p2func)() = &CTest::static_func;
	(*p2func)();		//	CTest::static_func


	//“初始化”: 无法从“int CTest::* ”转换为“int* ”
	int CTest::*p1 = &CTest::ma;
	t1.*p1 = 20;
	t2->*p1 = 30;
	cout << t1.ma << " " << t2->ma << endl;		//	20	30

	int* p2 = &CTest::mb;
	*p2 = 40;
	cout << "static: " << CTest::mb << endl;	//	static:40

	delete t2;
	return 0;
}
#endif