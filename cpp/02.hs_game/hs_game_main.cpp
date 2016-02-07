#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#define GRID_SEG_SIZE  5
using namespace std;

class Point
{
    public:
        Point(int row, int col) 
         : m_row(row), m_col(col)
        {}
        int getRow()        { return m_row; }
        int getCol()        { return m_col; }
        int setRow(int row) { m_row = row; }
        int setCol(int col) { m_col = col; }
    private:
        int m_row, m_col;
};

void clearScreen() 
{
    for(int i = 0; i < 100; ++i)
        printf("\n");
}

void displayGrid(std::vector<std::vector<char> > grid, Point user, Point enemy)
{
    clearScreen();
    grid[user.getRow()*GRID_SEG_SIZE + 2][user.getCol()*GRID_SEG_SIZE + 2] = 'o';
    grid[enemy.getRow()*GRID_SEG_SIZE + 3][enemy.getCol()*GRID_SEG_SIZE + 3] = '*';
    for(auto itr : grid) {
        for(auto c : itr) {
            printf(" %c ", c);
        }
        printf("\n");
    }
}

int main() 
{
    char move = 'W';
    int gridLength = 0;
    Point user(0,0), enemy(1,1);

    // Prompt for size of grid
    cout << "What is the size of the grid you want to play in (>= 2)? ";
    cin >> gridLength;
    cin.ignore(1000000, '\n');

    // Set up random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,gridLength -1);

    // Build the grid skeleton
    std::vector<char> tempVec (gridLength*GRID_SEG_SIZE + 1, ' ');
    std::vector<std::vector<char> > grid(gridLength*GRID_SEG_SIZE +1, tempVec);
    for (int i = 0; i <= gridLength*GRID_SEG_SIZE; ++i) {
        for (int j = 0; j <= gridLength*GRID_SEG_SIZE; ++j) {
            if ((i % GRID_SEG_SIZE == 0 || i == grid.size() -1) ||
                (j % GRID_SEG_SIZE == 0 || j == grid[i].size() -1) ) {
                grid[i][j] = 'x';
            }
        }
    }
    displayGrid(grid, user, enemy);
    bool continueGame = true;
    while (continueGame) {
        cout << "Please insert move (W,A,S,D): ";
        move = getc(stdin);
        cin.ignore(1000000, '\n');

        switch (move) {
            case 'w':
                user.setRow((user.getRow() + gridLength - 1) % gridLength);
                break;
            case 's':
                user.setRow((user.getRow() + 1) % gridLength);
                break;
            case 'a':
                user.setCol((user.getCol() + gridLength - 1) % gridLength);
                break;
            case 'd':
                user.setCol((user.getCol() + 1) % gridLength);
                break;
            default:
                printf("You dun messed up. Try again.\n");
        }
        enemy.setRow(dis(gen));
        enemy.setCol(dis(gen));
        if (enemy.getRow() == user.getRow() && enemy.getCol() == user.getCol()) {
            continueGame = false;
        }
        displayGrid(grid, user, enemy);
    }
    printf("YOU GOT CAUGHT!\n");
}
