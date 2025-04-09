#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
// #include <iostream>
#include <QDebug>
#include <QJsonArray>
#include <QJsonParseError>
#include <QSerialPort>

static const QString inputType[]
{
    "Disable", //1
    "Ignition", //2
    "RegularCons", //3
    "LoBeam",
    "HiBeam",
    "AnyHeadlignt",
    "AnyTurner",
    "LeftTurner",
    "RightTurner",
    "EmergencyLight",
    "Heater",
    "StopLight"
};

static const QString inputTypeRU[]
    {
        "Отключено",
        "Зажигание",
        "Постоянный потребитель",
        "Ближний свет",
        "Дальний свет",
        "Любой свет",
        "Поворотники",
        "Левый поворотник",
        "Правый поворотник",
        "Аварийка",
        "Подогрев",
        "Стопы"
    };

class Params
{
public:
    //параметры платы
    QString name = "F800GS";

    int
        signalSource = 0,
        pwmValue = 50,
        flashType = 0,
        flashCount = 5,
        heater1 = 20,
        heater2 = 50,
        delayTimerValue = 0,
        shutdownTimerValue = 300,
        vCutOffValue = 1250,        //сантивольты (делить на 100)
        vAutoEnValue = 1280,        //сантивольты (делить на 100)
        flashFreq = 200,            //*100
        currCutOffValue = 7000;     //*100

    // float
        // vCutOffValue = 12.5,
        // vAutoEnValue = 12.8,
        // flashFreq = 2.0,
        // currCutOffValue = 7.0;

    bool
        engineOn = false,
        shutdownTimer = false,
        vCutOff = false,
        vAutoEn = false,
        pwm = false,
        currCutOff = false,
        delayTimer = false,
        flash = false;
private:
};

class singletonSettings
{
public:

    static singletonSettings* getInstance()
    {
        if(instance == nullptr)
        {
            instance = new singletonSettings();
            instance->setDefaultSettings();
        }
        return instance;
    }

    void setDefaultSettings()
    {
        serialPortName = "COM0";
        serialBoudRate = "115200";
        serialDataBits = 8,
        serialStopBits = "1";
        serilaParity = "No Parity";
        serialFlowControl = "No Flow Control";
        serialCode = "";
    }

    void readParamsFromJSON()
    {
        file.setFileName("./params.json");
        if (file.exists())
        {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            qInfo() << "File EXISTS\n";
            val = file.readAll();
            file.close();
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);
            qDebug() << "JSON parcer debug msg: " << error.errorString() << error.offset << error.error;

            if (!doc.isObject()) //проверка
            {
                qWarning() << "DOC ISNT IBJECT\n";
                return;
            }
            QJsonObject json = doc.object();

            //считывание параметров
            for (int i = 0; i < 6; i++)
            {
                chParams[i].signalSource = json["vCutOff"].toBool();
                chParams[i].signalSource = json["vAutoEn"].toBool();
                chParams[i].signalSource = json["shutdownTimer"].toBool();
                chParams[i].signalSource = json["pwm"].toBool();
                chParams[i].signalSource = json["flash"].toBool();
                chParams[i].signalSource = json["engineOn"].toBool();
                chParams[i].signalSource = json["delayTimer"].toBool();
                chParams[i].signalSource = json["currCutOff"].toBool();

                chParams[i].signalSource = json["currCutOffValue"].toDouble();
                chParams[i].signalSource = json["vAutoEnValue"].toDouble();
                chParams[i].signalSource = json["vCutOffValue"].toDouble();

                chParams[i].signalSource = json["signalSource"].toInt();
                chParams[i].signalSource = json["shutdownTimerValue"].toInt();
                chParams[i].signalSource = json["pwmValue"].toInt();
                chParams[i].signalSource = json["heater2"].toInt();
                chParams[i].signalSource = json["heater1"].toInt();
                chParams[i].signalSource = json["flashType"].toInt();
                chParams[i].signalSource = json["flashFreq"].toInt();
                chParams[i].signalSource = json["flashCount"].toInt();
                chParams[i].signalSource = json["delayTimerValue"].toInt();

            }
        }
        else
        {
            qWarning() << "File DID NOT EXISTS\n";
            writeParamsToJSON();
        }

    }

    void writeParamsToJSON()
    {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QJsonObject recordObject;
        QJsonArray jsonArray;

        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].signalSource);
        }
        recordObject.insert("signalSource", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].engineOn);
        }
        recordObject.insert("engineOn", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].shutdownTimer);
        }
        recordObject.insert("shutdownTimer", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].shutdownTimerValue);
        }
        recordObject.insert("shutdownTimerValue", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].vCutOff);
        }
        recordObject.insert("vCutOff", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].vCutOffValue);
        }
        recordObject.insert("vCutOffValue", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].vAutoEn);
        }
        recordObject.insert("vAutoEn", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].vAutoEnValue);
        }
        recordObject.insert("vAutoEnValue", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].pwm);
        }
        recordObject.insert("pwm", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].pwmValue);
        }
        recordObject.insert("pwmValue", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].currCutOff);
        }
        recordObject.insert("currCutOff", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].currCutOffValue);
        }
        recordObject.insert("currCutOffValue", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].delayTimer);
        }
        recordObject.insert("delayTimer", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].delayTimerValue);
        }
        recordObject.insert("delayTimerValue", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].flash);
        }
        recordObject.insert("flash", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].flashType);
        }
        recordObject.insert("flashType", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].flashFreq);
        }
        recordObject.insert("flashFreq", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].flashCount);
        }
        recordObject.insert("flashCount", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].heater1);
        }
        recordObject.insert("heater1", jsonArray);

        jsonArray = QJsonArray{};
        for (int i = 0; i < 6; i++)
        {
            jsonArray.push_back(chParams[i].heater2);
        }
        recordObject.insert("heater2", jsonArray);


        QJsonDocument doc(recordObject);
        QString jsonString = doc.toJson(QJsonDocument::Indented);

        QTextStream stream (&file);
        stream << jsonString;
        file.close();
    }

    //параметры соединения
    QString serialPortName,
        serilaParity,
        serialFlowControl,
        serialCode,
        serialStopBits,
        serialBoudRate;

    int serialDataBits;

    QSerialPort serialPort;

    // параметры каналов
    Params chParams[6];

    QJsonObject jsonObject;



private:

    static singletonSettings* instance;

    QString val;
    QFile file;
};




#endif // SETTINGS_H
