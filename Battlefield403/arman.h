#ifndef ARMAN_H
#define ARMAN_H
#include "IPlayer.h"
#include "shotresult.h"
std::vector<Coordinate> CreateGrid()
{
    std::vector<Coordinate> grid;
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
            grid.push_back(Coordinate(i,j));
    return grid;
}
std::vector<Coordinate> a = CreateGrid();
class Arman : public IPlayer
{
public:

    void ProcessShotResult(ShotResult res, Coordinate coord) override{}
    void ProcessRoundResult(bool youWin) override{}
    QString PlayerName() override
    {
        return "Arman";
    }
    std::vector<Ship> PlaceShips() override
    {
        std::vector<Ship> v;
        v.push_back(Ship(Coordinate(9,6),Ship::Horizontal,4));
        v.push_back(Ship(Coordinate(0,8),Ship::Vertical,3));
        v.push_back(Ship(Coordinate(2,5),Ship::Vertical,3));
        v.push_back(Ship(Coordinate(2,2),Ship::Horizontal,2));
        v.push_back(Ship(Coordinate(1,0),Ship::Vertical,2));
        v.push_back(Ship(Coordinate(5,3),Ship::Vertical,2));
        v.push_back(Ship(Coordinate(0,2),Ship::Horizontal,1));
        v.push_back(Ship(Coordinate(4,0),Ship::Horizontal,1));
        v.push_back(Ship(Coordinate(8,0),Ship::Horizontal,1));
        v.push_back(Ship(Coordinate(9,2),Ship::Horizontal,1));
        return v;
    }

    Coordinate Shoot() override
    {
        int index = rand()%(a.size());
        return a[index];
    }

};

#endif // ARMAN_H
