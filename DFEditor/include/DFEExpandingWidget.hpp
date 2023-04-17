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
    explicit DFEExpandingWidget(const QString &title = "", const int animationDuration = 100, QWidget *parent = nullptr);
    ~DFEExpandingWidget();
    void setContentLayout(QLayout *contentLayout);

private:
    QGridLayout *m_mainLayout;
    QToolButton *m_toggleButton;
    QFrame *m_headerLine;
    QParallelAnimationGroup *m_toggleAnimation;
    QScrollArea *m_contentArea;
    int m_animationDuration = 300;
};
