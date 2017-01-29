/**
* @file Animals.h
* @brief 动物类，与植物类并列，继承于生物类(living)，也是一个抽象类，作为食肉动物类和植食动物类的基类
* @author 喻永生
*/

#pragma once
#ifndef __ANIMALS_H__
#define __ANIMALS_H__
#include "Living.h"
class Animals : public Living
{
public:
	Animals();
	~Animals();
	void Chase(IplImage *Bg);/*!< 捕食 */
	void Flee(IplImage *Bg);/*!< 逃跑 */
	int GetEnergy() { return m_hungry; }/*!< 获取能量值 */
	void SetTargetPos(int posx, int posy) {
		m_targetPos.x = posx;
		m_targetPos.y = posy;
	}
	int GetStaticViewRange() { return m_staticViewRange; }/*!< 获取静息状态视野 */
	int GetActiveViewRange() { return m_activeViewRange; }/*!< 获取活跃状态视野 */
	int GetStaticSpeed() { return m_staticSpeed; }/*!< 获取静息状态移动速度 */
	int GetActiveSpeed() { return m_activeSpeed; }/*!< 获取活跃状态移动速度 */
	void SetFindTarget(bool is) { m_isFindTarget = is; }/*!< 设置是否找到了目标对象 */
	void SetisActive(bool is) {
		m_isStatic = !is;
	}
	bool isStatic() { return m_isStatic; }/*!< 获取是否为静息状态 */
	bool isFindTarget() { return m_isFindTarget; }/*!< 获取是否找到了目标对象 */
	void ChangeEnergy(int energy) { m_hungry += energy; }/*!< 改变当前移动方向 */
	int GetDirection() { return m_moveDir; }/*!< 获取当前移动方向 */
	int GetImgID() { return m_imgId; }/*!< 获取当前图片序号 */
	int GetMoveDir() { return m_moveDir; }/*!< 获取当前移动方向 */
	int IsCollision() { return m_isCollision; }/*!< 判断是否碰撞 */
	int isMove() { return m_isMove; }/*!< 判断是否在移动 */
	int GetMoveDis() { return m_moveDis; }/*!< 获取已移动的像素值 */
	int GetMaxEatTime() { return m_maxEatTime; }/*!< 获取当天最多能吃的顿数 */
	int GetNowEatTime() { return m_nowEatTime; }/*!< 获取当天吃了的顿数 */
	void Eat() { m_nowEatTime++; }/*!< 捕食到了生物 */
	void InitEatTime() { m_nowEatTime = 0; }
	IplImage *GetImage() { return m_img[m_imgId]; }/*!< 获取生物图片 */
protected:
	IplImage *m_img[ANIMAL_MOVEIMG_COUNT];/**< 动物图片 */
	CvPoint m_targetPos;		/**< 目标的坐标点 */
	bool m_isFindTarget;		/**< 是否已经发现了目标 */
	int m_staticViewRange;		/**< 静默状态视野范围 */
	int m_activeViewRange;		/**< 活跃状态视野范围 */
	bool m_isStatic;			/**< 是否处于静默状态（和活跃状态对比，活跃状态就是生物追杀或者逃生的状态） */
	int m_staticSpeed;			/**< 静默状态的移动速度 */
	int m_activeSpeed;			/**< 活跃状态的移动速度 */
	int m_imgId;				/**< 图片显示ID */
	int m_hungry;				/**< 当前的饥饿程度，低于0时死亡 */
	int m_moveDir;				/**< 移动方向 */
	bool m_isMove;				/**< 是否正在移动 */
	int m_moveDis;				/**< 当前已经移动的距离 */
	bool m_isCollision;			/**< 是否发生碰撞 */
	int m_maxEatTime;			/**< 一天最高吃东西的次数 */
	int m_nowEatTime;			/**< 当前已经吃了多少次 */
};
#endif

