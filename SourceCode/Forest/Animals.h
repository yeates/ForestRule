/**
* @file Animals.h
* @brief �����࣬��ֲ���ಢ�У��̳���������(living)��Ҳ��һ�������࣬��Ϊʳ�⶯�����ֲʳ������Ļ���
* @author ������
*/

#pragma once
#ifndef __ANIMALS_H__
#define __ANIMALS_H__
#include "Living.h"
class Animals : public Living
{
public:
	Animals();
	~Animals();
	void Chase(IplImage *Bg);/*!< ��ʳ */
	void Flee(IplImage *Bg);/*!< ���� */
	int GetEnergy() { return m_hungry; }/*!< ��ȡ����ֵ */
	void SetTargetPos(int posx, int posy) {
		m_targetPos.x = posx;
		m_targetPos.y = posy;
	}
	int GetStaticViewRange() { return m_staticViewRange; }/*!< ��ȡ��Ϣ״̬��Ұ */
	int GetActiveViewRange() { return m_activeViewRange; }/*!< ��ȡ��Ծ״̬��Ұ */
	int GetStaticSpeed() { return m_staticSpeed; }/*!< ��ȡ��Ϣ״̬�ƶ��ٶ� */
	int GetActiveSpeed() { return m_activeSpeed; }/*!< ��ȡ��Ծ״̬�ƶ��ٶ� */
	void SetFindTarget(bool is) { m_isFindTarget = is; }/*!< �����Ƿ��ҵ���Ŀ����� */
	void SetisActive(bool is) {
		m_isStatic = !is;
	}
	bool isStatic() { return m_isStatic; }/*!< ��ȡ�Ƿ�Ϊ��Ϣ״̬ */
	bool isFindTarget() { return m_isFindTarget; }/*!< ��ȡ�Ƿ��ҵ���Ŀ����� */
	void ChangeEnergy(int energy) { m_hungry += energy; }/*!< �ı䵱ǰ�ƶ����� */
	int GetDirection() { return m_moveDir; }/*!< ��ȡ��ǰ�ƶ����� */
	int GetImgID() { return m_imgId; }/*!< ��ȡ��ǰͼƬ��� */
	int GetMoveDir() { return m_moveDir; }/*!< ��ȡ��ǰ�ƶ����� */
	int IsCollision() { return m_isCollision; }/*!< �ж��Ƿ���ײ */
	int isMove() { return m_isMove; }/*!< �ж��Ƿ����ƶ� */
	int GetMoveDis() { return m_moveDis; }/*!< ��ȡ���ƶ�������ֵ */
	int GetMaxEatTime() { return m_maxEatTime; }/*!< ��ȡ��������ܳԵĶ��� */
	int GetNowEatTime() { return m_nowEatTime; }/*!< ��ȡ������˵Ķ��� */
	void Eat() { m_nowEatTime++; }/*!< ��ʳ�������� */
	void InitEatTime() { m_nowEatTime = 0; }
	IplImage *GetImage() { return m_img[m_imgId]; }/*!< ��ȡ����ͼƬ */
protected:
	IplImage *m_img[ANIMAL_MOVEIMG_COUNT];/**< ����ͼƬ */
	CvPoint m_targetPos;		/**< Ŀ�������� */
	bool m_isFindTarget;		/**< �Ƿ��Ѿ�������Ŀ�� */
	int m_staticViewRange;		/**< ��Ĭ״̬��Ұ��Χ */
	int m_activeViewRange;		/**< ��Ծ״̬��Ұ��Χ */
	bool m_isStatic;			/**< �Ƿ��ھ�Ĭ״̬���ͻ�Ծ״̬�Աȣ���Ծ״̬��������׷ɱ����������״̬�� */
	int m_staticSpeed;			/**< ��Ĭ״̬���ƶ��ٶ� */
	int m_activeSpeed;			/**< ��Ծ״̬���ƶ��ٶ� */
	int m_imgId;				/**< ͼƬ��ʾID */
	int m_hungry;				/**< ��ǰ�ļ����̶ȣ�����0ʱ���� */
	int m_moveDir;				/**< �ƶ����� */
	bool m_isMove;				/**< �Ƿ������ƶ� */
	int m_moveDis;				/**< ��ǰ�Ѿ��ƶ��ľ��� */
	bool m_isCollision;			/**< �Ƿ�����ײ */
	int m_maxEatTime;			/**< һ����߳Զ����Ĵ��� */
	int m_nowEatTime;			/**< ��ǰ�Ѿ����˶��ٴ� */
};
#endif

