#include "stdafx.h"
#include "Plant.h"


Plant::Plant()
{
}

Plant::Plant(int age, int life, int heat, int posx, int posy, IplImage *img[], int imgIndex) {
	m_heat = heat;
	m_life = life;
	m_age = age;
	m_drawPos.x = posx * GRID_SIZE;
	m_drawPos.y = posy * GRID_SIZE;
	m_movePos.x = posx;
	m_movePos.y = posy;
	m_isClear = false;
	SetImage(img);
	m_imgIndex = imgIndex;
}

Plant::Plant(int posx, int posy, int heat, int life, IplImage *img[], int imgIndex) {
	m_heat = heat;
	m_life = life;
	m_age = 0;
	m_drawPos.x = posx * GRID_SIZE;
	m_drawPos.y = posy * GRID_SIZE;
	m_movePos.x = posx;
	m_movePos.y = posy;
	m_isClear = false;
	SetImage(img);
	m_imgIndex = imgIndex;
}

void Plant::Draw(IplImage *Bg) {
	Tools::DrawToBack(m_drawPos.x, m_drawPos.y, Bg, m_img[m_imgIndex], 255, 255, 255);
}

Plant::~Plant()
{
}

void Plant::SetImage(IplImage *img[]){
	for (int i = 0; i < PLANT_IMAGE_COUNT; i++) {
		m_img[i] = img[i];
	}
}

