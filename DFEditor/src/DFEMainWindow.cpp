#include "DFEMainWindow.hpp"
#include "ui_DFEMainWindow.h"
#include "DFESceneInspector.hpp"
#include "DFEViewport.hpp"

#include <QtWidgets>

DFEMainWindow::DFEMainWindow(QWidget *parent) : 
    QMainWindow(parent),
    ui(new Ui::DFEMainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
}
