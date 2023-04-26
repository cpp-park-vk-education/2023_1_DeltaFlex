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

private:
    QFileSystemModel *mp_model;
};
