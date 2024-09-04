// Модель для отображение сущности Editor в интерфейсе

#include "editorslist.h"

EditorsList::EditorsList(QObject *parent)
    : QAbstractTableModel{parent} {
    selectEditors(editorsService->selectAll());
}

int EditorsList::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_editors.count();
}

int EditorsList::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return LAST;
}

QVariant EditorsList::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || m_editors.count() <= index.row() ||
        (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();
    return m_editors[index.row()][Column(index.column())];
}

bool EditorsList::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || role != Qt::EditRole || m_editors.count() <= index.row())
        return false;
    m_editors[index.row()][Column(index.column())] = value;
    emit dataChanged(index, index);

    Editor editor;
    editor.setTextEditor(m_editors[index.row()][TEXT_EDITOR].toString());
    editor.setFileFormats(m_editors[index.row()][FILE_FORMATS].toString());
    editor.setEncoding(m_editors[index.row()][ENCODING].toString());
    editor.setHasIntelligence(m_editors[index.row()][HAS_INTELLIGENCE].toBool());
    editor.setHasPlugins(m_editors[index.row()][HAS_PLUGINS].toBool());
    editor.setCanCompile(m_editors[index.row()][CAN_COMPILE].toBool());
    editorsService->updateEditor(editor);

    return true;
}

Qt::ItemFlags EditorsList::flags( const QModelIndex &index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.isValid()) {
        if(index.column() != TEXT_EDITOR)
            flags |= Qt::ItemIsEditable;
    }
    return flags;
}

QVariant EditorsList::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Vertical)
        return section;
    else
        switch(section) {
            case TEXT_EDITOR:
                return QVariant("Text editor");
            case FILE_FORMATS:
                return QVariant("File formats");
            case ENCODING:
                return QVariant("Encoding");
            case HAS_INTELLIGENCE:
                return QVariant("Has intelligence");
            case HAS_PLUGINS:
                return QVariant("Has plugins");
            case CAN_COMPILE:
                return QVariant("Can compile");
            default:
                return QVariant();
        }
}

void EditorsList::selectEditors(const QList<Editor*> &newEditors) {
    int row = m_editors.count();
    beginInsertRows(QModelIndex(), row, row+newEditors.count()-1);
    for(int i=0; i<newEditors.size(); i++) {
        EditorsData editor;
        editor[TEXT_EDITOR] = newEditors.at(i)->getTextEditor();
        editor[FILE_FORMATS] = newEditors.at(i)->getFileFormats();
        editor[ENCODING] = newEditors.at(i)->getEncoding();
        editor[HAS_INTELLIGENCE] = newEditors.at(i)->getHasIntelligence();
        editor[HAS_PLUGINS] = newEditors.at(i)->getHasPlugins();
        editor[CAN_COMPILE] = newEditors.at(i)->getCanCompile();
        m_editors.append(editor);
    }
    endInsertRows();
}

void EditorsList::addEditor(const Editor &newEditor) {
    EditorsData editor;
    editor[TEXT_EDITOR] = newEditor.getTextEditor();
    editor[FILE_FORMATS] = newEditor.getFileFormats();
    editor[ENCODING] = newEditor.getEncoding();
    editor[HAS_INTELLIGENCE] = newEditor.getHasIntelligence();
    editor[HAS_PLUGINS] = newEditor.getHasPlugins();
    editor[CAN_COMPILE] = newEditor.getCanCompile();
    int row = m_editors.count();
    beginInsertRows(QModelIndex(), row, row);
    m_editors.append(editor);
    endInsertRows();
}

void EditorsList::addEditors(const QList<Editor*> &newEditors) {
    int row = m_editors.count();
    for(int i=0; i<newEditors.size(); i++) {
        if(editorsService->insertEditor(*newEditors.at(i))) {
            beginInsertRows(QModelIndex(), row, row);
            EditorsData editor;
            editor[TEXT_EDITOR] = newEditors.at(i)->getTextEditor();
            editor[FILE_FORMATS] = newEditors.at(i)->getFileFormats();
            editor[ENCODING] = newEditors.at(i)->getEncoding();
            editor[HAS_INTELLIGENCE] = newEditors.at(i)->getHasIntelligence();
            editor[HAS_PLUGINS] = newEditors.at(i)->getHasPlugins();
            editor[CAN_COMPILE] = newEditors.at(i)->getCanCompile();
            m_editors.append(editor);
            endInsertRows();
        }
    }
}

void EditorsList::removeEditor(const QString &editorName) {
    listOfEditors::iterator it = m_editors.begin();
    for(int i=0; it != m_editors.end(); i++, it++) {
        if(it->value(TEXT_EDITOR) == editorName) {
            beginRemoveRows(QModelIndex(), i, i);
            it = m_editors.erase(it);
            endRemoveRows();
            editorsService->deleteEditor(editorName);
            break;
        }
    }
}

void EditorsList::removeEditors() {
    beginRemoveRows(QModelIndex(), 0, m_editors.count()-1);
    m_editors.clear();
    endRemoveRows();
    editorsService->deleteAll();
}
