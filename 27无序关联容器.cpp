#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
//	set
void usingset()
{
	unordered_set<int> myset1;
	for (int i = 0; i < 100; i++)
	{
		//	单重集合 不会出现重复元素
		myset1.insert(rand() % 20 + 1);
	}
	cout << myset1.size() << endl;		//	20
	cout << myset1.count(15) << endl;	//	1	

	cout << "-----------------------" << endl;
	unordered_multiset<int> myset2;
	for (int i = 0; i < 100; i++)
	{
		//	多重集合 能出现重复元素
		myset2.insert(rand() % 20 + 1);
	}
	cout << myset2.size() << endl;		//	100
	cout << myset2.count(15) << endl;	//	4

	//	遍历
	cout << "-----------------------" << endl;
	for (int v : myset1)
	{
		cout << v << " ";
	}
	cout << endl;

	//	删除
	cout << "-----------------------" << endl;
	auto it = myset1.begin();
	while (it !=  myset1.end())
	{
		if (*it % 2 == 0) 
		{
			it = myset1.erase(it);
		}
		else
		{
			++it;
		}
	}
}
//	map
void usingmap()
{
	unordered_map<int, string> mymap1;
	/* map的operator[]
	* 1、查询
	* 2、如果key不存在，它会插入一对数据[key,string()]
	* V& operator[](const K& key)
	* {
	*	   insert( { K,V() } );
	* }
	*/
	mymap1[1020] = "张三";			//	先插入{1020,string()}，返回引用，再修改
	mymap1[1030];					//	插入一个{1030,string()}
	mymap1[1020] = "张三修改";		//	返回值的引用，修改
	cout << mymap1.size() << endl;	//	2
	cout << mymap1[1020] << endl;	//	张三修改
}
//	海量数据查重复
void solution()
{
	const int ARR_LEN = 100;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; i++)
	{
		arr[i] = rand() % 100 + 1;
	}
	//	善用 operator[]
	//	如果没有创建默认的为0，然后++，为1；
	//	有则在原有基础上++
	unordered_map<int, int> map1;
	for (int v : arr)
	{
		map1[v]++;	
	}
	//看重复
	for (const pair<int,int>& p : map1)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << " value:" << p.second << endl;
		}
	}
}
#if 0
int main()
{
	//usingset();
	//usingmap();
	solution();
	return 0;
}
#endif