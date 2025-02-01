#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

void initialize_grid(int grid[HEIGHT][WIDTH]) {
    // Red glider
    grid[1][1] = 1;
    grid[2][2] = 1;
    grid[2][3] = 1;
    grid[1][3] = 1;
    grid[0][3] = 1;

    // Blue glider
    grid[15][15] = 2;
    grid[16][16] = 2;
    grid[16][17] = 2;
    grid[15][17] = 2;
    grid[14][17] = 2;
}

int count_neighbors(int grid[HEIGHT][WIDTH], int x, int y, int population) {
    int count = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            
            int new_x = (x + i + WIDTH) % WIDTH;
            int new_y = (y + j + HEIGHT) % HEIGHT;
            
            if(grid[new_y][new_x] == population) count++;
        }
    }
    return count;
}

void next_generation(int grid[HEIGHT][WIDTH], int new_grid[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            int red_neighbors = count_neighbors(grid, x, y, 1);
            int blue_neighbors = count_neighbors(grid, x, y, 2);
            
            if(grid[y][x] == 0) {  // Dead cell
                if(red_neighbors == 3) new_grid[y][x] = 1;
                else if(blue_neighbors == 3) new_grid[y][x] = 2;
                else new_grid[y][x] = 0;
            }
            else if(grid[y][x] == 1) {  // Red cell
                if(red_neighbors < 2 || red_neighbors > 3) new_grid[y][x] = 0;
                else new_grid[y][x] = 1;
            }
            else if(grid[y][x] == 2) {  // Blue cell
                if(blue_neighbors < 2 || blue_neighbors > 3) new_grid[y][x] = 0;
                else new_grid[y][x] = 2;
            }
        }
    }
}

void display_grid(int grid[HEIGHT][WIDTH]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");  // Clear screen for Windows
    
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            if(grid[y][x] == 0) {
                printf(".");
            }
            else if(grid[y][x] == 1) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("O");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("O");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
        }
        printf("\n");
    }
}

void copy_grid(int src[HEIGHT][WIDTH], int dst[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            dst[y][x] = src[y][x];
        }
    }
}

int main() {
    int grid[HEIGHT][WIDTH] = {0};
    int new_grid[HEIGHT][WIDTH] = {0};
    
    initialize_grid(grid);
    
    while(1) {
        display_grid(grid);
        next_generation(grid, new_grid);
        copy_grid(new_grid, grid);
        Sleep(100);  // Windows sleep function (milliseconds)
    }
    
    return 0;
}