#include "stdafx.h"
#include "Resources.h"


Resources::Resources()
{
	InitResources();
}


Resources::~Resources()
{
	ReleaseResources();
}

void Resources::ReleaseResources()
{
	for (int i = 0; i < MAP_IMG_COUNT; i++)
		cvReleaseImage(m_mapImage + i);
	for (int i = 0; i < ANIMAL_MOVEIMG_COUNT; i++)
		cvReleaseImage(m_carnivorousImage + i);
	for (int i = 0; i < ANIMAL_MOVEIMG_COUNT; i++)
		cvReleaseImage(m_plantImage + i);
	for (int i = 0; i < PLANT_IMAGE_COUNT; i++) {
		cvReleaseImage(m_plantImage + i);
	}
	for (int i = 0; i < DEAD_IMAGE_COUNT; i++) {
		cvReleaseImage(m_harmlessDeadImage + i);
	}
}

void Resources::InitResources()
{
	char filename[80];
	for (int i = 0; i < MAP_IMG_COUNT; i++) {
		sprintf_s(filename, "./img/map/%d.jpg", i);
		m_mapImage[i] = cvLoadImage(filename);
	}	

	for (int i = 0; i < ANIMAL_MOVEIMG_COUNT; i++) {
		sprintf_s(filename, "./img/carnivorous/%d.png", i);
		m_carnivorousImage[i] = cvLoadImage(filename);
	}

	for (int i = 0; i < ANIMAL_MOVEIMG_COUNT; i++) {
		sprintf_s(filename, "./img/harmless/%d.png", i);
		m_harmlessImage[i] = cvLoadImage(filename);
	}
		
	for (int i = 0; i < PLANT_IMAGE_COUNT; i++) {
		sprintf_s(filename, "./img/grass/%d.jpg", i);
		m_plantImage[i] = cvLoadImage(filename);
	}

	for (int i = 0; i < DEAD_IMAGE_COUNT; i++) {
		sprintf_s(filename, "./img/dead/2_%d.jpg", i);
		m_harmlessDeadImage[i] = cvLoadImage(filename);
	}
}