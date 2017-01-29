#include "stdafx.h"
#include "Manage.h"



Manage::Manage()
{
	m_times = 0;					//计时器置0
	m_displayinfo_swi = false;
}


Manage::~Manage()
{
	fclose(fp);
	fclose(fp_cur);
}

void Manage::DataInit() {
	srand((unsigned)time(NULL));			//更新随机数种子
	cvNamedWindow(m_ui.m_forestName, CV_WINDOW_AUTOSIZE);		//新建窗口（用户不能改变大小）
	m_map.SetMapImage(m_resources.m_mapImage);

	CvSize tmp;								//创建窗口
	tmp.width = MAP_X_SIZE * GRID_SIZE, tmp.height = MAP_Y_SIZE * GRID_SIZE;
	m_Bg = cvCreateImage(tmp, IPL_DEPTH_8U, 3);
	m_map.DrawMap(m_Bg);					//创建背景地图
	m_showBg = cvCloneImage(m_Bg);

	if (m_ui.IsCreatNewMap()) {
		//创建新的地图信息，程序数据初始化

		for (int i = 0; i < m_ui.GetPlantNum(); i++) {		//随机坐标生成植物
			int posx, posy;
			posx = rand() % MAP_X_SIZE;
			posy = rand() % MAP_Y_SIZE;
			int imgIndex = rand() % 4;
			int heat = rand() % 10 + 25;
			m_plant.push_back(new Plant(posx, posy, heat, 120, m_resources.m_plantImage, imgIndex));
			m_plant[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_plant[i]->GetPosX(), m_plant[i]->GetPosY(), m_plant[i]->GetAge(), m_plant[i]->GetHeat());
		}
		for (int i = 0; i < m_ui.GetCarnivorousNum(); i++) {	//随机坐标生成食肉动物
			int posx, posy;
			posx = rand() % MAP_X_SIZE;
			posy = rand() % MAP_Y_SIZE;
			int sv = rand() % 2 + 3;
			int av = sv + 2;
			int hungry = rand() % 10 + 60;
			m_wolf.push_back(new Carnivorous(posx, posy, sv, av, 2, 8, hungry, hungry * 0.2, 60, m_resources.m_carnivorousImage));
		}
		for (int i = 0; i < m_ui.GetHarmlessNum(); i++) {		//随机坐标生成植食动物
			int posx, posy;
			posx = rand() % MAP_X_SIZE;
			posy = rand() % MAP_Y_SIZE;
			int sv = rand() % 2 + 2;
			int av = sv + 2;
			int hungry = rand() % 10 + 90;
			m_rabit.push_back(new Harmless(posx, posy, sv, av, 4, 8, hungry, hungry * 0.4, 80, m_resources.m_harmlessImage));
		}

		cvShowImage(m_ui.m_forestName, m_showBg);

		//打开文件
		char name[80];
		sprintf_s(name, "data//%s_info.txt", m_ui.m_forestName);
		if ((fp = fopen(name, "w+")) == NULL) {
			cout << "open file failed!" << endl;
		}

	}
	else {
		//从JSON文件中读取已有的森林信息。
		int i = 1;
		char name[80];
		sprintf_s(name, "data//%s_save.json", m_ui.m_forestName);
		cJSON *jsonArr = Tools::GetJsonArray(name);			//使用TOOLS类中的方法
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

		//打开文件
		memset(name, 0, sizeof(name));
		sprintf_s(name, "data//%s_info.txt", m_ui.m_forestName);
		if ((fp = fopen(name, "w+")) == NULL) {
			cout << "open file failed!" << endl;
		}
	}
}	

/*
每帧对地图中的对象进行状态的更新
*/
void Manage::LivingUpdate() {
	TargetSearch();
	CreatureIllusionCheck();
	if (!m_plant.empty())	PlantUpdate();
	if(!m_wolf.empty())		CarnivorousUpdate();
	if(!m_rabit.empty())	HarmlessUpdate();
}

//食肉动物状态的更新
void Manage::CarnivorousUpdate() {
	vector<Carnivorous *>::iterator iter;
	
	int heat, age, life;
	heat = age = life = 0;

	//删除可清理对象
	iter = m_wolf.begin();
	while (iter != m_wolf.end()) {
		if ((*iter)->IsNeedClear()) {
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == CANIVOROUS)					//要保证在重置之前这个地图信息就是食肉动物，如果不是不能随便清空为默认态
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), 0);		//不要忘记把地图信息给重置了
			delete *iter;
			iter = m_wolf.erase(iter);
		}
		else {
			heat = max(heat, (*iter)->GetEnergy());
			age = max(age, (*iter)->GetAge());
			life = max(life, (*iter)->GetLife());

			//虚函数的优越性：这一段在三种生物中代码都一样，直接粘贴也不会有错 
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == GRASS)
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), (*iter)->GetAge(), (*iter)->GetHeat(), (*iter)->GetEnergy(), (*iter)->GetNowEatTime(), (*iter)->isFindTarget());
			iter++;
		}
	}

	m_carnivorousMaxCount.age = age, m_carnivorousMaxCount.life = life, m_carnivorousMaxCount.energy = heat * 10 / 2;

	int sizeN = m_wolf.size();
	for (int i = 0; i < sizeN; i++) {
		//年龄更新
		if (0 == m_times % 20) {
			m_wolf[i]->Old();
		}
		if (m_wolf[i]->isTooOld()) {
			m_wolf[i]->SetLiveType(false);
		}

		//饥饿度更新
		if (0 == m_times % 20) {
			if (m_wolf[i]->isStatic()) m_wolf[i]->ChangeEnergy(-1);			//当前是否处于活跃状态
			else m_wolf[i]->ChangeEnergy(-3);
		}

		if (m_wolf[i]->GetEnergy() <= 0) {
			m_wolf[i]->SetLiveType(false);
		}
		//捕食状态更新
		if (0 == m_times % 900)	m_wolf[i]->InitEatTime();

		//繁殖
		if (0 == m_times % 600 && m_times != 0) {
			int dir = rand() % 4 + 1;					//后代的坐标相对于原对象的方向
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
		//位置更新
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

	//删除可清理对象
	iter = m_rabit.begin();
	while (iter != m_rabit.end()) {
		if ((*iter)->IsNeedClear()) {
			if (m_map.m_mapInfo[(*iter)->GetPosY()][(*iter)->GetPosX()] == HARMLESS)			//和食肉动物那行代码一个原理
				(*iter)->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, (*iter)->GetPosX(), (*iter)->GetPosY(), 0);	//修改坐标地图
			m_deadEffective.push_back(new DeadEffective(m_resources.m_harmlessDeadImage[(*iter)->GetDirection() - 1], (*iter)->GetDrawPosX(), (*iter)->GetDrawPosY()));		//死亡效果

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
		//年龄更新
		if (0 == m_times % 20) {
			m_rabit[i]->Old();
		}
		if (m_rabit[i]->isTooOld()) {
			m_rabit[i]->SetLiveType(false);
		}

		//饥饿度更新
		if (0 == m_times % 20) {
			if (m_rabit[i]->isStatic()) m_rabit[i]->ChangeEnergy(-1);
			else m_rabit[i]->ChangeEnergy(-2);
		}
		if (m_rabit[i]->GetEnergy() <= 0) {
			m_rabit[i]->SetLiveType(false);
		}
		//捕食状态更新
		if (0 == m_times % 900)	m_rabit[i]->InitEatTime();

		//繁殖
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
		//位置更新
		if (m_map.m_mapInfo[m_rabit[i]->GetPosY()][m_rabit[i]->GetPosX()] == HARMLESS)
			m_rabit[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[i]->GetPosX(), m_rabit[i]->GetPosY(), 0);
		if (m_rabit[i]->IsFlee())
			m_rabit[i]->Flee(m_Bg);
		else
			m_rabit[i]->Chase(m_Bg);
		if(m_map.m_mapInfo[m_rabit[i]->GetPosY()][m_rabit[i]->GetPosX()] == GRASS)
			m_rabit[i]->EditMapInfo(m_map.m_mapInfo, m_map.m_AnimalInfo, m_rabit[i]->GetPosX(), m_rabit[i]->GetPosY(), m_rabit[i]->GetAge(), m_rabit[i]->GetHeat(), m_rabit[i]->GetEnergy(), m_rabit[i]->GetNowEatTime(), m_rabit[i]->isFindTarget(), m_rabit[i]->IsFlee());	//因为mapinfo保存的地图信息只有一重，所以写数据的时候会直接覆盖掉原数据，所以当harmless经过plant的时候，mapinfo上plant的标志就被重写了，而且不会复原，所以直接delete掉plant就行（具体实现见PlantUpdate函数）
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
		//年龄更新
		if (0 == m_times % 20) {
			m_plant[i]->Old();
		}
		if (m_plant[i]->isTooOld()) {
			m_plant[i]->SetLiveType(false);
		}

		//繁殖
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
判断地图中的对象能看见目标
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
	
	//食肉动物开始在视野范围内搜寻目标
	while (iter1 != m_wolf.end()) {
		//如果吃饱了并且饥饿度不是太低，那么就不用搜索目标了
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
			//在记录地图信息的mapinfo[][]中按格子搜索
			for (int i = posy - range; i <= posy + range; i++) {
				for (int j = posx - range; j <= posx + range; j++) {
					x = j, y = i;
					//边缘越界，到屏幕另一边
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

	//食草动物开始在视野范围内搜寻食物
	while (iter2 != m_rabit.end()) {
		//如果吃饱了并且饥饿度不是太低，那么就不用搜索目标了
		if ((*iter2)->GetMaxEatTime() <= (*iter2)->GetNowEatTime() &&  (*iter2)->GetEnergy() >= (*iter2)->GetHeat()) {
			(*iter2)->SetFindTarget(false);
			(*iter2)->SetTargetPos(-1, -1);
			(*iter2)->SetisActive(false);
			iter2++;
			continue;
		}

		minDis = INF;
		//觅食
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
	//食草动物开始在视野范围内搜寻天敌
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
	sprintf_s(str, " 第%d年 ", m_times / 20 + 1);
	Tools::print(str, 40);
	Tools::print(str, 40, fp);

	//输出当前植物的数量和属性峰值
	sprintf_s(str, "> 植物：");
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	sprintf_s(str, "	数量: %d个", m_plant.size());
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	if (m_plant.size() > 0) {
		sprintf_s(str, "	活的最久： %d岁", m_plantMaxCount.age);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	标准寿命： %d岁", m_plantMaxCount.life);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	储存能量： %d值", m_plantMaxCount.energy);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
	}

	//输出当前食肉动物的数量
	sprintf_s(str, "> 食肉动物：");
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	sprintf_s(str, "	数量: %d个", m_wolf.size());
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	if (m_plant.size() > 0) {
		sprintf_s(str, "	活的最久： %d岁", m_carnivorousMaxCount.age);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	标准寿命： %d岁", m_carnivorousMaxCount.life);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	最高能量： %d值", m_carnivorousMaxCount.energy);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
	}
	
	//输出当前食草动物的数量
	sprintf_s(str, "> 食草动物：");
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	sprintf_s(str, "	数量: %d个", m_rabit.size());
	cout << str << endl;
	fprintf(fp, str);
	fprintf_s(fp, "\n");
	if (m_plant.size() > 0) {
		sprintf_s(str, "	活的最久： %d岁", m_harmlessMaxCount.age);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	年度标准寿命： %d岁", m_harmlessMaxCount.life);
		cout << str << endl;
		fprintf(fp, str);
		fprintf_s(fp, "\n");
		sprintf_s(str, "	年度最高能量： %d值", m_harmlessMaxCount.energy);
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

	cJSON *root, *obj;		//root是JSON数组， obj是JSON对象
	char *out;
	root = cJSON_CreateArray();
	int no = 1;			//记录存活对象ID
	char name[80];
	sprintf_s(name, "data//%s_save.json", m_ui.m_forestName);
	if (NULL == (fp_cur = fopen(name, "w+"))) {
		cout << "open file failed!" << endl;
	}

	//保存食肉动物的json数据
	while (iter1 != m_wolf.end()) {
		cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
		//为了保证存档的属性完整，是在调试中，查看对象的所有属性，一一看是否应该添加到存档文件中。
		cJSON_AddNumberToObject(obj, "ID", no++);
		cJSON_AddNumberToObject(obj, "Species", CANIVOROUS);
		cJSON_AddNumberToObject(obj, "Age", (*iter1)->GetAge());
		cJSON_AddNumberToObject(obj, "Life", (*iter1)->GetLife());
		cJSON_AddNumberToObject(obj, "Heat", (*iter1)->GetHeat());
		cJSON_AddNumberToObject(obj, "PosX", (*iter1)->GetPosX());
		cJSON_AddNumberToObject(obj, "PosY", (*iter1)->GetPosY());
		//因为每帧都会全局搜索目标对象，所以记录下坐标就够了，不用记录目标坐标/是否有目标
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

	//保存植食动物的json数据
	while (iter2 != m_rabit.end()) {
		cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
		//为了保证存档的属性完整，是在调试中，查看对象的所有属性，一一看是否应该添加到存档文件中。
		cJSON_AddNumberToObject(obj, "ID", no++);
		cJSON_AddNumberToObject(obj, "Species", HARMLESS);
		cJSON_AddNumberToObject(obj, "Age", (*iter2)->GetAge());
		cJSON_AddNumberToObject(obj, "Life", (*iter2)->GetLife());
		cJSON_AddNumberToObject(obj, "Heat", (*iter2)->GetHeat());
		cJSON_AddNumberToObject(obj, "PosX", (*iter2)->GetPosX());
		cJSON_AddNumberToObject(obj, "PosY", (*iter2)->GetPosY());
		//因为每帧都会全局搜索目标对象，所以记录下坐标就够了，不用记录目标坐标/是否有目标
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

	//植物属性
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
	
	//Manage属性
	cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
	cJSON_AddNumberToObject(obj, "Species", 4);		//4代表程序全局属性
	cJSON_AddNumberToObject(obj, "Times", m_times);	//当前时间
	cJSON_AddNumberToObject(obj, "CarNumber", m_wolf.size());	//食肉动物数量
	cJSON_AddNumberToObject(obj, "HarNumber", m_rabit.size());	//植食动物数量
	cJSON_AddNumberToObject(obj, "PlaNumber", m_plant.size());	//植物数量


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
				//食肉动物吃到了植食动物
				if (Tools::CheckRectIllusion(cvPoint(m_rabit[i]->GetPosX() * GRID_SIZE, m_rabit[i]->GetPosY() * GRID_SIZE), m_rabit[i]->GetImage(), cvPoint(m_wolf[j]->GetPosX() * GRID_SIZE, m_wolf[j]->GetPosY() * GRID_SIZE), m_wolf[j]->GetImage())) {
					//然后确保食肉动物没有吃饱（因为有可能矩形判断中碰巧吃到多只）
					if (m_wolf[j]->GetMaxEatTime() > m_wolf[j]->GetNowEatTime()) {
						m_wolf[j]->ChangeEnergy(m_rabit[i]->GetHeat());
						m_wolf[j]->Eat();
						m_rabit[i]->SetLiveType(false);
					}
				}
			}
			//植食动物吃植物
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
		text.putText(m_showBg, "植物", cvPoint(posx, posy));
		char str[20];
		sprintf_s(str, "年龄:%d", m_map.m_AnimalInfo[y][x].age);
		text.putText(m_showBg, str, cvPoint(posx, posy + 15));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "能量:%d", m_map.m_AnimalInfo[y][x].heat);
		text.putText(m_showBg, str, cvPoint(posx, posy + 30));
	}
	else if (m_map.m_AnimalInfo[y][x].liveType == HARMLESS) {
		text.putText(m_showBg, "食草动物", cvPoint(posx, posy));
		char str[20];
		sprintf_s(str, "年龄:%d", m_map.m_AnimalInfo[y][x].age);
		text.putText(m_showBg, str, cvPoint(posx, posy + 15));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "能量:%d", m_map.m_AnimalInfo[y][x].heat);
		text.putText(m_showBg, str, cvPoint(posx, posy + 30));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "饥饿度:%d", m_map.m_AnimalInfo[y][x].hungry);
		text.putText(m_showBg, str, cvPoint(posx, posy + 45));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "吃了%d顿", m_map.m_AnimalInfo[y][x].nowEatTime);
		text.putText(m_showBg, str, cvPoint(posx, posy + 60));
		memset(str, '\0', sizeof(str));
		if (m_map.m_AnimalInfo[y][x].isFindTarget)
			if (m_map.m_AnimalInfo[y][x].isFlee) {
				sprintf_s(str, "正在逃跑…");
			}
			else
				sprintf_s(str, "正在觅食…");
		else
			sprintf_s(str, "正在漫游…");
		text.putText(m_showBg, str, cvPoint(posx, posy + 75));
	}
	else if (m_map.m_AnimalInfo[y][x].liveType == CANIVOROUS) {
		text.putText(m_showBg, "食肉动物", cvPoint(posx, posy));
		char str[20];
		sprintf_s(str, "年龄:%d", m_map.m_AnimalInfo[y][x].age);
		text.putText(m_showBg, str, cvPoint(posx, posy + 15));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "能量:%d", m_map.m_AnimalInfo[y][x].heat);
		text.putText(m_showBg, str, cvPoint(posx, posy + 30));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "饥饿度:%d", m_map.m_AnimalInfo[y][x].hungry);
		text.putText(m_showBg, str, cvPoint(posx, posy + 45));
		memset(str, '\0', sizeof(str));
		sprintf_s(str, "吃了%d顿", m_map.m_AnimalInfo[y][x].nowEatTime);
		text.putText(m_showBg, str, cvPoint(posx, posy + 60));
		memset(str, '\0', sizeof(str));
		if (m_map.m_AnimalInfo[y][x].isFindTarget)
			sprintf_s(str, "正在捕猎…");
		else
			sprintf_s(str, "正在漫游…");
		text.putText(m_showBg, str, cvPoint(posx, posy + 75));
	}
}


//下面是以前记录写的，不具备最新性
/*
整理一下程序目前已有的主要功能：
1、生成三种不同的生物：食肉动物、食草动物和植物
2、实现捕食链
3、实现繁殖
借下来说一下三个主要功能的内部细节：
一、
1、写了一个抽象类Living，表示生物，植物和动物共同的属性和方法都放在了里面。
2、因为植物只有一种，所以直接从Living继承过来一个类就行。而动物有食肉和食草两种不同的行为模式的物种，所以还需要一个抽象类Animals，然后再用两个类来继承Animals即可
二、
捕食链中有两个基本行为，捕捉和逃亡，在介绍两种行为的规则设计之前要先说一下我在Animals类中添加的一些属性（自己的想法）
1、动物的行动分为了两种状态：静息(Static)和活跃(Active)
静息状态：当动物没有追捕目标/逃离目标 和 能量(m_hungry)较低 和 年龄太大 三种情况下，便是静息状态。
活跃状态：当动物有了追捕目标/逃离目标 和 能量足够且年龄不大的情况下，便会处于活跃状态。

静息状态和活跃状态的比较：
移动速度		静 < 活
能量消耗		静 < 活
视野范围		静 < 活

年龄的设定：
年龄由程序运行时间决定，故在控制类中使用m_times来作为计时器，在本程序中，生物对象分为了四个类：幼年、青年、中年和老年。在实际情况下，每个阶段的时长为15s，因为每一秒m_times会自加20次，所以每300个m_times就是一个阶段。

2、捕食的实现细节————主要函数：目标搜索
程序的每一次更新（在我这儿是1秒20次更新），每次更新都会遍历每一个动物对象，获取该对象的当前坐标和视野范围，再利用唯一的坐标地图（m_mapInfo）再进行一次搜索，搜索在当前坐标的一定范围内是否有能够成为目标的对象，如果有，则设置目标坐标
至于对象实际的移动则在Move函数里，根据综合的条件来判断移动状态（比如能量是否不够了，或者年龄太老了）

三、繁殖
我的繁殖做的比较简单。主要是根据生物对象的成长周期决定，当到达了青年或者是中年的时间段将会繁殖。
繁殖的实现形式：在类定义中重载构造函数，向本类对象数组（Vector）中加入new出来的新对象时，能传递当前对象的属性，以达到继承效果。


代码设计特点：
1、建立了
两个数据类：
Resources类用于存放图像资源，以便于硬盘资源数据的同一读取和释放。
Map类用于存放生物对象的坐标地图，有读取接口，便于坐标信息管理。

一个工具类：
Tools:存放程序常用的工具类型函数，比如当前的一个绘图的静态函数。好处是能同一存放工具内函数，且能不需要实例化对象便可执行。

2、
利用虚函数的特性，实现了函数的多态（覆盖）：
Living类中的SetImage()和Draw()即为例子，在子类中，再次声明了同名函数，并在不同的子类中定义不同的方法。调用该函数时，将会根据具体是哪种对象来执行。

3、
多态（重载）：
比如EditMapInfo()函数的重载和食肉动物类构造函数的重载。
根据实现功能的不同，利用动态特性重载的同名函数。

4、
实例化的生物对象存放在C++ STL的Vector型数组中。

遍历数组时可使用迭代器,如：vector<Carnivorous>::iterator iter

5、
常值用宏定义放在了头文件中，便于使用、避免出错

*/

/*
介绍一下整个程序的底层机制，用到了能量地图（m_energyMap）和坐标地图(m_mapInfo)两个二维数组。而且当然，这两个数组分别都是独一无二的。
先说m_mapInfo，这个二维数组，是保存的地图上生物的位置信息（以x，y坐标的形式）：
0代表什么都没有；
1表示此处是食肉动物
2表示此处是食草动物
3表示此处是植物
然后是m_energyMap,这个二维数组，保存的是当前坐标点上的能量大小，一般情况下均为0，但是当该坐标点上有生物被捕食时，则会将该动物的能量值存储到能量地图的该坐标上。
*/

/*
最后在后期要改进和实现的功能
√1、实现存储和读取：每秒收集程序信息，生成JSON数据文件，JSON文件的读取。
2、繁殖的科学性：贴近自然选择理论（最初的父对象是随机属性-》影响生成类似的后代-》基因？）
3、植物的耐久性：不会被一口吃掉
4、增加非生物部分：森林很空-》障碍物-》影响移动算法-》A星
5、优化程序生物数值之间的平衡性（尽量最后实现生态平衡【雾】）
6、增加生物的图片种类
√7、数据的即时显示，这个数据不是当前程序局面的数据(那个就是存档，用来复盘的)，而是森林发展进程的数据，比如当前植物数量，生物的属性峰值等，这个也会作为外部文件保存到硬盘上，和 森林存档文件 并列，可称为 森林进程文件。
*/

/*
12.16
计时方式更新:由以前的超快节奏，一秒1年的方式转变为,60s为一天
饥饿度更新时间单位：500ms
寿命更新时间单位：60s
TODO：
1、加入夜晚效果
2、即时输出框做在界面下方
3、美化欢迎界面（动效）
4、实现鼠标移到生物能够显示生物的即时信息

4、植物不是被一次性吃完的，一次只能吃一部分
5、根据现实情况修改初始生物属性数值和变化数值
6、食肉动物：一天最多一餐，除非饥饿度已经达到了很低；植食动物：一天最多两餐，除非饥饿度已经达到了很低。（添加饱食度相关变量）
7、去除能量地图(m_energyMap)的设定(坏处，牺牲时间)
*/