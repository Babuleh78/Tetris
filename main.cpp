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
	void Update() {
		if (dvigat) {
			int a = max(matrix[0].y, matrix[1].y), b = (matrix[2].y, matrix[3].y);
			a = max(a, b);
			if (a != 19) {
				for (int i = 0; i < 4; i++) {
					matrix[i] = Vector2Add(matrix[i], y1);
				}
				y_perem += 1;
			}
			else {
				dvigat = false;
			}
		}
	}
	void Draw() {
		for (int i = 0; i < 4; i++) {
			int x = matrix[i].x; int y = matrix[i].y;

			DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, color);
		}

	}
	void Move(bool flag) { //flag == true вправо иначе влево
		if (dvigat) {
			for (int i = 0; i < 4; i++) {
				matrix[i] = (flag ? (Vector2Add(matrix[i], x1)) : Vector2Add(matrix[i], Vector2Scale(x1, -1)));

			}
			if (flag) { x_perem += 1; }
			else { x_perem -= 1; }
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
	bool dvigat = true;
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
	
	void Rotate(bool flag) {//flag == true по часовой
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

};

class QuadroBlock : public Tetramino {
public:
	QuadroBlock() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 0 + 10, 1 };matrix[3] = { 1 + 10, 1 };
		color = YELLOW;
	}

	void Rotate(bool flag) {//flag == true по часовой
		return;

	}
};
class LongBlock : public Tetramino {
public:

	LongBlock() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 2 + 10, 0 };matrix[3] = { 3 + 10, 0 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 2, 0 }; matrix0[3] = { 3, 0 };
		matrix1[0] = { 1, 0 }; matrix1[1] = { 1,1 }; matrix1[2] = { 1,2 }; matrix1[3] = { 1, 3 };
		condition = 0;
		color = GREEN;
	}

	void Rotate(bool flag) {//flag == true по часовой
		condition = (condition == 0 ? 1 : 0);
		if (!condition) {
			Equal_matrix(matrix, matrix0);
		}
		else {
			Equal_matrix(matrix, matrix1);
		}
		for (int i = 0; i < 4; i++) {
			matrix[i] = Vector2Add(matrix[i], Vector2Scale(x1, x_perem));
			matrix[i] = Vector2Add(matrix[i], Vector2Scale(y1, y_perem));
		}

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

	void Rotate(bool flag) {//flag == true по часовой
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

	void Rotate(bool flag) {//flag == true по часовой
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

};
class ZBlockRight: public Tetramino {
public:

	ZBlockRight() {
		matrix[0] = { 0 + 10,0 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 1 };
		matrix0[0] = { 0, 0 }; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 2,1 };
		matrix1[0] = { 1, 1 }; matrix1[1] = { 2, 1 }; matrix1[2] = { 1,2}; matrix1[3] = { 2,0 };
		
		condition = 0;
		color = GREEN;
	}

	void Rotate(bool flag) {//flag == true по часовой
		condition = (condition == 0 ? 1 : 0);
		if (!condition) {
			Equal_matrix(matrix, matrix0);
		}
		else {
			Equal_matrix(matrix, matrix1);
		}
		for (int i = 0; i < 4; i++) {
			matrix[i] = Vector2Add(matrix[i], Vector2Scale(x1, x_perem));
			matrix[i] = Vector2Add(matrix[i], Vector2Scale(y1, y_perem));
		}

	}
};
class ZBlockLeft : public Tetramino {
public:

	ZBlockLeft() {
		matrix[0] = { 0 + 10,1 };matrix[1] = { 1 + 10,0 };matrix[2] = { 1 + 10, 1 };matrix[3] = { 2 + 10, 0};
		matrix0[0] = { 0, 1}; matrix0[1] = { 1, 0 }; matrix0[2] = { 1,1 }; matrix0[3] = { 2,0 };
		matrix1[0] = { 1, 0 }; matrix1[1] = { 1, 1 }; matrix1[2] = { 2, 1 }; matrix1[3] = { 2,2 };

		condition = 0;
		color = GREEN;
	}

	void Rotate(bool flag) {//flag == true по часовой
		condition = (condition == 0 ? 1 : 0);
		if (!condition) {
			Equal_matrix(matrix, matrix0);
		}
		else {
			Equal_matrix(matrix, matrix1);
		}
		for (int i = 0; i < 4; i++) {
			matrix[i] = Vector2Add(matrix[i], Vector2Scale(x1, x_perem));
			matrix[i] = Vector2Add(matrix[i], Vector2Scale(y1, y_perem));
		}

	}

};
int main() {
	SetTraceLogLevel(LOG_NONE);
	InitWindow(800, 600, "Tetris");
	SetTargetFPS(60);
	//LongBlock a;
	//QuadroBlock a;
	//TBlock a;
	//GBlockRight a;
	//GBlockLeft a;
	ZBlockLeft a;
	//ZBlockRight a;
	while (!WindowShouldClose()) {
		BeginDrawing();
		a.Draw();
		
		ClearBackground(BLUE);
		if (updTriggered(0.2)) {
			a.Update();
			if (IsKeyDown(KEY_D)) {
				a.Move(true);
			}
			else if (IsKeyDown(KEY_A)) {
				a.Move(false);
			}
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			a.Rotate(true);
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			a.Rotate(false);
		}
		/*else if (IsKeyDown(KEY_D)) {
			a.Move(true);
		}
		else if (IsKeyDown(KEY_A)) {
			a.Move(false);
		}*/
		EndDrawing();
	}

}
