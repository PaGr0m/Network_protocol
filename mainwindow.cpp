#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    searchPorts();

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
