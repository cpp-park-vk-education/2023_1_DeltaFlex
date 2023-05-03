#pragma once

#include <DFEExpandingWidget.hpp>

class TestDFEExpandingWidget : public DFEExpandingWidget
{
public:
    TestDFEExpandingWidget(const QString &title = "", const int animationDuration = 100, QWidget *parent = nullptr)
        : DFEExpandingWidget(title, animationDuration, parent)
    {
    }

    QGridLayout *GetMainLayout()
    {
        return mp_mainLayout;
    }

    QToolButton *GetToggleButton()
    {
        return mp_toggleButton;
    }

    QFrame *GetHeaderLine()
    {
        return mp_headerLine;
    }

    QParallelAnimationGroup *GetToggleAnimation()
    {
        return mp_toggleAnimation;
    }

    QScrollArea *GetContentArea()
    {
        return mp_contentArea;
    }

    int GetAnimationDuration()
    {
        return m_animationDuration;
    }
};
