#include "controller/uartcontroller.h"
#include <QDebug>

UARTController::UARTController(QObject *parent)
    : QObject(parent)
    , videoView(nullptr)
    , audioView(nullptr)
{
}

void UARTController::setVideoView(VideoView *view)
{
    videoView = view;
}

void UARTController::setAudioView(AudioView *view)
{
    audioView = view;
}

void UARTController::handleControlCommand(const QString &command)
{
    if (command == "stop") {
        if (videoView) {
            videoView->handleUARTCommand("stop");
        }
        if (audioView) {
            audioView->handleUARTCommand("stop");
        }
    }
    else if (command == "play_pause") {
        if (videoView) {
            videoView->handleUARTCommand("play_pause");
        }
        if (audioView) {
            audioView->handleUARTCommand("play_pause");
        }
    }
    else if (command == "previous") {
        if (videoView) {
            videoView->handleUARTCommand("previous");
        }
        if (audioView) {
            audioView->handleUARTCommand("previous");
        }
    }
    else if (command == "next") {
        if (videoView) {
            videoView->handleUARTCommand("next");
        }
        if (audioView) {
            audioView->handleUARTCommand("next");
        }
    }
}

void UARTController::handleNumber(int number)
{
    if (number >= 0 && number <= 100) {
        if (videoView) {
            videoView->handleUARTNumber(number);
        }
        if (audioView) {
            audioView->handleUARTNumber(number);
        }
    }
}

void UARTController::handleError(const QString &error)
{
    if (videoView) {
        videoView->handleUARTError(error);
    }
    if (audioView) {
        audioView->handleUARTError(error);
    }
} 