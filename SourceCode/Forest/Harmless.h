/**
* @file Harmless.h
* @brief 植食动物类，继承于Animals类
* @author 喻永生
*/

#pragma once

#ifndef __HARMLESS_H__
#define __HARMLESS_H__

#include "Animals.h"
class Harmless : public Animals
{
public:
	Harmless();
	/*!< 植食动物构造函数：从存档构造/由程序重新生成 */
	Harmless(int age, int life, int heat, int posx, int posy, int staticview, int activeview, int isstatic, int ismove, int staticspeed, int activespeed, int imgid, int hungry, int movedir, int iscollision, int movedis, IplImage *img[ANIMAL_MOVEIMG_COUNT], int maxEatTime, int nowEatTime);
	Harmless(int posx, int posy, int staticViewRange, int activeViewRange, int staticSpeed, int activeSpeed, int hungry, int heat, int life, IplImage *img[]);
	~Harmless();
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int age, int heat, int hungry, int nowEatTime, bool isFindTarget, bool isFlee) {
		mapInfo[yi][xi] = HARMLESS;
		animalInfo[yi][xi].age = age;
		animalInfo[yi][xi].heat = heat;
		animalInfo[yi][xi].hungry = hungry;
		animalInfo[yi][xi].nowEatTime = nowEatTime;
		animalInfo[yi][xi].isFindTarget = isFindTarget;
		animalInfo[yi][xi].liveType = HARMLESS;
		animalInfo[yi][xi].isFlee = isFlee;
	}
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int null) {
		mapInfo[yi][xi] = GRASS;
		animalInfo[yi][xi].age = 0;
		animalInfo[yi][xi].heat = 0;
		animalInfo[yi][xi].hungry = 0;
		animalInfo[yi][xi].nowEatTime = 0;
		animalInfo[yi][xi].isFindTarget = false;
		animalInfo[yi][xi].liveType = GRASS;
		animalInfo[yi][xi].isFlee = false;
	}
	int GetDrawPosX() { return m_drawPos.x; }/*!< 获取植食生物当前X坐标 */
	int GetDrawPosY() { return m_drawPos.y; }/*!< 获取植食生物当前Y坐标 */
	void Draw(IplImage *Bg);/*!< 绘图 */
	void SetImage(IplImage *img[], int n = ANIMAL_MOVEIMG_COUNT);/*!< 设置植食动物图片 */
	bool IsFlee() { return m_isFlee; }/*!< 获取逃跑状态 */
	void SetIsFlee(bool is) { m_isFlee = is; }/*!< 设置逃跑状态 */
private:
	bool m_isFlee;/**< 逃跑状态 */
};
#endif