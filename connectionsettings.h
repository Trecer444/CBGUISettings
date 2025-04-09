#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <settings.h>


namespace Ui {
class ConnectionSettings;
}

class ConnectionSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSettings(QWidget *parent = nullptr);
    ~ConnectionSettings();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_2_clicked();

private:
    Ui::ConnectionSettings *ui;
    QSerialPortInfo serialPortInfo;
    QSerialPort serialPorts;

};

#endif // CONNECTIONSETTINGS_H
