#include <iostream>
#include <memory>
using namespace std;
#if 0
//	自己实现的强智能指针，给每个对象资源匹配一个引用计数
//	自己实现的引用计数++、--本身并不是线程安全的；多线程下不可使用
//	库中的shared_ptr、weak_ptr引用计数增加、减少是线程安全的

//	计数器
template<typename T>
class CRefCount
{
public:
	CRefCount(T* ptr = nullptr)
		:mptr(ptr), mcount(1)
	{	}
	void addRef() { mcount++; }			//	增加资源引用计数
	int delRef() { return --mcount; }	//	减少资源引用计数
private:
	T* mptr;		//	指向外部资源的指针
	int mcount;		//	引用计数
};

//	强智能指针
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr)
		:mptr(ptr) {
		mRefCnt = new CRefCount<T>(ptr);
	}
	~CSmartPtr() 
	{ 
		if (mRefCnt->delRef() == 0)
		{
			delete mptr;
			delete mRefCnt;
		}
	}
	T& operator * () { return *mptr; }
	T* operator -> () { return mptr; }

	//	拷贝构造
	CSmartPtr(const CSmartPtr<T>& src)
		:mptr(src.mptr), mRefCnt(src.mRefCnt)
	{
		if (mptr != nullptr)
			mRefCnt->addRef();
	}
	//	拷贝赋值
	CSmartPtr<T>& operator = (const CSmartPtr<T>& src)
	{
		if (this == &src)
			return *this;
		if (mRefCnt->delRef() == 0)
		{
			delete mptr;
			delete mRefCnt;
		}
		mptr = src.mptr;
		mRefCnt = src.mRefCnt;
		if (mptr != nullptr)
			mRefCnt->addRef();
		return *this;
	}
private:
	T* mptr;
	CRefCount<T>* mRefCnt;
};

//	主函数
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CSmartPtr<int> p1(new int);
	*p1 = 40;

	CSmartPtr<int> p2(p1);
	CSmartPtr<int> p3;
	p3 = p2;

	cout << *p3 << endl;
	return 0;
}
#endif