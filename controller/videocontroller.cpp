#include "videocontroller.h"
#include "ui_videowindow.h"

VideoWindow::VideoWindow(const QString &videoPath, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::VideoWindow),
      controller(new MediaController(this)),
      uartReceiver(UARTReceiver::getInstance()),
      totalDuration(0),
      isPaused(false),
      isMuted(false)
{
    ui->setupUi(this);

    // Tạo QVideoWidget và gán vào group box
    videoWidget = new QVideoWidget();
    QVBoxLayout* videoLayout = new QVBoxLayout(ui->groupBox_Video);
    videoLayout->setContentsMargins(0, 0, 0, 0);
    videoLayout->addWidget(videoWidget);
    ui->groupBox_Video->setLayout(videoLayout);

    // Thiết lập video output
    controller->getPlayer()->setVideoOutput(videoWidget);

    // Thiết lập nguồn video
    controller->setSource(QUrl::fromLocalFile(videoPath));

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

    // Khởi tạo slider thời gian
    ui->horizontalSlider_Duration->setRange(0, 0);

    // Kết nối tín hiệu từ controller đến các slot của view
    connect(controller, &MediaController::durationChanged, this, &VideoWindow::handleDurationChanged);
    connect(controller, &MediaController::positionChanged, this, &VideoWindow::handlePositionChanged);

    // Kết nối tín hiệu từ UARTReceiver
    connect(uartReceiver, &UARTReceiver::controlCommandReceived, this, &VideoWindow::handleUARTCommand);
    connect(uartReceiver, &UARTReceiver::numberReceived, this, &VideoWindow::handleUARTNumber);
    connect(uartReceiver, &UARTReceiver::errorOccurred, this, &VideoWindow::handleUARTError);

    // Khởi động UART nếu chưa được khởi động
    if (!uartReceiver->startListening()) {
        qDebug() << "Failed to start UART listening in VideoWindow";
    }

    // Tự động phát video khi mở cửa sổ
    controller->play();

    // Thêm phím tắt F1 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &VideoWindow::toggleFullScreen);
    showFullScreen();
}

VideoWindow::~VideoWindow() {
    // Dừng UARTReceiver nếu cần
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    controller->stop();
    controller->getPlayer()->setVideoOutput(nullptr);
    delete ui;
}

void VideoWindow::closeEvent(QCloseEvent *event) {
    // Dừng UARTReceiver nếu cần
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    controller->stop();
    controller->getPlayer()->setVideoOutput(nullptr);
    QMainWindow::closeEvent(event);
}

void VideoWindow::handleDurationChanged(qint64 duration) {
    totalDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(totalDuration);
}

void VideoWindow::handlePositionChanged(qint64 position) {
    int currentSec = position / 1000;
    if (!ui->horizontalSlider_Duration->isSliderDown()) {
        ui->horizontalSlider_Duration->setValue(currentSec);
    }
    updateDurationDisplay(currentSec);
}

void VideoWindow::updateDurationDisplay(qint64 currentSeconds) {
    if (totalDuration > 0) {
        QTime currentTime(currentSeconds / 3600, (currentSeconds / 60) % 60, currentSeconds % 60);
        QTime totalTime(totalDuration / 3600, (totalDuration / 60) % 60, totalDuration % 60);
        QString format = (totalDuration > 3600) ? "hh:mm:ss" : "mm:ss";
        ui->label_Current_Time->setText(currentTime.toString(format));
        ui->label_Total_Time->setText(totalTime.toString(format));
    }
}

void VideoWindow::on_horizontalSlider_Duration_valueChanged(int value) {
    if (ui->horizontalSlider_Duration->isSliderDown()) {
        controller->setPosition(value * 1000);
    }
}

void VideoWindow::on_pushButton_Play_Pause_clicked() {
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

void VideoWindow::on_pushButton_Stop_clicked() {
    controller->stop();
    this->close();
}

void VideoWindow::on_pushButton_Seek_Forward_clicked() {
    // Seek forward 20 giây
    controller->seekForward(20);
}

void VideoWindow::on_pushButton_Seek_Backward_clicked() {
    // Seek backward 20 giây
    controller->seekBackward(20);
}

void VideoWindow::on_horizontalSlider_Volume_valueChanged(int value) {
    controller->setVolume(value);
}

void VideoWindow::on_pushButton_Volume_clicked() {
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

void VideoWindow::toggleFullScreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void VideoWindow::handleUARTCommand(const QString &command)
{
    qDebug() << "VideoWindow received UART command:" << command;

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

void VideoWindow::handleUARTNumber(int number) {
    qDebug() << "VideoWindow received UART number:" << number;
    if (number >= 0 && number <= 100) {
        ui->horizontalSlider_Volume->setValue(number);
    }
}

void VideoWindow::handleUARTError(const QString &error)
{
    qDebug() << "VideoWindow UART error:" << error;
}
