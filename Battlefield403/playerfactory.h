#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H
#include <QString>
#include "IPlayer.h"

class PlayerFactory
{
public:
    PlayerFactory();
    IPlayer* CreatePlayer(const QString& str);
};

#endif // PLAYERFACTORY_H
