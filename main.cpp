#include "dataviewermain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataViewerMain w;
    w.show();
    return a.exec();
}
