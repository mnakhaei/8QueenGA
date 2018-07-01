#include <QCoreApplication>
#include <QRandomGenerator64>
#include "eightqueenstate.h"
#include <QDebug>
#include <QVector>
#include <QElapsedTimer>
#include <QFile>

typedef  unsigned int uint;

constexpr uint N = 60;
constexpr uint M =1   ;
int main()
{
    qint64 res(0);

    for (uint k=0;k<M;k++)
    {
        QVector<eightQueenState> populationd;
        for(uint i=0;i<N;++i)
            populationd.push_back(eightQueenState());
        eightQueenState goal;
        bool goalfinded = false;
        int d =0;
        QElapsedTimer timer;
        timer.start();
        while (!goalfinded) {
            d++;
            QVector<eightQueenState> newPopulation;
            for(uint i=0;i<N;++i)
                newPopulation.push_back(eightQueenState::selection(populationd)
                                        +eightQueenState::selection(populationd));
            for (auto& i:newPopulation)
                i.mutation();
            for(auto i:newPopulation)
                if(i.cost()==0)
                {
                    goal = i;
                    goalfinded=true;
                }
            populationd=newPopulation;
        }
        goal.print();
        res +=timer.elapsed();
    }

    QFile result("result.txt");
    result.open(QFile::Append);
    QTextStream out(&result);
    out << qreal(res)/M << '\n';
    result.close();
    return 0;
}
