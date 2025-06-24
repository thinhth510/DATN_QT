#include "audiocontroller.h"
#include "ui_audiowindow.h"

AudioWindow::AudioWindow(const QString &audioPath, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::AudioWindow),
      controller(new MediaController(this)),
      uartReceiver(UARTReceiver::getInstance()),
      totalDuration(0),
      isPaused(false),
      isMuted(false)
{
    ui->setupUi(this);

    // Thiết lập nguồn audio
    controller->setSource(QUrl::fromLocalFile(audioPath));

    // Hiển thị tên file
    QFileInfo fileInfo(audioPath);
    ui->label_File_Name->setText(fileInfo.fileName());

    // Thiết lập icon cho các nút
    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    // Cài đặt slider volume
    ui->horizontalSlider_Volume->setMinimum(0);
    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setValue(30);

    // Cài đặt slider duration
    ui->horizontalSlider_Duration->setRange(0, 0);

    // Kết nối tín hiệu từ controller
    connect(controller, &MediaController::durationChanged, this, &AudioWindow::handleDurationChanged);
    connect(controller, &MediaController::positionChanged, this, &AudioWindow::handlePositionChanged);

    // Kết nối tín hiệu từ UARTReceiver
    connect(uartReceiver, &UARTReceiver::controlCommandReceived, this, &AudioWindow::handleUARTCommand);
    connect(uartReceiver, &UARTReceiver::numberReceived, this, &AudioWindow::handleUARTNumber);
    connect(uartReceiver, &UARTReceiver::errorOccurred, this, &AudioWindow::handleUARTError);

    // Khởi động UART nếu chưa được khởi động
    if (!uartReceiver->startListening()) {
        qDebug() << "Failed to start UART listening in AudioWindow";
    }

    // Tự động phát audio khi mở cửa sổ
    controller->play();

    // Thêm phím tắt F1 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &AudioWindow::toggleFullScreen);
    showFullScreen();
}

AudioWindow::~AudioWindow() {
    // Dừng UARTReceiver nếu cần
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    delete ui;
}

void AudioWindow::closeEvent(QCloseEvent *event) {
    // Dừng UARTReceiver nếu cần
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    controller->stop();
    QMainWindow::closeEvent(event);
}

void AudioWindow::handleDurationChanged(qint64 duration) {
    totalDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(totalDuration);
}

void AudioWindow::handlePositionChanged(qint64 position) {
    int currentSec = position / 1000;
    if (!ui->horizontalSlider_Duration->isSliderDown()) {
        ui->horizontalSlider_Duration->setValue(currentSec);
    }
    updateDurationDisplay(currentSec);
}

void AudioWindow::updateDurationDisplay(qint64 currentSeconds) {
    if (totalDuration > 0) {
        QTime currentTime(currentSeconds / 3600, (currentSeconds / 60) % 60, currentSeconds % 60);
        QTime totalTime(totalDuration / 3600, (totalDuration / 60) % 60, totalDuration % 60);
        QString format = (totalDuration > 3600) ? "hh:mm:ss" : "mm:ss";
        ui->label_Current_Time->setText(currentTime.toString(format));
        ui->label_Total_Time->setText(totalTime.toString(format));
    }
}

void AudioWindow::on_horizontalSlider_Duration_valueChanged(int value) {
    if (ui->horizontalSlider_Duration->isSliderDown()) {
        controller->setPosition(value * 1000);
    }
}

void AudioWindow::on_pushButton_Play_Pause_clicked() {
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

void AudioWindow::on_pushButton_Stop_clicked() {
    controller->stop();
    this->close();
}

void AudioWindow::on_pushButton_Seek_Forward_clicked() {
    controller->seekForward(20);
}

void AudioWindow::on_pushButton_Seek_Backward_clicked() {
    controller->seekBackward(20);
}

void AudioWindow::on_horizontalSlider_Volume_valueChanged(int value) {
    controller->setVolume(value);
}

void AudioWindow::on_pushButton_Volume_clicked() {
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

void AudioWindow::toggleFullScreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void AudioWindow::handleUARTCommand(const QString &command)
{
    qDebug() << "AudioWindow received UART command:" << command;

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

void AudioWindow::handleUARTNumber(int number) {
    qDebug() << "AudioWindow received UART number:" << number;
    if (number >= 0 && number <= 100) {
        ui->horizontalSlider_Volume->setValue(number);
    }
}

void AudioWindow::handleUARTError(const QString &error)
{
    qDebug() << "AudioWindow UART error:" << error;
}
