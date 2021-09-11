#ifndef BATTLESHIP_SRC_STATISTICS_MODELS_DB_RECORD_H
#define BATTLESHIP_SRC_STATISTICS_MODELS_DB_RECORD_H

template <class T>
struct DbRecord
{
    bool isFoundInDb;
    T entity;

    DbRecord() : isFoundInDb(false) {};
    DbRecord(const T &t_entity) : entity(t_entity), isFoundInDb(true) {};
};

#endif
