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
    return query.lastInsertId().toInt();
}

bool PlaylistDAO::updatePlaylist(const Playlist &playlist) {
    QSqlQuery query(m_db->connection());
    query.prepare("UPDATE playlists SET name=?, modified_at=? WHERE id=?");
    query.addBindValue(playlist.name());
    query.addBindValue(playlist.modifiedAt().toString(Qt::ISODate));
    query.addBindValue(playlist.id());
    return query.exec();
}

bool PlaylistDAO::deletePlaylist(int playlistId)
{
    QSqlQuery query(m_db->connection());
    query.prepare("DELETE FROM playlists WHERE id = ?");
    query.addBindValue(playlistId);
    return query.exec();
}

QList<Playlist> PlaylistDAO::getAllPlaylists()
{
    QList<Playlist> playlists;
    QSqlQuery query(m_db->connection());
    query.prepare("SELECT id, name, created_at, modified_at FROM playlists ORDER BY name");
    
    if (query.exec()) {
        while (query.next()) {
            Playlist playlist;
            playlist.setId(query.value("id").toInt());
            playlist.setName(query.value("name").toString());
            playlist.setCreatedAt(query.value("created_at").toDateTime());
            playlist.setModifiedAt(query.value("modified_at").toDateTime());
            playlists.append(playlist);
        }
    }
    
    return playlists;
}

Playlist PlaylistDAO::getPlaylistById(int playlistId) const {
    QSqlQuery query(m_db->connection());
    query.prepare("SELECT id, name, created_at, modified_at FROM playlists WHERE id=?");
    query.addBindValue(playlistId);
    if (query.exec() && query.next()) {
        Playlist playlist;
        playlist.setId(query.value("id").toInt());
        playlist.setName(query.value("name").toString());
        playlist.setCreatedAt(query.value("created_at").toDateTime());
        playlist.setModifiedAt(query.value("modified_at").toDateTime());
        return playlist;
    }
    return Playlist();
} 