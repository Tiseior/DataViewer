#include "fileparsingwondow.h"
#include "ui_fileparsingwondow.h"

FileParsingWondow::FileParsingWondow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileParsingWondow)
{
    ui->setupUi(this);
}

FileParsingWondow::~FileParsingWondow()
{
    delete ui;
}

void FileParsingWondow::on_OkButton_clicked() {
    close();
}

void FileParsingWondow::setProgress(double value) {
    ui->progressBar->setValue(value);
}
