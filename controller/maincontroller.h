/**
 * @file mainwindow.h
 * @brief Định nghĩa lớp MainWindow - cửa sổ chính của ứng dụng media player
 */
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QtWidgets> // Bao gồm QFileDialog, QMessageBox
#include <QtCore>
#include <QtGui> // Bao gồm QScreen, QGuiApplication
#include <QtSql> // Bao gồm QSqlQuery

#include "videocontroller.h"      
#include "audiocontroller.h"    
#include "playlistcontroller.h" 

#include "../view/virtualkeyboard.h"
  
#include "../model/playlist.h"  
#include "../model/usbscanner.h"  

#include "database/database.h"
#include "database/playlistdao.h"
#include "database/mediafiledao.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Lớp chính quản lý giao diện và logic của ứng dụng
 * 
 * MainWindow kế thừa từ QMainWindow và triển khai các chức năng:
 * - Quản lý và phát file media (audio/video)
 * - Quản lý playlist
 * - Duyệt và tìm kiếm file media
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT  // Macro cho phép sử dụng Qt's signals và slots

public:
    /**
     * @brief Constructor
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor - Giải phóng tài nguyên
     */
    ~MainWindow();

protected:
    /**
     * @brief Override closeEvent để xử lý khi đóng cửa sổ
     * @param event Event đóng cửa sổ
     */
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Media File Operations
    /**
     * @brief Xử lý khi người dùng mở file audio
     */
    void on_actionOpen_Audio_triggered();
    
    /**
     * @brief Xử lý khi người dùng mở file video
     */
    void on_actionOpen_Video_triggered();
    
    void on_actionScan_USB_triggered();

    // Browse Media Files
    /**
     * @brief Mở dialog cho phép chọn thư mục chứa media
     */
    void on_actionBrowseFolder_triggered();
    
    /**
     * @brief Xử lý khi double click vào file trong tree view
     * @param index Model index của item được click
     */
    void on_mediaTreeView_doubleClicked(const QModelIndex &index);
    
    /**
     * @brief Lọc file media theo text tìm kiếm
     * @param text Chuỗi tìm kiếm
     */
    void on_searchLineEdit_textChanged(const QString &text);
    
    // Playlist Management
    /**
     * @brief Tạo playlist mới
     */
    void on_actionNewPlaylist_triggered();
    
    /**
     * @brief Xóa playlist hiện tại
     */
    void on_actionDeletePlaylist_triggered();
    
    /**
     * @brief Xử lý khi chuyển đổi playlist
     * @param index Index của playlist được chọn
     */
    void on_playlistComboBox_currentIndexChanged(int index);
    
    /**
     * @brief Thêm file media vào playlist
     */
    void on_addToPlaylistButton_clicked();
    
    /**
     * @brief Xóa file media khỏi playlist
     */
    void on_removeFromPlaylistButton_clicked();
    
    /**
     * @brief Phát file media được chọn
     */
    void on_playButton_clicked();

    void toggleFullScreen();

    void on_actionToggle_Fullscreen_triggered();

    void on_actionExit_App_triggered();

private:
    // UI Components
    Ui::MainWindow *ui;                   // Con trỏ đến UI được tạo bởi Qt Designer
    QFileSystemModel *m_fileModel;        // Model quản lý file system
    QStringListModel *m_playlistModel;    // Model quản lý danh sách trong playlist
    QList<Playlist> m_playlists;          // Danh sách các playlist
    Playlist *m_currentPlaylist;          // Con trỏ đến playlist hiện tại
    QPointer<PlaylistWindow> m_playlistWindow;         // Window hiển thị playlist
    QString m_currentMediaPath;           // Đường dẫn thư mục media hiện tại
    VirtualKeyboard *m_virtualKeyboard;   // Bàn phím ảo
    Database *m_db;
    PlaylistDAO *m_playlistDao;

    // Setup Methods
    void setupUI();           // Thiết lập giao diện người dùng
    void setupMediaBrowser(); // Thiết lập trình duyệt media
    void setupPlaylistManager(); // Thiết lập quản lý playlist
    void setupVirtualKeyboard(); // Thiết lập bàn phím ảo
    
    // Playlist Operations
    void loadPlaylists();     // Load danh sách playlist từ file
    void savePlaylists();     // Lưu danh sách playlist vào file
    
    // Media List Operations
    void updateMediaList(const QString &path);  // Cập nhật danh sách media
    void filterMediaFiles(const QString &filter); // Lọc file media
    void updatePlaylistModel(); // Cập nhật model playlist

    // Event filter để bắt sự kiện focus của QLineEdit
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // MAINCONTROLLER_H
