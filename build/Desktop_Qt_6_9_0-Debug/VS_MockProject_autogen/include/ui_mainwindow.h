/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Audio;
    QAction *actionOpen_Video;
    QAction *actionBrowseFolder;
    QAction *actionNewPlaylist;
    QAction *actionDeletePlaylist;
    QAction *actionSavePlaylist;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *mediaBrowserWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *searchLineEdit;
    QTreeView *mediaTreeView;
    QWidget *playlistWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *playlistComboBox;
    QPushButton *newPlaylistButton;
    QPushButton *deletePlaylistButton;
    QListView *playlistView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addToPlaylistButton;
    QPushButton *removeFromPlaylistButton;
    QPushButton *playButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuPlaylist;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color : rgb(52,51,64);"));
        actionOpen_Audio = new QAction(MainWindow);
        actionOpen_Audio->setObjectName("actionOpen_Audio");
        actionOpen_Video = new QAction(MainWindow);
        actionOpen_Video->setObjectName("actionOpen_Video");
        actionBrowseFolder = new QAction(MainWindow);
        actionBrowseFolder->setObjectName("actionBrowseFolder");
        actionNewPlaylist = new QAction(MainWindow);
        actionNewPlaylist->setObjectName("actionNewPlaylist");
        actionDeletePlaylist = new QAction(MainWindow);
        actionDeletePlaylist->setObjectName("actionDeletePlaylist");
        actionSavePlaylist = new QAction(MainWindow);
        actionSavePlaylist->setObjectName("actionSavePlaylist");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        mediaBrowserWidget = new QWidget(splitter);
        mediaBrowserWidget->setObjectName("mediaBrowserWidget");
        verticalLayout = new QVBoxLayout(mediaBrowserWidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(mediaBrowserWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        searchLineEdit = new QLineEdit(mediaBrowserWidget);
        searchLineEdit->setObjectName("searchLineEdit");

        verticalLayout->addWidget(searchLineEdit);

        mediaTreeView = new QTreeView(mediaBrowserWidget);
        mediaTreeView->setObjectName("mediaTreeView");

        verticalLayout->addWidget(mediaTreeView);

        splitter->addWidget(mediaBrowserWidget);
        playlistWidget = new QWidget(splitter);
        playlistWidget->setObjectName("playlistWidget");
        verticalLayout_2 = new QVBoxLayout(playlistWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(playlistWidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        playlistComboBox = new QComboBox(playlistWidget);
        playlistComboBox->setObjectName("playlistComboBox");

        horizontalLayout_2->addWidget(playlistComboBox);

        newPlaylistButton = new QPushButton(playlistWidget);
        newPlaylistButton->setObjectName("newPlaylistButton");

        horizontalLayout_2->addWidget(newPlaylistButton);

        deletePlaylistButton = new QPushButton(playlistWidget);
        deletePlaylistButton->setObjectName("deletePlaylistButton");

        horizontalLayout_2->addWidget(deletePlaylistButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        playlistView = new QListView(playlistWidget);
        playlistView->setObjectName("playlistView");

        verticalLayout_2->addWidget(playlistView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addToPlaylistButton = new QPushButton(playlistWidget);
        addToPlaylistButton->setObjectName("addToPlaylistButton");

        horizontalLayout_3->addWidget(addToPlaylistButton);

        removeFromPlaylistButton = new QPushButton(playlistWidget);
        removeFromPlaylistButton->setObjectName("removeFromPlaylistButton");

        horizontalLayout_3->addWidget(removeFromPlaylistButton);

        playButton = new QPushButton(playlistWidget);
        playButton->setObjectName("playButton");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("media-playback-start")));
        playButton->setIcon(icon);

        horizontalLayout_3->addWidget(playButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        splitter->addWidget(playlistWidget);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuPlaylist = new QMenu(menubar);
        menuPlaylist->setObjectName("menuPlaylist");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuPlaylist->menuAction());
        menuFile->addAction(actionBrowseFolder);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_Audio);
        menuFile->addAction(actionOpen_Video);
        menuPlaylist->addAction(actionNewPlaylist);
        menuPlaylist->addAction(actionDeletePlaylist);
        menuPlaylist->addSeparator();
        menuPlaylist->addAction(actionSavePlaylist);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Media Player", nullptr));
        actionOpen_Audio->setText(QCoreApplication::translate("MainWindow", "Open Audio", nullptr));
        actionOpen_Video->setText(QCoreApplication::translate("MainWindow", "Open Video", nullptr));
        actionBrowseFolder->setText(QCoreApplication::translate("MainWindow", "Browse Folder", nullptr));
        actionNewPlaylist->setText(QCoreApplication::translate("MainWindow", "New Playlist", nullptr));
        actionDeletePlaylist->setText(QCoreApplication::translate("MainWindow", "Delete Playlist", nullptr));
        actionSavePlaylist->setText(QCoreApplication::translate("MainWindow", "Save Playlist", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Media Browser", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search media files...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Playlists", nullptr));
        newPlaylistButton->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        deletePlaylistButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        addToPlaylistButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        removeFromPlaylistButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuPlaylist->setTitle(QCoreApplication::translate("MainWindow", "Playlist", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
