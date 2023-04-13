#include "DFEMainWindow.hpp"
#include "ui_DFEMainWindow.h"

#include "DFESceneInspector.hpp"
#include "DFEViewport.hpp"

#include <QtWidgets>

DFEMainWindow::DFEMainWindow(QWidget *parent) 
    : QMainWindow(parent),
      ui(new Ui::DFEMainWindow),
      m_contentManager(new DFEContentManager(this))

{
    ui->setupUi(this);
    setMouseTracking(true);

    addDockWidget(Qt::BottomDockWidgetArea, m_contentManager);
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
    delete m_contentManager;
}
