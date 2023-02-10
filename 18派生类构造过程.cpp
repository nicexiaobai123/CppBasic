#include <iostream>
using namespace std;
#if 0

class Base
{
public:
	Base(int data)
		:ma(data) 
	{
		cout << "Base(int)" << endl;
	}
	Base() :ma(0)
	{
		cout << "Base(0)" << endl;
	}
	~Base()
	{
		cout << "~Base" << endl;
	}
protected:
	int ma;
};
class Drived : public Base
{
public:
	Drived(int data)
		:Base(data),mb(data)
	{
		cout << "Drived(int)" << endl;
	}
	~Drived()
	{
		cout << "~Drived" << endl;
	}
protected:
	int mb;
};

int main()
{
	Drived dri(10);	

	//	Base(int)
	//	Drived(int)
	//	~Drived
	//	~Base

	return 0;
}
#endif