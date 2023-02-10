#include <iostream>
#include <memory>
using namespace std;
#if 0
int main()
{
	//==== 不带引用计数的指针，一个外部资源只能被一个指针指针指向，是unique的 ====
	//	1、auto_ptr，在17中被移除了，需要切换到14，这个不建议使用
	auto_ptr<int> p1(new int);
	auto_ptr<int> p2(p1);	//	使用浅拷贝，并将原来p1的指针指向nullptr；如果使用者不知道底层原理，使用起来非常危险
	*p2 = 10;				//	表示资源转移
	//*p1 = 10;				//	访问nullptr

	//	2、C11新标准：boost::scoped_ptr
	//	将拷贝构造和赋值删除了
	// scoped_ptr(consts coped_ptr<T>& ptr) = delete;
	// scoped_ptr<T>& operator=(consts coped_ptr<T>& ptr) = delete;

	//	3、推荐使用unique_ptr，同样拷贝构造和赋值删除了；但提供了右值引用版本的
	unique_ptr<int> p3(new int);
	unique_ptr<int> p4(std::move(p3));	//	使用者在使用过程中 知道自己已经移动了；auto_ptr就是用户感知不到
	//*p3 = 20;	已经被移动了，不在持有资源了
	*p4 = 10;
	cout << *p4 << endl;
	return 0;
}
#endif