#include <iostream>
#include <list>
#include <thread>
#include <mutex>
using namespace std;
#if 0

// 多个线程竞争同一资源的的时候就会，如果对资源访问顺序敏感，就会存在竞态条件
int ticketCount = 100;
mutex mtx;
void sellTicket(int index)
{
	while (ticketCount > 0) {
		// 需要：锁 + 双重判断
		/* 原因：在ticketCount = 1的时候, 线程1满足>0, 加锁, ticketCount--时时间片到期;
				线程2同样满足>0,lock阻塞等待线程1执行完; 时间片切换到线程1,ticketCount--完成,unlock
				这时ticketCount=0，但线程2被继续执行,使用了ticketCount=0,逻辑错误；所以需要 锁 + 双重判断
		*/
		//mtx.lock();
		//ticketCount--;
		//mtx.unlock();
		// 
		{
			// 将直接使用mutex换成了lock_guard，lock_guard就相当于智能指针里面的scope_ptr(没拷贝构造和赋值)
			// 防止临界区代码段因为异常而导致锁不能正确释放，造成死锁
			lock_guard<mutex> lock(mtx);
			if (ticketCount > 0) {
				// 导致竞态条件的代码区->临界区，需要让这一块变成原子操作，则需要线程间互斥->使用mutex
				cout << "窗口:" << index << " 卖出第" << ticketCount << "票了！" << endl;
				ticketCount--;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
int main()
{
	list<thread> thdList;
	for (int i = 1; i <= 3; i++) {
		thdList.push_back(std::thread(sellTicket, i));
	}
	for (thread& t : thdList) {
		t.join();
	}
	cout << "车票已经全部卖完!" << endl;
	return 0;
}
#endif