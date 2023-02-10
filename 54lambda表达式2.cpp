#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <set>
#include <queue>
using namespace std;
#if 0
class Data
{
public:
	Data(int a = 10, int b = 10) :ma(a), mb(b) {  }
	// bool operator<(const Data& a) { return this->ma < a.ma; }
	int ma;
	int mb;
};
int main()
{
	// 有两种方法使用有序关联容器存对象：
	// 1、对象有些operator<重载函数  2、自己提供容器的比较函数对象，不使用默认的less
	using FUNC = function<bool(const Data&, const Data&)>;
	set<Data, FUNC> mySet( 
		[](const Data& a, const Data& b)->bool
		{
			return a.ma < b.ma;
		}
	);
	mySet.insert(Data(10, 20));
	mySet.insert(Data(11, 20));

	// 使用优先级队列
	priority_queue<Data, vector<Data>, FUNC> maxQue(
		[](const Data& a, const Data& b)->bool
		{
			return a.ma > b.ma;
		}
	);
	maxQue.push(Data(10, 10));
	maxQue.push(Data(20, 10));

	// map里面存储函数对象
	map<int, function<int(int, int)>> calcFunc;
	calcFunc[1] = [](int a, int b)->int { return a + b; };
	calcFunc[2] = [](int a, int b)->int { return a - b; };
	calcFunc[3] = [](int a, int b)->int { return a * b; };

	// 智能指针自定义删除器
	unique_ptr<FILE, function<void(FILE*)>> ptr(fopen("test.txt", "w"),
		[](FILE* fp)
		{
			fclose(fp);
		});
	return 0;
}
#endif