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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoView
{
public:
    QGroupBox *groupBox_Video;
    QPushButton *pushButton_Seek_Backward;
    QPushButton *pushButton_Play_Pause;
    QPushButton *pushButton_Stop;
    QPushButton *pushButton_Seek_Forward;
    QPushButton *pushButton_Volume;
    QSlider *horizontalSlider_Volume;
    QSlider *horizontalSlider_Duration;
    QLabel *label_Current_Time;
    QLabel *label_Total_Time;
    QLabel *label_File_Name;

    void setupUi(QWidget *VideoView)
    {
        if (VideoView->objectName().isEmpty())
            VideoView->setObjectName(QString::fromUtf8("VideoView"));
        VideoView->resize(810, 650);
        groupBox_Video = new QGroupBox(VideoView);
        groupBox_Video->setObjectName(QString::fromUtf8("groupBox_Video"));
        groupBox_Video->setGeometry(QRect(0, 0, 810, 460));
        groupBox_Video->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"	border : 1px solid black;\n"
"}"));
        pushButton_Seek_Backward = new QPushButton(VideoView);
        pushButton_Seek_Backward->setObjectName(QString::fromUtf8("pushButton_Seek_Backward"));
        pushButton_Seek_Backward->setGeometry(QRect(30, 570, 60, 60));
        pushButton_Seek_Backward->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 15px;\n"
"	min-width : 60px;\n"
"	max-width : 60px;\n"
"	min-height : 60px;\n"
"	max-height: 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	padding : 0px;\n"
"}"));
        pushButton_Play_Pause = new QPushButton(VideoView);
        pushButton_Play_Pause->setObjectName(QString::fromUtf8("pushButton_Play_Pause"));
        pushButton_Play_Pause->setGeometry(QRect(110, 570, 60, 60));
        pushButton_Play_Pause->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 15px;\n"
"	min-width : 60px;\n"
"	max-width : 60px;\n"
"	min-height : 60px;\n"
"	max-height: 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	padding : 0px;\n"
"}"));
        pushButton_Stop = new QPushButton(VideoView);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));
        pushButton_Stop->setGeometry(QRect(190, 570, 60, 60));
        pushButton_Stop->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 15px;\n"
"	min-width : 60px;\n"
"	max-width : 60px;\n"
"	min-height : 60px;\n"
"	max-height: 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	padding : 0px;\n"
"}"));
        pushButton_Seek_Forward = new QPushButton(VideoView);
        pushButton_Seek_Forward->setObjectName(QString::fromUtf8("pushButton_Seek_Forward"));
        pushButton_Seek_Forward->setGeometry(QRect(270, 570, 60, 60));
        pushButton_Seek_Forward->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 15px;\n"
"	min-width : 60px;\n"
"	max-width : 60px;\n"
"	min-height : 60px;\n"
"	max-height: 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	padding : 0px;\n"
"}"));
        pushButton_Volume = new QPushButton(VideoView);
        pushButton_Volume->setObjectName(QString::fromUtf8("pushButton_Volume"));
        pushButton_Volume->setGeometry(QRect(550, 570, 60, 60));
        pushButton_Volume->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 15px;\n"
"	min-width : 60px;\n"
"	max-width : 60px;\n"
"	min-height : 60px;\n"
"	max-height: 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	padding : 0px;\n"
"}"));
        horizontalSlider_Volume = new QSlider(VideoView);
        horizontalSlider_Volume->setObjectName(QString::fromUtf8("horizontalSlider_Volume"));
        horizontalSlider_Volume->setGeometry(QRect(629, 594, 160, 16));
        horizontalSlider_Volume->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"	height : 5px;\n"
"	width : 140px;\n"
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
        horizontalSlider_Volume->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_Duration = new QSlider(VideoView);
        horizontalSlider_Duration->setObjectName(QString::fromUtf8("horizontalSlider_Duration"));
        horizontalSlider_Duration->setGeometry(QRect(120, 540, 601, 16));
        horizontalSlider_Duration->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"	height : 10px;\n"
"	width : 550px;\n"
"	background : red;\n"
"	border-radius : 5px;\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"	background : rgb(255,255,255);\n"
"	width : 20px;\n"
"	height : 40px;\n"
"	margin : -5px -5px;\n"
"	border-radius : 10px;\n"
"}"));
        horizontalSlider_Duration->setOrientation(Qt::Orientation::Horizontal);
        label_Current_Time = new QLabel(VideoView);
        label_Current_Time->setObjectName(QString::fromUtf8("label_Current_Time"));
        label_Current_Time->setGeometry(QRect(30, 540, 66, 18));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_Current_Time->setFont(font);
        label_Total_Time = new QLabel(VideoView);
        label_Total_Time->setObjectName(QString::fromUtf8("label_Total_Time"));
        label_Total_Time->setGeometry(QRect(730, 540, 66, 18));
        label_Total_Time->setFont(font);
        label_File_Name = new QLabel(VideoView);
        label_File_Name->setObjectName(QString::fromUtf8("label_File_Name"));
        label_File_Name->setGeometry(QRect(0, 480, 811, 41));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_File_Name->setFont(font1);
        label_File_Name->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color : rgb(255,255,255);\n"
"	border : 2px solid rgb(255,255,255);\n"
"}"));
        label_File_Name->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(VideoView);

        QMetaObject::connectSlotsByName(VideoView);
    } // setupUi

    void retranslateUi(QWidget *VideoView)
    {
        VideoView->setWindowTitle(QCoreApplication::translate("VideoView", "Form", nullptr));
        groupBox_Video->setTitle(QString());
        pushButton_Seek_Backward->setText(QString());
        pushButton_Play_Pause->setText(QString());
        pushButton_Stop->setText(QString());
        pushButton_Seek_Forward->setText(QString());
        pushButton_Volume->setText(QString());
        label_Current_Time->setText(QCoreApplication::translate("VideoView", "00:00:00", nullptr));
        label_Total_Time->setText(QCoreApplication::translate("VideoView", "00:00:00", nullptr));
        label_File_Name->setText(QCoreApplication::translate("VideoView", "File Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoView: public Ui_VideoView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOVIEW_H
