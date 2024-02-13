#include "webserver.h"
#include <unistd.h>
#include <iostream>
#include <QFile>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

WebServer::WebServer(QObject *parent) : QObject(parent) {

    // Webserver
    webServer = new QWebSocketServer(QStringLiteral("WebServer"), QWebSocketServer::NonSecureMode, this);

    QObject::connect(webServer, &QWebSocketServer::newConnection, this, &WebServer::onWebServerNewConnection);


    //fichier pour l'ip des cloche
    QFile fichier("/home/debian/Bureau/Projetdemerde/ip.ini");
    fichier.open(QIODevice::ReadOnly);
    QString contenu = fichier.readLine();
    qDebug() << contenu;

    /*QString contenuport = fichier.readLine(2);
    qDebug() << contenuport;
    fichier.close();*/

    char buf[1024];
    qint64 lineLength = fichier.readLine(buf, sizeof(buf));
    if (lineLength != -1) {
        qDebug() << buf;
    }


    webServer->listen(QHostAddress::AnyIPv4, 16050);
    qDebug() << "Server Started";

    socket = new QTcpSocket();
    socket->connectToHost(contenu, 502);
    //int( buf[0] )
}

void WebServer::onWebServerNewConnection() {

    qDebug() << "Un client WEB s'est connecte";

    QWebSocket * webClient = webServer->nextPendingConnection();
    QTcpSocket::connect(webClient, &QWebSocket::textMessageReceived, this, &WebServer::onWebClientCommunication);
    QTcpSocket::connect(webClient, &QWebSocket::disconnected, this, &WebServer::onWebClientDisconnected);



}

void WebServer::onWebClientCommunication(QString entryMessage) {

    this->obj = qobject_cast<QWebSocket*>(sender());
    QString data = entryMessage;



    qDebug() << "------------------" << data;

    if (data == "cloche1") {
        // Connexion de l'utilisateur
        qDebug() << "cloche1";

        char trame[12];
        trame[0] = 0x00;
        trame[1] = 0x01;
        trame[2] = 0x00;
        trame[3] = 0x00;
        trame[4] = 0x00;
        trame[5] = 0x06;
        trame[6] = 0x11;
        trame[7] = 0x06;
        trame[8] = 0x00;
        trame[9] = 0x02;
        trame[10] = 0x00;
        trame[11] = 0x01;

        QByteArray data(trame, 12);
        qDebug() << trame[0];
        socket->write(data);
        socket->flush();

        char trame2[12];
        trame2[0] = 0x00;
        trame2[1] = 0x01;
        trame2[2] = 0x00;
        trame2[3] = 0x00;
        trame2[4] = 0x00;
        trame2[5] = 0x06;
        trame2[6] = 0x11;
        trame2[7] = 0x06;
        trame2[8] = 0x00;
        trame2[9] = 0x02;
        trame2[10] = 0x00;
        trame2[11] = 0x00;

        QByteArray data2(trame2, 12);
        socket->write(data2);
        socket->flush();

    }

    if (data == "cloche2") {

        qDebug() << "cloche2";
        char trame3[12];
        trame3[0] = 0x00;
        trame3[1] = 0x01;
        trame3[2] = 0x00;
        trame3[3] = 0x00;
        trame3[4] = 0x00;
        trame3[5] = 0x06;
        trame3[6] = 0x11;
        trame3[7] = 0x06;
        trame3[8] = 0x00;
        trame3[9] = 0x02;
        trame3[10] = 0x00;
        trame3[11] = 0x02;

        QByteArray data3(trame3, 12);
        socket->write(data3);
        socket->flush();

        char trame4[12];
        trame4[0] = 0x00;
        trame4[1] = 0x01;
        trame4[2] = 0x00;
        trame4[3] = 0x00;
        trame4[4] = 0x00;
        trame4[5] = 0x06;
        trame4[6] = 0x11;
        trame4[7] = 0x06;
        trame4[8] = 0x00;
        trame4[9] = 0x02;
        trame4[10] = 0x00;
        trame4[11] = 0x00;

        QByteArray data4(trame4, 12);
        socket->write(data4);
        socket->flush();

    }


    if (data == "cloche3") {

        qDebug() << "cloche3";
        char trame5[12];
        trame5[0] = 0x00;
        trame5[1] = 0x01;
        trame5[2] = 0x00;
        trame5[3] = 0x00;
        trame5[4] = 0x00;
        trame5[5] = 0x06;
        trame5[6] = 0x11;
        trame5[7] = 0x06;
        trame5[8] = 0x00;
        trame5[9] = 0x02;
        trame5[10] = 0x00;
        trame5[11] = 0x04;

        QByteArray data5(trame5, 12);
        socket->write(data5);
        socket->flush();

        char trame6[12];
        trame6[0] = 0x00;
        trame6[1] = 0x01;
        trame6[2] = 0x00;
        trame6[3] = 0x00;
        trame6[4] = 0x00;
        trame6[5] = 0x06;
        trame6[6] = 0x11;
        trame6[7] = 0x06;
        trame6[8] = 0x00;
        trame6[9] = 0x02;
        trame6[10] = 0x00;
        trame6[11] = 0x00;

        QByteArray data6(trame6, 12);
        socket->write(data6);
        socket->flush();

    }


    if (data == "cloche4") {

        qDebug() << "cloche4";
        char trame7[12];
        trame7[0] = 0x00;
        trame7[1] = 0x01;
        trame7[2] = 0x00;
        trame7[3] = 0x00;
        trame7[4] = 0x00;
        trame7[5] = 0x06;
        trame7[6] = 0x11;
        trame7[7] = 0x06;
        trame7[8] = 0x00;
        trame7[9] = 0x02;
        trame7[10] = 0x00;
        trame7[11] = 0x08;

        QByteArray data7(trame7, 12);
        socket->write(data7);
        socket->flush();

        char trame8[12];
        trame8[0] = 0x00;
        trame8[1] = 0x01;
        trame8[2] = 0x00;
        trame8[3] = 0x00;
        trame8[4] = 0x00;
        trame8[5] = 0x06;
        trame8[6] = 0x11;
        trame8[7] = 0x06;
        trame8[8] = 0x00;
        trame8[9] = 0x02;
        trame8[10] = 0x00;
        trame8[11] = 0x00;

        QByteArray data8(trame8, 12);
        socket->write(data8);
        socket->flush();


        }

    if( data !=  "cloche1" &&  data != "cloche2" &&  data != "cloche3" &&  data != "cloche4" ) {

        qDebug() << "J'attend " + data;
        sleep_for(milliseconds(data.toInt()));

    }


}

void WebServer::onWebClientDisconnected() {

    qDebug() << "Deconexion Client";
}

WebServer::~WebServer() {
    qDebug() << "Destruction Serveur";
}

