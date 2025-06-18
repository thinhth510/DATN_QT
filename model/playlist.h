/**
 * @file playlist.h
 * @brief Định nghĩa lớp Playlist - quản lý danh sách phát media
 */
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtCore>
#include "mediafile.h"

/**
 * @class Playlist
 * @brief Lớp quản lý danh sách phát media
 * 
 * Lớp này quản lý:
 * - Danh sách các file media
 * - Thông tin về playlist (tên, thời gian tạo/sửa)
 * - Các thao tác với playlist (thêm/xóa/lưu/load)
 */
class Playlist {
public:
    /**
     * @brief Constructor
     * @param name Tên của playlist
     * @param id id của playlist trong database
     */
    Playlist(const QString &name = "", int id = -1);
    
    /**
     * @brief Destructor
     */
    ~Playlist();

    // Basic Playlist Information
    /**
     * @brief Lấy tên playlist
     * @return Tên của playlist
     */
    QString name() const;
    
    /**
     * @brief Đặt tên cho playlist
     * @param name Tên mới của playlist
     */
    void setName(const QString &name);

    // Timestamp Information
    /**
     * @brief Lấy thời điểm tạo playlist
     * @return QDateTime của thời điểm tạo
     */
    QDateTime createdAt() const;
    
    /**
     * @brief Đặt thời điểm tạo playlist
     * @param createdAt Thời điểm tạo mới
     */
    void setCreatedAt(const QDateTime &createdAt);
    
    /**
     * @brief Lấy thời điểm chỉnh sửa cuối
     * @return QDateTime của lần chỉnh sửa cuối
     */
    QDateTime modifiedAt() const;
    
    /**
     * @brief Đặt thời điểm chỉnh sửa cuối
     * @param modifiedAt Thời điểm chỉnh sửa mới
     */
    void setModifiedAt(const QDateTime &modifiedAt);

    // Persistence Operations
    // (Đã chuyển sang DAO, không còn lưu file ở đây)

    int id() const { return m_id; }
    void setId(int id) { m_id = id; }

private:
    QString m_name;              ///< Tên của playlist
    // QList<MediaFile> m_mediaFiles; ///< Đã bỏ, không giữ metadata trong RAM
    QDateTime m_createdAt;       ///< Thời điểm tạo playlist
    QDateTime m_modifiedAt;      ///< Thời điểm chỉnh sửa cuối
    int m_id; // id của playlist trong database
};

#endif // PLAYLIST_H 