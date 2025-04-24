#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QtMultimedia>
#include <QtCore>

class MediaController : public QObject {
    Q_OBJECT
public:
    explicit MediaController(QObject *parent = nullptr);
    ~MediaController();

    QMediaPlayer* getPlayer() const;
    QAudioOutput* getAudioOutput() const;

    // Thiết lập nguồn media (audio hoặc video)
    void setSource(const QUrl &url);

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

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
};

#endif // MEDIACONTROLLER_H
