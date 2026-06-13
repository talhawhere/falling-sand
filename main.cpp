#include "raylib.h"
#include <vector>
using namespace std;

const int COLS = 200, ROWS = 150, SCALE = 4;

enum class Element {Empty,
                    Sand
                    };

struct Cell {
    Element type = Element::Empty;
    Color color = BLACK;
};


vector<Cell> grid(COLS * ROWS);

int idx(int x, int y){
    return y * COLS + x;
}

bool inBounds(int x, int y){
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}
bool isEmpty(int x, int y){
    return inBounds(x, y) && grid[idx(x, y)].type == Element::Empty;
}


void update(){
    for (int y = ROWS - 1; y >= 0; y--){
        for (int x = 0; x < COLS; x++){
            if(grid[idx(x, y)].type != Element::Sand) continue;

            if (isEmpty(x, y + 1)){
                swap(grid[idx(x, y)], grid[idx(x, y + 1)]);
            }
            else {
                int dir = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                if (isEmpty(x + dir, y + 1)){
                    swap(grid[idx(x, y)], grid[idx(x + dir, y + 1)]);
                }
                else if (isEmpty(x - dir, y + 1)){
                    swap(grid[idx(x, y)], grid[idx(x - dir, y + 1)]);
                }
            }
        }
    }
}



//run cmd 
//clang++ main.cpp -o sandbox $(pkg-config --cflags --libs raylib) -framework OpenGL -framework Cocoa -framework IOKit && ./sandbox


int main(){
    InitWindow(800, 600, "Sand Sandbox");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            int mx = GetMouseX() / SCALE;
            int my = GetMouseY() / SCALE;

            if (isEmpty(mx, my)){
                grid[idx(mx, my)].type = Element :: Sand;
                grid[idx(mx, my)].color = (Color){220, 190, 90, 255};
            }
        }

        update();

        BeginDrawing();

        ClearBackground(BLACK);
        
        for(int y = 0; y < ROWS; y++)
            for(int x = 0; x < COLS; x++)
                if(grid [idx(x,y)].type != Element::Empty)
                    DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, grid[idx(x, y)].color);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}