/**
* @file DeadEffective.h
* @brief ���������Ч����
* @author ������
*/

#ifndef __DEADEFFECTIVE_H__
#define __DEADEFFECTIVE_H__

#include "Tools.h"
class DeadEffective
{
public:
	DeadEffective();
	~DeadEffective();
	DeadEffective(IplImage *img, int posx, int posy);/*!< ����Ч���๹�캯�� */
	void TimeGoOn();/*!< �ݽ���ʱ�� */
	bool CheckIsClear() { return m_isClear; }/*!< �ж��Ƿ�ñ����� */
	/*!< ��ͼ */
	void Draw(IplImage *Bg) {
		Tools::DrawToBack(m_drawPos.x, m_drawPos.y, Bg, m_harmlessDeadImg, 255, 255, 255);
	}
private:
	IplImage *m_harmlessDeadImg;/**< ����ͼƬ */
	const int m_imgLife = 25;/**< ͼƬ��ʾʱ�� */
	int m_nowTimes;/**< ��ǰ��ʱ */
	bool m_isClear;/**< �Ƿ�ñ����� */
	CvPoint m_drawPos;/**< ��ͼ���� */
};


#endif __DEADEFFECTIVE_H__