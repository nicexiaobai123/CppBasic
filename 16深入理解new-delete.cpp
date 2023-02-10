#include <iostream>
using namespace std;

#if 0
void* operator new (size_t size) 
{
	void* ptr = malloc(size);
	if (ptr == nullptr)
	{
		throw bad_alloc();
	}
	cout << "operator new: " << ptr << endl;
	return ptr;
}
void operator delete (void* ptr)
{
	cout << "operator delete: " << ptr << endl;
	free(ptr);
}
void* operator new[] (size_t size)
{
	void* ptr = malloc(size);
	if (ptr == nullptr)
	{
		throw bad_alloc();
	}
	cout << "operator new[]: " << ptr << endl;
	return ptr;
}
void operator delete[] (void* ptr)
{
	cout << "operator delete[]: " << ptr << endl;
	free(ptr);
}

class Test 
{
public:
	Test(int a = 0)
		:ma(a)
	{
		cout << "Test" << endl;
	}
	~Test()
	{
		cout << "~Test" << endl;
	}
private:
	int ma;
};

int main()
{
	//	new 普通类型也可以直接初始化
	int* m1 = new int[5]{ 0 };
	delete m1;

	cout << "==============================" << endl;

	//	new 自定义类型
	Test* m2 = new Test[5];
	//delete m2;	ERROR
	delete[] m2;

	return 0;
}
#endif