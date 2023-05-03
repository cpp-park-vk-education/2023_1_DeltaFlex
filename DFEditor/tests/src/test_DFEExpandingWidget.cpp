#include <QtTest>
#include <QObject>
#include <TestDFEExpandingWidget.hpp>

class test_DFEExpandingWidget : public QObject
{
public:
    void testConstructor()
    {
        TestDFEExpandingWidget *expWidget = new TestDFEExpandingWidget(
            "This is a test widget",
            500
        );

        delete expWidget;
    }
};