#ifndef MEDIAFILEDAO_H
#define MEDIAFILEDAO_H

#include <QtCore>
#include <QtSql>
#include "../model/mediafile.h"
#include "database.h"

class MediaFileDAO {
public:
    MediaFileDAO(Database *db);
    ~MediaFileDAO();

    bool addMediaFile(int playlistId, const MediaFile &file);
    bool removeMediaFile(int mediaFileId);
    QList<MediaFile> getMediaFiles(int playlistId) const;

private:
    Database *m_db;
};

#endif // MEDIAFILEDAO_H 