#ifndef BATTLESHIP_CORE_INFRASTRUCTURE_IOBSERVABLE_H
#define BATTLESHIP_CORE_INFRASTRUCTURE_IOBSERVABLE_H

#include "iobserver.h"
#include "../models/map-update-data.h"

template<typename T> class IObservable {
public:
    virtual void subscribe(IObserver<MapUpdateData> *observer) = 0;
    virtual void unsubscribe(IObserver<MapUpdateData> *observer) = 0;
};

#endif
