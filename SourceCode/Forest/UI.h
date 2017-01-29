/**
* @file UI.h
* @brief 负责图形化显示开始界面的一个类
* @author 喻永生
*/

#ifndef __UI_H__
#define __UI_H__
#include "Tools.h"
class UI
{
public:
	UI();
	~UI();
	void InitOneUi();/*!< 初始化开始界面 */
	int calCenterX(int text_size, int text_num, int win_width);		/*!< 居中显示字体算法 */

	bool IsCreatNewMap() { return m_firstIndex == 1 ? true : false; }/*!< 获取是否开始新森林 */
	int GetPlantNum() { return m_plantNum; }/*!< 获取植物数量 */
	int GetCarnivorousNum() { return m_carnivorousNum; }/*!< 获取食肉动物数量 */
	int GetHarmlessNum() { return m_harmlessNum; }/*!< 获取植食动物数量 */
	char m_forestName[25];	/**< 森林名字：用于窗口名称，存档名称 */
private:
	int m_plantNum;/**< 输入的植物数量 */
	int m_carnivorousNum;/**< 输入的食肉动物数量 */
	int m_harmlessNum;/**< 输入的植食动物数量 */
	CvSize map_size;				/**< 窗口大小 */
	IplImage *map_image, *map_image_backup;		/**< 背景图片 */
	IplImage *map_image_backup_highstage;/**< 背景图片 */
	int m_width, m_height;/**< 窗口宽高（按方格） */
	int m_firstIndex;/**< 第一次选择的序号 */
	int m_secondIndex;/**< 第二次选择的序号 */
};
#endif

