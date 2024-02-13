

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

class MyWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit MyWebSocketServer(quint16 port, QObject* parent = Q_NULLPTR);
    ~MyWebSocketServer();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(const QString& message);
    void socketDisconnected();
    void broadcastMessage(QWebSocket* sender, const QString& message);
    void broadcastDisconnection(QWebSocket* disconnectedClient);
    void sendUDPMessage(const QString& message);

private:
    QWebSocketServer* m_pWebSocketServer;
    QList<QWebSocket*> m_clients;
};

