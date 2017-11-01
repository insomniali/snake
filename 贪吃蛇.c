#include<stdio.h>
#include<stdlib.h>
#include<time.h> //获取时间
#include<conio.h>//控制台库函数
#include<windows.h>//windows库函数
#include<mmsystem.h>//windows接口函数头文件
#pragma comment(lib, "winmm.lib")//#pragma 指令，接入winmm库

/*定义蛇的节点*/
typedef struct snake
{

	int x;

	int y;

	struct snake *next;

}s1;

int direction1, flag = 0, sum = 0, add = 1;//方向判断符，死亡判断
s1 *q1, *head1, *food;//定义蛇的遍历指针,蛇头指针，食物指针

void setgametitle();
void face();
//void music_start();
void start();
//void myplaysound()；
//void music_stop();
void Pos(int, int);
void map_create();
void snake1_create();
void snake1_move();
void wallcrash();
int biteitself();
void food_produce();
void game_before();
void game_run();
void game_pause();
void showscore();
void game_over();


//标题
void setgametitle() {
	system("title 正常的贪吃蛇");
}

//封面
void face() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                                                       欢迎来到贪吃蛇\n");
	printf("                                                        按空格键开始   \n");
	printf("                                                     ↑ ↓ ← →   控制方向     \n");
}

//游戏开始
void start() {
	char get;
	while (1) {
		get = _getch();
		if (get == ' ') {
			break;
		}
	}
}

/*打开音乐文件*/
//播放音乐
/*void music_start() {
mciSendString("play ", NULL, 0, NULL);
Sleep(50000);
}*/

//停止音乐
/*void music_stop() {
char get2;
get2 = getch();
if (get2 == 'p') {
mciSendString("close 1.mp3", NULL, 0, NULL);
}
}*/

/*另一种方案只能播wav文件
void myplaysound(){
PlaySound(TEXT("Cruzo - Epic Sax Guy (Remix) [mqms2].wav"),NULL,SND_FILENAME|SND_SYNC);
}*/

/*停止播放
void music_stop(){
char get2;
get2=getch;
if("p"==get2){
PlaySound(NULL,0,0);
}
}
*/

//设置光标
void Pos(int x, int y) {
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//创建地图
void map_create() {
	int i;
	//打印上下边框
	for (i = 0; i < 60; i += 2) {
		Pos(i, 0);
		printf("■");
		Pos(i, 30);
		printf("■");
	}
	//打印左右边框
	for (i = 0; i < 30; i++) {
		Pos(0, i);
		printf("■");
		Pos(58, i);
		printf("■");
	}
}

//画蛇，从后往前画
void snake1_create() {
	s1 *tail1;
	int  i;
	tail1 = (s1*)malloc(sizeof(s1));
	tail1->x = 6;
	tail1->y = 3;
	tail1->next = NULL;
	for (i = 0; i<2; i++) {
		head1 = (s1*)malloc(sizeof(s1));
		head1->x = tail1->x + 2;
		head1->y = tail1->y;
		head1->next = tail1;
		tail1 = head1;
	}
	//输出蛇身
	while (tail1 != NULL) {
		Pos(tail1->x, tail1->y);
		printf("■");
		tail1 = tail1->next;
	}
}

//判断是否撞墙
void wallcrash() {
	if (head1->x >= 59 || head1->x <= 0 || head1->y >= 29 || head1->y <= 0) {
		flag = 1;
	}
}

//判断是否咬到自己
int biteitself() {
	s1*self;
	self = (s1*)malloc(sizeof(s1));
	self = head1->next;
	while (self != NULL) {
		if (self->x == head1->x&&self->y == head1->y) {
			return  2;
		}
		self = self->next;

	}
	return 0;
}

//随机产生食物
void food_produce() {
	//随机位置
	srand((unsigned int)time(NULL));
	//产生食物
	s1*food1;
	food1 = (s1*)malloc(sizeof(s1));
	while (food1->x % 2 != 0 || food1->x >= 58 || food1->x <= 0 || head1->y >= 29 || head1->y <= 0) {
		food1->x = rand() % 53 + 2;
	}
	food1->y = rand() % 28 + 1;
	//判断是否和蛇身重合
	q1 = head1;
	while (q1->next != NULL)
	{
		if (q1->x == food1->x&&q1->y == food1->y) {
			free(food1);
			food_produce();
		}
		q1 = q1->next;
	}
	food = food1;
	Pos(food->x, food->y);
	printf("★");
}

//蛇移动
void snake1_move() {
	s1 * nexthead1;
	wallcrash();
	flag = biteitself();
	nexthead1 = (s1*)malloc(sizeof(s1));

	if (direction1 == 1)

	{

		nexthead1->x = head1->x;

		nexthead1->y = head1->y - 1;

		if (nexthead1->x == food->x && nexthead1->y == food->y)//如果下一个有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//如果没有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			Pos(q1->next->x, q1->next->y);

			printf("  ");

			free(q1->next);

			q1->next = NULL;

		}

	}

	if (direction1 == 2)

	{

		nexthead1->x = head1->x;

		nexthead1->y = head1->y + 1;

		if (nexthead1->x == food->x && nexthead1->y == food->y)//如果下一个有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//如果没有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			Pos(q1->next->x, q1->next->y);

			printf("  ");

			free(q1->next);

			q1->next = NULL;

		}

	}
	if (direction1 == 3)

	{

		nexthead1->x = head1->x - 2;

		nexthead1->y = head1->y;

		if (nexthead1->x == food->x && nexthead1->y == food->y)//如果下一个有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//如果没有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			Pos(q1->next->x, q1->next->y);

			printf("  ");

			free(q1->next);

			q1->next = NULL;

		}

	}
	if (direction1 == 4)

	{

		nexthead1->x = head1->x + 2;

		nexthead1->y = head1->y;

		if (nexthead1->x == food->x && nexthead1->y == food->y)//如果下一个有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//如果没有食物//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("■");

				q1 = q1->next;

			}

			Pos(q1->next->x, q1->next->y);

			printf("  ");

			free(q1->next);

			q1->next = NULL;

		}

	}
}




//游戏暂停
void game_pause() {
	while (1) {
		Sleep(300);
		Pos(80, 10);
		if (GetAsyncKeyState(VK_SPACE)) {
			break;
		}
	}
}

void showscore() {
	Pos(80, 14);
	printf("刚进来是暂停的,防止你的蛇不小心死掉");
	Pos(80, 15);
	printf("每吃掉一颗星得 1 分");
	Pos(80, 16);
	printf("↑ ↓ ← → 分别控制上下左右");
	Pos(80, 17);
	printf("按空格键暂停，再按即恢复，ESC键退出");
	Pos(80, 18);
	printf("你目前的分数是：%d", sum);
	Pos(120, 50);
}
void game_before() {
	system("mode con cols=120 lines=50");
	setgametitle();
	face();
	start();
	system("cls");
	//music_start();
	map_create();
	snake1_create();
	food_produce();
}

void game_run() {
	direction1 = 4;
	while (1) {
		showscore();
		wallcrash();
		if (flag != 0) {
			break;
		}
		else if (GetAsyncKeyState(VK_UP) && direction1 != 2) {
			direction1 = 1;
		}
		else if (GetAsyncKeyState(VK_DOWN) && direction1 != 1) {
			direction1 = 2;
		}
		else if (GetAsyncKeyState(VK_LEFT) && direction1 != 4) {
			direction1 = 3;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && direction1 != 3) {
			direction1 = 4;
		}
		else if (GetAsyncKeyState(VK_SPACE)) {
			game_pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			flag = 3;
		}
		Sleep(200);
		snake1_move();
	}
}

void game_over() {
	system("cls");
	switch (flag) {
	case 1:printf("活着不好吗？为什么要去撞墙!\n"); break;
	case 2:printf("你咬到自己了！\n"); break;
	}
	printf("你的最终分数是： %d\n", sum);
	switch ((int)(sum / 5)) {
	case 0:printf("我居然有这么菜的朋友!\n"); break;
	case 1:printf("不努力一下,你都不知道什么叫绝望哦!\n"); break;
	case 2:printf("活到现在,朋友你的蛇还真顽强哦!\n"); break;
	case 3:printf("诶,好像有一丝丝厉害诶!\n"); break;
	case 4:printf("wow,不得了!\n"); break;
	case 5:printf("贪吃蛇界的faker!\n"); break;
	case 6:printf("中国电竞界的未来!\n"); break;
	case 7:printf("你真是无聊呢,玩这么久!\n"); break;
	case 8:printf("哇哦，犀利!\n"); break;
	case 9:printf("你是我真正的粉丝!\n"); break;
	case 10:printf("好啦,最后一条,截图给我哦!\n"); break;
	default: printf("怎么可能有人玩到50分以上\n"); break;
	}
	system("pause");
	exit(0);
}

int main(void) {
	game_before();
	game_run();
	game_over();
	return 0;
}