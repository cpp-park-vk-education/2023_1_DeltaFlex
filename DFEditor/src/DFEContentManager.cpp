#include "DFEContentManager.hpp"

#include <QDebug>
#include <QList>
#include <QFileDialog>

DFEContentManager::DFEContentManager(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      m_assetViewer(new DFEAssetViewer()),
      m_projectExplorer(new DFEProjectExplorer()),
      m_currentDirectory(new QString())
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
    delete m_currentDirectory;
}

void DFEContentManager::UpdateViews(const QString &dir)
{
    m_projectExplorer->UpdateView(dir);
    m_assetViewer->UpdateView(dir);
}

void DFEContentManager::OpenDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, 
        tr("Open Directory"), 
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    *m_currentDirectory = dir;

    UpdateViews(*m_currentDirectory);
}
