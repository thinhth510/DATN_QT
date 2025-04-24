#ifndef AUDIOVIEW_H
#define AUDIOVIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mediacontroller.h"

namespace Ui {
class AudioView;
}

class AudioView : public QMainWindow {
    Q_OBJECT

public:
    explicit AudioView(const QString &audioPath, QWidget *parent = nullptr);
    ~AudioView();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void handleDurationChanged(qint64 duration);
    void handlePositionChanged(qint64 position);

    void on_horizontalSlider_Duration_valueChanged(int value);
    void on_pushButton_Play_Pause_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Seek_Forward_clicked();
    void on_pushButton_Seek_Backward_clicked();
    void on_horizontalSlider_Volume_valueChanged(int value);
    void on_pushButton_Volume_clicked();

private:
    Ui::AudioView *ui;
    MediaController *controller;
    qint64 totalDuration;
    bool isPaused;
    bool isMuted;

    void updateDurationDisplay(qint64 currentSeconds);
};

#endif // AUDIOVIEW_H
