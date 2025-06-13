#ifndef UARTCONTROLLER_H
#define UARTCONTROLLER_H

#include <QtCore>
#include "view/videoview.h"
#include "view/audioview.h"

class UARTController : public QObject
{
    Q_OBJECT

public:
    explicit UARTController(QObject *parent = nullptr);

    // View Management
    void setVideoView(VideoView *view);
    void setAudioView(AudioView *view);

public slots:
    // UART Command Handlers
    void handleControlCommand(const QString &command);
    void handleNumber(int number);
    void handleError(const QString &error);

private:
    // View References
    VideoView *videoView;
    AudioView *audioView;
};

#endif // UARTCONTROLLER_H 