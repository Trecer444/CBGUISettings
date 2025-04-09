#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <stdio.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    singletonSettings* settings = singletonSettings::getInstance();
    settings = singletonSettings::getInstance();

    //работа с портами КОМ
    QList<QSerialPortInfo> serialPorts = serialPortInfo.availablePorts();
    QList<QString> stringPorts;
    for (int i = 0; i < serialPorts.size(); i++)
    {
        stringPorts.append(serialPorts.at(i).portName());
    }
    ui->comboBoxCOMPortsMain->addItems(stringPorts);
    settings->serialPortName = ui->comboBoxCOMPortsMain->currentText();

    //заполняем поле "источник сигнала"
    int typeIndex = 0;
    for (QString s : inputTypeRU)
    {
        ui->comboBoxSignal->addItem(inputTypeRU[typeIndex]);
        typeIndex++;
    }

    //прячем все настройки
    hideCh(ui);

    settings->readParamsFromJSON();
    for (int i = 0; i < ui->comboBoxCOMPortsMain->count(); i++)
    {
        if (QString::compare(ui->comboBoxCOMPortsMain->currentText(), settings->serialPortName, Qt::CaseInsensitive))
        {
            ui->comboBoxCOMPortsMain->setCurrentIndex(i);
            break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectionSettingsBtn_triggered()
{
    ConnectionSettings _connectionSettings;
    _connectionSettings.exec();

    QList<QSerialPortInfo> serialPorts = serialPortInfo.availablePorts();
    QList<QString> stringPorts;
    for (int i = 0; i < serialPorts.size(); i++)
    {
        stringPorts.append(serialPorts.at(i).portName());
    }
    ui->comboBoxCOMPortsMain->clear();
    ui->comboBoxCOMPortsMain->addItems(stringPorts);

    singletonSettings* settings = singletonSettings::getInstance();


    int currentPort = ui->comboBoxCOMPortsMain->findText(settings->serialPortName);
    if (currentPort != -1)
    {
        ui->comboBoxCOMPortsMain->setCurrentIndex(currentPort);
    }
    else
    {
        ui->comboBoxCOMPortsMain->setCurrentIndex(0);
    }


}


void hideCh(Ui::MainWindow* ui)
{
    ui->checkBoxEngineOn->hide();           //только при работающем двигателе
    ui->checkBoxTimer->hide();              //выключение по таймеру
    ui->timeOutWidget->hide();              //выбор времени выключения по таймеру
    ui->checkBoxVCutoff->hide();          //выключение по напряжениею
    ui->vCutOffWidget->hide();              //минимальное напряжение отключения
    ui->pwmWidget->hide();                  //ШИМ
    ui->checkBoxDelayOff->hide();           //выключение с задержкой
    ui->delayWidget->hide();                //выбор времени выключения
    ui->checkBoxFlash->hide();              //моргать
    ui->flashWidget->hide();                //выбор параметров моргания
    ui->heaterWidget->hide();               //подогрев
    ui->currentControlWidget->hide();       //ограничение тока
    ui->checkBoxVCutoffAutoEn->hide();      //автоматическое включение
    ui->vCutOffAutoEnWidget->hide();        //напряжение автоматического включения

}


void MainWindow::updateState()
{
    hideCh(ui);
    switch(ui->comboBoxSignal->currentIndex())
    {
    case 0: //Отключено
        break;
    case 1: //Зажигание
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxTimer->show();        //выключение по таймеру
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->currentControlWidget->show();
        break;
    case 2: //Постоянный потребитель
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        // ui->checkBoxTimer->show();     //выключение по таймеру
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->currentControlWidget->show();
        break;
    case 3: //Ближний свет
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 4: //Дальний свет
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 5: //Любой свет
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 6: //Поворотники
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 7://Левый поворотник
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 8://Правый поворотник
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 9://Аварийка
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();
        break;
    case 10://подогрев
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->heaterWidget->show();         //подогрев
        ui->currentControlWidget->show();
        break;
    case 11://стопы
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxFlash->show();        //моргать
        ui->currentControlWidget->show();

        break;
    default:
        break;
    }
}

void MainWindow::on_comboBoxSignal_currentIndexChanged(int index)
{
    updateState();
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].signalSource = index; //сохраняем в конфиг текущий выбранный параметр источника сигнала
}


void MainWindow::on_checkBoxEngineOn_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    if (ui->checkBoxEngineOn->isChecked())
    {
        settings->chParams[ui->comboBoxChNumber->currentIndex()].engineOn = true; //только при раб двиг
    }
    else
    {
        settings->chParams[ui->comboBoxChNumber->currentIndex()].engineOn = false; //только при раб двиг
    }
}


void MainWindow::on_checkBoxTimer_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimer = ui->checkBoxTimer->isChecked(); //таймер

    if (ui->checkBoxTimer->isChecked())
    {
        ui->timeOutWidget->show();
    }
    else
    {
        ui->timeOutWidget->hide();
    }
}


void MainWindow::on_checkBoxVCutoffOn_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOff = ui->checkBoxVCutoff->isChecked();
    if (ui->checkBoxVCutoff->isChecked())
    {
        ui->vCutOffWidget->show();
    }
    else
    {
        ui->vCutOffWidget->hide();
    }
}


void MainWindow::on_checkBoxVCutoffAutoEn_stateChanged(int arg1)
{
     singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].vAutoEn = ui->checkBoxVCutoffAutoEn->isChecked();
    if (ui->checkBoxVCutoffAutoEn->isChecked())
    {
        ui->vCutOffAutoEnWidget->show();
    }
    else
    {
        ui->vCutOffAutoEnWidget->hide();
    }
}


void MainWindow::on_checkBoxDelayOff_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimer = ui->checkBoxDelayOff->isChecked();
    if (ui->checkBoxDelayOff->isChecked())
    {
        ui->delayWidget->show();
    }
    else
    {
        ui->delayWidget->hide();
    }
}


void MainWindow::on_checkBoxFlash_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flash = ui->checkBoxFlash->isChecked();
    if (ui->checkBoxFlash->isChecked())
    {
        ui->flashWidget->show();
    }
    else
    {
        ui->flashWidget->hide();
    }
}


void MainWindow::on_checkBoxVCutoff_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOff = ui->checkBoxVCutoff->isChecked();
    if (ui->checkBoxVCutoff->isChecked())
    {
        ui->vCutOffWidget->show();
        ui->checkBoxVCutoffAutoEn->show();
        if (ui->checkBoxVCutoffAutoEn->isChecked())
        {
            ui->vCutOffAutoEnWidget->show();
        }
        else
        {
            ui->vCutOffAutoEnWidget->hide();
        }
    }
    else
    {
        ui->vCutOffWidget->hide();
        ui->checkBoxVCutoffAutoEn->hide();
        ui->vCutOffAutoEnWidget->hide();
    }
}


void MainWindow::on_timeEditTOff_userTimeChanged(const QTime &time)
{
    singletonSettings* settings = singletonSettings::getInstance();
    QTime timeOff = ui->timeEditTOff->time();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimerValue = timeOff.hour()*3600 + timeOff.minute()*60 + timeOff.second();

}


void MainWindow::on_doubleSpinBoxVCutOff_valueChanged(double arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();

    ui->doubleSpinBoxVCuAutoEn->setMinimum(ui->doubleSpinBoxVCutOff->value() + 0.2);
    if (ui->doubleSpinBoxVCuAutoEn->value() < ui->doubleSpinBoxVCuAutoEn->minimum())
    {
        ui->doubleSpinBoxVCuAutoEn->setValue(ui->doubleSpinBoxVCuAutoEn->minimum());
    }
    settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOffValue = (int)(ui->doubleSpinBoxVCutOff->value()*100);
}


void MainWindow::on_checkBoxPWM_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].pwm = ui->checkBoxPWM->isChecked();
}


void MainWindow::on_spinBoxPWM_valueChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].pwmValue = ui->spinBoxPWM->value();
}


void MainWindow::on_checkBoxCurrent_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].currCutOff = ui->checkBoxCurrent->isChecked();
}


void MainWindow::on_doubleSpinBoxCurrent_valueChanged(double arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].currCutOffValue = (int) (ui->doubleSpinBoxCurrent->value() * 100);
}


void MainWindow::on_timeEditDelay_userTimeChanged(const QTime &time)
{
    singletonSettings* settings = singletonSettings::getInstance();
    QTime timeOff = ui->timeEditDelay->time();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimerValue = timeOff.hour()*3600 + timeOff.minute()*60 + timeOff.second();
}


void MainWindow::on_radioButtonStrob_clicked()
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flashType = 1;
    ui->label_2->show();
}


void MainWindow::on_radioButtonFew_clicked()
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flashType = 2;
    ui->label_2->hide();
}


void MainWindow::on_doubleSpinBoxFrequency_valueChanged(double arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flashFreq = (int) (ui->doubleSpinBoxFrequency->value() * 100);
}


void MainWindow::on_spinBoxNumFlash_valueChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flashCount = ui->spinBoxNumFlash->value();
}


void MainWindow::on_spinBoxHeater1_valueChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].heater1 = ui->spinBoxHeater1->value();
}


void MainWindow::on_spinBoxHeater2_valueChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].heater2 = ui->spinBoxHeater2->value();
}



void MainWindow::on_doubleSpinBoxVCuAutoEn_valueChanged(double arg1)
{
    ui->doubleSpinBoxVCuAutoEn->setMinimum(ui->doubleSpinBoxVCutOff->value() + 0.2);
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].vAutoEnValue = (int) (ui->doubleSpinBoxVCuAutoEn->value() * 100);
}


void MainWindow::on_pushButtonApply_clicked()
{
    singletonSettings* settings = singletonSettings::getInstance();
    uartSend();

}


int MainWindow::uartOpen()
{
    singletonSettings* settings = singletonSettings::getInstance();

    settings->serialPort.setPortName(settings->serialPortName);
    settings->serialPort.setBaudRate(settings->serialBoudRate.toInt());
    switch (settings->serialDataBits) {
    case 5:
        settings->serialPort.setDataBits(QSerialPort::Data5);
        break;
    case 6:
        settings->serialPort.setDataBits(QSerialPort::Data6);
        break;
    case 7:
        settings->serialPort.setDataBits(QSerialPort::Data7);
        break;
    case 8:
        settings->serialPort.setDataBits(QSerialPort::Data8);
        break;
    default:
        settings->serialPort.setDataBits(QSerialPort::Data8);
        break;
    }

    settings->serialPort.setParity(QSerialPort::NoParity);
    settings->serialPort.setStopBits(QSerialPort::OneStop);
    settings->serialPort.setFlowControl(QSerialPort::NoFlowControl);
    if (settings->serialPort.isOpen())
    {
        ui->statusbar->showMessage("Порт уже подключен", 5000);
        qDebug() << "ALREADY CONNECTED\n";
        return 0;
    }
    if (settings->serialPort.open(QIODevice::ReadWrite)) {


        ui->statusbar->showMessage("Подключено", 0);
        qDebug() << "CONNECTED\n";
        return 0;


    } else {
        ui->statusbar->showMessage("ОШИБКА ПОДКЛЮЧЕНИЯ К ПОРТУ", 0);
        qDebug() << "NOT CONNECTED\n";
        QMessageBox::warning(this, "Ошибка","Ошибка подключения к порту!\nПроверьте параметры.");
    }
    return 1;
}


int MainWindow::uartSend()
{
    singletonSettings* settings = singletonSettings::getInstance();
    QString stringData, buffer;
    QByteArray data;
    for (int i = 0; i < 6; i++)
    {
        buffer.clear();
        stringData.append("*Ch=");
        buffer.setNum(i);
        stringData.append(buffer);
        stringData.append(": ");

        buffer.clear();
        stringData.append("signalSource=");
        stringData.append(buffer.setNum(settings->chParams[i].signalSource));

        buffer.clear();
        stringData.append(", pwmValue=");
        stringData.append(buffer.setNum(settings->chParams[i].pwmValue));

        buffer.clear();
        stringData.append(", flashType=");
        stringData.append(buffer.setNum(settings->chParams[i].flashType));

        buffer.clear();
        stringData.append(", heater1=");
        stringData.append(buffer.setNum(settings->chParams[i].heater1));

        buffer.clear();
        stringData.append(", heater2=");
        stringData.append(buffer.setNum(settings->chParams[i].heater2));

        buffer.clear();
        stringData.append(", delayTimerValue=");
        stringData.append(buffer.setNum(settings->chParams[i].delayTimerValue));

        buffer.clear();
        stringData.append(", shutdownTimerValue=");
        stringData.append(buffer.setNum(settings->chParams[i].shutdownTimerValue));

        buffer.clear();
        stringData.append(", vCutOffValue=");
        stringData.append(buffer.setNum(settings->chParams[i].vCutOffValue));

        buffer.clear();
        stringData.append(", vAutoEnValue=");
        stringData.append(buffer.setNum(settings->chParams[i].vAutoEnValue));

        buffer.clear();
        stringData.append(", flashFreq=");
        stringData.append(buffer.setNum(settings->chParams[i].flashFreq));

        buffer.clear();
        stringData.append(", currCutOffValue=");
        stringData.append(buffer.setNum(settings->chParams[i].currCutOffValue));

        buffer.clear();
        stringData.append(", engineOn=");
        stringData.append(buffer.setNum(settings->chParams[i].engineOn));

        buffer.clear();
        stringData.append(", shutdownTimer=");
        stringData.append(buffer.setNum(settings->chParams[i].shutdownTimer));

        buffer.clear();
        stringData.append(", vCutOff=");
        stringData.append(buffer.setNum(settings->chParams[i].vCutOff));

        buffer.clear();
        stringData.append(", vAutoEn=");
        stringData.append(buffer.setNum(settings->chParams[i].vAutoEn));

        buffer.clear();
        stringData.append(", pwm=");
        stringData.append(buffer.setNum(settings->chParams[i].pwm));

        buffer.clear();
        stringData.append(", currCutOff=");
        stringData.append(buffer.setNum(settings->chParams[i].currCutOff));

        buffer.clear();
        stringData.append(", delayTimer=");
        stringData.append(buffer.setNum(settings->chParams[i].delayTimer));

        buffer.clear();
        stringData.append(", flash=");
        stringData.append(buffer.setNum(settings->chParams[i].flash));

        stringData.append("%\n");
    }
    stringData.append("***\n");
    settings->serialPort.write(stringData.toUtf8());
    settings->serialPort.waitForBytesWritten();
    stringData.clear();
    return 0;
}


void MainWindow::on_pushButtonConnect_clicked()
{
    qDebug() << "TEST\n";
    MainWindow::uartOpen();
}


void MainWindow::on_comboBoxCOMPortsMain_activated(int index)
{
    // QList<QSerialPortInfo> serialPorts = serialPortInfo.availablePorts();
    // QList<QString> stringPorts;
    // for (int i = 0; i < serialPorts.size(); i++)
    // {
    //     stringPorts.append(serialPorts.at(i).portName());
    // }
    // ui->comboBoxCOMPortsMain->clear();
    // ui->comboBoxCOMPortsMain->addItems(stringPorts);
}


void MainWindow::on_comboBoxCOMPortsMain_currentIndexChanged(int index)
{
    singletonSettings* settings = singletonSettings::getInstance();
    if (settings->serialPort.isOpen())
    {
        settings->serialPort.close();
        ui->statusbar->showMessage("Порт закрыт", 3000);
    }
    settings->serialPortName = ui->comboBoxCOMPortsMain->currentText();
}


void MainWindow::on_pushButtonDisconnect_clicked()
{
    singletonSettings* settings = singletonSettings::getInstance();
    if (settings->serialPort.isOpen())
    {
        settings->serialPort.close();
        ui->statusbar->showMessage("Порт закрыт", 3000);
    }
    else
    {
        ui->statusbar->showMessage("Нет открытых портов", 3000);
    }

}


void MainWindow::on_comboBoxChNumber_currentIndexChanged(int index)
{
    singletonSettings* settings = singletonSettings::getInstance();
    ui->comboBoxSignal->setCurrentIndex(settings->chParams[ui->comboBoxChNumber->currentIndex()].signalSource);
}

