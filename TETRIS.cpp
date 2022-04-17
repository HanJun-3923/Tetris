#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;
//github hi~
//no hi ㅋㅇ
#define length_x 24
#define length_y 25
#define initial_x 20
#define initial_y 5

#define LEFT 75 // ←
#define RIGHT 77  // →
#define UP 72 // ↑
#define DOWN 80 // ↓

//□ ■ ○ ● ▩ ▤ ▥ ▨ ▧ ▦ ▣ ⊙
int table_data[length_x][length_y]; // 테이블 판 0 = " ", 1 = "▩" , 2  = "■", 3 = "▣"
// 이상적인 데이터 번호 1 ~ 7 = "block", 0 = " ", 10 = "▩", 9 = "■", 8 = "▣",  -1 = "ghost"
int rot; //rotation
int x = initial_x + (length_x / 2 - 4), y = initial_y + 1;
int shape[4][4][4];

const int block1[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {1, 1, 1, 1},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 9, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {9, 9, 9, 9},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 9, 0}
        },

};
const int block2[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 0},
                        {0, 9, 9, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 0},
                        {0, 9, 9, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 0},
                        {0, 9, 9, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 0},
                        {0, 9, 9, 0},
                        {0, 0, 0, 0}
        },

};
const int block3[4][4][4] = {
        {
                        {0, 9, 0, 0},
                        {0, 9, 0, 0},
                        {0, 9, 9, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 9},
                        {0, 9, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 9, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 0, 9, 0},
                        {9, 9, 9, 0},
                        {0, 0, 0, 0}

        },

};
const int block4[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 9, 0, 0},
                        {0, 9, 9, 0},
                        {0, 0, 9, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 0},
                        {9, 9, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 0, 0},
                        {0, 9, 9, 0},
                        {0, 0, 9, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 0},
                        {9, 9, 0, 0},
                        {0, 0, 0, 0}

        },

};
const int block5[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 9, 9, 9},
                        {0, 0, 9, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 9, 0},
                        {0, 9, 9, 0},
                        {0, 0, 9, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 9, 0},
                        {0, 9, 9, 9},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 9, 0},
                        {0, 0, 9, 9},
                        {0, 0, 9, 0},
                        {0, 0, 0, 0}

        },

};

//기본 함수들
void gotoxy(short x, short y) { // Windows.h
    COORD pos{ x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//메인 함수들
void draw_frame(int len_x, int len_y, int i_x, int i_y) {
    int pos[2] = { i_x, i_y };
    len_x--; //보정
    for (int i = 0; i <= len_x; i++) {
        if (i % 2 == 0) {
            gotoxy(pos[0] + i, pos[1]);
            cout << "▩";
        }
        table_data[i][0] = 10;
    }

    for (int i = 0; i <= len_x; i++) {
        if (i % 2 == 0) {
            gotoxy(pos[0] + i, pos[1] + len_y - 1);
            cout << "▩";
        }
        table_data[i][length_y - 1] = 10;
    }

    for (int i = 1; i < len_y - 1; i++) {
        gotoxy(pos[0], pos[1] + i);
        cout << "▩";
        table_data[0][i] = 10;
        table_data[1][i] = 10;
    }

    for (int i = 1; i < len_y - 1; i++) {
        gotoxy(pos[0] + len_x - 1, pos[1] + i);
        cout << "▩";
        table_data[length_x - 2][i] = 10;
        table_data[length_x - 1][i] = 10;
    }
}
void clear_gametable()
{
    for (int i = 0; i < length_x; i++) {
        for (int j = 0; j < length_y; j++) {
            if (table_data[i][j] == 9 || table_data[i][j] == -1) table_data[i][j] = 0;
        }
    }
    for (int i = 2; i < length_x - 2; i++) {
        for (int j = 1; j < length_y - 1; j++) {
            gotoxy(initial_x + i, initial_y + j);
            printf(" ");
        }
    }
}
void draw_gametable() {
    for (int fx = 0; fx < length_x; fx++) {
        for (int fy = 0; fy < length_y; fy++) {
            if (table_data[fx][fy] == 0 || table_data[fx][fy] == 10) continue;
            else if (table_data[fx][fy] == 9) {
                if (fx % 2 == 0) {
                    gotoxy(fx + initial_x, fy + initial_y);
                    cout << "■";
                }
            }
            else if (table_data[fx][fy] == 8) {
                if (fx % 2 == 0) {
                    gotoxy(fx + initial_x, fy + initial_y);
                    cout << "▣";
                }
            }
            else if (table_data[fx][fy] == -1) {
                if (fx % 2 == 0) {
                    gotoxy(fx + initial_x, fy + initial_y);
                    cout << "□";
                }
            }
        }
    }
}
void print_gametable_data() {
    gotoxy(initial_x + length_x + 10, initial_y);
    for (int i = 0; i < length_y; i++) {
        for (int j = 0; j < length_x; j++) {
            if (table_data[j][i] == 10) {
                if (j % 2 == 0)
                    cout << "▩";

            }
            else if (table_data[j][i] == -1) {
                if (j % 2 == 0)
                    cout << table_data[j][i];
            }
            else cout << table_data[j][i];
        }
        gotoxy(initial_x + length_x + 10, initial_y + i + 1);
    }
}

class Block
{
protected:

public:
    int gy = initial_y;

    void set_block1() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    shape[i][j][k] = block1[i][j][k];
                }
            }
        }
    }
    void set_block2() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    shape[i][j][k] = block2[i][j][k];
                }
            }
        }
    }
    void set_block3() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    shape[i][j][k] = block3[i][j][k];
                }
            }
        }
    }
    void set_block4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    shape[i][j][k] = block4[i][j][k];
                }
            }
        }
    }
    void set_block5() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    shape[i][j][k] = block5[i][j][k];
                }
            }
        }
    }

    void print_block() {
        if (can_print()) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    gotoxy(x + 2 * i, y + j);
                    if (shape[rot][i][j] == 9) {
                        table_data[x - initial_x + 2 * i][y - initial_y + j] = 9;
                        table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 9;
                    }
                }
            }
        }
    }
    bool can_print() {
        int count = 0;
        for (int fx = 0; fx < 4; fx++) {
            for (int fy = 0; fy < 4; fy++) {
                if (shape[rot][fy][fx] == 9) {
                    if (table_data[x - initial_x + (2 * fy)][y - initial_y + fx] == 10)
                        count++;

                    if (table_data[x - initial_x + (2 * fy)][y - initial_y + fx] == 8)
                        count++;
                }
            }
        }
        if (count == 0) return true;
        else return false;
    }
    bool ghost_can_print() {
        int count = 0;
        for (int fx = 0; fx < 4; fx++) {
            for (int fy = 0; fy < 4; fy++) {
                if (shape[rot][fy][fx] == 9) {
                    if (table_data[x - initial_x + (2 * fy)][gy - initial_y + fx] == 10)
                        count++;

                    if (table_data[x - initial_x + (2 * fy)][gy - initial_y + fx] == 8)
                        count++;
                }
            }
        }
        if (count == 0) return true;
        else return false;
    }
    void print_ghost() {
        gy = y;
        while (true) {
            gy++;
            if (ghost_can_print()) continue;
            else {
                gy--;
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                gotoxy(x + 2 * i, gy + j);
                if (shape[rot][i][j] == 9) {
                    table_data[x - initial_x + 2 * i][gy - initial_y + j] = -1;
                    table_data[x - initial_x + 2 * i + 1][gy - initial_y + j] = -1;
                }
            }
        }



    }
    void print_variables() {
        gotoxy(0, 0);
        cout << "(" << x << ", " << y << ")" << endl;
        cout << "rotation = " << rot << endl;
    }

    void Down() {
        y++;
        if (can_print() == false) y--;
    }
    void Left() {
        x -= 2;
        if (can_print() == false) x += 2;
    }
    void Right() {
        x += 2;
        if (can_print() == false) x -= 2;
    }
    void Rotate_Z() { // Z or z
        rot = (rot + 1) % 4;
        if (can_print() == false) { //undo
            if (rot == 0) rot = 3;
            else rot--;
        }
    }
    void Rotate_X() { // X or x
        if (rot == 0) rot = 3;
        else rot--;
        if (can_print() == false) { //undo
            rot = (rot + 1) % 4;
        }
    }
    void SpaceBar() { //Hard Drop
        while (true) {
            y++;
            if (can_print()) continue;
            else {
                y--;
                Solid();
                break;
            }
        }
    }
    void Solid() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[rot][i][j] == 9) {
                    table_data[x - initial_x + 2 * i][y - initial_y + j] = 8;
                    table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 8;
                }
            }
        }
    }
    void next_block() {
        int which_block = rand() % 5 + 1;
        if (which_block == 1) set_block1();
        else if (which_block == 2) set_block2();
        else if (which_block == 3) set_block3();
        else if (which_block == 4) set_block4();
        else if (which_block == 5) set_block5();
    }
};

class GamePlay : public Block
{
public:
    GamePlay() {
        srand(time(NULL));
        Block block;
        int key;
        bool next_block = false;
        rot = 0;

        block.next_block();
        block.print_block();
        block.print_ghost();
        draw_gametable();
        print_gametable_data(); //test
        print_gametable_data(); //test
        print_variables(); //test
        gotoxy(x, y); //test
        printf("●"); //test
        while (true) //키 입력
        {
            if (_kbhit()) {
                key = _getch();
                if (key == 224) {
                    key = _getch();
                    switch (key) {
                    case DOWN:
                        block.Down();
                        break;
                    case LEFT:
                        block.Left();
                        break;
                    case RIGHT:
                        block.Right();
                        break;
                    default:
                        break;
                    }
                }
                else if (key == 90 || key == 122) { // Z or z
                    block.Rotate_Z();
                }
                else if (key == 88 || key == 120) { // X or x
                    block.Rotate_X();
                }
                else if (key == 32) { // SpaceBar 
                    block.SpaceBar();
                    next_block = true;
                } //키 입력 끝



                if (next_block) {
                    block.next_block();
                    clear_gametable();
                    x = initial_x + (length_x / 2 - 4), y = initial_y + 1;
                    block.print_ghost();
                    block.print_block();
                    next_block = false;
                }
                else if (block.can_print()) {
                    clear_gametable(); //clear
                    block.print_ghost();
                    block.print_block();
                }


                draw_frame(length_x, length_y, initial_x, initial_y);
                draw_gametable(); // gametable Reload!!


                print_gametable_data(); //test
                print_variables(); //test
                gotoxy(x, y); //test
                printf("●"); //test
            }
        }
    }
};

int main()
{
    CursorView(false);
    draw_frame(length_x, length_y, initial_x, initial_y);
    GamePlay();

    gotoxy(0, 30);
}

// 검사


