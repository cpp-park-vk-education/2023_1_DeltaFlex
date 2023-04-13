#include "DFEContentManager.hpp"

#include <QDebug>
#include <QList>

DFEContentManager::DFEContentManager(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      m_assetViewer(new DFEAssetViewer(this)),
      m_projectExplorer(new DFEProjectExplorer(this))
{ 
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(m_projectExplorer);
    splitter->addWidget(m_assetViewer);

    setWidget(splitter);

    setWindowTitle("Content Manager");
}

DFEContentManager::~DFEContentManager()
{
    delete m_assetViewer;
    delete m_projectExplorer;
}
