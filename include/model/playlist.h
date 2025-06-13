/**
 * @file playlist.h
 * @brief Định nghĩa lớp Playlist - quản lý danh sách phát media
 */
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtCore>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
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
     */
    Playlist(const QString &name = "");
    
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

    // Media File Management
    /**
     * @brief Lấy danh sách các file media
     * @return QList chứa các MediaFile
     */
    QList<MediaFile> mediaFiles() const;
    
    /**
     * @brief Thêm file media vào playlist
     * @param filePath Đường dẫn đến file media
     */
    void addMediaFile(const QString &filePath);
    
    /**
     * @brief Xóa file media khỏi playlist
     * @param filePath Đường dẫn đến file cần xóa
     */
    void removeMediaFile(const QString &filePath);
    
    /**
     * @brief Xóa tất cả file media khỏi playlist
     */
    void clear();

    // Playlist Statistics
    /**
     * @brief Tính tổng thời lượng của playlist
     * @return Tổng thời lượng (milliseconds)
     */
    int totalDuration() const;
    
    /**
     * @brief Lấy tổng thời lượng dạng chuỗi (HH:MM:SS)
     * @return Chuỗi biểu diễn thời lượng
     */
    QString totalDurationString() const;
    
    /**
     * @brief Đếm số lượng file trong playlist
     * @return Số lượng file
     */
    int fileCount() const;
    
    /**
     * @brief Tính tổng kích thước của các file
     * @return Tổng kích thước (bytes)
     */
    qint64 totalSize() const;
    
    /**
     * @brief Lấy tổng kích thước dạng chuỗi (KB/MB/GB)
     * @return Chuỗi biểu diễn kích thước
     */
    QString totalSizeString() const;

    // Timestamp Information
    /**
     * @brief Lấy thời điểm tạo playlist
     * @return QDateTime của thời điểm tạo
     */
    QDateTime createdAt() const;
    
    /**
     * @brief Lấy thời điểm chỉnh sửa cuối
     * @return QDateTime của lần chỉnh sửa cuối
     */
    QDateTime modifiedAt() const;

    // Persistence Operations
    /**
     * @brief Lưu playlist vào file
     * @return true nếu lưu thành công
     */
    bool save() const;
    
    /**
     * @brief Load playlist từ file
     * @param filePath Đường dẫn đến file playlist
     * @return true nếu load thành công
     */
    bool load(const QString &filePath);

private:
    QString m_name;              ///< Tên của playlist
    QList<MediaFile> m_mediaFiles; ///< Danh sách các file media
    QDateTime m_createdAt;       ///< Thời điểm tạo playlist
    QDateTime m_modifiedAt;      ///< Thời điểm chỉnh sửa cuối
};

#endif // PLAYLIST_H 