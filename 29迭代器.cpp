#include <iostream>
#include <vector>
using namespace std;

//	迭代器的继承结构
/*
class const_iterator
{
public:
	const T& operator*() { return *_ptr; }
};
class iterator : public const_iterator
{
public:
	T& operator*() { return *_ptr; }
};
*/

#if 0
int main()
{
	vector<int> vec1;
	for (int i = 0; i < 10; i++)
	{
		vec1.push_back(rand() % 100 + 1);
	}

	// 正向迭代器
	// vector<int>::const_iterator it1 = vec1.begin();
	vector<int>::iterator it1 = vec1.begin();
	while (it1 != vec1.end())
	{
		if (*it1 % 2 == 0) 
		{
			//const_iterator
			*it1 = 0;
		}
		cout << *it1 << " ";
		++it1;
	}
	cout << endl;

	// 反向迭代器
	// vector<int>::const_reverse_iterator rit2 = vec1.rbegin();
	vector<int>::reverse_iterator rit2 = vec1.rbegin();
	while (rit2 != vec1.rend())
	{
		cout << *rit2 << " ";
		++rit2;
	}
	cout << endl;

	return 0;
}
#endif
