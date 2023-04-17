#include "DFEProjectExplorer.hpp"
#include <QFrame>
#include <QIcon>
#include <QDebug>

DFEProjectExplorer::DFEProjectExplorer(QWidget *parent)
    : QTreeView(parent)
{
    setFrameShape(QFrame::NoFrame);
}

