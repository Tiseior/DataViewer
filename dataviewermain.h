#ifndef DATAVIEWERMAIN_H
#define DATAVIEWERMAIN_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QThread>
#include "Models/editorslist.h"
#include "Config/database.h"
#include "Util/datafile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DataViewerMain;
}
QT_END_NAMESPACE

class DataViewerMain : public QMainWindow
{
    Q_OBJECT

public:
    DataViewerMain(QWidget *parent = nullptr);
    ~DataViewerMain();

private slots:
    void on_importButton_clicked();
    void on_clearButton_clicked();
    void slotEditRecord();
    void slotRemoveRecord();
    void slotExportRecord();
    void slotCustomMenuRequested(QPoint p);

private:
    Ui::DataViewerMain *ui;
    EditorsList *editorsList;
    DataBase *db;
    DataFile *df;
    QPushButton *add;
};
#endif // DATAVIEWERMAIN_H
