#include <iostream>
#include <vector>
using namespace std;
#if 0

int sum(int a, int b = 10);
int sum(int a = 20, int b);
int sum(int a, int b)
{
	return a + b;
}
int main()
{
	cout << sum() << endl;
	return 0;
}
#endif

