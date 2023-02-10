#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;
#if 0
// 生产者消费者模型：生产者生产一个物品，通知消费者；消费完了，消费者再通知生产者继续生产物品

std::mutex mtx;				// 定义互斥锁，用于线程间的互斥
std::condition_variable cv;	// 定义条件变量，用于做线程间的同步通信操作

template<typename T = int>
class Queue {
public:
	// ============ 生产 =============
	void put(T val) {
		unique_lock<std::mutex> lok(mtx);
		// 为什么是while而不是if： 这个例子是一个生产线程一个消费线程用if不会出错，但多个线程生产或消费就会出错
		while (!Que.empty()) {
			// 不为空，则可以不用生产了
			// 1、wait有两部操作（原子）：#1等待信号  #2释放锁
			// 2、wait当被唤醒(notify_all)，解除等待，阻塞到获取互斥锁
			cv.wait(lok); 
		}
		Que.push(val);
		// 生产完，通知消费者消费
		// 其他线程会得到该通知，就会：等待状态=>阻塞状态=>获取到锁才继续执行
		cv.notify_all();
		cout << "生产者 生产" << val << "号物品" << endl;
	}
	// ============ 消费 =============
	T get() {
		unique_lock<std::mutex> lok(mtx);
		// 如果队列没有，则不消费
		while (Que.empty()) {
			cv.wait(lok);
		}
		T val = Que.front();
		Que.pop();
		cv.notify_all();
		cout << "消费者 消费" << val << "号物品" << endl;
		return val;
	}
private:
	queue<T> Que;
};
// 生产者线程函数
void consumer(Queue<int>* que)
{
	for (int i = 1; i <= 10; i++) {
		que->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
// 消费者线程函数
void producer(Queue<int>* que)
{
	for (int i = 1; i <= 10; i++) {
		que->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
// 主线程函数
int main()
{
	// -产品-
	Queue<int> que;
	std::thread t1(consumer,&que);
	std::thread t2(producer,&que);
	t1.join();
	t2.join();
	return 0;
}
#endif