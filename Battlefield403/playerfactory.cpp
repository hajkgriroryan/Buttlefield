#include "playerfactory.h"
#include "playermary.h"
#include "Hayk.h"
#include "Gevor.h"
#include "annie.h"
#include "arman.h"
PlayerFactory::PlayerFactory()
{
}

IPlayer* PlayerFactory::CreatePlayer(const QString &str)
{
    if(str == "Mary")
    {
        return new PlayerMary;
    }
    if(str == "Annie")
    {
        return new Annie;
    }
    if(str == "Hayk")
    {
        return new HaykPlayer;
    }
    if(str == "Gevorg")
    {
        return new GEVORG_PLAYER;
    }
    if(str == "Arman")
    {
        return new Arman;
    }

    return nullptr;
}
