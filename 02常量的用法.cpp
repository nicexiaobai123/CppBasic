#include <iostream>
#include <vector>
using namespace std;


#if 0
int main()
{
	//volatile const int a = 20;	//	volatile修饰时就不会在编译时用常量的值进行替换
	const int a = 20;
	int b1 = 10;
	const int b2 = b1;	//	常变量

	int arr[a];			//	作为声明数组大小数字
	//int arr1[b2];

	int* p = (int*)&a;
	*p = 10;
	printf("%d  %d  %d\n", a, *p, *(&a));

	return 0;
}
#endif