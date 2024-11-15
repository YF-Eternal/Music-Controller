/********************************************************************************
** Form generated from reading UI file 'MusicController.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICCONTROLLER_H
#define UI_MUSICCONTROLLER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *exportButton;
    QProgressBar *progressBar;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QSlider *volumeSlider;
    QSpinBox *volumeSpinBox;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout;
    QSlider *speedSlider;
    QSpinBox *speedSpinBox;
    QLabel *speedLabel;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *fileNameLabel;
    QPushButton *openButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(775, 395);
        MainWindow->setMinimumSize(QSize(775, 395));
        MainWindow->setMaximumSize(QSize(775, 395));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/yfete/.designer/backup/icon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 220, 631, 131));
        groupBox->setFont(font);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(60, 20, 513, 111));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        exportButton = new QPushButton(layoutWidget);
        exportButton->setObjectName("exportButton");
        exportButton->setMinimumSize(QSize(271, 31));
        exportButton->setFont(font);

        verticalLayout_2->addWidget(exportButton);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(511, 23));
        progressBar->setFont(font);
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(660, 10, 101, 341));
        groupBox_2->setFont(font);
        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 30, 81, 301));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        volumeSlider = new QSlider(layoutWidget_2);
        volumeSlider->setObjectName("volumeSlider");
        volumeSlider->setMaximumSize(QSize(40, 269));
        volumeSlider->setFont(font);
        volumeSlider->setStyleSheet(QString::fromUtf8(""));
        volumeSlider->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        volumeSlider->setMinimum(-30);
        volumeSlider->setMaximum(30);
        volumeSlider->setValue(0);
        volumeSlider->setOrientation(Qt::Orientation::Vertical);
        volumeSlider->setTickPosition(QSlider::TickPosition::TicksBothSides);
        volumeSlider->setTickInterval(10);

        verticalLayout->addWidget(volumeSlider, 0, Qt::AlignmentFlag::AlignHCenter);

        volumeSpinBox = new QSpinBox(layoutWidget_2);
        volumeSpinBox->setObjectName("volumeSpinBox");
        volumeSpinBox->setMinimumSize(QSize(42, 24));
        volumeSpinBox->setFont(font);
        volumeSpinBox->setMinimum(-30);
        volumeSpinBox->setMaximum(30);
        volumeSpinBox->setValue(0);

        verticalLayout->addWidget(volumeSpinBox);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 110, 631, 101));
        groupBox_3->setFont(font);
        layoutWidget_3 = new QWidget(groupBox_3);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(10, 40, 611, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        speedSlider = new QSlider(layoutWidget_3);
        speedSlider->setObjectName("speedSlider");
        speedSlider->setMinimumSize(QSize(500, 30));
        speedSlider->setMaximumSize(QSize(500, 30));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        speedSlider->setFont(font1);
        speedSlider->setStyleSheet(QString::fromUtf8(""));
        speedSlider->setMinimum(500);
        speedSlider->setMaximum(10000);
        speedSlider->setPageStep(10);
        speedSlider->setValue(1000);
        speedSlider->setOrientation(Qt::Orientation::Horizontal);
        speedSlider->setTickPosition(QSlider::TickPosition::TicksBelow);
        speedSlider->setTickInterval(500);

        horizontalLayout->addWidget(speedSlider);

        speedSpinBox = new QSpinBox(layoutWidget_3);
        speedSpinBox->setObjectName("speedSpinBox");
        speedSpinBox->setMinimumSize(QSize(100, 24));
        speedSpinBox->setMaximumSize(QSize(100, 24));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(8);
        speedSpinBox->setFont(font2);
        speedSpinBox->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        speedSpinBox->setMinimum(500);
        speedSpinBox->setMaximum(10000);
        speedSpinBox->setValue(1000);

        horizontalLayout->addWidget(speedSpinBox);

        speedLabel = new QLabel(groupBox_3);
        speedLabel->setObjectName("speedLabel");
        speedLabel->setGeometry(QRect(280, 20, 181, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setItalic(false);
        speedLabel->setFont(font3);
        speedLabel->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(20, 10, 631, 91));
        groupBox_4->setFont(font);
        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(40, 30, 561, 44));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        fileNameLabel = new QLabel(layoutWidget1);
        fileNameLabel->setObjectName("fileNameLabel");
        fileNameLabel->setMaximumSize(QSize(483, 15));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        fileNameLabel->setFont(font4);
        fileNameLabel->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align: right;"));

        horizontalLayout_2->addWidget(fileNameLabel, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        openButton = new QPushButton(layoutWidget1);
        openButton->setObjectName("openButton");
        openButton->setMinimumSize(QSize(100, 30));
        openButton->setMaximumSize(QSize(70, 24));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font5.setPointSize(9);
        font5.setBold(false);
        font5.setItalic(false);
        openButton->setFont(font5);
        openButton->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout_2->addWidget(openButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 775, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Export", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Volume Control", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Speed Control", nullptr));
        speedLabel->setText(QCoreApplication::translate("MainWindow", "Speed: 1.000x", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Import", nullptr));
        fileNameLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Current file: &quot;&quot;</p></body></html>", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICCONTROLLER_H
