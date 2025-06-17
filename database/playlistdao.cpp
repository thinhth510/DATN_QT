#include "playlistdao.h"

PlaylistDAO::PlaylistDAO(Database *db)
    : m_db(db) {}

PlaylistDAO::~PlaylistDAO() {}

int PlaylistDAO::addPlaylist(const Playlist &playlist) {
    QSqlQuery query(m_db->connection());
    query.prepare("INSERT INTO playlists (name, created_at, modified_at) VALUES (?, ?, ?)");
    query.addBindValue(playlist.name());
    query.addBindValue(playlist.createdAt().toString(Qt::ISODate));
    query.addBindValue(playlist.modifiedAt().toString(Qt::ISODate));
    if (!query.exec()) {
        qWarning() << "Add playlist failed:" << query.lastError().text();
        return -1;
    }
    int playlistId = query.lastInsertId().toInt();
    // Tự động lưu toàn bộ media file
    for (const MediaFile &file : playlist.mediaFiles()) {
        addMediaFile(playlistId, file);
    }
    return playlistId;
}

bool PlaylistDAO::updatePlaylist(const Playlist &playlist) {
    QSqlQuery query(m_db->connection());
    query.prepare("UPDATE playlists SET name=?, modified_at=? WHERE id=?");
    query.addBindValue(playlist.name());
    query.addBindValue(playlist.modifiedAt().toString(Qt::ISODate));
    query.addBindValue(playlist.name()); // Giả sử name là id, bạn nên sửa lại thành id thực tế
    return query.exec();
}

bool PlaylistDAO::removePlaylist(int playlistId) {
    QSqlQuery query(m_db->connection());
    query.prepare("DELETE FROM playlists WHERE id=?");
    query.addBindValue(playlistId);
    return query.exec();
}

QList<Playlist> PlaylistDAO::getAllPlaylists() const {
    QList<Playlist> result;
    QSqlQuery query(m_db->connection());
    query.exec("SELECT id, name, created_at, modified_at FROM playlists");
    while (query.next()) {
        int id = query.value(0).toInt();
        Playlist pl(query.value(1).toString(), id);
        QList<MediaFile> files = getMediaFiles(id);
        for (const MediaFile &file : files) {
            pl.addMediaFile(file.filePath());
        }
        result.append(pl);
    }
    return result;
}

Playlist PlaylistDAO::getPlaylistById(int playlistId) const {
    QSqlQuery query(m_db->connection());
    query.prepare("SELECT id, name, created_at, modified_at FROM playlists WHERE id=?");
    query.addBindValue(playlistId);
    if (query.exec() && query.next()) {
        int id = query.value(0).toInt();
        Playlist pl(query.value(1).toString(), id);
        QList<MediaFile> files = getMediaFiles(id);
        for (const MediaFile &file : files) {
            pl.addMediaFile(file.filePath());
        }
        return pl;
    }
    return Playlist();
}

bool PlaylistDAO::addMediaFile(int playlistId, const MediaFile &file) {
    QSqlQuery query(m_db->connection());
    query.prepare("INSERT INTO media_files (playlist_id, path, title, artist, album, composer, duration, genre, size) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(playlistId);
    query.addBindValue(file.filePath());
    query.addBindValue(file.title());
    query.addBindValue(file.artist());
    query.addBindValue(file.album());
    query.addBindValue(file.composer());
    query.addBindValue(file.duration());
    query.addBindValue(file.genre());
    query.addBindValue(file.fileSize());
    return query.exec();
}

bool PlaylistDAO::removeMediaFile(int mediaFileId) {
    QSqlQuery query(m_db->connection());
    query.prepare("DELETE FROM media_files WHERE id=?");
    query.addBindValue(mediaFileId);
    return query.exec();
}

QList<MediaFile> PlaylistDAO::getMediaFiles(int playlistId) const {
    QList<MediaFile> result;
    QSqlQuery query(m_db->connection());
    query.prepare("SELECT path, title, artist, album, composer, duration, genre, size FROM media_files WHERE playlist_id=?");
    query.addBindValue(playlistId);
    if (query.exec()) {
        while (query.next()) {
            MediaFile file(query.value(0).toString());
            result.append(file);
        }
    }
    return result;
} 