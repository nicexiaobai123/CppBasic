#include <iostream>
using namespace std;

class CComplex {
public:
	CComplex(int r = 0, int i = 0)
		:mreal(r), mimage(i) {}

	//	指导编译器怎么做CComplex的加法操作
	CComplex operator+(const CComplex& src) {
		return CComplex(mreal + src.mreal, mimage + src.mimage);
	}

	//	前置 返回引用，可作为左值
	CComplex& operator++() {
		++mreal;
		++mimage;
		return *this;
	}

	//	后置 返回临时变量，不可作为左值
	CComplex operator++(int) {
		return CComplex(mreal++, mimage++);
	}
	void show() {
		cout << "mreal: " << mreal << " mimage:" << mimage << endl;
	}

private:
	int mreal;
	int mimage;
	friend CComplex operator+(const CComplex& rhs, const CComplex& lhs);
	friend ostream& operator << (ostream& out, const CComplex& src);
	friend istream& operator >> (istream& in, CComplex& src);
};

//	全局运算符重载
CComplex operator + (const CComplex& rhs, const CComplex& lhs) {
	return CComplex(rhs.mreal + lhs.mreal, rhs.mimage + lhs.mimage);
}
ostream& operator << (ostream& out, const CComplex& src) {
	return out << "mreal:" << src.mreal << " mimage:" << src.mimage;
}
istream& operator >> (istream& in, CComplex& src) {
	return in >> src.mimage >> src.mreal;
}

#if 0
int main()
{
	CComplex com1(20, 20), com2(10, 10);
	CComplex com3 = com1 + com2;

	//	隐式类型转换，因为函数是调用 com1.operator+(const CComplex& src)
	//	这时编译器就会看20是否可以转换成CComplex，就看CComplex构造函数，有其构造函数就产生临时对象
	CComplex com4 = com1 + 20;		
	com3.show();
	com4.show();

	//	成员方法没有重载运算符，就在全局作用域找合适的运算符重载函数
	CComplex com5 = 15 + com1;
	com5.show();

	//	前置++和后置++
	cout << " ================================== " << endl;
	com5 = com1++;
	com1.show();
	com5.show();
	com5 = ++com1;
	com1.show();
	com5.show();

	//	输入输出运算符重载
	cout << " ================================== " << endl;
	CComplex com6;
	cin >> com6;
	cout << com6 << endl;

	return 0;
}
#endif