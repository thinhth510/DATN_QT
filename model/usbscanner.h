#ifndef USBSCANNER_H
#define USBSCANNER_H

#include <QtCore> 
class USBScanner : public QObject
{
    Q_OBJECT

public:
    explicit USBScanner(QObject *parent = nullptr);
    QStringList scanForMediaFiles();

signals:
    void scanCompleted(const QStringList &mediaFiles);
    void scanError(const QString &error);

private:
    QStringList findUSBDrives();
    QStringList scanDirectoryForMedia(const QString &path);
    bool isMediaFile(const QString &filename);
};

#endif // USBSCANNER_H 