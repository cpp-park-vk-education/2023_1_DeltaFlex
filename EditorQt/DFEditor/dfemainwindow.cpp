#include "dfemainwindow.h"
#include "./ui_dfemainwindow.h"

DFEMainWindow::DFEMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DFEMainWindow)
{
    ui->setupUi(this);
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
}

