#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
#if 0

// 单例模式:一个类不管创建多少次对象，永远只能得到该类型一个对象的实例
// 饿汉单例模式：程序启动时就实例化了该对象，并没有推迟到第一次使用该对象时再进行实例化
// 懒汉单例模式：对象的实例化，延迟到第一次使用它的时候

// ------------------  饿汉单例模式 创建对象时是线程安全的 ---------------------------
// 单例模式创建3步
class Singleton01
{
public:
	// #3 获取唯一实例对象的接口
	static Singleton01* getInstance() {
		return &single;
	}
private:
	// #1 构造函数私有化
	Singleton01() {
		// 很多初始化代码...
		cout << "Singleton01 初始化构造函数..." << endl;
	}
	~Singleton01() { cout << "~Singleton01 " << endl; }
	// #2 定义唯一的实例对象
	static Singleton01 single;
	// 删除拷贝构造和复制，防止产生新的对象
	Singleton01(const Singleton01&) = delete;
	Singleton01& operator=(const Singleton01&) = delete;
};
Singleton01 Singleton01::single;

// ------------------ 懒汉单例模式  非线程安全的，需要加锁 ---------------------------
std::mutex mtx;
class Singleton02
{
public:
	static Singleton02* getInstance() {
		// 在实例化对象的时候加锁，防止多线程时创建多个唯一对象
		if (single == nullptr)
		{
			// 双重校验锁
			lock_guard<std::mutex> guard(mtx);
			if (single == nullptr) {
				single = new Singleton02;
			}
		}
		return single;
	}
private:
	// 其实就是定义一个静态对象，只是这个对象只做释放资源
	// 定义一个嵌套类，在该类的析构函数中，自动释放外层类的资源
	class Release {
	public:
		~Release() { delete single; }
	};
	Singleton02() { cout << "Singleton02 初始化构造函数..." << endl; }
	~Singleton02() { cout << "~Singleton02 " << endl; }

	// 通过该静态对象在程序结束时自动析构的特点，来释放外层类的对象资源
	static Release release;
	static Singleton02* single;
	Singleton02(const Singleton02&) = delete;
	Singleton02& operator=(const Singleton02&) = delete;
};
Singleton02* Singleton02::single = nullptr;
Singleton02::Release Singleton02::release;

// --------------------- 懒汉单例模式 不需要加锁线程安全 -------------------------------
class Singleton03
{
public:
	static Singleton03* getInstance() {
		// 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了
		static Singleton03 single;
		return &single;
	}
private:
	Singleton03() { cout << "Singleton03 初始化构造函数..." << endl; }
	~Singleton03() { cout << "~Singleton03 " << endl; }

	Singleton03(const Singleton03&) = delete;
	Singleton03& operator=(const Singleton03&) = delete;
};

int main()
{
	Singleton01* sig1 = Singleton01::getInstance();
	Singleton01* sig2 = Singleton01::getInstance();
	cout << sig1 << " -- " << sig2 << endl;

	cout << "--------------------------" << endl;
	Singleton02* sig3 = Singleton02::getInstance();
	Singleton02* sig4 = Singleton02::getInstance();
	cout << sig3 << " -- " << sig4 << endl;

	cout << "--------------------------" << endl;
	Singleton03* sig5 = Singleton03::getInstance();
	Singleton03* sig6 = Singleton03::getInstance();
	cout << sig5 << " -- " << sig6 << endl;
	return 0;
}
#endif