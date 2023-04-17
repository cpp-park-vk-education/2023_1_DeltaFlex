#include "DFEPropertiesPanel.hpp"
#include <QFrame>

DFEPropertiesPanel::DFEPropertiesPanel(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent),
      m_test(new DFEExpandingWidget("abober", 100, this))
{
    setWindowTitle("Properties");

    QVBoxLayout *lt = new QVBoxLayout();
    qDebug() << "aboba";
    QLineEdit *abober = new QLineEdit();
    lt->addWidget(abober);

    m_test->setContentLayout(lt);

    QWidget *container = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setAlignment(Qt::AlignTop);

    contentLayout->addWidget(m_test);
    container->setLayout(contentLayout);

    setWidget(container);
}

DFEPropertiesPanel::~DFEPropertiesPanel()
{
    delete m_test;
}
