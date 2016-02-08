#ifndef _DERIVED_BAITS_H_
#define _DERIVED_BAITS_H_

#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <algorithm>

#include "Bait.h"
#include "Snake.h"

class SymbolBait : public Bait
{
    public:
        SymbolBait (int inX=0, int inY=0, int inColor=0)
            : Bait(inX, inY, inColor, 'S')
        {}
        virtual ~SymbolBait()
        {}

        // Derived classes must implement this
        virtual void modify(Snake &snake) {
            snake.setSymb(rand()% 12 + 33);
        }
};

class ColorBait : public Bait
{
    public:
        ColorBait (int inX=0, int inY=0, int inColor=0)
            : Bait(inX, inY, inColor, 'C')
        {}
        virtual ~ColorBait()
        {}

        // Derived classes must implement this
        virtual void modify(Snake &snake) {
            snake.setColorID(colorID);
        }
};

class ExtendBait : public Bait
{
    public:
        ExtendBait (int inX=0, int inY=0, int inColor=0)
            : Bait(inX, inY, inColor, 'X')
        {}
        virtual ~ExtendBait()
        {}

        // Derived classes must implement this
        virtual void modify(Snake &snake) {
            snake.resizeSnake(5);
        }
};

class ShrinkBait : public Bait
{
    public:
        ShrinkBait (int inX=0, int inY=0, int inColor=0)
            : Bait(inX, inY, inColor, 'D')
        {}
        virtual ~ShrinkBait()
        {}

        // Derived classes must implement this
        virtual void modify(Snake &snake) {
            snake.resizeSnake(-1);
        }
};
#endif // _DERIVED_BAITS_H_
