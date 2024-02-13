#pragma once

#include <QObject>
#include <qdebug.h>

#include <QSqlDatabase>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include <QtSql>

#include <QWebSocket>
#include <QWebSocketServer>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSerialPort>

#include <QFile>
#include <QTextStream>
#include <QRegExp>

class iServerGPS : public QObject
{
	Q_OBJECT

		QWebSocketServer *webSocketServer;
		QWebSocket * wsSocket;
		QList<QWebSocket*> wsclients;

		QTcpSocket * tcpSocket;

		QSerialPort * serialPort;

public:

	/* Constructeur */
	iServerGPS(quint16 wsport, quint16 tcpport);

	/* Destructeur */
	~iServerGPS();

	/* Initialisation database */
	void dbInit(QString hostName, QString userName, QString password, QString dbName);

private slots:

	/* New WebSocket Client Connection */
	void onNewConnection();

	/* WebSocket Client Disconnection */
	void socketDisconnected();

	/* Receive message of WebSocket Client */
	void processTextMessage(const QString& message);

	/* Receive message from SerialPort */
	void onSerialReadyRead();

	/* Receive message from TCP */
	void onTCPReadyRead();

	/* Process the trame receive */
	void processTrame(QString data);

	/* Start timer of the sampling */
	void timerOn();

	/* Recuperation of four values and send them to database */
	void insertValue();

	/* Send	values at WebSocket Client */
	void selectValue();

private:

	QString serverName;

	QSqlDatabase db;

	QByteArray trame;
	QString data;
	QStringList dataListGPS;

	QTimer *timer;

	QString latitude;
	QString longitude;

	quint16 wsport;
	quint16 tcpport;

};


