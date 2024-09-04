#include "dataviewermain.h"
#include "Util/datafile.h"
#include "ui_dataviewermain.h"

#include <QDebug>

DataViewerMain::DataViewerMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataViewerMain)
{
    ui->setupUi(this);
    ui->tableView->setModel(editorsList = new EditorsList);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

DataViewerMain::~DataViewerMain() {
    delete ui;
}

void DataViewerMain::on_importButton_clicked() {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    if(dialog.exec()) {
        QDir dir(dialog.directory());
        QList<Editor*> editors = df->readDir(dir);
        editorsList->addEditors(editors);
    }
}


void DataViewerMain::on_clearButton_clicked() {
    editorsList->removeEditors();
}

void DataViewerMain::slotCustomMenuRequested(QPoint p) {
    QMenu* menu = new QMenu(this);
    QAction* exportRec = new QAction("Экспортировать строку в JSON/XML");
    QAction* editRec = new QAction("Редактировать", this);
    QAction* deleteRec = new QAction("Удалить строку", this);
    QModelIndex index = ui->tableView->indexAt(p);
    connect(exportRec, SIGNAL(triggered()), this, SLOT(slotExportRecord()));
    connect(editRec, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
    connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotRemoveRecord()));
    menu->addAction(exportRec);
    menu->addAction(editRec);
    menu->addAction(deleteRec);
    menu->popup(ui->tableView->viewport()->mapFromParent(cursor().pos()));
}

void DataViewerMain::slotExportRecord() {
    ui->tableView->selectRow(ui->tableView->currentIndex().row());
    QString selectedFilter;
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save as..."), QString(),
                                                        tr("JSON (*.json);;XML (*.xml)"),
                                                        &selectedFilter, QFileDialog::DontUseNativeDialog);
    if(selectedFilter.contains("JSON"))
        saveFileName += ".json";
    else
        saveFileName += ".xml";
    int row = ui->tableView->currentIndex().row();
    Editor editor;
    editor.setTextEditor(ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString());
    editor.setFileFormats(ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString());
    editor.setEncoding(ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString());
    editor.setHasIntelligence(ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toBool());
    editor.setHasPlugins(ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toBool());
    editor.setCanCompile(ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toBool());
    df->writeFile(saveFileName, editor);

}

void DataViewerMain::slotRemoveRecord() {
    ui->tableView->selectRow(ui->tableView->currentIndex().row());
    QString edName = ui->tableView->model()->data(ui->tableView->currentIndex()).toString();
    editorsList->removeEditor(edName);
}

void DataViewerMain::slotEditRecord() {
    ui->tableView->edit(ui->tableView->currentIndex());
}
