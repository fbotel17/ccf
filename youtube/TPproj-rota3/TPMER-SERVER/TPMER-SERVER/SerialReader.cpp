#include "SerialReader.h"
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QtSql/QSqlQuery>

SerialReader::SerialReader()
{
    // Initialisation de la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.200");
    db.setDatabaseName("TpGPS");
    db.setUserName("root");
    db.setPassword("root");

    if (db.open()) {
        qDebug() << "Connexion à la base de donnees reussie.";
    }
    else {
        qDebug() << "Impossible de se connecter à la base de donnees.";
    }

    // Configurer le port série
    serialPort.setPortName("COM4");
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
    serialPort.setReadBufferSize(1024);

    // Connecter le slot onReadyRead au signal readyRead du port série
    connect(&serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    // Ouvrir le port série
    if (serialPort.open(QIODevice::ReadOnly)) {
        qDebug() << "Port serie ouvert.";
    }
    else {
        qDebug() << "Impossible d'ouvrir le port serie.";
    }
}

void SerialReader::onReadyRead()
{
    QByteArray data = serialPort.readAll();
    trame.append(data);
    while (trame.contains('\n')) {
        int endIndex = trame.indexOf('\n');
        QByteArray sentence = trame.left(endIndex).trimmed();
        trame.remove(0, endIndex + 1);
        processNMEASentence(sentence);
    }
}

void SerialReader::processNMEASentence(const QByteArray& sentence)
{
    if (sentence.startsWith("$GPGGA") || sentence.startsWith("$GPRMC")) {
        QList<QByteArray> parts = sentence.split(',');
        if (parts.length() >= 10) {
            QByteArray timeStr = parts[1];
            QByteArray latitudeStr = parts[2];
            QByteArray longitudeStr = parts[4];

            QTime time = QTime::fromString(timeStr.left(6), "hhmmss");
            QDate currentDate = QDate::currentDate();

            // Obtenez la date et l'heure complètes en utilisant la date actuelle et l'heure de la trame NMEA
            QDateTime currentDateTime(currentDate, time);

            QString currentDateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

            QString latitudePartBeforeComma = latitudeStr.mid(0, 2);
            QString latitudePartAfterComma = latitudeStr.mid(2);

            QString longitudePartBeforeComma = longitudeStr.mid(0, 2);
            QString longitudePartAfterComma = longitudeStr.mid(1);

            qDebug() << "Date et heure de la trame : " << currentDateTimeStr;
            qDebug() << "Latitude : " << latitudePartAfterComma;
            qDebug() << "Longitude : " << longitudePartAfterComma;
            qDebug() << "";

            // Insérer les données dans la base de données
            insertDataIntoDatabase(currentDateTimeStr, latitudePartAfterComma, longitudePartAfterComma);
        }
    }
}



void SerialReader::insertDataIntoDatabase(const QString& currentDateTimeStr, const QString& latitudeStr, const QString& longitudeStr)
{
    QSqlQuery query;
    query.prepare("INSERT INTO `trame`(`longitude`, `latitude`) VALUES (:longitude, :latitude)");

    query.bindValue(":longitude", longitudeStr);
    query.bindValue(":latitude", latitudeStr);
   

    if (query.exec()) {
        qDebug() << "Donnees inserees avec succes dans la base de donnees.";
    }
    else {
        
    }
}
