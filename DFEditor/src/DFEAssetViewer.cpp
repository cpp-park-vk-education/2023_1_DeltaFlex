#include "DFEAssetViewer.hpp"
#include <QStyle>

DFEAssetViewer::DFEAssetViewer(QWidget *parent)
    : QListView(parent),
      mp_model(new QFileSystemModel())
{
    setFrameShape(QFrame::NoFrame);
    setViewMode(QListView::IconMode);

    mp_model->setFilter(QDir::QDir::AllEntries);
    mp_model->setRootPath("");
    mp_model->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    setModel(mp_model);
    
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

    if (QFileInfo(dir).isDir())
        setRootIndex(mp_model->index(dir));
}

QString DFEAssetViewer::GetDirByIndex(const QModelIndex &index)
{
    return mp_model->filePath(index);
}
