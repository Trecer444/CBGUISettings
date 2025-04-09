#include "connectionsettings.h"
#include "ui_connectionsettings.h"


ConnectionSettings::ConnectionSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);

    //title
    QWidget::setWindowTitle("Настройки COM порта");

    //ports
    QList<QSerialPortInfo> serialPorts = serialPortInfo.availablePorts();
    QList<QString> stringPorts;
    for (int i = 0; i < serialPorts.size(); i++)
    {
        stringPorts.append(serialPorts.at(i).portName());
    }
    ui->comboBoxPorts->addItems(stringPorts);


    //прописать вычитывание настроек из settings

}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;
}

void ConnectionSettings::on_buttonBox_accepted()
{
    //прописать сохранение настроек

    singletonSettings* settings = singletonSettings::getInstance();

    settings->serialPortName = ui->comboBoxPorts->currentText();
    settings->serialBoudRate = ui->comboBoxBoudrate->currentText();
    settings->serialDataBits = ui->comboBoxDataBits->currentText().toInt();
    settings->serialStopBits = ui->comboBoxStopBits->currentText();
    settings->serialFlowControl = ui->comboBoxFlowControl->currentText();
    settings->serialCode = ui->textEditCode->toPlainText();
    this->close();
}


void ConnectionSettings::on_buttonBox_rejected()
{
    //прописать отмену настроек
    this->close();
}


void ConnectionSettings::on_pushButton_2_clicked()
{
    //QList<QSerialPortInfo> ports = info;
    ui->comboBoxPorts->clear();
    QList<QSerialPortInfo> serialPorts = serialPortInfo.availablePorts();
    QList<QString> stringPorts;
    for (int i = 0; i < serialPorts.size(); i++)
    {
        stringPorts.append(serialPorts.at(i).portName());
    }
    ui->comboBoxPorts->addItems(stringPorts);
}

