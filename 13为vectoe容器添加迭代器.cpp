#include <iostream>
#include <vector>
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
	void construct(T* p, const T& val) {
		new (p) T(val);
	}
	//	只析构~T()代表T类型的析构函数
	void destroy(T* p) {
		p->~T();
	}
};

template<typename T, typename Alloc = Allocator<T>>
class Vector {
public:
	//	构造
	Vector(int size = 10) 
	{			
		_first = allocator.allocate(size);	//	不直接new对象了，而是只开辟空间
		_last = _first;
		_end = _first + size;
	}
	//	析构
	~Vector()
	{
		//delete[] _first;
		for (T* f = _first; f != _last; f++)
		{
			allocator.destroy(f);
		}
		allocator.deallocate(_first);		//	析构容器有效元素，然后释放_first指向的空间
		_first = _last = _end = nullptr;
	}
	//	拷贝构造
	Vector(const Vector<T>& rhs) 
	{
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
	Vector<T>& operator=(const Vector<T>& rhs) 
	{
		if (this == &rhs) {
			return *this;
		}

		// delete[] _first;
		for (T* f = _first; f != _last; f++) 
		{
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
	//	添加数
	void push_back(const T& val)
	{
		if (isFull()) {
			expand();
		}
		allocator.construct(_last, val);	//	_last指向的内存构造一个值为val的对象
		++_last;
	}
	//	弹出
	void pop_back()
	{
		if (isEmpty())
			return;
		allocator.destroy(--_last);			//	不仅要--_last，还得析构删除的元素
	}
	//	最后数
	T& back() const {
		if (isEmpty()) 
		{
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
	void expand() 
	{
		int size = _end - _first;
		T* ptem = allocator.allocate(size * 2);
		for (int i = 0; i < size; i++) 
		{
			allocator.construct(&ptem[i], _first[i]);
		}

		for (T* f = _first; f != _last; f++) 
		{
			allocator.destroy(f);
		}
		allocator.deallocate(_first);

		_first = ptem;
		_last = _first + size;
		_end = _first + 2 * size;
	}
public:
	//	迭代器
	class iterator 
	{
	public:
		iterator(T* p = nullptr) :_ptr(p) {}
		iterator& operator ++ ()
		{
			++_ptr;
			return *this;
		}
		bool operator != (const iterator& it) const
		{
			return _ptr != it._ptr;
		}
		T& operator * ()
		{
			return *_ptr;
		}
		const T& operator * () const
		{
			return *_ptr;
		}
	private:
		T* _ptr;
	};
	//	容器提供begin方法
	iterator begin() 
	{
		return iterator(_first);
	}
	//	容器提供end方法
	iterator end()
	{
		return iterator(_last);
	}

private:
	T* _first;	//	数组中起始元素位置
	T* _last;	//	数组中有效元素的后继
	T* _end;	//	数组空间的后继
	Alloc allocator;
};

#if 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Vector<int> ve1;
	for (int i = 0; i < 5; i++) 
	{
		ve1.push_back(rand() % 100 + 1);
	}

	Vector<int>::iterator it;
	it = ve1.begin();
	for (; it != ve1.end(); ++it) 
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}
#endif