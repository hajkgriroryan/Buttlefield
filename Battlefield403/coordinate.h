#ifndef COORDINATE_H
#define COORDINATE_H
#include "settings.h"
#include <stdexcept>

class Coordinate
{
public:
    Coordinate(int Row, int Column)
        :m_row(Row), m_column(Column)
    {
        if(Row < 0 || Row > Settings::boardWidth
           || Column < 0 || Column > Settings::boardHeight)
        {
             throw std::out_of_range("Incorrect coordinates");
        }
    }

    int row () const
    {
        return m_row;
    }

    int column () const
    {
        return m_column;
    }


    bool operator == (const Coordinate & c) const
    {
        return c.row()==this->row() && c.column()==this->column();
    }

    bool operator < (const Coordinate & c) const
    {
        if(this->row() == c.row())
            return this->column() < c.column();
        return this->row() < c.row();
    }

private:
    int m_row;
    int m_column;
};

#endif // COORDINATE_H
