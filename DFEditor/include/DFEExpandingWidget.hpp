#pragma once

#include <QtWidgets>
#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>

class DFEExpandingWidget : public QWidget
{
public:
    DFEExpandingWidget(const QString &title = "", const int animationDuration = 100, QWidget *parent = nullptr);
    ~DFEExpandingWidget();
    void setContentLayout(QLayout *contentLayout);

protected:
    QGridLayout *mp_mainLayout;
    QToolButton *mp_toggleButton;
    QFrame *mp_headerLine;
    QParallelAnimationGroup *mp_toggleAnimation;
    QScrollArea *mp_contentArea;
    int m_animationDuration = 300;
};
