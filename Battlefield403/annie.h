#ifndef ANNIE
#define ANNIE
#include <QVector>
#include "IPlayer.h"
#include "settings.h"
#include "coordinate.h"
#include "shotresult.h"



class Annie:public IPlayer
{
 public:
    QString PlayerName() override
    {
        return "Annie";
    }

    void PrepareForNewRound() override
    {
        C.clear();
        for(int i = 0; i < Settings::boardHeight; ++i)
            for(int j = 0; j < Settings::boardWidth; ++j)
                C.push_back(Coordinate(i, j));
    }
    void ProcessShotResult(ShotResult res, Coordinate coord) override
    {
        if(res == ShotResult::AlreadyShot && coord == Coordinate (0,1))
        {

        }

    }
    void ProcessRoundResult(bool youWin) override
    {

    }

    Coordinate Shoot() override
    {
        int i = rand()%(C.size());
        Coordinate Coord = C[i];
        std::swap(C[i], C.back());
        C.pop_back();
        return Coord;
    }

    std::vector<Ship> PlaceShips() override
    {
        std::vector<Ship> v;
        v.push_back(Ship(Coordinate(1,1),Ship::Vertical,4));
        v.push_back(Ship(Coordinate(9,7),Ship::Horizontal,3));
        v.push_back(Ship(Coordinate(0,9),Ship::Vertical,3));
        v.push_back(Ship(Coordinate(2,3),Ship::Horizontal,2));
        v.push_back(Ship(Coordinate(4,5),Ship::Horizontal,2));
        v.push_back(Ship(Coordinate(7,3),Ship::Vertical,2));
        v.push_back(Ship(Coordinate(5,3),Ship::Horizontal,1));
        v.push_back(Ship(Coordinate(8,0),Ship::Horizontal,1));
        v.push_back(Ship(Coordinate(7,6),Ship::Horizontal,1));
        v.push_back(Ship(Coordinate(2,7),Ship::Horizontal,1));
        return v;
    }
private:
    std::vector<Coordinate> C;



};

#endif // ANNIE
