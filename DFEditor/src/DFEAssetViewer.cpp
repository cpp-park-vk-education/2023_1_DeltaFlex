#include "DFEAssetViewer.hpp"
#include <QStyle>

DFEAssetViewer::DFEAssetViewer(QWidget *parent)
    : QListWidget(parent)
{
    setFrameShape(QFrame::NoFrame);
    setViewMode(QListView::IconMode);
}

void DFEAssetViewer::SetCurrentDirectory(const QString &dir)
{
    currentDirectory = dir;
}
