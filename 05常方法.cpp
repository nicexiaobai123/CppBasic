#include <iostream>
#include <vector>
using namespace std;

class CPerson {
public:
	CPerson(int a = 0, int w = 0)
		:_age(a), _weight(w)
	{

	}
	void show() {
		cout << "normal" << endl;
		cout << "age = " << _age << " weight = " << _weight << endl;
	}
	void show() const {
		cout << "const" << endl;
		cout << "age = " << _age << " weight = " << _weight << endl;
	}
private:
	int _age;
	int _weight;
};

#if 0
int main()
{
	CPerson lisi(14, 5);
	lisi.show();

	const CPerson lier(15, 10);
	lier.show();

	return 0;
}
#endif