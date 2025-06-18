#include "videoview.h"
#include "ui_videoview.h"

VideoView::VideoView(const QString &videoPath, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::VideoView),
      controller(new MediaController(this)),
      uartReceiver(new UARTReceiver(this)),
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

    // Kết nối tín hiệu từ controller đến các slot của view
    connect(controller, &MediaController::durationChanged, this, &VideoView::handleDurationChanged);
    connect(controller, &MediaController::positionChanged, this, &VideoView::handlePositionChanged);

    // Kết nối tín hiệu UART
    connect(uartReceiver, &UARTReceiver::controlCommandReceived, this, &VideoView::handleUARTCommand);
    connect(uartReceiver, &UARTReceiver::numberReceived, this, &VideoView::handleUARTNumber);
    connect(uartReceiver, &UARTReceiver::errorOccurred, this, &VideoView::handleUARTError);

    // Khởi động UART
    if (!uartReceiver->startListening()) {
        qDebug() << "Failed to start UART listening in VideoView";
    }

    // Khởi tạo slider thời gian
    ui->horizontalSlider_Duration->setRange(0, 0);

    // Tự động phát video khi mở cửa sổ
    controller->play();

    // Thêm phím tắt F1 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &VideoView::toggleFullScreen);
    showFullScreen();
}

VideoView::~VideoView() {
    if (uartReceiver) {
        uartReceiver->stopListening();
        delete uartReceiver;
        uartReceiver = nullptr;
    }
    delete ui;
}

void VideoView::closeEvent(QCloseEvent *event) {
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    controller->stop();
    controller->getPlayer()->setVideoOutput(nullptr);
    QMainWindow::closeEvent(event);
}

void VideoView::handleDurationChanged(qint64 duration) {
    totalDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(totalDuration);
}

void VideoView::handlePositionChanged(qint64 position) {
    int currentSec = position / 1000;
    if (!ui->horizontalSlider_Duration->isSliderDown()) {
        ui->horizontalSlider_Duration->setValue(currentSec);
    }
    updateDurationDisplay(currentSec);
}

void VideoView::updateDurationDisplay(qint64 currentSeconds) {
    if (totalDuration > 0) {
        QTime currentTime(currentSeconds / 3600, (currentSeconds / 60) % 60, currentSeconds % 60);
        QTime totalTime(totalDuration / 3600, (totalDuration / 60) % 60, totalDuration % 60);
        QString format = (totalDuration > 3600) ? "hh:mm:ss" : "mm:ss";
        ui->label_Current_Time->setText(currentTime.toString(format));
        ui->label_Total_Time->setText(totalTime.toString(format));
    }
}

void VideoView::on_horizontalSlider_Duration_valueChanged(int value) {
    if (ui->horizontalSlider_Duration->isSliderDown()) {
        controller->setPosition(value * 1000);
    }
}

void VideoView::on_pushButton_Play_Pause_clicked() {
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

void VideoView::on_pushButton_Stop_clicked() {
    controller->stop();
    this->close();
}

void VideoView::on_pushButton_Seek_Forward_clicked() {
    // Seek forward 20 giây
    controller->seekForward(20);
}

void VideoView::on_pushButton_Seek_Backward_clicked() {
    // Seek backward 20 giây
    controller->seekBackward(20);
}

void VideoView::on_horizontalSlider_Volume_valueChanged(int value) {
    controller->setVolume(value);
}

void VideoView::on_pushButton_Volume_clicked() {
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

void VideoView::handleUARTCommand(const QString &command)
{
    qDebug() << "VideoView received UART command:" << command;

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

void VideoView::handleUARTNumber(int number) {
    qDebug() << "VideoView received UART number:" << number;
    if (number >= 0 && number <= 100) {
        ui->horizontalSlider_Volume->setValue(number);
    }
}

void VideoView::handleUARTError(const QString &error)
{
    qDebug() << "VideoView UART error:" << error;
}

void VideoView::toggleFullScreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}
