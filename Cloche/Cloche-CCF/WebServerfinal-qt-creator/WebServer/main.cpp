#include "WebServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	WebServer w;
    w.show();
    return a.exec();
}
