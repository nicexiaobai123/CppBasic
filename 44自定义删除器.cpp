#include <iostream>
#include <memory>
#include <functional>
using namespace std;
#if 0
class MyDeleter
{
public:
	void operator()(void* p)
	{
		cout << "完美删除:" << p << endl;
		delete[] p;
	}
};
// 主函数
int main()
{
	// 仿函数的形式
	unique_ptr<int, MyDeleter> p1(new int[5]);

	// shared_ptr不用提供类型，只用提供删除器
	shared_ptr<int> p2(new int[5], MyDeleter());
	*p2 = 10;
	shared_ptr<int> p3(p2);
	cout << *p3 << endl;

	cout << "----------------------------" << endl;

	// 推荐使用function + lambda表达式
	unique_ptr<FILE, function<void(FILE*)>> p4(fopen("data.txt", "w"),
		[](FILE* fp)->void{
			cout << "关闭文件:" << fp << endl;
			fclose(fp);
		});

	// shared_ptr不用提供类型，只用提供删除器
	shared_ptr<FILE> p5(fopen("data.txt", "w"), 
		[](FILE* fp)->void {
			cout << "关闭文件:" << fp << endl;
			fclose(fp);
		});
	return 0;
}
#endif