// main.cpp
#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();

	for (const QSerialPortInfo &portInfo : portList) {
		QSerialPort serial;
		serial.setPort(portInfo);
		serial.setBaudRate(QSerialPort::Baud9600);

		if (serial.open(QIODevice::ReadOnly)) {
			if (serial.waitForReadyRead(3000)) {  // Attendez les données pendant 3 secondes
				QByteArray data = serial.readAll();
				QTextStream stream(data);
				QString receivedData = stream.readAll();
				qDebug() << "Received data from port " << portInfo.portName() << ": " << receivedData;
			}
			else {
				qDebug() << "Timeout while waiting for data on port " << portInfo.portName();
			}

			serial.close();
		}
		else {
			qDebug() << "Failed to open serial port " << portInfo.portName();
		}
	}

	return a.exec();
}
