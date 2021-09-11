#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_DATABASE_SERVICE_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_DATABASE_SERVICE_H

#include <filesystem>
#include "idatabase-service.h"
#include "db-record.h"
#include "sql-exception.h"

#include "queries.h"

template <class T>
class DatabaseService : public IDatabaseService<T>
{
    typedef std::function<const T(sqlite3_stmt *)> recorReaderFunc;
    typedef std::function<const void(sqlite3_stmt *)> paramsBinderFunc;

public:
    void ensureDbCreated() const
    {
        const std::filesystem::path dbPath = DB_NAME;
        auto isDbCreated = std::filesystem::exists(dbPath);
        if (!isDbCreated)
        {
            executeCommand(Queries::CREATE_PLAYER_TABLE);
        }
    }

    DbRecord<T> readSingle(
        const char *query, recorReaderFunc recordReader, paramsBinderFunc paramsBinder) const override
    {
        sqlite3 *db = nullptr;
        sqlite3_stmt *statement;

        auto openResult = sqlite3_open(DB_NAME, &db);
        if (openResult != SQLITE_OK)
        {
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        auto prepareResult = sqlite3_prepare_v2(db, query, -1, &statement, 0);
        if (prepareResult != SQLITE_OK)
        {
            sqlite3_finalize(statement);
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        paramsBinder(statement);

        auto queryResult = sqlite3_step(statement);
        auto isRecordFound = queryResult == SQLITE_ROW;

        auto record = isRecordFound ? DbRecord(recordReader(statement)) : DbRecord<T>();

        sqlite3_finalize(statement);
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
        auto openResult = sqlite3_open(DB_NAME, &db);
        if (openResult != SQLITE_OK)
        {
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        auto prepareResult = sqlite3_prepare_v2(db, query, -1, &statement, 0);
        if (prepareResult != SQLITE_OK)
        {
            sqlite3_finalize(statement);
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        paramsBinder(statement);

        auto result = std::vector<T>();
        while (true)
        {
            auto rowResult = sqlite3_step(statement);
            if (rowResult != SQLITE_DONE && rowResult != SQLITE_ROW)
            {
                sqlite3_finalize(statement);
                sqlite3_close(db);
                throw SqlException(sqlite3_errmsg(db));
            }
            if (rowResult == SQLITE_DONE)
            {
                break;
            }

            auto record = recordReader(statement);
            result.push_back(record);
        }

        sqlite3_finalize(statement);
        sqlite3_close(db);
        return result;
    }

    void executeCommand(const char *query) const override
    {
        paramsBinderFunc doNothingBinder = [](sqlite3_stmt *t_statement) {};
        executeCommand(query, doNothingBinder);
    }
    
    void executeCommand(const char *t_query, paramsBinderFunc paramsBinder) const override
    {
        sqlite3 *db = nullptr;
        auto openResult = sqlite3_open(DB_NAME, &db);
        if (openResult != SQLITE_OK)
        {
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        sqlite3_stmt *statement;
        auto prepareResult = sqlite3_prepare_v2(db, t_query, -1, &statement, 0);
        if (prepareResult != SQLITE_OK)
        {
            sqlite3_finalize(statement);
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        paramsBinder(statement);

        auto executeResult = sqlite3_step(statement);
        if (executeResult != SQLITE_DONE)
        {
            sqlite3_finalize(statement);
            sqlite3_close(db);
            throw SqlException(sqlite3_errmsg(db));
        }

        sqlite3_finalize(statement);
        sqlite3_close(db);
    }

private:
    const char *DB_NAME = "statistics.db";
};

#endif
