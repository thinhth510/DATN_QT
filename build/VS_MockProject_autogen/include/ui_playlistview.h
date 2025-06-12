/********************************************************************************
** Form generated from reading UI file 'playlistview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYLISTVIEW_H
#define UI_PLAYLISTVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaylistView
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *infoWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QLabel *artistLabel;
    QLabel *albumLabel;
    QHBoxLayout *timeLayout;
    QLabel *currentTimeLabel;
    QSlider *positionSlider;
    QLabel *totalTimeLabel;
    QWidget *controlsWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *previousButton;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QSlider *volumeSlider;
    QTreeView *playlistView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlaylistView)
    {
        if (PlaylistView->objectName().isEmpty())
            PlaylistView->setObjectName(QString::fromUtf8("PlaylistView"));
        PlaylistView->resize(1000, 700);
        PlaylistView->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: rgb(52,51,64);\n"
"}\n"
"QLabel {\n"
"    color: rgb(255,255,255);\n"
"}\n"
"QPushButton {\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    min-width: 60px;\n"
"    max-width: 60px;\n"
"    min-height: 60px;\n"
"    max-height: 60px;\n"
"    background-color: rgb(255,255,255);\n"
"    color: rgb(52,51,64);\n"
"    padding: 0px;\n"
"}\n"
"QSlider::groove:horizontal {\n"
"    height: 10px;\n"
"    background: red;\n"
"    border-radius: 5px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background: rgb(255,255,255);\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    margin: -7px -7px;\n"
"    border-radius: 10px;\n"
"}\n"
"QTreeView {\n"
"    background-color: rgb(40,40,50);\n"
"    color: rgb(255,255,255);\n"
"    border: 2px solid rgb(255,255,255);\n"
"    border-radius: 5px;\n"
"}\n"
"QTreeView::item:selected {\n"
"    background-color: rgb(70,70,80);\n"
"    color: rgb(255,255,255);\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: rgb(60,60,70);\n"
""
                        "    color: rgb(255,255,255);\n"
"    border: 1px solid rgb(80,80,90);\n"
"    padding: 5px;\n"
"}"));
        centralwidget = new QWidget(PlaylistView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        infoWidget = new QWidget(centralwidget);
        infoWidget->setObjectName(QString::fromUtf8("infoWidget"));
        verticalLayout_2 = new QVBoxLayout(infoWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        titleLabel = new QLabel(infoWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font.setPointSize(14);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: 2px solid rgb(255,255,255);\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}"));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(titleLabel);

        artistLabel = new QLabel(infoWidget);
        artistLabel->setObjectName(QString::fromUtf8("artistLabel"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font1.setPointSize(12);
        font1.setBold(true);
        artistLabel->setFont(font1);
        artistLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    padding: 5px;\n"
"}"));
        artistLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(artistLabel);

        albumLabel = new QLabel(infoWidget);
        albumLabel->setObjectName(QString::fromUtf8("albumLabel"));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font2.setPointSize(10);
        font2.setBold(true);
        albumLabel->setFont(font2);
        albumLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    padding: 5px;\n"
"}"));
        albumLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(albumLabel);

        timeLayout = new QHBoxLayout();
        timeLayout->setObjectName(QString::fromUtf8("timeLayout"));
        currentTimeLabel = new QLabel(infoWidget);
        currentTimeLabel->setObjectName(QString::fromUtf8("currentTimeLabel"));
        currentTimeLabel->setMinimumSize(QSize(60, 0));
        currentTimeLabel->setFont(font2);

        timeLayout->addWidget(currentTimeLabel);

        positionSlider = new QSlider(infoWidget);
        positionSlider->setObjectName(QString::fromUtf8("positionSlider"));
        positionSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"	height : 10px;\n"
"	width : 800px;\n"
"	background : red;\n"
"	border-radius : 5px;\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"	background : rgb(255,255,255);\n"
"	width : 10px;\n"
"	height : 20px;\n"
"	margin : -7px -7px;\n"
"	border-radius : 10px;\n"
"}"));
        positionSlider->setOrientation(Qt::Orientation::Horizontal);

        timeLayout->addWidget(positionSlider);

        totalTimeLabel = new QLabel(infoWidget);
        totalTimeLabel->setObjectName(QString::fromUtf8("totalTimeLabel"));
        totalTimeLabel->setMinimumSize(QSize(60, 0));
        totalTimeLabel->setFont(font2);

        timeLayout->addWidget(totalTimeLabel);


        verticalLayout_2->addLayout(timeLayout);


        verticalLayout->addWidget(infoWidget);

        controlsWidget = new QWidget(centralwidget);
        controlsWidget->setObjectName(QString::fromUtf8("controlsWidget"));
        horizontalLayout = new QHBoxLayout(controlsWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        previousButton = new QPushButton(controlsWidget);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));
        previousButton->setMinimumSize(QSize(70, 70));
        previousButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0078D7;\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E88E5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #005A9E;\n"
"}"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("media-skip-backward")));
        previousButton->setIcon(icon);
        previousButton->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(previousButton);

        playButton = new QPushButton(controlsWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setMinimumSize(QSize(70, 70));
        playButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0078D7;\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E88E5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #005A9E;\n"
"}"));
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("media-playback-start")));
        playButton->setIcon(icon1);
        playButton->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(playButton);

        stopButton = new QPushButton(controlsWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setMinimumSize(QSize(70, 70));
        stopButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0078D7;\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E88E5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #005A9E;\n"
"}"));
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("media-playback-stop")));
        stopButton->setIcon(icon2);
        stopButton->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(stopButton);

        nextButton = new QPushButton(controlsWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setMinimumSize(QSize(70, 70));
        nextButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0078D7;\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E88E5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #005A9E;\n"
"}"));
        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("media-skip-forward")));
        nextButton->setIcon(icon3);
        nextButton->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(nextButton);

        volumeSlider = new QSlider(controlsWidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setEnabled(true);
        volumeSlider->setMinimumSize(QSize(150, 0));
        volumeSlider->setMaximumSize(QSize(149, 16777215));
        volumeSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"	height : 5px;\n"
"	width : 120px;\n"
"	background : red;\n"
"	border-radius : 2px;\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"	background : rgb(255,255,255);\n"
"	width : 10px;\n"
"	height : 20px;\n"
"	margin : -5px -5px;\n"
"	border-radius : 5px;\n"
"}"));
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(volumeSlider);


        verticalLayout->addWidget(controlsWidget);

        playlistView = new QTreeView(centralwidget);
        playlistView->setObjectName(QString::fromUtf8("playlistView"));
        playlistView->setStyleSheet(QString::fromUtf8("QTreeView {\n"
"    background-color: rgb(40,40,50);\n"
"    color: rgb(255,255,255);\n"
"    border: 2px solid rgb(255,255,255);\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTreeView::item:selected {\n"
"    background-color: rgb(70,70,80);\n"
"    color: rgb(255,255,255);\n"
"}\n"
"\n"
"QTreeView::item:hover {\n"
"    background-color: rgb(60,60,70);\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgb(45,45,55);\n"
"    color: rgb(255,255,255);\n"
"    padding: 5px;\n"
"    border: 1px solid rgb(60,60,70);\n"
"}"));
        playlistView->setAlternatingRowColors(true);
        playlistView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        playlistView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        playlistView->setRootIsDecorated(false);
        playlistView->setUniformRowHeights(true);
        playlistView->header()->setVisible(true);
        playlistView->header()->setMinimumSectionSize(50);
        playlistView->header()->setDefaultSectionSize(150);
        playlistView->header()->setStretchLastSection(true);

        verticalLayout->addWidget(playlistView);

        PlaylistView->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(PlaylistView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlaylistView->setStatusBar(statusbar);

        retranslateUi(PlaylistView);

        QMetaObject::connectSlotsByName(PlaylistView);
    } // setupUi

    void retranslateUi(QMainWindow *PlaylistView)
    {
        PlaylistView->setWindowTitle(QCoreApplication::translate("PlaylistView", "MainWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("PlaylistView", "No file playing", nullptr));
        artistLabel->setText(QString());
        albumLabel->setText(QString());
        currentTimeLabel->setText(QCoreApplication::translate("PlaylistView", "00:00", nullptr));
        totalTimeLabel->setText(QCoreApplication::translate("PlaylistView", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaylistView: public Ui_PlaylistView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYLISTVIEW_H
