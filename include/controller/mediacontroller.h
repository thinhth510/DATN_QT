#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>

class MediaController : public QObject
{
    Q_OBJECT

public:
    explicit MediaController(QObject *parent = nullptr);
    ~MediaController();

    QMediaPlayer* getPlayer() const;
    QAudioOutput* getAudioOutput() const;
    bool isPaused() const;

    // Thiết lập nguồn media (audio hoặc video)
    void setSource(const QUrl &url);
    void setMedia(const QUrl &url);  // Alias for setSource
    void setVideoOutput(QVideoWidget *videoWidget);

    // Các chức năng điều khiển media
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
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    bool m_isPaused;
};

#endif // MEDIACONTROLLER_H
