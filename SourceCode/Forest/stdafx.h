// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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


//UI部分
#define NOTICETEXTSIZE 40
#define NORMALTEXTSIZE 24
#define TITLETEXTSIZE 38

#define INF 0x3f3f3f

#endif


// TODO:  在此处引用程序需要的其他头文件
