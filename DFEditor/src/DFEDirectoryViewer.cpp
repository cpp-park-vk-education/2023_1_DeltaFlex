#include "DFEDirectoryViewer.hpp"
#include <QFrame>
#include <QDebug>

DFEDirectoryViewer::DFEDirectoryViewer(QWidget *parent)
    : QWidget(parent), 
      m_pathEdit(new QLineEdit(this)),
      m_explorer(new QTreeView(this)),
      m_verticalLayout(new QVBoxLayout(this))
{
    m_explorer->setFrameShape(QFrame::NoFrame);
    m_pathEdit->setFrame(false);
    
    connect(m_pathEdit, &QLineEdit::editingFinished, [&](){ qDebug() << m_pathEdit->text(); });

    m_verticalLayout->addWidget(m_pathEdit);
    m_verticalLayout->addWidget(m_explorer);

    setLayout(m_verticalLayout);
}

DFEDirectoryViewer::~DFEDirectoryViewer()
{
    delete m_pathEdit;
    delete m_explorer;
    delete m_verticalLayout;
}
