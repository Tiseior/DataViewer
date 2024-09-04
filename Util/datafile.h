// Класс для работы с внешними файлами

#ifndef DATAFILE_H
#define DATAFILE_H

#include <QObject>
#include <QDir>
#include <QDirIterator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QXmlStreamReader>
#include <filereaderwindow.h>
#include "Models/editor.h"

class DataFile : public QObject
{
    Q_OBJECT
public:
    explicit DataFile(QObject *parent = nullptr);
    QList<Editor*> readDir(QDir &dir);
    void writeFile(QString &path, Editor &editor);

private:
    Editor* parseJson(QFile &file);
    Editor* parseXml(QFile &file);
    void writeJson(QFile &file, Editor &editor);
    void writeXml(QFile &file, Editor &editor);

private:
    FileReaderWindow *readerWindow;

signals:
};

#endif // DATAFILE_H
