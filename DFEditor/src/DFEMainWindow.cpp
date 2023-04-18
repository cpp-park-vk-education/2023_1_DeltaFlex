#include "DFEMainWindow.hpp"
#include "ui_DFEMainWindow.h"

#include "DFEViewport.hpp"

#include <QtWidgets>

DFEMainWindow::DFEMainWindow(QWidget *parent) 
    : QMainWindow(parent),
      ui(new Ui::DFEMainWindow),
      m_contentManager(new DFEContentManager(this)),
      m_sceneInspector(new DFESceneInspector(this)),
      m_propertiesPanel(new DFEPropertiesPanel(this))

{
    ui->setupUi(this);

    addDockWidget(Qt::BottomDockWidgetArea, m_contentManager);
    addDockWidget(Qt::RightDockWidgetArea, m_sceneInspector);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesPanel);

    ui->menuWindow->addAction(m_contentManager->toggleViewAction());
    ui->menuWindow->addAction(m_sceneInspector->toggleViewAction());
    ui->menuWindow->addAction(m_propertiesPanel->toggleViewAction());

    connect(
        ui->actionOpen_Project,
        &QAction::triggered, 
        m_contentManager,
        &DFEContentManager::OpenDirectory
    );
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
    delete m_contentManager;
    delete m_sceneInspector;
    delete m_propertiesPanel;
}
