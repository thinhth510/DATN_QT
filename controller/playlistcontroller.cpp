#include "playlistcontroller.h"
#include "ui_playlistwindow.h"


PlaylistWindow::PlaylistWindow(Playlist *playlist, Database *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlaylistWindow)
    , uartReceiver(UARTReceiver::getInstance())
    , m_playlist(playlist)
    , m_controller(new MediaController(this))
    , m_currentIndex(-1)
    , m_isPlaying(false)
    , isMuted(false)
    , m_db(db)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    updatePlaylistModel();
    loadPlaylist();

    // Kết nối tín hiệu từ UARTReceiver
    connect(uartReceiver, &UARTReceiver::controlCommandReceived, this, &PlaylistWindow::handleUARTCommand);
    connect(uartReceiver, &UARTReceiver::numberReceived, this, &PlaylistWindow::handleUARTNumber);
    connect(uartReceiver, &UARTReceiver::errorOccurred, this, &PlaylistWindow::handleUARTError);

    // Khởi động UART nếu chưa được khởi động
    if (!uartReceiver->startListening()) {
        qDebug() << "Failed to start UART listening in PlaylistWindow";
    }

    // Thêm phím tắt F1 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &PlaylistWindow::toggleFullScreen);
    showFullScreen();
}

PlaylistWindow::~PlaylistWindow()
{
    // Dừng UARTReceiver nếu cần
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    delete ui;
}

void PlaylistWindow::closeEvent(QCloseEvent *event) {
    // Dừng UARTReceiver nếu cần
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    m_controller->stop();
    QMainWindow::closeEvent(event);
}

void PlaylistWindow::setupUI()
{
    setWindowTitle(QString("Playlist: %1").arg(m_playlist->name()));
    
    // Set up media player
    m_controller->getAudioOutput()->setVolume(ui->volumeSlider->value() / 100.0);
    
    // Set up playlist view
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Title", "Artist", "Album", "Genre", "Duration", "Size"});
    ui->playlistView->setModel(model);
    
    // Set column widths
    ui->playlistView->header()->resizeSection(0, 250); // Title
    ui->playlistView->header()->resizeSection(1, 300); // Artist
    ui->playlistView->header()->resizeSection(2, 150); // Album
    ui->playlistView->header()->resizeSection(3, 100); // Genre
    ui->playlistView->header()->resizeSection(4, 100);  // Duration
    ui->playlistView->header()->resizeSection(5, 100);  // Size

    // Thiết lập icons và kích thước cho các buttons
    QSize iconSize(32, 32);
    
    // Play button
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->playButton->setIconSize(iconSize);
    ui->playButton->setText("");
    ui->playButton->setFixedSize(40, 40);
    
    // Previous button (thay thế seek backward)
    ui->previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->previousButton->setIconSize(iconSize);
    ui->previousButton->setText("");
    ui->previousButton->setFixedSize(40, 40);
    ui->previousButton->setToolTip("Previous track");
    
    // Next button (thay thế seek forward)
    ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->nextButton->setIconSize(iconSize);
    ui->nextButton->setText("");
    ui->nextButton->setFixedSize(40, 40);
    ui->nextButton->setToolTip("Next track");
    
    // Stop button
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->stopButton->setIconSize(iconSize);
    ui->stopButton->setText("");
    ui->stopButton->setFixedSize(40, 40);

    // Volume button
    ui->volumeButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->stopButton->setIconSize(iconSize);
    ui->stopButton->setText("");
    ui->stopButton->setFixedSize(40, 40);

    // Cài đặt slider volume
    ui->volumeSlider->setMinimum(0);
    ui->volumeSlider->setMaximum(100);
    ui->volumeSlider->setValue(30);

}

void PlaylistWindow::setupConnections()
{
    // MediaController signals
    connect(m_controller, &MediaController::durationChanged, this, &PlaylistWindow::updateDuration);
    connect(m_controller, &MediaController::positionChanged, this, &PlaylistWindow::updatePosition);
    connect(m_controller, &MediaController::playbackStateChanged, this, &PlaylistWindow::handleStateChanged);
    connect(m_controller, &MediaController::currentIndexChanged, this, &PlaylistWindow::handleCurrentIndexChanged);
    
    // Player signals for metadata
    connect(m_controller->getPlayer(), &QMediaPlayer::metaDataChanged, this, &PlaylistWindow::updateMetadata);
}

void PlaylistWindow::loadPlaylist()
{
    MediaFileDAO mediaFileDao(m_db);
    QList<MediaFile> files = mediaFileDao.getMediaFiles(m_playlist->id());
    
    QStringList filePaths;
    for (const MediaFile &file : files) {
        filePaths.append(file.filePath());
    }
    
    m_controller->setPlaylist(filePaths);
}

void PlaylistWindow::updatePlaylistModel()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->playlistView->model());
    model->removeRows(0, model->rowCount());
    if (!m_playlist) return;
    MediaFileDAO mediaFileDao(m_db);
    QList<MediaFile> files = mediaFileDao.getMediaFiles(m_playlist->id());
    int row = 0;
    for (const MediaFile &file : files) {
        QList<QStandardItem*> items;
        items << new QStandardItem(file.title());
        items << new QStandardItem(file.artist());
        items << new QStandardItem(file.album());
        items << new QStandardItem(file.genre());
        items << new QStandardItem(file.durationString());
        items << new QStandardItem(file.fileSizeString());
        model->insertRow(row++, items);
    }
}

void PlaylistWindow::updateCurrentFileInfo()
{
    MediaFileDAO mediaFileDao(m_db);
    QList<MediaFile> files = mediaFileDao.getMediaFiles(m_playlist->id());
    
    int currentIndex = m_controller->getCurrentIndex();
    if (currentIndex >= 0 && currentIndex < files.size()) {
        const MediaFile &file = files[currentIndex];
        ui->titleLabel->setText(file.title());
        ui->artistLabel->setText(file.artist());
        ui->albumLabel->setText(file.album());
    } else {
        ui->titleLabel->setText("No file playing");
        ui->artistLabel->setText("");
        ui->albumLabel->setText("");
    }
}

QString PlaylistWindow::formatTime(qint64 ms) const
{
    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

void PlaylistWindow::on_playButton_clicked()
{
    if (!m_controller->hasPlaylist()) {
        return;
    }
    
    if (m_isPlaying) {
        m_controller->pause();
    } else {
        m_controller->play();
    }
}

void PlaylistWindow::on_nextButton_clicked()
{
    m_controller->next();
}

void PlaylistWindow::on_previousButton_clicked()
{
    m_controller->previous();
}

void PlaylistWindow::on_stopButton_clicked()
{
    m_controller->stop();
    this->close();
}

void PlaylistWindow::on_volumeSlider_valueChanged(int value)
{
    m_controller->setVolume(value);
}

void PlaylistWindow::on_positionSlider_sliderMoved(int position)
{
    m_controller->setPosition(position);
}

void PlaylistWindow::on_playlistView_doubleClicked(const QModelIndex &index)
{
    // Set flag to force play when loading new item
    m_controller->setShouldPlayOnLoad(true);
    m_controller->setCurrentIndex(index.row());
}

void PlaylistWindow::updateDuration(qint64 duration)
{
    ui->positionSlider->setMaximum(duration);
    ui->totalTimeLabel->setText(formatTime(duration));
}

void PlaylistWindow::updatePosition(qint64 position)
{
    ui->positionSlider->setValue(position);
    ui->currentTimeLabel->setText(formatTime(position));
}

void PlaylistWindow::updateMetadata()
{
    updateCurrentFileInfo();
}

void PlaylistWindow::handleStateChanged(QMediaPlayer::PlaybackState state)
{
    m_isPlaying = (state == QMediaPlayer::PlayingState);
    ui->playButton->setIcon(style()->standardIcon(
        m_isPlaying ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay
    ));
}

void PlaylistWindow::handleCurrentIndexChanged(int index)
{
    m_currentIndex = index;
    updateCurrentFileInfo();
    
    // Highlight current item in playlist view
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->playlistView->model());
    if (model && index >= 0 && index < model->rowCount()) {
        ui->playlistView->setCurrentIndex(model->index(index, 0));
    }
}

void PlaylistWindow::handlePlaylistEnded()
{
    m_isPlaying = false;
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void PlaylistWindow::toggleFullScreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void PlaylistWindow::on_volumeButton_clicked()
{
    isMuted = !isMuted;
    m_controller->getAudioOutput()->setMuted(isMuted);
    ui->volumeButton->setIcon(style()->standardIcon(isMuted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
}

void PlaylistWindow::handleUARTCommand(const QString &command)
{
    qDebug() << "PlaylistWindow received UART command:" << command;

    if (command == "stop") {
        on_stopButton_clicked();
    }
    else if (command == "play_pause") {
        on_playButton_clicked();
    }
    else if (command == "previous") {
        on_previousButton_clicked();
    }
    else if (command == "next") {
        on_nextButton_clicked();
    }
}

void PlaylistWindow::handleUARTNumber(int number) {
    qDebug() << "PlaylistWindow received UART number:" << number;
    if (number >= 0 && number <= 100) {
        ui->volumeSlider->setValue(number);
    }
}

void PlaylistWindow::handleUARTError(const QString &error)
{
    qDebug() << "PlaylistWindow UART error:" << error;
}
