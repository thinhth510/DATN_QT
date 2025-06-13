#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QtWidgets>
#include <QtMultimedia>

#include "../model/playlist.h"
#include "../model/uartreceiver.h"

namespace Ui {
class PlaylistView;
}

class PlaylistView : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaylistView(Playlist *playlist, QWidget *parent = nullptr);
    ~PlaylistView();

    // UART Interface
    void handleUARTCommand(const QString &command);
    void handleUARTNumber(int number);
    void handleUARTError(const QString &error);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Media Control Slots
    void on_playButton_clicked();
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void on_stopButton_clicked();
    void on_volumeSlider_valueChanged(int value);
    void on_positionSlider_sliderMoved(int position);
    void on_playlistView_doubleClicked(const QModelIndex &index);
    
    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);
    void updateMetadata();
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handleStateChanged(QMediaPlayer::PlaybackState state);
    void toggleFullScreen();

private:
    // UI Components
    Ui::PlaylistView *ui;
    Playlist *m_playlist;
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    UARTReceiver *uartReceiver;

    // Media State
    int m_currentIndex;
    bool m_isPlaying;

    // Setup Methods
    void setupUI();
    void setupConnections();
    void setupStyle();
    void updatePlaylistModel();
    void loadFile(int index);
    void updateCurrentFileInfo();
    QString formatTime(qint64 ms) const;
};

#endif // PLAYLISTVIEW_H 
