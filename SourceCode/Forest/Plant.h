/**
* @file Plant.h
* @brief ֲ����
* @author ������
*/

#pragma once
#ifndef __PLANT_H__
#define __PLANT_H__
#include "Living.h"
class Plant : public Living
{
public:
	Plant();
	Plant(int age, int life, int heat, int posx, int posy, IplImage *img[], int imgIndex);/*!< ֲ����Ĺ��캯�����Ӵ浵���� */
	Plant(int posx, int posy, int heat, int life, IplImage *img[], int imgIndex);/*!< ֲ����Ĺ��캯��:�ɳ����������� */
	~Plant();
	/*!< ����ͼ��Ϣ����Ϊֲ���д�뵱ǰֲ��״̬ */
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int age, int heat) {
		mapInfo[yi][xi] = PLANT;			
		animalInfo[yi][xi].liveType = PLANT;
		animalInfo[yi][xi].age = age;
		animalInfo[yi][xi].heat = heat;
	}
	/*!< ����ͼ��Ϣ����Ϊȱʡ״̬ */
	void EditMapInfo(int mapInfo[MAP_Y_SIZE][MAP_X_SIZE], Map::ANIMALNODE animalInfo[MAP_Y_SIZE][MAP_X_SIZE], int xi, int yi, int null) {
		mapInfo[yi][xi] = GRASS;
		animalInfo[yi][xi].liveType = GRASS;
		animalInfo[yi][xi].age = 0;
		animalInfo[yi][xi].heat = 0;
	}
	void SetImage(IplImage *img[]);/*!< ��������ͼƬ */
	void Draw(IplImage *Bg);/*!< ������ͼƬ���Ƶ�����ͼƬ�� */
	int GetImgIndex() { return m_imgIndex; }/*!< ��ȡ��ǰ����ͼƬ��� */
	IplImage *GetImage() { return m_img[m_imgIndex]; }/*!< ��ȡ��ǰ����ͼƬ */
private:
	IplImage *m_img[PLANT_IMAGE_COUNT];/**< ����ͼƬ */
	int m_imgIndex;/**< ��ǰͼƬ��� */
};
#endif
