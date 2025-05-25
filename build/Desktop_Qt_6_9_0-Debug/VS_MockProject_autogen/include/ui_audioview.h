/********************************************************************************
** Form generated from reading UI file 'audioview.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOVIEW_H
#define UI_AUDIOVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioView
{
public:
    QAction *actionOpen_Audio;
    QAction *actionOpen_Video;
    QWidget *centralwidget;
    QLabel *label_File_Name;
    QSlider *horizontalSlider_Duration;
    QSlider *horizontalSlider_Volume;
    QPushButton *pushButton_Volume;
    QLabel *label_Current_Time;
    QLabel *label_Total_Time;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Seek_Backward;
    QPushButton *pushButton_Play_Pause;
    QPushButton *pushButton_Stop;
    QPushButton *pushButton_Seek_Forward;
    QMenuBar *menubar;

    void setupUi(QMainWindow *AudioView)
    {
        if (AudioView->objectName().isEmpty())
            AudioView->setObjectName("AudioView");
        AudioView->resize(800, 550);
        AudioView->setStyleSheet(QString::fromUtf8("background-color : rgb(52,51,64);\n"
"\n"
""));
        actionOpen_Audio = new QAction(AudioView);
        actionOpen_Audio->setObjectName("actionOpen_Audio");
        QFont font;
        font.setPointSize(14);
        actionOpen_Audio->setFont(font);
        actionOpen_Video = new QAction(AudioView);
        actionOpen_Video->setObjectName("actionOpen_Video");
        actionOpen_Video->setFont(font);
        centralwidget = new QWidget(AudioView);
        centralwidget->setObjectName("centralwidget");
        label_File_Name = new QLabel(centralwidget);
        label_File_Name->setObjectName("label_File_Name");
        label_File_Name->setGeometry(QRect(0, 100, 801, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        label_File_Name->setFont(font1);
        label_File_Name->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color : rgb(255,255,255);\n"
"	border : 2px solid rgb(255,255,255);\n"
"}"));
        label_File_Name->setFrameShape(QFrame::Shape::Panel);
        label_File_Name->setLineWidth(2);
        label_File_Name->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalSlider_Duration = new QSlider(centralwidget);
        horizontalSlider_Duration->setObjectName("horizontalSlider_Duration");
        horizontalSlider_Duration->setGeometry(QRect(0, 170, 801, 31));
        horizontalSlider_Duration->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"	height : 10px;\n"
"	width : 600px;\n"
"	background : red;\n"
"	border-radius : 5px;\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"	background : rgb(255,255,255);\n"
"	width : 20px;\n"
"	height : 20px;\n"
"	margin : -7px -7px;\n"
"	border-radius : 10px;\n"
"}"));
        horizontalSlider_Duration->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_Volume = new QSlider(centralwidget);
        horizontalSlider_Volume->setObjectName("horizontalSlider_Volume");
        horizontalSlider_Volume->setGeometry(QRect(150, 420, 611, 31));
        horizontalSlider_Volume->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"	height : 10px;\n"
"	width : 500px;\n"
"	background : red;\n"
"	border-radius : 5px;\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"	background : rgb(255,255,255);\n"
"	width : 20px;\n"
"	height : 20px;\n"
"	margin : -7px -7px;\n"
"	border-radius : 10px;\n"
"}"));
        horizontalSlider_Volume->setOrientation(Qt::Orientation::Horizontal);
        pushButton_Volume = new QPushButton(centralwidget);
        pushButton_Volume->setObjectName("pushButton_Volume");
        pushButton_Volume->setGeometry(QRect(40, 390, 100, 100));
        pushButton_Volume->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 15px;\n"
"	min-width : 100px;\n"
"	max-width : 100px;\n"
"	min-height : 100px;\n"
"	max-height: 100px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	padding : 0px;\n"
"}"));
        pushButton_Volume->setIconSize(QSize(60, 60));
        label_Current_Time = new QLabel(centralwidget);
        label_Current_Time->setObjectName("label_Current_Time");
        label_Current_Time->setGeometry(QRect(0, 165, 80, 40));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font2.setPointSize(12);
        font2.setBold(true);
        label_Current_Time->setFont(font2);
        label_Current_Time->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	min-height : 40px;\n"
"	max-height: 40px;\n"
"	color : rgb(255,255,255);\n"
"}"));
        label_Current_Time->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_Total_Time = new QLabel(centralwidget);
        label_Total_Time->setObjectName("label_Total_Time");
        label_Total_Time->setGeometry(QRect(720, 165, 80, 40));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        label_Total_Time->setFont(font3);
        label_Total_Time->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	min-height : 40px;\n"
"	max-height: 40px;\n"
"	color : rgb(255,255,255);\n"
"}"));
        label_Total_Time->setAlignment(Qt::AlignmentFlag::AlignCenter);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 230, 801, 122));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Seek_Backward = new QPushButton(layoutWidget);
        pushButton_Seek_Backward->setObjectName("pushButton_Seek_Backward");
        pushButton_Seek_Backward->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	min-width : 120px;\n"
"	max-width : 120px;\n"
"	min-height : 120px;\n"
"	max-height: 120px;\n"
"	padding : 0px;\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color : rgb(140,140,140);\n"
"}"));
        pushButton_Seek_Backward->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_Seek_Backward);

        pushButton_Play_Pause = new QPushButton(layoutWidget);
        pushButton_Play_Pause->setObjectName("pushButton_Play_Pause");
        pushButton_Play_Pause->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	min-width : 120px;\n"
"	max-width : 120px;\n"
"	min-height : 120px;\n"
"	max-height: 120px;\n"
"	padding : 0px;\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color : rgb(140,140,140);\n"
"}"));
        pushButton_Play_Pause->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_Play_Pause);

        pushButton_Stop = new QPushButton(layoutWidget);
        pushButton_Stop->setObjectName("pushButton_Stop");
        pushButton_Stop->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	min-width : 120px;\n"
"	max-width : 120px;\n"
"	min-height : 120px;\n"
"	max-height: 120px;\n"
"	padding : 0px;\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color : rgb(140,140,140);\n"
"}"));
        pushButton_Stop->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_Stop);

        pushButton_Seek_Forward = new QPushButton(layoutWidget);
        pushButton_Seek_Forward->setObjectName("pushButton_Seek_Forward");
        pushButton_Seek_Forward->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border : none;\n"
"	border-radius : 60px;\n"
"	background-color : rgb(255,255,255);\n"
"	color : rgb(52,51,64);\n"
"	min-width : 120px;\n"
"	max-width : 120px;\n"
"	min-height : 120px;\n"
"	max-height: 120px;\n"
"	padding : 0px;\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color : rgb(140,140,140);\n"
"}"));
        pushButton_Seek_Forward->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_Seek_Forward);

        AudioView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AudioView);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        AudioView->setMenuBar(menubar);

        retranslateUi(AudioView);

        QMetaObject::connectSlotsByName(AudioView);
    } // setupUi

    void retranslateUi(QMainWindow *AudioView)
    {
        AudioView->setWindowTitle(QCoreApplication::translate("AudioView", "MainWindow", nullptr));
        actionOpen_Audio->setText(QCoreApplication::translate("AudioView", "Open Audio", nullptr));
        actionOpen_Video->setText(QCoreApplication::translate("AudioView", "Open Video", nullptr));
        label_File_Name->setText(QCoreApplication::translate("AudioView", "FILE NAME", nullptr));
        pushButton_Volume->setText(QString());
        label_Current_Time->setText(QCoreApplication::translate("AudioView", "00:00:00", nullptr));
        label_Total_Time->setText(QCoreApplication::translate("AudioView", "00:00:00", nullptr));
        pushButton_Seek_Backward->setText(QString());
        pushButton_Play_Pause->setText(QString());
        pushButton_Stop->setText(QString());
        pushButton_Seek_Forward->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AudioView: public Ui_AudioView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOVIEW_H
