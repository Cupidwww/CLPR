/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GUI_H
#define GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *title;
    QFrame *midFrame;
    QGridLayout *gridLayout_4;
    QGridLayout *midLayout;
    QFrame *midRightFrame;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QLabel *matchCountLabel;
    QGraphicsView *resultImageDisplay;
    QLabel *regionLabel;
    QLabel *matchCount;
    QLabel *resultImageLabel;
    QLabel *regionDisplay;
    QLabel *resultLabel;
    QLabel *resultText;
    QFrame *midLeftFrame;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_3;
    QLabel *sourceImageTitle;
    QGraphicsView *sourceImageDisplay;
    QFrame *selectButtonFrame;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *selectImage;
    QPushButton *clearSelection;
    QFrame *lowerFrame;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QPushButton *historyButton;
    QPushButton *startButton;
    QPushButton *pushButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1235, 839);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        title->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(title, 0, 0, 1, 1);

        midFrame = new QFrame(centralwidget);
        midFrame->setObjectName("midFrame");
        midFrame->setFrameShape(QFrame::StyledPanel);
        midFrame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(midFrame);
        gridLayout_4->setObjectName("gridLayout_4");
        midLayout = new QGridLayout();
        midLayout->setObjectName("midLayout");
        midRightFrame = new QFrame(midFrame);
        midRightFrame->setObjectName("midRightFrame");
        midRightFrame->setFrameShape(QFrame::StyledPanel);
        midRightFrame->setFrameShadow(QFrame::Raised);
        gridLayout_10 = new QGridLayout(midRightFrame);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName("gridLayout_9");
        matchCountLabel = new QLabel(midRightFrame);
        matchCountLabel->setObjectName("matchCountLabel");

        gridLayout_9->addWidget(matchCountLabel, 0, 0, 1, 1);

        resultImageDisplay = new QGraphicsView(midRightFrame);
        resultImageDisplay->setObjectName("resultImageDisplay");

        gridLayout_9->addWidget(resultImageDisplay, 2, 1, 1, 1);

        regionLabel = new QLabel(midRightFrame);
        regionLabel->setObjectName("regionLabel");

        gridLayout_9->addWidget(regionLabel, 1, 0, 1, 1);

        matchCount = new QLabel(midRightFrame);
        matchCount->setObjectName("matchCount");

        gridLayout_9->addWidget(matchCount, 0, 1, 1, 1);

        resultImageLabel = new QLabel(midRightFrame);
        resultImageLabel->setObjectName("resultImageLabel");

        gridLayout_9->addWidget(resultImageLabel, 2, 0, 1, 1);

        regionDisplay = new QLabel(midRightFrame);
        regionDisplay->setObjectName("regionDisplay");

        gridLayout_9->addWidget(regionDisplay, 1, 1, 1, 1);

        resultLabel = new QLabel(midRightFrame);
        resultLabel->setObjectName("resultLabel");

        gridLayout_9->addWidget(resultLabel, 3, 0, 1, 1);

        resultText = new QLabel(midRightFrame);
        resultText->setObjectName("resultText");

        gridLayout_9->addWidget(resultText, 3, 1, 1, 1);

        gridLayout_9->setRowStretch(0, 1);
        gridLayout_9->setRowStretch(1, 1);
        gridLayout_9->setRowStretch(2, 1);
        gridLayout_9->setRowStretch(3, 1);
        gridLayout_9->setColumnStretch(0, 1);
        gridLayout_9->setColumnStretch(1, 2);

        gridLayout_10->addLayout(gridLayout_9, 0, 0, 1, 1);


        midLayout->addWidget(midRightFrame, 0, 1, 1, 1);

        midLeftFrame = new QFrame(midFrame);
        midLeftFrame->setObjectName("midLeftFrame");
        midLeftFrame->setFrameShape(QFrame::StyledPanel);
        midLeftFrame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(midLeftFrame);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        sourceImageTitle = new QLabel(midLeftFrame);
        sourceImageTitle->setObjectName("sourceImageTitle");

        gridLayout_3->addWidget(sourceImageTitle, 0, 0, 1, 1);

        sourceImageDisplay = new QGraphicsView(midLeftFrame);
        sourceImageDisplay->setObjectName("sourceImageDisplay");

        gridLayout_3->addWidget(sourceImageDisplay, 1, 0, 1, 1);

        selectButtonFrame = new QFrame(midLeftFrame);
        selectButtonFrame->setObjectName("selectButtonFrame");
        selectButtonFrame->setFrameShape(QFrame::StyledPanel);
        selectButtonFrame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(selectButtonFrame);
        gridLayout_6->setObjectName("gridLayout_6");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        selectImage = new QPushButton(selectButtonFrame);
        selectImage->setObjectName("selectImage");

        horizontalLayout->addWidget(selectImage);

        clearSelection = new QPushButton(selectButtonFrame);
        clearSelection->setObjectName("clearSelection");

        horizontalLayout->addWidget(clearSelection);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(selectButtonFrame, 2, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 9);
        gridLayout_3->setRowStretch(2, 1);

        gridLayout_5->addLayout(gridLayout_3, 0, 0, 1, 1);


        midLayout->addWidget(midLeftFrame, 0, 0, 1, 1);

        midLayout->setColumnStretch(0, 2);
        midLayout->setColumnStretch(1, 1);

        gridLayout_4->addLayout(midLayout, 0, 0, 1, 1);


        gridLayout->addWidget(midFrame, 1, 0, 1, 1);

        lowerFrame = new QFrame(centralwidget);
        lowerFrame->setObjectName("lowerFrame");
        lowerFrame->setFrameShape(QFrame::StyledPanel);
        lowerFrame->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(lowerFrame);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName("gridLayout_7");
        historyButton = new QPushButton(lowerFrame);
        historyButton->setObjectName("historyButton");

        gridLayout_7->addWidget(historyButton, 0, 2, 1, 1);

        startButton = new QPushButton(lowerFrame);
        startButton->setObjectName("startButton");

        gridLayout_7->addWidget(startButton, 0, 0, 1, 1);

        pushButton = new QPushButton(lowerFrame);
        pushButton->setObjectName("pushButton");

        gridLayout_7->addWidget(pushButton, 0, 1, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);


        gridLayout->addWidget(lowerFrame, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 5);
        gridLayout->setRowStretch(2, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1235, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "\350\275\246\347\211\214\350\257\206\345\210\253\347\263\273\347\273\237", nullptr));
        matchCountLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\206\345\210\253\346\225\260\351\207\217", nullptr));
        regionLabel->setText(QCoreApplication::translate("MainWindow", "\345\234\260\345\214\272", nullptr));
        matchCount->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        resultImageLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\206\345\210\253\347\273\223\346\236\234\357\274\210\345\233\276\347\211\207\357\274\211", nullptr));
        regionDisplay->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\206\345\210\253\347\273\223\346\236\234\357\274\210\346\226\207\345\255\227\357\274\211", nullptr));
        resultText->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        sourceImageTitle->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\233\276\347\211\207", nullptr));
        selectImage->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        clearSelection->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\351\200\211\346\213\251", nullptr));
        historyButton->setText(QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\350\257\206\345\210\253", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\257\246\347\273\206\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GUI_H
