#include "stdafx.h"
#include "DeadEffective.h"


DeadEffective::DeadEffective()
{
}


DeadEffective::~DeadEffective()
{
}

DeadEffective::DeadEffective(IplImage *img, int posx, int posy) {
	m_harmlessDeadImg = img;
	m_nowTimes = 0;
	m_isClear = false;
	m_drawPos.x = posx, m_drawPos.y = posy;
}

void DeadEffective::TimeGoOn() {
	m_nowTimes++;
	if (m_nowTimes >= m_imgLife)
		m_isClear = true;
}
