#include "ship.h"
#include "settings.h"
#include <stdexcept>

Ship::Ship(const Coordinate& topLeft,
     const Orientation& orientation,
     int size)
    :m_TopLeft(topLeft),
     m_Orientation(orientation),
     m_Size(size),
     m_live_cell_count(size)
{
    if((orientation == Vertical
       && topLeft.row() + size - 1 >= Settings::boardWidth)
       || (orientation == Horizontal
       && topLeft.column() + size - 1 >= Settings::boardHeight))
    {
        throw std::out_of_range("Ship out of board bounds");

    }
    if(size < 1 || size > Settings::maxShipSize )
    {
        throw std::logic_error("Incorrect Ship size");
    }


}

bool Ship::is_part_of_ship(Coordinate c) const //Edgar
{
    for (int i=0;i<m_Size;++i)
        {
            if (m_Orientation==Horizontal && Coordinate(m_TopLeft.row(),m_TopLeft.column()+i)==c)
            {
                return true;
            }
            if (m_Orientation==Vertical && Coordinate(m_TopLeft.row()+i,m_TopLeft.column())==c )
            {
                return true;
            }
        }
        return false;

}


bool Ship::check_ship(int Row, int Column) const
{
    if(Row < 0 || Row > Settings::boardWidth || Column < 0 || Column > Settings::boardHeight)
    {
        return false;
    }
    return true;
}

bool Ship::is_neighbour_of_ship(Coordinate c) const
{
    int topleft_r, topleft_c, bottomright_r, bottomright_c;
    if(m_Orientation == Vertical)
    {
        topleft_r = m_TopLeft.row() - 1;
        if(topleft_r < 0)
            topleft_r = 0;
        topleft_c = m_TopLeft.column() - 1;
        if(topleft_c < 0)
            topleft_c = 0;
        bottomright_r = m_TopLeft.row() + m_Size;
        if(bottomright_r >= Settings::boardHeight)
            bottomright_r = Settings::boardHeight - 1;

        bottomright_c = m_TopLeft.column() + 1;
        if(bottomright_c >= Settings::boardWidth)
            bottomright_c = Settings::boardWidth - 1;
    }
    else
    {
        topleft_r = m_TopLeft.row() - 1;
        if(topleft_r < 0)
            topleft_r = 0;
        topleft_c = m_TopLeft.column() - 1;
        if(topleft_c < 0)
            topleft_c = 0;
        bottomright_r = m_TopLeft.row() + 1;
        if(bottomright_r >= Settings::boardHeight)
            bottomright_r = Settings::boardHeight - 1;

        bottomright_c = m_TopLeft.column() + m_Size;
        if(bottomright_c >= Settings::boardWidth)
            bottomright_c = Settings::boardWidth - 1;
    }

    for(int i = topleft_r; i <= bottomright_r; ++i)
        for(int j = topleft_c; j <= bottomright_c; ++j)
           if(Coordinate(i, j) == c)
                return true;

    return false;
}










