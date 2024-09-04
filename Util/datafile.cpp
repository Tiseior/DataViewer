// Класс для работы с внешними файлами

#include "datafile.h"
#include <QThread>

DataFile::DataFile(QObject *parent)
    : QObject{parent} {}

QList<Editor*> DataFile::readDir(QDir &dir) {
    readerWindow = new FileReaderWindow();
    QList<Editor*> editors;
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    if(!dir.exists()) {
        readerWindow->addMessage("Directory not found");
    } else {
        QDirIterator it(dir);
        QFileInfo finfo;
        QFile file;
        while(it.hasNext()) {
            it.next();
            file.setFileName(it.filePath());
            finfo.setFile(it.filePath());
            if(finfo.suffix().toLower() == "json") {
                editors.append(parseJson(file));
            }
            else if(finfo.suffix().toLower() == "xml") {
                editors.append(parseXml(file));
            }
        }
        readerWindow->addMessage("Reading files completed");
    }
    readerWindow->show();
    return editors;
}

Editor* DataFile::parseJson(QFile &file) {
    Editor *ed = new Editor;
    QString val;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        readerWindow->addMessage("Faild to open JSON file: " + file.fileName());
    } else {
        val = file.readAll();
        file.close();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);
        if(!(error.error == 0))
            readerWindow->addMessage("Error while working with JSON " + file.fileName() + ": "
                                        + error.errorString() + " "+ QString::number(error.offset));
        if(doc.isObject()) {
            QJsonObject json = doc.object();
            QJsonValue jsonValue = json.value("root");
            if(jsonValue.isObject()) {
                QJsonObject obj = jsonValue.toObject();
                ed->setTextEditor(obj["texteditor"].toString());
                ed->setFileFormats(obj["fileformats"].toString());
                ed->setEncoding(obj["encoding"].toString());
                ed->setHasIntelligence(obj["hasintellisense"].toBool());
                ed->setHasPlugins(obj["hasplugins"].toBool());
                ed->setCanCompile(obj["cancompile"].toBool());
            }
        }
    }
    return ed;
}

Editor* DataFile::parseXml(QFile &file) {
    Editor* ed = new Editor;
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        readerWindow->addMessage("Faild to open XML file: " + file.fileName());
    } else {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd() && !xmlReader.hasError()) {
            if(xmlReader.isStartElement()) {
                if(xmlReader.name().toString() == "texteditor") {
                    ed->setTextEditor(xmlReader.readElementText());
                } else if(xmlReader.name().toString() == "fileformats") {
                    ed->setFileFormats(xmlReader.readElementText());
                } else if(xmlReader.name().toString() == "encoding") {
                    ed->setEncoding(xmlReader.readElementText());
                } else if(xmlReader.name().toString() == "hasintellisense") {
                    ed->setHasIntelligence((QString::compare(xmlReader.readElementText(), "true") == 0) ? true : false);
                } else if(xmlReader.name().toString() == "hasplugins") {
                    ed->setHasPlugins((QString::compare(xmlReader.readElementText(), "true") == 0) ? true : false);
                } else if(xmlReader.name().toString() == "cancompile") {
                    ed->setCanCompile((QString::compare(xmlReader.readElementText(), "true") == 0) ? true : false);
                }
            }
            xmlReader.readNext();
        }
        if(xmlReader.hasError()) {
            readerWindow->addMessage("Error while working with XML " + file.fileName() + ": " + xmlReader.errorString());
        }
        xmlReader.clear();
        file.close();
    }
    return ed;
}

void DataFile::writeFile(QString &path, Editor &editor) {
    QFile file(path);
    QFileInfo finfo(path);
    if(finfo.suffix().toLower() == "json") {
        writeJson(file, editor);
    } else if(finfo.suffix().toLower() == "xml") {
        writeXml(file, editor);
    }
}

void  DataFile::writeJson(QFile &file, Editor &editor) {
    if(!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
        qDebug() << "File open error";
    } else {
        QJsonObject rootObject;
        QJsonObject edObject;
        edObject.insert("texteditor", editor.getTextEditor());
        edObject.insert("fileformats", editor.getFileFormats());
        edObject.insert("encoding", editor.getEncoding());
        edObject.insert("hasintellisense", editor.getHasIntelligence());
        edObject.insert("hasplugins", editor.getHasPlugins());
        edObject.insert("cancompile", editor.getCanCompile());
        rootObject.insert("root", edObject);
        QJsonDocument jsonDoc(rootObject);
        file.write(jsonDoc.toJson(QJsonDocument::Indented));
        file.close();
    }
}

void  DataFile::writeXml(QFile &file, Editor &editor) {
    if(!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
        qDebug() << "File open error";
    } else {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("root");
        xmlWriter.writeStartElement("texteditor");
        xmlWriter.writeCharacters(editor.getTextEditor());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("fileformats");
        xmlWriter.writeCharacters(editor.getFileFormats());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("encoding");
        xmlWriter.writeCharacters(editor.getEncoding());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("hasintellisense");
        xmlWriter.writeCharacters(editor.getHasIntelligence() ? "true" : "false");
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("hasplugins");
        xmlWriter.writeCharacters(editor.getHasPlugins() ? "true" : "false");
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("cancompile");
        xmlWriter.writeCharacters(editor.getCanCompile() ? "true" : "false");
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}
