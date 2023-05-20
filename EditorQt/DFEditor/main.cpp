#include "dfemainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DFEMainWindow w;
    w.show();
    return a.exec();
}
