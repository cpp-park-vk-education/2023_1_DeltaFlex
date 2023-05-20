#include "DFEProjectExplorer.hpp"

#include <QFrame>
#include <QIcon>
#include <QDebug>
#include <QErrorMessage>

DFEProjectExplorer::DFEProjectExplorer(QWidget *parent)
    : QTreeView(parent),
      mp_model(new QFileSystemModel())
{
    setFrameShape(QFrame::NoFrame);

    setWordWrap(true);
    setHeaderHidden(true);

    mp_model->setRootPath("");
    setModel(mp_model);
    
    mp_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    setRootIndex(mp_model->index("/"));

    setStyleSheet("QTreeView { font: 12px }");

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
}

void DFEProjectExplorer::UpdateView(const QString &dir)
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

QString DFEProjectExplorer::GetDirByIndex(const QModelIndex &index)
{
    return mp_model->filePath(index);
}

void DFEProjectExplorer::ExpandDirectory(const QString &dir)
{
    expand(mp_model->index(dir));
}
