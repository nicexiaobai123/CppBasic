#include <iostream>
#include <string>
using namespace std;

#if 0
class String {
public:
	//	构造函数
	String(const char* p = nullptr) 
	{
		if (p != nullptr) 
		{
			int len = strlen(p) + 1;
			_pstr = new char[len];
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
		_pstr = new char[rhs.length() + 1];
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
		_pstr = new char[rhs.length() + 1];
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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	String str1;
	String str2 = "aaa";
	String str3 = "bbb";
	String str4 = str2 + str3;
	String str5 = str2 + "ccc";
	String str6 = "ddd" + str2;

	cout << "str6:" << str6 << endl;
	if (str5 < str6) {
		cout << "str5 < str6" << endl;
	}

	cout << "=======================" << endl;
	int len = str6.length();
	for (int i = 0; i < len; i++)
	{
		cout << str6[i] << " ";
	}
	cout << endl;

	cout << "=======================" << endl;
	char buf[1024]{ 0 };
	strcpy(buf, str6.c_str());
	cout << buf << endl;

	return 0;
}
#endif