#include "mediafiledao.h"

MediaFileDAO::MediaFileDAO(Database *db)
    : m_db(db) {}

MediaFileDAO::~MediaFileDAO() {}

bool MediaFileDAO::addMediaFile(int playlistId, const MediaFile &file) {
    QSqlQuery query(m_db->connection());
    query.prepare("INSERT INTO media_files (playlist_id, path, title, artist, album, duration, genre, size) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(playlistId);
    query.addBindValue(file.filePath());
    query.addBindValue(file.title());
    query.addBindValue(file.artist());
    query.addBindValue(file.album());
    query.addBindValue(file.duration());
    query.addBindValue(file.genre());
    query.addBindValue(file.fileSize());
    return query.exec();
}

bool MediaFileDAO::removeMediaFile(int mediaFileId) {
    QSqlQuery query(m_db->connection());
    query.prepare("DELETE FROM media_files WHERE id=?");
    query.addBindValue(mediaFileId);
    return query.exec();
}

QList<MediaFile> MediaFileDAO::getMediaFiles(int playlistId) const {
    QList<MediaFile> result;
    QSqlQuery query(m_db->connection());
    query.prepare("SELECT path, title, artist, album, duration, genre, size FROM media_files WHERE playlist_id=?");
    query.addBindValue(playlistId);
    if (query.exec()) {
        while (query.next()) {
            MediaFile file(query.value(0).toString());
            result.append(file);
        }
    }
    return result;
} 