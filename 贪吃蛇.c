#include<stdio.h>
#include<stdlib.h>
#include<time.h> //��ȡʱ��
#include<conio.h>//����̨�⺯��
#include<windows.h>//windows�⺯��
#include<mmsystem.h>//windows�ӿں���ͷ�ļ�
#pragma comment(lib, "winmm.lib")//#pragma ָ�����winmm��

/*�����ߵĽڵ�*/
typedef struct snake
{

	int x;

	int y;

	struct snake *next;

}s1;

int direction1, flag = 0, sum = 0, add = 1;//�����жϷ��������ж�
s1 *q1, *head1, *food;//�����ߵı���ָ��,��ͷָ�룬ʳ��ָ��

void setgametitle();
void face();
//void music_start();
void start();
//void myplaysound()��
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


//����
void setgametitle() {
	system("title ������̰����");
}

//����
void face() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                                                       ��ӭ����̰����\n");
	printf("                                                        ���ո����ʼ   \n");
	printf("                                                     �� �� �� ��   ���Ʒ���     \n");
}

//��Ϸ��ʼ
void start() {
	char get;
	while (1) {
		get = _getch();
		if (get == ' ') {
			break;
		}
	}
}

/*�������ļ�*/
//��������
/*void music_start() {
mciSendString("play ", NULL, 0, NULL);
Sleep(50000);
}*/

//ֹͣ����
/*void music_stop() {
char get2;
get2 = getch();
if (get2 == 'p') {
mciSendString("close 1.mp3", NULL, 0, NULL);
}
}*/

/*��һ�ַ���ֻ�ܲ�wav�ļ�
void myplaysound(){
PlaySound(TEXT("Cruzo - Epic Sax Guy (Remix) [mqms2].wav"),NULL,SND_FILENAME|SND_SYNC);
}*/

/*ֹͣ����
void music_stop(){
char get2;
get2=getch;
if("p"==get2){
PlaySound(NULL,0,0);
}
}
*/

//���ù��
void Pos(int x, int y) {
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//������ͼ
void map_create() {
	int i;
	//��ӡ���±߿�
	for (i = 0; i < 60; i += 2) {
		Pos(i, 0);
		printf("��");
		Pos(i, 30);
		printf("��");
	}
	//��ӡ���ұ߿�
	for (i = 0; i < 30; i++) {
		Pos(0, i);
		printf("��");
		Pos(58, i);
		printf("��");
	}
}

//���ߣ��Ӻ���ǰ��
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
	//�������
	while (tail1 != NULL) {
		Pos(tail1->x, tail1->y);
		printf("��");
		tail1 = tail1->next;
	}
}

//�ж��Ƿ�ײǽ
void wallcrash() {
	if (head1->x >= 59 || head1->x <= 0 || head1->y >= 29 || head1->y <= 0) {
		flag = 1;
	}
}

//�ж��Ƿ�ҧ���Լ�
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

//�������ʳ��
void food_produce() {
	//���λ��
	srand((unsigned int)time(NULL));
	//����ʳ��
	s1*food1;
	food1 = (s1*)malloc(sizeof(s1));
	while (food1->x % 2 != 0 || food1->x >= 58 || food1->x <= 0 || head1->y >= 29 || head1->y <= 0) {
		food1->x = rand() % 53 + 2;
	}
	food1->y = rand() % 28 + 1;
	//�ж��Ƿ�������غ�
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
	printf("��");
}

//���ƶ�
void snake1_move() {
	s1 * nexthead1;
	wallcrash();
	flag = biteitself();
	nexthead1 = (s1*)malloc(sizeof(s1));

	if (direction1 == 1)

	{

		nexthead1->x = head1->x;

		nexthead1->y = head1->y - 1;

		if (nexthead1->x == food->x && nexthead1->y == food->y)//�����һ����ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//���û��ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

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

		if (nexthead1->x == food->x && nexthead1->y == food->y)//�����һ����ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//���û��ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

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

		if (nexthead1->x == food->x && nexthead1->y == food->y)//�����һ����ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//���û��ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

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

		if (nexthead1->x == food->x && nexthead1->y == food->y)//�����һ����ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1 != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

				q1 = q1->next;

			}

			sum += add;

			food_produce();

		}

		else//���û��ʳ��//

		{

			nexthead1->next = head1;

			head1 = nexthead1;

			q1 = head1;

			while (q1->next->next != NULL)

			{

				Pos(q1->x, q1->y);

				printf("��");

				q1 = q1->next;

			}

			Pos(q1->next->x, q1->next->y);

			printf("  ");

			free(q1->next);

			q1->next = NULL;

		}

	}
}




//��Ϸ��ͣ
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
	printf("�ս�������ͣ��,��ֹ����߲�С������");
	Pos(80, 15);
	printf("ÿ�Ե�һ���ǵ� 1 ��");
	Pos(80, 16);
	printf("�� �� �� �� �ֱ������������");
	Pos(80, 17);
	printf("���ո����ͣ���ٰ����ָ���ESC���˳�");
	Pos(80, 18);
	printf("��Ŀǰ�ķ����ǣ�%d", sum);
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
	case 1:printf("���Ų�����ΪʲôҪȥײǽ!\n"); break;
	case 2:printf("��ҧ���Լ��ˣ�\n"); break;
	}
	printf("������շ����ǣ� %d\n", sum);
	switch ((int)(sum / 5)) {
	case 0:printf("�Ҿ�Ȼ����ô�˵�����!\n"); break;
	case 1:printf("��Ŭ��һ��,�㶼��֪��ʲô�о���Ŷ!\n"); break;
	case 2:printf("�����,��������߻�����ǿŶ!\n"); break;
	case 3:printf("��,������һ˿˿������!\n"); break;
	case 4:printf("wow,������!\n"); break;
	case 5:printf("̰���߽��faker!\n"); break;
	case 6:printf("�й��羺���δ��!\n"); break;
	case 7:printf("������������,����ô��!\n"); break;
	case 8:printf("��Ŷ��Ϭ��!\n"); break;
	case 9:printf("�����������ķ�˿!\n"); break;
	case 10:printf("����,���һ��,��ͼ����Ŷ!\n"); break;
	default: printf("��ô���������浽50������\n"); break;
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