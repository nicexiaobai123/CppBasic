#include <iostream>
using namespace std;

//	 顺序栈
class SeqStack {
public:
	//	构造
	SeqStack(int size = 5) {
		_pdata = new int[size];
		_top = -1;
		_size = size;
	}
	//	析构
	~SeqStack() {
		if (_pdata != nullptr) {
			delete[] _pdata;
			_pdata = nullptr;
		}
	}
	void push(int x) {
		if (isFull()) {
			resize();
		}
		_pdata[++_top] = x;
	}
	void pop() {
		--_top;
	}
	int top() {
		return _pdata[_top];
	}
	bool isEmpty() {
		return _top == -1;
	}
private:
	bool isFull() {
		return _top == _size - 1;
	}
	void resize() {
		int* ptemp = new int[_size * 2];
		for (int i = 0; i < _size; i++) {
			ptemp[i] = _pdata[i];
		}
		delete[] _pdata;
		_pdata = ptemp;
		_size = _size * 2;
	}
private:
	int* _pdata;
	int _top;
	int _size;
};

#if 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	new 先申请内存malloc，再调用构造
	SeqStack* seq1 = new SeqStack(5);

	srand(time(NULL));
	for (int i = 0; i < 15; i++) {
		seq1->push(rand() % 100);
	}

	while (!seq1->isEmpty())
	{
		cout << seq1->top() << " ";
		seq1->pop();
	}
	cout << endl;

	//	delete 先调用析构，再释放内存free
	delete seq1;
	return 0;
}
#endif