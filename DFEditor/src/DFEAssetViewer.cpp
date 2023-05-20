#include "DFEAssetViewer.hpp"
#include <QStyle>
#include <QErrorMessage>

DFEAssetViewer::DFEAssetViewer(QWidget *parent)
    : QListView(parent),
      mp_model(new QFileSystemModel(this))
{
    setFrameShape(QFrame::NoFrame);
    setViewMode(QListView::IconMode);

    mp_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    mp_model->setRootPath("/");
    setModel(mp_model);

    setRootIndex(mp_model->index("/"));

    setStyleSheet("QListView { font: 12px }");

    setFlow(QListView::LeftToRight);
    setMovement(QListView::Static);
    setGridSize(QSize(100, 100));
    setResizeMode(QListView::Adjust);

    setUniformItemSizes(true);
    setWrapping(true);
    setWordWrap(true);
    setDragEnabled(true);
    setTextElideMode(Qt::ElideMiddle);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(
        this,
        &DFEAssetViewer::customContextMenuRequested,
        this,
        &DFEAssetViewer::ContextMenuRequested);

    QShortcut *folder_rename_shortcut = new QShortcut(QKeySequence(Qt::Key_F2), this);
    connect(folder_rename_shortcut, &QShortcut::activated, this, &DFEAssetViewer::handleFolderRenamed);
}

void DFEAssetViewer::UpdateView(const QString &dir)
{
    QDir directory(dir);
    if (directory.exists() && directory.isReadable())
    {
        setRootIndex(mp_model->index(dir));
    }
    else
    {
        QErrorMessage *err_msgbox = new QErrorMessage();
        QString msg = "Error accessing " + dir + ": permission denied";
        err_msgbox->showMessage(msg);
        err_msgbox->exec();
        qDebug() << msg;
        delete err_msgbox;
    }
}

QString DFEAssetViewer::GetDirByIndex(const QModelIndex &index)
{
    return mp_model->filePath(index);
}

void DFEAssetViewer::CreateFolder()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new folder"),
                                         tr("New folder name"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        QString current_dir = mp_model->filePath(rootIndex());
        QDir dir(current_dir);
        dir.mkdir(text);
    }
}

void DFEAssetViewer::ContextMenuRequested(const QPoint &pos)
{
    QMenu *menu{new QMenu()};
    QAction *create_file{new QAction("New file", this)};
    QAction *create_folder{new QAction("New folder", this)};

    connect(
        create_folder,
        &QAction::triggered,
        this,
        &DFEAssetViewer::CreateFolder);

    menu->addAction(create_file);
    menu->addAction(create_folder);
    menu->popup(mapToGlobal(pos));
}

void DFEAssetViewer::handleFolderRenamed()
{
    QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty())
    {
        QModelIndex selectedIndex = selectedIndexes.first();
        QString currentName = GetDirByIndex(selectedIndex);

        auto name = currentName.split("/").last();

        QLineEdit *lineEdit = new QLineEdit(name, this);
        setIndexWidget(selectedIndex, lineEdit);
        lineEdit->selectAll();
        lineEdit->setFocus();

        connect(
            lineEdit,
            &QLineEdit::returnPressed,
            this,
            [this, lineEdit, currentName, selectedIndex]()
            {
                QString newName = lineEdit->text();
                QDir currentDir = mp_model->fileInfo(selectedIndex).absolutePath();
                currentDir.rename(currentName, newName);
                lineEdit->hide();
            });
    }
}
