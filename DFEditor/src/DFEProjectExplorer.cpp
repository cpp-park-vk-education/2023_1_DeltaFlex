#include "DFEProjectExplorer.hpp"
#include <QFrame>
#include <QIcon>
#include <QDebug>

DFEProjectExplorer::DFEProjectExplorer(QWidget *parent)
    : QTreeView(parent),
      mp_model(new QFileSystemModel())
{
    setFrameShape(QFrame::NoFrame);

    setWordWrap(true);
    setHeaderHidden(true);

    mp_model->setRootPath("");
    setModel(mp_model);

    setStyleSheet("QTreeView { font: 12px }");

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
}

void DFEProjectExplorer::UpdateView(const QString &dir)
{
    qDebug() << dir;
    setRootIndex(mp_model->index(dir));
}
