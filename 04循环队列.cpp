#include <iostream>
using namespace std;

class Queue {
public:
	Queue(int size = 5) {
		_pQue = new int[size];
		_front = _rear = 0;
		_size = size;
	}
	~Queue() {
		delete[] _pQue;
		_pQue = nullptr;
	}
	Queue(const Queue& que) {
		_front = que._front;
		_rear = que._rear;
		_size = que._size;
		_pQue = new int[_size];
		for (int i = _front; i != _rear; i = (i + 1) % _size) {
			_pQue[i] = que._pQue[i];
		}
	}
	Queue& operator=(const Queue& que) {
		//	自己赋值自己 q1 = q1
		if (this == &que) {
			return *this;
		}
		//	删除自身
		delete[] _pQue;
		//	复制
		_front = que._front;
		_rear = que._rear;
		_size = que._size;
		_pQue = new int[_size];
		for (int i = _front; i != _rear; i = (i + 1) % _size) {
			_pQue[i] = que._pQue[i];
		}
	}
public:
	void push(int val) {
		if (isFull()) {
			resize();
		}
		_pQue[_rear] = val;
		_rear = (_rear + 1) % _size;
	}
	void pop() {
		if (isEmpty())return;
		_front = (_front + 1) % _size;
	}
	int front() {
		return _pQue[_front];
	}
	bool isEmpty() {
		return _front == _rear;
	}
private:
	void resize() {
		int* ptemp = new int[_size * 2];
		int index = 0;
		for (int i = _front; i != _rear; i = (i + 1) % _size){
			ptemp[index++] = _pQue[i];
		}
		delete[] _pQue;
		_pQue = ptemp;

		_size = _size * 2;
		_front = 0;
		_rear = index;
	}
	bool isFull() {
		return  (_rear + 1) % _size == _front;
	}
private:
	int* _pQue;
	int _front;		// 队头位置
	int _rear;		// 队尾的位置，最后元素的下一个，空一格
	int _size;
};

#if 0
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Queue qu;
	for (int i = 0; i < 10; i++) {
		qu.push(rand() % 100);
	}
	qu.pop();
	
	while (!qu.isEmpty()) {
		cout << qu.front() << " ";
		qu.pop();
	}
	cout << endl;

	//	拷贝构造、拷贝赋值
	Queue q1(qu), q2;
	q2 = q1;
	
	return 0;
}
#endif