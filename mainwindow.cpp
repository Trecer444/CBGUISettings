#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <stdio.h>

enum surceStatus{
    Disable = 0, //1
    Ignition, //2
    RegularCons, //3
    LoBeam,
    HiBeam,
    AnyHeadlignt,
    AnyTurner,
    LeftTurner,
    RightTurner,
    EmergencyLight,
    Heater,
    StopLight
};

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
    int h = 0, m = 0, s = 0;
    singletonSettings* settings = singletonSettings::getInstance();
    hideCh(ui);
    int signalSourceInd = ui->comboBoxSignal->currentIndex();

    switch (signalSourceInd) {
    case Ignition:
    case LoBeam:
    case HiBeam:
    case AnyHeadlignt:
    case AnyTurner:
    case LeftTurner:
    case RightTurner:
    case EmergencyLight:
    case Heater:
    case StopLight:
        ui->checkBoxEngineOn->show();     //только при работающем двигателе
        ui->checkBoxEngineOn->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].engineOn);
        break;
    default:
        break;
    }

    switch (signalSourceInd) {
    case Ignition:
    case LoBeam:
    case HiBeam:
    case AnyHeadlignt:
    case AnyTurner:
    case LeftTurner:
    case RightTurner:
    case EmergencyLight:
    case Heater:
    case StopLight:
        ui->checkBoxTimer->show();        //выключение по таймеру
        ui->checkBoxTimer->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimer);
        if (settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimer)
        {
            ui->timeOutWidget->show();
            h = settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimerValue/3600;
            m = (settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimerValue - 3600 * h) / 60;
            s = settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimerValue % 60;
            ui->timeEditTOff->setTime(QTime(h, m, s));

        }
        break;
    default:
        break;
    }

    switch (signalSourceInd) {
    case Ignition:
    case RegularCons:
    case LoBeam:
    case HiBeam:
    case AnyHeadlignt:
    case AnyTurner:
    case LeftTurner:
    case RightTurner:
    case EmergencyLight:
    case Heater:
    case StopLight:
        ui->checkBoxVCutoff->show();    //выключение по напряжениею
        ui->checkBoxVCutoff->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOff);
        if (settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOff)
        {
            ui->vCutOffWidget->show();
            ui->doubleSpinBoxVCutOff->setValue((double)(settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOffValue) / 100);
            ui->checkBoxVCutoffAutoEn->show();
            ui->checkBoxVCutoffAutoEn->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].vAutoEn);
            if (settings->chParams[ui->comboBoxChNumber->currentIndex()].vAutoEn) //включение по напряжению
            {
                ui->vCutOffAutoEnWidget->show();
                ui->doubleSpinBoxVCuAutoEn->setValue((double)(settings->chParams[ui->comboBoxChNumber->currentIndex()].vAutoEnValue) / 100);
            }
        }
        break;
    default:
        break;
    }

    switch (signalSourceInd) {
    case Ignition:
    case RegularCons:
    case LoBeam:
    case HiBeam:
    case AnyHeadlignt:
    case AnyTurner:
    case LeftTurner:
    case RightTurner:
    case EmergencyLight:
    case StopLight:
        ui->pwmWidget->show();            //ШИМ
        ui->checkBoxPWM->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].pwm);
        ui->spinBoxPWM->setValue(settings->chParams[ui->comboBoxChNumber->currentIndex()].pwmValue);
        break;
    default:
        break;
    }

    switch (signalSourceInd) {
    case Ignition:
    case RegularCons:
    case LoBeam:
    case HiBeam:
    case AnyHeadlignt:
    case AnyTurner:
    case LeftTurner:
    case RightTurner:
    case EmergencyLight:
    case StopLight:
        ui->checkBoxDelayOff->show();     //выключение с задержкой
        ui->checkBoxDelayOff->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimer);
        if (settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimer)  //если отмечено выключение с задержкой
        {
            ui->delayWidget->show();
            h = settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimerValue/3600;
            m = (settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimerValue - 3600 * h) / 60;
            s = settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimerValue % 60;
            ui->timeEditDelay->setTime(QTime(h, m, s));
        }
        break;
    default:
        break;
    }



    switch (signalSourceInd) {
    case LoBeam:
    case HiBeam:
    case AnyHeadlignt:
    case AnyTurner:
    case LeftTurner:
    case RightTurner:
    case EmergencyLight:
    case StopLight:
        ui->checkBoxFlash->show();        //моргать
        ui->checkBoxFlash->setChecked(settings->chParams[ui->comboBoxChNumber->currentIndex()].flash);
        ui->doubleSpinBoxFrequency->setValue((double)settings->chParams[ui->comboBoxChNumber->currentIndex()].flashFreq / 100);
        ui->spinBoxNumFlash->setValue(settings->chParams[ui->comboBoxChNumber->currentIndex()].flashCount);

        if (settings->chParams[ui->comboBoxChNumber->currentIndex()].flash)
        {
            ui->flashWidget->show();
            if (settings->chParams[ui->comboBoxChNumber->currentIndex()].flashType)
            {
                ui->radioButtonFew->setChecked(0);
                ui->radioButtonStrob->setChecked(1);

            }
            else
            {
                ui->radioButtonStrob->setChecked(0);
                ui->radioButtonFew->setChecked(1);
            }
        }
        break;
    default:
        break;
    }

    switch (signalSourceInd) {
    case Heater:
        ui->heaterWidget->show();
        ui->spinBoxHeater1->setValue(settings->chParams[ui->comboBoxChNumber->currentIndex()].heater1);
        ui->spinBoxHeater2->setValue(settings->chParams[ui->comboBoxChNumber->currentIndex()].heater2);
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
    settings->chParams[ui->comboBoxChNumber->currentIndex()].engineOn = ui->checkBoxEngineOn->isChecked();
    updateState();
}


void MainWindow::on_checkBoxTimer_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].shutdownTimer = ui->checkBoxTimer->isChecked(); //таймер
    updateState();
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
    updateState();
}


void MainWindow::on_checkBoxDelayOff_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].delayTimer = ui->checkBoxDelayOff->isChecked();
    updateState();
}


void MainWindow::on_checkBoxFlash_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flash = ui->checkBoxFlash->isChecked();
    updateState();
}


void MainWindow::on_checkBoxVCutoff_stateChanged(int arg1)
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].vCutOff = ui->checkBoxVCutoff->isChecked();
    updateState();
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
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flashType = 0;
    ui->label_2->show();
}


void MainWindow::on_radioButtonFew_clicked()
{
    singletonSettings* settings = singletonSettings::getInstance();
    settings->chParams[ui->comboBoxChNumber->currentIndex()].flashType = 1;
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
    // QByteArray data((char*)&settings->chParams[0], sizeof(settings->chParams[0]));
    for (int i = 0; i < 6; i++)
    {
        buffer.clear();
        stringData.append("$");
        buffer.setNum(i);
        stringData.append(buffer);
        // stringData.append(":");

        buffer.clear();
        // stringData.append("signalSource=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].signalSource));           //0

        buffer.clear();
        // stringData.append(", pwmValue=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].pwmValue));               //1

        buffer.clear();
        // stringData.append(", flashType=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].flashType));              //2

        buffer.clear();
        // stringData.append(", heater1=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].flashCount));             //3

        buffer.clear();
        // stringData.append(", heater2=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].heater1));                //4

        buffer.clear();
        // stringData.append(", delayTimerValue=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].heater2));                //5

        buffer.clear();
        // stringData.append(", shutdownTimerValue=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].delayTimerValue));        //6

        buffer.clear();
        // stringData.append(", vCutOffValue=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].shutdownTimerValue));     //7

        buffer.clear();
        // stringData.append(", vAutoEnValue=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].vCutOffValue));           //8

        buffer.clear();
        // stringData.append(", flashFreq=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].vAutoEnValue));          //9

        buffer.clear();
        // stringData.append(", currCutOffValue=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].flashFreq));              //10

        buffer.clear();
        // stringData.append(", engineOn=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].currCutOffValue));        //11

        buffer.clear();
        // stringData.append(", shutdownTimer=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].engineOn));               //12

        buffer.clear();
        // stringData.append(", vCutOff=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].shutdownTimer));          //13

        buffer.clear();
        // stringData.append(", vAutoEn=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].vCutOff));                //14

        buffer.clear();
        // stringData.append(", pwm=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].vAutoEn));                //15

        buffer.clear();
        // stringData.append(", currCutOff=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].pwm));                    //16

        buffer.clear();
        // stringData.append(", delayTimer=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].currCutOff));             //17

        buffer.clear();
        // stringData.append(", flash=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].delayTimer));             //18

        buffer.clear();
        // stringData.append(", flash=");
        stringData.append(" ");
        stringData.append(buffer.setNum(settings->chParams[i].flash));                  //19

        stringData.append(";");
    }
    stringData.append("*\n");
    qsizetype size = stringData.size();
    qDebug() << size << "\n\n";
    settings->serialPort.write(stringData.toUtf8(),size);
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
    updateState();
}

