/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Nov 29 15:40:27 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionApri;
    QAction *actionGenera_Cornici;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *txtOriginalDir;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QListView *listView;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSlider *frameSize;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblPreview;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(866, 578);
        actionApri = new QAction(MainWindow);
        actionApri->setObjectName(QString::fromUtf8("actionApri"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/open-folder"), QSize(), QIcon::Normal, QIcon::Off);
        actionApri->setIcon(icon);
        actionGenera_Cornici = new QAction(MainWindow);
        actionGenera_Cornici->setObjectName(QString::fromUtf8("actionGenera_Cornici"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/play"), QSize(), QIcon::Normal, QIcon::Off);
        actionGenera_Cornici->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        txtOriginalDir = new QLineEdit(centralWidget);
        txtOriginalDir->setObjectName(QString::fromUtf8("txtOriginalDir"));
        txtOriginalDir->setMinimumSize(QSize(400, 0));
        txtOriginalDir->setReadOnly(true);

        horizontalLayout->addWidget(txtOriginalDir);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/bmb.png")));

        horizontalLayout->addWidget(label);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMinimumSize(QSize(450, 0));
        listView->setViewMode(QListView::ListMode);
        listView->setUniformItemSizes(true);

        horizontalLayout_2->addWidget(listView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(200, 0));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout_3->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setChecked(false);

        verticalLayout_3->addWidget(radioButton_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(label_3);

        frameSize = new QSlider(groupBox);
        frameSize->setObjectName(QString::fromUtf8("frameSize"));
        frameSize->setMinimumSize(QSize(280, 0));
        frameSize->setMaximumSize(QSize(280, 16777215));
        frameSize->setMaximum(40);
        frameSize->setValue(16);
        frameSize->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(frameSize);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(groupBox);

        lblPreview = new QLabel(centralWidget);
        lblPreview->setObjectName(QString::fromUtf8("lblPreview"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblPreview->sizePolicy().hasHeightForWidth());
        lblPreview->setSizePolicy(sizePolicy);
        lblPreview->setMinimumSize(QSize(400, 300));
        lblPreview->setMaximumSize(QSize(400, 16777215));
        lblPreview->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lblPreview);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setMinimumSize(QSize(400, 0));
        progressBar->setMaximumSize(QSize(400, 16777215));
        progressBar->setBaseSize(QSize(400, 0));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);

        verticalLayout_2->addWidget(progressBar);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 866, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionApri);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionGenera_Cornici);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "BMB Framer", 0, QApplication::UnicodeUTF8));
        actionApri->setText(QApplication::translate("MainWindow", "Apri", 0, QApplication::UnicodeUTF8));
        actionGenera_Cornici->setText(QApplication::translate("MainWindow", "Genera Cornici", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Cartella degli originali:", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Opzioni", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("MainWindow", "Matrimonio", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "Reportage", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Dimensione bordo:", 0, QApplication::UnicodeUTF8));
        lblPreview->setText(QApplication::translate("MainWindow", "Anteprima", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
