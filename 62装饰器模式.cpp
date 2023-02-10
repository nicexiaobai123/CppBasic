#include <iostream>
#include <string>
#include <memory>
using namespace std;
#if 0
// 装饰器模式：Decorator
/* 
	通过子类实现功能增加的问题：为了增强现有类的功能，通过实现子类的方式重写接口，
	是可以完成功能的扩展的，但是代码中有太多的子类添加进来了
*/
// 抽象类
class Car {
public:
	virtual void showInfo() = 0;
};
// 实际类
class Bwm :public Car {
public:
	void showInfo() { cout << "这是一辆宝马汽车，配置有: 基本配置"; }
};
class Audi :public Car {
public:
	void showInfo() { cout << "这是一辆奥迪汽车，配置有: 基本配置"; }
};
class Bnze :public Car {
public:
	void showInfo() { cout << "这是一辆奔驰汽车，配置有: 基本配置"; }
};
// 装饰器，增加新功能
// 如果没有需要新增的公共方法，可以不用写一个抽象基类再继承
class ConcreateDecorator01 : public Car {
public:
	ConcreateDecorator01(Car* p) :pCar(p) { }
	// 装饰：添加新功能 定速巡航
	void showInfo() {
		pCar->showInfo();
		cout << "，定速巡航功能";
	}
private:
	Car* pCar;
};
class ConcreateDecorator02 : public Car {
public:
	ConcreateDecorator02(Car* p) :pCar(p) { }
	// 装饰：添加新功能 自动刹车
	void showInfo() {
		pCar->showInfo();
		cout << "，自动刹车功能";
	}
private:
	Car* pCar;
};
// 主函数
int main()
{
	// 通过装饰器装饰
	unique_ptr<Car> p1(new Audi);
	unique_ptr<Car> p2(new ConcreateDecorator01(p1.get()));	// 一次装饰
	unique_ptr<Car> p3(new ConcreateDecorator02(p2.get())); // 二次装饰

	p2->showInfo();
	cout << endl;

	p3->showInfo();
	cout << endl;
	return 0;
}
#endif