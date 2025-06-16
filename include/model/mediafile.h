/**
 * @file mediafile.h
 * @brief Định nghĩa lớp MediaFile - đại diện cho một file media (audio/video)
 */
#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QtCore>
#include <QtMultimedia>

/**
 * @class MediaFile
 * @brief Lớp quản lý thông tin và metadata của file media
 * 
 * Lớp này đóng gói các thông tin về file media như:
 * - Thông tin cơ bản (tên file, đường dẫn, kích thước)
 * - Metadata (title, artist, album)
 * - Thông tin kỹ thuật (duration, type)
 */
class MediaFile {
public:
    /**
     * @enum Type
     * @brief Định nghĩa các loại file media được hỗ trợ
     */
    enum Type {
        Audio,    ///< File âm thanh (mp3, wav)
        Video,    ///< File video (mp4, avi)
        Unknown   ///< Loại file không xác định
    };

    /**
     * @brief Constructor
     * @param filePath Đường dẫn đến file media
     */
    MediaFile(const QString &filePath = "");
    
    /**
     * @brief Destructor
     */
    ~MediaFile();

    // File Information Methods
    QString filePath() const;     ///< Lấy đường dẫn đầy đủ của file
    QString fileName() const;      ///< Lấy tên file
    QString title() const;        ///< Lấy tiêu đề từ metadata
    QString artist() const;       ///< Lấy tên nghệ sĩ từ metadata
    QString album() const;        ///< Lấy tên album từ metadata
    QString composer() const;
    QString genre() const;
    qint64 duration() const;      ///< Lấy độ dài (milliseconds)
    QString durationString() const; ///< Lấy độ dài dạng chuỗi (mm:ss)
    qint64 fileSize() const;      ///< Lấy kích thước file (bytes)
    QString fileSizeString() const; ///< Lấy kích thước dạng chuỗi (KB/MB/GB)
    Type type() const;            ///< Lấy loại file (Audio/Video)
    QDateTime lastModified() const; ///< Lấy thời gian chỉnh sửa cuối
    QString typeString() const;    ///< Lấy loại file dạng chuỗi

    /**
     * @brief Load metadata từ file media
     * 
     * Phương thức này sẽ:
     * 1. Đọc thông tin cơ bản từ file system
     * 2. Xác định loại file dựa vào phần mở rộng
     * 3. Load metadata sử dụng QMediaPlayer
     */
    void loadMetadata();

    /**
     * @brief Kiểm tra file có hợp lệ không
     * @return true nếu file tồn tại và load metadata thành công
     */
    bool isValid() const;

private:
    QString m_filePath;       ///< Đường dẫn đến file
    QString m_title;          ///< Tiêu đề từ metadata
    QString m_artist;         ///< Tên nghệ sĩ từ metadata
    QString m_album;          ///< Tên album từ metadata
    QString m_composer;       ///< Tên composer từ metadata
    QString m_genre;          ///< Thể loại từ metadata
    qint64 m_duration;        ///< Độ dài (milliseconds)
    qint64 m_fileSize;        ///< Kích thước file (bytes)
    Type m_type;             ///< Loại file (Audio/Video)
    QDateTime m_lastModified; ///< Thời gian chỉnh sửa cuối
    bool m_isValid;          ///< Trạng thái hợp lệ của file
};

#endif // MEDIAFILE_H 