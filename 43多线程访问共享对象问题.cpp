#include <iostream>
#include <memory>
#include <thread>
using namespace std;
#if 0
// 类
class Test
{
public:
	Test() :_ptr(new int(20)) { cout << "Test()" << endl; }
	~Test()
	{
		delete _ptr;
		_ptr = nullptr;
		cout << "~Test()" << endl;
	}
	void show() { cout << "show:" << *_ptr << endl; }
private:
	int* volatile _ptr;
};

// 线程回调函数
void threadPro1(Test* p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	p->show();
}
void threadPro2(weak_ptr<Test> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	// 将弱智能指针提升成强智能指针
	shared_ptr<Test> sp = p.lock();
	if (sp != nullptr) {
		sp->show();
	}
}

// 主函数
int main()
{
	Test* p1 = new Test;
	std::thread t1(threadPro1, p1);
	//delete p1;	这里析构对象会导致子线程访问不到共享的对象；如果是分离
	t1.join();

	// 强弱指针的配合一般在多线程上的应用
	shared_ptr<Test> p2(new Test);
	std::thread t2(threadPro2, weak_ptr<Test>(p2));
	t2.join();
	t2.detach();	// 设置成分离线程则主线程会先执行完，共享对象会直接析构
					// 这就是强弱指针结合的好处：可以知道共享对象是否存在，如果不存在就不执行show()
	return 0;
}
#endif