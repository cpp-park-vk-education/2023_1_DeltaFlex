#include "DFEContentManager.hpp"

#include <QDebug>
#include <QList>
#include <QFileDialog>

DFEContentManager::DFEContentManager(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      mp_assetViewer(new DFEAssetViewer()),
      mp_projectExplorer(new DFEProjectExplorer())
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

    connect(
        mp_projectExplorer,
        &QTreeView::doubleClicked,
        mp_assetViewer,
        [&](const QModelIndex &index){ mp_assetViewer->UpdateView(mp_assetViewer->GetDirByIndex(index)); }
    );
}

DFEContentManager::~DFEContentManager()
{
    delete mp_assetViewer;
    delete mp_projectExplorer;
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

    UpdateViews(dir);
}

void DFEContentManager::UpdateAssetViewer(const QModelIndex &index)
{
    mp_assetViewer->UpdateView(mp_assetViewer->GetDirByIndex(index));
    mp_projectExplorer->ExpandDirectory(mp_projectExplorer->GetDirByIndex(index));
}
