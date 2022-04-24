#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define length_x 24
#define length_y 25
#define initial_x 20
#define initial_y 5

#define len_next_x 12

#define hold_ini_x 10
#define hold_ini_y 6

#define LEFT 75 // ←
#define RIGHT 77  // →
#define UP 72 // ↑
#define DOWN 80 // ↓


//□ ■ ○ ● ▩ ▤ ▥ ▨ ▧ ▦ ▣ ⊙
/* table_data 번호 의미
0 = " "
1 ~ 7 -> o i s z l j t  /// color + ■
11 ~ 17 -> solid(0, i, s, z, l, j, t)  /// color + ▣
10 = wall  ///▩
-2 = ghost wall //▩
-1 = "ghost"  /// □ (no color)
*/

//block: O I S Z L J T 순서
const int block1[4][4][4] = {
		{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{0, 1, 1, 0},
						{0, 0, 0, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{0, 1, 1, 0},
						{0, 0, 0, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{0, 1, 1, 0},
						{0, 0, 0, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 1, 1, 0},
						{0, 1, 1, 0},
						{0, 0, 0, 0}
		},

};
const int block2[4][4][4] = {
		{
						{0, 0, 0, 0},
						{2, 2, 2, 2},
						{0, 0, 0, 0},
						{0, 0, 0, 0}
		},
		{
						{0, 0, 2, 0},
						{0, 0, 2, 0},
						{0, 0, 2, 0},
						{0, 0, 2, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{2, 2, 2, 2},
						{0, 0, 0, 0}

		},
		{
						{0, 2, 0, 0},
						{0, 2, 0, 0},
						{0, 2, 0, 0},
						{0, 2, 0, 0}

		},

};
const int block3[4][4][4] = {
		{
						{0, 0, 0, 0},
						{0, 3, 3, 0},
						{3, 3, 0, 0},
						{0, 0, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 3, 0, 0},
						{0, 3, 3, 0},
						{0, 0, 3, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{0, 3, 3, 0},
						{3, 3, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{3, 0, 0, 0},
						{3, 3, 0, 0},
						{0, 3, 0, 0}
		},

};
const int block4[4][4][4] = {
		{
						{0, 0, 0, 0},
						{4, 4, 0, 0},
						{0, 4, 4, 0},
						{0, 0, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 0, 4, 0},
						{0, 4, 4, 0},
						{0, 4, 0, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{4, 4, 0, 0},
						{0, 4, 4, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 4, 0, 0},
						{4, 4, 0, 0},
						{4, 0, 0, 0}
		},

};
const int block5[4][4][4] = {
		{
						{0, 0, 0, 0},
						{0, 0, 5, 0},
						{5, 5, 5, 0},
						{0, 0, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 5, 0, 0},
						{0, 5, 0, 0},
						{0, 5, 5, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{5, 5, 5, 0},
						{5, 0, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{5, 5, 0, 0},
						{0, 5, 0, 0},
						{0, 5, 0, 0}

		},

};
const int block6[4][4][4] = {
		{
						{0, 0, 0, 0},
						{6, 0, 0, 0},
						{6, 6, 6, 0},
						{0, 0, 0, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 6, 6, 0},
						{0, 6, 0, 0},
						{0, 6, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{6, 6, 6, 0},
						{0, 0, 6, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 6, 0, 0},
						{0, 6, 0, 0},
						{6, 6, 0, 0}

		},

};
const int block7[4][4][4] = {
		{
						{0, 0, 0, 0},
						{0, 7, 0, 0},
						{7, 7, 7, 0},
						{0, 0, 0, 0}
		},
		{
						{0, 0, 0, 0},
						{0, 7, 0, 0},
						{0, 7, 7, 0},
						{0, 7, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{7, 7, 7, 0},
						{0, 7, 0, 0}

		},
		{
						{0, 0, 0, 0},
						{0, 7, 0, 0},
						{7, 7, 0, 0},
						{0, 7, 0, 0}

		},

};

enum SYSTEM_CONDITION
{
	SYSTEM_OK,
	SYSTEM_PAUSE,
	SYSTEM_ERROR
};
enum TIME {
	TIME_START,
	TIME_RESTART,
	TIME_STOP,
	TIME_RESET
};
enum BLOCK_STATE {
	DROP,
	T_SPIN,
	TETRIS = 4,
	THREE_LINE_CLEAR = 3,
	TWO_LINE_CLEAR = 2,
	ONE_LINE_CLEAR = 1,
	BACK_TO_BACK
};
enum PLUS_MINUS {
	PLUS = 1,
	MINUS = 0
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
void setcolor(int color)
{
	/*
	14 -> O미노
	11 -> I미노
	10 -> S미노
	4 -> Z미노
	12 -> L미노
	1 -> J 미노
	13 -> T미노
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class Main_Menu
{
private:
	const int Number_of_SubMenu = 3;
	int pointer = 1;

public:
	void Start_Main_Menu() {
		int key;

		setcolor(15);
		draw_console_Menu(); // TETRIS 문구 띄우기
		Show_SubMenu(); // 서브 메뉴 띄우기

		while (true) {
			if (_kbhit()) {
				key = _getch();
				if (key == 224) {
					key = _getch();
					switch (key) {
					case UP:
						pointer -= 1;
						if (pointer < 0) pointer += (Number_of_SubMenu + 1);
						break;
					case DOWN:
						pointer += 1;
						if (pointer > Number_of_SubMenu) pointer -= (Number_of_SubMenu + 1);
						break;
					}
				}
				else if (key == 32 || key == 13) { //Space_Bar or Enter
					break;
				}
				Show_SubMenu();
			}
		}
		Get_Menu();
	}
	void draw_console_Menu()
	{// 10 20 1 20 10
		gotoxy(0, 1);
		cout << endl << endl << endl;
		cout << "\t" << "          ▣▣▣▣▣▣▣  ▣▣▣▣▣▣  ▣▣▣▣▣▣▣  ▣▣▣▣▣    ▣▣▣    ▣▣▣▣▣▣      " << endl;
		cout << "\t" << "                ▣        ▣                  ▣        ▣      ▣      ▣      ▣                " << endl;
		cout << "\t" << "                ▣        ▣                  ▣        ▣      ▣      ▣      ▣                " << endl;
		cout << "\t" << "                ▣        ▣▣▣▣▣▣        ▣        ▣    ▣        ▣      ▣▣▣▣▣▣      " << endl;
		cout << "\t" << "                ▣        ▣                  ▣        ▣▣▣          ▣                ▣      " << endl;
		cout << "\t" << "                ▣        ▣                  ▣        ▣    ▣        ▣                ▣      " << endl;
		cout << "\t" << "                ▣        ▣▣▣▣▣▣        ▣        ▣      ▣    ▣▣▣    ▣▣▣▣▣▣      " << endl;
	}
	void Get_Menu() {
		switch (pointer) {
		case 1: // > 게임 시작 <
			setcolor(15);
			break;
		case 2: // > 게임 설명 <
			Game_Explanation();
			break;
		case 3: // > 게임 종료 <
			break;

		}
	}
	void Game_Explanation() {



		// ---

	}
	void Show_SubMenu() {
		if (pointer == 1) {
			gotoxy(52, 17);
			cout << "> 게임 시작 <" << endl;
		}
		else {
			gotoxy(52, 17);
			cout << "  게임 시작  " << endl;
		}
		if (pointer == 2) {
			gotoxy(52, 19);
			cout << "> 게임 설명 <" << endl;
		}
		else {
			gotoxy(52, 19);
			cout << "  게임 설명  " << endl;
		}
		if (pointer == 3) {
			gotoxy(52, 21);
			cout << "> 게임 종료 <" << endl;
		}
		else {
			gotoxy(52, 21);
			cout << "  게임 종료  " << endl;
		}

	}
};

//clear_console
class Block
{
private:
	int block_next[14] = { }; // 7 blocks(1 bag) x 2
	int ghost_y = initial_y;
	int next_shape[4][4][4] = { };
	int hold_shape[4][4][4] = { };
	int block_shape[4][4][4] = { };
	int rot = 0; //rotation
	int hold = -1;
	int re_next_count = -1;
	int block_number = -1;

protected:
	int table_data[length_x + len_next_x][length_y] = { };
	int hold_data[8][4] = { };
	int x = initial_x + (length_x / 2 - 4), y = initial_y;
	int deleted_line = 0;
	bool can_hold = true;
	/*
	int rot = 0; //rotation
	int x = initial_x + (length_x / 2 - 4), y = initial_y + 1;
	int shape[4][4][4] = { };
	int block_next[14] = { }; // 7 blocks(1 bag) x 2
	int hold = -1;
	int re_next_count = -1;
	bool can_hold = true;
	*/
	void set_block1(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block1[i][j][k];
					}
				}
			}
			block_number = 1;
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block1[i][j][k];
					}
				}
			}
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block1[i][j][k];
					}
				}
			}
		}
	}
	void set_block2(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block2[i][j][k];
					}
				}
			}
			block_number = 2;
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block2[i][j][k];
					}
				}
			}
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block2[i][j][k];
					}
				}
			}
		}
	}
	void set_block3(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block3[i][j][k];
					}
				}
			}
			block_number = 3;
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block3[i][j][k];
					}
				}
			}
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block3[i][j][k];
					}
				}
			}
		}
	}
	void set_block4(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block4[i][j][k];
					}
				}
			}
			block_number = 4;
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block4[i][j][k];
					}
				}
			}
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block4[i][j][k];
					}
				}
			}
		}
	}
	void set_block5(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block5[i][j][k];
					}
				}
			}
			block_number = 5;
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block5[i][j][k];
					}
				}
			}
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block5[i][j][k];
					}
				}
			}
		}
	}
	void set_block6(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block6[i][j][k];
					}
				}
			}
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block6[i][j][k];
					}
				}
			}
			block_number = 6;
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block6[i][j][k];
					}
				}
			}
		}
	}
	void set_block7(int n) {
		if (n == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						block_shape[i][k][j] = block7[i][j][k];
					}
				}
			}
			block_number = 7;
		}
		else if (n == 2) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						next_shape[i][k][j] = block7[i][j][k];
					}
				}
			}
		}
		else if (n == 3) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						hold_shape[i][k][j] = block7[i][j][k];
					}
				}
			}
		}
	}
	
	void Set_Data_Block() {
		Set_Data_Ghost();
		if (Can_Block_Move()) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Is_Overlapped_Ghost_Wall(i, j)) {
						gotoxy(x + 2 * i, y + j);
						/*
						if (shape[rot][i][j] == 9) {
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 9;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 9;
						}
						*/
						switch (block_shape[rot][i][j]) {
						case 1:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 1;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 1;
							break;
						case 2:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 2;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 2;
							break;
						case 3:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 3;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 3;
							break;
						case 4:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 4;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 4;
							break;
						case 5:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 5;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 5;
							break;
						case 6:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 6;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 6;
							break;
						case 7:
							table_data[x - initial_x + 2 * i][y - initial_y + j] = 7;
							table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 7;
							break;

						}
					}
				}

			}
		}
	}
	bool Can_Block_Move() {
		int count = 0;
		for (int fx = 0; fx < 4; fx++) {
			for (int fy = 0; fy < 4; fy++) {
				if (1 <= block_shape[rot][fy][fx] && block_shape[rot][fy][fx] <= 7) {
					if (table_data[x - initial_x + (2 * fy)][y - initial_y + fx] == 10)
						count++;

					if (11 <= table_data[x - initial_x + (2 * fy)][y - initial_y + fx] && table_data[x - initial_x + (2 * fy)][y - initial_y + fx] <= 17)
						count++;
				}
			}
		}
		if (count == 0) return true;
		else return false;
	}
	bool Is_Overlapped_Ghost_Wall(int i, int j) {
		int count = 0;
		if (table_data[x - initial_x + 2 * i][y - initial_y + j] == -2) {
			count++;
		}

		if (count == 0) return true;
		else return false;
	}

	//sold -> delete line

	bool Can_Ghost_Move() {
		int count = 0;
		for (int fx = 0; fx < 4; fx++) {
			for (int fy = 0; fy < 4; fy++) {
				if (1 <= block_shape[rot][fy][fx] && block_shape[rot][fy][fx] <= 7) {
					if (table_data[x - initial_x + (2 * fy)][ghost_y - initial_y + fx] == 10)
						count++;

					if (11 <= table_data[x - initial_x + (2 * fy)][ghost_y - initial_y + fx] && table_data[x - initial_x + (2 * fy)][ghost_y - initial_y + fx] <= 17)
						count++;
				}
			}
		}
		if (count == 0) return true;
		else return false;
	}
	void Set_Data_Ghost() {
		ghost_y = y;
		while (true) {
			ghost_y++;
			if (Can_Ghost_Move()) continue;
			else {
				ghost_y--;
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gotoxy(x + 2 * i, ghost_y + j);
				if (1 <= block_shape[rot][i][j] && block_shape[rot][i][j] <= 7) {
					table_data[x - initial_x + 2 * i][ghost_y - initial_y + j] = -1;
					table_data[x - initial_x + 2 * i + 1][ghost_y - initial_y + j] = -1;
				}
			}
		}



	}

	void Move(int key) {
		if (key == LEFT) {
			x -= 2;
			if (Can_Block_Move() == false) x += 2;
		}
		else if (key == RIGHT) {
			x += 2;
			if (Can_Block_Move() == false) x -= 2;
		}
		else if (key == DOWN) {
			y++;
			if (Can_Block_Move() == false) y--;
		}
		else { //(key == UP)
			rot = (rot + 2) % 4;
			if (Can_Block_Move() == false) {
				if (rot == 0) rot = 2;
				else if (rot == 1) rot = 3;
				else rot -= 2;
			}
		}
	}
	void Rotate_Plus() { // X or x or D or d
		int angle = rot * 90;
		int temp_x = x, temp_y = y;
		int preset = 0;

		rot++;
		if (rot == 4) rot = 0;

		if (3 <= block_number && block_number <= 7) {
			if (Can_Block_Move() == false) {
				for (preset = 1; preset <= 5;) {
					Rotation_Preset(angle, preset, PLUS);
					if (Can_Block_Move() == false) {
						x = temp_x, y = temp_y;
						preset++;
					}
					else break;
				}
			}
		}
		else if(block_number == 2) { // I 미노 
			
		}

		if (Can_Block_Move() == false) { //preset 이후에도 회전 불가면 회전 안 함
			rot--;
			if (rot == -1) rot = 3;
		}
		gotoxy(0, 0);
		printf("temp x, y = %d %d                  \n", temp_x, temp_y);
		printf("angle = %d / preset = %d                     ", angle, preset);
	}
	void Rotate_Minus() { // Z or z or S or s
		int angle = rot * 90;
		int temp_x = x, temp_y = y;
		int preset = 0;

		rot--;
		if (rot == -1) rot = 3;

		if (3 <= block_number && block_number <= 7) {
			if (Can_Block_Move() == false) {
				for (preset = 1; preset <= 5;) {
					Rotation_Preset(angle, preset, MINUS);
					if (Can_Block_Move() == false) {
						x = temp_x, y = temp_y;
						preset++;
					}
					else break;
				}
			}
		}
		else if (block_number == 2) { // I 미노 

		}

		if (Can_Block_Move() == false) { //preset 이후에도 회전 불가면 회전 안 함
			rot++;
			if (rot == 4) rot = 0;
		}
		gotoxy(0, 0);
		printf("temp x, y = %d %d                  \n", temp_x, temp_y);
		printf("angle = %d / preset = %d                     ", angle, preset);
	}
	void Rotation_Preset(int angle, int preset, int plus)
	{
		int type = 0;
		if ((angle == 0 && plus == 1) || angle == 90 || (angle == 180 && plus == 0)) {
			if ((angle == 0 && plus == 1) || (angle == 180 && plus == 0)) type = 1;
			if (angle == 90) type = 0;
			switch (preset) {
			case 1:
				break;
			case 2:
				if (type) x -= 2;
				else x += 2;
				break;
			case 3:
				if (type) x -= 2, y--;
				else x += 2, y++;
				break;
			case 4:
				if (type) y += 2;
				else y -= 2;
				break;
			case 5:
				if (type) x -= 2, y += 2;
				else x == 2, y -= 2;
				break;
			}
		}
		else if ((angle == 180 && plus == 1) || angle == 270 || (angle == 0 && plus == 0)) {
			if ((angle == 180 && plus == 1) || (angle == 0 && plus == 0)) type = 1;
			if (angle == 270) type = 0;
			switch (preset) {
			case 1: 
				break;
			case 2: 
				if (type) x += 2; 
				else x -= 2; 
				break;
			case 3: 
				if (type) x += 2, y--; 
				else x -= 2, y++; 
				break;
			case 4: 
				if (type) y += 2; 
				else y -= 2; 
				break;
			case 5: 
				if (type) x += 2, y += 2; 
				else x -= 2, y -= 2; 
				break;
			}
		}
	}

	bool Hold() {
		bool whether_next;
		int temp;
		x = initial_x + (length_x / 2 - 4), y = initial_y;
		if (hold == -1) {
			hold = block_next[re_next_count - 1];
			whether_next = 1;
		}
		else {
			temp = hold;
			hold = block_next[re_next_count - 1];

			if (temp == 1) set_block1(1);
			else if (temp == 2) set_block2(1);
			else if (temp == 3) set_block3(1);
			else if (temp == 4) set_block4(1);
			else if (temp == 5) set_block5(1);
			else if (temp == 6) set_block6(1);
			else if (temp == 7) set_block7(1);

			whether_next = 0;
		}
		rot = 0;
		Set_Data_Hold();
		return whether_next;
	}
	void Set_Data_Hold() {
		if (hold != -1) {
			if (hold == 1) set_block1(3);
			else if (hold == 2) set_block2(3);
			else if (hold == 3) set_block3(3);
			else if (hold == 4) set_block4(3);
			else if (hold == 5) set_block5(3);
			else if (hold == 6) set_block6(3);
			else if (hold == 7) set_block7(3);
		}
		for (int i = 0; i < 8; i++) { //초기화
			for (int j = 0; j < 4; j++) {
				hold_data[i][j] = 0;
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hold_data[2 * i][j] = hold_shape[0][i][j];
				hold_data[2 * i + 1][j] = hold_shape[0][i][j];
			}
		}
	}

	//SpaceBar -> Solid -> delete line -> Score
	void Hard_Drop() { //Hard Drop
		while (true) {
			y++;
			if (Can_Block_Move()) continue;
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
				if (1 <= block_shape[rot][i][j] && block_shape[rot][i][j] <= 7) {
					if (Is_Overlapped_Ghost_Wall(i, j)) {
						table_data[x - initial_x + 2 * i][y - initial_y + j] = 10 + block_shape[rot][i][j];
						table_data[x - initial_x + 2 * i + 1][y - initial_y + j] = 10 + block_shape[rot][i][j];
					}
				}
			}
		}
		if (can_hold == false) can_hold = true;
		rot = 0;
		//set_nexts_and_hold();
		Delete_Line();
	}
	void Delete_Line() {
		int count = 0;
		for (int j = 0; j < length_y; j++) {
			for (int i = 0; i < length_x; i++) {
				if (i % 2 == 0) {
					if (11 <= table_data[i][j] && table_data[i][j] <= 17) {
						count++;
					}
				}
			}
			if (count >= length_x / 2 - 2) { //delete line
				deleted_line++;
				for (int fy = j; fy > 1; fy--) {
					for (int fx = 0; fx < length_x; fx++) {
						table_data[fx][fy] = table_data[fx][fy - 1];
					}
				}
				count = 0;
				j--;
			}
			else count = 0;
		}
		//빈도수 고려함
		/*
		if (deleted_line == 2) {
			if(t_spin)
		}
		*/
	}
	
	

	void Set_Order_Next_Block() {
		if (re_next_count >= 7) {
			re_next_count = 0;
			for (int i = 0; i < 7; i++) {
				block_next[i] = block_next[i + 7];
			}
		Re_second_bag:
			for (int i = 7; i < 14; i++) {
				block_next[i] = rand() % 7 + 1;
			}
			for (int i = 7; i < 14; i++) {
				for (int j = 7; j < 14; j++) {
					if (i != j) {
						if (block_next[i] == block_next[j]) {
							goto Re_second_bag;
						}
					}
				}
			}
		}
		else if (re_next_count == -1) {
			re_next_count = 0;
		Re_first_bag:
			for (int i = 0; i < 7; i++) {
				block_next[i] = rand() % 7 + 1;
			}
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					if (i != j) {
						if (block_next[i] == block_next[j]) {
							goto Re_first_bag;
						}
					}
				}
			}
			goto Re_second_bag;
		}

		if (block_next[re_next_count] == 1) set_block1(1);
		else if (block_next[re_next_count] == 2) set_block2(1);
		else if (block_next[re_next_count] == 3) set_block3(1);
		else if (block_next[re_next_count] == 4) set_block4(1);
		else if (block_next[re_next_count] == 5) set_block5(1);
		else if (block_next[re_next_count] == 6) set_block6(1);
		else if (block_next[re_next_count] == 7) set_block7(1);

		re_next_count++;

	}
	void Clear_Data_Next_Block() {
		for (int i = length_x; i < length_x + len_next_x; i++) {
			for (int j = 0; j < length_y; j++) {
				table_data[i][j] = 0;
			}
		}
	}
	void Set_Data_Next_Block() {
		Clear_Data_Next_Block();
		for (int k = 0; k < 5; k++) {
			if (block_next[re_next_count + k] == 1) set_block1(2);
			else if (block_next[re_next_count + k] == 2) set_block2(2);
			else if (block_next[re_next_count + k] == 3) set_block3(2);
			else if (block_next[re_next_count + k] == 4) set_block4(2);
			else if (block_next[re_next_count + k] == 5) set_block5(2);
			else if (block_next[re_next_count + k] == 6) set_block6(2);
			else if (block_next[re_next_count + k] == 7) set_block7(2);

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					table_data[length_x + 2 * i + 1][4 * k + j - k] = next_shape[0][i][j];
					table_data[length_x + 2 * i + 2][4 * k + j - k] = next_shape[0][i][j];
				}
			}
		}
	}

	bool Is_Block_On_Ground() {
		y++;
		if (Can_Block_Move()) {
			y--;
			return false;
		}
		else {
			y--;
			return true;
		}
	}

	bool GameOver() {
		bool bool_Gameover = false;
		for (int i = 9; i < 16; i++) {
			for (int j = 3; j > 0; j--) {
				if (11 <= table_data[i][j] && table_data[i][j] <= 17) bool_Gameover = true;
			}
		}
		return bool_Gameover;
	}
};

class Console : public Block
{
public:
	void Clear_Console_Gametable()
	{
		for (int i = 0; i < length_x; i++) {
			for (int j = 0; j < length_y; j++) {
				if ((1 <= table_data[i][j] && table_data[i][j] <= 7) || table_data[i][j] == -1) table_data[i][j] = 0;
			}
		}
		for (int i = 2; i < length_x - 2; i++) {
			for (int j = 1; j < length_y - 1; j++) {
				gotoxy(initial_x + i, initial_y + j);
				if (table_data[i][j] != 10 && !(11 <= table_data[i][j] && table_data[i][j] <= 17))
					cout << " ";
			}
		}
	}
	void Clear_Console_Next_Block() {
		for (int i = length_x; i < length_x + len_next_x - 2; i++) {
			for (int j = 1; j < length_y - 1; j++) {
				gotoxy(initial_x + i, initial_y + j);
				if (table_data[i][j] != 10 && !(11 <= table_data[i][j] && table_data[i][j] <= 17))
					cout << " ";
			}
		}
	}
	void Clear_Console_Hold() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				gotoxy(hold_ini_x + i, hold_ini_y + j);
				cout << " ";
			}
		}
	}


	//draw_console
	void Draw_Console_Basic_Frame(int len_x, int len_y, int i_x, int i_y) {
		int pos[2] = { i_x, i_y };
		len_x--; //보정 
		for (int i = 0; i <= len_x; i++) {
			if (i % 2 == 0) {
				gotoxy(pos[0] + i, pos[1]);
				cout << "▩";
			}
			table_data[i][0] = -2;
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
	void Draw_Console_Gametable() {
		for (int fx = 0; fx < length_x + len_next_x; fx++) {
			for (int fy = 0; fy < length_y; fy++) {
				if (table_data[fx][fy] == 0 || table_data[fx][fy] == 10) continue;
				else if (1 <= table_data[fx][fy] && table_data[fx][fy] <= 7) {
					switch (table_data[fx][fy]) {
					case 1: //14
						setcolor(14);
						break;
					case 2: //11
						setcolor(11);
						break;
					case 3: //10
						setcolor(10);
						break;
					case 4: //4
						setcolor(4);
						break;
					case 5: //12
						setcolor(12);
						break;
					case 6: //1
						setcolor(1);
						break;
					case 7: //13
						setcolor(13);
						break;
					}
					if (fx % 2 == 0) {
						gotoxy(fx + initial_x, fy + initial_y);
						cout << "■";
					}
					setcolor(15);

				}
				else if (11 <= table_data[fx][fy] && table_data[fx][fy] <= 17) {
					switch (table_data[fx][fy]) {
					case 11: //14
						setcolor(14);
						break;
					case 12: //11
						setcolor(11);
						break;
					case 13: //10
						setcolor(10);
						break;
					case 14: //4
						setcolor(4);
						break;
					case 15: //12
						setcolor(12);
						break;
					case 16: //1
						setcolor(1);
						break;
					case 17: //13
						setcolor(13);
						break;
					}
					if (fx % 2 == 0) {
						gotoxy(fx + initial_x, fy + initial_y);
						cout << "▣";
					}
					setcolor(15);
				}
				else if (table_data[fx][fy] == -1) {
					//no color
					if (fx % 2 == 0) {
						gotoxy(fx + initial_x, fy + initial_y);
						cout << "□";
					}
				}
				else if (table_data[fx][fy] == -2) {
					if (fx % 2 == 0) {
						gotoxy(fx + initial_x, fy + initial_y);
						cout << "▩";
					}
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				if (1 <= hold_data[i][j] && hold_data[i][j] <= 7) {
					switch (hold_data[i][j]) {
					case 1: //14
						setcolor(14);
						break;
					case 2: //11
						setcolor(11);
						break;
					case 3: //10
						setcolor(10);
						break;
					case 4: //4
						setcolor(4);
						break;
					case 5: //12
						setcolor(12);
						break;
					case 6: //1
						setcolor(1);
						break;
					case 7: //13
						setcolor(13);
						break;
					}
					if (i % 2 == 0) {
						gotoxy(hold_ini_x + i, hold_ini_y + j);
						cout << "■";
					}
					setcolor(15);
				}
			}
		}
	}

	//test
	void Print_Gametable_Data() {

		gotoxy(initial_x + length_x + 14, initial_y);
		for (int i = 0; i < length_y; i++) {
			for (int j = 0; j < length_x + len_next_x; j++) {
				if (table_data[j][i] == 10) {
					if (j % 2 == 0)
						cout << "▩";

				}
				else if (table_data[j][i] < 0) {
					if (j % 2 == 0)
						cout << table_data[j][i];
				}
				else {
					if (table_data[j][i] >= 10) {
						if (j % 2 == 0)
							cout << table_data[j][i];

					}
					else cout << table_data[j][i];
				}
			}
			gotoxy(initial_x + length_x + 14, initial_y + i + 1);
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				if (i % 2 == 0) {
					gotoxy(2 * (length_x + initial_x + len_next_x) + i - 6, initial_y + j);
					cout << hold_data[i][j];
				}
			}
		}
	}
};

class Game : public Console
{
private:
	unsigned int score = 0;
	bool next_block = false;
	bool bool_Auto_Down = false;
	bool counting_on_ground = false;

	clock_t Auto_Down_Start = 0, Auto_Down_End = 0;
	float Auto_Down_Time = 0;
	float Temp_Time_Auto_Down = 0;

	clock_t On_Ground_Start = 0, On_Ground_End = 0;
	float On_Ground_Time = 0;
	float Temp_Time_On_Ground = 0;

public:
	void GameStart() {
		srand((unsigned int)time(NULL));

		Main_Menu Tetris_Menu;
		Tetris_Menu.Start_Main_Menu();
		system("cls");

		Draw_Console_Basic_Frame(length_x, length_y, initial_x, initial_y); // frame 그리기
		Set_Order_Next_Block(); //초기 블럭, 넥스트 블럭 결정
		Set_Data_Block(); //초기 블럭 데이터 입력
		Set_Data_Next_Block(); // 넥스트 블럭 데이터 입력
		Draw_Console_Gametable(); // 입력된 데이터를 출력

		Auto_Down_Start = clock();
		while (true) //키 입력
		{
			int key;

			Gravity(); //중력(Auto Down)
			if (_kbhit() || bool_Auto_Down) {
				if (_kbhit()) {
					key = _getch();
					if (key == 224) {
						key = _getch();
						switch (key) {
						case UP:
							Move(UP);
							break;
						case DOWN:
							Auto_Down_Time = 0;
							Auto_Down_Start = clock();
							Move(DOWN);
							break;
						case LEFT:
							Auto_Down_Time = 0;
							Auto_Down_Start = clock();
							Move(LEFT);
							break;
						case RIGHT:
							Auto_Down_Time = 0;
							Auto_Down_Start = clock();
							Move(RIGHT);
							break;
						}
					}
					else if (key == 97 || key == 65) { // A or a 
						if (can_hold) {
							next_block = Hold();
							Clear_Console_Hold();
							can_hold = false;
						}
						else continue;
					}
					else if (key == 88 || key == 120 || key == 100 || key == 68) { // X or x or D or d
						Auto_Down_Time = 0;
						Auto_Down_Start = clock();
						Rotate_Plus();
					}
					else if (key == 90 || key == 122 || key == 115 || key == 83) { // Z or z or S or s
						Auto_Down_Time = 0;
						Auto_Down_Start = clock();
						Rotate_Minus();
					}
					else if (key == 32) { // SpaceBar 
						Hard_Drop();
						next_block = true;
					}
					else if (key == 27) {
						//game_pause();
						break;
					}
				}
				//키 입력 끝


				if (GameOver()) {
					//GameOver();
					break;
				}
				if (next_block) {
					Set_Order_Next_Block(); // next 갱신
					Clear_Console_Gametable();  // 콘솔 지우기
					Clear_Console_Next_Block(); // 콘솔 지우기
					x = initial_x + (length_x / 2 - 4), y = initial_y; // 위치 초기화
					Set_Data_Block(); // 블록 데이터 입력
					Set_Data_Next_Block(); // 넥스트 데이터 입력
					next_block = false;
					On_Ground_Times(TIME_RESET);
				}
				else if (Can_Block_Move()) {
					Clear_Console_Gametable(); //clear
					Set_Data_Block(); // 블록 데이터 입력
				}

				//마무리 - 데이터 정리 및 마무리 함수

				Score(deleted_line); //점수 추가


				bool_Auto_Down = false;
				Draw_Console_Gametable(); // gametable Reload!!
				Print_Gametable_Data(); //test

			}
		}
	}
	void Auto_Down_Times(int CONDITION) {
		if (CONDITION == TIME_START) {
			Auto_Down_Start = clock();
		}
		else if (CONDITION == TIME_RESTART) {
			Auto_Down_Start = clock();
		}
		else if (CONDITION == TIME_STOP) {
			Auto_Down_End = clock();
			Auto_Down_Time = ((float)(Auto_Down_End - Auto_Down_Start) / CLOCKS_PER_SEC) + Temp_Time_Auto_Down;
			Temp_Time_Auto_Down = Auto_Down_Time;

		}
		else if (CONDITION == TIME_RESET) {
			Auto_Down_Time = 0;
			Temp_Time_Auto_Down = 0;
			Auto_Down_Start = clock();
		}
	}
	void On_Ground_Times(int CONDITION) {
		if (CONDITION == TIME_START) {
			On_Ground_Start = clock();
		}
		else if (CONDITION == TIME_RESTART) {
			On_Ground_Start = clock();
		}
		else if (CONDITION == TIME_STOP) {
			On_Ground_End = clock();
			On_Ground_Time = ((float)(On_Ground_End - On_Ground_Start) / CLOCKS_PER_SEC) + Temp_Time_On_Ground;
			Temp_Time_On_Ground = On_Ground_Time;

		}
		else if (CONDITION == TIME_RESET) {
			On_Ground_Time = 0;
			Temp_Time_On_Ground = 0;
			On_Ground_Start = clock();
		}
	}
	void Gravity() {
		Auto_Down_End = clock();
		if (counting_on_ground) On_Ground_End = clock();
		Auto_Down_Time = ((float)(Auto_Down_End - Auto_Down_Start) / CLOCKS_PER_SEC) + Temp_Time_Auto_Down;
		if (counting_on_ground) On_Ground_Time = ((float)(On_Ground_End - On_Ground_Start) / CLOCKS_PER_SEC) + Temp_Time_On_Ground;
		if (Auto_Down_Time >= 1) { // DOWN or SOLID
			y++;
			bool_Auto_Down = true;
			if (Can_Block_Move()) {
				Set_Data_Block();
				Auto_Down_Times(TIME_START);
			}
			else {
				y--;
				Solid();
				next_block = true;
				Auto_Down_Times(TIME_START);
			}
		}
		if (Is_Block_On_Ground()) { // On_Ground 측정
			if (counting_on_ground == false) { // 측정 중이 아니였나면 측정 시작
				On_Ground_Times(TIME_RESTART);
				counting_on_ground = true;
			}
		}
		else { // On_Ground 아니면
			if (counting_on_ground == true) { // 측정 중단
				On_Ground_Times(TIME_STOP);
				counting_on_ground = false;
			}
		}
		if (On_Ground_Time >= 3 && Is_Block_On_Ground()) { //소프트 드랍으로 Solid가 안되게 하는 오류 수정
			Solid();
			next_block = true;
			bool_Auto_Down = true;
			counting_on_ground = false;
			Auto_Down_Times(TIME_RESTART);
			On_Ground_Times(TIME_RESET);
		}
	}

	void Score(int CONDITION) {
		if (CONDITION == DROP) {

		}
		else if (CONDITION == T_SPIN) {

		}
		else if (CONDITION == TETRIS) {

		}
		else if (CONDITION == THREE_LINE_CLEAR) {

		}
		else if (CONDITION == TWO_LINE_CLEAR) {

		}
		else if (CONDITION == ONE_LINE_CLEAR) {

		}
		else if (CONDITION == BACK_TO_BACK) {

		}
	}
};

int main()
{
	system("mode con cols=120 lines=30 | title TETRIS"); // 콘솔창 크기 및 제목 설정
	CursorView(false);
	Game Tetris;
	Tetris.GameStart();



	gotoxy(0, 50);
}

//https://gall.dcinside.com/mgallery/board/view/?id=pute&no=19824 //한국어
//https://harddrop.com/wiki/SRS#Basic_Rotation //영어 (자세함)