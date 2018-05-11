#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Network protocol");

    addItemsToBoxes();
    searchPorts();

    QThread *thread = new QThread;
    Port *port = new Port();

    port->moveToThread(thread);
    port->serialPort.moveToThread(thread);

    connect(port, SIGNAL(printOut(QString)),
            this, SLOT(printToConsole(QString)));
    connect(thread, SIGNAL(started()),
            port, SLOT(processPort()));
    connect(port, SIGNAL(finishedPort()),
            thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()),
            port, SLOT(deleteLater()));
    connect(port, SIGNAL(finishedPort()),
            thread, SLOT(deleteLater()));

    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonSearch_clicked()
{
    searchPorts();
}

void MainWindow::searchPorts()
{
    ui->boxPortName->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->boxPortName->addItem(info.portName());
    }
}

void MainWindow::addItemsToBoxes()
{
    ui->boxBaudrate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->boxBaudrate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->boxBaudrate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->boxBaudrate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
}

void MainWindow::sendToPort()
{
    if (port.serialPort.isOpen())
    {
        QString protocol;
        QByteArray data;

        protocol = ui->lineDestination->text() + ui->lineSource->text();
        data = protocol.toLocal8Bit().toHex();

        port.writeToPort(data);
        printToConsole(protocol);
        printToConsole(data);
    }
}

void MainWindow::printToConsole(QString data)
{
    ui->console->textCursor().insertText(data + '\r');
    ui->console->moveCursor(QTextCursor::End);
}

void MainWindow::on_buttonConnect_clicked()
{
    port.saveSettings(ui->boxPortName->currentText(),
                      ui->boxBaudrate->currentText().toInt());
    port.connectPort();
}

void MainWindow::on_buttonDisconnect_clicked()
{
    port.disconnectPort();
}

void MainWindow::on_buttonSend_clicked()
{
    sendToPort();
}
