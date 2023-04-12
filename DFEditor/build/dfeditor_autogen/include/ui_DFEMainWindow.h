/********************************************************************************
** Form generated from reading UI file 'DFEMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DFEMAINWINDOW_H
#define UI_DFEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "DFEDirectoryViewer.hpp"
#include "DFESceneInspector.hpp"

QT_BEGIN_NAMESPACE

class Ui_DFEMainWindow
{
public:
    QAction *actionSave;
    QAction *actionScene_Inspector;
    QAction *actionProperties;
    QAction *actionContent_Manager;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuWindow;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTableView *tableView;
    DFEDirectoryViewer *widget;
    QDockWidget *sceneGraphView;
    QWidget *dockWidgetContents_6;
    QVBoxLayout *verticalLayout_2;
    DFESceneInspector *treeView;
    QDockWidget *propertiesView;
    QWidget *dockWidgetContents_10;
    QToolBar *toolBar;

    void setupUi(QMainWindow *DFEMainWindow)
    {
        if (DFEMainWindow->objectName().isEmpty())
            DFEMainWindow->setObjectName(QString::fromUtf8("DFEMainWindow"));
        DFEMainWindow->resize(1315, 873);
        QFont font;
        font.setPointSize(11);
        DFEMainWindow->setFont(font);
        actionSave = new QAction(DFEMainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave->setIcon(icon);
        actionScene_Inspector = new QAction(DFEMainWindow);
        actionScene_Inspector->setObjectName(QString::fromUtf8("actionScene_Inspector"));
        actionScene_Inspector->setCheckable(true);
        actionProperties = new QAction(DFEMainWindow);
        actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
        actionProperties->setCheckable(true);
        actionContent_Manager = new QAction(DFEMainWindow);
        actionContent_Manager->setObjectName(QString::fromUtf8("actionContent_Manager"));
        actionContent_Manager->setCheckable(true);
        centralwidget = new QWidget(DFEMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(graphicsView);

        DFEMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DFEMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1315, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        DFEMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DFEMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DFEMainWindow->setStatusBar(statusbar);
        dockWidget_4 = new QDockWidget(DFEMainWindow);
        dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(dockWidgetContents_4);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMouseTracking(true);
        tableView->setAcceptDrops(true);
        tableView->setStyleSheet(QString::fromUtf8(""));
        tableView->setFrameShape(QFrame::NoFrame);
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setVisible(false);
        tableView->verticalHeader()->setVisible(false);
        widget = new DFEDirectoryViewer(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        splitter->addWidget(widget);

        horizontalLayout->addWidget(splitter);

        dockWidget_4->setWidget(dockWidgetContents_4);
        DFEMainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_4);
        sceneGraphView = new QDockWidget(DFEMainWindow);
        sceneGraphView->setObjectName(QString::fromUtf8("sceneGraphView"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeView = new DFESceneInspector(dockWidgetContents_6);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setStyleSheet(QString::fromUtf8(""));
        treeView->setFrameShape(QFrame::NoFrame);
        treeView->setFrameShadow(QFrame::Plain);

        verticalLayout_2->addWidget(treeView);

        sceneGraphView->setWidget(dockWidgetContents_6);
        DFEMainWindow->addDockWidget(Qt::RightDockWidgetArea, sceneGraphView);
        propertiesView = new QDockWidget(DFEMainWindow);
        propertiesView->setObjectName(QString::fromUtf8("propertiesView"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sans Serif"));
        font1.setPointSize(11);
        propertiesView->setFont(font1);
        dockWidgetContents_10 = new QWidget();
        dockWidgetContents_10->setObjectName(QString::fromUtf8("dockWidgetContents_10"));
        propertiesView->setWidget(dockWidgetContents_10);
        DFEMainWindow->addDockWidget(Qt::RightDockWidgetArea, propertiesView);
        toolBar = new QToolBar(DFEMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        DFEMainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menuWindow->addAction(actionScene_Inspector);
        menuWindow->addAction(actionProperties);
        menuWindow->addAction(actionContent_Manager);
        toolBar->addAction(actionSave);

        retranslateUi(DFEMainWindow);

        QMetaObject::connectSlotsByName(DFEMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DFEMainWindow)
    {
        DFEMainWindow->setWindowTitle(QCoreApplication::translate("DFEMainWindow", "DeltaFlex Engine Editor", nullptr));
        actionSave->setText(QCoreApplication::translate("DFEMainWindow", "Save", nullptr));
        actionScene_Inspector->setText(QCoreApplication::translate("DFEMainWindow", "Scene Inspector", nullptr));
        actionProperties->setText(QCoreApplication::translate("DFEMainWindow", "Properties", nullptr));
        actionContent_Manager->setText(QCoreApplication::translate("DFEMainWindow", "Content Manager", nullptr));
        menuFile->setTitle(QCoreApplication::translate("DFEMainWindow", "File", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("DFEMainWindow", "Window", nullptr));
        dockWidget_4->setWindowTitle(QCoreApplication::translate("DFEMainWindow", "Content Manager", nullptr));
        sceneGraphView->setWindowTitle(QCoreApplication::translate("DFEMainWindow", "Scene Inspector", nullptr));
        propertiesView->setWindowTitle(QCoreApplication::translate("DFEMainWindow", "Properties", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("DFEMainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DFEMainWindow: public Ui_DFEMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DFEMAINWINDOW_H
