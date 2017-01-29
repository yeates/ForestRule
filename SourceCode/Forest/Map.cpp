#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	GenerateMapInfo();
}


Map::~Map()
{
}

void Map::GenerateMapInfo() {
	for (int i = 0; i < MAP_Y_SIZE; i++) {
		for (int j = 0; j < MAP_X_SIZE; j++) {
			m_mapInfo[i][j] = 0;
		}
	}
}

void Map::SetMapImage(IplImage *img[]) {
	for (int i = 0; i < MAP_IMG_COUNT; i++)
		m_mapImg[i] = img[i];
}
//¾ÍÊÇ»­²İ
void Map::DrawMap(IplImage *Bg) {
	for (int i = 0; i < MAP_Y_SIZE; i++) {
		for (int j = 0; j < MAP_X_SIZE; j++) {
			Tools::DrawToBack(j * GRID_SIZE, i * GRID_SIZE, Bg, m_mapImg[0], 255, 255, 255);
		}
	}
}
