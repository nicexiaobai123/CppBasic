#include <iostream>
#include <ctime>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
#if 0
//	类模板+函数模板；函数模板自动类型推导做封装
//	自己实现bind1st
template<typename Comp,typename T>
class _MyBind1st
{
public:
	_MyBind1st(const Comp& c, const T& v)
		: _comp(c), _val(v)
	{	}
	bool operator ()(const T& _sec)
	{
		return _comp(_val, _sec);
	}
private:
	Comp _comp;
	T	_val;
};
template<typename Comp,typename T>
_MyBind1st<Comp, T> MyBind1st(const Comp& comp, const T& val)
{
	// 使用函数模板，好处是可以自动做类型推演；在使用的时候就不用指定类型
	// 返回一个对象（函数对象）
	return _MyBind1st<Comp, T>(comp, val);
}

//	自己实现bind2nd
template<typename Comp, typename T>
class _MyBind2nd
{
public:
	_MyBind2nd(const Comp& c, const T& v) : _comp(c), _val(v) { }
	bool operator ()(const T& v) { return _comp(v, _val); }
private:
	Comp _comp;
	T	_val;
};
template<typename Comp,typename T>
_MyBind2nd<Comp, T> MyBind2nd(const Comp& comp, const T& val)
{
	return _MyBind2nd<Comp, T>(comp, val);
}

//	自己实现的find_if
template<typename Iter,typename Comp>
Iter my_find_if(Iter _begin, Iter _last,Comp _comp)
{
	for (; _begin != _last; ++_begin)
	{
		if (_comp(*_begin)) {
			return _begin;
		}
	}
	return _last;
}

//	打印容器内容
template<typename Container>
void ShowCont(Container cnt)
{
	typename Container::iterator it = cnt.begin();
	for (; it != cnt.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> vec1;
	srand(time(nullptr));
	for (int i = 0; i < 20; i++)
	{
		vec1.push_back(rand() % 100 + 1);
	}

	// 提供函数对象，从大到小
	std::sort(vec1.begin(), vec1.end(), greater<int>());
	ShowCont(vec1);

	// 使用自己实现的find_if和绑定器
	auto it1 = my_find_if(vec1.begin(), vec1.end(),
		MyBind2nd(less<int>(), 70)
	);

	if (it1 != vec1.end()) {
		vec1.insert(it1, 70);
	}
	ShowCont(vec1);

	return 0;
}
#endif
