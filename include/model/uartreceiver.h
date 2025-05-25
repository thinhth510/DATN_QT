#ifndef UARTRECEIVER_H
#define UARTRECEIVER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QList>
#include <QTimer>

class UARTReceiver : public QObject
{
    Q_OBJECT

public:
    explicit UARTReceiver(QObject *parent = nullptr);
    ~UARTReceiver();

    bool startListening(const QString &portName = "/dev/ttyACM0", int baudRate = 9600);
    void stopListening();

signals:
    void controlCommandReceived(const QString &command);
    void numberReceived(int number);
    void errorOccurred(const QString &error);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void processBufferedData();

private:
    QSerialPort *serialPort;
    QList<QString> validCommands;
    QByteArray uartBuffer;
    void processCommand(const QString &command);
    QTimer bufferTimer;
};

#endif // UARTRECEIVER_H 