#include "DFEMainWindow.hpp"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DFEMainWindow w;
    w.show();

    // qDebug() << QStyleFactory::keys();
    // QApplication::setStyle("Breeze");

    return app.exec();
}
