#include "port.h"

Port::Port(QObject *parent) : QObject(parent)
{

}

Port::~Port()
{
    emit finishedPort();
}

void Port::connectPort()
{
    serialPort.setPortName(settingPort.name);

    if (serialPort.open(QIODevice::ReadWrite))
    {
        if (serialPort.setBaudRate(settingPort.baudRate))
        {
            if (serialPort.isOpen())
            {
                qDebug() << "Port is open";
            }
            else
            {
                serialPort.close();
                qDebug() << "Port is close";
            }
        }
        else
        {
            serialPort.close();
            qDebug() << "Port is close";
        }
    }
}

void Port::disconnectPort()
{
    if(serialPort.isOpen())
    {
        serialPort.close();
        qDebug() << "Disconnect";
    }
}

void Port::saveSettings(QString name, int baudRate)
{
    settingPort.name = name;
    settingPort.baudRate = baudRate;
}

void Port::writeToPort(QByteArray data)
{
    if (serialPort.isOpen())
        serialPort.write(data);
}

void Port::readFromPort()
{
    QByteArray data;
    data.append(serialPort.readAll());

    printOut(data);
}

void Port::processPort()
{
    connect(&serialPort, SIGNAL(readyRead()),this,SLOT(readFromPort()));
}
