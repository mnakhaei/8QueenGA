#include "eightqueenstate.h"
#include <random>
#include <ctime>
#include <iostream>

std::default_random_engine eightQueenState::engin(time(0));
const double eightQueenState::epsilon = 0.1;

eightQueenState eightQueenState::operator+(const eightQueenState &right)
{
    std::uniform_int_distribution<int> u(0,N-1);
    int crossOverPoint = u(engin);
    QVector<int> p(N);
    for(int i=0;i<crossOverPoint;++i)
        p[i]=this->plane[i];
    for (int i=crossOverPoint;i<N;++i)
        p[i]=right.plane[i];
    return eightQueenState(p);
}

int eightQueenState::fitnes()
{
    return (N*(N-1))/2-cost();
}

eightQueenState eightQueenState::selection(const QVector<eightQueenState>& population)
{
    int c = 0;
    for(auto p:population)
        c += p.fitnes();
    std::uniform_int_distribution<int> u(0,c);
    eightQueenState s;
    int r = u(engin);
    for (auto p:population)
        if (r < p.fitnes())
        {
            s= p;
            break;
        }
        else
            r-=p.fitnes();
    return s;
}

eightQueenState::eightQueenState() :plane(N)
{
    std::uniform_int_distribution<int> u(0,N-1);
    for (int i=0;i<N;++i)
        plane[i]= u(engin);
}

eightQueenState::eightQueenState(const QVector< int> &vec):
    plane(vec)
{

}

int eightQueenState::cost() const
{
    int c(0);
    for (int i=0;i<N-1;++i)
        for(int j=i+1;j<N;j++)
            if (plane[i]==plane[j])
                c++;
    for (int i=0;i<N-1;++i)
        for (int j=1;j+i < N && plane[i]+j <N;++j)
            if(plane[i+j]==plane[i]+j)
                c++;
    for (int i=0;i<N-1;++i)
        for (int j=1;j+i < N && plane[i]-j >=0;++j)
            if(plane[i+j]==plane[i]-j)
                c++;
    return c;
}

void eightQueenState::mutation()
{
    std::uniform_real_distribution<double> d(0,1);
    std::uniform_int_distribution<int> u(0,N-1);

    for (int i=0;i< N;i++)
        if (epsilon > d(engin))
            plane[i]=u(engin);
}

void eightQueenState::print() const
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            if(plane[j]!=i)
                std::cout << '-';
            else
                std::cout << '*';
        std::cout << std::endl;
    }
}
