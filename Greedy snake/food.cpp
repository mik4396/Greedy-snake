#include "food.h"
#include <Windows.h>

void gotoxy2(HANDLE hOut2, int x, int y) {
	COORD pos;
	pos.X = x;//横坐标
	pos.Y = y;//纵坐标
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);
//通过获取控制台光标在墙内随机生成食物
Food::Food(Wall &tempwall) :wall(tempwall) {
	
}
void Food::setFood() {
	while (true) {
		Foodx = rand() % (Wall::ROW - 2) + 1;
		Foody = rand() % (Wall::COL - 2) + 1;
		//如果随机生成的位置是蛇头或蛇身，则重新生成随机数
		if (wall.getWall(Foodx, Foody) == ' ') {
			wall.setWall(Foodx, Foody, '#');
			gotoxy2(hOut2, Foody * 2, Foodx);
			cout << '#';
			break;
		}
	}
}