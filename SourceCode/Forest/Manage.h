/**
* @file Manage.h
* @brief 程序控制类
* @author 喻永生
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
	void DataInit();		/*!< 数据初始化 */
	void LivingUpdate();	/*!< 对象状态更新 */
	void TargetSearch();	/*!< 搜寻目标对象 */
	void CarnivorousUpdate();/*!< 食肉动物状态更新 */
	void HarmlessUpdate();/*!< 植食动物状态更新 */
	void PlantUpdate();/*!< 植物状态更新 */
	void DeadEffectiveUpdate();/*!< 死亡效果状态更新 */
	void ProcessInfoUpdate();/*!< 即时信息更新 */
	void SaveJSONData();/*!< 存档 */
	void CreatureIllusionCheck();		/*!< 判断是否生物与生物之间发生的碰撞并做出相应的行为 */
	void DisplayAnimalInfo(int posx, int posy);/*!< 显示当前光标所指的生物的个体信息 */
	void CheckHaveAnimal(int posx, int posy);	/*!< 检测当前格是否是生物 */
	UI m_ui;
	int m_times;			/**< 计时器 */
	IplImage *m_showBg;/**< 背景图片 */
	IplImage *m_Bg;/**< 背景图片 */
	bool m_displayinfo_swi;/**< 是否显示当前所指生物的信息的开关变量 */
	int m_infoX, m_infoY;/**< 当前所指的坐标 */
private:
	Resources m_resources;
	
	Map m_map;
	vector<Carnivorous *>m_wolf;/**< 食肉动物容器 */
	vector<Harmless *>m_rabit;/**< 植食动物容器 */
	vector<Plant *>m_plant;/**< 植物容器 */
	vector<DeadEffective *>m_deadEffective;/**< 死亡效果容器 */
	FILE *fp;				/**< 输出即时消息的文件指针 */
	FILE *fp_cur;			/**< 输出当前存档信息的文件指针 */
	
	/** @brief 记录每单位时间生物的属性峰值 */
	struct attributeNode {		
		int energy;/**< 饥饿度 */
		int life;/**< 寿命 */
		int age;/**< 年龄 */
	}m_carnivorousMaxCount, m_harmlessMaxCount, m_plantMaxCount;
};
#endif
