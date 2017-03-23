#include "match.h"
#include "playerfactory.h"
#include "IPlayer.h"
#include "round.h"
#include <QPair>
Match::Match()
{

}

QPair<int, int> Match::Play(const QString& player1Name,
                 const QString& player2Name,
                 int roundCount)
{

    PlayerFactory fact;
    IPlayer* p1 = fact.CreatePlayer(player1Name);
    IPlayer* p2 = fact.CreatePlayer(player2Name);
    if(!p1 || !p2)
        throw std::exception("could not create players.");
    QPair<int, int> score;
    for(int i = 0; i < roundCount; ++i)
    {
        Round rnd1(p1, p2);
        IPlayer* winner = rnd1.play();
        if(winner == p1)
            ++score.first;
        else
            ++score.second;
        Round rnd2(p2, p1);
        winner = rnd2.play();
        if(winner == p1)
            ++score.first;
        else
            ++score.second;
    }
    delete p1;
    delete p2;
    return score;
}
