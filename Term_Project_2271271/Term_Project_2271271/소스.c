#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


//화면정의
#define   WITDH 152
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
    for (int j = 20; j < HEIGHT; j++)
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
                case '(':
                    textcolor(CYAN1, BLACK);
                    printf("(");
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
            if (i <= 18 || i == 36 || i == 44) printf("  ");
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

void erase_characterHp(int i) {
    int x = 118;
    textcolor(WHITE, BLACK);
    for (int j = 0; j < i; j++) {
        gotoxy(x + 2, 9);
        printf("  ");
        gotoxy(x + 6, 9);
        printf("  ");
        gotoxy(x, 10);
        printf("          ");
        gotoxy(x + 2, 11);
        printf("      ");
        gotoxy(x + 4, 12);
        printf("  ");
        x -= 15;
    }
    textcolor(WHITE, RED1);
}

void print_characterHp(int hp) {
    int x = 88;
    textcolor(WHITE, RED1);
    switch (hp) {
    case 4:
        x = 118;
        textcolor(WHITE, YELLOW2);
        gotoxy(x + 2, 9);
        printf("  ");
        gotoxy(x + 6, 9);
        printf("  ");
        gotoxy(x, 10);
        printf("          ");
        gotoxy(x + 2, 11);
        printf("      ");
        gotoxy(x + 4, 12);
        printf("  ");
        textcolor(WHITE, RED1);
        break;
    case 3:
        x = 88;
        for (int i = 0; i < 3; i++) {
            gotoxy(x + 2, 9);
            printf("  ");
            gotoxy(x + 6, 9);
            printf("  ");
            gotoxy(x, 10);
            printf("          ");
            gotoxy(x + 2, 11);
            printf("      ");
            gotoxy(x + 4, 12);
            printf("  ");
            x += 15;
        }
        break;
    case 2:
        erase_characterHp(3);
        x = 88;
        for (int i = 0; i < 2; i++) {
            gotoxy(x + 2, 9);
            printf("  ");
            gotoxy(x + 6, 9);
            printf("  ");
            gotoxy(x, 10);
            printf("          ");
            gotoxy(x + 2, 11);
            printf("      ");
            gotoxy(x + 4, 12);
            printf("  ");
            x += 15;
        }
        break;
    case 1:
        erase_characterHp(2);
        x = 88;
        for (int i = 0; i < 1; i++) {
            gotoxy(x + 2, 9);
            printf("  ");
            gotoxy(x + 6, 9);
            printf("  ");
            gotoxy(x, 10);
            printf("          ");
            gotoxy(x + 2, 11);
            printf("      ");
            gotoxy(x + 4, 12);
            printf("  ");
            x += 15;
        }
        break;
    }
    textcolor(WHITE, BLACK);
}
//======================================================================================================================================

//총 관련>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void shoot(int x, int y) {
    drawToBackBuffer(x, y, "(");
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// 맵관련 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//장애물 그리기 48~149
void print_obs(int X, int h) {
    for (int i = 1; i <= h; i++) {
        drawToBackBuffer(X, 40 - h + i, "|");
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

void gameover_win() {
    textcolor(WHITE, BLACK);

    srand(time(NULL));

    int x = 28, y = 15;

    int x1;
    int y1, y2;
    int sleep_count = 0;

    system("cls");
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf("  ___    ___ ________  ___  ___          ___       __   ___  ________           ___  ___       ");
    gotoxy(x, y + 1);
    printf(" |\\  \\  /  /|\\   __  \\|\\  \\|\\  \\        |\\  \\     |\\  \\|\\  \\|\\   ___  \\        |\\  \\|\\  \\      ");
    gotoxy(x, y + 2);
    printf(" \\ \\  \\/  / | \\  \\|\\  \\ \\  \\\\\\  \\       \\ \\  \\  __\\ \\  \\ \\  \\ \\  \\\\ \\  \\       \\ \\  \\ \\  \\     ");
    gotoxy(x, y + 3);
    printf("  \\ \\    / / \\ \\  \\\\\\  \\ \\  \\\\\\  \\       \\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\       \\ \\  \\ \\  \\    ");
    gotoxy(x, y + 4);
    printf("   \\/  /  /   \\ \\  \\\\\\  \\ \\  \\\\\\  \\       \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\\\ \\  \\       \\ \\__\\ \\__\\   ");
    gotoxy(x, y + 5);
    printf(" __/  / /      \\ \\_______\\ \\_______\\       \\ \\____________\\ \\__\\ \\__\\\\ \\__\\       \\|__|\\|__|");
    gotoxy(x, y + 6);
    printf("|\\___/ /        \\|_______|\\|_______|        \\|____________|\\|__|\\|__| \\|__|           ___  ___");
    gotoxy(x, y + 7);
    printf("\\|___|/                                                                              |\\__\\|\\__\\");
    gotoxy(x, y + 8);
    printf("                                                                                     \\|__|\\|__|");

    while (1) {
        x1 = rand() % 140 + 6;
        y1 = rand() % 8 + 3;
        y2 = rand() % 8 + 25;

        if (sleep_count % 2 == 0) {
            textcolor(sleep_count % 15, BLACK);
            gotoxy(x1, y1);
            printf(" \\|/");
            gotoxy(x1, y1 + 1);
            printf("--*--");
            gotoxy(x1, y1 + 2);
            printf(" /|\\");
        }
        else {
            textcolor(sleep_count % 15, BLACK);
            gotoxy(x1, y2);
            printf(" \\|/");
            gotoxy(x1, y2 + 1);
            printf("--*--");
            gotoxy(x1, y2 + 2);
            printf(" /|\\");
        }

        sleep_count++;
        Sleep(500);
    }
}

void gameover_lose() {
    textcolor(WHITE, BLACK);

    srand(time(NULL));

    int x = 45, y = 15;

    int x1;
    int y1, y2;
    int sleep_count = 0;

    system("cls");
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(" __   __  _______  __   __    ___      _______  _______  _______ ");
    gotoxy(x, y + 1);
    printf("|  | |  ||       ||  | |  |  |   |    |       ||       ||       |");
    gotoxy(x, y + 2);
    printf("|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|");
    gotoxy(x, y + 3);
    printf("|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ");
    gotoxy(x, y + 4);
    printf("|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|");
    gotoxy(x, y + 5);
    printf("  |   |  |       ||       |  |       ||       | _____| ||   |___ ");
    gotoxy(x, y + 6);
    printf("  |___|  |_______||_______|  |_______||_______||_______||_______|");

    while (1) {
        x1 = rand() % 140 + 6;
        y1 = rand() % 8 + 3;
        y2 = rand() % 8 + 25;

        if (sleep_count % 2 == 0) {
            textcolor(sleep_count % 15, BLACK);
            gotoxy(x1, y1);
            printf("  /\\");
            gotoxy(x1, y1 + 1);
            printf(" (__)");
            gotoxy(x1, y1 + 2);
            printf("(____)");
        }
        else {
            textcolor(sleep_count % 15, BLACK);
            gotoxy(x1, y2);
            printf("  /\\");
            gotoxy(x1, y2 + 1);
            printf(" (__)");
            gotoxy(x1, y2 + 2);
            printf("(____)");
        }

        sleep_count++;
        Sleep(500);
    }
}

//설명 화면
int print_info() {

    char kbh;
    int boxNum = -1;
    int waitStart = 1;
    int xBox1 = 35, xBox2 = 90, yBox = 32;

    system("cls");
    textcolor(YELLOW1, BLACK);
    gotoxy(50, 5);
    printf("이 게임의 목적은 화면 좌측에 있는 괴물을 물리치는 것입니다");
    gotoxy(40, 9);
    printf("방향키를 이용해 움직일 수 있으며 윗 방향키를 누르면 점프를 할 수 있습니다");
    gotoxy(35, 13);
    printf("게임이 시작되면 우측에서 장애물이 나오는데, 부딪히게 되면 체력이 한칸 깎이게 됩니다");
    gotoxy(42, 17);
    printf("움직인 방향으로 계속해서 움직이며, 점프를 하면 자리에 멈출 수 있게 됩니다");
    gotoxy(36, 21);
    printf("보스의 체력에 따라 등장하는 아이템을 획득함에 따라 보다 더 쉽게 클리어가 가능해집니다");

    {
        textcolor(WHITE, RED2);
        gotoxy(xBox1, yBox);
        printf("                      ");
        gotoxy(xBox1, yBox + 1);
        printf(" ");
        gotoxy(xBox1 + 21, yBox + 1);
        printf(" ");
        gotoxy(xBox1, yBox + 2);
        printf(" ");
        textcolor(WHITE, BLACK);
        gotoxy(xBox1 + 7, yBox + 2);
        printf("게임시작");
        textcolor(WHITE, RED2);
        gotoxy(xBox1 + 21, yBox + 2);
        printf(" ");
        gotoxy(xBox1, yBox + 3);
        printf(" ");
        gotoxy(xBox1 + 21, yBox + 3);
        printf(" ");
        gotoxy(xBox1, yBox + 4);
        printf("                      ");
        textcolor(WHITE, BLACK);
    }
    {
        textcolor(WHITE, GREEN1);
        gotoxy(xBox2, yBox);
        printf("                      ");
        gotoxy(xBox2, yBox + 1);
        printf(" ");
        gotoxy(xBox2 + 21, yBox + 1);
        printf(" ");
        gotoxy(xBox2, yBox + 2);
        printf(" ");
        textcolor(WHITE, BLACK);
        gotoxy(xBox2 + 7, yBox + 2);
        printf("게임종료");
        textcolor(WHITE, CYAN1);
        gotoxy(xBox2 + 21, yBox + 2);
        printf(" ");
        gotoxy(xBox2, yBox + 3);
        printf(" ");
        gotoxy(xBox2 + 21, yBox + 3);
        printf(" ");
        gotoxy(xBox2, yBox + 4);
        printf("                      ");
    }
    while (1) {
        if (kbhit() == 1) {
            kbh = getch(); // key 값을 읽는다

            if (kbh == SPECIAL1 || kbh == SPECIAL2) // 만약 특수키 -- 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                kbh = getch();

            if (waitStart == 1) {
                switch (kbh) {
                case RIGHT: //우로 이동
                    if (boxNum == -1) {
                        //왼쪽 색 돌려놓기
                        {
                            textcolor(WHITE, BLUE2);
                            gotoxy(xBox1, yBox);
                            printf("                      ");
                            gotoxy(xBox1, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1, yBox + 2);
                            printf(" ");
                            textcolor(WHITE, BLACK);
                            gotoxy(xBox1 + 7, yBox + 2);
                            printf("게임시작");
                            textcolor(WHITE, GREEN1);
                            gotoxy(xBox1 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox1, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1, yBox + 4);
                            printf("                      ");
                        }
                        //오른쪽 색 빨강으로
                        {
                            textcolor(WHITE, RED2);
                            gotoxy(xBox2, yBox);
                            printf("                      ");
                            gotoxy(xBox2, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2, yBox + 4);
                            printf("                      ");
                            textcolor(WHITE, BLACK);
                        }
                        boxNum = 0;
                    }
                    break;
                case LEFT:  //좌로 이동
                    if (boxNum == 0) {
                        //오른쪽 색 돌려놓기
                        {
                            textcolor(WHITE, GREEN1);
                            gotoxy(xBox2, yBox);
                            printf("                      ");
                            gotoxy(xBox2, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2, yBox + 2);
                            printf(" ");
                            textcolor(WHITE, BLACK);
                            gotoxy(xBox2 + 7, yBox + 2);
                            printf("게임종료");
                            textcolor(WHITE, CYAN1);
                            gotoxy(xBox2 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2, yBox + 4);
                            printf("                      ");
                        }
                        //왼쪽 색 빨강으로
                        {
                            textcolor(WHITE, RED2);
                            gotoxy(xBox1, yBox);
                            printf("                      ");
                            gotoxy(xBox1, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1, yBox + 2);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox1, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1, yBox + 4);
                            printf("                      ");
                            textcolor(WHITE, BLACK);
                        }
                        boxNum = -1;
                    }
                    break;
                case SPACE: //선택
                    if (boxNum == -1) {//게임시작
                        system("cls");
                        return 1;
                    }
                    else if (boxNum == 0) {//게임종료
                        system("cls");
                        gotoxy(56, 30);
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

//시작 화면
int mainScreen() {
    char ch;
    int boxNum;
    int waitStart = 0;
    int x = 10, y = 8;
    int xBox1 = 17, xBox2 = 64, xBox3 = 111, yBox = 32;
    int color, stack = 0;

    textcolor(WHITE, BLUE2);
    {
        gotoxy(xBox1, yBox);
        printf("                      ");
        gotoxy(xBox1, yBox + 1);
        printf(" ");
        gotoxy(xBox1 + 21, yBox + 1);
        printf(" ");
        gotoxy(xBox1, yBox + 2);
        printf(" ");
        textcolor(WHITE, BLACK);
        gotoxy(xBox1 + 7, yBox + 2);
        printf("게임설명");
        textcolor(WHITE, GREEN1);
        gotoxy(xBox1 + 21, yBox + 2);
        printf(" ");
        gotoxy(xBox1, yBox + 3);
        printf(" ");
        gotoxy(xBox1 + 21, yBox + 3);
        printf(" ");
        gotoxy(xBox1, yBox + 4);
        printf("                      ");
    }
    {
        gotoxy(xBox2, yBox);
        printf("                      ");
        gotoxy(xBox2, yBox + 1);
        printf(" ");
        gotoxy(xBox2 + 21, yBox + 1);
        printf(" ");
        gotoxy(xBox2, yBox + 2);
        printf(" ");
        textcolor(WHITE, BLACK);
        gotoxy(xBox2 + 7, yBox + 2);
        printf("게임시작");
        textcolor(WHITE, CYAN1);
        gotoxy(xBox2 + 21, yBox + 2);
        printf(" ");
        gotoxy(xBox2, yBox + 3);
        printf(" ");
        gotoxy(xBox2 + 21, yBox + 3);
        printf(" ");
        gotoxy(xBox2, yBox + 4);
        printf("                      ");
    }
    {
        gotoxy(xBox3, yBox);
        printf("                      ");
        gotoxy(xBox3, yBox + 1);
        printf(" ");
        gotoxy(xBox3 + 21, yBox + 1);
        printf(" ");
        gotoxy(xBox3, yBox + 2);
        printf(" ");
        textcolor(WHITE, BLACK);
        gotoxy(xBox3 + 7, yBox + 2);
        printf("게임종료");
        textcolor(WHITE, CYAN2);
        gotoxy(xBox3 + 21, yBox + 2);
        printf(" ");
        gotoxy(xBox3, yBox + 3);
        printf(" ");
        gotoxy(xBox3 + 21, yBox + 3);
        printf(" ");
        gotoxy(xBox3, yBox + 4);
        printf("                      ");
    }

    while (1) {
        color = stack % 7 + 1;
        gotoxy(x, y);
        textcolor(color, BLACK);
        printf(" ________  ___  ___  ________           ________ ________  ________  _____ ______           ________  ___  ________   ________     ");
        textcolor(color + 1, BLACK);
        gotoxy(x, y + 1);
        printf("|\\   __  \\|\\  \\|\\  \\|\\   ___  \\        |\\  _____\\\\   __  \\|\\   __  \\|\\   _ \\  _   \\        |\\   ___ \\|\\  \\|\\   ___  \\|\\   __  \\    ");
        textcolor(color + 2, BLACK);
        gotoxy(x, y + 2);
        printf("\\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\       \\ \\  \\__/\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\       \\ \\  \\_|\\ \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\   ");
        textcolor(color + 3, BLACK);
        gotoxy(x, y + 3);
        printf(" \\ \\   _  _\\ \\  \\\\\\  \\ \\  \\\\ \\  \\       \\ \\   __\\\\ \\   _  _\\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\       \\ \\  \\ \\\\ \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\  ");
        textcolor(color + 4, BLACK);
        gotoxy(x, y + 4);
        printf("  \\ \\  \\\\  \\\\ \\  \\\\\\  \\ \\  \\\\ \\  \\       \\ \\  \\_| \\ \\  \\\\  \\\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\       \\ \\  \\_/  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ ");
        textcolor(color + 5, BLACK);
        gotoxy(x, y + 5);
        printf("   \\ \\__\\\\ _\\\\ \\_______\\ \\__\\\\ \\__\\       \\ \\__\\   \\ \\__\\\\ _\\\\ \\_______\\ \\__\\    \\ \\__\\       \\ \\_____/|\\ \\__\\ \\__\\\\ \\__\\ \\_______\\");
        textcolor(color + 6, BLACK);
        gotoxy(x, y + 6);
        printf("    \\|__|\\|__|\\|_______|\\|__| \\|__|        \\|__|    \\|__|\\|__|\\|_______|\\|__|     \\|__|        \\|_____/  \\|__|\\|__| \\|__|\\|_______|");
        textcolor(color + 7, BLACK);

        if (stack % 7 == 0 && waitStart == 0) {
            textcolor(YELLOW1, BLACK);
            gotoxy(63, 24);
            printf("스페이스바를 눌러주세요 !");
        }

        stack++;

        if (stack % 14 == 0 && waitStart == 0) {
            textcolor(BLACK, BLACK);
            gotoxy(63, 24);
            printf("스페이스바를 눌러주세요 !");
        }

        if (kbhit() == 1) {
            ch = getch(); // key 값을 읽는다

            if (ch == SPECIAL1 || ch == SPECIAL2) // 만약 특수키 -- 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = getch();

            if (waitStart == 1) {
                switch (ch) {
                case RIGHT: //우로 이동
                    if (boxNum == 0) {
                        //가운데 색 돌려놓기
                        {
                            textcolor(WHITE, GREEN1);
                            gotoxy(xBox2, yBox);
                            printf("                      ");
                            gotoxy(xBox2, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2, yBox + 2);
                            printf(" ");
                            textcolor(WHITE, BLACK);
                            gotoxy(xBox2 + 7, yBox + 2);
                            printf("게임시작");
                            textcolor(WHITE, CYAN1);
                            gotoxy(xBox2 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2, yBox + 4);
                            printf("                      ");
                        }
                        //오른쪽 색 빨강으로
                        {
                            textcolor(WHITE, RED2);
                            gotoxy(xBox3, yBox);
                            printf("                      ");
                            gotoxy(xBox3, yBox + 1);
                            printf(" ");
                            gotoxy(xBox3 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox3, yBox + 2);
                            printf(" ");
                            gotoxy(xBox3 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox3, yBox + 3);
                            printf(" ");
                            gotoxy(xBox3 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox3, yBox + 4);
                            printf("                      ");
                            textcolor(WHITE, BLACK);
                        }
                        boxNum = 1;
                    }
                    else if (boxNum == -1) {
                        //왼쪽 색 돌려놓기
                        {
                            textcolor(WHITE, BLUE2);
                            gotoxy(xBox1, yBox);
                            printf("                      ");
                            gotoxy(xBox1, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1, yBox + 2);
                            printf(" ");
                            textcolor(WHITE, BLACK);
                            gotoxy(xBox1 + 7, yBox + 2);
                            printf("게임설명");
                            textcolor(WHITE, GREEN1);
                            gotoxy(xBox1 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox1, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1, yBox + 4);
                            printf("                      ");
                        }
                        //오른쪽 색 빨강으로
                        {
                            textcolor(WHITE, RED2);
                            gotoxy(xBox2, yBox);
                            printf("                      ");
                            gotoxy(xBox2, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2, yBox + 4);
                            printf("                      ");
                            textcolor(WHITE, BLACK);
                        }
                        boxNum = 0;
                    }
                    break;
                case LEFT:  //좌로 이동
                    if (boxNum == 0) {
                        //가운데 색 돌려놓기
                        {
                            textcolor(WHITE, GREEN1);
                            gotoxy(xBox2, yBox);
                            printf("                      ");
                            gotoxy(xBox2, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2, yBox + 2);
                            printf(" ");
                            textcolor(WHITE, BLACK);
                            gotoxy(xBox2 + 7, yBox + 2);
                            printf("게임시작");
                            textcolor(WHITE, CYAN1);
                            gotoxy(xBox2 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2, yBox + 4);
                            printf("                      ");
                        }
                        //왼쪽 색 빨강으로
                        {
                            textcolor(WHITE, RED2);
                            gotoxy(xBox1, yBox);
                            printf("                      ");
                            gotoxy(xBox1, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox1, yBox + 2);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox1, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox1, yBox + 4);
                            printf("                      ");
                            textcolor(WHITE, BLACK);
                        }
                        boxNum = -1;
                    }
                    else if (boxNum == 1) {
                        //오른쪽 색 돌려놓기
                        {
                            textcolor(WHITE, CYAN1);
                            gotoxy(xBox3, yBox);
                            printf("                      ");
                            gotoxy(xBox3, yBox + 1);
                            printf(" ");
                            gotoxy(xBox3 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox3, yBox + 2);
                            printf(" ");
                            textcolor(WHITE, BLACK);
                            gotoxy(xBox3 + 7, yBox + 2);
                            printf("게임종료");
                            textcolor(WHITE, CYAN2);
                            gotoxy(xBox3 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox3, yBox + 3);
                            printf(" ");
                            gotoxy(xBox3 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox3, yBox + 4);
                            printf("                      ");
                        }
                        //가운데 색 빨강으로
                        {
                            textcolor(WHITE, RED2);
                            gotoxy(xBox2, yBox);
                            printf("                      ");
                            gotoxy(xBox2, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 1);
                            printf(" ");
                            gotoxy(xBox2, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 2);
                            printf(" ");
                            gotoxy(xBox2, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2 + 21, yBox + 3);
                            printf(" ");
                            gotoxy(xBox2, yBox + 4);
                            printf("                      ");
                            textcolor(WHITE, BLACK);
                        }
                        boxNum = 0;
                    }
                    break;
                case SPACE: //선택
                    if (boxNum == -1) {//게임설명
                        int i = print_info();
                        if (i == 1)
                            return 1; //게임 시작
                        else if (i == -1)
                            return 0;//게임 종료
                    }
                    else if (boxNum == 0) {//게임시작
                        system("cls");
                        return 1;
                    }
                    else if (boxNum == 1) {//게임종료
                        system("cls");
                        gotoxy(56, 30);
                        return 0;
                    }
                    break;
                }
            }

            if (ch == SPACE && waitStart == 0) {
                {
                    textcolor(WHITE, RED2);
                    gotoxy(xBox2, yBox);
                    printf("                      ");
                    gotoxy(xBox2, yBox + 1);
                    printf(" ");
                    gotoxy(xBox2 + 21, yBox + 1);
                    printf(" ");
                    gotoxy(xBox2, yBox + 2);
                    printf(" ");
                    gotoxy(xBox2 + 21, yBox + 2);
                    printf(" ");
                    gotoxy(xBox2, yBox + 3);
                    printf(" ");
                    gotoxy(xBox2 + 21, yBox + 3);
                    printf(" ");
                    gotoxy(xBox2, yBox + 4);
                    printf("                      ");
                    textcolor(BLACK, BLACK);
                    gotoxy(63, 24);
                    printf("스페이스바를 눌러주세요 !");
                    textcolor(WHITE, BLACK);
                    waitStart = 1;
                    boxNum = 0;
                }
            }
        }
        Sleep(100);
    }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//실행
int main() {
    unsigned char ch;

    //아이템
    int x_item1 = 0, y_item1 = 0, item1 = 1;
    int x_item2 = 0, y_item2 = 0, item2 = 1;
    int x_item3 = 0, y_item3 = 0, item3 = 1;
    int x_item4 = 0, y_item4 = 0, item4 = 1;
    int x_item5 = 0, y_item5 = 0, item5 = 1;

    int checkOverRap[150] = { 0 };

    //공룡
    int HP_boss = 100;

    //버퍼 초기화
    for (int j = 0; j < HEIGHT; j++)
        for (int i = 0; i < WITDH; i++) {
            front_buffer[j][i] = '\0';
            back_buffer[j][i] = '\0';
        }

    int renderCheck;

    //캐릭터   
    int keep_moving = 0, moving_check = STOP;
    int oldx, oldy, newx, newy;

    int HP = 3;
    int no_hit_time = 0;

    int sleep_stack = 0;
    int jump_count = 0; //땅에 닿아있는지 확인
    int jump_check = 0; //땅에 닿아있는지 확인 keep_moving을 위한 변수

    //총알
    int shooting = -1;
    int bullet = 1;
    int x_bullet, y_bullet;
    int damage = 1;

    //장애물
    int oldx_obs, newx_obs, h = 0;

    newx_obs = 149;

    oldx = newx = 70;
    oldy = newy = 38;

    removeCursor();

    //시작 화면
    int gameCheck = mainScreen();
    switch (gameCheck) {
    case 1:
        break;
    case 0:
        return;
    }

    drawBox(0, 0, 150, 40);

    //게임 시작
    init_game(); // 테두리 그리고 공룡 머리 만들기
    print_characterHp(HP);

    time_t startTime = clock();
    time_t endTime;

    while (1) {
        startTime = clock();
        //장애물 관련
        if (sleep_stack % 3 == 0) {
            if (sleep_stack > 13) {
                if (newx_obs == 149) {
                    h = rand() % 3 + 3;
                    print_obs(newx_obs, h);
                }
                else if (newx_obs <= 51) {
                    print_obs(newx_obs + 1, h, " ");
                    newx_obs = 149;
                }
                else {
                    print_obs(newx_obs, h);
                }
            }
        }
        print_obs(newx_obs, h);
        //공룡
        if (sleep_stack % 30 < 15) {
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
                    /*else if (moving_check == GORIGHT) {
                       keep_moving = 0;
                       moving_check = STOP;
                    }*/
                    else keep_moving = 1;
                    break;
                case RIGHT:
                    if (moving_check == STOP) keep_moving = 1;
                    /*if (moving_check == GOLEFT) {
                       keep_moving = 0;
                       moving_check = STOP;
                    }*/
                    else keep_moving = 1;
                    break;
                }
            }
        }
        if (keep_moving) { // 움직이고 있으면
            switch (ch) {
            case UP:
                if (jump_count == 0) {
                    newy = oldy - 2;
                    jump_count = 2;
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
                jump_count += 2;
                newy = oldy - 2;
            }
            else if (jump_count >= 12) {//낙하
                jump_count += 2;
                newy = oldy + 2;
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

        if (sleep_stack % 15 == 0) {
            if (shooting == 1) {
                if (bullet == 1) {
                    bullet = 0;
                    x_bullet = newx - 5;
                    y_bullet = newy - 3;
                }
            }
        }

        if (bullet == 0) {
            shoot(x_bullet, y_bullet);
            x_bullet -= 6;
            if (x_bullet <= 47) {
                bullet = 1;
                HP_boss -= damage;
            }
        }

        //보스 체력
        {
            if (HP_boss <= 0) {
                erase_hpBar();
                gameover_win();
                break;
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
                if (item5 == 1) {//다섯 번째 아이템
                    x_item5 = rand() % 45 + 90;
                    y_item5 = rand() % 5 + 30;

                    if (checkOverRap[x_item5] == 1) {
                        while (1) {
                            if (checkOverRap[x_item5] != 1)
                                break;
                            x_item5 = rand() % 45 + 90;
                        }
                    }

                    checkOverRap[x_item5 - 90] = 1;

                    gotoxy(x_item5, y_item5);
                    textcolor(RED1, BLACK);
                    printf("X2");
                    textcolor(WHITE, BLACK);
                    item5 = 0;
                }
            }
            else if (HP_boss <= 50) {
                erase_hpBar();
                hp_bar(5);
            }
            else if (HP_boss <= 60) {
                erase_hpBar();
                hp_bar(6);
                if (item4 == 1) {//네 번째 아이템
                    x_item4 = rand() % 45 + 90;
                    y_item4 = rand() % 5 + 30;

                    if (checkOverRap[x_item4] == 1) {
                        while (1) {
                            if (checkOverRap[x_item4] != 1)
                                break;
                            x_item4 = rand() % 45 + 90;
                        }
                    }

                    checkOverRap[x_item4] = 1;

                    gotoxy(x_item4, y_item4);
                    textcolor(GREEN2, BLACK);
                    printf("+2");
                    textcolor(WHITE, BLACK);
                    item4 = 0;
                }
            }
            else if (HP_boss <= 70) {
                erase_hpBar();
                hp_bar(7);
                if (item3 == 1) {//세 번째 아이템
                    x_item3 = rand() % 45 + 90;
                    y_item3 = rand() % 5 + 30;

                    if (checkOverRap[x_item3 - 90] == 1) {
                        while (1) {
                            if (checkOverRap[x_item3] != 1)
                                break;
                            x_item3 = rand() % 45 + 90;
                        }
                    }

                    checkOverRap[x_item3] = 1;

                    gotoxy(x_item3, y_item3);
                    textcolor(YELLOW1, BLACK);
                    printf("+♥");
                    textcolor(WHITE, BLACK);
                    item3 = 0;
                }
            }
            else if (HP_boss <= 80) {
                erase_hpBar();
                hp_bar(8);
            }
            else if (HP_boss <= 90) {
                erase_hpBar();
                hp_bar(9);
                if (item2 == 1) {//두 번째 아이템
                    x_item2 = rand() % 45 + 90;
                    y_item2 = rand() % 5 + 30;

                    if (checkOverRap[x_item2] == 1) {
                        while (1) {
                            if (checkOverRap[x_item2] != 1)
                                break;
                            x_item2 = rand() % 45 + 90;
                        }
                    }

                    checkOverRap[x_item2] = 1;

                    gotoxy(x_item2, y_item2);
                    textcolor(CYAN2, BLACK);
                    printf("X2");
                    textcolor(WHITE, BLACK);
                    item2 = 0;
                }
            }
            else {
                if (item1 == 1) {//첫 아이템
                    x_item1 = rand() % 45 + 90;
                    y_item1 = rand() % 5 + 30;

                    checkOverRap[x_item1] = 1;

                    gotoxy(x_item1, y_item1);
                    textcolor(GREEN1, BLACK);
                    printf("+1");
                    textcolor(WHITE, BLACK);
                    item1 = 0;
                }
            }
        }

        //아이템 먹은지 확인
        {
            //첫 번째 아이템
            if (x_item1 > 0 && y_item1 > 0) {
                if (
                    x_item1 >= newx && x_item1 <= newx + 3 && newy - 4 <= y_item1 &&
                    x_item1 <= newx + 3 && newy + 2 >= y_item1
                    ) {
                    damage += 1;
                    gotoxy(x_item1 - 1, y_item1);
                    textcolor(WHITE, BLACK);
                    printf("   ");
                    checkOverRap[x_item1] = 0;
                    x_item1 = 0, y_item1 = 0;
                }
            }
            //두 번째 아이템
            if (x_item2 > 0 && y_item2 > 0) {
                if (
                    x_item2 >= newx && x_item2 <= newx + 3 && newy - 4 <= y_item2 &&
                    x_item2 <= newx + 3 && newy + 2 >= y_item2
                    ) {
                    damage *= 2;
                    gotoxy(x_item2 - 1, y_item2);
                    textcolor(WHITE, BLACK);
                    printf("   ");
                    checkOverRap[x_item2] = 0;
                    x_item2 = 0, y_item2 = 0;
                }
            }
            //세 번째 아이템
            if (x_item3 > 0 && y_item3 > 0) {
                if (
                    x_item3 >= newx && x_item3 <= newx + 3 && newy - 4 <= y_item3 &&
                    x_item3 <= newx + 3 && newy + 2 >= y_item3
                    ) {
                    HP++;
                    print_characterHp(HP);
                    gotoxy(x_item3 - 1, y_item3);
                    textcolor(WHITE, BLACK);
                    printf("   ");
                    checkOverRap[x_item3] = 0;
                    x_item3 = 0, y_item3 = 0;
                }
            }
            //네 번째 아이템
            if (x_item4 > 0 && y_item4 > 0) {
                if (
                    x_item4 >= newx && x_item4 <= newx + 3 && newy - 4 <= y_item4 ||
                    x_item4 <= newx + 3 && newy + 2 >= y_item4
                    ) {
                    damage += 2;
                    gotoxy(x_item4 - 1, y_item4);
                    textcolor(WHITE, BLACK);
                    printf("   ");
                    checkOverRap[x_item4] = 0;
                    x_item4 = 0, y_item4 = 0;
                }
            }
            //다섯 번째 아이템
            if (x_item5 > 0 && y_item5 > 0) {
                if (
                    x_item5 >= newx && x_item5 <= newx + 3 && newy - 4 <= y_item5 ||
                    x_item5 <= newx + 3 && newy + 2 >= y_item5
                    ) {
                    damage *= 2;
                    gotoxy(x_item5 - 1, y_item5);
                    textcolor(WHITE, BLACK);
                    printf("   ");
                    checkOverRap[x_item5] = 0;
                    x_item5 = 0, y_item5 = 0;
                }
            }
        }

        //피격 판정 처리
        if (no_hit_time == 0) {
            if (
                newx_obs >= newx && newy - 4 <= 39 - h &&
                newx_obs <= newx + 3 && newy + 2 >= 39 - h
                ) {
                no_hit_time = 15;
                HP--;
                switch (HP) {
                case 3:
                    print_characterHp(HP);
                    break;
                case 2:
                    print_characterHp(HP);
                    break;
                case 1:
                    print_characterHp(HP);
                    break;
                }
                if (HP == 0) {
                    //게임종료
                    erase_characterHp(3);
                    gameover_lose();
                    break;
                }
            }
        }

        print_character(newx, newy);

        if (sleep_stack % 3 == 0) {
            if (sleep_stack > 13) {
                if (shooting == 1)
                    newx_obs -= 2.5;
                else
                    newx_obs -= 1.5;
            }
        }

        sleep_stack++; //개체의 속도 조절
        if (no_hit_time > 0)
            no_hit_time--;

        render(renderCheck);

        endTime = clock();
        int delay = (endTime - startTime);
        if (delay > 20) delay = 0;
        Sleep(20 - delay);
    }
}