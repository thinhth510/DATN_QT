#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QtWidgets>
#include <QtMultimediaWidgets>

#include "mediacontroller.h"
#include "../model/uartreceiver.h"

namespace Ui {
class VideoWindow;
}

class VideoWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit VideoWindow(const QString &videoPath, QWidget *parent = nullptr);
    ~VideoWindow();

    // UART Interface
    void handleUARTCommand(const QString &command);
    void handleUARTNumber(int number);
    void handleUARTError(const QString &error);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Media Control Slots
    void handleDurationChanged(qint64 duration);
    void handlePositionChanged(qint64 position);
    void on_horizontalSlider_Duration_valueChanged(int value);
    void on_pushButton_Play_Pause_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Seek_Forward_clicked();
    void on_pushButton_Seek_Backward_clicked();
    void on_horizontalSlider_Volume_valueChanged(int value);
    void on_pushButton_Volume_clicked();
    void toggleFullScreen();

private:
    // UI Components
    Ui::VideoWindow *ui;
    MediaController *controller;
    UARTReceiver *uartReceiver;
    QVideoWidget *videoWidget;

    // Media State
    qint64 totalDuration;
    bool isPaused;
    bool isMuted;

    // Helper Methods
    void updateDurationDisplay(qint64 currentSeconds);
};

#endif // VIDEOCONTROLLER_H
