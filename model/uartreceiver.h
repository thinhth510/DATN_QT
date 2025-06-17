#ifndef UARTRECEIVER_H
#define UARTRECEIVER_H

#include <QtCore>
#include <QtSerialPort>

class UARTReceiver : public QObject
{
    Q_OBJECT

public:
    explicit UARTReceiver(QObject *parent = nullptr);
    ~UARTReceiver();

    // UART Control
    bool startListening(const QString &portName = "/dev/ttyACM0", int baudRate = 9600);
    void stopListening();

signals:
    // UART Events
    void controlCommandReceived(const QString &command);
    void numberReceived(int number);
    void errorOccurred(const QString &error);

private slots:
    // UART Event Handlers
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void processBufferedData();

private:
    // UART Components
    QSerialPort *serialPort;
    QList<QString> validCommands;
    QByteArray uartBuffer;
    QTimer bufferTimer;

    // Helper Methods
    void processCommand(const QString &command);
};

#endif // UARTRECEIVER_H 