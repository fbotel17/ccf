#include <QtCore/QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QtSql/QtSql>
#include <iostream>
#include "SerialReader.h"
// ... autres inclusions d'en-t�te

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	SerialReader serialReader;
	return a.exec();
}
