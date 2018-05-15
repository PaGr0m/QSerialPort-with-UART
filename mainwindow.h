#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

struct Settings
{
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectToPort();
    void disconnectFromPort();

    void writeToPort();
    void readFromPort();

    void addItemsToBoxes();
    void searchPorts();
    void saveSettings();

    void prepareMessage();
    void test();


private slots:
    void on_buttonConnect_clicked();
    void on_buttonSearchPorts_clicked();

    void on_buttonDisconnect_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort serialPort;
    Settings settings;

    qint8 start;
    qint8 destination;
    qint8 source;
    qint8 length;
    qint8 end;
    qint32 data;

};

#endif // MAINWINDOW_H
