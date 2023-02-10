#include <iostream>
#include <string>
#include <memory>
using namespace std;
#if 0

//------------------- 简单工厂 ------------------------
// 大型项目的时候有很多类，类名难以记住
// 并且如果想要修改类名，那项目中new类名的地方都要修改，不符合软件设计的思想
// 简单工厂 --- 将创建对象 封装在了SimpleFactory类的createProduct方法当中，通过枚举创建对象
//  产品类型一
class Car
{
public:
	Car(const string& name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};
class Bwm :public Car
{
public:
	Bwm(const string& name) :Car(name) {}
	void show() { cout << "获取了一辆宝马汽车:" << _name << endl; }
};
class Audi :public Car
{
public:
	Audi(const string& name) :Car(name) {}
	void show() { cout << "获取了一辆奥迪汽车:" << _name << endl; }
};
// 简单工厂
enum CarType { BWM, AUDI };
class SimpleFactory
{
public:
	Car* createProduct(CarType ct, const string& name)
	{
		switch (ct)
		{
		case BWM:
			return new Bwm(name);
		case AUDI:
			return new Audi(name);
		default:
			cerr << "闯入参数不正确:" << ct << endl;
			break;
		}
		return nullptr;
	}
};
//------------------- 工厂方法 ------------------------
// 工厂基类
class Factory
{
public:
	virtual Car* createProduct(const string& name) = 0;
};
// 宝马工厂
class BwmFactory : public Factory
{
public:
	Car* createProduct(const string& name) { return new Bwm(name); }
};
// 奥迪工厂
class AudiFactory : public Factory
{
public:
	Car* createProduct(const string& name) { return new Audi(name); }
};
//------------------- 抽象工厂 ------------------------
//  对一组有关联关系的产品簇提供产品对象的统一创建
//  产品类型二
class Light {
public:
	virtual void show() = 0;
};
class BwmLight :public Light {
public:
	void show() { cout << "BWM Light!" << endl; }
};
class AudiLight :public Light {
public:
	void show() { cout << "Audi Light!" << endl; }
};
// 工厂
class AbstractFactory {
public:
	virtual Car* createCar(const string& name) = 0;
	virtual Light* createCarLight() = 0;
};
class BwmFactory2 : public AbstractFactory
{
public:
	Car* createCar(const string& name) { return new Bwm(name); }
	Light* createCarLight() { return new BwmLight; }
};
class AudiFactory2 : public AbstractFactory
{
public:
	Car* createCar(const string& name) { return new Audi(name); }
	Light* createCarLight() { return new AudiLight; }
};

// 主函数
int main()
{
	// 简单工厂演示
	unique_ptr<SimpleFactory> factory(new SimpleFactory);
	unique_ptr<Car> p1(factory->createProduct(BWM, "X1"));
	unique_ptr<Car> p2(factory->createProduct(AUDI, "A6"));
	p1->show();
	p2->show();

	// 工厂方法演示
	cout << "----------------------------" << endl;
	unique_ptr<Factory> bwnFty(new BwmFactory);
	unique_ptr<Factory> audiFty(new AudiFactory);
	unique_ptr<Car> p3(bwnFty->createProduct("X2"));
	unique_ptr<Car> p4(audiFty->createProduct("A8"));
	p3->show();
	p4->show();

	// 抽象工厂演示
	cout << "----------------------------" << endl;
	unique_ptr<AbstractFactory> bwnFty2(new BwmFactory2);
	unique_ptr<AbstractFactory> audiFty2(new AudiFactory2);
	unique_ptr<Car> p5(bwnFty2->createCar("X3"));
	unique_ptr<Car> p6(audiFty2->createCar("A9"));
	unique_ptr<Light> p7(bwnFty2->createCarLight());
	unique_ptr<Light> p8(audiFty2->createCarLight());
	p5->show();
	p6->show();
	p7->show();
	p8->show();

	return 0;
}
#endif