#include <QStyle>
#include <QFileInfo>
#include <QTime>
#include <QShortcut>
#include "view/audioview.h"
#include "ui_audioview.h"

AudioView::AudioView(const QString &audioPath, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::AudioView),
      controller(new MediaController(this)),
      uartReceiver(new UARTReceiver(this)),
      totalDuration(0),
      isPaused(true),
      isMuted(false)
{
    ui->setupUi(this);

    // Thiết lập nguồn audio
    controller->setSource(QUrl::fromLocalFile(audioPath));

    // Hiển thị tên file
    QFileInfo fileInfo(audioPath);
    ui->label_File_Name->setText(fileInfo.fileName());

    // Thiết lập icon cho các nút
    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    // Cài đặt slider volume
    ui->horizontalSlider_Volume->setMinimum(1);
    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setValue(30);

    // Kết nối tín hiệu từ controller
    connect(controller, &MediaController::durationChanged, this, &AudioView::handleDurationChanged);
    connect(controller, &MediaController::positionChanged, this, &AudioView::handlePositionChanged);

    // Kết nối tín hiệu UART
    connect(uartReceiver, &UARTReceiver::controlCommandReceived, this, &AudioView::handleUARTCommand);
    connect(uartReceiver, &UARTReceiver::numberReceived, this, &AudioView::handleUARTNumber);
    connect(uartReceiver, &UARTReceiver::errorOccurred, this, &AudioView::handleUARTError);

    // Khởi động UART
    if (!uartReceiver->startListening()) {
        qDebug() << "Failed to start UART listening in AudioView";
    }

    ui->horizontalSlider_Duration->setRange(0, 0);

    // Thêm phím tắt F11 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &AudioView::toggleFullScreen);
}

AudioView::~AudioView() {
    if (uartReceiver) {
        uartReceiver->stopListening();
        delete uartReceiver;
        uartReceiver = nullptr;
    }
    delete ui;
}

void AudioView::closeEvent(QCloseEvent *event) {
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    controller->stop();
    QMainWindow::closeEvent(event);
}

void AudioView::handleDurationChanged(qint64 duration) {
    totalDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(totalDuration);
}

void AudioView::handlePositionChanged(qint64 position) {
    int currentSec = position / 1000;
    if (!ui->horizontalSlider_Duration->isSliderDown()) {
        ui->horizontalSlider_Duration->setValue(currentSec);
    }
    updateDurationDisplay(currentSec);
}

void AudioView::updateDurationDisplay(qint64 currentSeconds) {
    if (totalDuration > 0) {
        QTime currentTime(currentSeconds / 3600, (currentSeconds / 60) % 60, currentSeconds % 60);
        QTime totalTime(totalDuration / 3600, (totalDuration / 60) % 60, totalDuration % 60);
        QString format = (totalDuration > 3600) ? "hh:mm:ss" : "mm:ss";
        ui->label_Current_Time->setText(currentTime.toString(format));
        ui->label_Total_Time->setText(totalTime.toString(format));
    }
}

void AudioView::on_horizontalSlider_Duration_valueChanged(int value) {
    if (ui->horizontalSlider_Duration->isSliderDown()) {
        controller->setPosition(value * 1000);
    }
}


void AudioView::on_pushButton_Play_Pause_clicked() {
    if (isPaused) {
        isPaused = false;
        controller->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        isPaused = true;
        controller->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void AudioView::on_pushButton_Stop_clicked() {
    controller->stop();
    this->close();
}

void AudioView::on_pushButton_Seek_Forward_clicked() {
    controller->seekForward(20);
}

void AudioView::on_pushButton_Seek_Backward_clicked() {
    controller->seekBackward(20);
}

void AudioView::on_horizontalSlider_Volume_valueChanged(int value) {
    controller->setVolume(value);
}

void AudioView::on_pushButton_Volume_clicked() {
    if (!isMuted) {
        isMuted = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        controller->getAudioOutput()->setMuted(true);
    } else {
        isMuted = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        controller->getAudioOutput()->setMuted(false);
    }
}

void AudioView::handleUARTCommand(const QString &command)
{
    qDebug() << "AudioView received UART command:" << command;

    if (command == "stop") {
        on_pushButton_Stop_clicked();
    }
    else if (command == "play_pause") {
        on_pushButton_Play_Pause_clicked();
    }
    else if (command == "previous") {
        on_pushButton_Seek_Backward_clicked();
    }
    else if (command == "next") {
        on_pushButton_Seek_Forward_clicked();
    }
}

void AudioView::handleUARTNumber(int number) {
    qDebug() << "AudioView received UART number:" << number;
    if (number >= 0 && number <= 100) {
        ui->horizontalSlider_Volume->setValue(number);
    }
}

void AudioView::handleUARTError(const QString &error)
{
    qDebug() << "AudioView UART error:" << error;
}

void AudioView::toggleFullScreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}
