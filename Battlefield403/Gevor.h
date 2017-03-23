#ifndef GEVOR_H
#define GEVOR_H
#include "iplayer.h"
#include <time.h>
#include <stdlib.h>
#include "shotresult.h"
class GEVORG_PLAYER: public IPlayer
{
    void ProcessShotResult(ShotResult res, Coordinate coord) override{}
    void ProcessRoundResult(bool youWin) override{}
    QString PlayerName()
    {
        return "Gevorg";
    }
    virtual std::vector<Ship> PlaceShips()
    {
        std::vector<Ship> v;
        v.push_back(Ship(Coordinate(0,0),Ship::Horizontal,4));
        v.push_back(Ship(Coordinate(0,7),Ship::Horizontal,3));
        v.push_back(Ship(Coordinate(7,0),Ship::Horizontal,3));
        v.push_back(Ship(Coordinate(3,0),Ship::Horizontal,2));
        v.push_back(Ship(Coordinate(7,8),Ship::Horizontal,2));
        v.push_back(Ship(Coordinate(9,4),Ship::Horizontal,2));
        v.push_back(Ship(Coordinate(4,4),Ship::Vertical,1));
        v.push_back(Ship(Coordinate(3,7),Ship::Vertical,1));
        v.push_back(Ship(Coordinate(6,4),Ship::Vertical,1));
        v.push_back(Ship(Coordinate(5,8),Ship::Vertical,1));
        return v;
    }
    virtual Coordinate Shoot()
    {
        Coordinate fire (rand()% Settings::boardHeight,
                          rand()% Settings::boardWidth);
        return fire;
    }
};
#endif // GEVOR_H
