/**
* @file UI.h
* @brief ����ͼ�λ���ʾ��ʼ�����һ����
* @author ������
*/

#ifndef __UI_H__
#define __UI_H__
#include "Tools.h"
class UI
{
public:
	UI();
	~UI();
	void InitOneUi();/*!< ��ʼ����ʼ���� */
	int calCenterX(int text_size, int text_num, int win_width);		/*!< ������ʾ�����㷨 */

	bool IsCreatNewMap() { return m_firstIndex == 1 ? true : false; }/*!< ��ȡ�Ƿ�ʼ��ɭ�� */
	int GetPlantNum() { return m_plantNum; }/*!< ��ȡֲ������ */
	int GetCarnivorousNum() { return m_carnivorousNum; }/*!< ��ȡʳ�⶯������ */
	int GetHarmlessNum() { return m_harmlessNum; }/*!< ��ȡֲʳ�������� */
	char m_forestName[25];	/**< ɭ�����֣����ڴ������ƣ��浵���� */
private:
	int m_plantNum;/**< �����ֲ������ */
	int m_carnivorousNum;/**< �����ʳ�⶯������ */
	int m_harmlessNum;/**< �����ֲʳ�������� */
	CvSize map_size;				/**< ���ڴ�С */
	IplImage *map_image, *map_image_backup;		/**< ����ͼƬ */
	IplImage *map_image_backup_highstage;/**< ����ͼƬ */
	int m_width, m_height;/**< ���ڿ�ߣ������� */
	int m_firstIndex;/**< ��һ��ѡ������ */
	int m_secondIndex;/**< �ڶ���ѡ������ */
};
#endif

