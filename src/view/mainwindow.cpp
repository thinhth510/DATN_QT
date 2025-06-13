#include "view/mainwindow.h"
#include "ui_mainwindow.h"
#include "view/playlistview.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileModel(new QFileSystemModel(this))
    , m_playlistModel(new QStringListModel(this))
    , m_currentPlaylist(nullptr)
    , m_playlistView(nullptr)
{
    ui->setupUi(this);
    setupUI();
    setupMediaBrowser();
    setupPlaylistManager();
    loadPlaylists();

    // Thêm phím tắt F1 để chuyển đổi full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F1), this);
    connect(fullScreenShortcut, &QShortcut::activated, this, &MainWindow::toggleFullScreen);
    showFullScreen();
}

MainWindow::~MainWindow()
{
    savePlaylists();
    delete ui;
    if (m_playlistView) {
        delete m_playlistView;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_playlistView) {
        m_playlistView->close();
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
            PlaylistView *playlistWindow = new PlaylistView(m_currentPlaylist);
            playlistWindow->setAttribute(Qt::WA_DeleteOnClose);
            playlistWindow->show();
        }
    });
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
        AudioView *audioWindow = new AudioView(filePath);
        audioWindow->setAttribute(Qt::WA_DeleteOnClose);
        audioWindow->show();
    } else if (filePath.endsWith(".mp4", Qt::CaseInsensitive)) {
        VideoView *videoWindow = new VideoView(filePath);
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

void MainWindow::on_actionNewPlaylist_triggered()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("New Playlist"),
                                       tr("Playlist name:"), QLineEdit::Normal,
                                       "New Playlist", &ok);
    if (ok && !name.isEmpty()) {
        Playlist playlist(name);
        m_playlists.append(playlist);
        ui->playlistComboBox->addItem(name);
        ui->playlistComboBox->setCurrentIndex(ui->playlistComboBox->count() - 1);
    }
}

void MainWindow::on_actionDeletePlaylist_triggered()
{
    int index = ui->playlistComboBox->currentIndex();
    if (index >= 0) {
        m_playlists.removeAt(index);
        ui->playlistComboBox->removeItem(index);
        m_playlistModel->setStringList(QStringList());
    }
}

void MainWindow::on_actionSavePlaylist_triggered()
{
    savePlaylists();
}

void MainWindow::on_playlistComboBox_currentIndexChanged(int index)
{
    if (index >= 0 && index < m_playlists.size()) {
        m_currentPlaylist = &m_playlists[index];
        QStringList fileNames;
        for (const MediaFile &file : m_currentPlaylist->mediaFiles()) {
            fileNames << file.title();
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
        m_currentPlaylist->addMediaFile(filePath);
        QStringList fileNames;
        for (const MediaFile &file : m_currentPlaylist->mediaFiles()) {
            fileNames << file.title();
        }
        m_playlistModel->setStringList(fileNames);
    }
}

void MainWindow::on_removeFromPlaylistButton_clicked()
{
    QModelIndex index = ui->playlistView->currentIndex();
    if (!index.isValid() || m_currentPlaylist == nullptr) return;
    
    int row = index.row();
    if (row >= 0 && row < m_currentPlaylist->mediaFiles().size()) {
        QString filePath = m_currentPlaylist->mediaFiles()[row].filePath();
        m_currentPlaylist->removeMediaFile(filePath);
        QStringList fileNames;
        for (const MediaFile &file : m_currentPlaylist->mediaFiles()) {
            fileNames << file.title();
        }
        m_playlistModel->setStringList(fileNames);
    }
}

void MainWindow::loadPlaylists()
{
    // TODO: Implement loading playlists from file/database
}

void MainWindow::savePlaylists()
{
    // TODO: Implement saving playlists to file/database
}

void MainWindow::on_actionOpen_Audio_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open Audio File"), "",
        tr("Audio Files (*.mp3 *.wav *.ogg *.flac);;All Files (*)"));

    if (!filePath.isEmpty()) {
        AudioView *audioView = new AudioView(filePath, this);
        audioView->show();
    }
}

void MainWindow::on_actionOpen_Video_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open Video File"), "",
        tr("Video Files (*.mp4 *.avi *.mkv *.mov);;All Files (*)"));

    if (!filePath.isEmpty()) {
        VideoView *videoView = new VideoView(filePath, this);
        videoView->show();
    }
}

void MainWindow::on_playButton_clicked()
{
    if (m_currentPlaylist) {
        // Tạo một PlaylistView mới cho playlist hiện tại
        if (m_playlistView) {
            m_playlistView->close();
            delete m_playlistView;
        }
        m_playlistView = new PlaylistView(m_currentPlaylist, this);
        m_playlistView->setAttribute(Qt::WA_DeleteOnClose);
        m_playlistView->show();
        
        // Tự động bắt đầu phát
        QMetaObject::invokeMethod(m_playlistView, "on_playButton_clicked", Qt::QueuedConnection);
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




