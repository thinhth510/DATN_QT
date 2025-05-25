#include "model/uartreceiver.h"
#include <QDebug>

UARTReceiver::UARTReceiver(QObject *parent)
    : QObject(parent)
    , serialPort(new QSerialPort(this))
{
    validCommands = {"stop", "play_pause", "previous", "next"};

    connect(serialPort, &QSerialPort::readyRead, this, &UARTReceiver::handleReadyRead);
    connect(serialPort, &QSerialPort::errorOccurred, this, &UARTReceiver::handleError);

    bufferTimer.setSingleShot(true);
    connect(&bufferTimer, &QTimer::timeout, this, &UARTReceiver::processBufferedData);
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

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadOnly)) {
        emit errorOccurred(tr("Failed to open port %1: %2")
                          .arg(portName)
                          .arg(serialPort->errorString()));
        return false;
    }

    qDebug() << "Started listening on port" << portName;
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
    QByteArray newData = serialPort->readAll();
    uartBuffer.append(newData);

    // Đợi 50ms để tích lũy đủ dữ liệu
    if (!bufferTimer.isActive())
        bufferTimer.start(50);
}

void UARTReceiver::processBufferedData()
{
    if (uartBuffer.isEmpty())
        return;

    QString command = QString::fromUtf8(uartBuffer).trimmed();
    uartBuffer.clear();

    if (!command.isEmpty()) {
        processCommand(command);
    }
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