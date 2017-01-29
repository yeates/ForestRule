/**
* @file DeadEffective.h
* @brief 生物的死亡效果类
* @author 喻永生
*/

#ifndef __DEADEFFECTIVE_H__
#define __DEADEFFECTIVE_H__

#include "Tools.h"
class DeadEffective
{
public:
	DeadEffective();
	~DeadEffective();
	DeadEffective(IplImage *img, int posx, int posy);/*!< 死亡效果类构造函数 */
	void TimeGoOn();/*!< 递进计时器 */
	bool CheckIsClear() { return m_isClear; }/*!< 判断是否该被销毁 */
	/*!< 绘图 */
	void Draw(IplImage *Bg) {
		Tools::DrawToBack(m_drawPos.x, m_drawPos.y, Bg, m_harmlessDeadImg, 255, 255, 255);
	}
private:
	IplImage *m_harmlessDeadImg;/**< 死亡图片 */
	const int m_imgLife = 25;/**< 图片显示时间 */
	int m_nowTimes;/**< 当前计时 */
	bool m_isClear;/**< 是否该被销毁 */
	CvPoint m_drawPos;/**< 绘图坐标 */
};


#endif __DEADEFFECTIVE_H__