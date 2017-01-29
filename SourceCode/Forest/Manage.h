/**
* @file Manage.h
* @brief ���������
* @author ������
*/

#pragma once
#ifndef __MANAGE_H__
#define __MANAGE_H__
#include "stdafx.h"
#include "Resources.h"
#include "Map.h"
#include "Animals.h"
#include "Carnivorous.h"
#include "Harmless.h"
#include "plant.h"
#include "DeadEffective.h"
#include "UI.h"

class Manage
{
public:
	Manage();
	~Manage();
	void DataInit();		/*!< ���ݳ�ʼ�� */
	void LivingUpdate();	/*!< ����״̬���� */
	void TargetSearch();	/*!< ��ѰĿ����� */
	void CarnivorousUpdate();/*!< ʳ�⶯��״̬���� */
	void HarmlessUpdate();/*!< ֲʳ����״̬���� */
	void PlantUpdate();/*!< ֲ��״̬���� */
	void DeadEffectiveUpdate();/*!< ����Ч��״̬���� */
	void ProcessInfoUpdate();/*!< ��ʱ��Ϣ���� */
	void SaveJSONData();/*!< �浵 */
	void CreatureIllusionCheck();		/*!< �ж��Ƿ�����������֮�䷢������ײ��������Ӧ����Ϊ */
	void DisplayAnimalInfo(int posx, int posy);/*!< ��ʾ��ǰ�����ָ������ĸ�����Ϣ */
	void CheckHaveAnimal(int posx, int posy);	/*!< ��⵱ǰ���Ƿ������� */
	UI m_ui;
	int m_times;			/**< ��ʱ�� */
	IplImage *m_showBg;/**< ����ͼƬ */
	IplImage *m_Bg;/**< ����ͼƬ */
	bool m_displayinfo_swi;/**< �Ƿ���ʾ��ǰ��ָ�������Ϣ�Ŀ��ر��� */
	int m_infoX, m_infoY;/**< ��ǰ��ָ������ */
private:
	Resources m_resources;
	
	Map m_map;
	vector<Carnivorous *>m_wolf;/**< ʳ�⶯������ */
	vector<Harmless *>m_rabit;/**< ֲʳ�������� */
	vector<Plant *>m_plant;/**< ֲ������ */
	vector<DeadEffective *>m_deadEffective;/**< ����Ч������ */
	FILE *fp;				/**< �����ʱ��Ϣ���ļ�ָ�� */
	FILE *fp_cur;			/**< �����ǰ�浵��Ϣ���ļ�ָ�� */
	
	/** @brief ��¼ÿ��λʱ����������Է�ֵ */
	struct attributeNode {		
		int energy;/**< ������ */
		int life;/**< ���� */
		int age;/**< ���� */
	}m_carnivorousMaxCount, m_harmlessMaxCount, m_plantMaxCount;
};
#endif
