/********************************************************************************
** Form generated from reading UI file 'videoview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOVIEW_H
#define UI_VIDEOVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoView
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Video;
    QHBoxLayout *timeLayout;
    QLabel *label_Current_Time;
    QSlider *horizontalSlider_Duration;
    QLabel *label_Total_Time;
    QHBoxLayout *controlsLayout;
    QPushButton *pushButton_Seek_Backward;
    QPushButton *pushButton_Play_Pause;
    QPushButton *pushButton_Stop;
    QPushButton *pushButton_Seek_Forward;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Volume;
    QSlider *horizontalSlider_Volume;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VideoView)
    {
        if (VideoView->objectName().isEmpty())
            VideoView->setObjectName(QString::fromUtf8("VideoView"));
        VideoView->resize(1024, 600);
        VideoView->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: rgb(52,51,64);\n"
"}\n"
"QLabel {\n"
"    color: rgb(255,255,255);\n"
"}"));
        centralwidget = new QWidget(VideoView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        groupBox_Video = new QGroupBox(centralwidget);
        groupBox_Video->setObjectName(QString::fromUtf8("groupBox_Video"));
        groupBox_Video->setMinimumSize(QSize(0, 400));
        groupBox_Video->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid rgb(255,255,255);\n"
"    border-radius: 5px;\n"
"}"));

        verticalLayout->addWidget(groupBox_Video);

        timeLayout = new QHBoxLayout();
        timeLayout->setObjectName(QString::fromUtf8("timeLayout"));
        label_Current_Time = new QLabel(centralwidget);
        label_Current_Time->setObjectName(QString::fromUtf8("label_Current_Time"));
        label_Current_Time->setMinimumSize(QSize(60, 20));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_Current_Time->setFont(font);

        timeLayout->addWidget(label_Current_Time);

        horizontalSlider_Duration = new QSlider(centralwidget);
        horizontalSlider_Duration->setObjectName(QString::fromUtf8("horizontalSlider_Duration"));
        horizontalSlider_Duration->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    height: 10px;\n"
"    background: red;\n"
"    border-radius: 5px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background: rgb(255,255,255);\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    margin: -5px -5px;\n"
"    border-radius: 10px;\n"
"}"));
        horizontalSlider_Duration->setOrientation(Qt::Orientation::Horizontal);

        timeLayout->addWidget(horizontalSlider_Duration);

        label_Total_Time = new QLabel(centralwidget);
        label_Total_Time->setObjectName(QString::fromUtf8("label_Total_Time"));
        label_Total_Time->setMinimumSize(QSize(60, 20));
        label_Total_Time->setFont(font);

        timeLayout->addWidget(label_Total_Time);


        verticalLayout->addLayout(timeLayout);

        controlsLayout = new QHBoxLayout();
        controlsLayout->setObjectName(QString::fromUtf8("controlsLayout"));
        pushButton_Seek_Backward = new QPushButton(centralwidget);
        pushButton_Seek_Backward->setObjectName(QString::fromUtf8("pushButton_Seek_Backward"));
        pushButton_Seek_Backward->setMinimumSize(QSize(50, 50));
        pushButton_Seek_Backward->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 25px;\n"
"    background-color: rgb(255,255,255);\n"
"    color: rgb(52,51,64);\n"
"    padding: 0px;\n"
"}"));
        pushButton_Seek_Backward->setIconSize(QSize(32, 32));

        controlsLayout->addWidget(pushButton_Seek_Backward);

        pushButton_Play_Pause = new QPushButton(centralwidget);
        pushButton_Play_Pause->setObjectName(QString::fromUtf8("pushButton_Play_Pause"));
        pushButton_Play_Pause->setMinimumSize(QSize(50, 50));
        pushButton_Play_Pause->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 25px;\n"
"    background-color: rgb(255,255,255);\n"
"    color: rgb(52,51,64);\n"
"    padding: 0px;\n"
"}"));
        pushButton_Play_Pause->setIconSize(QSize(32, 32));

        controlsLayout->addWidget(pushButton_Play_Pause);

        pushButton_Stop = new QPushButton(centralwidget);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));
        pushButton_Stop->setMinimumSize(QSize(50, 50));
        pushButton_Stop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 25px;\n"
"    background-color: rgb(255,255,255);\n"
"    color: rgb(52,51,64);\n"
"    padding: 0px;\n"
"}"));
        pushButton_Stop->setIconSize(QSize(32, 32));

        controlsLayout->addWidget(pushButton_Stop);

        pushButton_Seek_Forward = new QPushButton(centralwidget);
        pushButton_Seek_Forward->setObjectName(QString::fromUtf8("pushButton_Seek_Forward"));
        pushButton_Seek_Forward->setMinimumSize(QSize(50, 50));
        pushButton_Seek_Forward->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 25px;\n"
"    background-color: rgb(255,255,255);\n"
"    color: rgb(52,51,64);\n"
"    padding: 0px;\n"
"}"));
        pushButton_Seek_Forward->setIconSize(QSize(32, 32));

        controlsLayout->addWidget(pushButton_Seek_Forward);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controlsLayout->addItem(horizontalSpacer);

        pushButton_Volume = new QPushButton(centralwidget);
        pushButton_Volume->setObjectName(QString::fromUtf8("pushButton_Volume"));
        pushButton_Volume->setMinimumSize(QSize(50, 50));
        pushButton_Volume->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 25px;\n"
"    background-color: rgb(255,255,255);\n"
"    color: rgb(52,51,64);\n"
"    padding: 0px;\n"
"}"));
        pushButton_Volume->setIconSize(QSize(32, 32));

        controlsLayout->addWidget(pushButton_Volume);

        horizontalSlider_Volume = new QSlider(centralwidget);
        horizontalSlider_Volume->setObjectName(QString::fromUtf8("horizontalSlider_Volume"));
        horizontalSlider_Volume->setMinimumSize(QSize(150, 0));
        horizontalSlider_Volume->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    height: 5px;\n"
"    background: red;\n"
"    border-radius: 2px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background: rgb(255,255,255);\n"
"    width: 10px;\n"
"    height: 20px;\n"
"    margin: -5px -5px;\n"
"    border-radius: 5px;\n"
"}"));
        horizontalSlider_Volume->setOrientation(Qt::Orientation::Horizontal);

        controlsLayout->addWidget(horizontalSlider_Volume);


        verticalLayout->addLayout(controlsLayout);

        VideoView->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(VideoView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        VideoView->setStatusBar(statusbar);

        retranslateUi(VideoView);

        QMetaObject::connectSlotsByName(VideoView);
    } // setupUi

    void retranslateUi(QMainWindow *VideoView)
    {
        VideoView->setWindowTitle(QCoreApplication::translate("VideoView", "Video Player", nullptr));
        groupBox_Video->setTitle(QString());
        label_Current_Time->setText(QCoreApplication::translate("VideoView", "00:00:00", nullptr));
        label_Total_Time->setText(QCoreApplication::translate("VideoView", "00:00:00", nullptr));
        pushButton_Seek_Backward->setText(QString());
        pushButton_Play_Pause->setText(QString());
        pushButton_Stop->setText(QString());
        pushButton_Seek_Forward->setText(QString());
        pushButton_Volume->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoView: public Ui_VideoView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOVIEW_H
