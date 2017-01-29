// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#ifndef __STADAFX_H__
#define __STADAFX_H__

#include <stdio.h>
#include <tchar.h>
#include <iostream>      
#include <opencv2/opencv.hpp>
#include <ft2build.h>  
#include "CvxText.h"
#include FT_FREETYPE_H  
#include <string.h>
#include <time.h>
#include <vector>
#include "cJSON.h"
using namespace std;

#define PLANT_IMAGE_COUNT 4
#define DEAD_IMAGE_COUNT 4
#define ANIMAL_MOVEIMG_COUNT 16
#define MAP_IMG_COUNT 1
#define MAP_X_SIZE 54
#define MAP_Y_SIZE 30
#define GRID_SIZE 30
#define GRASS 0

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define GRASS 0
#define CANIVOROUS 1
#define HARMLESS 2
#define PLANT 3


//UI����
#define NOTICETEXTSIZE 40
#define NORMALTEXTSIZE 24
#define TITLETEXTSIZE 38

#define INF 0x3f3f3f

#endif


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
