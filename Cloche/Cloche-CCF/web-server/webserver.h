#ifndef WEBSERVER_H
#define WEBSERVER_H
#pragma once

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QtWebSockets/QtWebSockets>
#include <QTimer>
#include <chrono>
#include <thread>
#include <QTimer>


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)


class WebServer : public QObject {

    Q_OBJECT

public:
    WebServer(QObject *parent = Q_NULLPTR);
    ~WebServer();

    QTcpSocket * socket;
    QTimer * timer;

private:
    QWebSocketServer *webServer;
    QWebSocket * obj;



public slots:
    void onWebServerNewConnection();
    void onWebClientDisconnected();
    void onWebClientCommunication(QString entryMessage);
};


#endif // WEBSERVER_H
