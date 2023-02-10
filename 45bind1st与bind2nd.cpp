#include <iostream>
#include <ctime>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
#if 0
//	==== bind1st和bind2nd在C++17后就删除了 ====

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
	ShowCont(vec1);

	// 默认从小到大
	std::sort(vec1.begin(), vec1.end());
	ShowCont(vec1);

	// 提供函数对象，从大到小
	std::sort(vec1.begin(), vec1.end(),greater<int>());
	ShowCont(vec1);

	// 绑定器 + 二元函数对象(因为stl只提供了二元函数对象) = 一元函数对象
	// 把70插入到容器中，找到第一个小于70的数字
	// less  a < b
	// greater a > b
	// 绑定器就是绑定二元函数对象的一个形参
	auto it1 = find_if(vec1.begin(), vec1.end(),
		//bind2nd(less<int>(), 70)
		bind1st(greater<int>(),70)
	);
	if (it1 != vec1.end()) {
		vec1.insert(it1, 70);
	}
	ShowCont(vec1);

	return 0;
}
#endif
