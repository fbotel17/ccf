#include "mywebsocketserver.h"
#include <QDebug>
#include <QUdpSocket>

// Constructeur de la classe MyWebSocketServer
MyWebSocketServer::MyWebSocketServer(quint16 port, QObject* parent)
    : QObject(parent), m_pWebSocketServer(Q_NULLPTR)
{
    // Initialiser le serveur WebSocket
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Serveur WebSocket"), QWebSocketServer::NonSecureMode, this);

    // V�rifier si le serveur d�marre avec succ�s sur le port sp�cifi�
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Serveur en �coute sur le port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &MyWebSocketServer::onNewConnection);
    }
}

// Destructeur de la classe MyWebSocketServer
MyWebSocketServer::~MyWebSocketServer()
{
    // Fermer le serveur WebSocket et supprimer les clients connect�s
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

// Fonction slot appel�e lorsqu'une nouvelle connexion WebSocket est �tablie
void MyWebSocketServer::onNewConnection()
{
    // Accepter la connexion en attente et connecter les signaux aux slots appropri�s
    QWebSocket* pSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "Nouvelle connexion :" << pSocket->peerAddress().toString();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &MyWebSocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &MyWebSocketServer::socketDisconnected);

    m_clients << pSocket;
}

// Fonction slot appel�e lorsqu'un message texte est re�u d'un client WebSocket
void MyWebSocketServer::processTextMessage(const QString& message)
{
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Message re�u :" << message << "de :" << pSender->peerAddress().toString();

    if (pSender)
    {
        pSender->sendTextMessage(QStringLiteral("Le serveur a re�u votre message : %1").arg(message));
        broadcastMessage(pSender, message); // Diffuser le message � tous les clients
        sendUDPMessage(message);  // Envoyer le message via UDP � Arduino
    }
}

// Fonction slot appel�e lorsqu'un client WebSocket est d�connect�
void MyWebSocketServer::socketDisconnected()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Socket d�connect� :" << pClient->peerAddress().toString();

    if (pClient)
    {
        m_clients.removeOne(pClient);
        pClient->deleteLater();
        broadcastDisconnection(pClient); // Diffuser la d�connexion � tous les clients
    }
}

// Diffuser un message � tous les clients sauf � l'�metteur
void MyWebSocketServer::broadcastMessage(QWebSocket* sender, const QString& message)
{
    for (QWebSocket* client : qAsConst(m_clients))
    {
        if (client != sender)
        {
            qDebug() << "Diffusion du message � :" << client->peerAddress().toString();
            client->sendTextMessage(message);
        }
    }
}

// Diffuser la d�connexion � tous les clients sauf au client d�connect�
void MyWebSocketServer::broadcastDisconnection(QWebSocket* disconnectedClient)
{
    for (QWebSocket* client : qAsConst(m_clients))
    {
        if (client != disconnectedClient)
        {
            qDebug() << "Diffusion de la d�connexion � :" << client->peerAddress().toString();
            client->sendTextMessage(QStringLiteral("Utilisateur d�connect� : %1").arg(disconnectedClient->peerAddress().toString()));
        }
    }
}

// Envoyer un message via UDP � une adresse IP et un port sp�cifi�s
void MyWebSocketServer::sendUDPMessage(const QString& message)
{
    // Cr�er un socket UDP
    QUdpSocket udpSocket;
    udpSocket.writeDatagram(message.toUtf8(), QHostAddress("192.168.64.10"), 12345);
}
