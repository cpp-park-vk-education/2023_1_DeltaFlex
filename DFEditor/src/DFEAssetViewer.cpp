#include "DFEAssetViewer.hpp"

DFEAssetViewer::DFEAssetViewer(QWidget *parent)
    : QTableView(parent)
{
}

void DFEAssetViewer::SetCurrentDirectory(const QString &dir)
{
    currentDirectory = dir;
}
