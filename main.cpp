#include "raylib.h"
#include <iostream>
#include "rlgl.h"
#include <deque>
#include <raymath.h>
Color Colors[7] = { ORANGE, YELLOW, LIME, PURPLE, PINK, WHITE, GREEN };
int cellSize = 30;
int cellCount = 25;
double lastUpdTime = 0;
using namespace std;
bool updTriggered(double inter) {
	double currentTime = GetTime();
	if (currentTime - lastUpdTime >= inter) {
		lastUpdTime = currentTime;
		return true;
	}
	return false;
}
void Equal_matrix(Vector2* matrix, Vector2* _matrix) {
	for (int i = 0; i < 4; i++) {
		matrix[i] = _matrix[i];
	}
}
class Tetramino {


public:

	void is_fall(int( *border)[20]) {
		int x1 = matrix[0].x, x2 = matrix[1].x, x3 = matrix[2].x, x4 = matrix[3].x;
		int y1 = matrix[0].y, y2 = matrix[1].y, y3 = matrix[2].y, y4 = matrix[3].y;
		
		if (y1 == 19 || y2 == 19 || y3 == 19 || y4 == 19) {
			fall = true;
		}
		else if (border[x1][y1 + 1] == 1 || border[x2][y2 + 1] == 1 || border[x3][y3 + 1] == 1 || border[x4][y4 + 1] == 1) {
			fall = true;
		}
		if (fall) {
			border[x1][y1] = 1;
			border[x2][y2] = 1;
			border[x3][y3] = 1;
			border[x4][y4] = 1;
			
		}

	}
	void Update() {
		
		
		if (!fall) {
			for (int i = 0; i < 4; i++) {
				matrix[i] = Vector2Add(matrix[i], y1);
			}
			y_perem += 1;
		}
			
			
		
	}
	void Draw() {
		for (int i = 0; i < 4; i++) {
			int x = matrix[i].x; int y = matrix[i].y;

			DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, color);
		}

	}
	void Move(bool flag, int(*border)[20]) { //flag == true вправо иначе влево
		bool _flag = true;
	
		if (!fall) {
			for (int i = 0; i < 4; i++) {
				int x = matrix[i].x, y = matrix[i].y;
					if ((x == 0 && !flag) || (x == 16 && flag)|| (flag && border[x+1][y] == 1) || (!flag && border[x-1][y] == 1)) {
						_flag = false;
						
						break;
					}

			}
			if (_flag) {
				for (int i = 0; i < 4; i++) {

					matrix[i] = (flag ? (Vector2Add(matrix[i], x1)) : Vector2Add(matrix[i], Vector2Scale(x1, -1)));

				}

				if (flag) { x_perem += 1; }
				else { x_perem -= 1; }
			}
		}
	}
	bool Right_Rotate_Check(Vector2 _matrix[4], int(*border)[20]) {
		int x = 0, y = 0;
		for (int i = 0; i < 4; i++) {
			x = 0, y = 0;
			x += x_perem + _matrix[i].x;
			y += y_perem + _matrix[i].y;
			if (x >= 17 || y >= 19 ||  border[x][y+1] == 1) {
				return false;
			}
		}
		return true;
	}
	void Rotate(bool flag, int(*border)[20]) {//flag == true по часовой
		bool _flag = true;
		if (!fall) {
			if (flag) {
				condition = (condition + 1 < 4 ? condition + 1 : 0);
			}
			else {
				condition = (condition - 1 >= 0 ? condition - 1 : 3);
			}
			switch (condition) {
			case 0: if (Right_Rotate_Check(matrix0, border)){
				Equal_matrix(matrix, matrix0);
			} else { _flag = false; }  break;
			case 1:if (Right_Rotate_Check(matrix1, border)) {
				Equal_matrix(matrix, matrix1);
			}
				  else { _flag = false; }  break;
			case 2:if (Right_Rotate_Check(matrix2, border)) {
				Equal_matrix(matrix, matrix2);
			}
				  else { _flag = false; }  break;
			case 3:if (Right_Rotate_Check(matrix3, border)) {
				Equal_matrix(matrix, matrix3);
			}
				  else { _flag = false; }  break;
			}
			if (_flag) {
				for (int i = 0; i < 4; i++) {
					matrix[i] = Vector2Add(matrix[i], Vector2Scale(x1, x_perem));
					matrix[i] = Vector2Add(matrix[i], Vector2Scale(y1, y_perem));
				}
			}
		}

	}
	void KickstartMyHeart() {
		y_perem = 0; x_perem = 10;
		fall = false;
		condition = 0;
		switch (type) {
		case 0:
			matrix[0] = { 1 + 10,1 };matrix[1] = { 1 + 10,0 };matrix[2] = { 2 + 10, 0 };matrix[3] = { 0 + 10, 0 }; break;
		case 1:
			matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 0 + 10, 1 };matrix[3] = { 1 + 10, 1 }; break;
		case 2:
			matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 2 + 10, 0 };matrix[3] = { 3 + 10, 0 }; break;
		case 3:
			matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 0 + 10, 1 };matrix[3] = { 0 + 10, 2 }; break;
		case 4:
			matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 1 + 10, 2 }; break;
		case 5:
			matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 1 }; break;
		case 6:
			matrix[0] = { 0 + 10,1 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 0 }; break;
		}
	}
	Vector2 y1 = { 0,1 };
	Vector2 e = { 1, 1 };
	Vector2 x1 = { 1, 0 };
	int x_perem = 10;
	int y_perem = 0;
	Vector2 matrix[4];
	Vector2 matrix0[4];
	Vector2 matrix1[4];
	Vector2 matrix2[4];
	Vector2 matrix3[4];
	int condition = 0;
	bool fall = false;
	int type;
	Color color;
};
class TBlock : public Tetramino {
public:

	TBlock(){
		matrix[0] = { 1+10,1 };matrix[1] = {1+10,0 };matrix[2] = { 2+10, 0};matrix[3] = { 0+10, 0};		
		matrix0[0] = { 1,1 }; matrix0[1] = { 0, 0 }; matrix0[2] = { 1, 0 }; matrix0[3] = { 2, 0 };
		matrix1[0] = { 1, 1 }; matrix1[1] = { 2, 0 }; matrix1[2] = { 2, 1 }; matrix1[3] = { 2,2 };
		matrix2[0] = { 1, 1 }; matrix2[1] = { 2, 2 }; matrix2[2] = { 1,2 }; matrix2[3] = { 0, 2 };
		matrix3[0] = { 1,1 }; matrix3[1] = { 0,2 }; matrix3[2] = { 0,1 }; matrix3[3] = { 0,0 };
		type = 0;
		color = Colors[type];
	}
	

};

class QuadroBlock : public Tetramino {
public:
	QuadroBlock() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 0 + 10, 1 };matrix[3] = { 1 + 10, 1 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 0,1 }; matrix0[3] = { 1, 1 };
		Equal_matrix(matrix1, matrix0); Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix0);
		type = 1;
		color = Colors[type];
	}
};
class LongBlock : public Tetramino {
public:

	LongBlock() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 2 + 10, 0 };matrix[3] = { 3 + 10, 0 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 2, 0 }; matrix0[3] = { 3, 0 };
		matrix1[0] = { 1, 0 }; matrix1[1] = { 1,1 }; matrix1[2] = { 1,2 }; matrix1[3] = { 1, 3 };
		Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix1);
		type = 2;
		color = Colors[type];
	}

};
class GBlockRight : public Tetramino {
public:

	GBlockRight() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 0 + 10, 1};matrix[3] = { 0+ 10, 2};
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 0,1 }; matrix0[3] = { 0,2 };
		matrix1[0] = { 0, 0 }; matrix1[1] = { 1, 0 }; matrix1[2] = { 2, 0 }; matrix1[3] = { 2,1 };
		matrix2[0] = { 2, 0 }; matrix2[1] = { 2, 1 }; matrix2[2] = {2,2 }; matrix2[3] = { 1, 2 };
		matrix3[0] = { 0,1 }; matrix3[1] = { 0,2 }; matrix3[2] = { 1,2 }; matrix3[3] = { 2,2};
		type = 3;
		color = Colors[type];
	}

};
class GBlockLeft : public Tetramino {
public:

	GBlockLeft() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 1 + 10, 2 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 1,2 };
		matrix1[0] = { 0, 1}; matrix1[1] = { 1, 1 }; matrix1[2] = { 2, 1 }; matrix1[3] = { 2,0 };
		matrix2[0] = { 0, 0 }; matrix2[1] = { 0, 1 }; matrix2[2] = { 0,2 }; matrix2[3] = { 1, 2 };
		matrix3[0] = { 0,1 }; matrix3[1] = { 0,0 }; matrix3[2] = { 1,0 }; matrix3[3] = { 2,0};
		type = 4;
		color = Colors[type];
	}

};
class ZBlockRight: public Tetramino {
public:

	ZBlockRight() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 1 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 2,1 };
		matrix1[0] = { 1, 1 }; matrix1[1] = { 2, 1 }; matrix1[2] = { 1,2}; matrix1[3] = { 2,0 };
		Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix1);
		type = 5;
		color = Colors[type];
	}
};
class ZBlockLeft : public Tetramino {
public:

	ZBlockLeft() {
		matrix[0] = { 0 + 10,1 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 0};
		matrix0[0] = { 0, 1}; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 2,0 };
		matrix1[0] = { 1, 0 }; matrix1[1] = { 1, 1 }; matrix1[2] = { 2, 1 }; matrix1[3] = { 2,2 };
		Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix1);
		type = 6;
		color = Colors[type];
	}
};
class playground {
public:
	playground() {
		for (int i = 0; i < y_len*x_len; i++) {
			play_matrix[i] = { 0, 0 };
		}
		
	}
	void Draw() {
		for (int i = 0; i < svobodn; i++) {
			
			DrawRectangle(play_matrix[i].x * cellSize, play_matrix[i].y * cellSize, cellSize, cellSize, Colors[play_matrix_color[i]]);
		}
	}
	void Otpechatok(Tetramino obj) {
		for (int i = 0; i<4; i++) {
			play_matrix[i + svobodn].x = obj.matrix[i].x;
			play_matrix[i + svobodn].y  = obj.matrix[i].y;
			play_matrix_color[i + svobodn] = obj.type;
		}
		
		svobodn += 4;
	}
	void is_streak(int(*border)[20]) {
		int stroka[20] = {};
		for (int i = 0; i < svobodn; i++) {
			int a = play_matrix[i].y;
			stroka[a] += 1;
		}
		for (int i = 0; i < 20; i++) {
			if (stroka[i] == 17) {
				int k = i;
				cout << 1;
				for (int j = 0; j < svobodn; j++) {
					if (play_matrix[j].y == i) {
						
						play_matrix[j].x = -1;
						play_matrix[j].y = -1;
					}
				}
				Vector2 buf;
				for (int i = 0; i < svobodn; i++) {
					if (play_matrix[i].y == -1) {
						for (int j = i; j<svobodn; j++) {
							buf = play_matrix[i];
							play_matrix[i] = play_matrix[i + 1];
							play_matrix[i + 1] = buf;
						}
					}
				}
				svobodn -= 17;
				for (int i = 0; i < svobodn; i++) {
					if (play_matrix[i].y >= k) {
						play_matrix[i].y -= 1;
					}
				}
			}
		}


	}
	int x_len = 20;
	int y_len = 17;
	int svobodn = 0; //Количество свободных ячеек
	Vector2 play_matrix[20*17];
	int play_matrix_color[20 * 17];
	
};
int main() {
	SetTraceLogLevel(LOG_NONE);//y - 20 x - 17
	InitWindow(800, 700, "Tetris");
	SetTargetFPS(60);
	/*QuadroBlock QuadroBlock;
	LongBlock LongBlock;
	GBlockRight GBlockRight;
	GBlockLeft GBlockLeft;
	ZBlockRight ZBlockRight;
	ZBlockLeft ZBlockLeft;
	TBlock TBlock;*/
	Tetramino Blocks[7] = { TBlock(), QuadroBlock(), LongBlock(), GBlockRight(), GBlockLeft(), ZBlockRight(), ZBlockLeft()};
	playground playground;
	int border[17][20];
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 20; j++) {
			border[i][j] = 0;
		}
	}
	int i = 0;
	while (!WindowShouldClose()) {
			
		BeginDrawing();
		
		ClearBackground(BLUE);
		DrawRectangle(0, 0, 510, 600, BLACK);
		
		playground.Draw();
			Blocks[i].Draw();
		
			if (updTriggered(0.2)) {

				Blocks[i].Update();
				if (IsKeyDown(KEY_D)) {
					Blocks[i].Move(true, border);
				}
				else if (IsKeyDown(KEY_A)) {
					Blocks[i].Move(false, border);
				}
				Blocks[i].is_fall(border);
			}
	

				if (IsKeyPressed(KEY_RIGHT)) {
					Blocks[i].Rotate(true, border);
				}
				else if (IsKeyPressed(KEY_LEFT)) {
					Blocks[i].Rotate(false, border);
				}
			
			if (Blocks[i].fall) {
			
				playground.Otpechatok(Blocks[i]);
				playground.is_streak(border);
				Blocks[i].KickstartMyHeart();
				if (i > 5) { i = 0; }
				else { i += 1; }
			}
		
		

			

		EndDrawing();
	}

}
