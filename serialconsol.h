#ifndef SERIALCONSOL_H
#define SERIALCONSOL_H

#include <QDialog>
#include <QDateTime>
#include <QTextCursor>

namespace Ui {
class serialconsol;
}

class serialconsol : public QDialog
{
    Q_OBJECT

public:
    explicit serialconsol(QWidget *parent = nullptr);
    ~serialconsol();

private slots:


    void on_pushButtonStart_clicked();

    void on_pushButtonClearExit_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonStop_clicked();


    void on_pushButtonClear_clicked();

public slots:
    void appendUartMessage(const QString &message, bool isSent = true);

private:
    Ui::serialconsol *ui;
    bool mConsoleEnable = true;
};

#endif // SERIALCONSOL_H
