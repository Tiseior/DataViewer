#ifndef FILEREADERWINDOW_H
#define FILEREADERWINDOW_H

#include <QDialog>

namespace Ui {
class FileReaderWindow;
}

class FileReaderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FileReaderWindow(QWidget *parent = nullptr);
    ~FileReaderWindow();

private:
    Ui::FileReaderWindow *ui;
};

#endif // FILEREADERWINDOW_H
