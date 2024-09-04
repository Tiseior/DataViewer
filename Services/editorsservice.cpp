// Сервис для взаимодействия с сущностью Editor в базе данных

#include "editorsservice.h"

EditorsService::EditorsService(QObject *parent)
    : QObject{parent} {}

QList<Editor*> EditorsService::selectAll() {
    db->connectToDataBase();
    QList<Editor*> editors;
    QSqlQuery query;
    query.exec("SELECT * FROM Editor");
    QSqlRecord rec = query.record();
    while (query.next()) {
        Editor* ed = new Editor;
        ed->setTextEditor(query.value(rec.indexOf("Text_editor")).toString());
        ed->setFileFormats(query.value(rec.indexOf("File_formats")).toString());
        ed->setEncoding(query.value(rec.indexOf("Encoding")).toString());
        ed->setHasIntelligence(query.value(rec.indexOf("Has_intelligence")).toBool());
        ed->setHasPlugins(query.value(rec.indexOf("Has_plugins")).toBool());
        ed->setCanCompile(query.value(rec.indexOf("Can_compile")).toBool());
        editors.append(ed);
    }
    return editors;
}

bool EditorsService::insertEditor(const Editor &editor) const {
    db->connectToDataBase();
    QSqlQuery query;
    query.prepare("INSERT INTO Editor VALUES (:name, :formats, :encoding, :intelligence, :plugins, :compile)");
    query.bindValue(":name", editor.getTextEditor());
    query.bindValue(":formats", editor.getFileFormats());
    query.bindValue(":encoding", editor.getEncoding());
    query.bindValue(":intelligence", editor.getHasIntelligence());
    query.bindValue(":plugins", editor.getHasPlugins());
    query.bindValue(":compile", editor.getCanCompile());
    query.exec();
    return !query.lastError().isValid();
}

void EditorsService::insertAll(const QList<Editor*> &editors) {
    db->connectToDataBase();
    QSqlQuery query;
    foreach (Editor* editor, editors) {
        query.prepare("INSERT INTO Editor VALUES (:name, :formats, :encoding, :intelligence, :plugins, :compile)");
        query.bindValue(":name", editor->getTextEditor());
        query.bindValue(":formats", editor->getFileFormats());
        query.bindValue(":encoding", editor->getEncoding());
        query.bindValue(":intelligence", editor->getHasIntelligence());
        query.bindValue(":plugins", editor->getHasPlugins());
        query.bindValue(":compile", editor->getCanCompile());
        query.exec();
    }
}

void EditorsService::deleteAll() {
    db->connectToDataBase();
    QSqlQuery query;
    query.exec("DELETE FROM Editor");
}

void EditorsService::deleteEditor(const QString &editorName) {
    db->connectToDataBase();
    QSqlQuery query;
    query.prepare("DELETE FROM Editor WHERE Text_editor = ?");
    query.addBindValue(editorName);
    query.exec();
}

void EditorsService::updateEditor(const Editor &editor) {
    db->connectToDataBase();
    QSqlQuery query;
    query.prepare("UPDATE Editor SET File_formats = :formats, Encoding = :encoding, "
                  "Has_intelligence = :intelligence, Has_plugins = :plugins, Can_compile = :compile WHERE Text_editor = :name");
    query.bindValue(":formats", editor.getFileFormats());
    query.bindValue(":encoding", editor.getEncoding());
    query.bindValue(":intelligence", editor.getHasIntelligence());
    query.bindValue(":plugins", editor.getHasPlugins());
    query.bindValue(":compile", editor.getCanCompile());
    query.bindValue(":name", editor.getTextEditor());
    query.exec();
}
