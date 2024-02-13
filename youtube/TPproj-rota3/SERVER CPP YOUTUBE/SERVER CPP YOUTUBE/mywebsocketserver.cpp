#include "mywebsocketserver.h"
#include <QDebug>

MyWebSocketServer::MyWebSocketServer(quint16 port, QObject* parent)
    : QObject(parent), m_pWebSocketServer(Q_NULLPTR)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"), QWebSocketServer::NonSecureMode, this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &MyWebSocketServer::onNewConnection);
    }
}

MyWebSocketServer::~MyWebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void MyWebSocketServer::onNewConnection()
{
    QWebSocket* pSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "New connection:" << pSocket->peerAddress().toString();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &MyWebSocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &MyWebSocketServer::socketDisconnected);

    m_clients << pSocket;
}

void MyWebSocketServer::processTextMessage(const QString& message)
{
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Message received:" << message << "from:" << pSender->peerAddress().toString();

    if (pSender)
    {
        pSender->sendTextMessage(QStringLiteral("Server received your message: %1").arg(message));
        broadcastMessage(pSender, message); // Broadcast the message to all clients
    }
}

void MyWebSocketServer::socketDisconnected()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Socket disconnected:" << pClient->peerAddress().toString();

    if (pClient)
    {
        m_clients.removeOne(pClient);
        pClient->deleteLater();
        broadcastDisconnection(pClient); // Broadcast disconnection to all clients
    }
}

void MyWebSocketServer::broadcastMessage(QWebSocket* sender, const QString& message)
{
    for (QWebSocket* client : qAsConst(m_clients))
    {
        if (client != sender)
        {
            qDebug() << "Broadcasting message to:" << client->peerAddress().toString();
            client->sendTextMessage(message);
        }
    }
}


void MyWebSocketServer::broadcastDisconnection(QWebSocket* disconnectedClient)
{
    for (QWebSocket* client : qAsConst(m_clients))
    {
        if (client != disconnectedClient)
        {
            qDebug() << "Broadcasting disconnection to:" << client->peerAddress().toString();
            client->sendTextMessage(QStringLiteral("User disconnected: %1").arg(disconnectedClient->peerAddress().toString()));
        }
    }
}
