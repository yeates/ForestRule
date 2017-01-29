/**
* @file Tools.h
* @brief ���ȫ�ֹ��ߺ������������
* @author ������
*/

#ifndef __TOOLS_H__
#define __TOOLS_H__
class Tools
{
public:
	Tools();
	~Tools();
	static void DrawToBack(int startX, int startY, IplImage *Bg, IplImage *img, int keyr, int keyb, int keyg);/*!< ��ͼƬ��ʾ������ͼƬ�� */
	static void print(char *str, int number);/*!< ����ʽ�����Ϣ���������� */
	static void print(char *str, int number, FILE *fp);/*!< ����ʽ�����Ϣ���ı� */
	static cJSON* GetJsonArray(char* fileName);/*!< �����ļ�ϵͳ��ȡcjson�ļ� */
	static int GetJSONNumberValue(cJSON* json, int no, char* key);/*!< ��ȡjson����ĸ��� */
	static bool CheckRectIllusion(CvPoint a, IplImage *a_img, CvPoint b, IplImage *b_img);/*!< �жϾ����Ƿ��غϵ��㷨 */
};

#endif