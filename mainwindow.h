#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>

#include "port.h"

//struct Settings
//{
//    QString name;
//    qint32 baudRate;
//    QSerialPort::DataBits dataBits;
//    QSerialPort::Parity parity;
//    QSerialPort::StopBits stopBits;
//    QSerialPort::FlowControl flowControl;
//};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void searchPorts();
    void addItemsToBoxes();

    void sendToPort();
    void printToConsole(QString data);

    void on_buttonSearch_clicked();
    void on_buttonConnect_clicked();
    void on_buttonDisconnect_clicked();

    void on_buttonSend_clicked();

private:
    Ui::MainWindow *ui;

    Port port;
};

#endif // MAINWINDOW_H
