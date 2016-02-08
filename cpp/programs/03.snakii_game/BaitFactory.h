#ifndef _BAIT_FACTORY_H_
#define _BAIT_FACTORY_H_

#include "Bait.h"

class BaitFactory
{
    public:
        explicit BaitFactory()
        {}
        ~BaitFactory()
        {}

        Bait * createBait(int num) {
            int select = num % 4;
            switch(select) {
                case 0:
                    return new SymbolBait();
                case 1:
                    return new ColorBait();
                case 2:
                    return new ExtendBait();
                default:
                    return new ShrinkBait();
            }
            return nullptr;
        }
};
#endif //  _BAIT_FACTORY_H_


