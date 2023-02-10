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
		this->ma = t.ma;
		cout << "operator=" << endl;
		return *this;
	}
private:
	int ma;
};
Test t0(10);	//	第一个构造，在进入main之前；程序结束时析构
int main()
{
	cout << "----------------------" << endl;
	Test t1;
	Test t2(t1);
	Test t3 = t1;			//	依然使用的是拷贝构造初始化
	// Test(10)显示生成临时对象，生存周期：所在的语句
	Test t4 = Test(10);		//	与Test t4(10);没有区别
	cout << "----------------------" << endl;
	
	t4 = t2;				//	调用 operator=
	t4 = Test(10);			//	显式构造临时对象：Test(10)构造、 operator=、Test(10)析构
	t4 = (0, 10);			//	隐式构造临时对象：(0,10)为逗号表达式，Test(10)构造、 operator=、Test(10)析构
	cout << "----------------------" << endl;

	// Test* p = &Test(50);		//	p成为野指针，Test(50)构造、 operator=、Test(50)析构
	const Test& ref = Test(50);	//	Test(50)构造,不析构
	cout << "----------------------" << endl;

	static Test t5 = Test(10);	//	静态变量虽然在.data区，但是初始化在语句处；程序结束时析构
	cout << "----------------------" << endl;
	return 0;
}
Test t6(10);	//	第二个构造，在进入main之前；程序结束时析构
#endif