#include <iostream>
#include <thread>
#include <atomic>
#include <list>
using namespace std;
#if 0

// 使用atomic类型变量++、--能保证是原子操作，是线程安全的
// 使用volatile，当一个线程改变data段的数据后，另外的线程能够马上访问到最新值，而不是一个缓存值
// volatile就是防止多线程对共享变量（全局变量）进行缓存，访问的原始内存里面的值
volatile std::atomic_bool isReady = false;
volatile std::atomic_int myCount = 0;

// 子线程函数
void task()
{
	if (!isReady) {
		// 当前线程让出CPU时间片，等待下次调度
		std::this_thread::yield();
	}
	// 使用myCount++是线程安全的
	for (int i = 0; i < 100; i++) myCount++;
}
// 主线程函数
int main()
{
	list<std::thread> tlist;
	for (int i = 0; i < 10; i++) {
		tlist.push_back(std::thread(task));
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));
	isReady = true;
	cout << "myCount: " << myCount << endl;

	for (thread& t : tlist) {
		t.join();
	}
	return 0;
}
#endif