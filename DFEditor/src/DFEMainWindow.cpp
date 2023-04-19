#include "DFEMainWindow.hpp"
#include "ui_DFEMainWindow.h"

#include "DFEViewport.hpp"

#include <QtWidgets>

DFEMainWindow::DFEMainWindow(QWidget *parent) 
    : QMainWindow(parent),
      ui(new Ui::DFEMainWindow),
      mp_contentManager(new DFEContentManager()),
      mp_sceneInspector(new DFESceneInspector()),
      mp_propertiesPanel(new DFEPropertiesPanel())

{
    ui->setupUi(this);

    addDockWidget(Qt::BottomDockWidgetArea, mp_contentManager);
    addDockWidget(Qt::RightDockWidgetArea, mp_sceneInspector);
    addDockWidget(Qt::RightDockWidgetArea, mp_propertiesPanel);

    ui->menuWindow->addAction(mp_contentManager->toggleViewAction());
    ui->menuWindow->addAction(mp_sceneInspector->toggleViewAction());
    ui->menuWindow->addAction(mp_propertiesPanel->toggleViewAction());

    connect(
        ui->actionOpen_Project,
        &QAction::triggered, 
        mp_contentManager,
        &DFEContentManager::OpenDirectory
    );
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
    delete mp_contentManager;
    delete mp_sceneInspector;
    delete mp_propertiesPanel;
}
