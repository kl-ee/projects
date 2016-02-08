#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <ncurses.h>

#include "Bait.h"
#include "DerivedBaits.h"
#include "BaitFactory.h"
#include "Snake.h"

#define test

using namespace std;

void color_init();
int occupied(int x, int y, deque<Point> &snakeSeg);
void insertBait(set<Bait *> &bait, int rows, int columns, deque<Point> snakeSeg);
void clearBait(set<Bait *> &bait);
int main()
{
    WINDOW *win;
    win = initscr();
    int delay = 50;
    timeout(delay);
    noecho();
    start_color();
    color_init();
    curs_set(0);

    int numRows = 30, numColumns = 50;
    Snake snakii(numRows, numColumns, '*');
    set<Bait *> bait;
    deque<Point> snakeSeg;
    DIRECTIONS dir;
    //----------
    char ch, lastch = 'd';
    //TODO find the keys for up/down/left/right arrows (wasd)

    while ((ch = getch()) != 'q') {
        if (ch != -1 && (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')) {
            lastch = ch;
        }

        // Handle pause(p) and resume(r)
        if (ch == 'p')
            while( (ch = getch()) != 'r') {
            }

        // Handle speed incrase(+) and decrease(-)
        if (ch == '-') {
            delay += 10;
            timeout(delay);
        } else if (ch == '+') {
            if(delay -10 > 0)
                delay -= 10;
            timeout(delay);
        }

        // Handle reset of baits(b)
        if (ch == 'b') {
            clearBait(bait);
            insertBait(bait, numRows, numColumns, snakeSeg);
        }

        switch(lastch) {
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            default:
                break;
        }

        clear();
        if (snakii.move(bait, dir) == 0)
            break;
        snakeSeg = snakii.getSnake();
        attron(COLOR_PAIR(snakii.getColorID()));
        for (int i = 0; i < snakeSeg.size(); i++) {
            mvaddch(snakeSeg[i].y, snakeSeg[i].x, snakii.getSymb());
        }
        attroff(COLOR_PAIR(snakii.getColorID()));
        for (auto itr = bait.begin(); itr != bait.end(); ++itr) {
            attron(COLOR_PAIR((*itr)->colorID));
            mvaddch((*itr)->y, (*itr)->x, (*itr)->symb);
            attroff(COLOR_PAIR((*itr)->colorID));
        }
        for (int i = 0; i < numColumns +1; ++i)
            mvaddch(numRows + 1, i, '-');
        for (int i = 0; i < numRows + 1; ++i)
            mvaddch(i, numColumns + 1, '|');
        insertBait(bait, numRows, numColumns, snakeSeg);
        refresh();
    }

    delwin(win);
    endwin();

    printf("GAME OVER\n");

    clearBait(bait);

    return(0);
}

void color_init()
{
    if(has_colors() && COLOR_PAIRS >= 7) {
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }
    return;
}

int occupied(int x, int y, const deque<Point> &snakeSeg, const set<Bait *> &bait)
{
    for(auto itr=snakeSeg.begin(); itr != snakeSeg.end(); ++itr) {
        if( x == itr->x && y == itr->y) {
            return(1);
        }
    }
    for(auto itr=bait.begin(); itr != bait.end(); ++itr)  {
        if( x == (*itr)->x && y == (*itr)->y) {
            return(1);
        }
    }
    return(0);
}

void insertBait(set<Bait *> &bait, int rows, int columns, deque<Point> snakeSeg) 
{
    static BaitFactory bFactory;
    while (bait.size() < 5) {
        Bait * newBait = bFactory.createBait(rand());
        do {
            newBait->x = rand() % columns;
            newBait->y = rand() % rows;
            newBait->colorID = rand()%6+1;
        } while(occupied(newBait->x, newBait->y, snakeSeg, bait));
        bait.insert(newBait);
    }
    return;
}

void clearBait(set<Bait *> &bait)
{
    for (auto itr = bait.begin(); itr != bait.end(); ++itr) {
        delete *itr;
    }
    bait.clear();
}

