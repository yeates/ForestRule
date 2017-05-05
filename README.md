# 森林法则
## 项目简介
该程序设计的是一个森林的食物链。森林中包含三种角色：食肉动物，植食动物和植物，每个动物都具有位置信息，性别、年龄等基本信息。动物都有一定的生存规则，如运动规则，繁殖规则（年龄、性别），死亡规则（年龄），捕食规则（可以通过位置判定可以捕食，植食动物可以逃跑）等。 程序初始化时，可以读取存档或者自定义动物和植物的数量，用于创建森林。 程序根据运行时间运行，动物按照自己的生存规则运行。 程序需要输出生存期间的生物属性峰值（如种族中最大寿命，最大能量等，用于探究繁殖的科学性）。

## 模块简述
|编号|功能模块|功能描述（功能描述中要有数据，比如多少种飞机、动物；存储到什么文件。）|
|:--|:--|:--|
|FUN_01|动物捕食规则|当动物在视野范围内搜索到食物时，在保证没有天敌和没有过度饮食的情况下，便会向食物方向移动，并完成觅食行为。|
|FUN_02|动物繁殖规则|每隔一段时间，生物便会进行繁殖，繁殖产生的新生物，会基于父生物的属性，产生自己的随机基因。|
|FUN_03|动物运动规则|当动物遇到食物且保证没有过度饮食的情况下，会向食物方向移动，但动物的视野范围中出现了天敌，则将优先远离天敌。|
|FUN_04|生物死亡规则|当动物饥饿度低于下限，年龄超过寿命上限，或者被捕食，将会死亡。当植物年龄超过寿命上限，或者被捕食后也将会死亡。|
|FUN_05|生物形象图形化（可视化界面）|程序正式开始后的界面，整个森林以及其中的生物的运动、死亡等都以图形化显示。|
|FUN_06|可视化交互与键盘输入森林信息|程序开始前的可视化初始化界面，用户可在该界面自定义森林名称和生物初始数量。|
|FUN_07|鼠标事件动态显示生物属性|当光标落在生物（植物，食肉动物，植食动物）上时，会显示当前生物的个体属性和状态|
|FUN_08|输出森林存盘信息|存储到*_save.json文件里面，*表示用户自定义的森林名称。用于存盘，只用再次访问该json文件便能恢复森林状态。|
|FUN_09|利用文件流，即时输出生存期间生物属性峰值到文本文件|用于输出一时间段内各类生物的数量与在种族中个体属性的巅峰值，可据此推测生态的走向。因本森林法则程序采用图形界面，便取消了输出生物行为，例如捕食、死亡、繁殖等。该信息输出到*_info.txt文件中，*表示用户自定义的森林名称。|
|FUN_10|Vector 容器缓存所有数据|包括了植物(m_plant)，食肉动物(m_wolf)，植食动物(m_rabit)|

## 总体设计
### 类关系图:  
Living类是所有生物的基类，Animals类是所有动物的基类，森林中的对象有由三种类：植物类(Plant)，植食动物类(Harmless)和食肉动物类(Carnivorous)来实例化得到。Plant类继承于Living类，Harmless类和Carnivorous类继承于Animals类。  
Manage类依赖于其余大部分类，可视化初始界面封装于UI类中，常用工具类函数封装与Tools类中，程序资源管理部分封装与Resources类中。如图  
![1](http://o70i2z34f.bkt.clouddn.com//forestRule/1.png)

## 主功能算法
### 文件系统输出即时信息与读写JSON存档
该部分有两个算法，一个是用森林名称生成存档(json形式)，以便下次输入该名称时能完全恢复之前地图上所有生物的状态。还有一个是计算本年度剩余物种的个数和物种属性的峰值并输出到txt文本文件中。  
流程图：  
![2](http://o70i2z34f.bkt.clouddn.com//forestRule/2.png)  

图1  读写森林存档  

![3](http://o70i2z34f.bkt.clouddn.com//forestRule/3.png)  

 图2  输出即时信息文件  
算法对应实现函数： 

|类|函数|
|:--|:--|
|cJSON类|cJSON_AddNumberToObject(),cJSON_AddItemToArray(),cJSON_Print()等|
|Manage类|SaveJSONData(),ProcessInfoUpdate(),LivingUpdate()|

### 图形化UI界面的实现
算法描述  
在OpenCV的基础上写的图形化UI，实现了程序全图形化界面、可视化交互、文字输入框，并结合freetype输出中文编码的字体。  
流程图  
![3](http://o70i2z34f.bkt.clouddn.com//forestRule/4.png)  
图3  图形化开始界面

|类|函数|
|:--|:--|
|UI类|InitOneUi(),calCenterX(),GetPlantNum(),GetCarnivorousNum(),GetHarmlessNum()|
|CvxText类|getFont()setFont()putText()|

### 添加鼠标事件动态显示生物信息
算法描述  
利用Map类中存放诸多生物信息的ANIMALNODE结构体二维数组，在OpenCV鼠标事件的基础上，实现了鼠标可视化交互：动态显示光标当前指向的生物的信息。  
![3](http://o70i2z34f.bkt.clouddn.com//forestRule/5.png)  
图4  随鼠标动态显示生物个体信息  

对应实现函数  

|类|函数|
|:--|:--|
|Manage类|CheckHaveAnimal(),DisplayAnimalInfo(),LivingUpdate()|
|Carnivorous类|EditMapInfo()|
|Harmless类|EditMapInfo()|
|OpenCV|cvSetMouseCallback(),on_mouse()|

## 程序实现
### 开发平台与编译运行要求

![3](http://o70i2z34f.bkt.clouddn.com//forestRule/9.png)  

### 效果截图
1. 文件系统输出即时信息与读写JSON存档  
该部分有两个算法，一个是用森林名称生成存档(json形式)，以便下次输入该名称时能完全恢复之前地图上所有生物的状态。还有一个是计算本年度剩余物种的个数和物种属性的峰值并输出到txt文本文件中。  
2. 图形化UI界面的实现  
在OpenCV的基础上写的图形化UI，实现了程序全图形化界面、可视化交互、文字输入框，并结合freetype输出中文编码的字体。  
![3](http://o70i2z34f.bkt.clouddn.com//forestRule/6.png)  
![3](http://o70i2z34f.bkt.clouddn.com//forestRule/7.png)  

3. 添加鼠标事件动态显示生物信息  
利用Map类中存放诸多生物信息的ANIMALNODE结构体二维数组，在OpenCV鼠标事件的基础上，实现了鼠标可视化交互：动态显示光标当前指向的生物的信息。  
![3](http://o70i2z34f.bkt.clouddn.com//forestRule/8.png) 

### 功能完成度

|编号|功能模块|完成情况描述|完成度|
|:--|:--|:--|:--|
|FUN_01|动物捕食规则|√|1|
|FUN_02|动物繁殖规则|基本繁殖功能完成，但未实现交配|0.9|
|FUN_03|动物运动规则|√|1|
|FUN_04|生物死亡规则|√|1|
|FUN_05|生物形象图形化（可视化界面）|√|1|
|FUN_06|可视化交互与键盘输入森林信息|√|1|
|FUN_07|鼠标事件动态显示生物属性|√|1|
|FUN_08|输出森林存盘信息|√|1|
|FUN_09|利用文件流，即时输出生存期间生物属性峰值到文本文件|√|1|
|FUN_10|Vector 容器缓存所有数据|√|1|


## 总结
### 优点:
> 1. 注重代码时间复杂度，尽量采用线性或者效率更高的算法，尽量减少数组的遍历。
> 2. 抛弃命令框界面，采用图形化界面，让森林从黑框框中变得动感具有色彩，并加入可视化交互效果，如键盘交互、鼠标交互，增强程序使用体验。
> 3. 增加存盘与读取存档的功能。
> 4. 生物繁殖符合现实规律具有一定随机性，不会完全复制父对象的基因。 
 
### 缺点:
> 1. 生物种类较少
> 2. 生物生存规则较少



## 参考资料
[1] [Visual C++ 2015 编译 FreeType 2.6.2](http://blog.csdn.net/yapingxin/article/details/51841039)  
[2] [opencv中结合Freetype实现在图像写入中文](http://blog.csdn.net/lilin020401/article/details/42534383)  
[3] [cJSON库源码分析](http://www.tuicool.com/articles/6ZrIJn)  
[4] [OpenCV中文网站](http://www.opencv.org.cn/)  
[5] [cJSON手册]( https://github.com/DaveGamble/cJSON)  
[6] [解决Visual C++工程中包含 .c 或cpp文件编译时产生的.pch预编译头错误(C1853)的办法](http://blog.csdn.net/chenlycly/article/details/18423359)  
[7] [图像与设计资源网站](https://dribbble.com/)
