// Forest.cpp : �������̨Ӧ�ó������ڵ㡣
//

//��������ͼ�ĸ����Ͷ�ά���飬����Y��ǰ��X�ں�

#include "stdafx.h"
#include "Manage.h"

Manage manage;

//��������������ʱ��ʾ���������ƶ�����Ϣ
void on_mouse(int event, int x, int y, int flags, void* ustc) {
	if (event == CV_EVENT_MOUSEMOVE) {
		manage.CheckHaveAnimal(x, y);
	}

}

int main()
{
	manage.m_ui.InitOneUi();	//UI����
	manage.DataInit();	//���ݳ�ʼ��

	cvSetMouseCallback(manage.m_ui.m_forestName, on_mouse, 0);	//ִ������¼��Ļص�����
	
	//����ʼ
	while (true) {
		manage.SaveJSONData();
		cvCopy(manage.m_Bg, manage.m_showBg);
		manage.DeadEffectiveUpdate();
		manage.LivingUpdate();
		if (manage.m_displayinfo_swi) manage.DisplayAnimalInfo(manage.m_infoX, manage.m_infoY);
		cvShowImage(manage.m_ui.m_forestName, manage.m_showBg);
		cvWaitKey(50);

		if(0 == manage.m_times % 20)
			manage.ProcessInfoUpdate();		//�����ʱ��Ϣ�ͱ��漴ʱ��Ϣ�ļ�
		manage.m_times++;
	}
	cvWaitKey(0);
    return 0;
}


/************************************************************************/
/* 
��֮ǰ��Ҫ����ĵ㣺
1����֤ͷ�ļ������ظ�����  
2���ļ�ϵͳ����ɭ�ֽ�����־���������ʽ�����ı��ļ��ϣ�
3�����е���ͳ���ϸ���ڲݸ��Ϲ�һ�Σ�˳����ϰUML��
*/
/************************************************************************/