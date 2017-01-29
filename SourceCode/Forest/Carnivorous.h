/**
* @file Carnivorous.h
* @brief ʳ�⶯���࣬�̳���Animals��
* @author ������
*/

#pragma once

#ifndef __CARNIVOROUS_H__
#define __CARNIVOROUS_H__
#include "Animals.h"
#include "Tools.h"

//ʳ�⶯��
class Carnivorous : public Animals
{
public:
	/*!< ʳ�⶯�ﹹ�캯��:�Ӵ浵����/�ɳ����������� */
	Carnivorous(int age, int life, int heat, int posx, int posy, int staticview, int activeview, int isstatic, int ismove, int staticspeed, int activespeed, int imgid, int hungry, int movedir, int iscollision, int movedis, IplImage *img[ANIMAL_MOVEIMG_COUNT], int maxEatTime, int nowEatTime) ;
	Carnivorous(int posx, int posy, int staticViewRange, int activeViewRange, int staticSpeed, int activeSpeed, int hungry, int heat, int life, IplImage *img[]);
	~Carnivorous();
	void SetImage(IplImage *img[]);/*!< ����ʳ�⶯��ͼƬ */
	void Draw(IplImage *Bg);/*!< ��ͼ */
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int age, int heat, int hungry, int nowEatTime, bool isFindTarget) {
		mapInfo[yi][xi] = CANIVOROUS;
		animalInfo[yi][xi].age = age;
		animalInfo[yi][xi].heat = heat;
		animalInfo[yi][xi].hungry = hungry;
		animalInfo[yi][xi].nowEatTime = nowEatTime;
		animalInfo[yi][xi].isFindTarget = isFindTarget;
		animalInfo[yi][xi].liveType = CANIVOROUS;
	}
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int null) {
		mapInfo[yi][xi] = GRASS;
		animalInfo[yi][xi].age = 0;
		animalInfo[yi][xi].heat = 0;
		animalInfo[yi][xi].hungry = 0;
		animalInfo[yi][xi].nowEatTime = 0;
		animalInfo[yi][xi].isFindTarget = false;
		animalInfo[yi][xi].liveType = GRASS;
	}
	bool JudgeEat();/*!< �ж��Ƿ�Ա� */
}; 
#endif