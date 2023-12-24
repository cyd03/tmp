#include<stdio.h>
#include<easyx.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#define NODE_WIDTH 40

enum direction
{
	eup,
	edown,
	eleft,
	eright
};
typedef struct
{
	int x;
	int y;
}node;
void PaintSnack(node* snake, int n)
{
	int lt, tp, rt, bm;
	for (int i = 0; i < n; i++)
	{
		lt = snake[i].x * NODE_WIDTH;
		tp = snake[i].y * NODE_WIDTH;
		rt = (snake[i].x + 1)*NODE_WIDTH;
		bm = (snake[i].y + 1) * NODE_WIDTH;
		solidrectangle(lt, tp, rt, bm);
	}
}
node SnakeMove(node* snake, int length, int direction)
{
	node tail = snake[length - 1];
	for (int i = length - 1; i > 0; i--)
	{
		snake[i] = snake[i - 1];
	}
	node newhead;
	newhead = snake[0];
	if (direction == eup)newhead.y--;
	if (direction == edown)newhead.y++;
	if (direction == eleft)newhead.x--;
	if (direction == eright)newhead.x++;
	snake[0] = newhead;
	return tail;
}
void paintline()
{
	for (int x = 0; x <= 800; x += NODE_WIDTH)
	{
		line(x, 0, x, 600);
	}
	for (int x = 0; x <= 600; x += NODE_WIDTH)
	{
		line(0, x, 800, x);
	}
}
void ChangeDirection(enum direction* d)
{
	if (_kbhit() != 0)
	{
		char c = _getch();
		switch (c)
		{
		case'w':
			if(*d!=edown)
			*d = eup;
			break;
		case'a':
			if(*d!=eright)
			*d = eleft;
			break;
		case'd':
			if(*d!=eleft)
			*d = eright;
			break;
		case's':
			if(*d!=eup)
			*d = edown;
			break;
		}
	}
}
node CreatFood(node* snake, int length)
{
	node food;
	while (1)
	{
		food.x = rand() % (800 / NODE_WIDTH);
		food.y = rand() % (600 / NODE_WIDTH);
		int i;
		for (i = 0; i < length; i++)
		{
			if (snake[i].x == food.x && snake[i].y == food.y)
			{
				break;
			}
		}
		if (i < length)
			continue;
		else
			break;
	}
	return food;
}
void PaintFood(node food)
{
	int lt,tp, rt, bm;
	lt = food.x * NODE_WIDTH;
	tp = food.y * NODE_WIDTH;
	rt = (food.x + 1) * NODE_WIDTH;
	bm = (food.y + 1) * NODE_WIDTH;
	setfillcolor(YELLOW);
	solidrectangle(lt, tp, rt, bm);
	setfillcolor(WHITE);
}
int isGameOver(node* snake, int length)
{
	if (snake[0].x < 0 || snake[0].x>800 / NODE_WIDTH-1)
		return 1;
	if (snake[0].y < 0 || snake[0].y>600 / NODE_WIDTH-1)
		return 1;
	for (int i = 1; i < length; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return 1;
	}
	return 0;
}
void reset(node* snake, int* plength, enum direction* d)
{
	snake[0] = node{ 5,7 };
	snake[1] = node{ 4,7 };
	snake[2] = node{ 3,7 };
	snake[3] = node{ 2,7 };
	snake[4] = node{ 1,7 };
	*plength = 5;
	*d = eright;
}
int main()
{
	initgraph(800, 600);
	setbkcolor(RGB(164, 225, 202));
	cleardevice();
	srand((unsigned int)time(NULL));
	node snake[100] = { {5,7},{4,7},{3,7},{2,7},{1,7} };
	int length = 5;
	node food=CreatFood(snake,length);
	enum direction d = eright;
	while (1)
	{
		cleardevice();
		paintline();
		PaintSnack(snake, length);
		PaintFood(food);
		Sleep(240);
		ChangeDirection(&d);
		node lastTail = SnakeMove(snake, length, d);
		if (snake[0].x == food.x && snake[0].y == food.y)
		{
			if (length < 100)
			{
				snake[length] = lastTail;
				length++;
			}
			food = CreatFood(snake, length);
		}
		if(isGameOver(snake, length) == 1)
		{
			reset(snake, &length, &d);
			food = CreatFood(snake, length);
		}
	}
	getchar();
	closegraph();
	return 0;

}