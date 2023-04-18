#include "DFEAssetViewer.hpp"
#include <QStyle>

DFEAssetViewer::DFEAssetViewer(QWidget *parent)
    : QListView(parent),
      m_model(new QFileSystemModel())
{
    setFrameShape(QFrame::NoFrame);
    setViewMode(QListView::IconMode);

    m_model->setRootPath("");
    setModel(m_model);
    
    setStyleSheet("QListView { font: 12px }");

    setFlow(QListView::LeftToRight);
    setMovement(QListView::Static);
    setGridSize(QSize(100, 100));
    setResizeMode(QListView::Adjust);
    // setLayoutMode(QListView::Batched);
    setUniformItemSizes(true);
    setWrapping(true);
    setWordWrap(true);
    setDragEnabled(true);
    setTextElideMode(Qt::ElideMiddle);
}

void DFEAssetViewer::UpdateView(const QString &dir)
{
    qDebug() << dir;
    setRootIndex(m_model->index(dir));
}
