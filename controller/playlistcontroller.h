#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <QtWidgets>
#include <QtMultimedia>

#include "../model/playlist.h"
#include "../model/uartreceiver.h"

#include "mediacontroller.h"

#include "database/database.h"
#include "database/mediafiledao.h"

namespace Ui {
class PlaylistWindow;
}

class PlaylistWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaylistWindow(Playlist *playlist, Database *db, QWidget *parent = nullptr);
    ~PlaylistWindow();

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
    void on_volumeButton_clicked();
    
    // MediaController slots
    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);
    void updateMetadata();
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handleStateChanged(QMediaPlayer::PlaybackState state);
    void handleCurrentIndexChanged(int index);
    void handlePlaylistEnded();
    void toggleFullScreen();

private:
    // UI Components
    Ui::PlaylistWindow *ui;
    Playlist *m_playlist;
    MediaController *m_controller;
    UARTReceiver *uartReceiver;

    // Media State
    int m_currentIndex;
    bool m_isPlaying;
    bool isMuted = false;

    // Setup Methods
    void setupUI();
    void setupConnections();
    void setupStyle();
    void updatePlaylistModel();
    void loadPlaylist();
    void updateCurrentFileInfo();
    QString formatTime(qint64 ms) const;

    Database *m_db;
};

#endif // PLAYLISTCONTROLLER_H 
