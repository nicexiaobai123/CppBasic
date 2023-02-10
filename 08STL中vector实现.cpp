#include <iostream>
using namespace std;

template<typename T>
class Vector {
public:
	//	构造
	Vector(int size = 10) {
		_first = new T[size];
		_last = _first;
		_end = _first + size;
	}
	//	析构
	~Vector() {
		delete[] _first;
		_first = _last = _end = nullptr;
	}
	//	拷贝构造
	Vector(const Vector<T>& rhs) {
		int size = rhs._end - rhs._first;
		int len = rhs._last - rhs._first;
		_first = new T[size];
		for (int i = 0; i < len; i++)
		{
			_first[i] = rhs[i];
		}
		_last = _first + len;
		_last = _first + size;
	}
	//	拷贝赋值
	Vector<T>& operator=(const Vector<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _first;

		int size = rhs._end - rhs._first;
		int len = rhs._last - rhs._first;
		_first = new T[size];
		for (int i = 0; i < len; i++)
		{
			_first[i] = rhs[i];
		}
		_last = _first + len;
		_last = _first + size;
	}
	//	添加数
	void push_back(const T& val) {
		if (isFull()) {
			expand();
		}
		*_last++ = val;
	}
	//	弹出
	void pop_back() {
		if (isEmpty())
			return;
		_last--;
	}
	//	最后数
	T& back() const{
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
		T* ptem = new T[size * 2];
		for (int i = 0; i < size; i++) {
			ptem[i] = _first[i];
		}
		delete[] _first;
		_first = ptem;
		_last = _first + size;
		_end = _first + 2 * size;
	}
private:
	T* _first;	//	数组中起始元素位置
	T* _last;	//	数组中有效元素的后继
	T* _end;	//	数组空间的后继
};

#if 0
int main()
{
	Vector<int> vec1;
	for (size_t i = 0; i < 15; i++)
	{
		vec1.push_back(rand() % 100);
	}

	vec1.pop_back();
	while (!vec1.isEmpty())
	{
		cout << vec1.back() << " ";
		vec1.pop_back();
	}
	cout << endl;

	//	看异常写对了没..
	try
	{
		vec1.back(); 
	}
	catch (...)
	{
		cout << "异常" << endl;
	}
	system("pause");
	return 0;
}
#endif