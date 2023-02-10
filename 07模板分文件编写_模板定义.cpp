#include <iostream>
using namespace std;
template<typename T>
bool compare(T a, T b) {
	cout << "template func" << endl;
	return a > b;
}
template<>
bool compare <const char*> (const char* a, const char* b) {
	cout << "template<> func" << endl;
	return strcmp(a, b) > 0;
}
bool compare(int a, int b) {
	cout << "normal func" << endl;
	return a > b;
}
//	告诉编译器指定类型实例化
template bool compare<char>(char, char);
template bool compare<double>(double, double);