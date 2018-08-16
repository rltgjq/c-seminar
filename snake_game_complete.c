#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>	//�ܼ� input output
#include <math.h>

#define bg_x 30
#define bg_y 20

#define none 0
#define body 1	//�� ����
#define head 2
#define apple 3
#define mrg 4 //�׵θ�

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

int bg[bg_y][bg_x]; //���
int x[100], y[100];	//�Ӹ��� x,y�� ��ǥ (������ ���븦 ���󰡰��ϱ�����)
int apple_x, apple_y;	//���� x,y��ǥ
int length;	//�� ����
int key;	//Ű���� Ű
int dir;	//����
int n;
int state;	//state 0 : ����ȭ�� 1: ��������
int check_state;	//checkstate�Լ��� return ���� ���� �μ�

void gotoxy(int x, int y)	//�� ��ġ�� Ŀ���� ������ �дٴ� ���
						  
{
	COORD Pos = { x - 1, y - 1 };	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void start() {
	int i;
	system("cls");
	while (1) {
	gotoxy(10, 11);	
	printf("������ �����Ͻðڽ��ϱ�?");
	gotoxy(12, 12);
	printf("1.Yes	2.No");
	gotoxy(20, 13);
	scanf_s("%d", &i);
	
		if (i == 1) {
			state = 1;
			break;
		}
		else if (i == 2) {
			exit(0);
		}
		else {
			continue;
		}
	}
}


void gameover() {
	int i;
	system("cls");
	gotoxy(15, 11);
	printf("GAME OVER");
	gotoxy(10, 12);
	printf("�ƹ�Ű�� �����ּ���.");
	while (1) {
		if (_kbhit()) {
			state = 0;
			break;
		}
		else {
		}
	}
}

void check(int k) {	//k��� ���Ʒ�,�¿찪�� �޾��� �� �� ���⿡ ���̳� ���� �ִ��� Ȯ���Ѵ�. �ִٸ� ���ӿ���
	if (k == UP) {
		if (bg[y[0] - 1][x[0]] == body || bg[y[0] - 1][x[0]] == mrg) {
			state = 2;
		}
	}
	else if (k == DOWN) {
		if (bg[y[0] + 1][x[0]] == body || bg[y[0] + 1][x[0]] == mrg) {
			state = 2;
		}
	}
	else if (k == LEFT) {
		if (bg[y[0]][x[0] - 1] == body || bg[y[0]][x[0] - 1] == mrg) {
			state = 2;
		}
	}
	else if (k == RIGHT) {
		if (bg[y[0]][x[0] + 1] == body || bg[y[0]][x[0] + 1] == mrg) {
			state = 2;
		}
	}
}

void mv_cell(int k) {	//check���� ������ ���⿡ �ƹ��͵� ���ٴ� ���� Ȯ�������Ƿ� ��ü������ ���� �̵����ش�.
	if (k == UP && bg[y[0] - 1][x[0]] != apple) {
		for (n = length; n > 0; n--)
		{
			if (length == 1)
			{
				bg[y[n - 1]][x[n - 1]] = none;
				break;
			}
			else
			{
				if (n == length) {
					bg[y[n - 1]][x[n - 1]] = none;
				}
				if (n == 1) {
					break;
				}
				else
				{
					x[n - 1] = x[n - 2];
					y[n - 1] = y[n - 2];
					bg[y[n - 1]][x[n - 1]] = body;
				}
			}
		}
		y[0] -= 1;
		bg[y[0]][x[0]] = head;
	}
	else if (k == UP && bg[y[0] - 1][x[0]] == apple) {
		bg[apple_y][apple_x] = head;
		length += 1;
		for (n = length; n > 1; n--)
		{
			if (n == length) {
				bg[y[n - 1]][x[n - 1]] = none;
			}
			x[n - 1] = x[n - 2];
			y[n - 1] = y[n - 2];
			bg[y[n - 1]][x[n - 1]] = body;
		}
		y[0] -= 1;
		apple_x = ((rand() % 28) + 1);
		apple_y = ((rand() % 18) + 1);
		bg[apple_y][apple_x] = apple;
	}

	else if (k == DOWN && bg[y[0] + 1][x[0]] != apple) {
		for (n = length; n > 0; n--)
		{
			if (length == 1)
			{
				bg[y[n - 1]][x[n - 1]] = none;
				break;
			}
			else
			{
				if (n == length) {
					bg[y[n - 1]][x[n - 1]] = none;
				}
				if (n == 1) {
					break;
				}
				else
				{
					x[n - 1] = x[n - 2];
					y[n - 1] = y[n - 2];
					bg[y[n - 1]][x[n - 1]] = body;
				}
			}
		}
		y[0] += 1;
		bg[y[0]][x[0]] = head;
	}
	else if (k == DOWN && bg[y[0] + 1][x[0]] == apple) {
		bg[apple_y][apple_x] = head;
		length += 1;
		for (n = length; n > 1; n--)
		{
			if (n == length) {
				bg[y[n - 1]][x[n - 1]] = none;
			}
			x[n - 1] = x[n - 2];
			y[n - 1] = y[n - 2];
			bg[y[n - 1]][x[n - 1]] = body;
		}
		y[0] += 1;
		apple_x = ((rand() % 28) + 1);
		apple_y = ((rand() % 18) + 1);
		bg[apple_y][apple_x] = apple;
	}

	else if (k == LEFT && bg[y[0]][x[0] - 1] != apple) {
		for (n = length; n > 0; n--)
		{
			if (length == 1)
			{
				bg[y[n - 1]][x[n - 1]] = none;
				break;
			}
			else
			{
				if (n == length) {
					bg[y[n - 1]][x[n - 1]] = none;
				}
				if (n == 1) {
					break;
				}
				else
				{
					x[n - 1] = x[n - 2];
					y[n - 1] = y[n - 2];
					bg[y[n - 1]][x[n - 1]] = body;
				}
			}
		}
		x[0] -= 1;
		bg[y[0]][x[0]] = head;
	}
	else if (k == LEFT && bg[y[0]][x[0] - 1] == apple) {
		bg[apple_y][apple_x] = head;
		length += 1;
		for (n = length; n > 1; n--)
		{
			if (n == length) {
				bg[y[n - 1]][x[n - 1]] = none;
			}
			x[n - 1] = x[n - 2];
			y[n - 1] = y[n - 2];
			bg[y[n - 1]][x[n - 1]] = body;
		}
		x[0] -= 1;
		apple_x = ((rand() % 28) + 1);
		apple_y = ((rand() % 18) + 1);
		bg[apple_y][apple_x] = apple;
	}

	else if (k == RIGHT && bg[y[0]][x[0] + 1] != apple) {
		for (n = length; n > 0; n--)
		{
			if (length == 1)
			{
				bg[y[n - 1]][x[n - 1]] = none;
				break;
			}
			else
			{
				if (n == length) {
					bg[y[n - 1]][x[n - 1]] = none;
				}
				if (n == 1) {
					break;
				}
				else
				{
					x[n - 1] = x[n - 2];
					y[n - 1] = y[n - 2];
					bg[y[n - 1]][x[n - 1]] = body;
				}
			}
		}
		x[0] += 1;
		bg[y[0]][x[0]] = head;
	}
	else if (k == RIGHT && bg[y[0]][x[0] + 1] == apple) {
		bg[apple_y][apple_x] = head;
		length += 1;
		for (n = length; n > 1; n--)
		{
			if (n == length) {
				bg[y[n - 1]][x[n - 1]] = none;
			}
			x[n - 1] = x[n - 2];
			y[n - 1] = y[n - 2];
			bg[y[n - 1]][x[n - 1]] = body;
		}
		x[0] += 1;
		apple_x = ((rand() % 28) + 1);
		apple_y = ((rand() % 18) + 1);
		bg[apple_y][apple_x] = apple;
	}
}

void draw() {
	gotoxy(1, 1);
	for (int j = 0; j < bg_y; j++) {
		for (int i = 0; i < bg_x; i++) {
			if (bg[j][i] == mrg)  //if (i == 0 || i == bg_x - 1 || j = 0 || j == bg_y - 1)
			{
				printf("��");
			}
			else if (bg[j][i] == body)
				printf("��");
			else if (bg[j][i] == head)
				printf("��");
			else if (bg[j][i] == apple)
				printf("��");
			else
				printf("  ");
		}
		printf("\n");
	}
}

void move() {
	fflush(stdin);	//������ �����Լ��� stdin �� ����������(û���Ѵ�) -> ���������� ��ⰰ���͵�
	if (_kbhit()) {
		do { key = _getch(); } while (key == 224);	//key���� 224�� �ƴ� �ٸ� ���� ������ ���� if���� �����Ѵ�.
	}
	if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP)) {	//�ٷ� �ڷ� �� �� ����.
		if (key == LEFT || key == RIGHT || key == DOWN || key == UP)
			dir = key;
	}

	switch (key) {
	case ESC:
		exit(0);
		break;
	case LEFT:
	case RIGHT:
	case UP:
	case DOWN:
	default:
		check(dir);
		mv_cell(dir);
		draw();
		break;
	}
	key = 0;	//�Է��ߴ� Ű �ʱ�ȭ

	if (length < 4)
		Sleep(100);	//���� ���� �ӵ� ����
	else if (length >= 4 && length < 7)
		Sleep(80);
	else if (length >= 7 && length < 10)
		Sleep(60);
	else if (length >= 10 && length < 13)
		Sleep(40);
	else if (length >= 13 && length < 16)
		Sleep(20);
	else
		Sleep(5);
}

int checkstate() {	//�׾����� Ȯ��
	if (state == 2)
		return 1;
	else
		return 0;
}
int main() {
	//init()
	state = 0;	
	dir = RIGHT;	//�⺻������ ���������� ���� -> �ʱ�ȭ����
	apple_x = 0, apple_y = 0;	//�ʱ�ȭ
	srand(time(NULL));
	apple_x = ((rand() % 28) + 1);
	apple_y = ((rand() % 18) + 1);
	check_state = 0;
	while (1) {
		length = 1;	//�Ӹ��ۿ�����
		start();

		for (int j = 0; j < bg_y; j++)
		{
			for (int i = 0; i < bg_x; i++)
			{
				if (i == 0 || i == bg_x - 1 || j == 0 || j == bg_y - 1)
				{
					bg[j][i] = mrg; //margin - �׵θ�
				}
				else if (i == apple_x && j == apple_y)
				{
					bg[j][i] = apple;
				}
				else
				{
					bg[j][i] = none;	//background
				}
			}
		}

		//set initial position
		x[0] = (bg_x / 2) - 4, y[0] = bg_y / 2;
		bg[y[0]][x[0]] = head;
		//init finish
		while (1) {
			draw();
			move();
			check_state = checkstate();
			if (check_state == 1) {
				break;
			}
		}
		gameover();
	}
}