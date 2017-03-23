#include "round.h"
#include <algorithm>
#include <functional>
#include <set>
#include <QtDebug>
#include <utility>


Round::Round(IPlayer* pl1, IPlayer* pl2)
{
    players[0] = pl1;
    players[1] = pl2;
    assert(pl1 != nullptr && pl2 != nullptr);
}

IPlayer *Round::play() //Mary
{
    try
    {
        try
        {
            players[0]->PrepareForNewRound();
            qDebug() << players[0]->PlayerName() << " prepares for new round.\n";
        }
        catch(const std::exception & e)
        {
            qDebug() << "Exception thrown from " << players[0]->PlayerName()
                     << "'s PrepareForNewRound. Exception: " << e.what();
            return players[1];
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown from " << players[0]->PlayerName()\
                        << "'s PrepareForNewRound.";
            return players[1];
        }


        try
        {
            players[1]->PrepareForNewRound();
            qDebug() << players[1]->PlayerName() << " prepares for new round.\n";
        }
        catch(const std::exception & e)
        {
            qDebug() << "Exception thrown from " << players[1]->PlayerName()\
                        << "'s PrepareForNewRound. Exception: " << e.what();
            return players[0];
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown from " << players[1]->PlayerName()\
                        << "'s PrepareForNewRound.";
            return players[0];
        }

        //std::for_each(players, players + 2, std::bind(PrepareForNewRound(), _1););



        std::vector<Ship> ships[2];
        try
        {
            ships[0] = players[0]->PlaceShips();
            qDebug() << players[0]->PlayerName() << " places ships.\n";
        }
        catch(const std::exception & e)
        {
            qDebug() << "Exception thrown from " << players[0]->PlayerName()\
                        << "'s PlaceShips. Exception: " << e.what();
            return players[1];
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown from " << players[0]->PlayerName()\
                        << "'s PlaceShips.";
            return players[1];
        }

        try
        {
            ships[1] = players[1]->PlaceShips();
            qDebug() << players[1]->PlayerName() << " places ships.\n";
        }
        catch(const std::exception & e)
        {
            qDebug() << "Exception thrown from " << players[1]->PlayerName()\
                        << "'s PlaceShips. Exception: " << e.what();
            return players[0];
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown from " << players[1]->PlayerName()\
                        << "'s PlaceShips.";
            return players[0];
        }




        try
        {            
            if(!check_ships(ships[0]))
            {
                qDebug() << "check_ships failed for " << players[0]->PlayerName();
                return players[1];
            }
        }
        catch(const std::exception & e)
        {
            qDebug() << "Exception thrown from " << players[0]->PlayerName()\
                     << "'s check_ships. Exception: " << e.what() ;
            return players[1];
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown from " << players[0]->PlayerName()\
                        << "'s check_ships.";
            return players[1];
        }

        try
        {
            if(!check_ships(ships[1]))
            {
                qDebug() << "check_ships failed for " << players[0]->PlayerName();
                return players[0];
            }
        }
        catch(const std::exception & e)
        {
            qDebug() << "Exception thrown from " << players[1]->PlayerName()\
                        << "'s check_ships. Exception: " << e.what();
            return players[0];
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown from " << players[1]->PlayerName()\
                        << "'s check_ships.";
            return players[0];
        }

        //shotFields[i] is the list of fields that player i shot at.
        std::set<Coordinate> shotFields[2];

        int curr_player = 0;
        for(;;)
        {

            int curr_opponent = 1 - curr_player;
          //  qDebug() << "start of loop. curPlayer  = " << curr_player;
            Coordinate coord(0,0);
            try
            {
                coord = players[curr_player]->Shoot();
            //    qDebug() << players[curr_player]->PlayerName()
//                         << " shoots at (" << coord.row()
  //                       << " " << coord.column() << ").\n";
            }
            catch(const std::exception & e)
            {
                qDebug() << "Exception thrown from " << players[curr_player]->PlayerName()\
                            << "'s Shoot. Exception: " << e.what();
                return players[curr_opponent];
            }
            catch(...)
            {
                qDebug() << "Unknown exception thrown from " << players[curr_player]->PlayerName()\
                            << "'s Shoot.";
                return players[curr_opponent];
            }

            if(shotFields[curr_player].find(coord) != shotFields[curr_player].end())
            {
                try
                {
                    players[curr_player]->ProcessShotResult(AlreadyShot, coord);
           //         qDebug() << coord.row() << " " << coord.column() << ") was already shot.\n";
                }
                catch(const std::exception & e)
                {
                    qDebug() << "Exception thrown from " << players[curr_player]->PlayerName()\
                                << "'s ProcessShotResult. Exception: " << e.what();
                    return players[curr_opponent];
                }
                catch(...)
                {
                    qDebug() << "Unknown exception thrown from " << players[curr_player]->PlayerName()\
                                << "'s ProcessShotResult.";
                    return players[curr_opponent];
                }
                curr_player = 1 - curr_player;
                continue;
            }
            else
            {
                shotFields[curr_player].insert(coord);
            }

            bool is_wounded= false;
            try
            {
                for(int j = 0; j < ships[curr_opponent].size(); ++j)
                {
                    if(ships[curr_opponent][j].is_part_of_ship(coord))
                    {
                        ships[curr_opponent][j].decrement_live_cells();
                        if(ships[curr_opponent][j].is_dead())
                        {
                            players[curr_player]->ProcessShotResult(Dead, coord);
                      //      qDebug() << "A ship was destroyed.\n";
                            ships[curr_opponent].erase(ships[curr_opponent].begin() + j);
                        }
                        else
                        {
                            players[curr_player]->ProcessShotResult(Wounded, coord);
                           // qDebug() << "A ship was wounded.\n";
                        }
                        is_wounded = true;
                        break;
                    }
                }
                if (!is_wounded)
                {
                     players[curr_player]->ProcessShotResult(Missed, coord);
                     //qDebug() << "Sorry loser, you missed\n";
                     curr_player = 1 - curr_player;
                }
            }
            catch(const std::exception& e)
            {
                qDebug() << "Exception: " << e.what() << " when processing shot result.";
            }

            if(ships[0].empty())
            {
                return players[1];
            }
            else if(ships[1].empty())
            {
                return players[0];
            }
        }
    }
    catch(...)
    {
        throw std::exception("unreachable code");
    }
}

bool Round::check_ships(const std::vector<Ship>& ships) const //Anna & Arman
{
    //TODO unit tests
    const int N = 10;
    const int M = 4;
    std::vector<int> V;
    for (int i = M; i > 0; --i)
        V.push_back(i);

    if (ships.size() != N)
        return false;

    std::vector<int> SizesOfShips(M);
    for (int i = 0; i < N; ++i)
    {
        if (ships[i].size() > M)
            return false;
        else
            ++SizesOfShips[ships[i].size() - 1];
    }

    if (SizesOfShips != V)
        return false;

    for (int i = 0; i<Settings::boardWidth; ++i)
    {
        for (int j = 0; j<Settings::boardHeight; ++j)
        {
            for (int a = 0; a < N; ++a)
            {
                for (int b = a+1; b < N; ++b)
                {
                    if (ships[a].is_part_of_ship(Coordinate(i, j)) && ships[b].is_neighbour_of_ship(Coordinate(i, j)))
                    {
                        qDebug() << "xx" << i << " " << j << " " << a << " " << b;
                        return false;
                    }
                }
            }
        }
    }

    return true;
}
