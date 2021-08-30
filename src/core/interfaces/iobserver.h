#ifndef BATTLESHIP_CORE_INFRASTRUCTURE_IOBSERVER_H
#define BATTLESHIP_CORE_INFRASTRUCTURE_IOBSERVER_H

template <typename T>
class IObserver
{
public:
    virtual void update(const T &data) = 0;
};

#endif