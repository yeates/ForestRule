/**
* @file Living.h
* @brief �����࣬��Ϊһ��������
* @author ������
*/

#pragma once

#ifndef __LIVING_H__	
#define __LIVING_H__
#include "stdafx.h"
#include "Map.h"

class Living
{
public:
	Living();
	virtual ~Living();
	virtual void Draw(IplImage *Bg) = 0;/*!< ��������ͼƬ�麯�� */
	virtual void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int null) = 0;/*!< �޸ĵ�ͼ��Ϣ�麯�� */
	void SetLiveType(bool is) { m_isClear = !is; }/*!< ����������״̬ */
	bool IsNeedClear() { return m_isClear; }/*!< �Ƿ���Ҫ���� */
	void Old() { m_age++; }/*!< ����ɳ� */
	bool isTooOld() { if (m_age >= m_life) return true; else  return false;	 }/*!< �ж��Ƿ񵽴��������� */
	int GetHeat() { return m_heat; }/*!< ��ȡ����ֵ */
	int GetLife() { return m_life; }/*!< ��ȡ����ֵ */
	int GetAge() { return m_age; }/*!< ��ȡ���� */
	int GetPosX() { return m_movePos.x; }/*!< ��ȡ���ﵱǰX���� */
	int GetPosY() { return m_movePos.y; }/*!< ��ȡ���ﵱǰY���� */
protected:
	int m_age;/**< ���� */
	int m_life;/**< ���� */
	CvPoint m_drawPos;/**< ��ͼ���� */
	CvPoint m_movePos;/**< ��ͼ���� */
	bool m_isClear;/**< �Ƿ�ñ���� */
	int m_heat;					/**< ���Ժ����ܴ��������� */
};
#endif
