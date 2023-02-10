#include <iostream>
#include <vector>
using namespace std;

#if 0

//	=============== 函数指针使用 ================ 
template<typename T>
bool Less(T a, T b) { return a < b; }
template<typename T>
bool Greater(T a, T b) { return a > b; }

//	=============== 仿函数使用 ================ 
template<typename T>
struct myless {
	bool operator()(T a, T b) { return a < b; }
	// int _count  // 如果需要，可以记录更多的信息
};
template<typename T>
struct mygreater {
	bool operator()(T a, T b) { return a > b; }
};

//	=============== 库函数使用 ================ 
template<typename T, typename Compare>
bool compare(T a, T b,Compare comp)
{
	return comp(a, b);
}
// 主函数
int main()
{
	cout << compare(10, 20, Less<int>) << endl;			//指定小于函数，1
	cout << compare(10, 20, Greater<int>) << endl;		//指定大于函数，0
	cout << compare(10, 20, myless<int>()) << endl;		//指定小于函数，1
	cout << compare(10, 20, mygreater<int>()) << endl;	//指定小于函数，0
	return 0;
}
#endif