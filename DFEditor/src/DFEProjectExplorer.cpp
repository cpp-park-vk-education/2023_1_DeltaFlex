#include "DFEProjectExplorer.hpp"
#include <QFrame>
#include <QIcon>
#include <QDebug>

DFEProjectExplorer::DFEProjectExplorer(QWidget *parent)
    : QTreeView(parent),
      m_model(new QFileSystemModel())
{
    setFrameShape(QFrame::NoFrame);

    setWordWrap(true);
    setHeaderHidden(true);

    m_model->setRootPath("");
    setModel(m_model);

    setStyleSheet("QTreeView { font: 11px }");

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
}

void DFEProjectExplorer::UpdateView(const QString &dir)
{
    qDebug() << dir;
    setRootIndex(m_model->index(dir));
}
