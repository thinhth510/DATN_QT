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

    // Playlist Control
    void setPlaylist(const QList<QUrl> &urls);
    void setPlaylist(const QStringList &filePaths);
    void previous();
    void next();
    void autoNext();  // Auto-next with forced play
    void setCurrentIndex(int index);
    void setShouldPlayOnLoad(bool shouldPlay);  // Set auto-play flag
    int getCurrentIndex() const;
    int getPlaylistSize() const;
    bool hasPlaylist() const;

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
    void currentIndexChanged(int index);
    void playlistEnded();

private slots:
    void handlePlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    // Media Components
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    bool m_isPaused;
    
    // Playlist Components
    QList<QUrl> m_playlist;
    int m_currentIndex;
    bool m_hasPlaylist;
    bool m_shouldPlayOnLoad;  // Track if we should play when loading new item
    
    // Helper Methods
    void loadCurrentItem();
};

#endif // MEDIACONTROLLER_H
