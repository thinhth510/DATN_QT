#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <QMainWindow>
#include <QVideoWidget>
#include "controller/mediacontroller.h"
#include "../model/uartreceiver.h"

namespace Ui {
class VideoView;
}

class VideoView : public QMainWindow {
    Q_OBJECT

public:
    explicit VideoView(const QString &videoPath, QWidget *parent = nullptr);
    ~VideoView();

    void handleUARTCommand(const QString &command);
    void handleUARTNumber(int number);
    void handleUARTError(const QString &error);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Các slot xử lý sự thay đổi của media
    void handleDurationChanged(qint64 duration);
    void handlePositionChanged(qint64 position);

    // Slot xử lý sự kiện của UI
    void on_horizontalSlider_Duration_valueChanged(int value);
    void on_pushButton_Play_Pause_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Seek_Forward_clicked();
    void on_pushButton_Seek_Backward_clicked();
    void on_horizontalSlider_Volume_valueChanged(int value);
    void on_pushButton_Volume_clicked();
    void toggleFullScreen();

private:
    Ui::VideoView *ui;
    MediaController *controller;
    UARTReceiver *uartReceiver;
    QVideoWidget *videoWidget;
    qint64 totalDuration;
    bool isPaused;
    bool isMuted;

    void updateDurationDisplay(qint64 currentSeconds);
};

#endif // VIDEOVIEW_H
