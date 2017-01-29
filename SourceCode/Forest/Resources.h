/**
* @file Resources.h
* @brief 程序资源管理类
* @author 喻永生
*/

#pragma once

#ifndef __RESOURCES_H__
#define __RESOURCES_H__

class Resources
{
public:
	Resources();
	~Resources();
	void InitResources();/*!< 初始化程序需要的资源 */
	void ReleaseResources();/*!< 释放程序资源 */

	IplImage *m_mapImage[MAP_IMG_COUNT];/**< 地图图片 */
	IplImage *m_carnivorousImage[ANIMAL_MOVEIMG_COUNT];/**< 食肉动物图片 */
	IplImage *m_harmlessImage[ANIMAL_MOVEIMG_COUNT];/**< 植食动物图片 */
	IplImage *m_plantImage[PLANT_IMAGE_COUNT];/**< 植物图片 */
	IplImage *m_harmlessDeadImage[DEAD_IMAGE_COUNT];/**< 植食动物死亡效果图片 */
};

#endif