// Модель для отображение сущности Editor в интерфейсе

#ifndef EDITORSLIST_H
#define EDITORSLIST_H

#include <QAbstractTableModel>
#include <QObject>
#include "Services/editorsservice.h"
#include "editor.h"

class EditorsList : public QAbstractTableModel
{
public:
    explicit EditorsList(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags( const QModelIndex &index ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void selectEditors(const QList<Editor*> &newEditors);
    void addEditor(const Editor &newEditor);
    void addEditors(const QList<Editor*> &newEditors);
    void removeEditor(const QString &editorName);
    void removeEditors();

private:
    EditorsService *editorsService;

    enum Column {
        TEXT_EDITOR,
        FILE_FORMATS,
        ENCODING,
        HAS_INTELLIGENCE,
        HAS_PLUGINS,
        CAN_COMPILE,
        LAST
    };

    typedef QHash<Column, QVariant> EditorsData;
    typedef QList<EditorsData> listOfEditors;
    listOfEditors m_editors;
};

#endif // EDITORSLIST_H
