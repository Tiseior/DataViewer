// Класс для конфигурации базы данных
// (подключение к ней или её создание)

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QFile>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#define DATABASE_DRIVER "QSQLITE"
#define DATABASE_NAME "TestDB"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    static DataBase *connectToDataBase();

private:
    QSqlDatabase db;

private:
    static DataBase *db_instance;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();

signals:
    void finished();
};

#endif // DATABASE_H
