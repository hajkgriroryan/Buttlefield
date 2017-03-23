#ifndef HAYK
#define HAYK
#include "IPlayer.h"
#include "ship.h"
#include "coordinate.h"
#include "ShotResult.h"
#include <QtDebug>
#include <QTime>
#include <algorithm>

class HaykPlayer : public IPlayer
{
public:
    HaykPlayer()
    {
        std::vector<std::pair<bool, int>> v(10, std::make_pair(true, 1));
        for(int i = 0; i < 10; ++i)
        {
            learned_board.push_back(v);
        }
    }
    void PrepareForNewRound() override
    {
        a.clear();
        future_index.clear();
        already_Wounded.clear();
        //future_index.push_back(std::vector<std::pair<int, int>> (1, std::make_pair(3, 1)));
        for(int i = 0; i < 10; ++i)
            for(int j = 0; j < 10; ++j)
            {
                a.push_back(std::make_pair(i,j));
                learned_board[i][j].first = true;
            }
    }
    void ProcessShotResult(ShotResult res, Coordinate coord) override
    {
        std::pair<int, int> coord_pair = std::make_pair(coord.row(), coord.column());
        if(res == Dead)
        {
            learned_board[coord_pair.first][coord_pair.second].first = false;
            ++learned_board[coord_pair.first][coord_pair.second].second;
            auto it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first - 1, coord_pair.second - 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first - 1][coord_pair.second - 1].first = false;
                a.erase(it);
            }
            it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first + 1, coord_pair.second + 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first + 1][coord_pair.second + 1].first = false;
                a.erase(it);
            }
            it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first - 1, coord_pair.second + 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first - 1][coord_pair.second + 1].first = false;
                a.erase(it);
            }
            it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first + 1, coord_pair.second - 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first + 1][coord_pair.second - 1].first = false;
                a.erase(it);
            }

            if(already_Wounded.empty())
            {
                it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first - 1, coord_pair.second));
                if(it != a.end())
                {
                    learned_board[coord_pair.first - 1][coord_pair.second].first = false;
                    a.erase(it);
                }
                it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first + 1, coord_pair.second));
                if(it != a.end())
                {
                    learned_board[coord_pair.first + 1][coord_pair.second].first = false;
                    a.erase(it);
                }
                it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first, coord_pair.second + 1));
                if(it != a.end())
                {
                    learned_board[coord_pair.first][coord_pair.second + 1].first = false;
                    a.erase(it);
                }
                it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first, coord_pair.second - 1));
                if(it != a.end())
                {
                    learned_board[coord_pair.first][coord_pair.second - 1].first = false;
                    a.erase(it);
                }
            }
            else
            {
                already_Wounded.push_back(coord_pair);
                std::sort(already_Wounded.begin(), already_Wounded.end());
                if(how_continue(already_Wounded.front(), already_Wounded.back()))
                {
                    it = std::find(a.begin(), a.end(), std::make_pair(already_Wounded.front().first, already_Wounded.front().second - 1));
                    if(it != a.end())
                    {
                        learned_board[already_Wounded.front().first][already_Wounded.front().second - 1].first = false;
                        a.erase(it);
                    }
                    it = std::find(a.begin(), a.end(), std::make_pair(already_Wounded.back().first, already_Wounded.back().second + 1));
                    if(it != a.end())
                    {
                        learned_board[already_Wounded.back().first][already_Wounded.back().second + 1].first = false;
                        a.erase(it);
                    }
                }
                else
                {
                    it = std::find(a.begin(), a.end(), std::make_pair(already_Wounded.front().first - 1, already_Wounded.front().second));
                    if(it != a.end())
                    {
                        learned_board[already_Wounded.front().first - 1][already_Wounded.front().second].first = false;
                        a.erase(it);
                    }
                    it = std::find(a.begin(), a.end(), std::make_pair(already_Wounded.back().first + 1, already_Wounded.back().second));
                    if(it != a.end())
                    {
                        learned_board[already_Wounded.back().first + 1][already_Wounded.back().second].first = false;
                        a.erase(it);
                    }
                }
            }

            future_index.clear();
            already_Wounded.clear();
        }
        else if(res == Wounded)
        {
            learned_board[coord_pair.first][coord_pair.second].first = false;
            ++learned_board[coord_pair.first][coord_pair.second].second;

            auto it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first - 1, coord_pair.second - 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first - 1][coord_pair.second - 1].first = false;
                a.erase(it);
            }
            it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first + 1, coord_pair.second + 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first + 1][coord_pair.second + 1].first = false;
                a.erase(it);
            }
            it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first - 1, coord_pair.second + 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first - 1][coord_pair.second + 1].first = false;
                a.erase(it);
            }
            it = std::find(a.begin(), a.end(), std::make_pair(coord_pair.first + 1, coord_pair.second - 1));
            if(it != a.end())
            {
                learned_board[coord_pair.first + 1][coord_pair.second - 1].first = false;
                a.erase(it);
            }


            if(already_Wounded.empty())
                make_future_index(coord);
            else if(already_Wounded.size() == 1)
            {
                bool dummy = how_continue(coord_pair, already_Wounded[0]);
                for(int i = 0; i < future_index.size(); ++i)
                {
                    if(dummy != how_continue(already_Wounded[0], future_index[i][0]))
                    {
                        future_index.erase(future_index.begin() + i);
                        i = -1;
                    }
                }
            }
            already_Wounded.push_back(coord_pair);
        }
        else if(res == Missed)
        {
            learned_board[coord_pair.first][coord_pair.second].first = false;
            if(!already_Wounded.empty() && future_index_shooted != -1)
               future_index.erase(future_index.begin() + future_index_shooted);
        }
    }
    void ProcessRoundResult(bool youWin) override{}
    QString PlayerName() override
    {
        return "Hayk";
    }
    std::vector<Ship> PlaceShips() override
    {
        std::vector<Ship> v;
        int random = rand() % 6;
        if(random == 0)
        {
            int r = rand() % 4;
            if(r == 0)
            {
                std::vector<std::pair<int, int>> dummy;
                for(int i = 0; i < 10; ++i)
                    for(int j = 0; j < 10; ++j)
                        dummy.push_back(std::make_pair(i,j));
                v.push_back(Ship(Coordinate(0,8),Ship::Horizontal,2));
                delete_coord(std::make_pair(0,8), Ship::Horizontal, 2, dummy);
                v.push_back(Ship(Coordinate(2,9),Ship::Vertical,2));
                delete_coord(std::make_pair(2,9), Ship::Vertical, 2, dummy);
                v.push_back(Ship(Coordinate(5,9),Ship::Vertical,3));
                delete_coord(std::make_pair(5,9), Ship::Vertical, 3, dummy);
                v.push_back(Ship(Coordinate(8,0),Ship::Vertical,2));
                delete_coord(std::make_pair(8,0), Ship::Vertical, 2, dummy);
                v.push_back(Ship(Coordinate(9,2),Ship::Horizontal,3));
                delete_coord(std::make_pair(9,2), Ship::Horizontal, 3, dummy);
                v.push_back(Ship(Coordinate(9,6),Ship::Horizontal,4));
                delete_coord(std::make_pair(9,6), Ship::Horizontal, 4, dummy);
                int index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            }
            else if(r == 1)
            {
                std::vector<std::pair<int, int>> dummy;
                for(int i = 0; i < 10; ++i)
                    for(int j = 0; j < 10; ++j)
                        dummy.push_back(std::make_pair(i,j));
                v.push_back(Ship(Coordinate(0,0),Ship::Vertical,4));
                delete_coord(std::make_pair(0,0),Ship::Vertical,4, dummy);
                v.push_back(Ship(Coordinate(5,0),Ship::Vertical,2));
                delete_coord(std::make_pair(5,0),Ship::Vertical,2, dummy);
                v.push_back(Ship(Coordinate(8,0),Ship::Vertical,2));
                delete_coord(std::make_pair(8,0),Ship::Vertical,2, dummy);
                v.push_back(Ship(Coordinate(0,9),Ship::Vertical,3));
                delete_coord(std::make_pair(0,9),Ship::Vertical,3, dummy);
                v.push_back(Ship(Coordinate(4,9),Ship::Vertical,2));
                delete_coord(std::make_pair(4,9),Ship::Vertical,2, dummy);
                v.push_back(Ship(Coordinate(7,9),Ship::Vertical,3));
                delete_coord(std::make_pair(7,9),Ship::Vertical,3, dummy);
                int index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            }
            else if(r == 2)
            {
                std::vector<std::pair<int, int>> dummy;
                for(int i = 0; i < 10; ++i)
                    for(int j = 0; j < 10; ++j)
                        dummy.push_back(std::make_pair(i,j));
                v.push_back(Ship(Coordinate(0,0),Ship::Vertical,4));
                delete_coord(std::make_pair(0,0),Ship::Vertical,4, dummy);
                v.push_back(Ship(Coordinate(5,0),Ship::Vertical,3));
                delete_coord(std::make_pair(5,0),Ship::Vertical,3, dummy);
                v.push_back(Ship(Coordinate(9,0),Ship::Horizontal,2));
                delete_coord(std::make_pair(9,0),Ship::Horizontal,2, dummy);
                v.push_back(Ship(Coordinate(0,9),Ship::Vertical,2));
                delete_coord(std::make_pair(0,9),Ship::Vertical,2, dummy);
                v.push_back(Ship(Coordinate(0,2),Ship::Horizontal,3));
                delete_coord(std::make_pair(0,2),Ship::Horizontal,3, dummy);
                v.push_back(Ship(Coordinate(0,6),Ship::Horizontal,2));
                delete_coord(std::make_pair(0,6),Ship::Horizontal,2, dummy);
                int index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            }
            else if(r == 3)
            {
                std::vector<std::pair<int, int>> dummy;
                for(int i = 0; i < 10; ++i)
                    for(int j = 0; j < 10; ++j)
                        dummy.push_back(std::make_pair(i,j));
                v.push_back(Ship(Coordinate(0,0),Ship::Horizontal,2));
                delete_coord(std::make_pair(0,0),Ship::Horizontal,2, dummy);
                v.push_back(Ship(Coordinate(0,3),Ship::Horizontal,2));
                delete_coord(std::make_pair(0,3),Ship::Horizontal,2, dummy);
                v.push_back(Ship(Coordinate(0,6),Ship::Horizontal,4));
                delete_coord(std::make_pair(0,6),Ship::Horizontal,4, dummy);
                v.push_back(Ship(Coordinate(9,0),Ship::Horizontal,3));
                delete_coord(std::make_pair(9,0),Ship::Horizontal,3, dummy);
                v.push_back(Ship(Coordinate(9,4),Ship::Horizontal,2));
                delete_coord(std::make_pair(9,4),Ship::Horizontal,2, dummy);
                v.push_back(Ship(Coordinate(9,7),Ship::Horizontal,3));
                delete_coord(std::make_pair(9,7),Ship::Horizontal,3, dummy);
                int index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
                index = rand() % dummy.size();
                v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
                delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            }
        }
        else if(random == 1)
        {
            std::vector<std::pair<int, int>> dummy;
            for(int i = 0; i < 10; ++i)
                for(int j = 0; j < 10; ++j)
                    dummy.push_back(std::make_pair(i,j));
            v.push_back(Ship(Coordinate(0,7),Ship::Vertical,3));
            delete_coord(std::make_pair(0,7),Ship::Vertical,3, dummy);
            v.push_back(Ship(Coordinate(0,9),Ship::Vertical,2));
            delete_coord(std::make_pair(0,9),Ship::Vertical,2, dummy);
            v.push_back(Ship(Coordinate(3,9),Ship::Vertical,2));
            delete_coord(std::make_pair(3,9),Ship::Vertical,2, dummy);
            v.push_back(Ship(Coordinate(4,7),Ship::Vertical,3));
            delete_coord(std::make_pair(4,7),Ship::Vertical,3, dummy);
            v.push_back(Ship(Coordinate(6,9),Ship::Vertical,4));
            delete_coord(std::make_pair(6,9),Ship::Vertical,4, dummy);
            v.push_back(Ship(Coordinate(8,7),Ship::Vertical,2));
            delete_coord(std::make_pair(8,7),Ship::Vertical,2, dummy);
            int index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
        }
        else if(random == 2)
        {
            std::vector<std::pair<int, int>> dummy;
            for(int i = 0; i < 10; ++i)
                for(int j = 0; j < 10; ++j)
                    dummy.push_back(std::make_pair(i,j));
            v.push_back(Ship(Coordinate(9,0),Ship::Horizontal,4));
            delete_coord(std::make_pair(9,0),Ship::Horizontal,4, dummy);
            v.push_back(Ship(Coordinate(9,5),Ship::Horizontal,2));
            delete_coord(std::make_pair(9,5),Ship::Horizontal,2, dummy);
            v.push_back(Ship(Coordinate(9,8),Ship::Horizontal,2));
            delete_coord(std::make_pair(9,8),Ship::Horizontal,2, dummy);
            v.push_back(Ship(Coordinate(7,0),Ship::Horizontal,2));
            delete_coord(std::make_pair(7,0),Ship::Horizontal,2, dummy);
            v.push_back(Ship(Coordinate(7,3),Ship::Horizontal,3));
            delete_coord(std::make_pair(7,3),Ship::Horizontal,3, dummy);
            v.push_back(Ship(Coordinate(7,7),Ship::Horizontal,3));
            delete_coord(std::make_pair(7,7),Ship::Horizontal,3, dummy);
            int index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
        }
        else if(random == 3)
        {
            std::vector<std::pair<int, int>> dummy;
            for(int i = 0; i < 10; ++i)
                for(int j = 0; j < 10; ++j)
                    dummy.push_back(std::make_pair(i,j));
            v.push_back(Ship(Coordinate(0,0),Ship::Vertical,4));
            delete_coord(std::make_pair(0,0),Ship::Vertical,4, dummy);
            v.push_back(Ship(Coordinate(5,0),Ship::Vertical,2));
            delete_coord(std::make_pair(5,0),Ship::Vertical,2, dummy);
            v.push_back(Ship(Coordinate(8,0),Ship::Vertical,2));
            delete_coord(std::make_pair(8,0),Ship::Vertical,2, dummy);
            v.push_back(Ship(Coordinate(0,2),Ship::Vertical,3));
            delete_coord(std::make_pair(0,2),Ship::Vertical,3, dummy);
            v.push_back(Ship(Coordinate(4,2),Ship::Vertical,3));
            delete_coord(std::make_pair(4,2),Ship::Vertical,3, dummy);
            v.push_back(Ship(Coordinate(8,2),Ship::Vertical,2));
            delete_coord(std::make_pair(8,2),Ship::Vertical,2, dummy);
            int index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
        }
        else if(random == 4)
        {
            std::vector<std::pair<int, int>> dummy;
            for(int i = 0; i < 10; ++i)
                for(int j = 0; j < 10; ++j)
                    dummy.push_back(std::make_pair(i,j));
            v.push_back(Ship(Coordinate(0,0),Ship::Horizontal,2));
            delete_coord(std::make_pair(0,0),Ship::Horizontal,2, dummy);
            v.push_back(Ship(Coordinate(0,3),Ship::Horizontal,2));
            delete_coord(std::make_pair(0,3),Ship::Horizontal,2, dummy);
            v.push_back(Ship(Coordinate(0,6),Ship::Horizontal,4));
            delete_coord(std::make_pair(0,6),Ship::Horizontal,4, dummy);
            v.push_back(Ship(Coordinate(2,0),Ship::Horizontal,2));
            delete_coord(std::make_pair(2,0),Ship::Horizontal,2, dummy);
            v.push_back(Ship(Coordinate(2,3),Ship::Horizontal,3));
            delete_coord(std::make_pair(2,3),Ship::Horizontal,3, dummy);
            v.push_back(Ship(Coordinate(2,7),Ship::Horizontal,3));
            delete_coord(std::make_pair(2,7),Ship::Horizontal,3, dummy);
            int index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
            index = rand() % dummy.size();
            v.push_back(Ship(Coordinate(dummy[index].first, dummy[index].second),Ship::Vertical,1));
            delete_coord(dummy[index], Ship::Horizontal, 1, dummy);
        }
        else if(random == 5)
        {
            int r = rand() % 2;
            if(r == 0)
            {
                int board_size = 0;
                for(int h = 0; h < 1; ++h)
                {
                    std::vector<Ship> ans;
                    std::vector<std::pair<int, int>> board;
                    for(int i = 0; i < 10; ++i)
                        for(int j = 0; j < 10; ++j)
                        {
                            board.push_back(std::make_pair(i,j));
                        }

                    for(int i = 4; i > 0; --i)
                    {
                        for(int j = 0; j <= 4-i; ++j)
                        {
                            int coord_ship = rand() % board.size();
                            int dummy = rand() % 2;
                            Ship::Orientation ship_orient = Ship::Horizontal;
                            if(dummy)
                                ship_orient = Ship::Vertical;
                            while(!check_ship(board[coord_ship], ship_orient, i, board))
                            {
                                coord_ship = rand() % board.size();
                                dummy = rand() % 2;
                                ship_orient = Ship::Horizontal;
                                if(dummy)
                                    ship_orient = Ship::Vertical;
                            }
                            ans.push_back(Ship(Coordinate(board[coord_ship].first, board[coord_ship].second),ship_orient, i));
                            delete_coord(board[coord_ship], ship_orient, i, board);
                        }
                    }
                    if(board_size < board.size())
                    {
                        v = ans;
                        board_size = board.size();
                    }
                }

            }
            else if(r == 1)
            {
                v.push_back(Ship(Coordinate(1,4),Ship::Horizontal,3));
                v.push_back(Ship(Coordinate(1,8),Ship::Horizontal,1));
                v.push_back(Ship(Coordinate(4,0),Ship::Horizontal,2));
                v.push_back(Ship(Coordinate(4,8),Ship::Vertical,3));
                v.push_back(Ship(Coordinate(6,1),Ship::Horizontal,1));
                v.push_back(Ship(Coordinate(8,1),Ship::Horizontal,1));
                v.push_back(Ship(Coordinate(8,3),Ship::Horizontal,4));
                v.push_back(Ship(Coordinate(6,3),Ship::Horizontal,2));
                v.push_back(Ship(Coordinate(5,6),Ship::Vertical,2));
                v.push_back(Ship(Coordinate(8,8),Ship::Vertical,1));
            }
        }
        return v;
    }

    Coordinate Shoot() override
    {
        if(future_index.empty())
        {
            int x = rand() % 1000;
            int index = (x * rand()) % sum_of_matrix(learned_board);
            std::pair<int, int> dummy = shooting(index, learned_board);
            auto it = std::find(a.begin(), a.end(), dummy);
            a.erase(it);
            future_index_shooted = -1;
            return Coordinate(dummy.first, dummy.second);;
        }
        else
        {
            int index = rand() % (future_index.size());
            future_index_shooted = index;
            std::pair<int, int> dummy = future_index[index][0];
            future_index[index].erase(future_index[index].begin());
            if(future_index[index].empty())
            {
                future_index_shooted = -1;
                future_index.erase(future_index.begin() + index);
            }
            auto it = std::find(a.begin(), a.end(), dummy);
            learned_board[dummy.first][dummy.second].first = false;
            a.erase(it);
            return Coordinate(dummy.first, dummy.second);
        }
    }

private:
    std::vector<std::pair<int, int>> a;
    std::vector<std::vector<std::pair<int, int>>> future_index;
    std::vector<std::pair<int, int>> already_Wounded;
    int future_index_shooted;
    std::vector<std::vector<std::pair<bool, int>>> learned_board;

    std::pair<int, int> shooting (int rand_num, const std::vector<std::vector<std::pair<bool, int>>>& matrix)
    {
        int index = -1;
        for(int i = 0; i < 10; ++i)
        {
            for(int j = 0; j < 10; ++j)
            {
                if(matrix[i][j].first)
                {
                    if(index + 1 <= rand_num && rand_num <= index + matrix[i][j].second)
                    {
                        //qDebug() << "Coordinate_Shooting " << i << j << "\n";
                        return std::make_pair(i, j);
                    }
                    else
                    {
                        index += matrix[i][j].second;
                    }
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    int sum_of_matrix(const std::vector<std::vector<std::pair<bool, int>>>& matrix)
    {
        int sum = 0;
        for(int i = 0; i < 10; ++i)
        {
            for(int j = 0; j < 10; ++j)
            {
                if(matrix[i][j].first)
                    sum += matrix[i][j].second;
            }
        }
        return sum;
    }
    bool how_continue(std::pair<int, int> a, std::pair<int, int> b)
    {
        return(a.first - b.first == 0);
    }
    void make_future_index(const Coordinate& coord)
    {
        if(std::find(a.begin(), a.end(), std::make_pair(coord.row() + 1, coord.column())) != a.end())
        {
            future_index.push_back(std::vector<std::pair<int, int>> (1, std::make_pair(coord.row() + 1, coord.column())));
            for(int i = 2; i < 4; ++i)
            {
                if(std::find(a.begin(), a.end(), std::make_pair(coord.row() + i, coord.column())) == a.end())
                    break;
                future_index[future_index.size() - 1].push_back(std::make_pair(coord.row() + i, coord.column()));
            }
        }
        if(std::find(a.begin(), a.end(), std::make_pair(coord.row() - 1, coord.column())) != a.end())
        {
            future_index.push_back(std::vector<std::pair<int, int>> (1, std::make_pair(coord.row() - 1, coord.column())));
            for(int i = 2; i < 4; ++i)
            {
                if(std::find(a.begin(), a.end(), std::make_pair(coord.row() - i, coord.column())) == a.end())
                    break;
                future_index[future_index.size() - 1].push_back(std::make_pair(coord.row() - i, coord.column()));
            }
        }
        if(std::find(a.begin(), a.end(), std::make_pair(coord.row(), coord.column() + 1)) != a.end())
        {
            future_index.push_back(std::vector<std::pair<int, int>> (1, std::make_pair(coord.row(), coord.column() + 1)));
            for(int i = 2; i < 4; ++i)
            {
                if(std::find(a.begin(), a.end(), std::make_pair(coord.row(), coord.column() + i)) == a.end())
                    break;
                future_index[future_index.size() - 1].push_back(std::make_pair(coord.row(), coord.column() + i));
            }
        }
        if(std::find(a.begin(), a.end(), std::make_pair(coord.row(), coord.column() - 1)) != a.end())
        {
            future_index.push_back(std::vector<std::pair<int, int>> (1, std::make_pair(coord.row(), coord.column() - 1)));
            for(int i = 2; i < 4; ++i)
            {
                if(std::find(a.begin(), a.end(), std::make_pair(coord.row(), coord.column() - i)) == a.end())
                    break;
                future_index[future_index.size() - 1].push_back(std::make_pair(coord.row(), coord.column() - i));
            }
        }
    }
    bool check_ship(const std::pair<int, int> topLeft, const Ship::Orientation orientation,
                    const int size, const std::vector<std::pair<int, int>>& board)
    {
        if(orientation == Ship::Vertical)
        {
            for(int i = topLeft.first; i < topLeft.first + size; ++i)
            {
                if(!std::binary_search(board.begin(), board.end(), std::make_pair(i, topLeft.second)))
                    return false;
            }
        }
        else if(orientation == Ship::Horizontal)
        {
            for(int i = topLeft.second; i < topLeft.second + size; ++i)
            {
                if(!std::binary_search(board.begin(), board.end(), std::make_pair(topLeft.first, i)))
                    return false;
            }
        }
        return true;
    }
    void delete_coord(const std::pair<int, int> topLeft, const Ship::Orientation orientation,
                                       const int size, std::vector<std::pair<int, int>>& board)
    {
        if(orientation == Ship::Vertical)
        {
            for(int i = topLeft.first - 1; i < topLeft.first + size + 1; ++i)
            {
                auto it = std::lower_bound(board.begin(), board.end(), std::make_pair(i, topLeft.second));
                if(it != board.end() && *it == std::make_pair(i, topLeft.second))
                    board.erase(it);
                it = std::lower_bound(board.begin(), board.end(), std::make_pair(i, topLeft.second - 1));
                if(it != board.end() && *it == std::make_pair(i, topLeft.second - 1))
                    board.erase(it);
                it = std::lower_bound(board.begin(), board.end(), std::make_pair(i, topLeft.second + 1));
                if(it != board.end() && *it == std::make_pair(i, topLeft.second + 1))
                    board.erase(it);
            }
        }
        else if(orientation == Ship::Horizontal)
        {
            for(int i = topLeft.second - 1; i < topLeft.second + size + 1; ++i)
            {
                auto it = std::lower_bound(board.begin(), board.end(), std::make_pair(topLeft.first, i));
                if(it != board.end() && *it == std::make_pair(topLeft.first, i))
                    board.erase(it);
                it = std::lower_bound(board.begin(), board.end(), std::make_pair(topLeft.first - 1, i));
                if(it != board.end() && *it == std::make_pair(topLeft.first - 1, i))
                    board.erase(it);
                it = std::lower_bound(board.begin(), board.end(), std::make_pair(topLeft.first + 1, i));
                if(it != board.end()  && *it == std::make_pair(topLeft.first + 1, i))
                    board.erase(it);
            }
        }
    }
};


#endif // HAYK

