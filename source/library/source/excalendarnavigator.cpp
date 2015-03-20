#include <QDate>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>

#include "excalendarwidget/excalendarnavigator.h"


class ExCalendarNavigatorPrivate {
    Q_DECLARE_PUBLIC(ExCalendarNavigator)

    ExCalendarNavigator *q_ptr;

    QDate min_date;
    QDate max_date;

    QDate current_date;

    ExCalendarNavigator::State state;

    QHBoxLayout *layout;

    QPushButton *view_button;

    QPushButton *previous_period_button;
    QPushButton *next_period_button;

    ExCalendarNavigatorPrivate(ExCalendarNavigator *q) :
        q_ptr(q),
        current_date(),
        state(ExCalendarNavigator::StateMonth) {}
    ~ExCalendarNavigatorPrivate() {}

    void initUi()
    {
        Q_Q(ExCalendarNavigator);

        layout = new QHBoxLayout(q);
        layout->setContentsMargins(QMargins());
        layout->setSpacing(0);

        view_button = new QPushButton(q);
        view_button->setObjectName("view-button");
        view_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        view_button->setFocusPolicy(Qt::NoFocus);
        view_button->setFlat(true);

        previous_period_button = new QPushButton(q);
        previous_period_button->setObjectName("previous-period-button");
        previous_period_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        previous_period_button->setFixedWidth(30);
        previous_period_button->setFocusPolicy(Qt::NoFocus);
        previous_period_button->setIconSize(QSize(16, 16));
        previous_period_button->setIcon(QIcon::fromTheme("go-previous"));
        previous_period_button->setFlat(true);

        next_period_button = new QPushButton(q);
        next_period_button->setObjectName("next-period-button");
        next_period_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        next_period_button->setFocusPolicy(Qt::NoFocus);
        next_period_button->setFixedWidth(30);
        next_period_button->setIconSize(QSize(16, 16));
        next_period_button->setIcon(QIcon::fromTheme("go-next"));
        next_period_button->setFlat(true);

        layout->addWidget(previous_period_button);
        layout->addWidget(view_button);
        layout->addWidget(next_period_button);

        q->setLayout(layout);

        updateUi();
    }

    void updateUi()
    {
        bool no_previous_period = true;
        bool no_next_period = true;

        switch (state) {
            case ExCalendarNavigator::StateMonth:
                view_button->setText(current_date.toString("MMMM yyyy"));

                no_previous_period = min_date.isValid() &&
                                     current_date.isValid() &&
                                     (min_date.year() >= current_date.year()) &&
                                     (min_date.month() >= current_date.month());

                no_next_period = max_date.isValid() &&
                                 current_date.isValid() &&
                                 (max_date.year() <= current_date.year()) &&
                                 (max_date.month() <= current_date.month());

                break;
            case ExCalendarNavigator::StateYear:
                view_button->setText(current_date.toString("yyyy"));

                no_previous_period = min_date.isValid() &&
                                     current_date.isValid() &&
                                     (min_date.year() >= current_date.year());

                no_next_period = max_date.isValid() &&
                                 current_date.isValid() &&
                                 (max_date.year() <= current_date.year());

                break;
            case ExCalendarNavigator::StateDecade:
                view_button->setText(QString("%1 - %2")
                                     .arg(current_date.year() - 5)
                                     .arg(current_date.year() + 6));

                no_previous_period = min_date.isValid() &&
                                     current_date.isValid() &&
                                     ((min_date.year() - current_date.year()) > -5);

                no_next_period = max_date.isValid() &&
                                 current_date.isValid() &&
                                 ((max_date.year() - current_date.year()) < 6);

                break;
            default:
                break;
        }

        previous_period_button->setDisabled(no_previous_period);
        next_period_button->setDisabled(no_next_period);
    }
};

ExCalendarNavigator::ExCalendarNavigator(QWidget *parent) :
    QFrame(parent),
    d_ptr(new ExCalendarNavigatorPrivate(this))
{
    setObjectName("navigator");

    Q_D(ExCalendarNavigator);
    d->initUi();

    connect(d->view_button, SIGNAL(clicked()), SLOT(onViewButtonClicked()));

    connect(d->previous_period_button, SIGNAL(clicked()), SLOT(onPreviousPeriodButtonClicked()));
    connect(d->next_period_button, SIGNAL(clicked()), SLOT(onNextPeriodButtonClicked()));

    connect(d->previous_period_button, SIGNAL(clicked()), SIGNAL(previousPeriodButtonClicked()));
    connect(d->next_period_button, SIGNAL(clicked()), SIGNAL(nextPeriodButtonClicked()));
}

ExCalendarNavigator::~ExCalendarNavigator()
{
    delete d_ptr;
}

QDate ExCalendarNavigator::minimumDate() const
{
    Q_D(const ExCalendarNavigator);
    return d->min_date;
}

QDate ExCalendarNavigator::maximumDate() const
{
    Q_D(const ExCalendarNavigator);
    return d->max_date;
}

QDate ExCalendarNavigator::currentDate() const
{
    Q_D(const ExCalendarNavigator);
    return d->current_date;
}

QPushButton *ExCalendarNavigator::previousPeriodButton() const
{
    Q_D(const ExCalendarNavigator);
    return d->previous_period_button;
}

QPushButton *ExCalendarNavigator::nextPeriodButton() const
{
    Q_D(const ExCalendarNavigator);
    return d->next_period_button;
}

void ExCalendarNavigator::setMinimumDate(const QDate &date)
{
    Q_D(ExCalendarNavigator);
    d->min_date = date;
}

void ExCalendarNavigator::setMaximumDate(const QDate &date)
{
    Q_D(ExCalendarNavigator);
    d->max_date = date;
}

void ExCalendarNavigator::setDateRange(const QDate &min_date, const QDate &max_date)
{
    Q_D(ExCalendarNavigator);
    d->min_date = min_date;
    d->max_date = max_date;
}

void ExCalendarNavigator::setCurrentDate(const QDate &date)
{
    Q_D(ExCalendarNavigator);
    d->current_date = date;
    d->updateUi();
}

void ExCalendarNavigator::toPreviousState()
{
    Q_D(ExCalendarNavigator);

    switch (d->state) {
        case StateMonth:
            break;
        case StateYear:
            d->state = StateMonth;
            d->updateUi();
            emit stateChanged(d->state, StateYear);
            break;
        case StateDecade:
            d->state = StateYear;
            d->updateUi();
            emit stateChanged(d->state, StateDecade);
            break;
        default:
            break;
    }
}

void ExCalendarNavigator::toNextState()
{
    Q_D(ExCalendarNavigator);

    switch (d->state) {
        case StateMonth:
            d->state = StateYear;
            emit stateChanged(d->state, StateMonth);
            d->updateUi();
            break;
        case StateYear:
            d->state = StateDecade;
            d->updateUi();
            emit stateChanged(d->state, StateYear);
            break;
        case StateDecade:
            d->state = StateMonth;
            d->updateUi();
            emit stateChanged(d->state, StateDecade);
            break;
        default:
            break;
    }
}

void ExCalendarNavigator::onViewButtonClicked()
{
    toNextState();
}

void ExCalendarNavigator::onPreviousPeriodButtonClicked()
{
    Q_D(ExCalendarNavigator);

    switch (d->state) {
        case StateMonth:
            emit currentDateChanged(d->current_date.addMonths(-1));
            break;
        case StateYear:
            emit currentDateChanged(d->current_date.addYears(-1));
            break;
        case StateDecade:
            emit currentDateChanged(d->current_date.addYears(-12));
            break;
        default:
            break;
    }
}

void ExCalendarNavigator::onNextPeriodButtonClicked()
{
    Q_D(ExCalendarNavigator);

    switch (d->state) {
        case StateMonth:
            emit currentDateChanged(d->current_date.addMonths(1));
            break;
        case StateYear:
            emit currentDateChanged(d->current_date.addYears(1));
            break;
        case StateDecade:
            emit currentDateChanged(d->current_date.addYears(12));
            break;
        default:
            break;
    }
}
