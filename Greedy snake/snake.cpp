#include"snake.h"
#include"wall.h"
#include<Windows.h>

void gotoxy1(HANDLE hOut1, int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut1, pos);
}

HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

Snake::Snake(Wall &tempWall, Food & tempFood) :wall(tempWall),food(tempFood) {
	pHead = NULL;
	isRool = false;
}

void Snake::destroypoint() {
	point * pCur = pHead;
	if (pHead!=NULL)
	{
		pCur = pHead->next;
		delete pHead;

		pHead = pCur;
	}
}

void Snake::addpoint(int x, int y) {
	//创建新结点
	point *newpoint = new point;
	
	newpoint->x = x;
	newpoint->y = y;
	newpoint->next = NULL;

	//如果原来头不为空，改为身子
	if (pHead != NULL) {
		wall.setWall(pHead->x, pHead->y, '=');

		gotoxy1(hOut1, pHead->y * 2,pHead->x );

		cout << "=";
	}

	newpoint->next = pHead;
	pHead = newpoint;//更新头部
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";

}

void Snake::InitSnake() {
	destroypoint();
	addpoint(5, 3);
	addpoint(5, 4);
	addpoint(5, 5);
}

void Snake::delpoint() {
	//两个以上结点，才去做删除操作
	if (pHead == NULL || pHead->next == NULL) {
		return;
	}
	//当前结点
	point *pCur = pHead->next;
	//上一个结点
	point *pPre = pHead;

	while (pCur->next != NULL) {
		pPre = pPre->next;
		pCur = pCur->next;

	}

	//删除尾结点
	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur ->y * 2, pCur->x);
	cout << " ";
	delete pCur;

	pCur = NULL;
	pPre->next = NULL;
}



bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;


	switch (key)
	{
	case up:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	
	point *pCur = pHead->next;
	//上一个结点
	point *pPre = pHead;

	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//if (pCur->x == x && pCur->y == y)
	//{
	//	//碰到尾巴的循环
	//	isRool = true;
	//}
	
		//判断用户要到达的位置是否成功
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addpoint(x, y);
			delpoint();
			system("cls");
			wall.drawWall();
			cout << "得分：" << getScore() << "分" << endl;
			cout << "GAME OVER" << endl;
			return false;
		}
	
	//移动成功 分两种
	//吃到食物，未吃到食物
	if (wall.getWall(x, y) == '#')
	{
		addpoint(x, y);

		//重新设置食物
		food.setFood();
	}
	else
	{
		addpoint(x, y);
		delpoint();

	/*	if (isRool == true)
		{
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, y * 2, x);
			cout << "@";
		}*/

	}

	return true;
}
//根据蛇的身段进行加速和获得分数
int Snake::getSleepTime()
{
	int sleepTime = 0;
	int size = countList();
	if (size < 5)
	{
		sleepTime = 300;
	}
	else if (size >= 5 && size <= 10)
	{
		sleepTime = 200;
	}
	else
	{
		sleepTime = 100;
	}
	return sleepTime;
}

int Snake::countList()
{
	int size = 0;
	point * curPoint = pHead;
	while (curPoint != NULL)
	{
		size++;
		curPoint = curPoint->next;
	}
	return size;
}

int Snake::getScore()
{
	int size = countList();
	int score = (size - 3) * 100;
	return score;
}