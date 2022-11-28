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

//back_buffer에 그리기 y=22
void drawToBackBuffer(const i, const j, char* image) {
	int ix = 0;
	while (1) {
		if (image[ix] == '\0') break;

		back_buffer[j][i + ix] = image[ix];

		ix++;
	}
}

//back_buffer와 front_buffer의 차이 캐칭
void render(int renderCheck) {
	for (int j = 0; j < HEIGHT; j++)
		for (int i = 0; i < WITDH; i++) {
			if (back_buffer[j][i] != front_buffer[j][i]) {
				gotoxy(i, j);

				if (renderCheck == 0)
					if (i >= 28 && i <= 31 && j == 33 ||
						i >= 28 && i <= 31 && j == 34 ||
						i >= 36 && i <= 39 && j == 33 ||
						i >= 36 && i <= 39 && j == 34 ||
						i >= 44 && i <= 47 && j == 33 ||
						i >= 44 && i <= 47 && j == 34)
						continue;

				switch (back_buffer[j][i]) {
				case '\0':
					printf(" ");
					break;
				case '|':
					textcolor(YELLOW1, YELLOW1);
					printf(" ");
					textcolor(WHITE, BLACK);
					break;
				case ',':
					textcolor(WHITE, BLACK);
					printf("━");
					break;
				case '.':
					textcolor(WHITE, BLACK);
					printf("┓");
					break;
				case 'D':
					textcolor(WHITE, WHITE);
					printf("                                              ");
					textcolor(WHITE, BLACK);
					break;
				case 'Q':
					textcolor(WHITE, BLACK);
					printf("                                              ");
					break;
				case '*':
					textcolor(CYAN1, BLACK);
					printf("*");
					textcolor(WHITE, BLACK);
					break;
				default:
					textcolor(WHITE, WHITE);
					printf("%c", back_buffer[j][i]);
					textcolor(WHITE, BLACK);
					break;
				}
			}
		}
	//update frame buffer
	for (int j = 0; j < HEIGHT; j++)
		for (int i = 0; i < WITDH; i++) {
			front_buffer[j][i] = back_buffer[j][i];
			back_buffer[j][i] = '\0';
		}
}

//체력바, hp를 계속해서 받아와 정수로 잘라서 출력함(100칸) -1차 완, 체력바 진행도에 따라 움직이도록 수정
void hp_bar(int hp) {
	if (hp == 10) {
		textcolor(WHITE, WHITE);
		//윗부분
		for (int i = 24; i <= 126; i += 2) {
			gotoxy(i, 4);
			printf("  ");
		}
		//중심
		gotoxy(24, 5);
		printf("  ");

		gotoxy(126, 5);
		printf("  ");

		gotoxy(24, 6);
		printf("  ");

		gotoxy(126, 6);
		printf("  ");
	}
	//hp바
	textcolor(WHITE, RED1);
	for (int i = 0; i < hp; i += 1) {
		gotoxy(26 + (i * 10), 5);
		printf("          ");
		gotoxy(26 + (i * 10), 6);
		printf("          ");
	}
	if (hp == 10) {
		textcolor(WHITE, WHITE);
		//아랫부분
		for (int i = 24; i <= 126; i += 2) {
			gotoxy(i, 7);
			printf("  ");
		}
	}
	textcolor(WHITE, BLACK);
}

void erase_hpBar() {
	textcolor(WHITE, BLACK);
		gotoxy(26, 5);
		printf("                                                                                                    ");
		gotoxy(26, 6);
		printf("                                                                                                    ");
}

//공룡 관련 -----------------------------------------------------------------------------------------------------------------------------

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

	//눈 19번줄
	textcolor(WHITE, RED1);
	y = 19;
	for (int j = 0; j < 2; j++) {
		gotoxy(26, y);
		printf("  ");
		y++;
	}
	textcolor(WHITE, BLACK);
}

//입 절반 벌린상태
void print_dino_halfmouthopen() {
	int y = 26;
	for (int j = 0; j < 2; j++) {//22
		for (int i = 0; i < 2; i++)
			drawToBackBuffer(28 + i, y, " ");
		y++;
	}//y28

	for (int j = 0; j < 2; j++) {//23
		for (int i = 0; i < 2; i++)
			drawToBackBuffer(28 + i, y, " ");
		y++;
	}//30

	for (int j = 0; j < 2; j++) {//24
		for (int i = 0; i < 2; i++)
			drawToBackBuffer(28 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(32 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(40 + i, y, " ");
		y++;
	}//32

	for (int j = 0; j < 2; j++) {//25
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(28 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(36 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(44 + i, y, " ");
		y++;
	}//34

	for (int j = 0; j < 2; j++) {//26
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(44 + i, y, " ");
		y++;
	}//36

	for (int j = 0; j < 2; j++) {//27
		drawToBackBuffer(2, y, "D");
		y++;
	}
}

//입 닫은상태
void print_dino_mouthclose() {
	int y = 26;
	for (int i = 0; i < 2; i++)//22
		drawToBackBuffer(28 + i, y, " ");
	y++;

	for (int j = 0; j < 2; j++) {//22.5
		for (int i = 0; i < 2; i++)
			drawToBackBuffer(28 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(32 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(40 + i, y, " ");
		y++;
	}

	for (int j = 0; j < 2; j++) {//23.5
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(28 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(36 + i, y, " ");
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(44 + i, y, " ");
		y++;
	}

	for (int j = 0; j < 2; j++) {//24.5
		for (int i = 0; i < 4; i++)
			drawToBackBuffer(44 + i, y, " ");
		y++;
	}

	for (int j = 0; j < 2; j++) {//25.5
		drawToBackBuffer(2, y, "D");
		y++;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------

// 캐릭터 관련 =========================================================================================================================

// 이동범위 53~146
void print_character(int X, int Y) {
	//캐릭터
	for (int i = 1; i <= 2; i++) {
		drawToBackBuffer(X + i, Y - 4, " ");
	}
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j < 4; j++) {
			drawToBackBuffer(X + j, Y - 3 + i, " ");
		}
	}
	for (int i = 0; i <= 2; i++) {
		drawToBackBuffer(X, Y + i, " ");
		drawToBackBuffer(X + 3, Y + i, " ");
	}
	//총
	drawToBackBuffer(X - 4, Y - 3, ",");
	drawToBackBuffer(X - 3, Y - 3, ".");
}
//======================================================================================================================================

//총 관련>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void shoot(int x, int y) {
	drawToBackBuffer(x, y, "*");
}


// 맵관련 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//장애물 그리기 48~149
void print_obs(int X, int h) {
	for (int i = 1; i <= h; i++) {
		drawToBackBuffer(X, 40-h+i, "|");
	}
}


//테두리 출력 -완료
void drawBox(int x1, int y1, int x2, int y2)
{
	int x, y;
	textcolor(MAGENTA1, MAGENTA1);
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
}

//게임 세팅
void init_game() {
	hp_bar(10);
	print_dino_mouthopen();
	print_character(70, 38);
}

//실행
int main() {
	unsigned char ch;

	int x;
	gotoxy(0, 0);
	scanf("%d", &x);

	//공룡
	int HP_boss = 100;

	//버퍼 초기화
	for(int j=0;j<HEIGHT;j++)
		for (int i = 0; i < WITDH; i++) {
			front_buffer[j][i] = '\0';
			back_buffer[j][i] = '\0';
		}

	int renderCheck;

	//캐릭터	
	int keep_moving = 0, moving_check = STOP;
	int oldx, oldy, newx, newy;

	int HP = 3;

	int sleep_stack = 0;
	int jump_count = 0; //땅에 닿아있는지 확인
	int jump_check = 0; //땅에 닿아있는지 확인 keep_moving을 위한 변수

	//총알
	int shooting = -1;
	int bullet = 1;
	int x_bullet, y_bullet;

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
		if (sleep_stack > 13) {
			if (newx_obs == 149) {
				h = rand() % 3 + 3;
				print_obs(newx_obs, h);
			}
			else if (newx_obs <= 47) {
				print_obs(newx_obs + 1, h, " ");
				newx_obs = 150;
			}
			else {
				print_obs(newx_obs, h);
			}
		}
		//공룡
		if (sleep_stack % 16 < 8) {
			renderCheck = 0;
			for (int j = 0; j < 2; j++) {//25.5
				drawToBackBuffer(2, 36 + j, "Q");
			}
			print_dino_mouthclose();
		}
		else {
			renderCheck = 1;
			for (int j = 0; j < 2; j++) {//25.5
				drawToBackBuffer(2, 33 + j, "Q");
			}
			print_dino_halfmouthopen();
		}
		//캐릭터
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다

			if (ch == SPACE) {
				shooting = shooting * -1;
			}

			else if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키 -- 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
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
		}
		if (keep_moving) { // 움직이고 있으면
			switch (ch) {
			case UP:
				if (jump_count == 0) {
					newy = oldy - 3;
					jump_count = 3;
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
					break;
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
			case SPACE:
				if (moving_check == GORIGHT) {
					if (oldx < 145) {
						newx = oldx + 2;
					}
					break;
				}
				else if (moving_check == GOLEFT) {
					if (oldx >= 54) {
						newx = oldx - 2;
					}
					break;
				}
			default:
				break;
			}
			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			if (jump_count < 12 && jump_count>0) {//점프
				jump_count += 3;
				newy = oldy - 3;
			}
			else if (jump_count >= 12) {//낙하
				jump_count += 3;
				newy = oldy + 3;
				if (jump_count == 24) {
					/*if (kbhit())
						while (kbhit())
							getch();*/
					oldy = newy;
					jump_count = 0;
					moving_check = STOP;
					jump_check = 1;
				}
			} //점프관련 처리
			if (jump_check == 0) keep_moving = 1; //1:계속이동, 0:한번에 한칸씩이동
			else {
				keep_moving = 0;
				jump_check = 0;
			}
		}

		if (sleep_stack % 8 == 0) {
			if (shooting == 1) {
				if (bullet == 1) {
					bullet = 0;
					x_bullet = newx - 5;
					y_bullet = newy - 3;
				}
			}
		}

		if (bullet == 0) {
			shoot(x_bullet,y_bullet);
			x_bullet -= 6;
			if (x_bullet <= 47) {
				bullet = 1;
				HP_boss -= 5;
			}
		}

		//보스 체력
		{
			if (HP_boss <= 0) {
				erase_hpBar();
			}
			else if (HP_boss <= 10) {
				erase_hpBar();
				hp_bar(1);
			}
			else if (HP_boss <= 20) {
				erase_hpBar();
				hp_bar(2);
			}
			else if (HP_boss <= 30) {
				erase_hpBar();
				hp_bar(3);
			}
			else if (HP_boss <= 40) {
				erase_hpBar();
				hp_bar(4);
			}
			else if (HP_boss <= 50) {
				erase_hpBar();
				hp_bar(5);
			}
			else if (HP_boss <= 60) {
				erase_hpBar();
				hp_bar(6);
			}
			else if (HP_boss <= 70) {
				erase_hpBar();
				hp_bar(7);
			}
			else if (HP_boss <= 80) {
				erase_hpBar();
				hp_bar(8);
			}
			else if (HP_boss <= 90) {
				erase_hpBar();
				hp_bar(9);
			}
		}

		if (sleep_stack > 13) {
			if (shooting == 1)
				newx_obs -= 4;
			else
				newx_obs -= 3;
		}

		sleep_stack++; //개체의 속도 조절

		print_character(newx, newy);

		//피격 판정 처리


		render(renderCheck);		

		Sleep(50);
	}
}