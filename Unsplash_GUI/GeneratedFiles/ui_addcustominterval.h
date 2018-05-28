/********************************************************************************
** Form generated from reading UI file 'addcustominterval.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCUSTOMINTERVAL_H
#define UI_ADDCUSTOMINTERVAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addCustomInterval
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QDialog *addCustomInterval)
    {
        if (addCustomInterval->objectName().isEmpty())
            addCustomInterval->setObjectName(QStringLiteral("addCustomInterval"));
        addCustomInterval->resize(216, 115);
        gridLayout = new QGridLayout(addCustomInterval);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit = new QLineEdit(addCustomInterval);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(100, 20));
        lineEdit->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(lineEdit);

        label = new QLabel(addCustomInterval);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cancelButton = new QPushButton(addCustomInterval);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(addCustomInterval);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(addCustomInterval);
        QObject::connect(cancelButton, SIGNAL(clicked()), addCustomInterval, SLOT(reject()));
        QObject::connect(okButton, SIGNAL(clicked()), addCustomInterval, SLOT(accept()));

        QMetaObject::connectSlotsByName(addCustomInterval);
    } // setupUi

    void retranslateUi(QDialog *addCustomInterval)
    {
        addCustomInterval->setWindowTitle(QApplication::translate("addCustomInterval", "addCustomInterval", nullptr));
        label->setText(QApplication::translate("addCustomInterval", "hour", nullptr));
        cancelButton->setText(QApplication::translate("addCustomInterval", "Cancel", nullptr));
        okButton->setText(QApplication::translate("addCustomInterval", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addCustomInterval: public Ui_addCustomInterval {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCUSTOMINTERVAL_H
