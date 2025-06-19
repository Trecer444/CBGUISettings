#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <connectionsettings.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <settings.h>
#include <QDebug>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // ConnectionSettings *_connectionSettings = new ConnectionSettings();
    void updateState();
    // void updateStateFromPar();
    // singletonSettings* settings;
    int uartOpen();
    int uartSend();
    void uartReceiveParams();
private slots:

    void on_connectionSettingsBtn_triggered();

    void on_comboBoxSignal_currentIndexChanged(int index);

    void on_checkBoxEngineOn_stateChanged(int arg1);

    void on_checkBoxTimer_stateChanged(int arg1);

    void on_checkBoxVCutoffOn_stateChanged(int arg1);

    void on_checkBoxVCutoffAutoEn_stateChanged(int arg1);

    void on_checkBoxDelayOff_stateChanged(int arg1);

    void on_checkBoxFlash_stateChanged(int arg1);

    void on_checkBoxVCutoff_stateChanged(int arg1);

    void on_timeEditTOff_userTimeChanged(const QTime &time);

    void on_doubleSpinBoxVCutOff_valueChanged(double arg1);

    void on_checkBoxPWM_stateChanged(int arg1);

    void on_spinBoxPWM_valueChanged(int arg1);

    void on_checkBoxCurrent_stateChanged(int arg1);

    void on_doubleSpinBoxCurrent_valueChanged(double arg1);

    void on_timeEditDelay_userTimeChanged(const QTime &time);

    void on_radioButtonStrob_clicked();

    void on_radioButtonFew_clicked();

    void on_doubleSpinBoxFrequency_valueChanged(double arg1);

    void on_spinBoxNumFlash_valueChanged(int arg1);

    void on_spinBoxHeater1_valueChanged(int arg1);

    void on_spinBoxHeater2_valueChanged(int arg1);

    void on_pushButtonApply_clicked();

    void on_doubleSpinBoxVCuAutoEn_valueChanged(double arg1);

    void on_pushButtonConnect_clicked();

    void on_comboBoxCOMPortsMain_activated(int index);

    void on_comboBoxCOMPortsMain_currentIndexChanged(int index);

    void on_pushButtonDisconnect_clicked();

    void on_comboBoxChNumber_currentIndexChanged(int index);

    void on_pushButtonRead_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPortInfo serialPortInfo;
    QSerialPort serialPorts;


};

void hideCh(Ui::MainWindow* ui);

#endif // MAINWINDOW_H
