#include "view/playlistview.h"
#include "ui_playlistview.h"
#include <QStandardItemModel>
#include <QHeaderView>

PlaylistView::PlaylistView(Playlist *playlist, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlaylistView)
    , uartReceiver(new UARTReceiver(this))
    , m_playlist(playlist)
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
    , m_currentIndex(-1)
    , m_isPlaying(false)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    updatePlaylistModel();
}

PlaylistView::~PlaylistView()
{
    if (uartReceiver) {
        uartReceiver->stopListening();
        delete uartReceiver;
        uartReceiver = nullptr;
    }
    delete ui;
}

void PlaylistView::closeEvent(QCloseEvent *event) {
    if (uartReceiver) {
        uartReceiver->stopListening();
    }
    m_player->stop();
    QMainWindow::closeEvent(event);
}

void PlaylistView::setupUI()
{
    setWindowTitle(QString("Playlist: %1").arg(m_playlist->name()));
    
    // Set up media player
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(ui->volumeSlider->value() / 100.0);
    
    // Set up playlist view
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Title", "Artist", "Album", "Duration", "Size"});
    ui->playlistView->setModel(model);
    
    // Set column widths
    ui->playlistView->header()->resizeSection(0, 200); // Title
    ui->playlistView->header()->resizeSection(1, 150); // Artist
    ui->playlistView->header()->resizeSection(2, 150); // Album
    ui->playlistView->header()->resizeSection(3, 80);  // Duration
    ui->playlistView->header()->resizeSection(4, 80);  // Size

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

    // Cài đặt slider volume
    ui->volumeSlider->setMinimum(1);
    ui->volumeSlider->setMaximum(100);
    ui->volumeSlider->setValue(30);
}

void PlaylistView::setupConnections()
{
    // Player signals
    connect(m_player, &QMediaPlayer::durationChanged, this, &PlaylistView::updateDuration);
    connect(m_player, &QMediaPlayer::positionChanged, this, &PlaylistView::updatePosition);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &PlaylistView::handleMediaStatusChanged);
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &PlaylistView::handleStateChanged);
    connect(m_player, &QMediaPlayer::metaDataChanged, this, &PlaylistView::updateMetadata);

    // Kết nối tín hiệu UART
    connect(uartReceiver, &UARTReceiver::controlCommandReceived, this, &PlaylistView::handleUARTCommand);
    connect(uartReceiver, &UARTReceiver::numberReceived, this, &PlaylistView::handleUARTNumber);
    connect(uartReceiver, &UARTReceiver::errorOccurred, this, &PlaylistView::handleUARTError);

    // Khởi động UART
    if (!uartReceiver->startListening()) {
        qDebug() << "Failed to start UART listening in VideoView";
    }
}

void PlaylistView::updatePlaylistModel()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->playlistView->model());
    model->removeRows(0, model->rowCount());
    
    int row = 0;
    for (const MediaFile &file : m_playlist->mediaFiles()) {
        QList<QStandardItem*> items;
        items << new QStandardItem(file.title());
        items << new QStandardItem(file.artist());
        items << new QStandardItem(file.album());
        items << new QStandardItem(file.durationString());
        items << new QStandardItem(file.fileSizeString());
        
        model->insertRow(row++, items);
    }
}

void PlaylistView::loadFile(int index)
{
    if (index < 0 || index >= m_playlist->mediaFiles().size())
        return;
        
    m_currentIndex = index;
    const MediaFile &file = m_playlist->mediaFiles()[index];
    m_player->setSource(QUrl::fromLocalFile(file.filePath()));
    updateCurrentFileInfo();
    m_player->play();
    m_isPlaying = true;
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void PlaylistView::updateCurrentFileInfo()
{
    if (m_currentIndex >= 0 && m_currentIndex < m_playlist->mediaFiles().size()) {
        const MediaFile &file = m_playlist->mediaFiles()[m_currentIndex];
        ui->titleLabel->setText(file.title());
        ui->artistLabel->setText(file.artist());
        ui->albumLabel->setText(file.album());
    } else {
        ui->titleLabel->setText("No file playing");
        ui->artistLabel->setText("");
        ui->albumLabel->setText("");
    }
}

QString PlaylistView::formatTime(qint64 ms) const
{
    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

void PlaylistView::on_playButton_clicked()
{
    if (m_currentIndex == -1 && !m_playlist->mediaFiles().isEmpty()) {
        loadFile(0);
        return;
    }
    
    if (m_isPlaying) {
        m_player->pause();
        m_isPlaying = false;
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    } else {
        m_player->play();
        m_isPlaying = true;
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
}

void PlaylistView::on_nextButton_clicked()
{
    if (m_playlist->mediaFiles().isEmpty()) {
        return;
    }
    
    if (m_currentIndex < m_playlist->mediaFiles().size() - 1) {
        loadFile(m_currentIndex + 1);
    } else {
        // Nếu đang ở bài cuối, quay về bài đầu
        loadFile(0);
    }
}

void PlaylistView::on_previousButton_clicked()
{
    if (m_currentIndex > 0) {
        loadFile(m_currentIndex - 1);
    }
}

void PlaylistView::on_stopButton_clicked()
{
    m_player->stop();
    m_isPlaying = false;
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
}

void PlaylistView::on_volumeSlider_valueChanged(int value)
{
    m_audioOutput->setVolume(value / 100.0);
}

void PlaylistView::on_positionSlider_sliderMoved(int position)
{
    m_player->setPosition(position);
}

void PlaylistView::on_playlistView_doubleClicked(const QModelIndex &index)
{
    loadFile(index.row());
}

void PlaylistView::updateDuration(qint64 duration)
{
    ui->positionSlider->setMaximum(duration);
    ui->totalTimeLabel->setText(formatTime(duration));
}

void PlaylistView::updatePosition(qint64 position)
{
    ui->positionSlider->setValue(position);
    ui->currentTimeLabel->setText(formatTime(position));
}

void PlaylistView::updateMetadata()
{
    updateCurrentFileInfo();
}

void PlaylistView::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        if (m_currentIndex < m_playlist->mediaFiles().size() - 1) {
            loadFile(m_currentIndex + 1);
        } else {
            m_player->stop();
            m_isPlaying = false;
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        }
    }
}

void PlaylistView::handleStateChanged(QMediaPlayer::PlaybackState state)
{
    m_isPlaying = (state == QMediaPlayer::PlayingState);
    ui->playButton->setIcon(style()->standardIcon(
        m_isPlaying ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay
    ));
}

void PlaylistView::handleUARTCommand(const QString &command)
{
    qDebug() << "VideoView received UART command:" << command;

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

void PlaylistView::handleUARTNumber(int number) {
    qDebug() << "VideoView received UART number:" << number;
    if (number >= 0 && number <= 100) {
        ui->volumeSlider->setValue(number);
    }
}

void PlaylistView::handleUARTError(const QString &error)
{
    qDebug() << "PlaylistView UART error:" << error;
}
