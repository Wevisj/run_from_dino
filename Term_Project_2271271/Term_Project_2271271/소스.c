#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNING

//화면정의
#define	WITDH 152
#define HEIGHT 41

char front_buffer[HEIGHT][WITDH];
char back_buffer[HEIGHT][WITDH];

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

//키 정의
#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define SPACE 0x20

#define GOLEFT 0
#define GORIGHT 1
#define STOP 2

void removeCursor(void) { // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

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

//공룡 관련 -----------------------------------------------------------------------------------------------------------------------------
//공룡 지우기
void erase_dino() {
	textcolor(WHITE, BLACK);
	int x = 2, y = 14;
	for (y; y <= 39; y++) {
		gotoxy(x, y);
		printf("                                              ");
	}
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
	textcolor(WHITE, RED1);
	y = 19;
	for (int j = 0; j < 2; j++) {
		gotoxy(26, y);
		printf("  ");
		y++;
	}
}

//입 닫은상태
void print_dino_mouthclose() {
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
			if (i <= 18 || i == 36 || i == 44) printf("  ");
			if (i == 28 || i == 30 || i == 38 || i == 46) printf("  ");
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
	y--;

	for (int j = 0; j < 2; j++) {
		for (int i = 4; i <= 48; i++) {//24
			gotoxy(i, y);
			if (i == 28 || i == 32 || i == 40) printf("  ");
			if (i == 34 || i == 42) printf("  ");
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
	textcolor(WHITE, RED1);
	y = 19;
	for (int j = 0; j < 2; j++) {
		gotoxy(26, y);
		printf("  ");
		y++;
	}
}

//공룡 최종출력 - 짝수 : Open -> Close, 홀수 : Close -> Open
void print_dino(int n) {
	erase_dino();
	if (n % 2 == 0) {
		print_dino_mouthclose();
	}
	else {
		print_dino_mouthopen();
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------

// 캐릭터 관련 =========================================================================================================================
// 이동범위 53~146
void print_character(int X, int Y) {
	//캐릭터
	textcolor(BLACK, WHITE);
	gotoxy(X + 1, Y - 4);
	printf("  ");
	for (int i = 0; i <= 2; i++) {
		textcolor(WHITE, WHITE);
		gotoxy(X, Y - 3 + i);
		printf("    ");
	}
	for (int i = 0; i <= 2; i++) {
		gotoxy(X, Y + i);
		printf(" ");
		gotoxy(X + 3, Y + i);
		printf(" ");
	}
	//총
	textcolor(WHITE, BLACK);
	gotoxy(X - 4, Y - 3);
	printf("━┓");
}

void erase_character(int X, int Y) {
	//캐릭터
	textcolor(BLACK, BLACK);
	gotoxy(X + 1, Y - 4);
	printf("●");
	for (int i = 0; i <= 2; i++) {
		textcolor(WHITE, BLACK);
		gotoxy(X, Y - 3 + i);
		printf("    ");
	}
	for (int i = 0; i <= 2; i++) {
		gotoxy(X, Y + i);
		printf(" ");
		gotoxy(X + 3, Y + i);
		printf(" ");
	}
	//총
	textcolor(BLACK, BLACK);
	gotoxy(X - 4, Y - 3);
	printf("━┓");
}
//======================================================================================================================================

// 맵관련 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//장애물 그리기 48~149
void print_obs(int X, int h) {
	textcolor(WHITE, YELLOW1);
	for (int i = 1; i <= h; i++) {
		gotoxy(X, 40 - h + i);
		printf(" ");
	}
	textcolor(WHITE, BLACK);
}

//장애물 지우기
void erase_obs(int X, int h) {
	textcolor(WHITE, BLACK);
	for (int i = 1; i <= h; i++) {
		gotoxy(X, 40 - h + i);
		printf(" ");
	}
}

//지우고, 새로운 위치에 그리기
void obstacle(int oldx, int newx, int h) {
	erase_obs(oldx, h);
	print_obs(newx, h);
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
	print_character(70, 38);
}

//실행
int main() {
	unsigned char ch;

	//버퍼 초기화
	for(int j=0;j<HEIGHT;j++)
		for (int i = 0; i < WITDH; i++) {
			front_buffer[j][i] = '\0';
			back_buffer[j][i] = '\0';
		}

	int x; //프로그램 정지용도

	//캐릭터	
	int keep_moving = 0, moving_check = STOP;
	int oldx, oldy, newx, newy;

	int HP = 3;

	int sleep_stack = 0;
	int jump_count = 0; //땅에 닿아있는지 확인
	int jump_check = 0; //땅에 닿아있는지 확인 keep_moving을 위한 변수

	//장애물
	int oldx_obs, newx_obs, h;

	newx_obs = 149;

	oldx = newx = 70;
	oldy = newy = 38;

	removeCursor();
	drawBox(0, 0, 150, 40);
	init_game(); // 테두리 그리고 공룡 머리 만들기

	while (1) {
		//장애물 관련
		if (newx_obs == 149) {
			h = rand() % 3 + 3;
			print_obs(newx_obs, h);
		}
		else if (newx_obs == 47) {
			erase_obs(newx_obs + 1, h);
			newx_obs = 150;
		}
		else {
			obstacle(oldx_obs, newx_obs, h);
		}
		//공룡
		if (sleep_stack % 5 == 0) {
			print_dino(sleep_stack);
		}
		//캐릭터
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			if (jump_count == 0) ch = getch(); // key 값을 읽는다

			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키 -- 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
				ch = getch();
				switch (ch) {
				case UP:
					keep_moving = 1;
					break;
				case LEFT:
					if (moving_check == STOP) keep_moving = 1;
					else if (moving_check == GORIGHT) {
						keep_moving = 0;
						moving_check = STOP;
					}
					else keep_moving = 1;
					break;
				case RIGHT:
					if (moving_check == STOP) keep_moving = 1;
					if (moving_check == GOLEFT) {
						keep_moving = 0;
						moving_check = STOP;
					}
					else keep_moving = 1;
					break;
				}
			}
		} //키 읽기
		if (keep_moving) { // 움직이고 있으면
			switch (ch) {
			case UP:
				if (jump_count == 0) {
					newy = oldy - 12;
					jump_count = 12;
				}
				if (moving_check == GORIGHT) { //점프중 움직임-우
					if (oldx < 145) {
						newx = oldx + 2;
						moving_check = GORIGHT;
					}
					else moving_check = STOP;
					break;
				}
				else if (moving_check == GOLEFT) { //점프중 움직임-왼
					if (oldx >= 54) {
						newx = oldx - 2;
						moving_check = GOLEFT;
					}
					else moving_check = STOP;
					break;
				}
				else

			case LEFT:
				if (oldx >= 54) {
					newx = oldx - 2;
					moving_check = GOLEFT;
				}
				else moving_check = STOP;
				break;
			case RIGHT:
				if (oldx < 145) {
					newx = oldx + 2;
					moving_check = GORIGHT;
				}
				else moving_check = STOP;
				break;
			}
			erase_character(oldx, oldy);
			print_character(newx, newy);
			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			if (jump_count != 0) {
				jump_count -= 1;
				newy = oldy + 1;
				if (jump_count == 0) {
					erase_character(oldx, oldy);
					print_character(newx, newy);
					oldy = newy;
					moving_check = STOP;
					jump_check = 1;
				}
			} //점프관련 처리
			if (jump_check == 0) keep_moving = 1; //1:계속이동, 0:한번에 한칸씩이동
			else {
				keep_moving = 0;
				jump_check = 0;
			}
		} //지속적인 움직임
		sleep_stack++; //개체의 속도 조절
		/*for (int i = 0; i <= 2; i++) {
			gotoxy(newx, newy - 3 + i);
		}
		for (int i = 0; i <= 2; i++) {
			if (newx, newy + i || newx + 3, newy + i)
		}*/
		oldx_obs = newx_obs;
		newx_obs--;
		Sleep(100);
	}
}