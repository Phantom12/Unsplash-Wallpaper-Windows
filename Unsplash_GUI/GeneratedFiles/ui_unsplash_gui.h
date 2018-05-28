/********************************************************************************
** Form generated from reading UI file 'unsplash_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNSPLASH_GUI_H
#define UI_UNSPLASH_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Unsplash_GUIClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *refreshLabel;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *intervalComboBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *resLabel;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *resComboBox;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *DifferentWallpapers_label;
    QLabel *DifferentWallpapers_label_2;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *differentWallpaper_checkBox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *autoStartCheckBox;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *saveLabel;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *defaultSaveButton;
    QPushButton *changeFolderButton;
    QLabel *saveFolderDisp;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *aboutButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshButton;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *exitButton;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Unsplash_GUIClass)
    {
        if (Unsplash_GUIClass->objectName().isEmpty())
            Unsplash_GUIClass->setObjectName(QStringLiteral("Unsplash_GUIClass"));
        Unsplash_GUIClass->resize(621, 458);
        centralWidget = new QWidget(Unsplash_GUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        refreshLabel = new QLabel(centralWidget);
        refreshLabel->setObjectName(QStringLiteral("refreshLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(12);
        refreshLabel->setFont(font);

        horizontalLayout->addWidget(refreshLabel);

        horizontalSpacer_6 = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        intervalComboBox = new QComboBox(centralWidget);
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->addItem(QString());
        intervalComboBox->setObjectName(QStringLiteral("intervalComboBox"));
        intervalComboBox->setEnabled(true);
        intervalComboBox->setMinimumSize(QSize(80, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        intervalComboBox->setFont(font1);
        intervalComboBox->setEditable(false);

        horizontalLayout->addWidget(intervalComboBox);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(577, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        resLabel = new QLabel(centralWidget);
        resLabel->setObjectName(QStringLiteral("resLabel"));
        resLabel->setFont(font);

        horizontalLayout_2->addWidget(resLabel);

        horizontalSpacer_5 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        resComboBox = new QComboBox(centralWidget);
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->addItem(QString());
        resComboBox->setObjectName(QStringLiteral("resComboBox"));
        resComboBox->setMinimumSize(QSize(80, 20));
        resComboBox->setFont(font1);

        horizontalLayout_2->addWidget(resComboBox);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(577, 19, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        DifferentWallpapers_label = new QLabel(centralWidget);
        DifferentWallpapers_label->setObjectName(QStringLiteral("DifferentWallpapers_label"));
        DifferentWallpapers_label->setFont(font);

        verticalLayout_2->addWidget(DifferentWallpapers_label);

        DifferentWallpapers_label_2 = new QLabel(centralWidget);
        DifferentWallpapers_label_2->setObjectName(QStringLiteral("DifferentWallpapers_label_2"));
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI"));
        font2.setPointSize(10);
        DifferentWallpapers_label_2->setFont(font2);

        verticalLayout_2->addWidget(DifferentWallpapers_label_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        differentWallpaper_checkBox = new QCheckBox(centralWidget);
        differentWallpaper_checkBox->setObjectName(QStringLiteral("differentWallpaper_checkBox"));
        differentWallpaper_checkBox->setFont(font);

        horizontalLayout_5->addWidget(differentWallpaper_checkBox);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(577, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout_6->addWidget(label);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        autoStartCheckBox = new QCheckBox(centralWidget);
        autoStartCheckBox->setObjectName(QStringLiteral("autoStartCheckBox"));
        autoStartCheckBox->setFont(font);

        horizontalLayout_6->addWidget(autoStartCheckBox);


        gridLayout->addLayout(horizontalLayout_6, 6, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 7, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        saveLabel = new QLabel(centralWidget);
        saveLabel->setObjectName(QStringLiteral("saveLabel"));
        saveLabel->setFont(font);

        horizontalLayout_3->addWidget(saveLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        defaultSaveButton = new QPushButton(centralWidget);
        defaultSaveButton->setObjectName(QStringLiteral("defaultSaveButton"));
        defaultSaveButton->setFont(font1);

        horizontalLayout_3->addWidget(defaultSaveButton);

        changeFolderButton = new QPushButton(centralWidget);
        changeFolderButton->setObjectName(QStringLiteral("changeFolderButton"));
        changeFolderButton->setEnabled(true);
        changeFolderButton->setFont(font1);

        horizontalLayout_3->addWidget(changeFolderButton);


        verticalLayout->addLayout(horizontalLayout_3);

        saveFolderDisp = new QLabel(centralWidget);
        saveFolderDisp->setObjectName(QStringLiteral("saveFolderDisp"));
        QFont font3;
        font3.setPointSize(12);
        saveFolderDisp->setFont(font3);

        verticalLayout->addWidget(saveFolderDisp);


        gridLayout->addLayout(verticalLayout, 8, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(577, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 9, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        aboutButton = new QPushButton(centralWidget);
        aboutButton->setObjectName(QStringLiteral("aboutButton"));
        aboutButton->setFont(font1);

        horizontalLayout_4->addWidget(aboutButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        refreshButton = new QPushButton(centralWidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));
        refreshButton->setFont(font1);

        horizontalLayout_4->addWidget(refreshButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setFont(font1);

        horizontalLayout_4->addWidget(exitButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 10, 0, 1, 1);

        Unsplash_GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Unsplash_GUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 621, 21));
        Unsplash_GUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Unsplash_GUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Unsplash_GUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Unsplash_GUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Unsplash_GUIClass->setStatusBar(statusBar);

        retranslateUi(Unsplash_GUIClass);
        QObject::connect(aboutButton, SIGNAL(clicked()), Unsplash_GUIClass, SLOT(on_About_clicked()));
        QObject::connect(refreshButton, SIGNAL(clicked()), Unsplash_GUIClass, SLOT(on_Refresh_clicked()));
        QObject::connect(resComboBox, SIGNAL(currentTextChanged(QString)), Unsplash_GUIClass, SLOT(on_Res_changed()));
        QObject::connect(intervalComboBox, SIGNAL(currentTextChanged(QString)), Unsplash_GUIClass, SLOT(on_Interval_changed()));
        QObject::connect(defaultSaveButton, SIGNAL(clicked()), Unsplash_GUIClass, SLOT(on_defaultSave_clicked()));
        QObject::connect(changeFolderButton, SIGNAL(clicked()), Unsplash_GUIClass, SLOT(on_changeSave_clicked()));
        QObject::connect(exitButton, SIGNAL(clicked()), Unsplash_GUIClass, SLOT(on_hide_clicked()));
        QObject::connect(differentWallpaper_checkBox, SIGNAL(stateChanged(int)), Unsplash_GUIClass, SLOT(on_differentWallpaper_clicked(int)));
        QObject::connect(autoStartCheckBox, SIGNAL(stateChanged(int)), Unsplash_GUIClass, SLOT(on_autoStart_clicked(int)));

        QMetaObject::connectSlotsByName(Unsplash_GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *Unsplash_GUIClass)
    {
        Unsplash_GUIClass->setWindowTitle(QApplication::translate("Unsplash_GUIClass", "Unsplash_GUI", nullptr));
        refreshLabel->setText(QApplication::translate("Unsplash_GUIClass", "Refresh interval (hour)", nullptr));
        intervalComboBox->setItemText(0, QApplication::translate("Unsplash_GUIClass", "5 min", nullptr));
        intervalComboBox->setItemText(1, QApplication::translate("Unsplash_GUIClass", "10 min", nullptr));
        intervalComboBox->setItemText(2, QApplication::translate("Unsplash_GUIClass", "15 min", nullptr));
        intervalComboBox->setItemText(3, QApplication::translate("Unsplash_GUIClass", "30 min", nullptr));
        intervalComboBox->setItemText(4, QApplication::translate("Unsplash_GUIClass", "1 hour", nullptr));
        intervalComboBox->setItemText(5, QApplication::translate("Unsplash_GUIClass", "2 hour", nullptr));
        intervalComboBox->setItemText(6, QApplication::translate("Unsplash_GUIClass", "4 hour", nullptr));
        intervalComboBox->setItemText(7, QApplication::translate("Unsplash_GUIClass", "6 hour", nullptr));
        intervalComboBox->setItemText(8, QApplication::translate("Unsplash_GUIClass", "12 hour", nullptr));
        intervalComboBox->setItemText(9, QApplication::translate("Unsplash_GUIClass", "1 day", nullptr));
        intervalComboBox->setItemText(10, QApplication::translate("Unsplash_GUIClass", "Custom", nullptr));

        intervalComboBox->setCurrentText(QApplication::translate("Unsplash_GUIClass", "5 min", nullptr));
        resLabel->setText(QApplication::translate("Unsplash_GUIClass", "Wallpaper resolution", nullptr));
        resComboBox->setItemText(0, QApplication::translate("Unsplash_GUIClass", "Auto", nullptr));
        resComboBox->setItemText(1, QApplication::translate("Unsplash_GUIClass", "1280x720", nullptr));
        resComboBox->setItemText(2, QApplication::translate("Unsplash_GUIClass", "1280x800", nullptr));
        resComboBox->setItemText(3, QApplication::translate("Unsplash_GUIClass", "1440x810", nullptr));
        resComboBox->setItemText(4, QApplication::translate("Unsplash_GUIClass", "1440x900", nullptr));
        resComboBox->setItemText(5, QApplication::translate("Unsplash_GUIClass", "1920x1080", nullptr));
        resComboBox->setItemText(6, QApplication::translate("Unsplash_GUIClass", "1920x1200", nullptr));
        resComboBox->setItemText(7, QApplication::translate("Unsplash_GUIClass", "2560x1440", nullptr));
        resComboBox->setItemText(8, QApplication::translate("Unsplash_GUIClass", "2560x1600", nullptr));
        resComboBox->setItemText(9, QApplication::translate("Unsplash_GUIClass", "3440x1440", nullptr));
        resComboBox->setItemText(10, QApplication::translate("Unsplash_GUIClass", "3840x2160", nullptr));

        DifferentWallpapers_label->setText(QApplication::translate("Unsplash_GUIClass", "Different Wallpapers on different monitors", nullptr));
        DifferentWallpapers_label_2->setText(QApplication::translate("Unsplash_GUIClass", "(minimum support: Windows 8)", nullptr));
        differentWallpaper_checkBox->setText(QApplication::translate("Unsplash_GUIClass", "Enable", nullptr));
        label->setText(QApplication::translate("Unsplash_GUIClass", "Auto start at system startup", nullptr));
        autoStartCheckBox->setText(QApplication::translate("Unsplash_GUIClass", "Enable", nullptr));
        saveLabel->setText(QApplication::translate("Unsplash_GUIClass", "Folder for saved wallpapers", nullptr));
        defaultSaveButton->setText(QApplication::translate("Unsplash_GUIClass", "Default", nullptr));
        changeFolderButton->setText(QApplication::translate("Unsplash_GUIClass", "Change", nullptr));
        saveFolderDisp->setText(QString());
        aboutButton->setText(QApplication::translate("Unsplash_GUIClass", "About", nullptr));
        refreshButton->setText(QApplication::translate("Unsplash_GUIClass", "Refresh now", nullptr));
        exitButton->setText(QApplication::translate("Unsplash_GUIClass", "Hide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Unsplash_GUIClass: public Ui_Unsplash_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNSPLASH_GUI_H
