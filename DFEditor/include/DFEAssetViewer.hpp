#pragma once
#include <QtWidgets>
#include <QFileSystemModel>

class DFEAssetViewer : public QListView
{
    Q_OBJECT
public:
    explicit DFEAssetViewer(QWidget *parent = nullptr);

public:
    void UpdateView(const QString &dir);
    QString GetDirByIndex(const QModelIndex &index);
    
public slots:
    // void CreateGenericFile();
    void CreateFolder();

protected:
    void ContextMenuRequested(const QPoint &pos);
    void handleFolderRenamed();

protected:
    QFileSystemModel *mp_model;
};
