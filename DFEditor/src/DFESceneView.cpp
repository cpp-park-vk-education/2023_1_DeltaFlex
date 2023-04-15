#include "DFESceneView.hpp"
#include <iostream>

DFESceneView::DFESceneView(QWidget *parent) : 
    QTreeView(parent)
{
    setFrameShape(QFrame::NoFrame);
}
