#include "controller/mediacontroller.h"

MediaController::MediaController(QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this)),
      m_isPaused(true)
{
    m_player->setAudioOutput(m_audioOutput);
    
    // Chuyển các tín hiệu từ m_player ra ngoài controller để view kết nối
    connect(m_player, &QMediaPlayer::durationChanged, this, &MediaController::durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MediaController::positionChanged);
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &MediaController::handlePlaybackStateChanged);
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
