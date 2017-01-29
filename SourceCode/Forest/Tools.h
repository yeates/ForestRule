/**
* @file Tools.h
* @brief 存放全局工具函数，方便调用
* @author 喻永生
*/

#ifndef __TOOLS_H__
#define __TOOLS_H__
class Tools
{
public:
	Tools();
	~Tools();
	static void DrawToBack(int startX, int startY, IplImage *Bg, IplImage *img, int keyr, int keyb, int keyg);/*!< 将图片显示到背景图片上 */
	static void print(char *str, int number);/*!< 按格式输出信息到命令框界面 */
	static void print(char *str, int number, FILE *fp);/*!< 按格式输出信息到文本 */
	static cJSON* GetJsonArray(char* fileName);/*!< 利用文件系统获取cjson文件 */
	static int GetJSONNumberValue(cJSON* json, int no, char* key);/*!< 获取json数组的个数 */
	static bool CheckRectIllusion(CvPoint a, IplImage *a_img, CvPoint b, IplImage *b_img);/*!< 判断矩形是否重合的算法 */
};

#endif