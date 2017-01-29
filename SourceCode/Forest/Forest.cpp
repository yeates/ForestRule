// Forest.cpp : 定义控制台应用程序的入口点。
//

//备忘：地图的各类型二维数组，都是Y在前，X在后。

#include "stdafx.h"
#include "Manage.h"

Manage manage;

//鼠标左键单击生物时显示跟随生物移动的信息
void on_mouse(int event, int x, int y, int flags, void* ustc) {
	if (event == CV_EVENT_MOUSEMOVE) {
		manage.CheckHaveAnimal(x, y);
	}

}

int main()
{
	manage.m_ui.InitOneUi();	//UI界面
	manage.DataInit();	//数据初始化

	cvSetMouseCallback(manage.m_ui.m_forestName, on_mouse, 0);	//执行鼠标事件的回调函数
	
	//程序开始
	while (true) {
		manage.SaveJSONData();
		cvCopy(manage.m_Bg, manage.m_showBg);
		manage.DeadEffectiveUpdate();
		manage.LivingUpdate();
		if (manage.m_displayinfo_swi) manage.DisplayAnimalInfo(manage.m_infoX, manage.m_infoY);
		cvShowImage(manage.m_ui.m_forestName, manage.m_showBg);
		cvWaitKey(50);

		if(0 == manage.m_times % 20)
			manage.ProcessInfoUpdate();		//输出即时消息和保存即时消息文件
		manage.m_times++;
	}
	cvWaitKey(0);
    return 0;
}


/************************************************************************/
/* 
做之前需要解决的点：
1、保证头文件不被重复引用  
2、文件系统（将森林进程日志输出（按格式）到文本文件上）
3、所有的类和程序细节在草稿上过一次（顺便练习UML）
*/
/************************************************************************/