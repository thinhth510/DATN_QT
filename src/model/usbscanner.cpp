#include "../../include/model/usbscanner.h"

USBScanner::USBScanner(QObject *parent)
    : QObject(parent)
{
}

QStringList USBScanner::scanForMediaFiles()
{
    QStringList allMediaFiles;
    QStringList usbDrives = findUSBDrives();

    if (usbDrives.isEmpty()) {
        emit scanError(tr("No USB drives found"));
        return allMediaFiles;
    }

    for (const QString &drive : usbDrives) {
        allMediaFiles.append(scanDirectoryForMedia(drive));
    }

    emit scanCompleted(allMediaFiles);
    return allMediaFiles;
}

QStringList USBScanner::findUSBDrives()
{
    QStringList usbDrives;
    const QList<QStorageInfo> drives = QStorageInfo::mountedVolumes();

    for (const QStorageInfo &drive : drives) {
        // Check if it's a removable drive (USB)
        if (drive.isValid() && drive.isReady()) {
            QString path = drive.rootPath();
            // Check if the drive is removable by checking its mount point
            if (path.startsWith("/media/") || path.startsWith("/mnt/")) {
                usbDrives.append(path);
            }
        }
    }

    return usbDrives;
}

QStringList USBScanner::scanDirectoryForMedia(const QString &path)
{
    QStringList mediaFiles;
    QDir dir(path);
    
    // Get all files in the directory
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    
    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            // Recursively scan subdirectories
            mediaFiles.append(scanDirectoryForMedia(entry.absoluteFilePath()));
        } else if (isMediaFile(entry.fileName())) {
            mediaFiles.append(entry.absoluteFilePath());
        }
    }
    
    return mediaFiles;
}

bool USBScanner::isMediaFile(const QString &filename)
{
    QStringList mediaExtensions = {".mp3", ".mp4", ".wav", ".avi"};
    return std::any_of(mediaExtensions.begin(), mediaExtensions.end(),
                      [&filename](const QString &ext) {
                          return filename.endsWith(ext, Qt::CaseInsensitive);
                      });
} 