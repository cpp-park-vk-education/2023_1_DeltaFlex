#include "DFEAssetViewer.hpp"

DFEAssetViewer::DFEAssetViewer(QWidget *parent)
    : QTableView(parent)
{
    setFrameShape(QFrame::NoFrame);
}

void DFEAssetViewer::SetCurrentDirectory(const QString &dir)
{
    currentDirectory = dir;
}
