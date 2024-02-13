#include <QCoreApplication>
#include "mywebsocketserver.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    MyWebSocketServer server(667);

    return a.exec();
}
