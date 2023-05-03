#include "DFEExpandingWidget.hpp"

DFEExpandingWidget::DFEExpandingWidget(const QString &title, const int animationDuration, QWidget *parent)
    : QWidget(parent),
      mp_toggleAnimation(new QParallelAnimationGroup(this)),
      mp_toggleButton(new QToolButton(this)),
      mp_contentArea(new QScrollArea(this)),
      mp_mainLayout(new QGridLayout(this)),
      mp_headerLine(new QFrame(this)),
      m_animationDuration(animationDuration)
{
    mp_toggleButton->setStyleSheet("QToolButton { border: none; }");
    mp_toggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mp_toggleButton->setArrowType(Qt::ArrowType::RightArrow);
    mp_toggleButton->setText(title);
    mp_toggleButton->setCheckable(true);
    mp_toggleButton->setChecked(false);

    mp_headerLine->setFrameShape(QFrame::HLine);
    mp_headerLine->setFrameShadow(QFrame::Sunken);
    mp_headerLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    mp_contentArea->setStyleSheet("QScrollArea { border: none; }");
    mp_contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mp_contentArea->setMinimumHeight(0);
    mp_contentArea->setMaximumHeight(0);

    mp_toggleAnimation->addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    mp_toggleAnimation->addAnimation(new QPropertyAnimation(this, "maximumHeight"));
    mp_toggleAnimation->addAnimation(new QPropertyAnimation(mp_contentArea, "maximumHeight"));

    mp_mainLayout->setVerticalSpacing(0);
    mp_mainLayout->setContentsMargins(0, 0, 0, 0);

    int row = 0;
    mp_mainLayout->addWidget(mp_toggleButton, row, 0, 1, 1, Qt::AlignLeft);
    mp_mainLayout->addWidget(mp_headerLine, row++, 2, 1, 1);
    mp_mainLayout->addWidget(mp_contentArea, row, 0, 1, 3);

    setLayout(mp_mainLayout);

    connect(
        mp_toggleButton,
        &QToolButton::clicked,
        [this](const bool checked)
        {
            mp_toggleButton->setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
            mp_toggleAnimation->setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
            mp_toggleAnimation->start();
        }
    );
}

DFEExpandingWidget::~DFEExpandingWidget()
{
    delete mp_toggleButton;
    delete mp_contentArea;
    delete mp_mainLayout;
    delete mp_headerLine;
}

void DFEExpandingWidget::setContentLayout(QLayout *contentLayout)
{
    delete mp_contentArea->layout();
    mp_contentArea->setLayout(contentLayout);

    const auto collapsedHeight = sizeHint().height() - mp_contentArea->maximumHeight();
    auto contentHeight = contentLayout->sizeHint().height();

    int i = 0;
    for (; i < mp_toggleAnimation->animationCount() - 1; ++i)
    {
        QPropertyAnimation *expandingWidgetAnim = static_cast<QPropertyAnimation *>(mp_toggleAnimation->animationAt(i));
        expandingWidgetAnim->setDuration(m_animationDuration);
        expandingWidgetAnim->setStartValue(collapsedHeight);
        expandingWidgetAnim->setEndValue(collapsedHeight + contentHeight);
    }

    QPropertyAnimation *contentAnim = static_cast<QPropertyAnimation *>(mp_toggleAnimation->animationAt(i));
    contentAnim->setDuration(m_animationDuration);
    contentAnim->setStartValue(0);
    contentAnim->setEndValue(contentHeight);
}
