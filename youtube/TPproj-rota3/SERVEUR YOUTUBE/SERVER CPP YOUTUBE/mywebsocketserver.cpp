#include "mywebsocketserver.h"
#include <QDebug>
#include <QUdpSocket>

// Constructeur de la classe MyWebSocketServer
MyWebSocketServer::MyWebSocketServer(quint16 port, QObject* parent)
    : QObject(parent), m_pWebSocketServer(Q_NULLPTR)
{
    // Initialiser le serveur WebSocket
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Serveur WebSocket"), QWebSocketServer::NonSecureMode, this);

    // Vérifier si le serveur démarre avec succès sur le port spécifié
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Serveur en écoute sur le port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &MyWebSocketServer::onNewConnection);
    }
}

// Destructeur de la classe MyWebSocketServer
MyWebSocketServer::~MyWebSocketServer()
{
    // Fermer le serveur WebSocket et supprimer les clients connectés
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

// Fonction slot appelée lorsqu'une nouvelle connexion WebSocket est établie
void MyWebSocketServer::onNewConnection()
{
    // Accepter la connexion en attente et connecter les signaux aux slots appropriés
    QWebSocket* pSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "Nouvelle connexion :" << pSocket->peerAddress().toString();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &MyWebSocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &MyWebSocketServer::socketDisconnected);

    m_clients << pSocket;
}

// Fonction slot appelée lorsqu'un message texte est reçu d'un client WebSocket
void MyWebSocketServer::processTextMessage(const QString& message)
{
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Message reçu :" << message << "de :" << pSender->peerAddress().toString();

    if (pSender)
    {
        pSender->sendTextMessage(QStringLiteral("Le serveur a reçu votre message : %1").arg(message));
        broadcastMessage(pSender, message); // Diffuser le message à tous les clients
        sendUDPMessage(message);  // Envoyer le message via UDP à Arduino
    }
}

// Fonction slot appelée lorsqu'un client WebSocket est déconnecté
void MyWebSocketServer::socketDisconnected()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Socket déconnecté :" << pClient->peerAddress().toString();

    if (pClient)
    {
        m_clients.removeOne(pClient);
        pClient->deleteLater();
        broadcastDisconnection(pClient); // Diffuser la déconnexion à tous les clients
    }
}

// Diffuser un message à tous les clients sauf à l'émetteur
void MyWebSocketServer::broadcastMessage(QWebSocket* sender, const QString& message)
{
    for (QWebSocket* client : qAsConst(m_clients))
    {
        if (client != sender)
        {
            qDebug() << "Diffusion du message à :" << client->peerAddress().toString();
            client->sendTextMessage(message);
        }
    }
}

// Diffuser la déconnexion à tous les clients sauf au client déconnecté
void MyWebSocketServer::broadcastDisconnection(QWebSocket* disconnectedClient)
{
    for (QWebSocket* client : qAsConst(m_clients))
    {
        if (client != disconnectedClient)
        {
            qDebug() << "Diffusion de la déconnexion à :" << client->peerAddress().toString();
            client->sendTextMessage(QStringLiteral("Utilisateur déconnecté : %1").arg(disconnectedClient->peerAddress().toString()));
        }
    }
}

// Envoyer un message via UDP à une adresse IP et un port spécifiés
void MyWebSocketServer::sendUDPMessage(const QString& message)
{
    // Créer un socket UDP
    QUdpSocket udpSocket;
    udpSocket.writeDatagram(message.toUtf8(), QHostAddress("192.168.64.10"), 12345);
}
