#include "stdafx.h"
#include "UI.h"


UI::UI()
{
	m_width = 800;
	m_height = 600;
	m_firstIndex = 1;
	m_secondIndex = 1;
}


UI::~UI()
{
}

void UI::InitOneUi() {
	CvxText text("simsun.ttc");		//������ͨ����
	CvxText text_title("simsun.ttc");	//��������
	CvxText text_notice("simsun.ttc");			//��ʾ����
	int _texttype, _textsize;
	bool _underline;
	float _diaphaneity;
	CvScalar _scalar;
	//�޸ı�����������
	text_title.getFont(&_texttype, &_scalar, &_underline, &_diaphaneity);
	_scalar.val[0] = TITLETEXTSIZE;
	_diaphaneity = 0.9;
	text_title.setFont(&_texttype, &_scalar, &_underline, &_diaphaneity);
	//�޸���ͨ��������
	text.getFont(&_texttype, &_scalar, &_underline, &_diaphaneity);
	_scalar.val[0] = NORMALTEXTSIZE;
	text.setFont(&_texttype, &_scalar, &_underline, &_diaphaneity);
	//����ʾ����Ĭ������
	text_notice.getFont(&_texttype, &_scalar, &_underline, &_diaphaneity);
	_scalar.val[0] = NOTICETEXTSIZE;
	text_notice.setFont(&_texttype, &_scalar, &_underline, &_diaphaneity);

	CvScalar mainColor = CV_RGB(111,149,58);
	CvScalar blackMainColor = CV_RGB(58, 93, 8);
	CvScalar brightMainColor = CV_RGB(131, 189, 48);
	CvScalar white = CV_RGB(255, 255, 255);
	CvScalar black = CV_RGB(0, 0, 0);
	cvNamedWindow("ɭ�ַ���", CV_WINDOW_AUTOSIZE);			//��������
	map_size.height = 600, map_size.width = 800;
	map_image = cvLoadImage("./img/uibg.jpg");
	map_image_backup = cvCloneImage(map_image);
	text.getFont(&_texttype, &_scalar);
	_textsize = _scalar.val[0];
	while (1) {
		cvCopy(map_image_backup, map_image);
		text_title.putText(map_image, "��ɭ�ַ���", cvPoint(310, 80), white);	//д�����嵽��ʼ����ͼƬ��
		int rpos = 150, cpos = 400, lpos = 650;
		cvCircle(map_image, cvPoint(rpos, 175), 33, mainColor, -1);
		cvCircle(map_image, cvPoint(cpos, 175), 33, mainColor, -1);
		cvCircle(map_image, cvPoint(lpos, 175), 33, mainColor, -1);
		int x;
		switch (m_firstIndex) {
		case 1:
			x = rpos - 5 * _textsize / 2;
			text.putText(map_image, "[������ɭ��]", cvPoint(x, 240), white);
			break;
		case 2:
			x = cpos - 7 * _textsize / 2;
			text.putText(map_image, "[�ص��߹���ɭ��]", cvPoint(x, 240), white);
			break;
		case 3:
			x = lpos - 6 * _textsize / 2;
			text.putText(map_image, "[�뿪�������]", cvPoint(x, 240), white);
			break;
		default:break;
		}
		cvShowImage("ɭ�ַ���", map_image);
		int k = cvWaitKey(10);
		//��������D
		if (k == 100) {
			m_firstIndex %= 3;
			m_firstIndex++;
		}
		//��������A
		else if (k == 97) {
			m_firstIndex--;
			m_firstIndex = m_firstIndex == 0 ? 3 : m_firstIndex;
		}
		//��������enter����space����ʱ��
		else if (k == 13 || k == 32) {
			//�ݴ浱ǰ����ͼ��
			//�ı�Բ����ɫ
			if (m_firstIndex == 1) {
				cvCircle(map_image, cvPoint(rpos, 175), 33, brightMainColor, -1);
				cvCircle(map_image, cvPoint(cpos, 175), 33, blackMainColor, -1);
				cvCircle(map_image, cvPoint(lpos, 175), 33, blackMainColor, -1);
			}
			else if (m_firstIndex == 2) {
				cvCircle(map_image, cvPoint(rpos, 175), 33, blackMainColor, -1);
				cvCircle(map_image, cvPoint(cpos, 175), 33, brightMainColor, -1);
				cvCircle(map_image, cvPoint(lpos, 175), 33, blackMainColor, -1);
			}
			map_image_backup_highstage = cvCloneImage(map_image);

			//ѡ����[������ɭ��]
			if (m_firstIndex == 1) {
				//������ɭ��
				int textFocus = 0;
				int recWidth = 300, recHeight = 30;
				char str[5][20];
				memset(str, '\0', sizeof(str));
				text_notice.setShadingPre();
				while (true) {
					cvCopy(map_image_backup_highstage, map_image);
					switch (m_secondIndex) {
					case 1:
						text_notice.putShadingText(map_image, "���������ɭ�ֵ�����", cvPoint(calCenterX(NOTICETEXTSIZE, 10, m_width), 400),white, 50);
						break;
					case 2:
						text_notice.putShadingText(map_image, "������ֲ�������", cvPoint(calCenterX(NOTICETEXTSIZE, 8, m_width), 400), white, 50);
						break;
					case 3:
						text_notice.putShadingText(map_image, "������ʳ�⶯�������", cvPoint(calCenterX(NOTICETEXTSIZE, 10, m_width), 400), white, 50);
						break;
					case 4:
						text_notice.putShadingText(map_image, "������ʳ�ݶ��������", cvPoint(calCenterX(NOTICETEXTSIZE, 10, m_width), 400), white, 50);
						break;
					default:break;
					}
					int kk = cvWaitKey(10);
					int len = strlen(str[m_secondIndex]);
					//�������˸��ʱ
					if (kk == 8 && len > 0) {
						str[m_secondIndex][len - 1] = '\0';
					}
					//����space����enter��ʱ
					else if ((kk == 13 || kk == 32) && m_secondIndex <= 4) {
						if (m_secondIndex == 4) {		//ɭ����Ϣ��д��ϣ����Կ�ʼ����ɭ��
							strcpy(m_forestName, str[1]);
							m_plantNum = atoi(str[2]);
							m_carnivorousNum = atoi(str[3]);
							m_harmlessNum = atoi(str[4]);
							//��ʼ����ɭ��
							cvDestroyWindow("ɭ�ַ���");
							return;
						}
						m_secondIndex++;
					}
					//������esc��ʱ
					else if (kk == 27 && m_secondIndex >= 0) {
						if (m_secondIndex == 1)	break;
						m_secondIndex--;
					}
					//��������Ǵ�ӡ�ַ�ʱ	
					else if (kk >= 33 && kk <= 126 && len <= 20) {
						if (m_secondIndex > 1 && (kk < 48 || kk > 57))	continue;		//�����ʽ����:����������ʱֻ����������
						str[m_secondIndex][len] = kk;
						str[m_secondIndex][len + 1] = '\0';
					}
					//char tmp_str[25];		//��������������ϵģ�����ʵ�洢�ַ��������������ǣ���һ��������ǿ�û������'|'����
					//strcpy(tmp_str, str[m_secondIndex]);
					len = strlen(str[m_secondIndex]);
					//tmp_str[len + 1] = '\0', tmp_str[len] = '|';
					text.putText(map_image, str[m_secondIndex], cvPoint(calCenterX(NORMALTEXTSIZE / 2, len, m_width), 500), white);
					cvShowImage("ɭ�ַ���", map_image);
				}
			}
			else if (m_firstIndex == 2) {
				//������ǰ��ɭ��
				char forestName[25];
				memset(forestName, '\0', sizeof(forestName));
				int recWidth = 300, recHeight = 30;
				text_notice.setShadingPre();
				while (true) {
					cvCopy(map_image_backup_highstage, map_image);
					text_notice.putShadingText(map_image, "�������ִ�ɭ�ֵ�����", cvPoint(calCenterX(NOTICETEXTSIZE, 10, m_width), 400), white, 50);
					int kk = cvWaitKey(10);
					int len = strlen(forestName);
					if (kk == 27)	break;
					else if ((kk >= 33 && kk <= 126) && len <= 20) {
						forestName[len] = kk;
						forestName[len + 1] = '\0';
					}
					else if (kk == 8 && len > 0) {
						forestName[len - 1] = '\0';
					}
					else if (kk == 13 || kk == 32) {
						//��ʼ���ɵ�ͼ
						strcpy(m_forestName, forestName);
						cvDestroyWindow("ɭ�ַ���");
						return;
					}
					text.putText(map_image, forestName, cvPoint(calCenterX(NORMALTEXTSIZE / 2, len, m_width), 500), white);
					cvShowImage("ɭ�ַ���", map_image);
				}
			}
			else	exit(0);
		}
		//��������esc����ʱ��
		else if (k == 27) {
			exit(0);
		}
	}

}

int UI::calCenterX(int text_size, int text_num, int win_width) {
	return (win_width - (text_size * text_num)) / 2;
}
