#include <DFEAssetViewer.hpp>

#include <QObject>
#include <QtTest>

class test_DFEAssetViewer : public QObject
{
    Q_OBJECT

public:
    explicit test_DFEAssetViewer(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testUpdateView()
    {
        DFEAssetViewer *viewer = new DFEAssetViewer();
        QListView *tstView = new QListView();
        QFileSystemModel *tstModel = new QFileSystemModel();

        tstModel->setRootPath("/home");
        tstView->setModel(tstModel);

        viewer->UpdateView("/home");
        QCOMPARE(viewer->rootIndex(), tstView->rootIndex());

        delete viewer;
        delete tstView;
        delete tstModel;
    }
};  

QTEST_MAIN(test_DFEAssetViewer)

#include "test_DFEAssetViewer.moc"
