#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
#if 0
class Student
{
public:
	// 要让map(unordered同样如此)能够存储，需提供默认构造函数
	Student(int id = 0, const string& name = "")
		:_id(id), _name(name)
	{	}
	// 提供 operator < 函数，让容器内部知道如何排序
	bool operator < (const Student& stu) const 
	{
		return _id < stu._id;
	}
private:
	int _id;
	string _name;
	friend ostream& operator << (ostream& out, const Student& stu);
};
ostream& operator << (ostream& out, const Student& stu)
{
	return out << stu._id << ":" << stu._name;
}

int main()
{
	//	使用set存储对象
	set<Student> set1;
	set1.insert(Student(1020, "张三"));
	set1.insert(Student(1010, "李四"));
	set1.insert(Student(1040, "王五"));
	for (auto v : set1)
	{
		cout << v << endl;
	}

	//	使用map存储对象
	map<int, Student> map1;
	map1.insert({1020,Student(1020,"1111") });
	map1[1030] = Student(1030, "2222");
	return 0;
}
#endif