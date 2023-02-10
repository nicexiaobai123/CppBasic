#include <iostream>
using namespace std;

class String {
public:
	//	构造函数
	String(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			int len = strlen(p) + 1;
			_pstr = new char[len] {0};
			strcpy(_pstr, p);
		}
		else
		{
			_pstr = new char[1];
			_pstr[0] = '\0';
		}
	}
	//	析构函数
	~String()
	{
		delete[] _pstr;
		_pstr = nullptr;
	}
	//	拷贝构造
	String(const String& rhs)
	{
		_pstr = new char[rhs.length() + 1]{ 0 };
		strcpy(_pstr, rhs.c_str());
	}
	//	拷贝赋值
	String& operator = (const String& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		delete[] _pstr;
		_pstr = new char[rhs.length() + 1]{ 0 };
		strcpy(_pstr, rhs.c_str());
		return *this;
	}
	//	[]运算符重载
	char& operator[](int i)
	{
		if (i<0 || i>strlen(_pstr)) {
			throw "OutOfRangeException";
		}
		return _pstr[i];
	}
	//	给常对象提供一个,防止修改的
	const char& operator[](int i) const
	{
		if (i<0 || i>strlen(_pstr)) {
			throw "OutOfRangeException";
		}
		return _pstr[i];
	}
	//	小于运算符重载
	bool operator < (const String& rhs) const
	{
		return strcmp(_pstr, rhs.c_str()) < 0;
	}
	const char* c_str() const
	{
		return _pstr;
	}
	size_t length() const
	{
		return strlen(_pstr);
	}
	//	用于迭代器
public:
	class iterator {
	public:
		//构造
		iterator(char* ptr = nullptr) :p(ptr) {}
		//后置++
		iterator operator ++ (int) {
			return iterator(p++);
		}
		//前置++
		iterator& operator ++ () {
			++p;
			return *this;
		}
		//*运算符重载
		char& operator * () {
			return *p;
		}
		//const版*运算符重载
		const char& operator * () const{
			return *p;
		}
		//!=运算符重载
		bool operator != (const iterator& it) const {
			return p != it.p;
		}
	private:
		char* p;
	};
	//	类提供begin函数，返回迭代器，指向容器开始
	iterator begin() const {
		return iterator(_pstr);
	}
	//	类提供end函数，返回迭代器，指向容器最后的后继
	iterator end() const {
		return iterator(_pstr + strlen(_pstr));
	}
private:
	char* _pstr;
	friend String operator + (const String& str1, const String& str2);
	friend ostream& operator << (ostream& out, const String& src);
};

//	全局重载
String operator + (const String& str1, const String& str2)
{
	//char* ptem = new char[str1.length() + str2.length() + 1]{ 0 };
	String ptem;
	delete[] ptem.c_str();
	ptem._pstr = new char[str1.length() + str2.length() + 1];
	strcpy(ptem._pstr, str1.c_str());
	strcat(ptem._pstr, str2.c_str());
	//String str = String(ptem);
	//delete[] ptem;
	return ptem;
}
ostream& operator << (ostream& out, const String& src)
{
	return out << src.c_str();
}

#if 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	String str1 = "Hello World";
	String::iterator it;
	for (it = str1.begin(); it != str1.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	//	C++11的foreach底层是通过迭代器实现
	//	此基于范围的“for”语句需要适合的 "begin" 函数
	cout << "=======================" << endl;
	for (char c : str1) {
		cout << c << " ";
	}
	cout << endl;

	return 0;
}
#endif