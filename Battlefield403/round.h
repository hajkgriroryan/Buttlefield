#ifndef ROUND_H
#define ROUND_H

#include <cassert>
#include "IPlayer.h"
class Round
{
public:
    Round(IPlayer* pl1, IPlayer* pl2);
    IPlayer* play();

private:
    IPlayer* players[2];
    bool check_ships(const std::vector<Ship>& ships) const;
};

#endif // ROUND_H
