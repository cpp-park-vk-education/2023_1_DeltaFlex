#pragma once

#include "DFEExpandingWidget.hpp"
#include <QObject>
#include <QtTest>

class DFEExpandingWidgetWrapper : public DFEExpandingWidget
{
public:
    DFEExpandingWidgetWrapper(const QString &title = "", const int animationDuration = 100, QWidget *parent = nullptr)
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


class test_DFEExpandingWidget : public QObject
{
    Q_OBJECT
public:
    explicit test_DFEExpandingWidget(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testConstructor()
    {
        DFEExpandingWidgetWrapper *obj = new DFEExpandingWidgetWrapper(
            "This is a cool widget",
            500
        );

        QVERIFY2(obj->GetMainLayout() != nullptr, "Main Layout was not initialized");
        QVERIFY2(obj->GetToggleButton() != nullptr, "Toggle Button was not initialized");
        QVERIFY2(obj->GetHeaderLine() != nullptr, "Header Line was not initialized");
        QVERIFY2(obj->GetContentArea() != nullptr, "Content Area was not initialized");
        QVERIFY2(obj->GetToggleAnimation() != nullptr, "Toggle Animation was not initialized");

        QCOMPARE(obj->GetToggleButton()->text(), "This is a cool widget");
        QCOMPARE(obj->GetAnimationDuration(), 500);

        delete obj;
    }

    void testSetContentLayout()
    {
        DFEExpandingWidgetWrapper *obj = new DFEExpandingWidgetWrapper("Hello");

        auto oldLayout = obj->GetContentArea()->layout();

        QLayout *contentLayout = new QVBoxLayout();
        obj->setContentLayout(contentLayout);

        QVERIFY2(oldLayout != obj->GetContentArea()->layout(), "Content layout was not set properly");
        

        delete obj;
    }
};