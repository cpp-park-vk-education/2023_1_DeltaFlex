#include "DFEExpandingWidget.hpp"

DFEExpandingWidget::DFEExpandingWidget(const QString &title, const int animationDuration, QWidget *parent)
    : QWidget(parent),
      m_toggleAnimation(new QParallelAnimationGroup(this)),
      m_toggleButton(new QToolButton(this)),
      m_contentArea(new QScrollArea(this)),
      m_mainLayout(new QGridLayout(this)),
      m_headerLine(new QFrame(this))
{
    m_toggleButton->setStyleSheet("QToolButton { border: none; }");
    m_toggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleButton->setArrowType(Qt::ArrowType::RightArrow);
    m_toggleButton->setText(title);
    m_toggleButton->setCheckable(true);
    m_toggleButton->setChecked(false);

    m_headerLine->setFrameShape(QFrame::HLine);
    m_headerLine->setFrameShadow(QFrame::Sunken);
    m_headerLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    m_contentArea->setStyleSheet("QScrollArea { border: none; }");
    m_contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_contentArea->setMinimumHeight(0);
    m_contentArea->setMaximumHeight(0);

    m_toggleAnimation->addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    m_toggleAnimation->addAnimation(new QPropertyAnimation(this, "maximumHeight"));
    m_toggleAnimation->addAnimation(new QPropertyAnimation(m_contentArea, "maximumHeight"));

    m_mainLayout->setVerticalSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    int row = 0;
    m_mainLayout->addWidget(m_toggleButton, row, 0, 1, 1, Qt::AlignLeft);
    m_mainLayout->addWidget(m_headerLine, row++, 2, 1, 1);
    m_mainLayout->addWidget(m_contentArea, row, 0, 1, 3);

    setLayout(m_mainLayout);

    connect(
        m_toggleButton,
        &QToolButton::clicked,
        [this](const bool checked)
        {
            m_toggleButton->setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
            m_toggleAnimation->setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
            m_toggleAnimation->start();
        }
    );
}

DFEExpandingWidget::~DFEExpandingWidget()
{
    delete m_toggleButton;
    delete m_contentArea;
    delete m_mainLayout;
    delete m_headerLine;
}

void DFEExpandingWidget::setContentLayout(QLayout *contentLayout)
{
    delete m_contentArea->layout();
    m_contentArea->setLayout(contentLayout);

    const auto collapsedHeight = sizeHint().height() - m_contentArea->maximumHeight();
    auto contentHeight = contentLayout->sizeHint().height();

    int i = 0;
    for (; i < m_toggleAnimation->animationCount() - 1; ++i)
    {
        QPropertyAnimation *expandingWidgetAnim = static_cast<QPropertyAnimation *>(m_toggleAnimation->animationAt(i));
        expandingWidgetAnim->setDuration(m_animationDuration);
        expandingWidgetAnim->setStartValue(collapsedHeight);
        expandingWidgetAnim->setEndValue(collapsedHeight + contentHeight);
    }

    QPropertyAnimation *contentAnim = static_cast<QPropertyAnimation *>(m_toggleAnimation->animationAt(i));
    contentAnim->setDuration(m_animationDuration);
    contentAnim->setStartValue(0);
    contentAnim->setEndValue(contentHeight);
}
