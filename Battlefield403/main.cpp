#include "tournament.h"
#include <QDebug>
#include <ctime>
#include <QVector>
#include <QString>
#include <QTime>
int main()
{
    srand(time(nullptr));
    try
    {
        QVector<QString> v;
        v.push_back("Mary");
        v.push_back("Annie");
        //v.push_back("Hayk");
        v.push_back("Gevorg");
        v.push_back("Arman");
        Tournament t(v);
        t.Play(1000);
    }
    catch(const std::exception& e)
    {
        qDebug() << "exception caught in main: " << e.what();
    }
    catch(...)
    {
        qDebug() << "unknown exception caught in main:";
    }
}


