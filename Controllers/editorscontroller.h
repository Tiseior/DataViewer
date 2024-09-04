#ifndef EDITORSCONTROLLER_H
#define EDITORSCONTROLLER_H

#include <QObject>
#include <QDir>
#include <QPushButton>
#include "Util/datafile.h"
#include "Models/editor.h"
#include "Models/editorslist.h"
#include "Services/editorsservice.h"

class EditorsController : public QObject
{
    Q_OBJECT
public:
    explicit EditorsController(QObject *parent = nullptr);
    void addEditors(QDir dir);

private:
    EditorsList* editorsList;
    EditorsService* editorsService;
    QPushButton *add;

signals:
};

#endif // EDITORSCONTROLLER_H
