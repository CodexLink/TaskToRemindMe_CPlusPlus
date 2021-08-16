#include "../IOHandler/ioHandlerDef.h"
#include "SQLiteRefs/sqlite3.h"
#include <iostream>

class DBHandler : protected IOHandler
{
public:
    enum DB_OPTIONS : unsigned {
        QUERY_DATA,
        COMMIT_DATA,
        UPDATE_DATA,
        DELETE_DATA,
        RECREATE_TABLE
    };
    enum DB_ERRORCODE : unsigned {
        QUERY_INVALID,
        QUERY_ERROR,
        QUERY_NOT_FOUND,
        QUERY_SUCCESS,
        COMMIT_ERROR,
        COMMIT_UNEXPECTED,
        COMMIT_SUCCESS,
        UPDATE_ERROR,
        UPDATE_UNEXPECTED,
        UPDATE_SUCCESS,
        DELETE_INVALID,
        DELETE_ERROR,
        DELETE_SUCCESS
    };

    // # We need to know more information regarding this one.
    typedef struct DB_CREDENTIALS {
        int a = 1;
    } DB_AUTH_DATA;


    DBHandler(bool OVERRIDE_DB_AUTH_DATA);
    ~DBHandler();

    // # We need to create CRUD for us to know how to make this one work.
    bool commitData();
    bool deleteData();
    bool updateData();
    bool dbConn();
    bool dbReconn();

private:
    void isUserAuthenticated();
    void recreateDB();
    void createDB();
    void deleteDB();
    void updateDB();
    void decodeDBError(DB_ERRORCODE errorSignal);
protected:

}