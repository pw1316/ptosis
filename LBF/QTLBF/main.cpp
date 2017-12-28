#include "QTLBF.h"

#include <QtWidgets/QApplication>

#include "Log.h"

QTLBF* w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(msgHandler);
    w = new QTLBF();
    w->show();
    return a.exec();
}
