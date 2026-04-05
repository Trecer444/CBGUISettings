#include "serialconsol.h"
#include "ui_serialconsol.h"

serialconsol::serialconsol(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::serialconsol)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Монитор порта");
    if (mConsoleEnable)
        ui->labelMonitorDisabled->hide();
}

serialconsol::~serialconsol()
{
    delete ui;
}


void serialconsol::appendUartMessage(const QString &message, bool isSent)
{
    if (!mConsoleEnable)
        return;   // Если вывод выключен, ничего не показываем

    // Выбираем цвет для префикса и самого сообщения
    QString prefixColor = isSent ? "#2ecc71" : "#3498db";   // зелёный для TX, синий для RX
    // QString textColor   = isSent ? "#27ae60" : "#2980b9";

    // Экранируем спецсимволы HTML
    QString escapedMessage = message.toHtmlEscaped();

    // Формируем время с миллисекундами
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");

    // Выбираем префикс: [TX] или [RX]
    QString prefix = isSent ? "[TX]" : "[RX]";

    // Собираем строку для вывода
    QString formatted = QString("%1 <font color='%2'>%3</font> %4").arg(timestamp, prefixColor, prefix, escapedMessage);

    // Добавляем в QTextBrowser
    ui->textBrowser->append(formatted);

    // Автопрокрутка вниз (опционально)
    if (ui->checkBoxAutoScroll->isChecked())
    {
        QTextCursor cursor = ui->textBrowser->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textBrowser->setTextCursor(cursor);
    }
}


void serialconsol::on_pushButtonStart_clicked()
{
    this->mConsoleEnable = true;
    ui->labelMonitorDisabled->hide();
}

void serialconsol::on_pushButtonStop_clicked()
{
    this->mConsoleEnable = false;
    ui->labelMonitorDisabled->show();
}

void serialconsol::on_pushButtonClearExit_clicked()
{
    close();
}


void serialconsol::on_pushButtonExit_clicked()
{
    hide();
}

void serialconsol::on_pushButtonClear_clicked()
{
    ui->textBrowser->clear();
}

