#include "stdafx.h"
#include "Manage.h"



Manage::Manage()
{
	m_times = 0;					//��ʱ����0
	m_displayinfo_swi = false;
}


Manage::~Manage()
{
	fclose(fp);
	fclose(fp_cur);
}

void Manage::DataInit() {
	srand((unsigned)time(NULL));			//�������������
	cvNamedWindow(m_ui.m_forestName, CV_WINDOW_AUTOSIZE);		//�½����ڣ��û����ܸı��С��
	m_map.SetMapImage(m_resources.m_mapImage);

	CvSize tmp;								//��������
	tmp.width = MAP_X_SIZE * GRID_SIZE, tmp.height = MAP_Y_SIZE * GRID_SIZE;
	m_Bg = cvCreateImage(tmp, IPL_DEPTH_8U, 3);
	m_map.DrawMap(m_Bg);					//����������ͼ
	m_showBg = cvCloneImage(m_Bg);

	if (m_ui.IsCreatNewMap()) {
		//�����µĵ�ͼ��Ϣ���������ݳ�ʼ��

		for (int i = 0; i < m_ui.GetPlantNum(); i++) {		//�����������ֲ��
			int posx, posy;
			posx = rand() % MAP_X_SIZE;
			posy = rand() % MAP_Y_SIZE;
			int imgIndex = rand() % 4;
			int heat = rand() % 10 + 25;
			m_plant.push_back(new Plant(posx, posy, heat, 120, m_resources.m_plantImage, imgIndex));
			m_plant[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_plant[i]->GetPosX(), m_plant[i]->GetPosY(), m_plant[i]->GetAge(), m_plant[i]->GetHeat());
		}
		for (int i = 0; i < m_ui.GetCarnivorousNum(); i++) {	//�����������ʳ�⶯��
			int posx, posy;
			posx = rand() % MAP_X_SIZE;
			posy = rand() % MAP_Y_SIZE;
			int sv = rand() % 2 + 3;
			int av = sv + 2;
			int hungry = rand() % 10 + 60;
			m_wolf.push_back(new Carnivorous(posx, posy, sv, av, 2, 8, hungry, hungry * 0.2, 60, m_resources.m_carnivorousImage));
		}
		for (int i = 0; i < m_ui.GetHarmlessNum(); i++) {		//�����������ֲʳ����
			int posx, posy;
			posx = rand() % MAP_X_SIZE;
			posy = rand() % MAP_Y_SIZE;
			int sv = rand() % 2 + 2;
			int av = sv + 2;
			int hungry = rand() % 10 + 90;
			m_rabit.push_back(new Harmless(posx, posy, sv, av, 4, 8, hungry, hungry * 0.4, 80, m_resources.m_harmlessImage));
		}

		cvShowImage(m_ui.m_forestName, m_showBg);

		//���ļ�
		char name[80];
		sprintf_s(name, "data//%s_info.txt", m_ui.m_forestName);
		if ((fp = fopen(name, "w+")) == NULL) {
			cout << "open file failed!" << endl;
		}

	}
	else {
		//��JSON�ļ��ж�ȡ���е�ɭ����Ϣ��
		int i = 1;
		char name[80];
		sprintf_s(name, "data//%s_save.json", m_ui.m_forestName);
		cJSON *jsonArr = Tools::GetJsonArray(name);			//ʹ��TOOLS���еķ���
		int arrLen = cJSON_GetArraySize(jsonArr);
		int carNum = Tools::GetJSONNumberValue(jsonArr, arrLen - 1, "CarNumber");
		int plaNum = Tools::GetJSONNumberValue(jsonArr, arrLen - 1, "PlaNumber");
		int harNum = Tools::GetJSONNumberValue(jsonArr, arrLen - 1, "HarNumber");
		
		for (i; i <= carNum; i++) {
			m_wolf.push_back(new Carnivorous(Tools::GetJSONNumberValue(jsonArr, i - 1, "Age"), Tools::GetJSONNumberValue(jsonArr, i - 1, "Life"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "Heat"), Tools::GetJSONNumberValue(jsonArr, i - 1, "PosX"), 
				Tools::GetJSONNumberValue(jsonArr, i - 1, "PosY"), Tools::GetJSONNumberValue(jsonArr, i - 1, "StaticView"), 
				Tools::GetJSONNumberValue(jsonArr, i - 1, "ActiveView"), Tools::GetJSONNumberValue(jsonArr, i - 1, "IsStatic"), 
				Tools::GetJSONNumberValue(jsonArr, i - 1, "IsMove"), Tools::GetJSONNumberValue(jsonArr, i - 1, "StaticSpeed"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "ActiveSpeed"), Tools::GetJSONNumberValue(jsonArr, i - 1, "ImgID"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "Hungry"), Tools::GetJSONNumberValue(jsonArr, i - 1, "MoveDir"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "IsCollision"), Tools::GetJSONNumberValue(jsonArr, i - 1, "MoveDis"), 
				m_resources.m_carnivorousImage, Tools::GetJSONNumberValue(jsonArr, i - 1, "MaxEatTime"), Tools::GetJSONNumberValue(jsonArr, i - 1, "NowEatTime")));
		}
		for (i; i <= carNum + harNum; i++) {
			m_rabit.push_back(new Harmless(Tools::GetJSONNumberValue(jsonArr, i - 1, "Age"), Tools::GetJSONNumberValue(jsonArr, i - 1, "Life"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "Heat"), Tools::GetJSONNumberValue(jsonArr, i - 1, "PosX"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "PosY"), Tools::GetJSONNumberValue(jsonArr, i - 1, "StaticView"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "ActiveView"), Tools::GetJSONNumberValue(jsonArr, i - 1, "IsStatic"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "IsMove"), Tools::GetJSONNumberValue(jsonArr, i - 1, "StaticSpeed"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "ActiveSpeed"), Tools::GetJSONNumberValue(jsonArr, i - 1, "ImgID"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "Hungry"), Tools::GetJSONNumberValue(jsonArr, i - 1, "MoveDir"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "IsCollision"), Tools::GetJSONNumberValue(jsonArr, i - 1, "MoveDis"),
				m_resources.m_harmlessImage, Tools::GetJSONNumberValue(jsonArr, i - 1, "MaxEatTime"), Tools::GetJSONNumberValue(jsonArr, i - 1, "NowEatTime")));
		}
		for (i; i <= carNum + harNum + plaNum; i++) {
			int posx = Tools::GetJSONNumberValue(jsonArr, i - 1, "PosX");
			int posy = Tools::GetJSONNumberValue(jsonArr, i - 1, "PosY");
			m_plant.push_back(new Plant(Tools::GetJSONNumberValue(jsonArr, i - 1, "Age"), Tools::GetJSONNumberValue(jsonArr, i - 1, "Life"),
				Tools::GetJSONNumberValue(jsonArr, i - 1, "Heat"), posx, posy, m_resources.m_plantImage, Tools::GetJSONNumberValue(jsonArr, i - 1, "imgIndex")));
			m_plant[m_plant.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, posx, posy, Tools::GetJSONNumberValue(jsonArr, i - 1, "Age"), Tools::GetJSONNumberValue(jsonArr, i - 1, "Heat"));
		}

		m_times = Tools::GetJSONNumberValue(jsonArr, i - 1, "Times");

		cvShowImage(m_ui.m_forestName, m_showBg);

		//���ļ�
		memset(name, 0, sizeof(name));
		sprintf_s(name, "data//%s_info.txt", m_ui.m_forestName);
		if ((fp = fopen(name, "w+")) == NULL) {
			cout << "open file failed!" << endl;
		}
	}
}	

/*
ÿ֡�Ե�ͼ�еĶ������״̬�ĸ���
*/
void Manage::LivingUpdate() {
	TargetSearch();
	CreatureIllusionCheck();
	if (!m_plant.empty())	PlantUpdate();
	if(!m_wolf.empty())		CarnivorousUpdate();
	if(!m_rabit.empty())	HarmlessUpdate();
}

//ʳ�⶯��״̬�ĸ���
void Manage::CarnivorousUpdate() {
	vector<Carnivorous *>::iterator iter;
	
	int heat, age, life;
	heat = age = life = 0;

	//ɾ�����������
	iter = m_wolf.begin();
	while (iter != m_wolf.end()) {
		if ((*iter)->IsNeedClear()) {
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == CANIVOROUS)					//Ҫ��֤������֮ǰ�����ͼ��Ϣ����ʳ�⶯�������ǲ���������ΪĬ��̬
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), 0);		//��Ҫ���ǰѵ�ͼ��Ϣ��������
			delete *iter;
			iter = m_wolf.erase(iter);
		}
		else {
			heat = max(heat, (*iter)->GetEnergy());
			age = max(age, (*iter)->GetAge());
			life = max(life, (*iter)->GetLife());

			//�麯������Խ�ԣ���һ�������������д��붼һ����ֱ��ճ��Ҳ�����д� 
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == GRASS)
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), (*iter)->GetAge(), (*iter)->GetHeat(), (*iter)->GetEnergy(), (*iter)->GetNowEatTime(), (*iter)->isFindTarget());
			iter++;
		}
	}

	m_carnivorousMaxCount.age = age, m_carnivorousMaxCount.life = life, m_carnivorousMaxCount.energy = heat * 10 / 2;

	int sizeN = m_wolf.size();
	for (int i = 0; i < sizeN; i++) {
		//�������
		if (0 == m_times % 20) {
			m_wolf[i]->Old();
		}
		if (m_wolf[i]->isTooOld()) {
			m_wolf[i]->SetLiveType(false);
		}

		//�����ȸ���
		if (0 == m_times % 20) {
			if (m_wolf[i]->isStatic()) m_wolf[i]->ChangeEnergy(-1);			//��ǰ�Ƿ��ڻ�Ծ״̬
			else m_wolf[i]->ChangeEnergy(-3);
		}

		if (m_wolf[i]->GetEnergy() <= 0) {
			m_wolf[i]->SetLiveType(false);
		}
		//��ʳ״̬����
		if (0 == m_times % 900)	m_wolf[i]->InitEatTime();

		//��ֳ
		if (0 == m_times % 600 && m_times != 0) {
			int dir = rand() % 4 + 1;					//��������������ԭ����ķ���
			int x = m_wolf[i]->GetPosX(), y = m_wolf[i]->GetPosY();
			switch (dir) {
			case 1:
				if (x + 1 >= MAP_X_SIZE)	x = 0;
				else x++;
				m_wolf.push_back(new Carnivorous(x, y, m_wolf[i]->GetStaticViewRange(), m_wolf[i]->GetStaticSpeed(), 
					m_wolf[i]->GetStaticSpeed(), m_wolf[i]->GetActiveSpeed(), m_wolf[i]->GetHeat() * 10 / 2 - 5 + rand() % 10,
					m_wolf[i]->GetHeat(), m_wolf[i]->GetLife(), m_resources.m_carnivorousImage));
				if (m_map.m_mapInfo[m_wolf[m_wolf.size() - 1]->GetPosY()][m_wolf[m_wolf.size() - 1]->GetPosX()] == GRASS)
					m_wolf[m_wolf.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_wolf[m_wolf.size() - 1]->GetPosX(), m_wolf[m_wolf.size() - 1]->GetPosY(), m_wolf[m_wolf.size() - 1]->GetAge(), m_wolf[m_wolf.size() - 1]->GetHeat(), m_wolf[m_wolf.size() - 1]->GetEnergy(), m_wolf[m_wolf.size() - 1]->GetNowEatTime(), m_wolf[m_wolf.size() - 1]->isFindTarget());
				break;
			case 2:
				if (x - 1 < 0)	x = MAP_X_SIZE - 1;
				else x--;
				m_wolf.push_back(new Carnivorous(x, y, m_wolf[i]->GetStaticViewRange(), m_wolf[i]->GetStaticSpeed(),
					m_wolf[i]->GetStaticSpeed(), m_wolf[i]->GetActiveSpeed(), m_wolf[i]->GetHeat() * 10 / 2 - 5 + rand() % 10,
					m_wolf[i]->GetHeat(), m_wolf[i]->GetLife(), m_resources.m_carnivorousImage));
				if (m_map.m_mapInfo[m_wolf[m_wolf.size() - 1]->GetPosY()][m_wolf[m_wolf.size() - 1]->GetPosX()] == GRASS)
					m_wolf[m_wolf.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_wolf[m_wolf.size() - 1]->GetPosX(), m_wolf[m_wolf.size() - 1]->GetPosY(), m_wolf[m_wolf.size() - 1]->GetAge(), m_wolf[m_wolf.size() - 1]->GetHeat(), m_wolf[m_wolf.size() - 1]->GetEnergy(), m_wolf[m_wolf.size() - 1]->GetNowEatTime(), m_wolf[m_wolf.size() - 1]->isFindTarget());
				break;
			case 3:
				if (y - 1 < 0)	y = MAP_Y_SIZE - 1;
				else y--;
				m_wolf.push_back(new Carnivorous(x, y, m_wolf[i]->GetStaticViewRange(), m_wolf[i]->GetStaticSpeed(), 
					m_wolf[i]->GetStaticSpeed(), m_wolf[i]->GetActiveSpeed(), m_wolf[i]->GetHeat() * 10 / 2 - 5 + rand() % 10,
					m_wolf[i]->GetHeat(), m_wolf[i]->GetLife(), m_resources.m_carnivorousImage));
				if (m_map.m_mapInfo[m_wolf[m_wolf.size() - 1]->GetPosY()][m_wolf[m_wolf.size() - 1]->GetPosX()] == GRASS)
					m_wolf[m_wolf.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_wolf[m_wolf.size() - 1]->GetPosX(), m_wolf[m_wolf.size() - 1]->GetPosY(), m_wolf[m_wolf.size() - 1]->GetAge(), m_wolf[m_wolf.size() - 1]->GetHeat(), m_wolf[m_wolf.size() - 1]->GetEnergy(), m_wolf[m_wolf.size() - 1]->GetNowEatTime(), m_wolf[m_wolf.size() - 1]->isFindTarget());
				break;
			case 4:
				if (y + 1 >= MAP_Y_SIZE)	y = 0;
				else y++;
				m_wolf.push_back(new Carnivorous(x, y, m_wolf[i]->GetStaticViewRange(), m_wolf[i]->GetStaticSpeed(), 
					m_wolf[i]->GetStaticSpeed(), m_wolf[i]->GetActiveSpeed(), m_wolf[i]->GetHeat() * 10 / 2 - 5 + rand() % 10,
					m_wolf[i]->GetHeat(), m_wolf[i]->GetLife(), m_resources.m_carnivorousImage));
				if (m_map.m_mapInfo[m_wolf[m_wolf.size() - 1]->GetPosY()][m_wolf[m_wolf.size() - 1]->GetPosX()] == GRASS)
					m_wolf[m_wolf.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_wolf[m_wolf.size() - 1]->GetPosX(), m_wolf[m_wolf.size() - 1]->GetPosY(), m_wolf[m_wolf.size() - 1]->GetAge(), m_wolf[m_wolf.size() - 1]->GetHeat(), m_wolf[m_wolf.size() - 1]->GetEnergy(), m_wolf[m_wolf.size() - 1]->GetNowEatTime(), m_wolf[m_wolf.size() - 1]->isFindTarget());
				break;
			default:break;
			}
		}
		//λ�ø���
		if (m_map.m_mapInfo[m_wolf[i]->GetPosY()][m_wolf[i]->GetPosX()] == CANIVOROUS)
			m_wolf[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_wolf[i]->GetPosX(), m_wolf[i]->GetPosY(), 0);
		m_wolf[i]->Chase(m_Bg);
		if (m_map.m_mapInfo[m_wolf[i]->GetPosY()][m_wolf[i]->GetPosX()] == GRASS)
			m_wolf[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_wolf[i]->GetPosX(), m_wolf[i]->GetPosY(), m_wolf[i]->GetAge(), m_wolf[i]->GetHeat(), m_wolf[i]->GetEnergy(), m_wolf[i]->GetNowEatTime(), m_wolf[i]->isFindTarget());
		m_wolf[i]->Draw(m_showBg);
	}
}

void Manage::HarmlessUpdate() {
	vector<Harmless *>::iterator iter;

	int heat, age, life;
	heat = age = life = 0;

	//ɾ�����������
	iter = m_rabit.begin();
	while (iter != m_rabit.end()) {
		if ((*iter)->IsNeedClear()) {
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == HARMLESS)			//��ʳ�⶯�����д���һ��ԭ��
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), 0);	//�޸������ͼ
			m_deadEffective.push_back(new DeadEffective(m_resources.m_harmlessDeadImage[(*iter)->GetDirection() - 1], (*iter)->GetDrawPosX(), (*iter)->GetDrawPosY()));		//����Ч��

			delete *iter;
			iter = m_rabit.erase(iter);

		}
		else {
			heat = max(heat, (*iter)->GetEnergy());
			age = max(age, (*iter)->GetAge());
			life = max(life, (*iter)->GetLife());

			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == GRASS)
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), (*iter)->GetAge(), (*iter)->GetHeat(), (*iter)->GetEnergy(), (*iter)->GetNowEatTime(), (*iter)->isFindTarget(), (*iter)->IsFlee());
			iter++;
		}
	}
	m_harmlessMaxCount.age = age;
	m_harmlessMaxCount.life = life;
	m_harmlessMaxCount.energy = heat * 10 / 4;
	
	int sizeN = m_rabit.size();
	for (int i = 0; i < sizeN; i++) {
		//�������
		if (0 == m_times % 20) {
			m_rabit[i]->Old();
		}
		if (m_rabit[i]->isTooOld()) {
			m_rabit[i]->SetLiveType(false);
		}

		//�����ȸ���
		if (0 == m_times % 20) {
			if (m_rabit[i]->isStatic()) m_rabit[i]->ChangeEnergy(-1);
			else m_rabit[i]->ChangeEnergy(-2);
		}
		if (m_rabit[i]->GetEnergy() <= 0) {
			m_rabit[i]->SetLiveType(false);
		}
		//��ʳ״̬����
		if (0 == m_times % 900)	m_rabit[i]->InitEatTime();

		//��ֳ
		if (0 == m_times % 600 && m_times != 0) {
			int dir = rand() % 4 + 1;
			int x = m_rabit[i]->GetPosX(), y = m_rabit[i]->GetPosY();
			switch (dir) {
			case 1:
				if (x + 1 >= MAP_X_SIZE)	x = 0;
				else x++;
				m_rabit.push_back(new Harmless(x, y, m_rabit[i]->GetStaticViewRange(), m_rabit[i]->GetStaticSpeed(), 
					m_rabit[i]->GetStaticSpeed(), m_rabit[i]->GetActiveSpeed(), m_rabit[i]->GetHeat() * 10 / 4 + -3 + rand() % 3,
					m_rabit[i]->GetHeat(), m_rabit[i]->GetLife(), m_resources.m_harmlessImage));
				if(m_map.m_mapInfo[m_rabit[m_rabit.size() - 1]->GetPosY()][m_rabit[m_rabit.size() - 1]->GetPosX()] == GRASS)
					m_rabit[m_rabit.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[m_rabit.size() - 1]->GetPosX(), m_rabit[m_rabit.size() - 1]->GetPosY(), m_rabit[m_rabit.size() - 1]->GetAge(), m_rabit[m_rabit.size() - 1]->GetHeat(), m_rabit[m_rabit.size() - 1]->GetEnergy(), m_rabit[m_rabit.size() - 1]->GetNowEatTime(), m_rabit[m_rabit.size() - 1]->isFindTarget(), (*iter)->IsFlee());
				break;
			case 2:
				if (x - 1 < 0)	x = MAP_X_SIZE - 1;
				else x--;
				m_rabit.push_back(new Harmless(x, y, m_rabit[i]->GetStaticViewRange(), m_rabit[i]->GetStaticSpeed(), 
					m_rabit[i]->GetStaticSpeed(), m_rabit[i]->GetActiveSpeed(), m_rabit[i]->GetHeat() * 10 / 4 + -3 + rand() % 3,
					m_rabit[i]->GetHeat(), m_rabit[i]->GetLife(), m_resources.m_harmlessImage));
				if (m_map.m_mapInfo[m_rabit[m_rabit.size() - 1]->GetPosY()][m_rabit[m_rabit.size() - 1]->GetPosX()] == GRASS)
					m_rabit[m_rabit.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[m_rabit.size() - 1]->GetPosX(), m_rabit[m_rabit.size() - 1]->GetPosY(), m_rabit[m_rabit.size() - 1]->GetAge(), m_rabit[m_rabit.size() - 1]->GetHeat(), m_rabit[m_rabit.size() - 1]->GetEnergy(), m_rabit[m_rabit.size() - 1]->GetNowEatTime(), m_rabit[m_rabit.size() - 1]->isFindTarget(), (*iter)->IsFlee());
				break;
			case 3:
				if (y - 1 < 0)	y = MAP_Y_SIZE - 1;
				else y--;
				m_rabit.push_back(new Harmless(x, y, m_rabit[i]->GetStaticViewRange(), m_rabit[i]->GetStaticSpeed(),
					m_rabit[i]->GetStaticSpeed(), m_rabit[i]->GetActiveSpeed(), m_rabit[i]->GetHeat() * 10 / 4 + - 3 + rand() % 3,
					m_rabit[i]->GetHeat(), m_rabit[i]->GetLife(), m_resources.m_harmlessImage));
				if (m_map.m_mapInfo[m_rabit[m_rabit.size() - 1]->GetPosY()][m_rabit[m_rabit.size() - 1]->GetPosX()] == GRASS)
					m_rabit[m_rabit.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[m_rabit.size() - 1]->GetPosX(), m_rabit[m_rabit.size() - 1]->GetPosY(), m_rabit[m_rabit.size() - 1]->GetAge(), m_rabit[m_rabit.size() - 1]->GetHeat(), m_rabit[m_rabit.size() - 1]->GetEnergy(), m_rabit[m_rabit.size() - 1]->GetNowEatTime(), m_rabit[m_rabit.size() - 1]->isFindTarget(), (*iter)->IsFlee());
				break;
			case 4:
				if (y + 1 >= MAP_Y_SIZE)	y = 0;
				else y++;
				m_rabit.push_back(new Harmless(x, y, m_rabit[i]->GetStaticViewRange(), m_rabit[i]->GetStaticSpeed(), 
					m_rabit[i]->GetStaticSpeed(), m_rabit[i]->GetActiveSpeed(), m_rabit[i]->GetHeat() * 10 / 4 + -3 + rand() % 3,
					m_rabit[i]->GetHeat(), m_rabit[i]->GetLife(), m_resources.m_harmlessImage));
				if (m_map.m_mapInfo[m_rabit[m_rabit.size() - 1]->GetPosY()][m_rabit[m_rabit.size() - 1]->GetPosX()] == GRASS)
					m_rabit[m_rabit.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[m_rabit.size() - 1]->GetPosX(), m_rabit[m_rabit.size() - 1]->GetPosY(), m_rabit[m_rabit.size() - 1]->GetAge(), m_rabit[m_rabit.size() - 1]->GetHeat(), m_rabit[m_rabit.size() - 1]->GetEnergy(), m_rabit[m_rabit.size() - 1]->GetNowEatTime(), m_rabit[m_rabit.size() - 1]->isFindTarget(), m_rabit[m_rabit.size() - 1]->IsFlee());
				break;
			default:break;
			}
		}
		//λ�ø���
		if (m_map.m_mapInfo[m_rabit[i]->GetPosY()][m_rabit[i]->GetPosX()] == HARMLESS)
			m_rabit[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[i]->GetPosX(), m_rabit[i]->GetPosY(), 0);
		if (m_rabit[i]->IsFlee())
			m_rabit[i]->Flee(m_Bg);
		else
			m_rabit[i]->Chase(m_Bg);
		if(m_map.m_mapInfo[m_rabit[i]->GetPosY()][m_rabit[i]->GetPosX()] == GRASS)
			m_rabit[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[i]->GetPosX(), m_rabit[i]->GetPosY(), m_rabit[i]->GetAge(), m_rabit[i]->GetHeat(), m_rabit[i]->GetEnergy(), m_rabit[i]->GetNowEatTime(), m_rabit[i]->isFindTarget(), m_rabit[i]->IsFlee());	//��Ϊmapinfo����ĵ�ͼ��Ϣֻ��һ�أ�����д���ݵ�ʱ���ֱ�Ӹ��ǵ�ԭ���ݣ����Ե�harmless����plant��ʱ��mapinfo��plant�ı�־�ͱ���д�ˣ����Ҳ��Ḵԭ������ֱ��delete��plant���У�����ʵ�ּ�PlantUpdate������
		m_rabit[i]->Draw(m_showBg);
	}
}

void Manage::PlantUpdate() {
	vector<Plant *>::iterator iter;

	int heat, age, life;
	heat = age = life = 0;

	iter = m_plant.begin();
	while (iter != m_plant.end()) {
		if ((*iter)->IsNeedClear() || m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] != PLANT) {
			if(m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == PLANT)
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), 0);
			delete *iter;
			iter = m_plant.erase(iter);
		}
		else {
			age = max(age, (*iter)->GetAge());
			life = max(life, (*iter)->GetLife());
			heat = max(heat, (*iter)->GetHeat());
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == PLANT)
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), (*iter)->GetAge(), (*iter)->GetHeat());
			iter++;
		}
	}

	m_plantMaxCount.age = age, m_plantMaxCount.life = life, m_plantMaxCount.energy = heat;
	
	int sizeN = m_plant.size();
	for (int i = 0; i < sizeN; i++) {
		//�������
		if (0 == m_times % 20) {
			m_plant[i]->Old();
		}
		if (m_plant[i]->isTooOld()) {
			m_plant[i]->SetLiveType(false);
		}

		//��ֳ
		if (0 == m_times % 1500 && m_times != 0) {
			int dir = rand() % 4 + 1;
			int x = m_plant[i]->GetPosX(), y = m_plant[i]->GetPosY();
			switch (dir) {
			case 1:
				if (x + 1 >= MAP_X_SIZE)	x = 0;
				else x++;
				m_plant.push_back(new Plant(x, y, m_plant[i]->GetHeat() - 2 + 4 , 60, m_resources.m_plantImage, m_plant[i]->GetImgIndex()));
				if(m_map.m_mapInfo[m_plant[m_plant.size() - 1]->GetPosY()][m_plant[m_plant.size() - 1]->GetPosX()] == GRASS)
					m_plant[m_plant.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_plant[m_plant.size() - 1]->GetPosX(), m_plant[m_plant.size() - 1]->GetPosY(), m_plant[m_plant.size() - 1]->GetAge(), m_plant[m_plant.size() - 1]->GetHeat());
				break;
			case 2:
				if (x - 1 < 0)	x = MAP_X_SIZE - 1;
				else x--;
				m_plant.push_back(new Plant(x, y, m_plant[i]->GetHeat() - 2 + 4, 60, m_resources.m_plantImage, m_plant[i]->GetImgIndex()));
				if (m_map.m_mapInfo[m_plant[m_plant.size() - 1]->GetPosY()][m_plant[m_plant.size() - 1]->GetPosX()] == GRASS)
					m_plant[m_plant.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_plant[m_plant.size() - 1]->GetPosX(), m_plant[m_plant.size() - 1]->GetPosY(), m_plant[m_plant.size() - 1]->GetAge(), m_plant[m_plant.size() - 1]->GetHeat());
				break;
			case 3:
				if (y - 1 < 0)	y = MAP_Y_SIZE - 1;
				else y--;
				m_plant.push_back(new Plant(x, y, m_plant[i]->GetHeat() - 2 + 4, 60, m_resources.m_plantImage, m_plant[i]->GetImgIndex()));
				if (m_map.m_mapInfo[m_plant[m_plant.size() - 1]->GetPosY()][m_plant[m_plant.size() - 1]->GetPosX()] == GRASS)
					m_plant[m_plant.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_plant[m_plant.size() - 1]->GetPosX(), m_plant[m_plant.size() - 1]->GetPosY(), m_plant[m_plant.size() - 1]->GetAge(), m_plant[m_plant.size() - 1]->GetHeat());
				break;
			case 4:
				if (y + 1 >= MAP_Y_SIZE)	y = 0;
				else y++;
				m_plant.push_back(new Plant(x, y, m_plant[i]->GetHeat() - 2 + 4, 60, m_resources.m_plantImage, m_plant[i]->GetImgIndex()));
				if (m_map.m_mapInfo[m_plant[m_plant.size() - 1]->GetPosY()][m_plant[m_plant.size() - 1]->GetPosX()] == GRASS)
					m_plant[m_plant.size() - 1]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_plant[m_plant.size() - 1]->GetPosX(), m_plant[m_plant.size() - 1]->GetPosY(), m_plant[m_plant.size() - 1]->GetAge(), m_plant[m_plant.size() - 1]->GetHeat());
				break;
			default:break;
			}
		}

		m_plant[i]->Draw(m_showBg);
	}
}


/*
�жϵ�ͼ�еĶ����ܿ���Ŀ��
*/
void Manage::TargetSearch() {
	int minDis, dis;
	int posx, posy;
	int range;
	int x, y;
	vector<Carnivorous *>::iterator iter1;
	vector<Harmless *>::iterator iter2;
	iter1 = m_wolf.begin();
	iter2 = m_rabit.begin();
	
	//ʳ�⶯�￪ʼ����Ұ��Χ����ѰĿ��
	while (iter1 != m_wolf.end()) {
		//����Ա��˲��Ҽ����Ȳ���̫�ͣ���ô�Ͳ�������Ŀ����
		if ((*iter1)->GetMaxEatTime() <= (*iter1)->GetNowEatTime() &&  (*iter1)->GetEnergy() >= (*iter1)->GetHeat()) {
			(*iter1)->SetFindTarget(false);
			(*iter1)->SetTargetPos(-1, -1);
			(*iter1)->SetisActive(false);
			iter1++;
			continue;
		}

		minDis = INF;
		if (!(*iter1)->isFindTarget()) {
			posx = (*iter1)->GetPosX(), posy = (*iter1)->GetPosY();
			range = (*iter1)->GetStaticViewRange();
			//�ڼ�¼��ͼ��Ϣ��mapinfo[][]�а���������
			for (int i = posy - range; i <= posy + range; i++) {
				for (int j = posx - range; j <= posx + range; j++) {
					x = j, y = i;
					//��ԵԽ�磬����Ļ��һ��
					if (y < 0)	y += MAP_Y_SIZE;
					if (y >= MAP_Y_SIZE)	y -= MAP_Y_SIZE;
					if (x < 0)	x += MAP_X_SIZE;
					if (x >= MAP_X_SIZE)	x -= MAP_X_SIZE;
					if (m_map.m_mapInfo[y][x] == HARMLESS) {
						dis = abs(posx - i) + abs(posy - j);
						if (dis < minDis) {
							minDis = dis;
							(*iter1)->SetFindTarget(true);
							(*iter1)->SetTargetPos(j, i);
							(*iter1)->SetisActive(true);
						}
					}
				}
			}
		}
		else {
			posx = (*iter1)->GetPosX(), posy = (*iter1)->GetPosY();
			range = (*iter1)->GetActiveViewRange();
			for (int i = posy - range; i <= posy + range; i++) {
				for (int j = posx - range; j <= posx + range; j++) {
					x = j, y = i;
					if (y < 0)	y += MAP_Y_SIZE;
					if (y >= MAP_Y_SIZE)	y -= MAP_Y_SIZE;
					if (x < 0)	x += MAP_X_SIZE;
					if (x >= MAP_X_SIZE)	x -= MAP_X_SIZE;
					if (m_map.m_mapInfo[y][x] == HARMLESS) {
						dis = abs(posx - i) + abs(posy - j);
						if (dis < minDis) {
							minDis = dis;
							(*iter1)->SetTargetPos(j, i);
						}
					}
				}
			}
		}
		if (minDis == INF) {
			(*iter1)->SetFindTarget(false);
			(*iter1)->SetTargetPos(-1, -1);
			(*iter1)->SetisActive(false);
		}

		iter1++;
	}

	//ʳ�ݶ��￪ʼ����Ұ��Χ����Ѱʳ��
	while (iter2 != m_rabit.end()) {
		//����Ա��˲��Ҽ����Ȳ���̫�ͣ���ô�Ͳ�������Ŀ����
		if ((*iter2)->GetMaxEatTime() <= (*iter2)->GetNowEatTime() &&  (*iter2)->GetEnergy() >= (*iter2)->GetHeat()) {
			(*iter2)->SetFindTarget(false);
			(*iter2)->SetTargetPos(-1, -1);
			(*iter2)->SetisActive(false);
			iter2++;
			continue;
		}

		minDis = INF;
		//��ʳ
		if (!(*iter2)->IsFlee()) {
			if (!(*iter2)->isFindTarget()) {
				posx = (*iter2)->GetPosX(), posy = (*iter2)->GetPosY();
				range = (*iter2)->GetActiveViewRange();
				for (int i = posy - range; i <= posy + range; i++) {
					for (int j = posx - range; j <= posx + range; j++) {
						x = j, y = i;
						if (y < 0)	y += MAP_Y_SIZE;
						if (y >= MAP_Y_SIZE)	y -= MAP_Y_SIZE;
						if (x < 0)	x += MAP_X_SIZE;
						if (x >= MAP_X_SIZE)	x -= MAP_X_SIZE;
						if (m_map.m_mapInfo[y][x] == PLANT) {
							dis = abs(posx - i) + abs(posy - j);
							if (dis < minDis) {
								minDis = dis;
								(*iter2)->SetFindTarget(true);
								(*iter2)->SetTargetPos(j, i);
								(*iter2)->SetisActive(true);
							}
						}
					}
				}
			}
			else {
				posx = (*iter2)->GetPosX(), posy = (*iter2)->GetPosY();
				range = (*iter2)->GetActiveViewRange();
				for (int i = posy - range; i <= posy + range; i++) {
					for (int j = posx - range; j <= posx + range; j++) {
						x = j, y = i;
						if (y < 0)	y += MAP_Y_SIZE;
						if (y >= MAP_Y_SIZE)	y -= MAP_Y_SIZE;
						if (x < 0)	x += MAP_X_SIZE;
						if (x >= MAP_X_SIZE)	x -= MAP_X_SIZE;
						if (m_map.m_mapInfo[y][x] == PLANT) {
							dis = abs(posx - i) + abs(posy - j);
							if (dis < minDis) {
								minDis = dis;
								(*iter2)->SetTargetPos(j, i);
							}
						}
					}
				}
			}
			if (minDis == INF) {
				(*iter2)->SetFindTarget(false);
				(*iter2)->SetTargetPos(-1, -1);
				(*iter2)->SetisActive(false);
			}
		}
		iter2++;
	}

	iter2 = m_rabit.begin();
	//ʳ�ݶ��￪ʼ����Ұ��Χ����Ѱ���
	while (iter2 != m_rabit.end()) {
		minDis = INF;
		if (!(*iter2)->isFindTarget()) {
			posx = (*iter2)->GetPosX(), posy = (*iter2)->GetPosY();
			range = (*iter2)->GetStaticViewRange();
			for (int i = posy - range; i <= posy + range; i++) {
				for (int j = posx - range; j <= posx + range; j++) {
					x = j, y = i;
					if (y < 0)	y += MAP_Y_SIZE;
					if (y >= MAP_Y_SIZE)	y -= MAP_Y_SIZE;
					if (x < 0)	x += MAP_X_SIZE;
					if (x >= MAP_X_SIZE)	x -= MAP_X_SIZE;
					if (m_map.m_mapInfo[y][x] == CANIVOROUS) {
						dis = abs(posx - i) + abs(posy - j);
						if (dis < minDis) {
							minDis = dis;
							(*iter2)->SetFindTarget(true);
							(*iter2)->SetTargetPos(j, i);
							(*iter2)->SetisActive(true);
							(*iter2)->SetIsFlee(true);
						}
					}
				}
			}
		}
		else if((*iter2)->IsFlee()){
			posx = (*iter2)->GetPosX(), posy = (*iter2)->GetPosY();
			range = (*iter2)->GetActiveViewRange();
			for (int i = posy - range; i <= posy + range; i++) {
				for (int j = posx - range; j <= posx + range; j++) {
					x = j, y = i;
					if (y < 0)	y += MAP_Y_SIZE;
					if (y >= MAP_Y_SIZE)	y -= MAP_Y_SIZE;
					if (x < 0)	x += MAP_X_SIZE;
					if (x >= MAP_X_SIZE)	x -= MAP_X_SIZE;
					if (m_map.m_mapInfo[y][x] == CANIVOROUS) {
						dis = abs(posx - i) + abs(posy - j);
						if (dis < minDis) {
							minDis = dis;
							(*iter2)->SetTargetPos(j, i);
						}
					}
				}
			}
		}
		if (minDis == INF && (*iter2)->IsFlee()) {
			(*iter2)->SetFindTarget(false);
			(*iter2)->SetTargetPos(-1, -1);
			(*iter2)->SetisActive(false);
			(*iter2)->SetIsFlee(false);
		}
		else if (minDis == INF)		(*iter2)->SetIsFlee(false);
		iter2++;
	}


}

void Manage::DeadEffectiveUpdate() {
	vector<DeadEffective *>::iterator iter;

	iter = m_deadEffective.begin();
	while (iter != m_deadEffective.end()) {
		if ((*iter)->CheckIsClear()) {
			delete *iter;
			iter = m_deadEffective.erase(iter);
		}
		else {
			(*iter)->Draw(m_showBg);
			(*iter)->TimeGoOn();
			iter++;
		}
	}
}

void Manage::ProcessInfoUpdate() {
	char str[80];
	sprintf_s(str, " ��%d�� ", m_times / 20 + 1);
	Tools::print(str, 40);
	Tools::print(str, 40, fp);

	//�����ǰֲ������������Է�ֵ
	sprintf_s(str, "> ֲ�");
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	sprintf_s(str, "	����: %d��", m_plant.size());
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	if (m_plant.size() > 0) {
		sprintf_s(str, "	�����ã� %d��", m_plantMaxCount.age);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	��׼������ %d��", m_plantMaxCount.life);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	���������� %dֵ", m_plantMaxCount.energy);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
	}

	//�����ǰʳ�⶯�������
	sprintf_s(str, "> ʳ�⶯�");
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	sprintf_s(str, "	����: %d��", m_wolf.size());
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	if (m_plant.size() > 0) {
		sprintf_s(str, "	�����ã� %d��", m_carnivorousMaxCount.age);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	��׼������ %d��", m_carnivorousMaxCount.life);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	��������� %dֵ", m_carnivorousMaxCount.energy);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
	}
	
	//�����ǰʳ�ݶ��������
	sprintf_s(str, "> ʳ�ݶ��");
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	sprintf_s(str, "	����: %d��", m_rabit.size());
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	if (m_plant.size() > 0) {
		sprintf_s(str, "	�����ã� %d��", m_harmlessMaxCount.age);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	��ȱ�׼������ %d��", m_harmlessMaxCount.life);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	������������ %dֵ", m_harmlessMaxCount.energy);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
	}

	fprintf(fp, "\n");
}

void Manage::SaveJSONData() {
	vector<Carnivorous *>::iterator iter1 = m_wolf.begin();
	vector<Harmless *>::iterator iter2 = m_rabit.begin();
	vector<Plant *>::iterator iter3 = m_plant.begin();

	cJSON *root, *obj;		//root��JSON���飬 obj��JSON����
	char *out;
	root = cJSON_CreateArray();
	int no = 1;			//��¼������ID
	char name[80];
	sprintf_s(name, "data//%s_save.json", m_ui.m_forestName);
	if (NULL == (fp_cur = fopen(name, "w+"))) {
		cout << "open file failed!" << endl;
	}

	//����ʳ�⶯���json����
	while (iter1 != m_wolf.end()) {
		cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
		//Ϊ�˱�֤�浵���������������ڵ����У��鿴������������ԣ�һһ���Ƿ�Ӧ����ӵ��浵�ļ��С�
		cJSON_AddNumberToObject(obj, "ID", no++);
		cJSON_AddNumberToObject(obj, "Species", CANIVOROUS);
		cJSON_AddNumberToObject(obj, "Age", (*iter1)->GetAge());
		cJSON_AddNumberToObject(obj, "Life", (*iter1)->GetLife());
		cJSON_AddNumberToObject(obj, "Heat", (*iter1)->GetHeat());
		cJSON_AddNumberToObject(obj, "PosX", (*iter1)->GetPosX());
		cJSON_AddNumberToObject(obj, "PosY", (*iter1)->GetPosY());
		//��Ϊÿ֡����ȫ������Ŀ��������Լ�¼������͹��ˣ����ü�¼Ŀ������/�Ƿ���Ŀ��
		cJSON_AddNumberToObject(obj, "StaticView", (*iter1)->GetStaticViewRange());
		cJSON_AddNumberToObject(obj, "ActiveView", (*iter1)->GetActiveViewRange());
		cJSON_AddNumberToObject(obj, "IsStatic", (*iter1)->isStatic());
		cJSON_AddNumberToObject(obj, "IsMove", (*iter1)->isMove());
		cJSON_AddNumberToObject(obj, "StaticSpeed", (*iter1)->GetStaticSpeed());
		cJSON_AddNumberToObject(obj, "ActiveSpeed", (*iter1)->GetActiveSpeed());
		cJSON_AddNumberToObject(obj, "ImgID", (*iter1)->GetImgID());
		cJSON_AddNumberToObject(obj, "Hungry", (*iter1)->GetEnergy());
		cJSON_AddNumberToObject(obj, "MoveDir", (*iter1)->GetMoveDir());
		cJSON_AddNumberToObject(obj, "IsCollision", (*iter1)->IsCollision());
		cJSON_AddNumberToObject(obj, "MoveDis", (*iter1)->GetMoveDis());
		cJSON_AddNumberToObject(obj, "MaxEatTime", (*iter1)->GetMaxEatTime());
		cJSON_AddNumberToObject(obj, "NowEatTime", (*iter1)->GetNowEatTime());
		iter1++;
	}

	//����ֲʳ�����json����
	while (iter2 != m_rabit.end()) {
		cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
		//Ϊ�˱�֤�浵���������������ڵ����У��鿴������������ԣ�һһ���Ƿ�Ӧ����ӵ��浵�ļ��С�
		cJSON_AddNumberToObject(obj, "ID", no++);
		cJSON_AddNumberToObject(obj, "Species", HARMLESS);
		cJSON_AddNumberToObject(obj, "Age", (*iter2)->GetAge());
		cJSON_AddNumberToObject(obj, "Life", (*iter2)->GetLife());
		cJSON_AddNumberToObject(obj, "Heat", (*iter2)->GetHeat());
		cJSON_AddNumberToObject(obj, "PosX", (*iter2)->GetPosX());
		cJSON_AddNumberToObject(obj, "PosY", (*iter2)->GetPosY());
		//��Ϊÿ֡����ȫ������Ŀ��������Լ�¼������͹��ˣ����ü�¼Ŀ������/�Ƿ���Ŀ��
		cJSON_AddNumberToObject(obj, "StaticView", (*iter2)->GetStaticViewRange());
		cJSON_AddNumberToObject(obj, "ActiveView", (*iter2)->GetActiveViewRange());
		cJSON_AddNumberToObject(obj, "IsStatic", (*iter2)->isStatic());
		cJSON_AddNumberToObject(obj, "IsMove", (*iter2)->isMove());
		cJSON_AddNumberToObject(obj, "StaticSpeed", (*iter2)->GetStaticSpeed());
		cJSON_AddNumberToObject(obj, "ActiveSpeed", (*iter2)->GetActiveSpeed());
		cJSON_AddNumberToObject(obj, "ImgID", (*iter2)->GetImgID());
		cJSON_AddNumberToObject(obj, "Hungry", (*iter2)->GetEnergy());
		cJSON_AddNumberToObject(obj, "MoveDir", (*iter2)->GetMoveDir());
		cJSON_AddNumberToObject(obj, "IsCollision", (*iter2)->IsCollision());
		cJSON_AddNumberToObject(obj, "IsFlee", (*iter2)->IsFlee());
		cJSON_AddNumberToObject(obj, "MoveDis", (*iter2)->GetMoveDis());
		cJSON_AddNumberToObject(obj, "MaxEatTime", (*iter2)->GetMaxEatTime());
		cJSON_AddNumberToObject(obj, "NowEatTime", (*iter2)->GetNowEatTime());
		iter2++;
	}

	//ֲ������
	while (iter3 != m_plant.end()) {
		cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
		cJSON_AddNumberToObject(obj, "ID", no++);
		cJSON_AddNumberToObject(obj, "Species", PLANT);
		cJSON_AddNumberToObject(obj, "Age", (*iter3)->GetAge());
		cJSON_AddNumberToObject(obj, "Life", (*iter3)->GetLife());
		cJSON_AddNumberToObject(obj, "Heat", (*iter3)->GetHeat());
		cJSON_AddNumberToObject(obj, "PosX", (*iter3)->GetPosX());
		cJSON_AddNumberToObject(obj, "PosY", (*iter3)->GetPosY());
		cJSON_AddNumberToObject(obj, "imgIndex", (*iter3)->GetImgIndex());
		iter3++;
	}
	
	//Manage����
	cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
	cJSON_AddNumberToObject(obj, "Species", 4);		//4�������ȫ������
	cJSON_AddNumberToObject(obj, "Times", m_times);	//��ǰʱ��
	cJSON_AddNumberToObject(obj, "CarNumber", m_wolf.size());	//ʳ�⶯������
	cJSON_AddNumberToObject(obj, "HarNumber", m_rabit.size());	//ֲʳ��������
	cJSON_AddNumberToObject(obj, "PlaNumber", m_plant.size());	//ֲ������


	out = cJSON_Print(root);
	fprintf(fp_cur, out);
	fclose(fp_cur);

	cJSON_Delete(root);
	free(out);

	out = NULL;
	root = NULL;

}

void Manage::CreatureIllusionCheck() {
	int size_c = m_wolf.size();
	int size_h = m_rabit.size();
	int size_p = m_plant.size();

	for (int i = 0; i < size_h; i++) {
		//if (m_rabit[i]->isFindTarget()) {
			for (int j = 0; j < size_c; j++) {
				//if (m_wolf[j]->isFindTarget())
				//ʳ�⶯��Ե���ֲʳ����
				if (Tools::CheckRectIllusion(cvPoint(m_rabit[i]->GetPosX() * GRID_SIZE, m_rabit[i]->GetPosY() * GRID_SIZE), m_rabit[i]->GetImage(), cvPoint(m_wolf[j]->GetPosX() * GRID_SIZE, m_wolf[j]->GetPosY() * GRID_SIZE), m_wolf[j]->GetImage())) {
					//Ȼ��ȷ��ʳ�⶯��û�гԱ�����Ϊ�п��ܾ����ж������ɳԵ���ֻ��
					if (m_wolf[j]->GetMaxEatTime() > m_wolf[j]->GetNowEatTime()) {
						m_wolf[j]->ChangeEnergy(m_rabit[i]->GetHeat());
						m_wolf[j]->Eat();
						m_rabit[i]->SetLiveType(false);
					}
				}
			}
			//ֲʳ�����ֲ��
			for (int j = 0; j < size_p; j++) {
				if (Tools::CheckRectIllusion(cvPoint(m_rabit[i]->GetPosX() * GRID_SIZE, m_rabit[i]->GetPosY() * GRID_SIZE), m_rabit[i]->GetImage(), cvPoint(m_plant[j]->GetPosX() * GRID_SIZE, m_plant[j]->GetPosY() * GRID_SIZE), m_plant[j]->GetImage())) {
					if (m_rabit[i]->isStatic() == false && m_rabit[i]->IsFlee() == false) {
						m_rabit[i]->ChangeEnergy(m_plant[j]->GetHeat());
						m_rabit[i]->Eat();
						m_plant[j]->SetLiveType(false);
					}
				}
			}
		//}
	}
}

void Manage::CheckHaveAnimal(int posx, int posy) {
	int x = posx / GRID_SIZE, y = posy / GRID_SIZE;
	
	if (m_map.m_AnimalInfo[y][x].liveType == GRASS) {
		m_displayinfo_swi = false;
	}
	else {
		m_displayinfo_swi = true;
		m_infoX = posx;
		m_infoY = posy;
	}
}

void Manage::DisplayAnimalInfo(int posx, int posy) {
	int x = posx / GRID_SIZE, y = posy / GRID_SIZE;

	IplImage *tmpImage = cvCloneImage(m_showBg);
	CvxText text("simsun.ttc");
	int texttype;
	CvScalar scalar;
	text.getFont(&texttype, &scalar);
	scalar.val[0] = 15;
	text.setFont(&texttype, &scalar);
	if (m_map.m_AnimalInfo[y][x].liveType == PLANT) {
		text.putText(m_showBg, "ֲ��", cvPoint(posx, posy));
		char str[20];
		sprintf_s(str, "����:%d", m_map.m_AnimalInfo[y][x].age);
		text.putText(m_showBg, str, cvPoint(posx, posy + 15));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "����:%d", m_map.m_AnimalInfo[y][x].heat);
		text.putText(m_showBg, str, cvPoint(posx, posy + 30));
	}
	else if (m_map.m_AnimalInfo[y][x].liveType == HARMLESS) {
		text.putText(m_showBg, "ʳ�ݶ���", cvPoint(posx, posy));
		char str[20];
		sprintf_s(str, "����:%d", m_map.m_AnimalInfo[y][x].age);
		text.putText(m_showBg, str, cvPoint(posx, posy + 15));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "����:%d", m_map.m_AnimalInfo[y][x].heat);
		text.putText(m_showBg, str, cvPoint(posx, posy + 30));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "������:%d", m_map.m_AnimalInfo[y][x].hungry);
		text.putText(m_showBg, str, cvPoint(posx, posy + 45));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "����%d��", m_map.m_AnimalInfo[y][x].nowEatTime);
		text.putText(m_showBg, str, cvPoint(posx, posy + 60));
		memset(str, '\0', sizeof(str));
		if (m_map.m_AnimalInfo[y][x].isFindTarget)
			if (m_map.m_AnimalInfo[y][x].isFlee) {
				sprintf_s(str, "�������ܡ�");
			}
			else
				sprintf_s(str, "������ʳ��");
		else
			sprintf_s(str, "�������Ρ�");
		text.putText(m_showBg, str, cvPoint(posx, posy + 75));
	}
	else if (m_map.m_AnimalInfo[y][x].liveType == CANIVOROUS) {
		text.putText(m_showBg, "ʳ�⶯��", cvPoint(posx, posy));
		char str[20];
		sprintf_s(str, "����:%d", m_map.m_AnimalInfo[y][x].age);
		text.putText(m_showBg, str, cvPoint(posx, posy + 15));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "����:%d", m_map.m_AnimalInfo[y][x].heat);
		text.putText(m_showBg, str, cvPoint(posx, posy + 30));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "������:%d", m_map.m_AnimalInfo[y][x].hungry);
		text.putText(m_showBg, str, cvPoint(posx, posy + 45));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "����%d��", m_map.m_AnimalInfo[y][x].nowEatTime);
		text.putText(m_showBg, str, cvPoint(posx, posy + 60));
		memset(str, '\0', sizeof(str));
		if (m_map.m_AnimalInfo[y][x].isFindTarget)
			sprintf_s(str, "���ڲ��ԡ�");
		else
			sprintf_s(str, "�������Ρ�");
		text.putText(m_showBg, str, cvPoint(posx, posy + 75));
	}
}


//��������ǰ��¼д�ģ����߱�������
/*
����һ�³���Ŀǰ���е���Ҫ���ܣ�
1���������ֲ�ͬ�����ʳ�⶯�ʳ�ݶ����ֲ��
2��ʵ�ֲ�ʳ��
3��ʵ�ַ�ֳ
������˵һ��������Ҫ���ܵ��ڲ�ϸ�ڣ�
һ��
1��д��һ��������Living����ʾ���ֲ��Ͷ��ﹲͬ�����Ժͷ��������������档
2����Ϊֲ��ֻ��һ�֣�����ֱ�Ӵ�Living�̳й���һ������С���������ʳ���ʳ�����ֲ�ͬ����Ϊģʽ�����֣����Ի���Ҫһ��������Animals��Ȼ���������������̳�Animals����
����
��ʳ����������������Ϊ����׽���������ڽ���������Ϊ�Ĺ������֮ǰҪ��˵һ������Animals������ӵ�һЩ���ԣ��Լ����뷨��
1��������ж���Ϊ������״̬����Ϣ(Static)�ͻ�Ծ(Active)
��Ϣ״̬��������û��׷��Ŀ��/����Ŀ�� �� ����(m_hungry)�ϵ� �� ����̫�� ��������£����Ǿ�Ϣ״̬��
��Ծ״̬������������׷��Ŀ��/����Ŀ�� �� �����㹻�����䲻�������£���ᴦ�ڻ�Ծ״̬��

��Ϣ״̬�ͻ�Ծ״̬�ıȽϣ�
�ƶ��ٶ�		�� < ��
��������		�� < ��
��Ұ��Χ		�� < ��

������趨��
�����ɳ�������ʱ����������ڿ�������ʹ��m_times����Ϊ��ʱ�����ڱ������У���������Ϊ���ĸ��ࣺ���ꡢ���ꡢ��������ꡣ��ʵ������£�ÿ���׶ε�ʱ��Ϊ15s����Ϊÿһ��m_times���Լ�20�Σ�����ÿ300��m_times����һ���׶Ρ�

2����ʳ��ʵ��ϸ�ڡ���������Ҫ������Ŀ������
�����ÿһ�θ��£����������1��20�θ��£���ÿ�θ��¶������ÿһ��������󣬻�ȡ�ö���ĵ�ǰ�������Ұ��Χ��������Ψһ�������ͼ��m_mapInfo���ٽ���һ�������������ڵ�ǰ�����һ����Χ���Ƿ����ܹ���ΪĿ��Ķ�������У�������Ŀ������
���ڶ���ʵ�ʵ��ƶ�����Move����������ۺϵ��������ж��ƶ�״̬�����������Ƿ񲻹��ˣ���������̫���ˣ�

������ֳ
�ҵķ�ֳ���ıȽϼ򵥡���Ҫ�Ǹ����������ĳɳ����ھ���������������������������ʱ��ν��ֳᷱ��
��ֳ��ʵ����ʽ�����ඨ�������ع��캯��������������飨Vector���м���new�������¶���ʱ���ܴ��ݵ�ǰ��������ԣ��Դﵽ�̳�Ч����


��������ص㣺
1��������
���������ࣺ
Resources�����ڴ��ͼ����Դ���Ա���Ӳ����Դ���ݵ�ͬһ��ȡ���ͷš�
Map�����ڴ���������������ͼ���ж�ȡ�ӿڣ�����������Ϣ����

һ�������ࣺ
Tools:��ų����õĹ������ͺ��������統ǰ��һ����ͼ�ľ�̬�������ô�����ͬһ��Ź����ں��������ܲ���Ҫʵ����������ִ�С�

2��
�����麯�������ԣ�ʵ���˺����Ķ�̬�����ǣ���
Living���е�SetImage()��Draw()��Ϊ���ӣ��������У��ٴ�������ͬ�����������ڲ�ͬ�������ж��岻ͬ�ķ��������øú���ʱ��������ݾ��������ֶ�����ִ�С�

3��
��̬�����أ���
����EditMapInfo()���������غ�ʳ�⶯���๹�캯�������ء�
����ʵ�ֹ��ܵĲ�ͬ�����ö�̬�������ص�ͬ��������

4��
ʵ�����������������C++ STL��Vector�������С�

��������ʱ��ʹ�õ�����,�磺vector<Carnivorous>::iterator iter

5��
��ֵ�ú궨�������ͷ�ļ��У�����ʹ�á��������

*/

/*
����һ����������ĵײ���ƣ��õ���������ͼ��m_energyMap���������ͼ(m_mapInfo)������ά���顣���ҵ�Ȼ������������ֱ��Ƕ�һ�޶��ġ�
��˵m_mapInfo�������ά���飬�Ǳ���ĵ�ͼ�������λ����Ϣ����x��y�������ʽ����
0����ʲô��û�У�
1��ʾ�˴���ʳ�⶯��
2��ʾ�˴���ʳ�ݶ���
3��ʾ�˴���ֲ��
Ȼ����m_energyMap,�����ά���飬������ǵ�ǰ������ϵ�������С��һ������¾�Ϊ0�����ǵ���������������ﱻ��ʳʱ����Ὣ�ö��������ֵ�洢��������ͼ�ĸ������ϡ�
*/

/*
����ں���Ҫ�Ľ���ʵ�ֵĹ���
��1��ʵ�ִ洢�Ͷ�ȡ��ÿ���ռ�������Ϣ������JSON�����ļ���JSON�ļ��Ķ�ȡ��
2����ֳ�Ŀ�ѧ�ԣ�������Ȼѡ�����ۣ�����ĸ��������������-��Ӱ���������Ƶĺ��-�����򣿣�
3��ֲ����;��ԣ����ᱻһ�ڳԵ�
4�����ӷ����ﲿ�֣�ɭ�ֺܿ�-���ϰ���-��Ӱ���ƶ��㷨-��A��
5���Ż�����������ֵ֮���ƽ���ԣ��������ʵ����̬ƽ�⡾����
6�����������ͼƬ����
��7�����ݵļ�ʱ��ʾ��������ݲ��ǵ�ǰ������������(�Ǹ����Ǵ浵���������̵�)������ɭ�ַ�չ���̵����ݣ����統ǰֲ����������������Է�ֵ�ȣ����Ҳ����Ϊ�ⲿ�ļ����浽Ӳ���ϣ��� ɭ�ִ浵�ļ� ���У��ɳ�Ϊ ɭ�ֽ����ļ���
*/

/*
12.16
��ʱ��ʽ����:����ǰ�ĳ�����࣬һ��1��ķ�ʽת��Ϊ,60sΪһ��
�����ȸ���ʱ�䵥λ��500ms
��������ʱ�䵥λ��60s
TODO��
1������ҹ��Ч��
2����ʱ��������ڽ����·�
3��������ӭ���棨��Ч��
4��ʵ������Ƶ������ܹ���ʾ����ļ�ʱ��Ϣ

4��ֲ�ﲻ�Ǳ�һ���Գ���ģ�һ��ֻ�ܳ�һ����
5��������ʵ����޸ĳ�ʼ����������ֵ�ͱ仯��ֵ
6��ʳ�⶯�һ�����һ�ͣ����Ǽ������Ѿ��ﵽ�˺ܵͣ�ֲʳ���һ��������ͣ����Ǽ������Ѿ��ﵽ�˺ܵ͡�����ӱ�ʳ����ر�����
7��ȥ��������ͼ(m_energyMap)���趨(����������ʱ��)
*/