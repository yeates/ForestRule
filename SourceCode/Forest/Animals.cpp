#include "stdafx.h"
#include "Animals.h"


Animals::~Animals()
{
}

Animals::Animals() {

}

void Animals::Chase(IplImage *Bg) {
	if (m_moveDis < GRID_SIZE && m_isMove) {
		if (m_moveDir == UP) {
			if (m_imgId >= 0 && m_imgId < 4) {
				m_imgId++;
				m_imgId = m_imgId > 3 ? 0 : m_imgId;
			}
			else m_imgId = 0;

			if (m_isStatic == false) {
				m_drawPos.y -= m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
			else {
				m_drawPos.y -= m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
		}
		else if (m_moveDir == DOWN) {
			if (m_imgId >= 4 && m_imgId < 8) {
				m_imgId++;
				m_imgId = m_imgId > 7 ? 4 : m_imgId;
			}
			else m_imgId = 4;

			if (m_isStatic == false) {
				m_drawPos.y += m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
			else {
				m_drawPos.y += m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
		}
		else if (m_moveDir == RIGHT) {
			if (m_imgId >= 8 && m_imgId < 12) {
				m_imgId++;
				m_imgId = m_imgId > 11 ? 8 : m_imgId;
			}
			else m_imgId = 8;

			if (m_isStatic == false) {
				m_drawPos.x += m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
			else {
				m_drawPos.x += m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
		}
		else if (m_moveDir == LEFT) {
			if (m_imgId >= 12 && m_imgId < 16) {
				m_imgId++;
				m_imgId = m_imgId > 15 ? 12 : m_imgId;
			}
			else m_imgId = 12;

			if (m_isStatic) {
				m_drawPos.x -= m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
			else {
				m_drawPos.x -= m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
		}

		//防止越界
		if (m_drawPos.x < 0) {
			m_drawPos.x = Bg->width + m_drawPos.x;
		}
		if (m_drawPos.x > Bg->width - m_img[m_imgId]->width - 1) {
			m_drawPos.x = m_drawPos.x - Bg->width;
		}
		if (m_drawPos.y < 0) {
			m_drawPos.y = Bg->height + m_drawPos.y;
		}
		if (m_drawPos.y > Bg->height - m_img[m_imgId]->height - 1) {
			m_drawPos.y = m_drawPos.y - Bg->height;
		}

		return;
	}
	//按格子移动完毕
	else if (m_isMove) {
		m_moveDis = 0;
		m_isMove = false;
		if (m_isCollision) {
			m_isCollision = false;
			return;
		}
		if (m_moveDir == UP) {
			m_movePos.y -= 1;
			if (m_movePos.y < 0) {
				m_movePos.y = MAP_Y_SIZE - 1;
			}
		}
		else if (m_moveDir == DOWN) {
			m_movePos.y += 1;
			if (m_movePos.y >= MAP_Y_SIZE)
				m_movePos.y = 0;
		}
		else if (m_moveDir == LEFT) {
			m_movePos.x -= 1;
			if (m_movePos.x < 0)
				m_movePos.x = MAP_X_SIZE - 1;
		}
		else if (m_moveDir == RIGHT) {
			m_movePos.x += 1;
			if (m_movePos.x >= MAP_X_SIZE)
				m_movePos.x = 0;
		}
		return;
	}


	//选择移动方向
	//如果当前生物是静息状态
	if (!m_isMove && !m_isFindTarget) {
		int tmp = rand() % 80 + 1;			//行走的几率有1/20

		if (tmp <= 4) {
			m_moveDir = tmp;
			m_moveDis = 0;
			m_isMove = true;
		}
		else {
			switch (m_moveDir)
			{
			case UP:
				m_imgId = 0;
				break;
			case DOWN:
				m_imgId = 4;
				break;
			case RIGHT:
				m_imgId = 8;
				break;
			case LEFT:
				m_imgId = 12;
				break;
			default:break;
			}
		}
	}
	//靠近目标
	else if (!m_isMove && m_isFindTarget) {
		int absx = m_targetPos.x - m_movePos.x;
		int absy = m_targetPos.y - m_movePos.y;
		if (abs(absx) - abs(absy) > 0) {
			if (absx < 0)
				m_moveDir = LEFT;
			else m_moveDir = RIGHT;
		}
		else {
			if (absy < 0)
				m_moveDir = UP;
			else m_moveDir = DOWN;
		}

		m_moveDis = 0;
		m_isMove = true;
	}
}

void Animals::Flee(IplImage *Bg) {
	if (m_moveDis < GRID_SIZE && m_isMove) {
		if (m_moveDir == UP) {
			if (m_imgId >= 0 && m_imgId < 4) {
				m_imgId++;
				m_imgId = m_imgId > 3 ? 0 : m_imgId;
			}
			else m_imgId = 0;

			if (m_isStatic == false) {
				m_drawPos.y -= m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
			else {
				m_drawPos.y -= m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
		}
		else if (m_moveDir == DOWN) {
			if (m_imgId >= 4 && m_imgId < 8) {
				m_imgId++;
				m_imgId = m_imgId > 7 ? 4 : m_imgId;
			}
			else m_imgId = 4;

			if (m_isStatic == false) {
				m_drawPos.y += m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
			else {
				m_drawPos.y += m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
		}
		else if (m_moveDir == RIGHT) {
			if (m_imgId >= 8 && m_imgId < 12) {
				m_imgId++;
				m_imgId = m_imgId > 11 ? 8 : m_imgId;
			}
			else m_imgId = 8;

			if (m_isStatic == false) {
				m_drawPos.x += m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
			else {
				m_drawPos.x += m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
		}
		else if (m_moveDir == LEFT) {
			if (m_imgId >= 12 && m_imgId < 16) {
				m_imgId++;
				m_imgId = m_imgId > 15 ? 12 : m_imgId;
			}
			else m_imgId = 12;

			if (m_isStatic) {
				m_drawPos.x -= m_staticSpeed;
				m_moveDis += m_staticSpeed;
			}
			else {
				m_drawPos.x -= m_activeSpeed;
				m_moveDis += m_activeSpeed;
			}
		}

		//防止越界
		if (m_drawPos.x < 0) {
			m_drawPos.x = Bg->width + m_drawPos.x;
		}
		if (m_drawPos.x > Bg->width - m_img[m_imgId]->width - 1) {
			m_drawPos.x = m_drawPos.x - Bg->width;
		}
		if (m_drawPos.y < 0) {
			m_drawPos.y = Bg->height + m_drawPos.y;
		}
		if (m_drawPos.y > Bg->height - m_img[m_imgId]->height - 1) {
			m_drawPos.y = m_drawPos.y - Bg->height;
		}

		return;
	}
	else if (m_isMove) {
		m_moveDis = 0;
		m_isMove = false;
		if (m_isCollision) {
			m_isCollision = false;
			return;
		}
		if (m_moveDir == UP) {
			m_movePos.y -= 1;
			if (m_movePos.y < 0) {
				m_movePos.y = MAP_Y_SIZE - 1;
			}
		}
		else if (m_moveDir == DOWN) {
			m_movePos.y += 1;
			if (m_movePos.y >= MAP_Y_SIZE)
				m_movePos.y = 0;
		}
		else if (m_moveDir == LEFT) {
			m_movePos.x -= 1;
			if (m_movePos.x < 0)
				m_movePos.x = MAP_X_SIZE - 1;
		}
		else if (m_moveDir == RIGHT) {
			m_movePos.x += 1;
			if (m_movePos.x >= MAP_X_SIZE)
				m_movePos.x = 0;
		}
		return;
	}

	if (!m_isMove && !m_isFindTarget) {
		//srand((unsigned)time(NULL));
		int tmp = rand() % 8 + 1;
		if (tmp > 4) {
			switch (m_moveDir)
			{
			case UP:
				m_imgId = 0;
				break;
			case DOWN:
				m_imgId = 4;
				break;
			case RIGHT:
				m_imgId = 8;
				break;
			case LEFT:
				m_imgId = 12;
				break;
			default:break;
			}
			return;
		}
		else m_moveDir = tmp;

		m_moveDis = 0;
		m_isMove = true;
	}
	//远离目标
	else if (!m_isMove && m_isFindTarget) {
		int absx = m_targetPos.x - m_movePos.x;
		int absy = m_targetPos.y - m_movePos.y;
		if (abs(absx) - abs(absy) > 0) {
			if (absx < 0)
				m_moveDir = RIGHT;
			else m_moveDir = LEFT;
		}
		else {
			if (absy < 0)
				m_moveDir = DOWN;
			else m_moveDir = UP;
		}

		m_moveDis = 0;
		m_isMove = true;
	}
}

