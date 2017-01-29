#include "stdafx.h"
#include "Harmless.h"

Harmless::Harmless(int posx, int posy, int staticViewRange, int activeViewRange, int staticSpeed, int activeSpeed, int hungry, int heat, int life, IplImage *img[]) {
	m_drawPos.x = posx * GRID_SIZE;
	m_drawPos.y = posy * GRID_SIZE;
	m_movePos.x = posx;
	m_movePos.y = posy;
	m_isMove = false;
	m_isFindTarget = false;
	m_age = 0;
	m_life = life;
	m_hungry = hungry;
	m_imgId = 0;
	m_isStatic = true;
	m_staticSpeed = staticSpeed;
	m_activeSpeed = activeSpeed;
	m_targetPos.x = -1;
	m_targetPos.y = -1;
	m_staticViewRange = staticViewRange;
	m_activeViewRange = activeViewRange;
	m_isCollision = false;
	m_isClear = false;
	m_isFlee = false;
	m_heat = heat;

	m_maxEatTime = 1;
	m_nowEatTime = 0;
	SetImage(img);
}

Harmless::Harmless(int age, int life, int heat, int posx, int posy, int staticview, int activeview,
	int isstatic, int ismove, int staticspeed, int activespeed, int imgid, int hungry, int movedir,
	int iscollision, int movedis, IplImage *img[ANIMAL_MOVEIMG_COUNT], int maxEatTime, int nowEatTime) {
	m_age = age;
	m_life = life;
	m_heat = heat;
	m_drawPos.x = posx * GRID_SIZE;
	m_drawPos.y = posy * GRID_SIZE;
	m_movePos.x = posx;
	m_movePos.y = posy;
	m_heat = heat;
	m_staticViewRange = staticview;
	m_activeViewRange = activeview;
	m_isStatic = isstatic;
	m_isMove = ismove;
	m_staticSpeed = staticspeed;
	m_activeSpeed = activespeed;
	m_imgId = imgid;
	m_hungry = hungry;
	m_moveDir = movedir;
	m_isCollision = iscollision;
	m_moveDis = movedis;

	m_maxEatTime = maxEatTime;
	m_nowEatTime = nowEatTime;
	SetImage(img);

	m_targetPos.x = -1;
	m_targetPos.y = -1;
	m_isFindTarget = false;
	m_isClear = false;
}

Harmless::Harmless()
{
}


Harmless::~Harmless()
{
}

void Harmless::SetImage(IplImage *img[], int n) {
	for (int i = 0; i < n; i++) {
		m_img[i] = img[i];
	}
}

void Harmless::Draw(IplImage *Bg) {
	Tools::DrawToBack(m_drawPos.x, m_drawPos.y, Bg, m_img[m_imgId], 0, 0, 0);
}