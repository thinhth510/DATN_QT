#ifndef PLAYLISTDAO_H
#define PLAYLISTDAO_H

#include <QtCore> // Bao gồm QString, QList, QVariant, QDebug
#include <QtSql> // Bao gồm QSqlQuery, QSqlError

#include "database.h"
#include "../model/playlist.h"

class PlaylistDAO {
public:
    PlaylistDAO(Database *db);
    ~PlaylistDAO();

    int addPlaylist(const Playlist &playlist);
    bool updatePlaylist(const Playlist &playlist);
    bool deletePlaylist(int playlistId);
    QList<Playlist> getAllPlaylists();
    Playlist getPlaylistById(int playlistId) const;

    // XÓA các hàm thao tác media file khỏi đây
    // bool addMediaFile(int playlistId, const MediaFile &file);
    // bool removeMediaFile(int mediaFileId);
    // QList<MediaFile> getMediaFiles(int playlistId) const;

private:
    Database *m_db;
};

#endif // PLAYLISTDAO_H 