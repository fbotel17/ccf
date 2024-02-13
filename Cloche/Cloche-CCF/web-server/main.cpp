#include <QCoreApplication>
#include "webserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    new WebServer;
    return a.exec();
}
