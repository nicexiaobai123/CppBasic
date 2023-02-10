#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;
#if 1
// 也可以叫观察者-监听者模型
// 监听者抽象类
class Listener {
public:
	virtual void handle(int msgId) = 0;
};
class Listener01 : public Listener {
public:
	void handle(int msgId) {
		if (msgId == 1) cout << "Listener01 recv 1 msg!" << endl;
		else if (msgId == 2) cout << "Listener01 recv 2 msg!" << endl;
		else cout << "Listener01 recv unknow msg!" << endl;
	}
};
class Listener02 : public Listener {
public:
	void handle(int msgId) {
		if (msgId == 2) cout << "Listener02 recv 2 msg!" << endl;
		else if (msgId == 3) cout << "Listener02 recv 3 msg!" << endl;
		else cout << "Listener02 recv unknow msg!" << endl;
	}
};
// 观察者类
class Observer {
public:
	void registerListener(weak_ptr<Listener> lter, int msgId) {
		// map中括号运算符，没有对应key会创建一个新的pair，且返回second的引用
		lterMap[msgId].push_back(lter);
	}
	void dispatchMessage(int msgId) {
		// 对消息感兴趣的"监听者"派送消息
		auto it = lterMap.find(msgId);
		if (it != lterMap.end()) {
			for_each(it->second.begin(), it->second.end(),
				[&msgId,this](weak_ptr<Listener> pLter)->void {
					shared_ptr<Listener>p = pLter.lock();
					// 监听者在多线程环境下先一步被销毁了，须在map删除
					if (p == nullptr) lterMap.erase(msgId);	
					else p->handle(msgId);
				} 
			);
		}
	}
private:
	// 消息id要发给哪些"监听者"
	unordered_map<int, list<weak_ptr<Listener>>> lterMap;
};

// 主函数
int main()
{
	cout << sizeof(int) << endl;
	shared_ptr<Listener>p1(new Listener01);
	shared_ptr<Listener>p2(new Listener02);
	Observer obser;
	obser.registerListener(p1, 0);	// 注册监听者不处理的消息
	obser.registerListener(p1, 1);
	obser.registerListener(p1, 2);
	obser.registerListener(p2, 2);
	obser.registerListener(p2, 3);
	// 注册了0，1，2，3号消息，其他接受不到
	int msgId;
	while (true) 
	{
		cout << "请输入消息ID:";
		cin >> msgId;
		if (msgId == -1)break;
		obser.dispatchMessage(msgId);
	}

	return 0;
}
#endif