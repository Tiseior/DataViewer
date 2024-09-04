#ifndef FILEPARSINGWONDOW_H
#define FILEPARSINGWONDOW_H

#include <QDialog>

namespace Ui {
class FileParsingWondow;
}

class FileParsingWondow : public QDialog
{
    Q_OBJECT

public:
    explicit FileParsingWondow(QWidget *parent = nullptr);
    void setProgress(double value);
    ~FileParsingWondow();

private slots:
    void on_OkButton_clicked();

private:
    Ui::FileParsingWondow *ui;
};

#endif // FILEPARSINGWONDOW_H
