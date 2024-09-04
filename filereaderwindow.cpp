#include "filereaderwindow.h"
#include "ui_filereaderwindow.h"

FileReaderWindow::FileReaderWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileReaderWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

FileReaderWindow::~FileReaderWindow() {
    delete ui;
}

void FileReaderWindow::on_OkButton_clicked() {
    close();
}

void FileReaderWindow::addMessage(const QString message) {
    ui->textEdit->append(message + "\n");
}
