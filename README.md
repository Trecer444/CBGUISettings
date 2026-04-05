# 🛠️ F800GS CB GUI Settings

Приложение для настройки управляющей платы коммутации дополнительных потребителей мотоцикла **BMW F800GS**. Позволяет гибко управлять параметрами каждого из 6 каналов, включая таймеры, отсечки по току и напряжению, управление подогревателями и т.д.

---

## 🔧 Возможности

- Настройка до 6 независимых каналов
- Управление:
  - источником сигнала (свет ближний, дальний, поворотники, аварийка, подогрев, зажигание)
  - широтно-импульсной модуляцией (PWM)
  - порогами тока и напряжения
  - таймерами включения и выключения
  - подогревателями
- Загрузка и сохранение параметров в JSON
- Связь с платой через USB
- Импорт и экспорт конфигурации

---

## Связанные проекты

- 💻️ **[CBFirmware](https://github.com/Trecer444/CBFirmware)** — прошивка для микроконтроллера платы управления (реализация протокола UART, логики включения/отключения нагрузки и защиты).
- 🔌 **[CBHardware](https://github.com/Trecer444/CBHardware)** — аппаратная часть: схема, разводка печатной платы, спецификация компонентов.


## 📦 Сборка проекта

### Требования:
- Qt 6.7 или новее (включая Qt Widgets, SerialPort)
- Компилятор MinGW (64-bit)
- CMake или Qt Creator
- Inno Setup (для сборки установщика)

### Сборка из Qt Creator:
1. Открой `CBGUISettings.pro` в Qt Creator
2. Выбери профиль сборки (например, `Desktop Qt 6.7.0 MinGW 64-bit`)
3. Нажми `Собрать` или `Ctrl+B`

### Сборка вручную (qmake + make):
```bash
qmake CBGUISettings.pro
mingw32-make
```

---

## 🧪 Запуск

Готовый исполняемый файл:  
`build/release/CBGUISettings.exe`

Необходимые библиотеки (`*.dll`) Qt автоматически копируются в папку сборки.

---

## 📁 Структура проекта

- `main.cpp` — инициализация приложения
- `mainwindow.*` — главное окно интерфейса
- `connectionsettings.*` — параметры соединения с COM-портом
- `settings.h` — глобальный singleton для хранения параметров
- `resources.qrc` — ресурсы (иконка и стили)

---

## 🔌 Структура UART-протокола

### Отправка настроек:
Метод `uartSend()` сериализует параметры каналов в строку формата:

```
$0 0 50 0 5 20 50 0 300 1250 1280 200 700 0 0 0 0 0 0 0 0;
...
$5 ...
*
```

### Получение настроек:
Метод `uartReceive()` отправляет:

```
#GET-ParamList\n
```

И ожидает в ответ блок вида:

```
$0 ...;$1 ...;...;$5 ...;*
```

Данные автоматически парсятся в `singletonSettings::chParams[i]`.

---

## 🔧 Структура параметров JSON

Пример параметров одного канала:

```json
{
  "name": "F800GS",
  "signalSource": [0, 0, 0, 0, 0, 0],
  "engineOn": false,
  "shutdownTimer": false,
  "shutdownTimerValue": -1,
  "vCutOff": false,
  "vCutOffValue": -1,
  "vAutoEn": false,
  "vAutoEnValue": 12.8,
  "pwm": false,
  "pwmValue": -1,
  "currCutoff": false,
  "currCutoffValue": -1,
  "delayTimer": false,
  "delayTimerValue": -1,
  "flash": false,
  "flashType": -1,
  "flashFreq": -1,
  "flashCount": -1,
  "heater1": -1,
  "heater2": -1
}
```

---

## 📥 Сборка установщика

Используется [Inno Setup](https://jrsoftware.org/isinfo.php):
Файл с конфигурацией установщика InnoScript.iss
Команда для копирования DLL файлов:
``` 
windeployqt.exe --verbose 1 cummutationBordGUISettings.exe 
```
Вызывается из консаоли MinGW в папке release с cummutationBordGUISettings.exe


## 🧑‍💻 Автор

Разработка: [Trecer444](https://github.com/Trecer444)  

---

## 📃 Лицензия

Данный проект распространяется под лицензией **GNU General Public License v3.0**.  
Вы можете свободно использовать, изменять и распространять его при условии сохранения открытого кода.

Подробнее: [https://www.gnu.org/licenses/gpl-3.0.html](https://www.gnu.org/licenses/gpl-3.0.html)