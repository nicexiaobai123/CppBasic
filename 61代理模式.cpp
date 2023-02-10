#include <iostream>
#include <string>
#include <memory>
using namespace std;
#if 0
// #1 抽象类
class VideoSite
{
public:
	virtual void freeMoive() = 0;
	virtual void vipMoive() = 0;
	virtual void ticketMoive() = 0;
};
// #2 委托类  真正做实际功能的类
class AQYVideoSite :public VideoSite
{
public:
	void freeMoive() { cout << "正在观看免费电影！" << endl; }
	void vipMoive() { cout << "正在观看VIP电影！" << endl; }
	void ticketMoive() { cout << "正在用券观看电影！" << endl; }
};
// #3 代理类  普通用户权限
class FreeVideoSiteProxy : public VideoSite
{
public:
	FreeVideoSiteProxy() :pVideo(new AQYVideoSite) { }
	~FreeVideoSiteProxy() { delete  pVideo; }
	// 控制访问权限，直接委托 或者 另外处理
	void freeMoive() { pVideo->freeMoive(); }
	void vipMoive() { cout << "目前是普通用户，不能观看vip电影！" << endl; }
	void ticketMoive() { cout << "目前无票，不观看用券电影！" << endl; }
private:
	// #4 有委托关系(指针)或者组合关系(对象)
	VideoSite* pVideo;
	//AQYVideoSite video;
};
// 代理类  VIP用户权限
class VipVideoSiteProxy : public VideoSite
{
public:
	VipVideoSiteProxy() :pVideo(new AQYVideoSite) { }
	~VipVideoSiteProxy() { delete  pVideo; }
	// 控制访问权限，直接委托 或者 另外处理
	void freeMoive() { pVideo->freeMoive(); }
	void vipMoive() { pVideo->vipMoive(); }
	void ticketMoive() { cout << "目前无票，不观看用券电影！" << endl; }
private:
	VideoSite* pVideo;
};
// 主函数
int main()
{
	// 如果不使用代理类(助理)，直接使用委托类(老板)
	// 就满足不了vip用户 和 普通用户的区别了
	unique_ptr<VideoSite> p1(new AQYVideoSite);
	p1->freeMoive();
	p1->vipMoive();
	p1->ticketMoive();

	// #5 客户直接使用代理对象，控制访问权限
	cout << "--------------------------" << endl;
	unique_ptr<VideoSite> p2(new FreeVideoSiteProxy);
	p2->freeMoive();
	p2->vipMoive();
	p2->ticketMoive();

	// 使用vip权限代理类
	cout << "--------------------------" << endl;
	unique_ptr<VideoSite> p3(new VipVideoSiteProxy);
	p3->freeMoive();
	p3->vipMoive();
	p3->ticketMoive();

	return 0;
}
#endif