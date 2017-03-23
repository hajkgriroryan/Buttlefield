#ifndef SHIP_H
#define SHIP_H
#include "coordinate.h"


class Ship
{
public:
    enum Orientation
    {
        Horizontal,
        Vertical,
    };

    Ship(const Coordinate& topLeft,
         const Orientation& orientation,
         int size);



    Coordinate topLeft() const
    {
        return m_TopLeft;
    }

    Orientation orientation () const
    {
        return m_Orientation;
    }

    int size () const
    {
        return m_Size;
    }
    bool check_ship(int Row, int Column) const;
    bool is_part_of_ship(Coordinate c) const;
    bool is_neighbour_of_ship(Coordinate c) const;
    void decrement_live_cells()
    {
        if(m_live_cell_count != 0)
            --m_live_cell_count;
    }

    bool is_dead() const
    {
        return m_live_cell_count == 0;
    }


private:
    Coordinate m_TopLeft;
    Orientation m_Orientation;
    int m_Size;
    int m_live_cell_count;

};




#endif // SHIP_H
