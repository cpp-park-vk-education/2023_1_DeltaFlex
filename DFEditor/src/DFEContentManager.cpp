#include "DFEContentManager.hpp"

#include <QDebug>
#include <QList>
#include <QFileDialog>

DFEContentManager::DFEContentManager(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      mp_assetViewer(new DFEAssetViewer()),
      mp_projectExplorer(new DFEProjectExplorer()),
      mp_currentDirectory(new QString())
{
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(mp_projectExplorer);
    splitter->addWidget(mp_assetViewer);

    setWidget(splitter);

    setWindowTitle("Content Manager");

    connect(
        mp_assetViewer, 
        &QListView::doubleClicked, 
        this, 
        &DFEContentManager::UpdateAssetViewer
    );
}

DFEContentManager::~DFEContentManager()
{
    delete mp_assetViewer;
    delete mp_projectExplorer;
    delete mp_currentDirectory;
}

void DFEContentManager::UpdateViews(const QString &dir)
{
    mp_projectExplorer->UpdateView(dir);
    mp_assetViewer->UpdateView(dir);
}

void DFEContentManager::OpenDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, 
        tr("Open Directory"), 
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    *mp_currentDirectory = dir;

    UpdateViews(*mp_currentDirectory);
}

void DFEContentManager::UpdateAssetViewer(const QModelIndex &index)
{
    mp_assetViewer->UpdateView(mp_assetViewer->GetDirByIndex(index));
    mp_projectExplorer->ExpandDirectory(mp_projectExplorer->GetDirByIndex(index));
}
