#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_IDATABASE_SERVICE_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_IDATABASE_SERVICE_H

#include <string>
#include <vector>
#include <functional>
#include "sqlite3.h"
#include "db-record.h"

template <class T>
class IDatabaseService
{
public:
    typedef std::function<const T(sqlite3_stmt *)> recorReaderFunc;
    typedef std::function<const void(sqlite3_stmt *)> paramsBinderFunc;

    virtual DbRecord<T> readSingle(
        const char *query, recorReaderFunc recordReader, paramsBinderFunc paramsBinder) const = 0;

    virtual std::vector<T> readCollection(const char *query, recorReaderFunc recordReader) const = 0;
    virtual std::vector<T> readCollection(
        const char *query, recorReaderFunc recordReader, paramsBinderFunc paramsBinder) const = 0;

    virtual void executeCommand(const char *query) const = 0;
    virtual void executeCommand(const char *t_query, paramsBinderFunc paramsBinder) const = 0;
};

#endif
