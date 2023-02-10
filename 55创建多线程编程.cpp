#include <iostream>
#include <thread>
using std::cout;
using std::endl;
#if 0

void threadHandle1(int time) {
	// 睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread1!" << endl;
}
void threadHandle2(int time) {
	// 睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread2!" << endl;
}
int main()
{
	// 定义一个线程对象，传入一个线程函数，线程就启动了
	std::thread t1(threadHandle1,2);
	std::thread t2(threadHandle2, 3);
	// 主线程等待子线程结束（回收子线程），主线程继续执行
	t1.join();
	t2.join();
	// 子线程有两种形态，分离态和非分离态，默认一般为非分离态
	// 如果设置子线程为分离态，那子线程就会自动回收
	// t1.detach();
	cout << "hello main thread!" << endl;
	return 0;
}
#endif
