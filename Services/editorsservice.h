// Сервис для взаимодействия с сущностью Editor в базе данных

#ifndef EDITORSSERVICE_H
#define EDITORSSERVICE_H

#include <QObject>
#include <QSqlRecord>
#include <QFileDialog>
#include "Config/database.h"
#include "Models/editor.h"

class EditorsService : public QObject
{
    Q_OBJECT
public:
    explicit EditorsService(QObject *parent = nullptr);
    QList<Editor*> selectAll();
    bool insertEditor(const Editor &editor) const;
    void insertAll(const QList<Editor*> &editors);
    void deleteAll();
    void deleteEditor(const QString &editorName);
    void updateEditor(const Editor &editor);

private:
    DataBase *db;

signals:
};

#endif // EDITORSSERVICE_H
