#include <iostream>
#include <string>
#include <memory>
using namespace std;
#if 0
// 适配器模式:可以让不兼容的接口一起工作
// 电脑  ---  需要接口投影到  ---  投影仪上   

// 接口类 VGA
class VGA {
public:
	virtual void play() = 0;
};
// 接口类 HDMI
class HDMI {
public:
	virtual void play() = 0;
};

// 投影仪类(接口是VGA接口)
class TV01 :public VGA {
public:
	void play() { cout << "通过 VGA 接口连接投影仪，进行视频播放" << endl; }
};
// 新的投影仪类(接口是HDMI接口)，需要使用新的投影仪
class TV02 :public HDMI {
public:
	void play() { cout << "通过 HDMI 接口连接投影仪，进行视频播放" << endl; }
};

// 电脑类(只能使用VGA接口)
class Computer {
public:
	// 由于电脑只支持VGA接口，使用方法的参数也只能是VGA接口的指针
	void playVideo(VGA* pVGA) { pVGA->play(); }
};
// 对象适配器
class VgaAdapter : public VGA {
public:
	VgaAdapter(HDMI* p) :pHdmi(p) { }
	void play() { pHdmi->play(); }
private:
	// 需要一个新接口(需要使用的),就成了 VGA -> HDMI
	HDMI* pHdmi;
};
// 主函数
int main()
{
	// VGA接口的电脑 与 VGA接口的投影，是能直接使用的
	Computer pc01;
	VGA* ptv01 = new TV01;
	pc01.playVideo(ptv01);

	// VGA接口的电脑 与 HDMI接口的投影
	// 不能直接使用HDMI接口的投影，接口不兼容，需要使用适配器
	Computer pc02;
	HDMI* ptv02 = new TV02;
	// pc02.playVideo(ptv02);
	VGA* pAdapter = new VgaAdapter(ptv02);
	pc02.playVideo(pAdapter);

	delete ptv01;
	delete ptv02;
	delete pAdapter;
	return 0;
}
#endif