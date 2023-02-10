#include <iostream>
#include <vector>
using namespace std;

#if 0

//	基类
class Animal {
public:
	Animal(const string& str):name(str) {}
	virtual void bark() {}
protected:
	string name;
};
//	狗
class Dog :public Animal {
public:
	Dog(const string& str) :Animal(str) { }
	virtual void bark() {
		cout << name << ": wangwang" << endl;
	}
};
//	猪
class Pig :public Animal {
public:
	Pig(const string& str) :Animal(str) { }
	virtual void bark() {
		cout << name << ": hengheng" << endl;
	}
};
//	猫
class Cat :public Animal {
public:
	Cat(const string& str) :Animal(str) { }
	virtual void bark() {
		cout << name << ": miaomiao" << endl;
	}
};
//	提供bark接口
//	软件设计原则："开闭原则" --> 对修改关闭，对扩展开放
//	在添加类后，依然可以直接使用这个bark接口，无需修改
//	删除一个类后，bark不用删除或修改，依然可以用
void bark(Animal& p) {
	p.bark();
}
int main()
{
	Pig pig("佩奇");
	Cat cat("小喵");
	Dog dbg("旺财");
	bark(pig);
	bark(cat);
	bark(dbg);
	return 0;
}
#endif