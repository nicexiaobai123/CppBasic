#include <iostream>
using namespace std;
//	短时间频繁中使用push、pop操作，会有很多次new、delete；并不合适
//	重载new、delete来管理内存   -----  对象池
//	先申请一块足够大的内存，直接使用这个大内存; 减少malloc、free操作

//	队列，底层使用链表完成
template <typename T>
class Queue
{
public:
	Queue()
	{
		//	带空头节点
		_front = _rear = new QueueItem();
	}
	~Queue()
	{
		//	先归还内存，再释放内存池；容器析构会将所有申请的内存归还给池
		//	容器析构中释放池只是目前的方法，STL内置容器可不能帮我们释放池
		//	这方法还有缺点：一个池不够申请了两个池，释放的时候只能释放一个池
		QueueItem* cur = _front;
		while (cur != nullptr)
		{
			_front = _front->_next;
			delete cur;
			cur = _front;
		}
		//	释放池
		QueueItem::destory();
	}
	T& front() const { return  _front->_next->_data; }
	bool isEmpty() const { return _rear == _front; }
	//	入队，先进先出
	void push_back(const T& val)
	{
		QueueItem* ptr = new QueueItem(val);
		_rear->_next = ptr;
		_rear = ptr;
	}
	//	出队
	void pop_front() 
	{
		if (isEmpty()) return;
		QueueItem* n = _front->_next;
		_front->_next = n->_next;
		delete n;
		//	删除完后发现没有节点了
		if (_front->_next == nullptr)
		{
			_rear = _front;
		}
	}
private:
	struct QueueItem
	{
		//	默认构造，T()
		QueueItem(T data = T())
			:_data(data), _next(nullptr) {}
	public:
		//	申请内存
		static void* operator new (size_t size)
		{
			//	第一次就先申请一块足够大的内存，链起来作为“池”
			if (QueueItem::_itemPool == nullptr)
			{
				QueueItem::_itemPool = (QueueItem*)new char[QueueItem::POOL_ITEM_SIZE * sizeof(QueueItem)];
				QueueItem* ptr = _itemPool;
				//	最后一块的next赋值为nullptr
				for (; ptr < _itemPool + POOL_ITEM_SIZE - 1; ptr++)
				{
					ptr->_next = (ptr + 1);
				}
				ptr->_next = nullptr;
			}
			//	从池中分配
			QueueItem* p = _itemPool;
			_itemPool = _itemPool->_next;
			return p;
		}
		//	释放内存	
		static void operator delete (void* ptr)
		{
			//	直接将释放的内存加入池中就可以了,不用free
			QueueItem* cur = (QueueItem*)ptr;
			cur->_next = _itemPool;
			_itemPool = cur;
		}
		//	释放池
		static void destory()
		{
			if (_itemPool != nullptr)
			{
				free(_itemPool);
			}
		}
	public:
		T _data;
		QueueItem* _next;
		static QueueItem* _itemPool;
		//	静态常数成员变量可以直接类中初始化
		static const int POOL_ITEM_SIZE = 1000;	
	};
private:
	QueueItem* _front;	//	指向头结尾
	QueueItem* _rear;	//	指向队尾	
};
//	typename可以告诉编译器后面一定是一个类型
template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;

#if 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Queue<int> Que;
	for (int i = 0; i < 1000; i++)
	{
		Que.push_back(15);
	}
	for (int i = 0; i < 1000; i++)
	{
		Que.pop_front();
	}
	cout << Que.isEmpty() << endl;
	return 0;
}
#endif