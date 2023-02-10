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
	int getData()const { return ma; }
private:
	int ma;
};
//	优化
//	1、参数传递引用，减少形参的构造于析构
Test GetObject(Test& t)
{
	int val = t.getData();
	//Test tmp(val);
	//return tmp;
	return Test(val);
	//	2、返回对象时，返回临时对象，
	//	用临时对象拷贝新对象，临时对象被优化；减少临时对象的构造于析构
}
int main()
{
	Test t1(10);
	//	3、接收时，按初始化方式接收而不是赋值方式
	//	用临时对象拷贝新对象，临时对象被优化；减少临时对象的构造于析构
	Test t2 = GetObject(t1);
	//	t2 = GetObject(t1);		//用赋值方式时main还会产生临时对象
	return 0;
	return 0;
}
#endif