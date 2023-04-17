#pragma once
#include <QtWidgets>

class DFEAssetViewer : public QListWidget
{
    Q_OBJECT
public:
    explicit DFEAssetViewer(QWidget *parent);
    void SetCurrentDirectory(const QString &dir);

private:
    QString currentDirectory;
};
