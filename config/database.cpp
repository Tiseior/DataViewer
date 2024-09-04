// Класс для конфигурации базы данных
// (подключение к ней или её создание)

#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent} {}

DataBase* DataBase::db_instance = NULL;

DataBase* DataBase::connectToDataBase() {
    if(db_instance == nullptr) {
        db_instance = new DataBase();
        if(!QFile(DATABASE_NAME).exists()) {
            db_instance->restoreDataBase();
        } else {
            db_instance->openDataBase();
        }
    }
    return db_instance;
}

bool DataBase::restoreDataBase() {
    if(db_instance->openDataBase()) {
        if(!db_instance->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Failed to restore database";
        return false;
    }
    return false;
}

bool DataBase::openDataBase() {
    db = QSqlDatabase::addDatabase(DATABASE_DRIVER);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()) {
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase() {
    db.close();
}

bool DataBase::createTable() {
    QSqlQuery query;
    if(!query.exec("CREATE TABLE Editor("
                    "Text_editor TEXT(100) PRIMARY KEY,"
                    "File_formats TEXT NOT NULL,"
                    "Encoding TEXT NOT NULL,"
                    "Has_intelligence BLOB NOT NULL,"
                    "Has_plugins BLOB NOT NULL,"
                    "Can_compile BLOB NOT NULL"
                    ")")) {
        qDebug() << "DataBase: error of create " << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return true;
}
