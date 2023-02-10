#include <iostream>
using namespace std;
#if 0
class MyString
{
public:
	MyString(const char* p = nullptr)
	{
		cout << "MyString(char*)" << endl;
		if (p != nullptr)
		{
			_ptr = new char[strlen(p) + 1]{ 0 };
			strcpy(_ptr, p);
		}
		else
		{
			_ptr = new char[1];
			*_ptr = '\0';
		}
	}
	~MyString()
	{
		cout << "~MyString()" << endl;
		delete[] _ptr;
		_ptr = nullptr;
	}
	MyString(const MyString& str)
	{
		cout << "MyString(MyString)" << endl;
		_ptr = new char[strlen(str._ptr) + 1]{ 0 };
		strcpy(_ptr, str._ptr);
	}
	MyString(MyString&& str)
	{
		cout << "MyString(MyString&&)" << endl;
		_ptr = str._ptr;
		str._ptr = nullptr;
	}
	MyString& operator= (const MyString& str)
	{
		cout << "MyString(operator=)" << endl;
		if (this == &str) return *this;
		delete[] _ptr;
		_ptr = new char[strlen(str._ptr) + 1]{ 0 };
		strcpy(_ptr, str._ptr);
		return *this;
	}
	MyString& operator= (MyString&& str)
	{
		cout << "MyString(operator=&&)" << endl;
		if (this == &str) return *this;
		delete[] _ptr;
		_ptr = str._ptr;
		str._ptr = nullptr;
		return *this;
	}
	char* c_str()const { return _ptr; }
private:
	char* _ptr;
};

//	待优化函数
//	假如这个函数不能被优化了，如何修改MyString类，让其效率高些?
MyString GetObject(MyString& t)
{
	char* ptr = t.c_str();
	MyString tmpStr(ptr);
	return tmpStr;
}
int main()
{
	MyString str1 = "123456789";
	MyString str2;
	str2 = GetObject(str1);
	cout << str2.c_str() << endl;
	/*
	* 优化class之后：没有更多的申请内存、释放内存的操作
	MyString(char*)
	MyString(char*)
	MyString(char*)
	MyString(MyString&&)	----> tmpStr浅拷贝给main函数栈帧上的临时对象
	~MyString()
	MyString(operator=&&)	----> main函数栈帧上的临时对象给str2赋值，只赋值指针
	~MyString()
	~MyString()
	~MyString()
	*/

	/*
	* 没有优化class之前：
	MyString(char*)
	MyString(char*)
	MyString(char*)
	MyString(MyString)	 ----> tmpStr拷贝构造main函数栈帧上的临时对象
	~MyString()
	MyString(operator=)	 ----> main函数栈帧上的临时对象给str2赋值
	~MyString()
	~MyString()
	~MyString()
	*/
	return 0;
}
#endif