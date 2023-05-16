#include "DFEPropertiesPanel.hpp"
#include <QFrame>

DFEPropertiesPanel::DFEPropertiesPanel(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent),
    mp_object()
{
    setWindowTitle("Properties");
}

void DFEPropertiesPanel::ChangeProperties(std::shared_ptr<IDFESceneObject> &object)
{
    mp_object = object;

    while (!m_properties.empty())
    {
        delete m_properties.back();
        m_properties.pop_back();
    }

    QVBoxLayout *lt = new QVBoxLayout();
    QLineEdit *line_edit = new QLineEdit();
    line_edit->setText(mp_object->GetName());
    lt->addWidget(line_edit);

    m_properties.push_back(new DFEExpandingWidget("Name"));
    m_properties.back()->setContentLayout(lt);

    QWidget *container = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setAlignment(Qt::AlignTop);

    contentLayout->addWidget(m_properties.back());
    container->setLayout(contentLayout);

    setWidget(container);
}
