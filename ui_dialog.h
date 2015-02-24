/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbSend;
    QLineEdit *leHost;
    QLineEdit *lePort;
    QCheckBox *cbToAll;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbStartStop;
    QListWidget *lwUsers;
    QListWidget *lwLog;
    QPlainTextEdit *pteMessage;
    QLabel *label_4;
    QLabel *lContrast;
    QLabel *Status;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(531, 339);
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(9, 238, 61, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 207, 515, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pbSend = new QPushButton(layoutWidget);
        pbSend->setObjectName(QString::fromUtf8("pbSend"));

        horizontalLayout->addWidget(pbSend);

        leHost = new QLineEdit(layoutWidget);
        leHost->setObjectName(QString::fromUtf8("leHost"));

        horizontalLayout->addWidget(leHost);

        lePort = new QLineEdit(layoutWidget);
        lePort->setObjectName(QString::fromUtf8("lePort"));

        horizontalLayout->addWidget(lePort);

        cbToAll = new QCheckBox(layoutWidget);
        cbToAll->setObjectName(QString::fromUtf8("cbToAll"));
        cbToAll->setChecked(true);
        cbToAll->setTristate(false);

        horizontalLayout->addWidget(cbToAll);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbStartStop = new QPushButton(layoutWidget);
        pbStartStop->setObjectName(QString::fromUtf8("pbStartStop"));
        pbStartStop->setCheckable(true);
        pbStartStop->setChecked(false);

        horizontalLayout->addWidget(pbStartStop);

        lwUsers = new QListWidget(Dialog);
        lwUsers->setObjectName(QString::fromUtf8("lwUsers"));
        lwUsers->setGeometry(QRect(443, 9, 81, 192));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lwUsers->sizePolicy().hasHeightForWidth());
        lwUsers->setSizePolicy(sizePolicy);
        lwUsers->setDragDropMode(QAbstractItemView::NoDragDrop);
        lwUsers->setSelectionMode(QAbstractItemView::MultiSelection);
        lwUsers->setSortingEnabled(true);
        lwLog = new QListWidget(Dialog);
        lwLog->setObjectName(QString::fromUtf8("lwLog"));
        lwLog->setGeometry(QRect(9, 9, 421, 192));
        sizePolicy.setHeightForWidth(lwLog->sizePolicy().hasHeightForWidth());
        lwLog->setSizePolicy(sizePolicy);
        lwLog->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        lwLog->setSelectionRectVisible(false);
        pteMessage = new QPlainTextEdit(Dialog);
        pteMessage->setObjectName(QString::fromUtf8("pteMessage"));
        pteMessage->setGeometry(QRect(9, 257, 515, 73));
        pteMessage->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 240, 46, 13));
        lContrast = new QLabel(Dialog);
        lContrast->setObjectName(QString::fromUtf8("lContrast"));
        lContrast->setGeometry(QRect(220, 240, 46, 13));
        Status = new QLabel(Dialog);
        Status->setObjectName(QString::fromUtf8("Status"));
        Status->setGeometry(QRect(270, 240, 46, 13));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\320\241\321\202\320\260\320\275\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        pbSend->setText(QApplication::translate("Dialog", "\320\241\320\262\321\217\320\267\321\214", 0, QApplication::UnicodeUTF8));
        leHost->setText(QApplication::translate("Dialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        lePort->setText(QApplication::translate("Dialog", "1234", 0, QApplication::UnicodeUTF8));
        cbToAll->setText(QApplication::translate("Dialog", "\320\236\320\261\321\211\320\265\320\265", 0, QApplication::UnicodeUTF8));
        cbToAll->setShortcut(QString());
        pbStartStop->setText(QApplication::translate("Dialog", "\320\241\320\274\320\265\320\275\320\260 \320\260\320\264\321\200\320\265\321\201\320\260", 0, QApplication::UnicodeUTF8));
        pteMessage->setPlainText(QString());
        label_4->setText(QApplication::translate("Dialog", "3.7", 0, QApplication::UnicodeUTF8));
        lContrast->setText(QString());
        Status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
