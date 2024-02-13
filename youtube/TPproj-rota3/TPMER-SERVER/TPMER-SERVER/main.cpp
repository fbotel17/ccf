#include <QtCore/QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QThread>
#include <QObject>

class SerialReader : public QObject
{
	Q_OBJECT

public slots:
	void onReadyRead()
	{
		QByteArray data = serialPort.readAll();
		trame.append(data);
		if (trame.contains('\n')) {
			int endIndex = trame.indexOf('\n');
			qDebug().noquote() << "Trame recue : " << trame.left(endIndex);
			trame.remove(0, endIndex + 1);
		}
	}



private:
	QSerialPort serialPort;
	QByteArray trame; // D�claration de la variable pour stocker la trame

public:
	SerialReader()
	{
		// Sp�cifiez le nom du port s�rie (v�rifiez le nom du port Arduino sur votre ordinateur)
		serialPort.setPortName("COM3"); // Remplacez "COM1" par le nom de votre port s�rie

		// Configurez le d�bit en bauds, les bits de donn�es, la parit�, le nombre de bits d'arr�t, etc.
		serialPort.setBaudRate(QSerialPort::Baud9600);
		serialPort.setDataBits(QSerialPort::Data8);
		serialPort.setParity(QSerialPort::NoParity);
		serialPort.setStopBits(QSerialPort::OneStop);
		serialPort.setFlowControl(QSerialPort::NoFlowControl);
		serialPort.setReadBufferSize(1024);


		connect(&serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

		// Ouvrez le port s�rie
		if (serialPort.open(QIODevice::ReadOnly)) {
			qDebug() << "Port serie ouvert.";
		}
		else {
			qDebug() << "Impossible d ouvrir le port serie.";
		}
	}
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SerialReader serialReader;

	return a.exec();
}

#include "main.moc"
