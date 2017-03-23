#ifndef MATCH_H
#define MATCH_H
#include <QString>
#include <QPair>
#include "IPlayer.h"
class Match
{
public:
    Match();
    QPair<int, int> Play(const QString& player1Name,
              const QString& player2Name,
              int roundCount);
};

#endif // MATCH_H
