#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#if 0
int main()
{
	const int ARR_LEN = 10;
	int arr[ARR_LEN] = { 10,2,1,4,5,68,8,4,45,13 };
	//	vector构造函数一种，起始位置-结束位置
	vector<int> vec1(arr, arr + sizeof(arr) / sizeof(arr[0]));

	//	sort指定一个函数对象，从大到小
	std::sort(vec1.begin(), vec1.end(), greater<int>());
	for (int v : vec1) cout << v << " ";
	cout << endl;

	//	sort默认从小到大排序
	std::sort(vec1.begin(), vec1.end());
	for (int v : vec1) cout << v << " ";
	cout << endl;

	//	二分查找 可以指定是在从大到小的容器中查找的
	if (std::binary_search(vec1.begin(), vec1.end(), 45, greater<int>()))
	{
		cout << "存在45这个数" << endl;
	}

	//	find，返回的是一个迭代器
	//	auto it = find(vec1.begin(), vec1.end(), 68);
	vector<int>::iterator it1 = find(vec1.begin(), vec1.end(), 68);
	if (it1 != vec1.end()) cout << "存在68这个数" << endl;

	//	find_if 按条件查找
	//	把11插入到vector容器中，找到第一个比11要大的数
	auto it2 = find_if(vec1.begin(), vec1.end(), bind2nd(greater<int>(), 11));
	vec1.insert(it2, 11);
	for (int v : vec1) cout << v << " ";
	cout << endl;

	//	lambda表达式
	//	for_each可以遍历容器所有元素
	for_each(vec1.begin(), vec1.end(),
		[](int& val)->void
		{
			if (val % 2 == 0) cout << val << " ";
		});
	return 0;
}
#endif