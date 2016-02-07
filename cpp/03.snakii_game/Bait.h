#ifndef _BAIT_H_
#define _BAIT_H_

#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <algorithm>

using namespace std;

class Snake;
class Bait
{
    public:
        Bait (int inX=0, int inY=0, int inColor=0, char inSymb='@')
            :x(inX), y(inY), colorID(inColor), symb(inSymb)
        {}
        virtual ~Bait()
        {}

        // Derived classes must implement this
        virtual void modify(Snake &snake) = 0;

        bool operator<(const Bait &bait) const{
            if(x < bait.x)
                return(true);
            return(false);
        }

        int x,y;
        int colorID;
        char symb;
};
#endif // _BAIT_H_
