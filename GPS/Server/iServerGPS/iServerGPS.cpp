//**********************************************************************************************//
//* Programme	:	iServerGPS.cpp																//
//*																	Date : 03/03/2022			//
//*																	Last update : 08/03/2022	//
//*---------------------------------------------------------------------------------------------//
//* Developper	:	CAUET Clément																//
//*---------------------------------------------------------------------------------------------//
//*																								//
//* Goal		:	Receive values of the iServer-GPS and send them to database					//
//*																								//
//**********************************************************************************************//

#include "iServerGPS.h"

/* Constructeur */
iServerGPS::iServerGPS(quint16 wsport, quint16 tcpport)
{

	this->wsport	= wsport;
	this->tcpport	= tcpport;

	this->timer = new QTimer(this);

	this->webSocketServer = new QWebSocketServer(QStringLiteral("Server WebSocket"), QWebSocketServer::NonSecureMode);

	if (this->webSocketServer->listen(QHostAddress::AnyIPv4, this->wsport))
	{
		qDebug() << "Server WebSocket: Nouvelle connexion sur le port " << this->wsport << "\n";

		QObject::connect(webSocketServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
	}
	else
	{
		qDebug() << "Server WebSocket: Erreur d'ecoute sur le port " << this->wsport << "\n";
	}

}

/* Destructeur */
iServerGPS::~iServerGPS()
{
	webSocketServer->close();

	QObject::disconnect(serialPort, nullptr, nullptr, nullptr);
}

/* New WebSocket Client Connection */
void iServerGPS::onNewConnection()
{
	wsSocket = this->webSocketServer->nextPendingConnection();

	QObject::connect(wsSocket, SIGNAL(textMessageReceived(const QString&)), this, SLOT(processTextMessage(const QString&)));

	QObject::connect(wsSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

	this->wsclients.push_back(wsSocket);
}

/* WebSocket Client Déconnexion */
void iServerGPS::socketDisconnected()
{

	this->timer->stop();

	qDebug() << "Server WebSocket: Deconnexion\n";

}

/* Receive message from WebSocket Client */
void iServerGPS::processTextMessage(const QString & message)
{

	if (message.section(";", 0, 0) == "connection")
	{

		serverName			= message.section(";", 1, 1);
		QString hostName	= message.section(";", 2, 2);
		QString userName	= message.section(";", 3, 3);
		QString password	= message.section(";", 4, 4);
		QString dbName		= message.section(";", 5, 5);

		dbInit(hostName, userName, password, dbName);

	}
	else if (message.section(";", 0, 0) == "serial")
	{

		this->serialPort = new QSerialPort(this);

		this->serialPort->setPortName("COM8");
		this->serialPort->open(QIODevice::ReadWrite);
		this->serialPort->setBaudRate(QSerialPort::Baud9600);
		this->serialPort->setDataBits(QSerialPort::DataBits::Data8);
		this->serialPort->setParity(QSerialPort::Parity::NoParity);
		this->serialPort->setStopBits(QSerialPort::StopBits::OneStop);
		this->serialPort->setFlowControl(QSerialPort::NoFlowControl);

		qDebug() << "TCP: Nouvelle connexion sur le port Serie\n";

		QObject::connect(this->serialPort, SIGNAL(readyRead()), this, SLOT(onSerialReadyRead()));

	}
	else if (message.section(";", 0, 0) == "tcp")
	{

		this->tcpSocket = new QTcpSocket(this);

		this->tcpSocket->connectToHost(QHostAddress("192.168.65.141"), this->tcpport);

		if (this->tcpSocket->state()) 
		{
			qDebug() << "TCP: Nouvelle connexion sur le port " << this->tcpport << "\n";

			QObject::connect(this->tcpSocket, SIGNAL(readyRead()), this, SLOT(onTCPReadyRead()));
		}
		else
		{
			qDebug() << "TCP: Erreur de connexion sur le port " << this->tcpport << "\n";
		}

	}
	else
	{
		qDebug() << "Server WebSocket: Protocol message error\n";
	}

}

/* Receive message from SerialPort */
void iServerGPS::onSerialReadyRead()
{

	trame = this->serialPort->readAll();
	data = data + trame.toStdString().c_str();

	processTrame(data);

}

/* Receive message from TCP */
void iServerGPS::onTCPReadyRead()
{

	trame = this->tcpSocket->readAll();
	data = data + trame.toStdString().c_str();

	processTrame(data);

}

/* Process the trame receive */
void iServerGPS::processTrame(QString data)
{

	QRegExp regExpGPS("\\$GPGGA([^\*]\*)");
	if (regExpGPS.indexIn(data) > -1) 
	{

		QStringList resDataListGPS = regExpGPS.capturedTexts();
		QString resDataGPS = resDataListGPS[0];
		QString gps = resDataGPS.left(resDataGPS.size());
		dataListGPS = gps.split(QLatin1Char(','), Qt::SkipEmptyParts);

		if (dataListGPS.size() == 15)
		{

			longitude = dataListGPS[2];
			latitude = dataListGPS[4];

			int longitudeDot = longitude.indexOf(".");
			longitude.insert(longitudeDot - 2, ",");
			QStringList longitudeSplit = longitude.split(",");
 
			double longitudeIntegerDivide = longitudeSplit.at(1).toDouble() / 60;

			double longitudeDecimalDivide = longitudeSplit.at(0).toDouble();
			double longitudeRes = longitudeIntegerDivide + longitudeDecimalDivide;

			if (dataListGPS[5] == 'O') {
				longitudeRes = longitudeRes * (-1);
			}

			int latitudeDot = latitude.indexOf(".");
			latitude.insert(latitudeDot - 2, ",");
			QStringList latitudeSplit = latitude.split(",");

			double latitudeIntegerDivide = latitudeSplit.at(1).toDouble() / 60;

			double latitudeDecimalDivide = latitudeSplit.at(0).toDouble();
			double latitudeRes = latitudeIntegerDivide + latitudeDecimalDivide;

			if (dataListGPS[3] == 'S') {
				latitudeRes = latitudeRes * (-1);
			}

			longitude = QString::number(longitudeRes);
			latitude = QString::number(latitudeRes);

			if (!(this->timer->isActive())) 
			{
				timerOn();
			}

		}

	}
}

/* Init bdd */
void iServerGPS::dbInit(QString hostName, QString userName, QString password, QString dbName)
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(hostName);
	db.setUserName(userName);
	db.setPassword(password);
	db.setDatabaseName(dbName);

	if (db.open()) 
	{

		qDebug() << "Database: New Connection\n";

		selectValue();

	}
	else 
	{
		qDebug() << db.lastError();
	}

}

/* Start timer of the sampling */
void iServerGPS::timerOn()
{

	QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(insertValue()));

	this->timer->start(10000);

}

/* Recuperation of iServerGPS values and send them to database */
void iServerGPS::insertValue()
{

	QSqlQuery query;
	query.prepare("INSERT INTO `iServerGPS`(`latitude`, `longitude`, `date`) VALUES(:latitude, :longitude, CURDATE())");
	query.bindValue(":latitude", latitude);
	query.bindValue(":longitude", longitude);
	query.exec();

	query.exec("SELECT `id`, `latitude`, `longitude`, DATE_FORMAT(`date`, '%H:%i:%s %d/%m/%Y') FROM `iServerGPS` ORDER BY `date` DESC");

	if (query.next())
	{
		QString id			= query.value(0).toString();
		QString latitude	= query.value(1).toString();
		QString longitude	= query.value(2).toString();
		QString date		= query.value(3).toString();

		QString sendText = id + ";" + latitude + ";" + longitude + ";" + date;

		for (QList<QWebSocket*>::iterator it = wsclients.begin(); it != wsclients.end(); it++) {
			(*it)->sendTextMessage(sendText);
		}
	}
}

/* Send	values at WebSocket Client */
void iServerGPS::selectValue()
{
	QSqlQuery query;
	query.exec("SELECT `id`, `latitude`, `longitude`, DATE_FORMAT(`date`, '%H:%i:%s %d/%m/%Y') FROM `iServerGPS` ORDER BY `date` ASC");

	while (query.next())
	{
		QString id = query.value(0).toString();
		QString latitude = query.value(1).toString();
		QString longitude = query.value(2).toString();
		QString date = query.value(3).toString();

		QString sendText = id + ";" + latitude + ";" + longitude + ";" + date;

		wsSocket->sendTextMessage(sendText);
	}

}