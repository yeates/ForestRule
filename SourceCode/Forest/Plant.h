/**
* @file Plant.h
* @brief 植物类
* @author 喻永生
*/

#pragma once
#ifndef __PLANT_H__
#define __PLANT_H__
#include "Living.h"
class Plant : public Living
{
public:
	Plant();
	Plant(int age, int life, int heat, int posx, int posy, IplImage *img[], int imgIndex);/*!< 植物类的构造函数：从存档构造 */
	Plant(int posx, int posy, int heat, int life, IplImage *img[], int imgIndex);/*!< 植物类的构造函数:由程序重新生成 */
	~Plant();
	/*!< 将地图信息设置为植物，并写入当前植物状态 */
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int age, int heat) {
		mapInfo[yi][xi] = PLANT;			
		animalInfo[yi][xi].liveType = PLANT;
		animalInfo[yi][xi].age = age;
		animalInfo[yi][xi].heat = heat;
	}
	/*!< 将地图信息设置为缺省状态 */
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int null) {
		mapInfo[yi][xi] = GRASS;
		animalInfo[yi][xi].liveType = GRASS;
		animalInfo[yi][xi].age = 0;
		animalInfo[yi][xi].heat = 0;
	}
	void SetImage(IplImage *img[]);/*!< 设置生物图片 */
	void Draw(IplImage *Bg);/*!< 将生物图片绘制到背景图片上 */
	int GetImgIndex() { return m_imgIndex; }/*!< 获取当前生物图片序号 */
	IplImage *GetImage() { return m_img[m_imgIndex]; }/*!< 获取当前生物图片 */
private:
	IplImage *m_img[PLANT_IMAGE_COUNT];/**< 生物图片 */
	int m_imgIndex;/**< 当前图片序号 */
};
#endif
