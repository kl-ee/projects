#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdio.h>
#include <math.h>
#include <deque>
#include <set>
#include <algorithm>

#include "Bait.h"

using namespace std;

enum DIRECTIONS  {LEFT, RIGHT, UP, DOWN, NODIR};

class Point
{
    public:
        int x,y;

        bool operator==(Point& point) {
            if(point.x == x && point.y == y)
                return true;
            return false;
        }
};

class Snake
{
    public:
        Snake(int rows, int columns, char inSymb)
            : maxRows(rows), maxColumns(columns), dir(RIGHT), colorID(1),
              symb(inSymb)
        {
            Point startPoint;
            startPoint.x = 0;
            startPoint.y = 0;
            segments.push_front(startPoint);
        }

        int move(set<Bait *> &bait, DIRECTIONS newDir = NODIR) {

            if( (dir == RIGHT && newDir == LEFT) || (dir == LEFT && newDir == RIGHT) ||
                (dir == DOWN && newDir == UP) || (dir == UP && newDir == DOWN) ||
                (newDir == NODIR)) {
                newDir = dir;
            }

            Point newFront;
            newFront.x = segments.front().x;
            newFront.y = segments.front().y;
            switch(newDir) {
               case LEFT:
                   (newFront.x)--;
                   break;
               case RIGHT:
                   (newFront.x)++;
                   break;
               case UP:
                   (newFront.y)--;
                   break;
               case DOWN:
                   (newFront.y)++;
                   break;
               default:
                   break;
            }
            segments.push_front(newFront);
            dir = newDir;

            if(!headbutt(bait)) {
                segments.pop_back();
            }

            stayWithinGrid();
            return(!intersect());
        }

        int headbutt(set<Bait *> &bait) {
            for(auto itr = bait.begin(); itr != bait.end(); ++itr) {
                if(segments.front().x == (*itr)->x && segments.front().y == (*itr)->y) {
                    (*itr)->modify(*this);
                    bait.erase(itr);
                    return(1);
                }
            }
            return(0);
        }

        void resizeSnake(int delta) {
            if (delta == 0) {
                return;
            } else if (delta > 0) {
                for (auto i = 0; i < delta; ++i) {
                    segments.emplace_back(segments.back());
                }
            } else {
                for (auto i = 0; i < -delta + 1; ++i) {
                    if (segments.size() == 1) {
                        return;
                    }
                    segments.pop_back();
                }
            }
            return;
        }

        const deque<Point>& getSnake() const {
            return(segments);
        }

        int getColorID() const {
            return colorID;
        }
        void setColorID(int newColorID) {
            colorID = newColorID;
        }

        char getSymb() const {
            return symb;
        }
        void setSymb(char newSymb) {
            symb = newSymb;
        }

    private:
        int intersect() {
                for(int j = 1; j < segments.size(); j++) {
                    if(segments[0] == segments[j]) {
                        return(1);
                    }
            }
            return(0);
        }

        void stayWithinGrid(){
            for(int i = 0; i < segments.size(); i++) {
                while(segments[i].x >= maxColumns || segments[i].x < 0 ||
                      segments[i].y >= maxRows || segments[i].y < 0) {
                    if(segments[i].x >= maxColumns)
                        segments[i].x = segments[i].x % maxColumns;
                    else if(segments[i].x < 0)
                        segments[i].x = segments[i].x + maxColumns;
                    if(segments[i].y >= maxRows)
                        segments[i].y = segments[i].y % maxRows;
                    else if(segments[i].y < 0)
                        segments[i].y = segments[i].y + maxRows;
                }
            }

        }

        deque<Point> segments;
        int colorID;
        char symb;
        int maxRows, maxColumns; //Row:y, Column:x
        DIRECTIONS dir; //
};
#endif // _SNAKE_H_
