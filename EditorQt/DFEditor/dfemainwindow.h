#ifndef DFEMAINWINDOW_H
#define DFEMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DFEMainWindow; }
QT_END_NAMESPACE

class DFEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DFEMainWindow(QWidget *parent = nullptr);
    ~DFEMainWindow();

private:
    Ui::DFEMainWindow *ui;
};
#endif // DFEMAINWINDOW_H
