#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;

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

											//	析构记录迭代器的链表
		Iterator_Base* pre = &this->_head;
		Iterator_Base* it = this->_head._next;
		while (it != nullptr)
		{
			it->_cur->_pVec = nullptr;
			pre->_next = it->_next;
			delete it;
			it = pre->_next;
		}
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
		verify(_last, _last);				//	最后元素的迭代器失效
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
		verify(_first, _end);				//	全部范围迭代器都失效

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
		friend class Vector<T, Alloc>;
		iterator(Vector<T, Alloc>* _pvec = nullptr, T* p = nullptr)
			:_ptr(p), _pVec(_pvec)
		{
			Iterator_Base* itb = new Iterator_Base(this, _pVec->_head._next);
			_pVec->_head._next = itb;
		}
		iterator& operator ++ ()
		{
			if (_pVec == nullptr)
			{
				//	迭代器失效的就抛异常
				_STL_REPORT_ERROR("iterator invalid");
				//throw "iterator invalid";
			}
			++_ptr;
			return *this;
		}
		bool operator != (const iterator& it) const
		{
			//	检查 迭代器合法性 和 同一容器
			if (_pVec == nullptr || _pVec != it._pVec)
			{
				_STL_REPORT_ERROR("iterator incompatabke");
				//throw "iterator incompatabke";
			}
			return _ptr != it._ptr;
		}
		T& operator * ()
		{
			if (_pVec == nullptr)
			{
				_STL_REPORT_ERROR("iterator invalid");
				//throw "iterator invalid";
			}
			return *_ptr;
		}
		const T& operator * () const
		{
			if (_pVec == nullptr)
			{
				_STL_REPORT_ERROR("iterator invalid");
				//throw "iterator invalid";
			}
			return *_ptr;
		}
	private:
		T* _ptr;
		//	当前迭代器是哪个容器对象
		Vector<T, Alloc>* _pVec;
	};

	//	每次由begin或者end返回的迭代器都由一个链表记录
	//	容器提供begin方法
	iterator begin()
	{
		return iterator(this,_first);
	}
	//	容器提供end方法
	iterator end()
	{
		return iterator(this,_last);
	}
	//	插入
	iterator insert(iterator& it, const T& val)
	{
		if (isFull())
		{
			expand();
		}
		verify(it._ptr, _last);
		T* temp = _last;
		while (temp > it._ptr)
		{
			//	还是需要使用空间配置器来构造和析构
			allocator.construct(temp, *(temp - 1));
			allocator.destroy(temp - 1);
			//*temp = *(temp - 1);
			 temp--;
		}
		allocator.construct(it._ptr, val);
		*it._ptr = val;
		++_last;
		return iterator(this, it._ptr);
	}
	//	删除
	iterator erase(iterator& it)
	{
		verify(it._ptr, _last);
		T* temp = it._ptr;
		while (temp < _last - 1)
		{
			allocator.destroy(temp);
			allocator.construct(temp, *(temp + 1));
			//*temp = *(temp + 1);
			temp++;
		}
		allocator.destroy(temp);
		--_last;
		return iterator(this, it._ptr);
	}

private:
	//	只要链表中有迭代器属于first - last之间，都失效
	void verify(T* first,T* last)
	{
		Iterator_Base* pre = &this->_head;
		Iterator_Base* it = this->_head._next;
		while (it != nullptr)
		{
			if (it->_cur->_ptr >= first && it->_cur->_ptr <= last)
			{
				//	让迭代器失效，就是把指向当前容器的指针置空
				it->_cur->_pVec = nullptr;
				//	继续判断后续节点是否失效
				pre->_next = it->_next;
				delete it;
				it = pre->_next;
			}
			else 
			{
				pre = it;
				it = it->_next;
			}
		}
	}
	//	容器迭代器失效增加代码
	struct Iterator_Base
	{
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			:_cur(c), _next(n) {}
		iterator* _cur;
		Iterator_Base* _next;
	};
	Iterator_Base _head;	//	链表头
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

	Vector<int> vec1;
	for (int i = 0; i < 15; i++) {
		vec1.push_back(rand() % 50 + i);
	}

	//	打印
	Vector<int>::iterator it = vec1.begin();
	for (; it != vec1.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	//	使用pop_back导致最后一个迭代器失效
	cout << "=======================";
	Vector<int>::iterator it1 = vec1.end();
	vec1.pop_back();	//	最后一个迭代器失效
	//++it1;

	//	删除，将容器中所有的偶数都删除
	cout << "=======================" << endl;
	Vector<int>::iterator it2 = vec1.begin();
	while (it2 != vec1.end()) 
	{
		if (*it2 % 2 == 0) 
		{
			//	第一次调用erase时，迭代器it就失效了
			//	需要更新it
			it2 = vec1.erase(it2);
		}
		else 
		{
			++it2;
		}
	}
	for (int x : vec1)
	{
		cout << x << " ";
	}
	cout << endl;

	//	插入，在容器中所有奇数前面添加一个+1的数字
	cout << "=======================" << endl;
	auto it3 = vec1.begin();
	for (; it3 != vec1.end(); ++it3)
	{
		if (*it3 % 2 != 0)
		{
			//	在调用insert之后，迭代器就失效了
			//	需要更新，同时确保代码逻辑正确
			it3 = vec1.insert(it3, *it3 + 1);
			++it3;
		}
	}
	for (int x : vec1)
	{
		cout << x << " ";
	}
	cout << endl;

	//	插入，string类型测试
	cout << "=======================" << endl;
	Vector<string> vec2;
	for (int i = 0; i < 5; i++)
	{
		vec2.push_back("123456");
	}
	auto it4 = vec2.begin();
	for (; it4 != vec2.end(); ++it4)
	{
		if (it4 != vec2.end())
		{
			//	在调用insert之后，迭代器就失效了
			//	需要更新，同时确保代码逻辑正确
			it4 = vec2.insert(it4, "456789");
			++it4;
		}
	}
	for (string x : vec2)
	{
		cout << x << endl;
	}
	return 0;
}
#endif