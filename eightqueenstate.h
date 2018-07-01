#ifndef EIGHTQUEENSTATE_H
#define EIGHTQUEENSTATE_H

#include <QVector>
#include <QObject>
#include <QDebug>
#include <random>



class eightQueenState
{

public:
    static constexpr int N = 8;
    static eightQueenState selection(const QVector<eightQueenState> &population);
    eightQueenState();
    eightQueenState(const QVector<int> &vec);
    int cost() const;
    void mutation();
    void print() const;
    eightQueenState operator+(const eightQueenState &right);
    int fitnes();

signals:

public slots:

private:

    QVector<int> plane;
    static std::default_random_engine engin;
    static  const double epsilon;



};

#endif // EIGHTQUEENSTATE_H
