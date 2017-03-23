#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QVector>
#include <QString>
#include <algorithm>
#include "match.h"
#include <sstream>
#include <QDateTime>
#include <QDebug>
#include <fstream>

class Tournament
{
public:
    Tournament(const QVector<QString>& players_)
        :players(players_)
    {
        std::random_shuffle(players.begin(), players.end());
        for(int i = 0; i < players.size(); ++i)
        {
            Match m;
            qDebug() << "Testing player " << players[i];
            try
            {
                m.Play(players[i], players[i], 1);
            }
            catch(...)
            {
                qDebug() << "Exception thrown from player " << players[i];
            }
        }
    }

    void Play(int roundCounts)
    {
        QVector<QVector<int>> result(players.size(), QVector<int> (players.size()));


        for(int i = 0; i < players.size(); ++i)
        {
            for(int j = i + 1; j < players.size(); ++j)
            {

                Match m;
                auto res = m.Play(players[i], players[j],roundCounts );
                result[i][j] = res.first - res.second;
                result[j][i] = res.second - res.first;
                qDebug() << "Match between" << players[i] << " and "
                            << players[j] << "finished";
            }
        }

        QString html = CreateHTMLTable(result);
        std::ostringstream filename;
        auto dt = QDateTime::currentDateTimeUtc();
        filename << "result_" << roundCounts << "_" << dt.date().day() << "_"
                 << dt.date().month() << "_" << dt.date().year()
                 << "_" << dt.time().hour() << dt.time().minute()
                    << dt.time().second() << dt.time().msec();

        qDebug() << filename.str().c_str();
        std::ofstream out(filename.str() + ".html");

        if(!out.is_open())
        {
            qDebug() << "UNABLE TO SAVE RESULTS";
        }
        out << html.toStdString();
    }


private:
    QString CreateHTMLTable(const QVector<QVector<int>>& result)
    {
       std::ostringstream oss;
       oss << "<table>";
       oss << "<tr>";

       oss <<"<td>NAME</td>";
       for(int i = 0; i < players.size(); ++i)
       {
           oss <<"<td>" << players[i].toStdString() << "</td>";
       }
       oss << "</tr>";
       for(int i = 0; i < players.size(); ++i)
       {
           oss << "<tr>";
           oss <<"<td>" << players[i].toStdString() << "</td>";
           for(int j = 0; j < players.size(); ++j)
           {
               oss << "<td>";
               oss << result[i][j];
               oss << "</td>";
           }
           oss << "</tr>";
       }
       oss << "</table>";
       return oss.str().c_str();

    }

    QVector<QString> players;
};

#endif // TOURNAMENT_H
