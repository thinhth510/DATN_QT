#ifndef USBSCANNERMODEL_H
#define USBSCANNERMODEL_H

#include <QtCore> 
class USBScannerModel : public QObject
{
    Q_OBJECT

public:
    explicit USBScannerModel(QObject *parent = nullptr);
    QStringList scanForMediaFiles();

signals:
    void scanCompleted(const QStringList &mediaFiles);
    void scanError(const QString &error);

private:
    QStringList findUSBDrives();
    QStringList scanDirectoryForMedia(const QString &path);
    bool isMediaFile(const QString &filename);
};

#endif // USBSCANNERMODEL_H 