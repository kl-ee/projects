#ifndef _DISPLAY_HANDLER_
#define _DISPLAY_HANDLER_

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class Pixel {
    public:
        Pixel(int row, int col, char c);
        void setPixel(int row, int col, char c);
        int getRow()        { return(m_row); }
        int getCol()        { return(m_col); }
        int getChar()       { return(m_char); }

    private:
        int m_row;
        int m_col;
        char m_char;
};

class DisplayHandler {
    public:
        DisplayHandler();
        void displayImage();
        bool addPiece();

    private:
        int m_rows;
        int m_cols;
        std::vector<std::vector<char> > m_image;
        std::vector<Pixel> m_parts;
};

#endif
