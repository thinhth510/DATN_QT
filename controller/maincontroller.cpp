#include "maincontroller.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileModel(new QFileSystemModel(this))
    , m_playlistModel(new QStringListModel(this))
    , m_currentPlaylist(nullptr)
    , m_playlistWindow(nullptr)
    , m_virtualKeyboard(nullptr)
    , m_db(nullptr)
    , m_playlistDao(nullptr)
{
    ui->setupUi(this);
    m_db = new Database("playlist.db");
    m_db->open();
    if (!m_db->initSchema()) {
        qWarning() << "Database schema creation failed!";
    }
    m_playlistDao = new PlaylistDAO(m_db);
    setupUI();
    setupMediaBrowser();
    setupPlaylistManager();
    setupVirtualKeyboard();
    loadPlaylists();

    // Thêm phím tắt F1 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &MainWindow::toggleFullScreen);
    showFullScreen();
}

MainWindow::~MainWindow()
{
    if (m_playlistDao) delete m_playlistDao;
    if (m_db) delete m_db;
    delete ui;
    if (m_playlistWindow) {
        delete m_playlistWindow;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_playlistWindow) {
        m_playlistWindow->close();
    }
    event->accept();
}

void MainWindow::setupUI()
{
    // Set up media file filters
    m_fileModel->setNameFilters(QStringList() << "*.mp3" << "*.mp4" << "*.wav" << "*.avi");
    m_fileModel->setNameFilterDisables(false);
    
    // Connect signals/slots
    connect(ui->newPlaylistButton, &QPushButton::clicked, this, &MainWindow::on_actionNewPlaylist_triggered);
    connect(ui->deletePlaylistButton, &QPushButton::clicked, this, &MainWindow::on_actionDeletePlaylist_triggered);
    
    // Style the buttons
    QString buttonStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #7aa2f7, stop:1 #2ac3de);
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 20px;
            font-weight: bold;
            min-width: 100px;
        }

        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #2ac3de, stop:1 #7aa2f7);
        }

        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #5d7ab8, stop:1 #1e95ad);
        }
    )";
    
    ui->addToPlaylistButton->setStyleSheet(buttonStyle);
    ui->removeFromPlaylistButton->setStyleSheet(buttonStyle);
    ui->playButton->setStyleSheet(buttonStyle);
    ui->newPlaylistButton->setStyleSheet(buttonStyle);
    ui->deletePlaylistButton->setStyleSheet(buttonStyle);

    // Set icon for Play button
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    QSize iconSize(24, 24);
    ui->playButton->setIconSize(iconSize);
}

void MainWindow::setupMediaBrowser()
{
    ui->mediaTreeView->setModel(m_fileModel);
    ui->mediaTreeView->setColumnWidth(0, 250);
    ui->mediaTreeView->hideColumn(1); // Size
    ui->mediaTreeView->hideColumn(2); // Type
    ui->mediaTreeView->hideColumn(3); // Date Modified
}

void MainWindow::setupPlaylistManager()
{
    ui->playlistView->setModel(m_playlistModel);
    ui->playlistView->setDragEnabled(true);
    ui->playlistView->setAcceptDrops(true);
    ui->playlistView->setDropIndicatorShown(true);
    
    // Add double-click handler
    connect(ui->playlistView, &QListView::doubleClicked,
            this, [this](const QModelIndex &index) {
        if (index.isValid() && m_currentPlaylist) {
            PlaylistWindow *playlistWindow = new PlaylistWindow(m_currentPlaylist, m_db);
            playlistWindow->setAttribute(Qt::WA_DeleteOnClose);
            playlistWindow->show();
        }
    });
}

void MainWindow::setupVirtualKeyboard()
{
    m_virtualKeyboard = new VirtualKeyboard(this);
    m_virtualKeyboard->hide(); // Ẩn ban đầu
    
    // Kết nối sự kiện mousePress của searchLineEdit
    ui->searchLineEdit->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->searchLineEdit && event->type() == QEvent::MouseButtonPress) {
        m_virtualKeyboard->setTargetLineEdit(ui->searchLineEdit);
        
        // Với màn hình 1024x600, căn giữa bàn phím
        int x = (1024 - m_virtualKeyboard->width()) / 2;  // Căn giữa theo chiều ngang
        int y = 600 - m_virtualKeyboard->height();   // Đặt ở dưới cùng, cách lề 10px
        
        m_virtualKeyboard->move(x, y);
        m_virtualKeyboard->show();
        m_virtualKeyboard->raise();
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_actionBrowseFolder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Media Folder"),
                                                  QDir::homePath(),
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    
    if (!dir.isEmpty()) {
        m_currentMediaPath = dir;
        m_fileModel->setRootPath(dir);
        ui->mediaTreeView->setRootIndex(m_fileModel->index(dir));
    }
}

void MainWindow::on_mediaTreeView_doubleClicked(const QModelIndex &index)
{
    QString filePath = m_fileModel->filePath(index);
    if (m_fileModel->isDir(index)) return;
    
    if (filePath.endsWith(".mp3", Qt::CaseInsensitive)) {
        AudioWindow *audioWindow = new AudioWindow(filePath);
        audioWindow->setAttribute(Qt::WA_DeleteOnClose);
        audioWindow->show();
    } else if (filePath.endsWith(".mp4", Qt::CaseInsensitive)) {
        VideoWindow *videoWindow = new VideoWindow(filePath);
        videoWindow->setAttribute(Qt::WA_DeleteOnClose);
        videoWindow->show();
    }
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        ui->mediaTreeView->setRootIndex(m_fileModel->index(m_currentMediaPath));
    } else {
        filterMediaFiles(text);
    }
}

void MainWindow::filterMediaFiles(const QString &filter)
{
    QStringList filters;
    filters << QString("*%1*").arg(filter);
    m_fileModel->setNameFilters(filters);
}

void MainWindow::on_actionScan_USB_triggered()
{
    USBScanner *scanner = new USBScanner(this);
    
    // Connect signals
    connect(scanner, &USBScanner::scanCompleted, this, [this](const QStringList &mediaFiles) {
        if (mediaFiles.isEmpty()) {
            QMessageBox::information(this, tr("Scan USB"),
                                   tr("No media files found in USB drives."));
            return;
        }

        // Create a temporary directory to show the files via symbolic links
        QString tempPath = QDir::tempPath() + "/usb_media";
        QDir tempDir(tempPath);
        if (!tempDir.exists()) {
            QDir().mkpath(tempPath);
        }
        
        // Clear previous contents of the temp directory to avoid stale links/files
        for (const QFileInfo &entry : tempDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
            QFile::remove(entry.absoluteFilePath());
        }

        // Set the root path to the temporary directory
        m_currentMediaPath = tempPath;
        m_fileModel->setRootPath(tempPath);
        ui->mediaTreeView->setRootIndex(m_fileModel->index(tempPath));

        // Create symbolic links to the found media files in the temporary directory
        for (const QString &filePath : mediaFiles) {
            QFileInfo fileInfo(filePath);
            QString linkPath = tempPath + "/" + fileInfo.fileName();
            if (!QFile::exists(linkPath)) { // Avoid creating duplicate links
                if (!QFile::link(filePath, linkPath)) {
                    qDebug() << "Failed to create symbolic link for:" << filePath << "to" << linkPath;
                }
            }
        }
    });

    connect(scanner, &USBScanner::scanError, this, [this](const QString &error) {
        QMessageBox::warning(this, tr("Scan USB"), error);
    });

    // Start scanning
    scanner->scanForMediaFiles();
}

void MainWindow::on_actionNewPlaylist_triggered()
{
    // Tạo tên playlist mặc định
    QString defaultName = "New Playlist";
    int counter = 1;
    
    // Tìm số thứ tự tiếp theo cho "New Playlist"
    while (true) {
        QString testName = QString("%1 %2").arg(defaultName).arg(counter);
        bool nameExists = false;
        for (const Playlist &pl : m_playlists) {
            if (pl.name().toLower() == testName.toLower()) {
                nameExists = true;
                break;
            }
        }
        if (!nameExists) {
            defaultName = testName;
            break;
        }
        counter++;
    }
    
    // Làm cho comboBox có thể edit được
    ui->playlistComboBox->setEditable(true);
    ui->playlistComboBox->setCurrentText(defaultName);
    ui->playlistComboBox->setFocus();
    
    // Lưu trạng thái cũ để khôi phục nếu cần
    int oldIndex = ui->playlistComboBox->currentIndex();
    
    // Kết nối signal để xử lý khi người dùng nhập xong
    connect(ui->playlistComboBox->lineEdit(), &QLineEdit::editingFinished, this, [this, oldIndex]() {
        QString name = ui->playlistComboBox->currentText().trimmed();
        
        // Khôi phục trạng thái không edit được ngay lập tức
        ui->playlistComboBox->setEditable(false);
        disconnect(ui->playlistComboBox->lineEdit(), &QLineEdit::editingFinished, this, nullptr);
        
        if (name.isEmpty()) {
            // Nếu tên rỗng, khôi phục index cũ
            if (oldIndex >= 0 && oldIndex < ui->playlistComboBox->count()) {
                ui->playlistComboBox->setCurrentIndex(oldIndex);
            }
            return;
        }
        
        // Kiểm tra xem tên playlist đã tồn tại chưa
        bool nameExists = false;
        for (const Playlist &pl : m_playlists) {
            if (pl.name().toLower() == name.toLower()) {
                nameExists = true;
                break;
            }
        }
        
        if (nameExists) {
            // Hiển thị thông báo lỗi và khôi phục index cũ
            QMessageBox::warning(this, tr("Error"), 
                tr("The Playlist name already exists, please enter a different name.").arg(name));
            if (oldIndex >= 0 && oldIndex < ui->playlistComboBox->count()) {
                ui->playlistComboBox->setCurrentIndex(oldIndex);
            }
            return;
        }
        
        // Tạo playlist mới
        Playlist playlist(name);
        int playlistId = m_playlistDao->addPlaylist(playlist);
        loadPlaylists();
        
        // Tìm index của playlist vừa tạo và chọn nó
        int newIndex = -1;
        for (int i = 0; i < m_playlists.size(); ++i) {
            if (m_playlists[i].id() == playlistId) {
                newIndex = i;
                break;
            }
        }
        if (newIndex != -1) {
            ui->playlistComboBox->setCurrentIndex(newIndex);
        }
    });
    
    // Kết nối signal để xử lý khi nhấn Enter
    connect(ui->playlistComboBox->lineEdit(), &QLineEdit::returnPressed, this, [this]() {
        ui->playlistComboBox->lineEdit()->clearFocus();
    });
}

void MainWindow::on_actionDeletePlaylist_triggered()
{
    int index = ui->playlistComboBox->currentIndex();
    if (index >= 0 && index < m_playlists.size()) {
        int playlistId = m_playlists[index].id();
        m_playlistDao->deletePlaylist(playlistId);
        m_playlists.removeAt(index);
        ui->playlistComboBox->removeItem(index);
        m_playlistModel->setStringList(QStringList());
        loadPlaylists();
    }
}

void MainWindow::on_playlistComboBox_currentIndexChanged(int index)
{
    if (index >= 0 && index < m_playlists.size()) {
        m_currentPlaylist = &m_playlists[index];
        // Lấy metadata từ database để hiển thị
        MediaFileDAO mediaFileDao(m_db);
        QList<MediaFile> files = mediaFileDao.getMediaFiles(m_currentPlaylist->id());
        QStringList fileNames;
        for (const MediaFile &f : files) {
            fileNames << f.title();
        }
        m_playlistModel->setStringList(fileNames);
    }
}

void MainWindow::on_addToPlaylistButton_clicked()
{
    QModelIndex index = ui->mediaTreeView->currentIndex();
    if (!index.isValid() || m_currentPlaylist == nullptr) return;
    
    QString filePath = m_fileModel->filePath(index);
    if (!m_fileModel->isDir(index)) {
        // Tạo MediaFile tạm để lấy metadata
        MediaFile file(filePath);
        if (file.isValid() && m_currentPlaylist->id() != -1) {
            // Lưu metadata vào database qua MediaFileDAO
            MediaFileDAO mediaFileDao(m_db);
            mediaFileDao.addMediaFile(m_currentPlaylist->id(), file);
        }
        // Update lại model hiển thị bằng cách lấy metadata từ database
        MediaFileDAO mediaFileDao(m_db);
        QList<MediaFile> files = mediaFileDao.getMediaFiles(m_currentPlaylist->id());
        QStringList fileNames;
        for (const MediaFile &f : files) {
            fileNames << f.title();
        }
        m_playlistModel->setStringList(fileNames);
    }
}

void MainWindow::on_removeFromPlaylistButton_clicked()
{
    QModelIndex index = ui->playlistView->currentIndex();
    if (!index.isValid() || m_currentPlaylist == nullptr) return;
    int row = index.row();
    
    // Lấy danh sách file từ database
    MediaFileDAO mediaFileDao(m_db);
    QList<MediaFile> files = mediaFileDao.getMediaFiles(m_currentPlaylist->id());
    
    if (row >= 0 && row < files.size()) {
        QString filePath = files[row].filePath();
        // Xóa trong database
        if (m_currentPlaylist->id() != -1) {
            // Tìm media file id trong database (giả sử chỉ có 1 file trùng path trong playlist)
            QSqlQuery query(m_db->connection());
            query.prepare("DELETE FROM media_files WHERE playlist_id=? AND path=?");
            query.addBindValue(m_currentPlaylist->id());
            query.addBindValue(filePath);
            query.exec();
        }
        
        // Update lại model hiển thị
        files = mediaFileDao.getMediaFiles(m_currentPlaylist->id());
        QStringList fileNames;
        for (const MediaFile &file : files) {
            fileNames << file.title();
        }
        m_playlistModel->setStringList(fileNames);
    }
}

void MainWindow::loadPlaylists()
{
    m_playlists = m_playlistDao->getAllPlaylists();
    ui->playlistComboBox->clear();
    for (const Playlist &pl : m_playlists) {
        ui->playlistComboBox->addItem(pl.name());
    }
    if (!m_playlists.isEmpty()) {
        m_currentPlaylist = &m_playlists[0];
        ui->playlistComboBox->setCurrentIndex(0);
    } else {
        m_currentPlaylist = nullptr;
        m_playlistModel->setStringList(QStringList());
    }
}

void MainWindow::on_actionOpen_Audio_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open Audio File"), "",
        tr("Audio Files (*.mp3 *.wav *.ogg *.flac);;All Files (*)"));

    if (!filePath.isEmpty()) {
        AudioWindow *audioWindow = new AudioWindow(filePath, this);
        audioWindow->show();
    }
}

void MainWindow::on_actionOpen_Video_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open Video File"), "",
        tr("Video Files (*.mp4 *.avi *.mkv *.mov);;All Files (*)"));

    if (!filePath.isEmpty()) {
        VideoWindow *videoWindow = new VideoWindow(filePath, this);
        videoWindow->show();
    }
}

void MainWindow::on_playButton_clicked()
{
    if (m_currentPlaylist) {
        if (m_playlistWindow) {
            m_playlistWindow->close();
        }
        m_playlistWindow = new PlaylistWindow(m_currentPlaylist, m_db, this);
        m_playlistWindow->setAttribute(Qt::WA_DeleteOnClose);
        m_playlistWindow->show();
        QMetaObject::invokeMethod(m_playlistWindow, "on_playButton_clicked", Qt::QueuedConnection);
    }
}

void MainWindow::toggleFullScreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void MainWindow::on_actionToggle_Fullscreen_triggered()
{
    MainWindow::toggleFullScreen();
}


void MainWindow::on_actionExit_App_triggered()
{
    this -> close();
}

