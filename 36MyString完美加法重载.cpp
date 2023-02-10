#include <iostream>
#include <vector>
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
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
};

//	加法运算符
MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString tmp;
	delete[] tmp._ptr;
	tmp._ptr = new char[strlen(lhs._ptr) + strlen(rhs._ptr) + 1];
	strcpy(tmp._ptr, lhs._ptr);
	strcat(tmp._ptr, rhs._ptr);
	return tmp;

	//char* str = new char[strlen(lhs._ptr) + strlen(rhs._ptr) + 1];
	//strcpy(str, lhs._ptr);
	//strcat(str, rhs._ptr);
	//MyString tmp(str);
	//delete[] str;			// 有过多的开辟内存，释放内存，拷贝内存
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MyString str1 = "hello ";
	MyString str2 = "world!";
	MyString str3 = str1 + str2;

	cout << "------------------" << endl;
	cout << str3.c_str() << endl;
	cout << "------------------" << endl;

	// MyString(char*)
	// MyString(char*)
	// MyString(char*)		-----> 局部对象构造
	// MyString(MyString&&)	-----> 返回的是局部对象，临时对象优先按带右值引用的拷贝构造接受
	// ~MyString()			-----> 析构局部对象，这时为nullptr
	// ------------------
	// hello world!
	// ------------------
	// ~MyString()
	// ~MyString()
	// ~MyString()

	vector<MyString> vec1;
	vec1.push_back(MyString("11111"));
	cout << "------------------" << endl;

	// MyString(char*)			----> 临时对象构造函数
	// MyString(MyString&&)		----> 带右值引用参数的拷贝构造
	// ~MyString()				----> 临时对象析构，这时指针为nullptr，不做任何操作
	// ~MyString()
	return 0;
}
#endif