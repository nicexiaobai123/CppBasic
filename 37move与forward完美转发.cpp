#include <iostream>
using namespace std;

#if 0
// 容器空间适配器
template<typename T>
struct Allocator {
	//	申请内存
	T* allocate(size_t size) {
		return (T*)malloc(sizeof(T) * size);
	}
	//	释放内存
	void deallocate(T* p) {
		free(p);
	}
	//	模板类的成员模板
	template<typename Ty>
	void construct(T* p, Ty&& val) {
		new (p) T(forward<Ty>(val));
	}
	////	只构造，使用定位new，调用的拷贝构造；
	//void construct(T* p, const T& val) {
	//	new (p) T(val);
	//}
	//
	////	move移动语义
	//void construct(T* p, T&& val) {
	//	new (p) T(std::move(val));
	//}
	//	只析构~T()代表T类型的析构函数
	void destroy(T* p) {
		p->~T();
	}
};

// Vector实现
template<typename T, typename Alloc = Allocator<T>>
class Vector {
public:
	//	构造
	Vector(int size = 10) {
		//_first = new T[size];				//	不直接new对象了，而是只开辟空间
		_first = allocator.allocate(size);
		_last = _first;
		_end = _first + size;
	}
	//	析构
	~Vector() {
		for (T* f = _first; f != _last; f++) {
			allocator.destroy(f);
		}
		allocator.deallocate(_first);		//	析构容器有效元素，然后释放_first指向的空间
		_first = _last = _end = nullptr;
	}
	//	拷贝构造
	Vector(const Vector<T>& rhs) {
		int size = rhs._end - rhs._first;
		int len = rhs._last - rhs._first;
		_first = allocator.allocate(size);	//	把申请空间和构造对象分开处理
		for (int i = 0; i < len; i++)
		{
			allocator.construct(&_first[i], rhs[i]);
		}
		_last = _first + len;
		_end = _first + size;

	}
	//	拷贝赋值
	Vector<T>& operator=(const Vector<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		for (T* f = _first; f != _last; f++) {
			allocator.destroy(f);
		}
		allocator.deallocate(_first);

		int size = rhs._end - rhs._first;
		int len = rhs._last - rhs._first;

		_first = allocator.allocate(size);
		for (int i = 0; i < len; i++)
		{
			allocator.construct(&_first[i], rhs[i]);
		}
		_last = _first + len;
		_last = _first + size;
	}
	//	添加数	声明
	template<typename Ty>
	void push_back(Ty&& val);

	//	弹出
	void pop_back() {
		if (isEmpty())
			return;
		allocator.destroy(--_last);			//	不仅要--_last，还得析构删除的元素
	}
	//	最后数
	T& back() const {
		if (isEmpty()) {
			throw "vector is empty";
		}
		return *(_last - 1);
	}
	//	为空
	bool isEmpty() const { return _first == _last; }
	//	为满
	bool isFull() const { return _last == _end; }
private:
	//	数组两倍增长
	void expand() {
		int size = _end - _first;
		T* ptem = allocator.allocate(size * 2);
		for (int i = 0; i < size; i++) {
			allocator.construct(&ptem[i], _first[i]);
		}

		for (T* f = _first; f != _last; f++) {
			allocator.destroy(f);
		}
		allocator.deallocate(_first);

		_first = ptem;
		_last = _first + size;
		_end = _first + 2 * size;
	}
private:
	T* _first;	//	数组中起始元素位置
	T* _last;	//	数组中有效元素的后继
	T* _end;	//	数组空间的后继
	Alloc allocator;
};

// MyString实现
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
		cout << "MyString(MyString&)" << endl;
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
		cout << "MyString(operator=&)" << endl;
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

// void Vector<T, Alloc>::push_back(T&& val)
// void Vector<T, Alloc>::push_back(const T& val)
// ---> template<typename Ty> 
//  使用类模板的成员模板时，编译器依旧根据提供的参数进行模板实参推断，就像函数模板一样
// 
//	引用折叠 &&+&&=&&; &&+&=&
//	成员模板类型推演 + 引用折叠
template<typename T, typename Alloc>
template<typename Ty>
void Vector<T, Alloc>::push_back(Ty&& val)
{
	if (isFull()) {
		expand();
	}
	//	forward会根据参数的定义 识别是左值还是右值
	allocator.construct(_last, std::forward<Ty>(val));
	++_last;
}
//	=======================
int main()
{
	MyString str1("11111");
	Vector<MyString> vec1;
	vec1.push_back(str1);				//	push左值
	vec1.push_back(MyString("22222"));	//	push右值
	return 0;
}
#endif