#include <iostream>
using namespace std;

//Allocator	容器空间适配器
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
	//	只构造，使用定位new，调用的拷贝构造；
	void construct(T* p,const T& val) {
		new (p) T(val);
	}
	//	只析构~T()代表T类型的析构函数
	void destroy(T* p) {
		p->~T();		
	}
};

template<typename T,typename Alloc = Allocator<T>>
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
		//delete[] _first;
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
		/*_first = new T[size];
		for (int i = 0; i < len; i++)
		{
			_first[i] = rhs[i];
		}*/
		_first = allocator.allocate(size);	//	把申请空间和构造对象分开处理
		for (int i=0; i< len; i++)
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

		// delete[] _first;
		for (T* f = _first; f != _last; f++) {
			allocator.destroy(f);
		}
		allocator.deallocate(_first);

		int size = rhs._end - rhs._first;
		int len = rhs._last - rhs._first;
		/*_first = new T[size];
		for (int i = 0; i < len; i++)
		{
			_first[i] = rhs[i];
		}*/
		_first = allocator.allocate(size);
		for (int i = 0; i < len; i++)
		{
			allocator.construct(&_first[i], rhs[i]);
		}
		_last = _first + len;
		_last = _first + size;
	}
	//	添加数
	void push_back(const T& val) {
		if (isFull()) {
			expand();
		}
		//*_last++ = val;
		allocator.construct(_last, val);	//	_last指向的内存构造一个值为val的对象
		++_last;
	}
	//	弹出
	void pop_back() {
		if (isEmpty())
			return;
		//_last--;
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
		//T* ptem = new T[size * 2];
		T* ptem = allocator.allocate(size * 2);
		for (int i = 0; i < size; i++) {
			allocator.construct(&ptem[i], _first[i]);
		}

		//delete[] _first;
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


//	类
class Test {
public:
	Test() {
		cout << "Test" << endl;
	}
	~Test() {
		cout << "~Test" << endl;
	}
	Test(const Test& ) {
		cout << "Test(const Test& t)" << endl;
	}
};


#if 0
int main()
{
	Test t1,t2,t3;
	cout << "=====================" << endl;

	Vector<Test> vec1;	//	只申请内存，不调用构造函数
	vec1.push_back(t1);	//	在push时才调用构造函数
	vec1.push_back(t2);
	vec1.push_back(t3);

	cout << "=====================" << endl;
	vec1.pop_back();
	vec1.pop_back();	//	在pop时调用析构函数
	vec1.pop_back();
	cout << "=====================" << endl;
						//	结束的时候，析构剩余存放对象，释放Vector真实空间


	//	C++语法允许这样
	//using t = int;
	//t* p = new int;
	//p->~t();

	//	直接用语法错误
	//int* p = new int;
	//p->~int();	error

	return 0; 
}
#endif