#include "playermary.h"
#include "ship.h"
#include <vector>
#include "coordinate.h"
#include <QGlobal.h>
#include <QTime>

PlayerMary::PlayerMary()
{

}

void PlayerMary::ProcessShotResult(ShotResult res, Coordinate coord)
{


}
void PlayerMary::ProcessRoundResult(bool youWin)
{

}

std::vector<Ship> PlayerMary::PlaceShips()
{
    std::vector<Ship> ships;
    ships.push_back(Ship (Coordinate (0, 5), Ship::Horizontal, 2));
    ships.push_back(Ship (Coordinate(1, 1), Ship::Vertical, 4));
    ships.push_back(Ship (Coordinate(1, 8), Ship::Vertical, 1));
    ships.push_back(Ship (Coordinate(2, 3), Ship::Vertical, 2));
    ships.push_back(Ship (Coordinate(4, 6), Ship::Horizontal, 2));
    ships.push_back(Ship (Coordinate(4, 9), Ship::Vertical, 3));
    ships.push_back(Ship (Coordinate(6, 4), Ship::Vertical, 1));
    ships.push_back(Ship (Coordinate(7, 1), Ship::Vertical, 1));
    ships.push_back(Ship (Coordinate(8, 3), Ship::Horizontal, 3));
    ships.push_back(Ship (Coordinate(9, 8), Ship::Vertical, 1));
    return ships;
}

Coordinate PlayerMary::Shoot()
{
    int x = rand() % 10;
    int y = rand() % 10;
    return Coordinate(x, y);
}

