#ifndef PLAYERMARY_H
#define PLAYERMARY_H
#include "iplayer.h"
#include "shotresult.h"
#include "coordinate.h"

class PlayerMary: public IPlayer
{
public:
    PlayerMary();
    std::vector<Ship> PlaceShips() override;
    Coordinate Shoot() override;
    void ProcessShotResult(ShotResult res, Coordinate coord) override;
    void ProcessRoundResult(bool youWin) override;
    QString PlayerName()
    {
        return "Mary";
    }
};

#endif // PLAYERMARY_H


