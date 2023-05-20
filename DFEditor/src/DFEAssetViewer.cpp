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

    QShortcut *rename_shortcut = new QShortcut(QKeySequence(Qt::Key_F2), this);
    connect(rename_shortcut, &QShortcut::activated, this, &DFEAssetViewer::HandleElementRenamed);

    QShortcut *delete_shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(delete_shortcut, &QShortcut::activated, this, &DFEAssetViewer::HandleElementDeleted);
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

void DFEAssetViewer::CreateFile()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new file"),
                                         tr("New file name"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        QString current_dir = mp_model->filePath(rootIndex());
        QDir dir(current_dir);
        QFile file(current_dir + '/' + text);
        file.open(QIODevice::WriteOnly);
        file.close();
    }
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

    connect(
        create_file,
        &QAction::triggered,
        this,
        &DFEAssetViewer::CreateFile);

    menu->addAction(create_file);
    menu->addAction(create_folder);
    menu->popup(mapToGlobal(pos));
}

void DFEAssetViewer::HandleElementRenamed()
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
                QFileInfo fileInfo = mp_model->fileInfo(selectedIndex);
                QDir currentDir = fileInfo.absolutePath();
                if (fileInfo.isDir())
                {
                    currentDir.rename(currentName, newName);
                }
                else
                {
                    currentDir.rename(currentName, currentDir.absolutePath() + "/" + newName);
                }
                lineEdit->hide();
            });
    }
}

void DFEAssetViewer::HandleElementDeleted()
{
    QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty())
    {
        QModelIndex selectedIndex = selectedIndexes.first();

        QFileInfo fileInfo = mp_model->fileInfo(selectedIndex);
        QDir currentDir = fileInfo.absolutePath();

        bool isDir = fileInfo.isDir();
        QString msg = isDir ? "folder" : "file";

        QMessageBox::StandardButton reply = QMessageBox::warning(
            this,
            "Deletion Attempt",
            "Are you sure you want to delete this " + msg + "?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            if (isDir)
            {
                QDir dir(currentDir.absoluteFilePath(fileInfo.fileName()));
                qDebug() << "Deleted folder " << currentDir.absoluteFilePath(fileInfo.fileName());
                dir.removeRecursively();
            }
            else
            {
                QFile file(currentDir.absoluteFilePath(fileInfo.fileName()));
                qDebug() << "Deleted file " << currentDir.absoluteFilePath(fileInfo.fileName());
                file.remove();
            }
        }
    }
}
