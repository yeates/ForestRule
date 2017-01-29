/**
* @file Living.h
* @brief 生物类，作为一个抽象类
* @author 喻永生
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
	virtual void Draw(IplImage *Bg) = 0;/*!< 绘制生物图片虚函数 */
	virtual void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int null) = 0;/*!< 修改地图信息虚函数 */
	void SetLiveType(bool is) { m_isClear = !is; }/*!< 设置生物存活状态 */
	bool IsNeedClear() { return m_isClear; }/*!< 是否需要清理 */
	void Old() { m_age++; }/*!< 生物成长 */
	bool isTooOld() { if (m_age >= m_life) return true; else  return false;	 }/*!< 判断是否到达年龄上限 */
	int GetHeat() { return m_heat; }/*!< 获取能量值 */
	int GetLife() { return m_life; }/*!< 获取寿命值 */
	int GetAge() { return m_age; }/*!< 获取年龄 */
	int GetPosX() { return m_movePos.x; }/*!< 获取生物当前X坐标 */
	int GetPosY() { return m_movePos.y; }/*!< 获取生物当前Y坐标 */
protected:
	int m_age;/**< 年龄 */
	int m_life;/**< 寿命 */
	CvPoint m_drawPos;/**< 绘图坐标 */
	CvPoint m_movePos;/**< 地图坐标 */
	bool m_isClear;/**< 是否该被清除 */
	int m_heat;					/**< 被吃后所能带来的热量 */
};
#endif
