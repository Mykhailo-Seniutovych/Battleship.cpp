#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_DATABASE_SERVICE_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_DATABASE_SERVICE_H

#include "idatabase-service.h"

template <class T>
class DatabaseService : public IDatabaseService<T>
{
    typedef std::function<const T(sqlite3_stmt *)> recorReaderFunc;
    typedef std::function<const void(sqlite3_stmt *)> paramsBinderFunc;

public:
    T readSingle(
        const char *query, recorReaderFunc recordReader, paramsBinderFunc paramsBinder) const override
    {
        sqlite3 *db = nullptr;
        sqlite3_stmt *statement;
        auto openResult = sqlite3_open(m_dbName, &db);
        if (openResult != SQLITE_OK)
        {
            // TODO: handle errors
            return T();
        }

        auto prepareResult = sqlite3_prepare_v2(db, query, -1, &statement, 0);
        if (prepareResult != SQLITE_OK)
        {
            // TODO: handle errors
            return T();
        }

        paramsBinder(statement);

        auto queryResult = sqlite3_step(statement);
        auto record = recordReader(statement);

        sqlite3_close(db);
        return record;
    }

    std::vector<T> readCollection(const char *query, recorReaderFunc recordReader) const override
    {
        paramsBinderFunc doNothingBinder = [](sqlite3_stmt *t_statement) {};
        return readCollection(query, recordReader, doNothingBinder);
    }

    std::vector<T> readCollection(
        const char *query, recorReaderFunc recordReader, paramsBinderFunc paramsBinder) const override
    {
        sqlite3 *db = nullptr;
        sqlite3_stmt *statement;
        auto openResult = sqlite3_open(m_dbName, &db);
        if (openResult != SQLITE_OK)
        {
            // TODO: handle errors
            return std::vector<T>{};
        }

        auto prepareResult = sqlite3_prepare_v2(db, query, -1, &statement, 0);
        if (prepareResult != SQLITE_OK)
        {
            // TODO: handle errors
            return std::vector<T>{};
        }

        paramsBinder(statement);

        auto result = std::vector<T>();
        while (sqlite3_step(statement) != SQLITE_DONE)
        {
            auto record = recordReader(statement);
            result.push_back(record);
        }

        sqlite3_close(db);
        return result;
    }

    void executeCommand(const char *t_query, paramsBinderFunc paramsBinder) const override
    {
        sqlite3 *db = nullptr;
        auto openResult = sqlite3_open(m_dbName, &db);
        if (openResult != SQLITE_OK)
        {
            // TODO: handle errors
            return;
        }

        sqlite3_stmt *statement;
        auto prepareResult = sqlite3_prepare(db, t_query, -1, &statement, 0);
        if (prepareResult != SQLITE_OK)
        {
            // TODO: handle errors
            return;
        }

        paramsBinder(statement);

        auto executeResult = sqlite3_step(statement);
        if (executeResult != SQLITE_OK)
        {
            // TODO: handle errors
            return;
        }

        sqlite3_close(db);
    }

private:
    const char *m_dbName = "statistics.db";
};

#endif
