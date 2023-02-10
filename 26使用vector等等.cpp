#include <iostream>
#include <vector>
using namespace std;

#if 0
int main()
{
	vector<int> ve1;
	ve1.reserve(10);	//	只给容器底层开辟指定大小的内存空间，并不会添加新的元素
	//ve1.resize(10);	//	不仅给容器底层开辟指定大小的内存空间，还会添加新的元素

	for (int i = 0; i < 10; i++)
	{
		ve1.push_back(rand() % 100 + 1);
	}

	//	遍历打印
	for (int i = 0; i<ve1.size(); i++)
	{
		//	中括号重载
		cout << ve1[i] << " ";
	}
	cout << endl;

	//	删除双数
	vector<int>::iterator t = ve1.begin();
	while (t != ve1.end())
	{
		if (*t % 2 == 0)
		{
			t = ve1.erase(t);
		}
		else
		{
			t++;
		}
	}

	//	遍历打印
	for (auto x : ve1)
	{
		//	中括号重载
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
#endif
