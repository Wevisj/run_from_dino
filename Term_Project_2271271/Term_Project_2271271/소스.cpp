#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNING

//색상정의
#define BLACK    0
#define BLUE1    1
#define GREEN1    2
#define CYAN1    3
#define RED1    4
#define MAGENTA1 5
#define YELLOW1    6
#define GRAY1    7
#define GRAY2    8
#define BLUE2    9
#define GREEN2    10
#define CYAN2    11
#define RED2    12
#define MAGENTA2 13
#define YELLOW2    14
#define WHITE    15

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

//체력바, hp를 계속해서 받아와 정수로 잘라서 출력함(100칸) -1차 완, 체력바 진행도에 따라 움직이도록 수정
void hp_bar(int hp) {
	int y = 4;
	textcolor(WHITE, WHITE);
	//윗부분
	for (int i = 24; i <= 128; i += 2) {
		gotoxy(i, y);
		printf("  ");
	}
	//중심
	y++;
	gotoxy(24, y);
	printf("  ");


	gotoxy(128, y);
	printf("  ");

	y++;
	gotoxy(24, y);
	printf("  ");


	gotoxy(128, y);
	printf("  ");
	//hp바
	textcolor(RED1, RED1);
	for (int i = 26; i <= 127; i ++) {
		gotoxy(i, y-1);
		printf(" ");
		gotoxy(i, y);
		printf(" ");
	}
	textcolor(WHITE, WHITE);

	//아랫부분
	y++;
	for (int i = 24; i <= 128; i += 2) {
		gotoxy(i, y);
		printf("  ");
	}
	textcolor(WHITE, BLACK);
}

//입 벌린상태
void print_dino_mouthopen() {
	int y = 14;
	textcolor(WHITE, WHITE);
	//머리
	for (int j = 0; j < 2; j++) {
		for (int i = 36; i <= 47; i++) {//16
			gotoxy(i, y);
			printf(" ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 8; i <= 47; i++) {//17
			gotoxy(i, y);
			if (i >= 40 && i <= 43) {
				continue;
			}
			printf(" ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 8; i <= 52; i++) {//18
			gotoxy(i, y);
			if (i == 8 || i == 44) printf("  ");
			if (i == 10 || i == 46) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 8; i <= 48; i++) {//19
			gotoxy(i, y);
			if (i <= 18 || i == 44 || i == 46) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 8; i <= 46; i++) {//20
			gotoxy(i, y);
			if (i == 16 || i >= 40) printf("  ");
			if (i == 18 || i == 32 || i == 34) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 2; i <= 48; i++) {//21
			gotoxy(i, y);
			if (i <= 18 || i == 36 || i==44) printf("  ");
			if (i == 28 || i == 30 || i == 38 || i == 46) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 4; i <= 48; i++) {//22
			gotoxy(i, y);
			if (i == 28) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 4; i <= 48; i++) {//23
			gotoxy(i, y);
			if (i == 28) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 4; i <= 48; i++) {//24
			gotoxy(i, y);
			if (i == 28 || i == 32 || i == 40) printf("  ");
			if (i == 34 || i == 42	) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 4; i <= 46; i++) {//25
			gotoxy(i, y);
			if (i == 28 || i == 30) printf("  ");
			if (i == 36 || i == 44) printf("  ");
			if (i == 38 || i == 46) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 4; i <= 48; i++) {//26
			gotoxy(i, y);
			if (i == 44) printf("  ");
			if (i == 46) printf("  ");
		}
		y++;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 2; i <= 47; i++) {//27
			gotoxy(i, y);
			printf(" ");
		}
		y++;
	}
	//눈 19번줄
	/*for (int j = 0; j < 2; j++) {
		for(int i=)
	}*/
}

void character() {
	/*gotoxy(50, 20);
	printf("|");
	gotoxy(49, 20);
	printf("|");
	gotoxy(48, 21);
	printf("■");
	gotoxy(49, 21);
	printf("■");*/
}

//테두리 출력 -완료
void drawBox(int x1, int y1, int x2, int y2)
{
	int x, y;
	textcolor(WHITE, MAGENTA1);
	for (x = x1; x < x2; x += 2) {
		gotoxy(x, 0);
		printf("  ");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x, y);
		printf("  ");
	}
	for (x = x1; x <= x2; x += 2) {
		gotoxy(x, y);
		printf("  ");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("  ");
	}
	textcolor(WHITE, BLACK);
}

//게임 세팅
void init_game() {
	hp_bar(100);
	print_dino_mouthopen();
	character();
}

//실행
int main() {
	int x;
	drawBox(0, 0, 150, 40);
	init_game();
	scanf("%d", &x);
}