/**
* @file Map.h
* @brief ��ͼ�࣬�������ɻ�����ͼ��Ϣ���ͼ�¼��ͼ���������Ϣ��
* @author ������
*/

#ifndef __MAP_H__
#define __MAP_H__
#include "stdafx.h"
#include "Tools.h"

class Map
{
public:
	Map();
	~Map();
	void GenerateMapInfo();
	void SetMapImage(IplImage *img[]);
	void DrawMap(IplImage *Bg);
	int m_mapInfo[MAP_Y_SIZE][MAP_X_SIZE];/**< ��ͼ��Ϣ */

	/** @brief ������Ϣ */
	struct ANIMALNODE {
		int liveType;/**< �������� */
		int age;/**< ���� */
		int heat;/**< ���ܴ��������� */
		int hungry;/**< ������ */
		int nowEatTime;/**< ����Է��Ķ��� */
		bool isFindTarget;/**< �Ƿ�������Ŀ�� */
		bool isFlee;/**< ����״̬ */
	};
	ANIMALNODE m_AnimalInfo[MAP_Y_SIZE][MAP_X_SIZE];/**< ��ͼ������ĸ�����Ϣ */
	IplImage *m_mapImg[MAP_IMG_COUNT];/**< ����ͼƬ */
};

#endif