#include "DFEMainWindow.hpp"
#include "ui_DFEMainWindow.h"

#include "DFEViewport.hpp"

#include <QtWidgets>

DFEMainWindow::DFEMainWindow(QWidget *parent) 
    : QMainWindow(parent),
      ui(new Ui::DFEMainWindow),
      m_contentManager(new DFEContentManager(this)),
      m_sceneInspector(new DFESceneInspector(this))

{
    ui->setupUi(this);

    addDockWidget(Qt::BottomDockWidgetArea, m_contentManager);
    addDockWidget(Qt::RightDockWidgetArea, m_sceneInspector);

    ui->menuWindow->addAction(m_contentManager->toggleViewAction());
    ui->menuWindow->addAction(m_sceneInspector->toggleViewAction());
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
    delete m_contentManager;
    delete m_sceneInspector;
}
