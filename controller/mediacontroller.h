#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QtCore>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtWidgets>

class MediaController : public QObject
{
    Q_OBJECT

public:
    explicit MediaController(QObject *parent = nullptr);
    ~MediaController();

    // Getters
    QMediaPlayer* getPlayer() const;
    QAudioOutput* getAudioOutput() const;
    bool isPaused() const;

    // Media Source Control
    void setSource(const QUrl &url);
    void setMedia(const QUrl &url);  // Alias for setSource
    void setVideoOutput(QVideoWidget *videoWidget);

    // Media Playback Control
    void play();
    void pause();
    void stop();
    void setPosition(qint64 position);
    void seekForward(qint64 seconds);
    void seekBackward(qint64 seconds);
    void setVolume(int percentage);

signals:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void playbackStateChanged(QMediaPlayer::PlaybackState state);

private slots:
    void handlePlaybackStateChanged(QMediaPlayer::PlaybackState state);

private:
    // Media Components
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    bool m_isPaused;
};

#endif // MEDIACONTROLLER_H
