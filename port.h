#ifndef PORT_H
#define PORT_H

#include <QObject>
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

class Port : public QObject
{
    Q_OBJECT
public:
    explicit Port(QObject *parent = nullptr);
    ~Port();

    QSerialPort serialPort;
    Settings settingPort;

signals:
    void finishedPort();
    void printOut(QString data);

public slots:
    void connectPort();
    void disconnectPort();
    void saveSettings(QString name, int baudRate);

    void writeToPort(QByteArray data);
    void readFromPort();

    void processPort();


private slots:


};

#endif // PORT_H
