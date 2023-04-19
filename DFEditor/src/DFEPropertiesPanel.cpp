#include "DFEPropertiesPanel.hpp"
#include <QFrame>

DFEPropertiesPanel::DFEPropertiesPanel(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent),
      mp_test(new DFEExpandingWidget("abober", 100, this))
{
    setWindowTitle("Properties");

    QVBoxLayout *lt = new QVBoxLayout();
    qDebug() << "aboba";
    QLineEdit *abober = new QLineEdit();
    lt->addWidget(abober);

    mp_test->setContentLayout(lt);

    QWidget *container = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setAlignment(Qt::AlignTop);

    contentLayout->addWidget(mp_test);
    container->setLayout(contentLayout);

    setWidget(container);
}

DFEPropertiesPanel::~DFEPropertiesPanel()
{
    delete mp_test;
}
