#include "excalendarwidget/excalendarwidget.h"
#include "excalendarwidget/excalendarwidget_p.h"


ExCalendarWidgetPrivate::ExCalendarWidgetPrivate(ExCalendarWidget *q)  :
    QObject(),
    q_ptr(q),
    is_animated(true)
{
}

ExCalendarWidgetPrivate::~ExCalendarWidgetPrivate()
{
}

void ExCalendarWidgetPrivate::initUi()
{
    Q_Q(ExCalendarWidget);

    QPalette palette = q->palette();
    palette.setBrush(QPalette::Window, palette.base());
    q->setPalette(palette);

    main_layout = new QVBoxLayout();
    main_layout->setContentsMargins(QMargins());
    main_layout->setSpacing(0);

    views_layout = new QStackedLayout();
    views_layout->setContentsMargins(QMargins());
    views_layout->setSpacing(0);

    navigator = new ExCalendarNavigator(q);
    main_layout->addWidget(navigator);

    views_frame = new QFrame(q);
    views_frame->setObjectName("views-frame");
    views_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(views_frame);

    month_view = new ExCalendarMonthView(views_frame);
    views_layout->addWidget(month_view);

    year_view = new ExCalendarYearView(views_frame);
    views_layout->addWidget(year_view);

    decade_view = new ExCalendarDecadeView(views_frame);
    views_layout->addWidget(decade_view);

    views_layout->setCurrentWidget(month_view);

    views_frame->setLayout(views_layout);

    q->setLayout(main_layout);

    connect(navigator, SIGNAL(stateChanged(int, int)), SLOT(onNavigatorStateChanged(int, int)));

    connect(year_view, SIGNAL(dateClicked(QDate)), navigator, SLOT(toPreviousState()));
    connect(decade_view, SIGNAL(dateClicked(QDate)), navigator, SLOT(toPreviousState()));

    connect(navigator, SIGNAL(previousPeriodButtonClicked()), SLOT(onNavigatorPreviousPeriodButtonClicked()));
    connect(navigator, SIGNAL(nextPeriodButtonClicked()), SLOT(onNavigatorNextPeriodButtonClicked()));

    connect(navigator, SIGNAL(currentDateChanged(QDate)), q, SLOT(setCurrentDate(QDate)));

    connect(month_view, SIGNAL(currentDateChanged(QDate)), q, SLOT(setCurrentDate(QDate)));
    connect(year_view, SIGNAL(currentDateChanged(QDate)), q, SLOT(setCurrentDate(QDate)));
    connect(decade_view, SIGNAL(currentDateChanged(QDate)), q, SLOT(setCurrentDate(QDate)));
}

void ExCalendarWidgetPrivate::onNavigatorStateChanged(int state, int previous_state)
{
    switch (ExCalendarNavigator::State(state)) {
        case ExCalendarNavigator::StateMonth:
            views_layout->setCurrentWidget(month_view);
            break;
        case ExCalendarNavigator::StateYear:
            views_layout->setCurrentWidget(year_view);
            break;
        case ExCalendarNavigator::StateDecade:
            views_layout->setCurrentWidget(decade_view);
            break;
        default:
            break;
    }

    if (is_animated) {
        ExCalendarView *current_view = qobject_cast<ExCalendarView *>(views_layout->currentWidget());
        if (current_view != 0) {
            if (state == ExCalendarNavigator::StateMonth && previous_state == ExCalendarNavigator::StateDecade)
                current_view->animatedSlideTop();
            else if (state < previous_state)
                current_view->animatedSlideBottom();
            else if (state > previous_state)
                current_view->animatedSlideTop();
        }
    }
}

void ExCalendarWidgetPrivate::onNavigatorPreviousPeriodButtonClicked()
{
    if (is_animated) {
        ExCalendarView *current_view = qobject_cast<ExCalendarView *>(views_layout->currentWidget());
        if (current_view != 0)
            current_view->animatedSlideLeft();
    }
}

void ExCalendarWidgetPrivate::onNavigatorNextPeriodButtonClicked()
{
    if (is_animated) {
        ExCalendarView *current_view = qobject_cast<ExCalendarView *>(views_layout->currentWidget());
        if (current_view != 0)
            current_view->animatedSlideRight();
    }
}
