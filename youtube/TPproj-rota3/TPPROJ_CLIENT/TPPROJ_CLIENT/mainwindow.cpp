// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	serial = new QSerialPort(this);
	serial->setPortName("COM1");  // Remplacez "COM1" par le port série approprié
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->open(QIODevice::WriteOnly);
}

MainWindow::~MainWindow()
{
	delete ui;
	serial->close();
}

void MainWindow::on_sendButton_clicked()
{
	QString data = ui->lineEdit->text();
	serial->write(data.toUtf8());
}
