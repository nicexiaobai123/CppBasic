#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <vector>
using namespace std;
#if 0

// 线程信息  function保留类型 
class Thread
{
public:
	Thread(function<void(int)> func, int no)
		: _func(func), _no(no)
	{	}
	thread start() { return thread(_func, _no); }
private:
	function<void(int)>	_func;	// 回调函数
	int _no;					// 参数
};

// 线程池  bind绑定成员方法 
class ThreadPool
{
public:	
	ThreadPool() {}
	~ThreadPool() { for (auto v : _pool) delete v; }
	void startPool(int size) 
	{
		for (int i = 0; i < size; i++) 
			// 需要借助绑定器，因为线程回调函数不能是成员方法，绑定器绑定this指针
			_pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, placeholders::_1), i));

		for (Thread* t : _pool)
			_handlers.push_back(t->start());

		for (thread& handler : _handlers)
			handler.join();
	}
private:
	// 把runInThread这个成员方法充当线程函数
	void runInThread(int no) {
		cout << "call runInThread id: " << no << endl;
	}
private:
	vector<Thread*> _pool;
	vector<thread> _handlers;
};
//////////////////////////////////////////////////////////////
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ThreadPool pool;
	pool.startPool(10);
	return 0;
}
#endif