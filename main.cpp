#include "raylib.h"
#include <iostream>
#include "rlgl.h"
#include <deque>
#include <raymath.h>

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
	Tetramino() {
		
	}
	void is_fall(int* border) {
		int x1 = matrix[0].x, x2 = matrix[1].x, x3 = matrix[2].x, x4 = matrix[3].x;
		int y1 = matrix[0].y, y2 = matrix[1].y, y3 = matrix[3].y, y4 = matrix[3].y;
		int max_y = max(y1, y2), b = max(y3, y4);
		max_y = max(max_y, b); //Максимальное значение по y самое низкое
		int min_y = min(y1, y2); b = min(y3, y4);
		min_y = min(min_y, b); //Самое высокое
		if (max_y == 19) {
			cout << 1 << endl;
			fall = true;
			
			
		}
		else if (border[x1] == max_y+1 ) {

			cout << 1 << " " << border[x1] << endl;
			fall = true;
		}
		else if (border[x2] == max_y +1) {
			cout << 2 << " " << border[x2] << endl;
			fall = true;
		}
		else if (border[x3] == max_y + 1) {
			cout << 3 << " " << border[x3] << endl;
			fall = true;
		}
		else if (border[x4] == max_y + 1) {
			cout << 4 << " " << border[x4] << endl;
			fall = true;
		} 
		if (fall) {
			border[x1] = min(border[x1], y1);
			border[x2] = min(border[x2], y2);
			border[x3] = min(border[x3], y3);
			border[x4] = min(border[x4], y4);
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
	void Move(bool flag) { //flag == true вправо иначе влево
		if (!fall) {
			for (int i = 0; i < 4; i++) {
				matrix[i] = (flag ? (Vector2Add(matrix[i], x1)) : Vector2Add(matrix[i], Vector2Scale(x1, -1)));

			}
			if (flag) { x_perem += 1; }
			else { x_perem -= 1; }
		}
	}
	void Rotate(bool flag) {//flag == true по часовой
		if (!fall) {
			if (flag) {
				condition = (condition + 1 < 4 ? condition + 1 : 0);
			}
			else {
				condition = (condition - 1 >= 0 ? condition - 1 : 3);
			}
			switch (condition) {
			case 0: Equal_matrix(matrix, matrix0);  break;
			case 1: Equal_matrix(matrix, matrix1); break;
			case 2: Equal_matrix(matrix, matrix2); break;
			case 3: Equal_matrix(matrix, matrix3); break;
			}
			for (int i = 0; i < 4; i++) {
				matrix[i] = Vector2Add(matrix[i], Vector2Scale(x1, x_perem));
				matrix[i] = Vector2Add(matrix[i], Vector2Scale(y1, y_perem));
			}
		}

	}
	Vector2 y1 = { 0,1 };
	Vector2 e = { 1, 1 };
	Vector2 x1 = { 1, 0 };
	int x_perem = 10;
	int y_perem = 0;
	Color color;	
	Vector2 matrix[4];
	Vector2 matrix0[4];
	Vector2 matrix1[4];
	Vector2 matrix2[4];
	Vector2 matrix3[4];
	
	bool fall = false;
	int condition;
};
class TBlock : public Tetramino {
public:

	TBlock(){
		matrix[0] = { 1+10,1 };matrix[1] = {1+10,0 };matrix[2] = { 2+10, 0};matrix[3] = { 0+10, 0};//0-точка вращения //		
		matrix0[0] = { 1,1 }; matrix0[1] = { 0, 0 }; matrix0[2] = { 1, 0 }; matrix0[0] = { 2, 0 };
		matrix1[0] = { 1, 1 }; matrix1[1] = { 2, 0 }; matrix1[2] = { 2, 1 }; matrix1[3] = { 2,2 };
		matrix2[0] = { 1, 1 }; matrix2[1] = { 2, 2 }; matrix2[2] = { 1,2 }; matrix2[3] = { 0, 2 };
		matrix3[0] = { 1,1 }; matrix3[1] = { 0,2 }; matrix3[2] = { 0,1 }; matrix3[3] = { 0,0 };
		condition = 0;
		color = GREEN;
	}
	

};

class QuadroBlock : public Tetramino {
public:
	QuadroBlock() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 0 + 10, 1 };matrix[3] = { 1 + 10, 1 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 0,1 }; matrix0[3] = { 1, 1 };
		Equal_matrix(matrix1, matrix0); Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix0);
		color = YELLOW;
	}
};
class LongBlock : public Tetramino {
public:

	LongBlock() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 2 + 10, 0 };matrix[3] = { 3 + 10, 0 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 2, 0 }; matrix0[3] = { 3, 0 };
		matrix1[0] = { 1, 0 }; matrix1[1] = { 1,1 }; matrix1[2] = { 1,2 }; matrix1[3] = { 1, 3 };
		Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix1);
		condition = 0;
		color = GREEN;
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
		condition = 0;
		color = GREEN;
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
		condition = 0;
		color = GREEN;
	}

};
class ZBlockRight: public Tetramino {
public:

	ZBlockRight() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 1 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 2,1 };
		matrix1[0] = { 1, 1 }; matrix1[1] = { 2, 1 }; matrix1[2] = { 1,2}; matrix1[3] = { 2,0 };
		Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix1);
		condition = 0;
		color = GREEN;
	}
};
class ZBlockLeft : public Tetramino {
public:

	ZBlockLeft() {
		matrix[0] = { 0 + 10,1 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 0};
		matrix0[0] = { 0, 1}; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 2,0 };
		matrix1[0] = { 1, 0 }; matrix1[1] = { 1, 1 }; matrix1[2] = { 2, 1 }; matrix1[3] = { 2,2 };
		Equal_matrix(matrix2, matrix0); Equal_matrix(matrix3, matrix1);
		condition = 0;
		color = GREEN;
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
			DrawRectangle(play_matrix[i].x * cellSize, play_matrix[i].y * cellSize, cellSize, cellSize, _Color);
		}
	}
	void Otpechatok(Tetramino obj) {
		for (int i = 0; i<4; i++) {
			play_matrix[i + svobodn].x = obj.matrix[i].x;
			play_matrix[i + svobodn].y  = obj.matrix[i].y;
		}
		svobodn += 4;
	}
	int x_len = 22;
	int y_len = 32;
	int svobodn = 0; //Количество свободных ячеек
	Vector2 play_matrix[32*22];

	Color _Color = RED;
};
int main() {
	SetTraceLogLevel(LOG_NONE);
	InitWindow(600, 600, "Tetris");
	SetTargetFPS(60);
	QuadroBlock QuadroBlock;
	LongBlock LongBlock;
	GBlockRight GBlockRight;
	GBlockLeft GBlockLeft;
	ZBlockRight ZBlockRight;
	ZBlockLeft ZBlockLeft;
	TBlock TBlock;
	Tetramino Blocks[7] = { QuadroBlock, LongBlock, GBlockRight, GBlockLeft, ZBlockRight, ZBlockLeft, TBlock};
	playground playground;
	int border[22];
	for (int i = 0; i < 22; i++) {
		border[i] = 100;
	}
	int i = 0;
	while (!WindowShouldClose()) {
			
		BeginDrawing();
		
		ClearBackground(BLUE);
		
		playground.Draw();
			Blocks[i].Draw();
		
			if (updTriggered(0.15)) {
				Blocks[i].Update();
				Blocks[i].is_fall(border);
				if (IsKeyDown(KEY_D)) {
					Blocks[i].Move(true);
				}
				else if (IsKeyDown(KEY_A)) {
					Blocks[i].Move(false);
				}
			}
			if (IsKeyPressed(KEY_RIGHT)) {
				Blocks[i].Rotate(true);
			}
			else if (IsKeyPressed(KEY_LEFT)) {
				Blocks[i].Rotate(false);
			}
			if (Blocks[i].fall) {
				Blocks[i].y_perem = 0;
			
				playground.Otpechatok(Blocks[i]);
				if (i > 5) { i = 0; }
				else { i += 1; }
			}
		
		



		EndDrawing();
	}

}
