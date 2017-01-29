#include "stdafx.h"
#include "Tools.h"


Tools::Tools()
{
}


Tools::~Tools()
{
}

void Tools::DrawToBack(int startX, int startY, IplImage *Bg, IplImage *img, int keyr, int keyb, int keyg) {
	int b, g, r;
	int x, y;
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			
			b = CV_IMAGE_ELEM(img, uchar, i, j * 3 + 0);
			g = CV_IMAGE_ELEM(img, uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(img, uchar, i, j * 3 + 2);

			if (abs(b - keyb) <= 10 && abs(r - keyr) <= 10 && abs(g - keyg) <= 10)	continue;
			x = j + startX;
			y = i + startY;
			if (x >= Bg->width)
				x -= Bg->width;
			if (x < 0)
				x += Bg->width;
			if (y >= Bg->height)
				y -= Bg->height;
			if (y < 0)
				y += Bg->height;

			CV_IMAGE_ELEM(Bg, uchar, y, x * 3 + 0) = b;
			CV_IMAGE_ELEM(Bg, uchar, y, x * 3 + 1) = g;
			CV_IMAGE_ELEM(Bg, uchar, y, x * 3 + 2) = r;
		}
	}
}

//¾ÓÖÐÊä³ö×Ö·û´®£¨Á½±ßÊÇÐÇºÅ£©
void Tools::print(char *str, int number) {
	int len = strlen(str);
	const int totLen = number;
	for (int i = 1; i <= (totLen - len) / 2; i++)	cout << "*";
	cout << str;
	for (int i = (totLen + len) / 2; i <= totLen; i++)	cout << "*";
	cout << endl;
}

void Tools::print(char *str, int number, FILE *fp) {
	int len = strlen(str);
	const int totLen = number;
	for (int i = 1; i <= (totLen - len) / 2; i++)	fprintf(fp, "*");
	fprintf(fp, str);
	for (int i = (totLen + len) / 2; i <= totLen; i++)	fprintf(fp, "*");
	fprintf(fp, "\n");
}

cJSON* Tools::GetJsonArray(char* fileName)
{
	long len;
	char* pContent;
	int tmp;
	cJSON *json;
	FILE* fp = fopen(fileName, "rb+");
	if (!fp)
	{
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	if (0 == len)
	{
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);
	pContent = (char*)malloc(sizeof(char)*len);
	tmp = fread(pContent, 1, len, fp);

	fclose(fp);
	json = cJSON_Parse(pContent);
	if (!json)
	{
		return NULL;
	}
	free(pContent);
	return json;
}

int Tools::GetJSONNumberValue(cJSON* json, int no, char* key)
{
	cJSON* node;
	node = cJSON_GetArrayItem(json, no);
	if (!node)
	{
		return -1;
	}
	return cJSON_GetObjectItem(node, key)->valueint;
}

bool Tools::CheckRectIllusion(CvPoint a, IplImage *a_img, CvPoint b, IplImage *b_img) {
	int offsetX, offsetY;
	offsetX = abs((a.x + a_img->width / 2) - (b.x + b_img->width / 2));
	offsetY = abs((a.y + a_img->height / 2) - (b.y + b_img->height / 2));
	if (offsetX < (a_img->width / 2 + b_img->width / 2) && offsetY < (a_img->height / 2 + b_img->height / 2))	return true;
	else return false;
}