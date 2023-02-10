#include <iostream>
#include <vector>
using namespace std;

#if 0
int main()
{
	vector<int> vec1;
	for (int i = 0; i < 10; i++) {
		vec1.push_back(rand() % 50 + 1);
	}
	for (int x : vec1) {
		cout << x << " ";
	}
	cout << endl;

	//	删除，将容器中所有的偶数都删除
	cout << "=======================" << endl;
	vector<int>::iterator it1 = vec1.begin();
	while (it1 != vec1.end()) {
		if (*it1 % 2 == 0) {
			//	第一次调用erase时，迭代器it就失效了
			//	需要更新it
			it1 = vec1.erase(it1);
		}
		else {
			it1++;
		}
	}
	for (int x : vec1) {
		cout << x << " ";
	}
	cout << endl;

	//	插入，在容器中所有奇数前面添加一个+1的数字
	cout << "=======================" << endl;
	auto it2 = vec1.begin();
	for (; it2 != vec1.end(); ++it2) {
		if (*it2 % 2 != 0) {
			//	在调用insert之后，迭代器就失效了
			//	需要更新，同时确保代码逻辑正确
			it2 = vec1.insert(it2, *it2 + 1);
			it2++;
		}
	}
	for (int x : vec1) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
#endif