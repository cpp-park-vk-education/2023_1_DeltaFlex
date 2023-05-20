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
    void CreateFile();
    void CreateFolder();

protected:
    void ContextMenuRequested(const QPoint &pos);
    void HandleElementRenamed();
    void HandleElementDeleted();

protected:
    QFileSystemModel *mp_model;
};
