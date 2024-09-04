#include "editorscontroller.h"

EditorsController::EditorsController(QObject *parent)
    : QObject{parent}
{}

void EditorsController::addEditors(QDir dir) {
    DataFile df;
    QList<Editor*> editors = df.readDir(dir);
    editorsList->addEditors(editors);
    editorsService->insertAll(editors);
}
