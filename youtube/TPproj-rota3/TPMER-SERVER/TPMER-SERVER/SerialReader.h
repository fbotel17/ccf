#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QtSql/QSqlDatabase>

class SerialReader : public QObject
{
    Q_OBJECT

public:
    SerialReader();

private slots:
    void onReadyRead();
    void processNMEASentence(const QByteArray& sentence);
    void insertDataIntoDatabase(const QString& currentDateTimeStr, const QString& latitudeStr, const QString& longitudeStr);

private:
    QSerialPort serialPort;
    QByteArray trame;
};

#endif // SERIALREADER_H
