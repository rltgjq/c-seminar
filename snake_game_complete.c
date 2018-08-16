#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>	//콘솔 input output
#include <math.h>

#define bg_x 30
#define bg_y 20

#define none 0
#define body 1	//뱀 몸통
#define head 2
#define apple 3
#define mrg 4 //테두리

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

int bg[bg_y][bg_x]; //배경
int x[100], y[100];	//머리의 x,y의 좌표 (꼬리가 자취를 따라가게하기위해)
int apple_x, apple_y;	//먹이 x,y좌표
int length;	//뱀 길이
int key;	//키보드 키
int dir;	//방향
int n;
int state;	//state 0 : 시작화면 1: 게임진행
int check_state;	//checkstate함수의 return 값을 받을 인수

void gotoxy(int x, int y)	//이 위치에 커서를 가져다 둔다는 얘기
						  
{
	COORD Pos = { x - 1, y - 1 };	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void start() {
	int i;
	system("cls");
	while (1) {
	gotoxy(10, 11);	
	printf("게임을 시작하시겠습니까?");
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
	printf("아무키나 눌러주세요.");
	while (1) {
		if (_kbhit()) {
			state = 0;
			break;
		}
		else {
		}
	}
}

void check(int k) {	//k라는 위아래,좌우값을 받았을 때 그 방향에 벽이나 몸이 있는지 확인한다. 있다면 게임오버
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

void mv_cell(int k) {	//check에서 가려는 방향에 아무것도 없다는 것을 확인했으므로 전체적으로 셀을 이동해준다.
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
				printf("■");
			}
			else if (bg[j][i] == body)
				printf("○");
			else if (bg[j][i] == head)
				printf("●");
			else if (bg[j][i] == apple)
				printf("♥");
			else
				printf("  ");
		}
		printf("\n");
	}
}

void move() {
	fflush(stdin);	//윈도우 지원함수로 stdin 을 날려버린다(청소한다) -> 이전까지의 찌꺼기같은것들
	if (_kbhit()) {
		do { key = _getch(); } while (key == 224);	//key값이 224가 아닌 다른 값을 받으면 다음 if문을 진행한다.
	}
	if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP)) {	//바로 뒤로 갈 수 없음.
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
	key = 0;	//입력했던 키 초기화

	if (length < 4)
		Sleep(100);	//게임 진행 속도 조절
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

int checkstate() {	//죽었는지 확인
	if (state == 2)
		return 1;
	else
		return 0;
}
int main() {
	//init()
	state = 0;	
	dir = RIGHT;	//기본방향을 오른쪽으로 정함 -> 초기화과정
	apple_x = 0, apple_y = 0;	//초기화
	srand(time(NULL));
	apple_x = ((rand() % 28) + 1);
	apple_y = ((rand() % 18) + 1);
	check_state = 0;
	while (1) {
		length = 1;	//머리밖에없음
		start();

		for (int j = 0; j < bg_y; j++)
		{
			for (int i = 0; i < bg_x; i++)
			{
				if (i == 0 || i == bg_x - 1 || j == 0 || j == bg_y - 1)
				{
					bg[j][i] = mrg; //margin - 테두리
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