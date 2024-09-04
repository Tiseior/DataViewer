#include "filereaderwindow.h"
#include "ui_filereaderwindow.h"

FileReaderWindow::FileReaderWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileReaderWindow)
{
    ui->setupUi(this);
}

FileReaderWindow::~FileReaderWindow()
{
    delete ui;
}
