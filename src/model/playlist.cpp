#include "model/playlist.h"

Playlist::Playlist(const QString &name)
    : m_name(name)
    , m_createdAt(QDateTime::currentDateTime())
    , m_modifiedAt(QDateTime::currentDateTime())
{
}

Playlist::~Playlist()
{
}

QString Playlist::name() const
{
    return m_name;
}

void Playlist::setName(const QString &name)
{
    m_name = name;
    m_modifiedAt = QDateTime::currentDateTime();
}

QList<MediaFile> Playlist::mediaFiles() const
{
    return m_mediaFiles;
}

void Playlist::addMediaFile(const QString &filePath)
{
    MediaFile file(filePath);
    if (file.isValid()) {
        for (const MediaFile &existingFile : m_mediaFiles) {
            if (existingFile.filePath() == filePath) {
                return;
            }
        }
        m_mediaFiles.append(file);
        m_modifiedAt = QDateTime::currentDateTime();
    }
}

void Playlist::removeMediaFile(const QString &filePath)
{
    for (int i = 0; i < m_mediaFiles.size(); ++i) {
        if (m_mediaFiles[i].filePath() == filePath) {
            m_mediaFiles.removeAt(i);
            m_modifiedAt = QDateTime::currentDateTime();
            break;
        }
    }
}

void Playlist::clear()
{
    if (!m_mediaFiles.isEmpty()) {
        m_mediaFiles.clear();
        m_modifiedAt = QDateTime::currentDateTime();
    }
}

int Playlist::totalDuration() const
{
    int total = 0;
    for (const MediaFile &file : m_mediaFiles) {
        total += file.duration();
    }
    return total;
}

QString Playlist::totalDurationString() const
{
    int totalMs = totalDuration();
    int seconds = totalMs / 1000;
    int minutes = seconds / 60;
    int hours = minutes / 60;
    minutes = minutes % 60;
    seconds = seconds % 60;

    if (hours > 0) {
        return QString("%1:%2:%3")
            .arg(hours)
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
    }
    return QString("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}

int Playlist::fileCount() const
{
    return m_mediaFiles.size();
}

qint64 Playlist::totalSize() const
{
    qint64 total = 0;
    for (const MediaFile &file : m_mediaFiles) {
        total += file.fileSize();
    }
    return total;
}

QString Playlist::totalSizeString() const
{
    double size = totalSize();
    QStringList units = {"B", "KB", "MB", "GB"};
    int unitIndex = 0;
    
    while (size >= 1024 && unitIndex < units.size() - 1) {
        size /= 1024;
        unitIndex++;
    }
    
    return QString("%1 %2").arg(size, 0, 'f', 1).arg(units[unitIndex]);
}

QDateTime Playlist::createdAt() const
{
    return m_createdAt;
}

QDateTime Playlist::modifiedAt() const
{
    return m_modifiedAt;
}

bool Playlist::save() const
{
    QJsonObject json;
    json["name"] = m_name;
    json["createdAt"] = m_createdAt.toString(Qt::ISODate);
    json["modifiedAt"] = m_modifiedAt.toString(Qt::ISODate);
    
    QJsonArray files;
    for (const MediaFile &file : m_mediaFiles) {
        QJsonObject fileObj;
        fileObj["path"] = file.filePath();
        fileObj["title"] = file.title();
        fileObj["artist"] = file.artist();
        fileObj["album"] = file.album();
        fileObj["duration"] = file.duration();
        files.append(fileObj);
    }
    json["files"] = files;
    
    QJsonDocument doc(json);
    QFile file(m_name + ".playlist");
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    file.write(doc.toJson());
    return true;
}

bool Playlist::load(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) {
        return false;
    }
    
    QJsonObject json = doc.object();
    m_name = json["name"].toString();
    m_createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    m_modifiedAt = QDateTime::fromString(json["modifiedAt"].toString(), Qt::ISODate);
    
    m_mediaFiles.clear();
    QJsonArray files = json["files"].toArray();
    for (const QJsonValue &value : files) {
        QJsonObject fileObj = value.toObject();
        QString path = fileObj["path"].toString();
        addMediaFile(path);
    }
    
    return true;
} 