/**
* @file Resources.h
* @brief ������Դ������
* @author ������
*/

#pragma once

#ifndef __RESOURCES_H__
#define __RESOURCES_H__

class Resources
{
public:
	Resources();
	~Resources();
	void InitResources();/*!< ��ʼ��������Ҫ����Դ */
	void ReleaseResources();/*!< �ͷų�����Դ */

	IplImage *m_mapImage[MAP_IMG_COUNT];/**< ��ͼͼƬ */
	IplImage *m_carnivorousImage[ANIMAL_MOVEIMG_COUNT];/**< ʳ�⶯��ͼƬ */
	IplImage *m_harmlessImage[ANIMAL_MOVEIMG_COUNT];/**< ֲʳ����ͼƬ */
	IplImage *m_plantImage[PLANT_IMAGE_COUNT];/**< ֲ��ͼƬ */
	IplImage *m_harmlessDeadImage[DEAD_IMAGE_COUNT];/**< ֲʳ��������Ч��ͼƬ */
};

#endif