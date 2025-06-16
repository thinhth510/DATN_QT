#include "../../include/model/mediafile.h"

MediaFile::MediaFile(const QString &filePath)
    : m_filePath(filePath)
    , m_duration(0)
    , m_fileSize(0)
    , m_type(Unknown)
    , m_isValid(false)
{
    if (!filePath.isEmpty()) {
        loadMetadata();
    }
}

MediaFile::~MediaFile()
{
}

QString MediaFile::filePath() const
{
    return m_filePath;
}

QString MediaFile::fileName() const
{
    QFileInfo fileInfo(m_filePath);
    return fileInfo.fileName();
}

QString MediaFile::title() const
{
    return m_title.isEmpty() ? fileName() : m_title;
}

QString MediaFile::artist() const
{
    return m_artist;
}

QString MediaFile::album() const
{
    return m_album;
}

QString MediaFile::composer() const
{
    return m_composer;
}


QString MediaFile::genre() const
{
    return m_genre;
}

qint64 MediaFile::duration() const
{
    return m_duration;
}

QString MediaFile::durationString() const
{
    qint64 seconds = m_duration / 1000;
    qint64 minutes = seconds / 60;
    seconds = seconds % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

qint64 MediaFile::fileSize() const
{
    return m_fileSize;
}

QString MediaFile::fileSizeString() const
{
    double size = m_fileSize;
    QStringList units = {"B", "KB", "MB", "GB"};
    int unitIndex = 0;
    
    while (size >= 1024 && unitIndex < units.size() - 1) {
        size /= 1024;
        unitIndex++;
    }
    
    return QString("%1 %2").arg(size, 0, 'f', 1).arg(units[unitIndex]);
}

MediaFile::Type MediaFile::type() const
{
    return m_type;
}

QDateTime MediaFile::lastModified() const
{
    return m_lastModified;
}

QString MediaFile::typeString() const
{
    switch (m_type) {
        case Audio: return "Audio";
        case Video: return "Video";
        default: return "Unknown";
    }
}

void MediaFile::loadMetadata()
{
    QFileInfo fileInfo(m_filePath);
    if (!fileInfo.exists()) {
        m_isValid = false;
        return;
    }

    // Basic file info
    m_fileSize = fileInfo.size();
    m_lastModified = fileInfo.lastModified();
    
    // Determine type
    QString suffix = fileInfo.suffix().toLower();
    if (suffix == "mp3" || suffix == "wav") {
        m_type = Audio;
    } else if (suffix == "mp4" || suffix == "avi") {
        m_type = Video;
    }

    // Load media metadata
    QMediaPlayer player;
    player.setSource(QUrl::fromLocalFile(m_filePath));

    // Wait for metadata to be loaded
    QEventLoop loop;
    QObject::connect(&player, &QMediaPlayer::metaDataChanged, &loop, &QEventLoop::quit);
    loop.exec();

    // Get metadata
    const QMediaMetaData &metadata = player.metaData();
    m_title = metadata.stringValue(QMediaMetaData::Title);
    m_artist = metadata.stringValue(QMediaMetaData::AlbumArtist);
    m_album = metadata.stringValue(QMediaMetaData::AlbumTitle);
    m_composer = metadata.stringValue(QMediaMetaData::ContributingArtist);
    m_genre = metadata.stringValue(QMediaMetaData::Genre);
    m_duration = player.duration();
    qDebug() << "Loaded metadata for file:" << m_filePath << ", Composer:" << m_composer;
    m_isValid = true;
}

bool MediaFile::isValid() const
{
    return m_isValid;
} 
