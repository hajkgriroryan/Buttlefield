#ifndef IPLAYER_H
#define IPLAYER_H
#include <vector>
#include <QString>
#include "ship.h"
#include "coordinate.h"
#include "ShotResult.h"

class IPlayer
{
public:
    virtual ~IPlayer()
    {
    }
    virtual void PrepareForNewRound()
    {
    }
    virtual std::vector<Ship> PlaceShips() = 0;
    virtual Coordinate Shoot() = 0;
    virtual void ProcessShotResult(ShotResult res, Coordinate coord) = 0;
    virtual void ProcessRoundResult(bool youWin) = 0;
    virtual QString PlayerName() = 0;
};

#endif // IPLAYER_H
