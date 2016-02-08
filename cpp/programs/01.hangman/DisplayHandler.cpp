#include "DisplayHandler.h"

// public
Pixel::Pixel(int row, int col, char c)
{
    m_row = row;
    m_col = col;
    m_char = c;
}

// public
void
Pixel::setPixel(int row, int col, char c)
{
    m_row = row;
    m_col = col;
    m_char = c;
}

// public
DisplayHandler::DisplayHandler()
{
    m_rows = 6;
    m_cols = 6;
    
    // Initialize image
    std::vector<char> temp(m_cols, ' ');
    std::vector<std::vector<char> > temp2(m_rows, temp);
    m_image = temp2;

    // Set stand
    m_image[0][2] = '-';
    m_image[1][1] = '|';
    m_image[2][1] = '|';
    m_image[3][1] = '|';
    m_image[4][1] = '|';
    m_image[5][0] = '-';
    m_image[5][1] = '-';
    m_image[5][2] = '-';

    // Set pieces
    m_parts.emplace_back(Pixel(3,5,'\\'));
    m_parts.emplace_back(Pixel(3,3,'/'));
    m_parts.emplace_back(Pixel(2,5,'\\'));
    m_parts.emplace_back(Pixel(2,3,'/'));
    m_parts.emplace_back(Pixel(2,4,'|'));
    m_parts.emplace_back(Pixel(1,4,'o'));
}

// public
void
DisplayHandler::displayImage()
{
    for(auto vec : m_image) {
        for(auto c : vec) {
            printf("%c", c);
        }
        printf("\n");
    }
}

// public
bool
DisplayHandler::addPiece()
{
    Pixel p = m_parts.back();
    m_parts.pop_back();

    m_image[p.getRow()][p.getCol()] = p.getChar();

    if(m_parts.empty()) {
        return(false);
    }

    return(true);
}
