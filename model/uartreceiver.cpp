#include "uartreceiver.h"

UARTReceiver::UARTReceiver(QObject *parent)
    : QObject(parent)
    , serialPort(new QSerialPort(this))
{
    validCommands = {"stop", "play_pause", "previous", "next"};

    connect(serialPort, &QSerialPort::readyRead, this, &UARTReceiver::handleReadyRead);
    connect(serialPort, &QSerialPort::errorOccurred, this, &UARTReceiver::handleError);
}

UARTReceiver::~UARTReceiver()
{
    stopListening();
}

bool UARTReceiver::startListening(const QString &portName, int baudRate)
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }

    QString actualPortName = portName.isEmpty() ? "/dev/ttyACM0" : portName;
    int actualBaudRate = (baudRate == 0) ? 9600 : baudRate;

    serialPort->setPortName(actualPortName);
    serialPort->setBaudRate(actualBaudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadOnly)) {
        emit errorOccurred(tr("Failed to open port %1: %2")
                          .arg(actualPortName)
                          .arg(serialPort->errorString()));
        return false;
    }

    qDebug() << "Started listening on port" << actualPortName;
    return true;
}

void UARTReceiver::stopListening()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        qDebug() << "Stopped listening on port" << serialPort->portName();
    }
}

void UARTReceiver::handleReadyRead()
{
    uartBuffer.append(serialPort->readAll());
    while (uartBuffer.contains('\n')) {
        int newlineIndex = uartBuffer.indexOf('\n');
        QByteArray commandData = uartBuffer.left(newlineIndex).trimmed();
        uartBuffer.remove(0, newlineIndex + 1);

        QString command = QString::fromUtf8(commandData);
        if (!command.isEmpty()) {
            processCommand(command);
        }
    }
}

void UARTReceiver::processBufferedData()
{
    // No longer needed as handleReadyRead processes data by newline
}

void UARTReceiver::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return;
    }

    emit errorOccurred(tr("Serial port error: %1")
                      .arg(serialPort->errorString()));
}

void UARTReceiver::processCommand(const QString &command)
{
    if (command.isEmpty()) {
        return;
    }

    // Kiểm tra xem có phải là số không
    bool ok;
    int number = command.toInt(&ok);
    if (ok && number >= 0 && number <= 100) {
        emit numberReceived(number);
        qDebug() << "Valid number processed:" << number;
        return;
    }

    // Kiểm tra các lệnh điều khiển
    if (validCommands.contains(command)) {
        emit controlCommandReceived(command);
        qDebug() << "Valid control command processed:" << command;
    } else {
        qDebug() << "Invalid command received:" << command;
    }
}

UARTReceiver* UARTReceiver::getInstance() {
    static UARTReceiver instance;
    return &instance;
} 