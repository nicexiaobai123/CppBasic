#include <iostream>
using namespace std;
#if 0
class Test
{
public:
	//普通构造
	Test(int x = 5) :ma(x) { cout << "Test(int)" << endl; }
	//拷贝构造
	Test(const Test& t) :ma(t.ma) { cout << "Test(Test)" << endl; }
	//析构函数
	~Test() { cout << "~Test()" << endl; }
	//拷贝赋值
	Test& operator = (const Test& t)
	{
		cout << "operator=" << endl;
		this->ma = t.ma;
		return *this;
	}
	int getData() { return ma; }
private:
	int ma;
};

//	需要优化的函数
//	3.实参给形参是初始化，调用拷贝构造
//	4.tmp构造函数
Test GetObject(Test t)
{
	int val = t.getData();
	Test tmp(val);
	return tmp;
	//	5.tmp给main中的临时对象，拷贝构造
	//	6.tmp析构	7.形参t析构
}
int main()
{
	Test t1(10);		//1. t1构造函数
	Test t2;			//2. t2构造函数	
	t2 = GetObject(t1);	//8. t2的operator=   9.临时对象析构
	return 0;
	//10. t2析构
	//11. t1析构
}
#endif