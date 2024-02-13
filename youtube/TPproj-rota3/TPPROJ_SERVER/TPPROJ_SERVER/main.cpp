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

		if (serial.open(QIODevice::WriteOnly)) {
			QTextStream out(&serial);
			out << "Hello from Server!";
			serial.close();
		}
		else {
			qDebug() << "Failed to open serial port " << portInfo.portName();
		}
	}

	return a.exec();
}
