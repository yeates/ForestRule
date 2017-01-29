/**
* @file Map.h
* @brief 地图类，用于生成基本地图信息，和记录地图结点生物信息。
* @author 喻永生
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
	int m_mapInfo[MAP_Y_SIZE][MAP_X_SIZE];/**< 地图信息 */

	/** @brief 生物信息 */
	struct ANIMALNODE {
		int liveType;/**< 生物种类 */
		int age;/**< 年龄 */
		int heat;/**< 所能带来的能量 */
		int hungry;/**< 饥饿度 */
		int nowEatTime;/**< 当天吃饭的顿数 */
		bool isFindTarget;/**< 是否搜索到目标 */
		bool isFlee;/**< 逃跑状态 */
	};
	ANIMALNODE m_AnimalInfo[MAP_Y_SIZE][MAP_X_SIZE];/**< 地图上生物的个体信息 */
	IplImage *m_mapImg[MAP_IMG_COUNT];/**< 背景图片 */
};

#endif