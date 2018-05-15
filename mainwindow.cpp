#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Network protocol");
    this->addItemsToBoxes();
    this->searchPorts();
//    this->test();

    connect(&serialPort, SIGNAL(readyRead()),
            this, SLOT(readFromPort()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToPort()
{
    serialPort.setPortName(settings.name);

    if (serialPort.open(QIODevice::ReadWrite))
    {
        if (serialPort.isOpen())
        {
            qDebug() << "Open";
            ui->lineEditStatus->setText("Connect");
        }

        else
            qDebug() << "Close";
    }
}

void MainWindow::disconnectFromPort()
{
    if (serialPort.isOpen())
    {
        serialPort.close();
        qDebug() << "Close";
        ui->lineEditStatus->setText("Disconnect");
    }
}

void MainWindow::writeToPort()
{
    if (serialPort.isOpen())
    {
        QString text = ui->lineEdit->text();

        serialPort.write(text.toLocal8Bit());
    }
}

void MainWindow::readFromPort()
{
    QByteArray data;
    data.append(serialPort.readAll());

    ui->lineEdit_2->setText(data);


}

void MainWindow::searchPorts()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->boxPortName->addItem(info.portName());
    }
}

void MainWindow::saveSettings()
{
    settings.name = ui->boxPortName->currentText();
    settings.baudRate = ui->boxBaudrate->currentText().toInt();
}

void MainWindow::prepareMessage()
{
    QString message;

    destination = ui->lineEditDestination->text().toInt();
    qDebug() << QString(destination, 4);
    source = ui->lineEditSource->text().toInt();

//    message = QString::number(destination, 2) +
//              QString::number(source, 2);

//    QByteArray data = message.toLower().toLocal8Bit();
    ui->lineEdit_3->setText(message);
}

void MainWindow::test()
{
    ui->lineEditDestination->setInputMask("bbbb.bbbb");
    ui->lineEditDestination->setMaxLength(8);
}

void MainWindow::addItemsToBoxes()
{
    ui->boxBaudrate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->boxBaudrate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->boxBaudrate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->boxBaudrate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
}

void MainWindow::on_buttonConnect_clicked()
{
    this->saveSettings();
    this->connectToPort();
}

void MainWindow::on_buttonDisconnect_clicked()
{
    this->disconnectFromPort();
}

void MainWindow::on_buttonSearchPorts_clicked()
{
    this->searchPorts();
}

void MainWindow::on_pushButton_clicked()
{
    this->prepareMessage();
}

void MainWindow::on_pushButton_2_clicked()
{
    writeToPort();
}
