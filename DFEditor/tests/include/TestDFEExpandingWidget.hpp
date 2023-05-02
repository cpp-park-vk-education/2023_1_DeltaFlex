#pragma once

#include <DFEExpandingWidget.hpp>

class TestDFEExpandingWidget : public DFEExpandingWidget
{
public:
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
