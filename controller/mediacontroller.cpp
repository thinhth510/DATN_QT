#include "mediacontroller.h"

MediaController::MediaController(QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this)),
      m_isPaused(true),
      m_currentIndex(-1),
      m_hasPlaylist(false),
      m_shouldPlayOnLoad(false)
{
    m_player->setAudioOutput(m_audioOutput);
    
    // Chuyển các tín hiệu từ m_player ra ngoài controller để view kết nối
    connect(m_player, &QMediaPlayer::durationChanged, this, &MediaController::durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MediaController::positionChanged);
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &MediaController::handlePlaybackStateChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MediaController::handleMediaStatusChanged);
}

MediaController::~MediaController() {
    // Các đối tượng con được xoá tự động khi controller bị xoá
}

QMediaPlayer* MediaController::getPlayer() const {
    return m_player;
}

QAudioOutput* MediaController::getAudioOutput() const {
    return m_audioOutput;
}

void MediaController::setSource(const QUrl &url) {
    m_player->setSource(url);
}

void MediaController::setPlaylist(const QList<QUrl> &urls) {
    m_playlist = urls;
    m_hasPlaylist = !urls.isEmpty();
    m_currentIndex = -1;
    
    if (m_hasPlaylist) {
        setCurrentIndex(0);
    }
}

void MediaController::setPlaylist(const QStringList &filePaths) {
    QList<QUrl> urls;
    for (const QString &path : filePaths) {
        urls.append(QUrl::fromLocalFile(path));
    }
    setPlaylist(urls);
}

void MediaController::previous() {
    if (!m_hasPlaylist || m_playlist.isEmpty()) {
        return;
    }
    
    // Remember current playing state
    m_shouldPlayOnLoad = !m_isPaused;
    
    if (m_currentIndex > 0) {
        setCurrentIndex(m_currentIndex - 1);
    } else {
        // Loop to end
        setCurrentIndex(m_playlist.size() - 1);
    }
}

void MediaController::next() {
    if (!m_hasPlaylist || m_playlist.isEmpty()) {
        return;
    }
    
    // Remember current playing state
    m_shouldPlayOnLoad = !m_isPaused;
    
    if (m_currentIndex < m_playlist.size() - 1) {
        setCurrentIndex(m_currentIndex + 1);
    } else {
        // Loop to beginning
        setCurrentIndex(0);
    }
}

void MediaController::autoNext() {
    if (!m_hasPlaylist || m_playlist.isEmpty()) {
        return;
    }
    
    // Force auto-play for next track
    m_shouldPlayOnLoad = true;
    
    if (m_currentIndex < m_playlist.size() - 1) {
        setCurrentIndex(m_currentIndex + 1);
    } else {
        // Loop to beginning
        setCurrentIndex(0);
    }
}

void MediaController::setCurrentIndex(int index) {
    if (!m_hasPlaylist || index < 0 || index >= m_playlist.size()) {
        return;
    }
    
    m_currentIndex = index;
    loadCurrentItem();
    emit currentIndexChanged(m_currentIndex);
}

void MediaController::setShouldPlayOnLoad(bool shouldPlay) {
    m_shouldPlayOnLoad = shouldPlay;
}

int MediaController::getCurrentIndex() const {
    return m_currentIndex;
}

int MediaController::getPlaylistSize() const {
    return m_playlist.size();
}

bool MediaController::hasPlaylist() const {
    return m_hasPlaylist;
}

void MediaController::loadCurrentItem() {
    if (m_hasPlaylist && m_currentIndex >= 0 && m_currentIndex < m_playlist.size()) {
        m_player->setSource(m_playlist[m_currentIndex]);
        
        // Auto-play if we should play on load (from next/previous) or if currently playing
        if (m_shouldPlayOnLoad || !m_isPaused) {
            m_player->play();
            m_shouldPlayOnLoad = false;  // Reset flag
        }
    }
}

void MediaController::play() {
    m_isPaused = false;
    m_player->play();
}

void MediaController::pause() {
    m_isPaused = true;
    m_player->pause();
}

void MediaController::stop() {
    m_isPaused = true;
    m_player->stop();
}

void MediaController::setPosition(qint64 position) {
    m_player->setPosition(position);
}

void MediaController::seekForward(qint64 seconds) {
    qint64 pos = m_player->position() + seconds * 1000;
    m_player->setPosition(pos);
}

void MediaController::seekBackward(qint64 seconds) {
    qint64 pos = m_player->position() - seconds * 1000;
    if (pos < 0)
        pos = 0;
    m_player->setPosition(pos);
}

void MediaController::setVolume(int percentage) {
    double volume = percentage / 100.0; // QAudioOutput nhận volume từ 0.0 đến 1.0
    m_audioOutput->setVolume(volume);
}

bool MediaController::isPaused() const {
    return m_isPaused;
}

void MediaController::handlePlaybackStateChanged(QMediaPlayer::PlaybackState state) {
    m_isPaused = (state != QMediaPlayer::PlayingState);
    emit playbackStateChanged(state);
}

void MediaController::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia && m_hasPlaylist) {
        // Always use autoNext to handle both next track and loop to beginning
        autoNext();
    }
}

void MediaController::setMedia(const QUrl &url) {
    setSource(url);
}

void MediaController::setVideoOutput(QVideoWidget *videoWidget) {
    m_player->setVideoOutput(videoWidget);
}
