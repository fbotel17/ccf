#include <QtCore/QCoreApplication>
#include <QSettings>
#include "iServerGPS.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QSettings *settings = new QSettings("config.ini", QSettings::IniFormat);

	QStringList list = settings->allKeys();

	if (!settings->contains("WS/port") && !settings->contains("TCP/port"))
	{
		settings->beginGroup("WS");
		settings->setValue("port", "3006");
		settings->endGroup();
		settings->sync();

		settings->beginGroup("TCP");
		settings->setValue("port", "3007");
		settings->endGroup();
		settings->sync();
	}

	int wsport = settings->value("WS/port", "config").toInt();
	int tcpport = settings->value("TCP/port", "config").toInt();

	new iServerGPS(wsport, tcpport);

	return a.exec();
}

