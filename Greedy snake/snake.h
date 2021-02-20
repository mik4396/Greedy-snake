#pragma once
#include <iostream>
#include "wall.h"
#include"food.h"
using namespace std;

class Snake {
public:
	Snake(Wall &tempWall, Food & food);

	enum {
		up = 'w',
		DOWN='s',
		LEFT='a',
		RIGHT='d'

	};
	struct point {
		//数据域
		int x;
		int y;
		//指针域
		point *next;
	};
	//初始化结点
	void InitSnake();
	//销毁结点
	void destroypoint();
	//添加结点
	void addpoint(int x, int y);
	//移动时删除结点
	void delpoint();
	//移动操作
	//返回值代表是否成功
	bool move(char key);
	//设定难度
	//获取刷屏时间
	int getSleepTime();
	//获取蛇的身段
	int countList();
	//获取分数
	int getScore();
	point *pHead;

	Wall &wall;

	Food & food;
	bool isRool;//循环的标识

};